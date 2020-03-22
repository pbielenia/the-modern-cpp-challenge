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

    unsigned number_of_elements{R * C};
    std::vector<T> elements;

};
