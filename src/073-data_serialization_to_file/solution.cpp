#include "solution.hpp"

#include <format>
#include <functional>
#include <iostream>
#include <optional>
#include <string_view>
#include <utility>
#include <vector>

#include "pugixml.hpp"

namespace solution {

namespace {

template <typename... Attributes>
bool NodeHasAllAttributes(const pugi::xml_node& node,
                          Attributes... attributes) {
  return ((!node.attribute(attributes).empty()) && ...);
}

template <typename... Children>
bool NodeHasAllChildren(const pugi::xml_node& node, Children... children) {
  return ((!node.child(children).empty()) && ...);
}

template <typename T>
struct AttributeParser {
  std::string_view name;
  T* target;
  // Returns nullopt if can't parse the attribute.
  std::function<std::optional<T>(const pugi::xml_attribute&)> parse;
};

AttributeParser<unsigned> MakeUnsignedAttributeParser(std::string_view name,
                                                      unsigned* target) {
  return AttributeParser<unsigned>{
      .name = name,
      .target = target,
      .parse =
          [](const auto& attribute) {
            return std::make_optional(attribute.as_uint());
          },
  };
}

AttributeParser<std::string> MakeStringAttributeParser(std::string_view name,
                                                       std::string* target) {
  return AttributeParser<std::string>{
      .name = name,
      .target = target,
      .parse =
          [](const auto& attribute) {
            return std::make_optional(attribute.as_string());
          },
  };
}

// Returns nullopt if succeeded, otherwise returns attribute name that failed
// first.
template <typename T>
std::optional<std::string_view> ParseAttribute(const pugi::xml_node& node,
                                               AttributeParser<T> parser) {
  auto attribute = node.attribute(parser.name);
  if (attribute.empty()) {
    return std::make_optional(parser.name);
  }

  auto parse_result = parser.parse(attribute);
  if (!parse_result.has_value()) {
    return std::make_optional(parser.name);
  }

  *parser.target = std::move(parse_result.value());
  return std::nullopt;
}

template <typename... Parsers>
std::optional<ParseError> ParseAttributes(const pugi::xml_node& node,
                                          Parsers&&... parsers) {
  std::optional<std::string_view> failed;
  ((failed = ParseAttribute(node, std::forward<Parsers>(parsers)),
    failed.has_value()) ||
   ...);

  return failed.has_value() ? std::make_optional(ParseError{
                                  .code = ParseError::Code::MissingAttribute,
                                  .message = std::format(
                                      "Missing attribute: {}", failed.value()),
                              })
                            : std::nullopt;
}

std::optional<std::vector<MovieMetadata::Role>> ParseCastNode(
    const pugi::xml_node& cast_node) {
  if (cast_node.empty()) {
    return std::nullopt;
  }

  std::vector<MovieMetadata::Role> roles;
  for (const auto& role_node : cast_node.children()) {
    if (!NodeHasAllAttributes(role_node, "star", "name")) {
      return {};
    }
    roles.push_back({
        .star = role_node.attribute("star").as_string(),
        .name = role_node.attribute("name").as_string(),
    });
  }
  return roles;
}

template <typename T>
struct ChildParser {
  std::string_view name;
  T* target;
  // Returns nullopt if can't parse the attribute.
  std::function<std::optional<T>(const pugi::xml_node&)> parse;
};

// TODO: create a common base for this and ParseAttribute
template <typename T>
std::optional<ParseError> ParseChild(const pugi::xml_node& node,
                                     ChildParser<T> parser) {
  auto child = node.child(parser.name);
  if (child.empty()) {
    return std::make_optional(ParseError{
        .code = ParseError::Code::MissingNode,
        .message = std::format("Node not found: {}", parser.name),
    });
  }

  auto parse_result = parser.parse(child);
  if (!parse_result.has_value()) {
    return std::make_optional(ParseError{
        .code = ParseError::Code::ParsingNodeFailed,
        .message = std::format("Could not parse node: {}", parser.name),
    });
  }

  *parser.target = std::move(parse_result.value());
  return std::nullopt;
}

template <typename... Parsers>
std::optional<ParseError> ParseChildren(const pugi::xml_node& node,
                                        Parsers&&... parsers) {
  std::optional<ParseError> parse_error;
  ((parse_error = ParseChild(node, std::forward<Parsers>(parsers)),
    parse_error.has_value()) ||
   ...);

  return parse_error;
}

std::pair<MovieMetadata, std::optional<ParseError>> ParseMovieMetadata(
    const pugi::xml_node& xml_node) {
  MovieMetadata movie_metadata;

  auto parse_error = ParseAttributes(
      xml_node, MakeUnsignedAttributeParser("id", &movie_metadata.id),
      MakeStringAttributeParser("title", &movie_metadata.title),
      MakeUnsignedAttributeParser("year", &movie_metadata.year),
      MakeUnsignedAttributeParser("length", &movie_metadata.length));

  if (parse_error.has_value()) {
    // TODO: would const parse_error prevent RVO?
    return std::make_pair(movie_metadata, parse_error);
  }

  // TODO: add parsing children vector
  // TODO: implement std::expected?
  parse_error = ParseChildren(
      xml_node,
      ChildParser<std::vector<MovieMetadata::Role>>{
          .name = "cast",
          .target = &movie_metadata.cast,
          .parse = [](const auto& node) { return ParseCastNode(node); },
      });

  return std::make_pair(movie_metadata, parse_error);
  //   if (!NodeHasAllAttributes(xml_node, "id", "title", "year", "length") ||
  //       !NodeHasAllChildren(xml_node, "cast", "directors", "writers")) {
  //     return std::nullopt;
  //   }

  //   return MovieMetadata{
  //       .id = xml_node.attribute("id").as_uint(),
  //       .title = xml_node.attribute("title").as_string(),
  //       .year = xml_node.attribute("year").as_uint(),
  //       .length = xml_node.attribute("length").as_uint(),
  //       .cast = ParseCastNode(xml_node.child("cast")),
  //   };
}

DeserializeReturnType MakeDeserializeError(ParseError error) {
  return std::make_pair(std::vector<MovieMetadata>{},
                        std::make_optional(std::move(error)));
}

}  // namespace

// TODO: pre-allocate vectors

DeserializeReturnType Deserialize(const std::string& file_path) {
  pugi::xml_document xml_document;
  const auto result = xml_document.load_file(file_path.c_str());
  if (!result) {
    return MakeDeserializeError(ParseError{
        .code = ParseError::Code::FileLoadingFailed,
        .message = result.description(),
    });
  }

  const auto movie_nodes = xml_document.child("movies");
  if (movie_nodes.empty()) {
    return MakeDeserializeError(ParseError{
        .code = ParseError::Code::MissingNode,
        .message = std::format("\"movies\" nodes not found"),
    });
  }

  std::vector<MovieMetadata> movies;

  for (auto movie_node = movie_nodes.first_child(); !movie_node.empty();
       movie_node = movie_node.next_sibling("movie")) {
    auto [movie, error] = ParseMovieMetadata(movie_node);
    if (error.has_value()) {
      return MakeDeserializeError(error.value());
    }
    movies.push_back(std::move(movie));
  }

  return std::make_pair(movies, std::nullopt);
}

}  // namespace solution