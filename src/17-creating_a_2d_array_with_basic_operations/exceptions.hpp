#include <stdexcept>

class Array2DException : public std::runtime_error {
public:
    explicit Array2DException(char const* const message)
        : std::runtime_error(message) { }
    explicit Array2DException(const std::string& message)
        : std::runtime_error(message) { }

    virtual char const* what() const throw() { return exception::what(); }

protected:
    std::string message;
};

class PassedElementsExceedArraySizeException : public Array2DException {
public:
    PassedElementsExceedArraySizeException(unsigned elements_length,
                                           unsigned array_length)
        : Array2DException(message)
    {
        message = "Number or passed elements ("
                + std::to_string(elements_length)
                + ") exceeds a number of elements in the array ("
                + std::to_string(array_length) + ")";
    }
};

class PassedElementsDoNotReachArraySizeException : public Array2DException {
public:
    PassedElementsDoNotReachArraySizeException(unsigned elements_length,
                                               unsigned array_length)
        : Array2DException(message)
    {
        message = "Number or passed elements ("
                + std::to_string(elements_length)
                + ") is less that a number of elements in the array ("
                + std::to_string(array_length) + ")";
    }
};

class RowIndexOutOfRangeException : public Array2DException {
public:
    RowIndexOutOfRangeException(unsigned incorrect_row,
                                unsigned max_correct_row)
        : Array2DException(message)
    {
        message = "Row index (" + std::to_string(incorrect_row)
                + ") is greater than the maximum possible one ("
                + std::to_string(max_correct_row) + ")";
    }
};

class ColumnIndexOutOfRangeException : public Array2DException {
public:
    ColumnIndexOutOfRangeException(unsigned incorrect_row,
                                   unsigned max_correct_row)
        : Array2DException(message)
    {
        message = "Column index (" + std::to_string(incorrect_row)
                + ") is greater than the maximum possible one ("
                + std::to_string(max_correct_row) + ")";
    }
};
