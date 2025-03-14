#pragma once

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus

template <typename T> class VectorIterator {
public:
    VectorIterator(T* values_ptr)
        : values_ptr_ { values_ptr }
        , position_ { 0 } { }

    VectorIterator(T* values_ptr, size_t size)
        : values_ptr_ { values_ptr }
        , position_ { size } { }

    bool operator!=(const VectorIterator<T>& other) const { return !(*this == other); }

    bool operator==(const VectorIterator<T>& other) const { return position_ == other.position_; }

    VectorIterator& operator++() {
        ++position_;
        return *this;
    }

    T& operator*() const { return *(values_ptr_ + position_); }

private:
    T* values_ptr_;
    size_t position_;
};

template <typename T> class Vector {
public:
    ~Vector() {
        delete[] values_;
        values_ = nullptr;
        max_size_ = 0;
        size_ = 0;
    }

    Vector(size_t max_size)
        : max_size_(max_size)
        , size_(0) {
        values_ = new T[max_size];
    }

    Vector(size_t max_size, const T* value)
        : Vector(max_size) {
        assign(max_size, value);
    }

    const T& operator[](size_t index) const { return values_[index]; }

    T& operator[](size_t index) { return values_[index]; }

    Vector<T>& operator=(const Vector<T>& neww){
        if(this == &neww)
            return *this;

        this->clear();
        this->assign(neww.size(), neww);

        return *this;
    }

    const T& at(size_t index) const { return values_[index]; }

    T& at(size_t index) { return values_[index]; }

    T& front() { return values_[0]; }

    T& back() { return values_[size_ - 1]; }

    void clear() { size_ = 0; }

    template <typename U> void fill(const U& value) { assign(max_size_, value); }

    template <typename U, size_t N> void fill(const U (&values)[N]) { assign(N, values); }

    template <typename U> void fill(const Vector<U>& values) { assign(values.size(), values); }

    template <typename U> void assign(size_t n, const U& value) {
        size_t assign_size = ((n < max_size_) ? n : max_size_);
        size_ = assign_size;
        for (size_t i = 0; i < assign_size; ++i) {
            values_[i] = value;
        }
    }

    void assign(size_t n, const T* value) {
        size_t assign_size = ((n < max_size_) ? n : max_size_);
        size_ = assign_size;
        for (size_t i = 0; i < assign_size; ++i) {
            values_[i] = *value;
        }
    }

    template <typename U, size_t N> void assign(size_t n, const U (&values)[N]) {
        size_t n_smallest = ((n < N) ? n : N);
        size_t assign_size = ((n_smallest < max_size_) ? n_smallest : max_size_);
        size_ = assign_size;
        for (size_t i = 0; i < assign_size; ++i) {
            values_[i] = values[i];
        }
    }

    template <typename U> void assign(size_t n, const Vector<U>& values) {
        size_t n_smallest = ((n < values.size()) ? n : values.size());
        size_t assign_size = ((n_smallest < max_size_) ? n_smallest : max_size_);
        size_ = assign_size;
        for (size_t i = 0; i < assign_size; ++i) {
            values_[i] = values[i];
        }
    }

    void push_back(const T& value) {
        if ((values_ != NULL) && (size_ < max_size_)) {
            values_[size_++] = value;
        }
    }

    void pop_back() {
        if (size_ > 0) {
            --size_;
        }
    }

    void remove(size_t index) {
        if (size_ > index) {
            for (size_t i = index; i < (size_ - 1); ++i) {
                values_[i] = values_[i + 1];
            }
            --size_;
        }
    }

    size_t size() const { return size_; }

    size_t max_size() const { return max_size_; }

    bool empty() const { return size_ == 0; }

    bool full() const { return size_ == max_size_; }

    T* data() { return values_; }

    const T* data() const { return values_; }

    typedef VectorIterator<T> iterator;
    iterator begin() { return iterator(values_); }

    iterator end() { return iterator(values_, size_); }

    typedef VectorIterator<const T> const_iterator;
    const_iterator begin() const { return const_iterator(values_); }

    const_iterator end() const { return const_iterator(values_, size_); }

private:
    T* values_;
    size_t max_size_;
    size_t size_;
};

#endif