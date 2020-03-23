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

class RowIndexOutOfRangeException : public Array2DException {
public:
    RowIndexOutOfRangeException(unsigned incorrect_row,
                                unsigned max_correct_row)
        : Array2DException("") // todo
    {
        message = "Row index (" + std::to_string(incorrect_row)
                + ") is greater than the maximum possible one ("
                + std::to_string(max_correct_row) + ")";
    }

private:
    std::string message;
};

class ColumnIndexOutOfRangeException : public Array2DException {
public:
    ColumnIndexOutOfRangeException(unsigned incorrect_row,
                                unsigned max_correct_row)
        : Array2DException("") // todo
    {
        message = "Column index (" + std::to_string(incorrect_row)
                + ") is greater than the maximum possible one ("
                + std::to_string(max_correct_row) + ")";
    }

private:
    std::string message;
};