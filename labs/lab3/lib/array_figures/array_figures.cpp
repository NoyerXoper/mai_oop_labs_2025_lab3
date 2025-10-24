#include "array_figures.hpp"

#include <cassert>
#include <memory>
#include <stdexcept>

#include "figure.hpp"
#include "array_exception.hpp"

namespace {
constexpr std::size_t DEFAULT_CAPACITY = 10;
}

namespace array {
Array::Array(): capacity_(0), size_(0), data_(nullptr) {}

// For now it stores only Figure*, so no reason for raw memory, in future it will be raw.
Array::Array(std::size_t size): capacity_(size), size_(0), data_(new Geometry::Figure*[size]) {}

Array::Array(const std::initializer_list<Geometry::Figure*>& il): capacity_(il.size()), size_(il.size()), data_(new Geometry::Figure*[capacity_]) {
    int i = 0;
    for (Geometry::Figure* ch: il) {
        data_[i++] = ch;
    }
}

Array::Array(const Array& other): capacity_(other.capacity_), size_(other.size_), data_(new Geometry::Figure*[capacity_]) {
    std::uninitialized_copy(other.data_, other.data_ + other.size_, data_);
}

Array::Array(Array&& other) noexcept: capacity_(other.capacity_), size_(other.size_), data_(other.data_)  {
    other.capacity_ = 0;
    other.size_= 0;
    other.data_ = nullptr;
}

Array::~Array() noexcept {
    delete[] data_;
}

Array& Array::operator=(const Array& other) {
    if (this == &other) {
        return *this;
    }
    Array temp = other;
    Swap(temp);
    return *this;
}

Array& Array::operator=(Array&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    Array temp = std::move(other);
    Swap(temp);
    return *this;
}

std::size_t Array::Size() const noexcept {
    return size_;
}

std::size_t Array::Capacity() const noexcept {
    return capacity_;
}

Geometry::Figure*& Array::operator[](std::size_t i) {
    // operator[] asserts, not throws in g++
    assert(i < size_);
    return data_[i];
}

Geometry::Figure* const& Array::operator[](std::size_t i) const {
    assert(i < size_);
    return data_[i];
}

Geometry::Figure*& Array::At(std::size_t i) {
    if (i >= size_) {
        throw exceptions::ArrayOutOfRange("Array out of range");
    }
    return data_[i];
}

Geometry::Figure* const& Array::At(std::size_t i) const {
    if (i >= size_) {
        throw exceptions::ArrayOutOfRange("Array out of range");
    }
    return data_[i];
}

void Array::PushBack(Geometry::Figure* figure) {
    CheckCapacity(size_ + 1);
    data_[size_] = figure;
    ++size_;
}

void Array::PopBack() {
    if (size_ > 0) {
        --size_;
    }
}

void Array::Pop(std::size_t i) {
    if (i >= size_) {
        throw exceptions::ArrayOutOfRange("Index out of range");
    }
    for (std::size_t j = i; j + 1 < size_; ++j) {
        // for template version there should be std::move
        data_[j] = data_[j + 1];
    }
    --size_;
}


Geometry::Figure*& Array::Front() {
    assert(size_ > 0);
    return data_[0];
};

Geometry::Figure* const& Array::Front() const {
    assert(size_ > 0);
    return data_[0];
}

Geometry::Figure*& Array::Back() {
    assert(size_ > 0);
    return data_[size_ - 1];
}

Geometry::Figure* const& Array::Back() const {
    assert(size_ > 0);
    return data_[size_ - 1];
}

void Array::Reserve(std::size_t size) {
    // if capacity is greater of equal to new capacity, just do nothing
    if (capacity_ >= size) {
        return;
    }

    Geometry::Figure** newdata_ = new Geometry::Figure*[size];
    capacity_ = size;
    if (data_) {
        // The same as uninitialized copy, but in future will be more much better
        std::uninitialized_move(data_, data_ + size_, newdata_);
    }
    delete[] data_;
    data_ = newdata_;
}

bool operator==(const Array& first, const Array& second) noexcept {
    if (first.size_ != second.size_) {
        return false;
    }
    for (int i = 0; i < first.size_; ++i) {
        if (first.data_[i] != second.data_[i]) {
            return false;
        }
    }
    return true;
}

void Array::CheckCapacity(std::size_t size) {
    if (size <= capacity_) {
        return;
    }
    Reserve(std::max(2 * capacity_, static_cast<std::size_t>(DEFAULT_CAPACITY)));
}

// Modern way of swap overloading
void Array::Swap(Array& other) noexcept {
    using std::swap;
    swap(capacity_, other.capacity_);
    swap(size_, other.size_);
    swap(data_, other.data_);
}

void swap(Array& first, Array& second) noexcept {
    first.Swap(second);
}
}
