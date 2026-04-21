#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace solution {

struct MovieMetadata {
  struct Role {
    std::string star;
    std::string name;
  };

  struct Director {
    std::string name;
  };

  struct Writer {
    std::string name;
  };

  unsigned id = 0;
  std::string title;
  unsigned year = 0;
  unsigned length = 0;
  std::vector<Role> cast;
  std::vector<Director> directors;
  std::vector<Writer> writers;
};

struct ParseError {
  enum class Code : std::uint8_t {
    FileLoadingFailed,
    MissingAttribute,
    MissingNode,
    ParsingNodeFailed,
  };

  Code code;
  std::string message;
};

using DeserializeReturnType =
    std::pair<std::vector<MovieMetadata>, std::optional<ParseError>>;
DeserializeReturnType Deserialize(const std::string& file_path);
// serialize movies list to XML file
// and deserialize

}  // namespace solution