#include <stdexcept>

struct Array2DException : public std::runtime_error {
    Array2DException(char const* const message) throw()
        : std::runtime_error(message) { }

    virtual char const* what() const throw() { return exception::what(); }
};

class PassedElementsExceedArraySizeException : public Array2DException {
public:
    PassedElementsExceedArraySizeException(unsigned elements_length,
                                           unsigned array_length)
        : Array2DException("") // todo
    {
        message = "Number or passed elements ("
                + std::to_string(elements_length)
                + ") exceeds a number of elements in the array ("
                + std::to_string(array_length) + ")";
    }

private:
    std::string message;
};

class PassedElementsDoNotReachArraySizeException : public Array2DException {
public:
    PassedElementsDoNotReachArraySizeException(unsigned elements_length,
                                               unsigned array_length)
        : Array2DException("") // todo
    {
        message = "Number or passed elements ("
                + std::to_string(elements_length)
                + ") is less that a number of elements in the array ("
                + std::to_string(array_length) + ")";
    }

private:
    std::string message;
};
