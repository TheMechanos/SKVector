#pragma once

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus

namespace SK {

template <typename T> class RingBuffer {
public:
    ~RingBuffer() {
        delete[] values_;
        values_ = nullptr;
    }

    RingBuffer(size_t max_size)
        : values_(0)
        , max_size_(max_size)
        , size_(0)
        , head_(0)
        , tail_(0) {
        values_ = new T[max_size_];
    }

    // --- COPY / ASSIGN ---
    RingBuffer(const RingBuffer& other)
        : values_(0)
        , max_size_(other.max_size_)
        , size_(other.size_)
        , head_(other.head_)
        , tail_(other.tail_) {
        values_ = new T[max_size_];
        for (size_t i = 0; i < size_; ++i) {
            values_[(head_ + i) % max_size_] = other.values_[(other.head_ + i) % max_size_];
        }
    }

    RingBuffer<T>& operator=(const RingBuffer<T>& neww) {
        if (this == &neww)
            return *this;

        clear();

        for (size_t i = 0; i < neww.size_; ++i) {
            size_t src_index = (neww.head_ + i) % neww.max_size_;
            push_back(neww.values_[src_index]);
        }

        return *this;
    }

    // --- GETTERS ---
    size_t size() const { return size_; }
    size_t max_size() const { return max_size_; }
    bool empty() const { return size_ == 0; }
    bool full() const { return size_ == max_size_; }

    T& front() { return values_[head_]; }
    T& back() { return values_[(tail_ + max_size_ - 1) % max_size_]; }

    // --- OPERATOR[] ---
    T& operator[](size_t index) { return values_[(head_ + index) % max_size_]; }
    const T& operator[](size_t index) const { return values_[(head_ + index) % max_size_]; }

    // --- PUSH / POP ---
    bool push_back(const T& value) {
        if (full())
            return false;
        values_[tail_] = value;
        tail_ = (tail_ + 1) % max_size_;
        ++size_;
        return true;
    }

    bool push_front(const T& value) {
        if (full())
            return false;
        head_ = (head_ + max_size_ - 1) % max_size_;
        values_[head_] = value;
        ++size_;
        return true;
    }

    bool pop_back(T& out) {
        if (empty())
            return false;
        tail_ = (tail_ + max_size_ - 1) % max_size_;
        out = values_[tail_];
        --size_;
        return true;
    }

    bool pop_front(T& out) {
        if (empty())
            return false;
        out = values_[head_];
        head_ = (head_ + 1) % max_size_;
        --size_;
        return true;
    }

    void clear() {
        size_ = 0;
        head_ = 0;
        tail_ = 0;
    }

    void remove(size_t index) {
        if (index >= size_)
            return;

        size_t phys_index = (head_ + index) % max_size_;

        size_t i = phys_index;
        while (i != (tail_ + max_size_ - 1) % max_size_) {
            size_t next = (i + 1) % max_size_;
            values_[i] = values_[next];
            i = next;
        }

        tail_ = (tail_ + max_size_ - 1) % max_size_;
        --size_;
    }

    bool removeValue(const T& data) {
        for (size_t i = 0; i < size_; ++i) {
            size_t phys_index = (head_ + i) % max_size_;
            if (values_[phys_index] == data) {
                remove(i);
                return true;
            }
        }
        return false;
    }

    // --- DATA ACCESS ---
    T* data() { return values_; }
    const T* data() const { return values_; }


private:
    T* values_;
    size_t max_size_;
    size_t size_;
    size_t head_;
    size_t tail_;
};


}
#endif
