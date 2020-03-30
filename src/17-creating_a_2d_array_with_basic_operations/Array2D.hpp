#pragma once

#include <vector>
#include "exceptions.hpp"

#include <iostream>

template<typename T, unsigned R, unsigned C>
class Array2D {
public:
    Array2D()
        : elements(number_of_elements) { }

    Array2D(std::initializer_list<T> elements)
        : elements(elements)
    {
        check_length_after_init(); 
    }

    T& at(unsigned const row, unsigned const column)
    {
        check_array_limits(row, column);
        return elements.at(get_index(row, column));
    }

    const T& at(unsigned const row, unsigned const column) const
    {
        check_array_limits(row, column);
        return elements.at(get_index(row, column));
    }

    constexpr T* data()
    {
        return elements.data();
    }

    constexpr const T* data() const
    {
        return elements.data();
    }

    constexpr size_t size() const
    {
        return number_of_elements;
    }

private:
    void check_length_after_init()
    {
        if (number_of_elements < elements.size()) {
            throw PassedElementsExceedArraySizeException(
                elements.size(), number_of_elements);
            
        } else if (number_of_elements > elements.size()) {
            throw PassedElementsDoNotReachArraySizeException(
                elements.size(), number_of_elements);
        }
    }

    void check_array_limits(unsigned row, unsigned column) const
    {
        if (number_of_rows <= row)
            throw RowIndexOutOfRangeException(row, number_of_rows);
        if (number_of_columns <= column)
            throw ColumnIndexOutOfRangeException(column, number_of_columns);
    }

    constexpr unsigned get_index(unsigned row, unsigned column) const noexcept
    {
        return row * number_of_rows + column;
    }

    unsigned number_of_elements{R * C};
    unsigned number_of_rows{R};
    unsigned number_of_columns{C};
    std::vector<T> elements;

};
