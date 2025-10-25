#pragma once

#include <initializer_list>

#include "figure.hpp"

// We don't delete in ~Array, Pop(), Figures because the array actually doesn't own them
// This is default behaviour, the same as in the std::vector
// So the user has to manually delete them

namespace array {

class Array {
public:
    Array();
    Array(std::size_t size);
    Array(const std::initializer_list<Geometry::Figure*>& il);

    Array(const Array& other);
    Array(Array&& other) noexcept;
    virtual ~Array() noexcept;

    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;

    std::size_t Size() const noexcept;
    std::size_t Capacity() const noexcept;

    Geometry::Figure*& operator[](std::size_t i);
    Geometry::Figure* const& operator[](std::size_t i) const;

    Geometry::Figure*& At(std::size_t i);
    Geometry::Figure* const& At(std::size_t i) const;

    void PushBack(Geometry::Figure* ch);
    void Reserve(std::size_t size);
    void PopBack();
    void Pop(std::size_t i);

    Geometry::Figure*& Front();
    Geometry::Figure* const& Front() const;

    Geometry::Figure*& Back();
    Geometry::Figure* const& Back() const;
    

    friend bool operator==(const Array& first, const Array& second) noexcept;

    friend void swap(Array& first, Array& second) noexcept;

private:
    void CheckCapacity(std::size_t size); 
    void Swap(Array& other) noexcept;
    std::size_t capacity_ = 0;
    std::size_t size_ = 0;
    Geometry::Figure** data_ = nullptr;

};
}