#pragma once

#include <stdint.h>
#include <stdio.h>
#include <string.h>


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

    Vector(const Vector& other)
        : Vector(other.max_size_) {

        this->assign(other.size(), other);
    }


    // GETTERS FUNCTIONS ------------------------------------------------------------------------------------

    const T& operator[](size_t index) const { return values_[index]; }

    T& operator[](size_t index) { return values_[index]; }

    const T& at(size_t index) const { return values_[index]; }

    T& at(size_t index) { return values_[index]; }

    T& front() { return values_[0]; }

    T& back() { return values_[size_ - 1]; }




    // FILL FUNCTIONS ----------------------------------------------------------------------------------------

    template <typename U> void fill(const U& value) { assign(max_size_, value); }

    template <typename U, size_t N> void fill(const U (&values)[N]) { assign(N, values); }

    template <typename U> void fill(const Vector<U>& values) { assign(values.size(), values); }




    // ASSIGN FUNCTIONS -------------------------------------------------------------------------------------

    Vector<T>& operator=(const Vector<T>& neww) {
        if (this == &neww)
            return *this;

        this->clear();
        this->assign(neww.size(), neww);

        return *this;
    }

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




    // FILL FUNCTIONS ----------------------------------------------------------------------------------------

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

    bool pop_back(T& out) {
        if (size_ > 0) {
            out = back();
            --size_;
            return true;
        }
        return false;
    }


    void push_front(const T& value) {
        if ((values_ != NULL) && (size_ < max_size_)) {
            for (size_t i = size_; i > 0; --i)
                values_[i] = values_[i - 1];
            values_[0] = value;
            ++size_;
        }
    }

    void pop_front() {
        if (size_ > 0) {
            for (size_t i = 0; i < size_ - 1; ++i)
                values_[i] = values_[i + 1];
            --size_;
        }
    }

    bool pop_front(T& out) {
        if (size_ > 0) {
            out = values_[0];
            pop_front();
            return true;
        }
        return false;
    }

    // CLEARING FUNCTIONS ---------------------------------------------------------------------------------------

    void clear() { size_ = 0; }

    void remove(size_t index) {
        if (size_ > index) {
            for (size_t i = index; i < (size_ - 1); ++i) {
                values_[i] = values_[i + 1];
            }
            --size_;
        }
    }

    bool removeValue(const T& data) {
        for (size_t i = 0; i < size_; ++i) {
            if (values_[i] == data) {
                remove(i);
                return true;
            }
        }
        return false;
    }




    // SIZE FUNCTIONS ---------------------------------------------------------------------------------------

    size_t size() const { return size_; }

    size_t max_size() const { return max_size_; }




    // CHECK FUNCTIONS --------------------------------------------------------------------------------------

    bool empty() const { return size_ == 0; }

    bool full() const { return size_ == max_size_; }



    // ACCESS TO BUFFER -------------------------------------------------------------------------------------

    T* data() { return values_; }

    const T* data() const { return values_; }

private:
    T* values_;
    size_t max_size_;
    size_t size_;
};
