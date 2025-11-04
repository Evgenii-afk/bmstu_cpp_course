#include <ostream>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <type_traits>

namespace bmstu {

template <typename T>
class raw_memory {
public:
    raw_memory() = default;
    explicit raw_memory(size_t size) {
        if (size > 0) {
            ptr_ = static_cast<T*>(operator new(size * sizeof(T)));
        }
    }
    
    ~raw_memory() {
        operator delete(ptr_);
    }

    raw_memory(const raw_memory&) = delete;
    raw_memory& operator=(const raw_memory&) = delete;
    
    raw_memory(raw_memory&& other) noexcept : ptr_(other.ptr_) {
        other.ptr_ = nullptr;
    }
    
    raw_memory& operator=(raw_memory&& other) noexcept {
        if (this != &other) {
            operator delete(ptr_);
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }
        return *this;
    }

    T* operator+(size_t offset) noexcept { return ptr_ + offset; }
    const T* operator+(size_t offset) const noexcept { return ptr_ + offset; }

    T& operator[](size_t index) noexcept { return ptr_[index]; }
    const T& operator[](size_t index) const noexcept { return ptr_[index]; }

    T* get() noexcept { return ptr_; }
    const T* get() const noexcept { return ptr_; }

    void swap(raw_memory& other) noexcept {
        std::swap(ptr_, other.ptr_);
    }

private:
    T* ptr_ = nullptr;
};

template <typename T>
class simple_vector {
public:
    class iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator() = default;
        explicit iterator(pointer ptr) : ptr_(ptr) {}

        reference operator*() const { return *ptr_; }
        pointer operator->() const { return ptr_; }

        iterator& operator++() {
            ++ptr_;
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++ptr_;
            return tmp;
        }

        iterator& operator--() {
            --ptr_;
            return *this;
        }

        iterator operator--(int) {
            iterator tmp = *this;
            --ptr_;
            return tmp;
        }

        iterator operator+(difference_type n) const {
            return iterator(ptr_ + n);
        }

        iterator operator-(difference_type n) const {
            return iterator(ptr_ - n);
        }

        difference_type operator-(const iterator& other) const {
            return ptr_ - other.ptr_;
        }

        iterator& operator+=(difference_type n) {
            ptr_ += n;
            return *this;
        }

        iterator& operator-=(difference_type n) {
            ptr_ -= n;
            return *this;
        }

        reference operator[](difference_type n) const {
            return ptr_[n];
        }

        bool operator==(const iterator& other) const {
            return ptr_ == other.ptr_;
        }

        bool operator!=(const iterator& other) const {
            return ptr_ != other.ptr_;
        }

        bool operator==(std::nullptr_t) const {
            return ptr_ == nullptr;
        }

        bool operator!=(std::nullptr_t) const {
            return ptr_ != nullptr;
        }

        iterator& operator=(std::nullptr_t) {
            ptr_ = nullptr;
            return *this;
        }

        bool operator<(const iterator& other) const {
            return ptr_ < other.ptr_;
        }

        bool operator>(const iterator& other) const {
            return ptr_ > other.ptr_;
        }

        bool operator<=(const iterator& other) const {
            return ptr_ <= other.ptr_;
        }

        bool operator>=(const iterator& other) const {
            return ptr_ >= other.ptr_;
        }

        pointer ptr() const { return ptr_; }

    private:
        pointer ptr_ = nullptr;
    };

    class const_iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = const T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        const_iterator() = default;
        explicit const_iterator(pointer ptr) : ptr_(ptr) {}
        const_iterator(const iterator& other) : ptr_(other.ptr()) {}

        reference operator*() const { return *ptr_; }
        pointer operator->() const { return ptr_; }

        const_iterator& operator++() {
            ++ptr_;
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator tmp = *this;
            ++ptr_;
            return tmp;
        }

        const_iterator& operator--() {
            --ptr_;
            return *this;
        }

        const_iterator operator--(int) {
            const_iterator tmp = *this;
            --ptr_;
            return tmp;
        }

        const_iterator operator+(difference_type n) const {
            return const_iterator(ptr_ + n);
        }

        const_iterator operator-(difference_type n) const {
            return const_iterator(ptr_ - n);
        }

        difference_type operator-(const const_iterator& other) const {
            return ptr_ - other.ptr_;
        }

        const_iterator& operator+=(difference_type n) {
            ptr_ += n;
            return *this;
        }

        const_iterator& operator-=(difference_type n) {
            ptr_ -= n;
            return *this;
        }

        reference operator[](difference_type n) const {
            return ptr_[n];
        }

        bool operator==(const const_iterator& other) const {
            return ptr_ == other.ptr_;
        }

        bool operator!=(const const_iterator& other) const {
            return ptr_ != other.ptr_;
        }

        bool operator==(std::nullptr_t) const {
            return ptr_ == nullptr;
        }

        bool operator!=(std::nullptr_t) const {
            return ptr_ != nullptr;
        }

        const_iterator& operator=(std::nullptr_t) {
            ptr_ = nullptr;
            return *this;
        }

        bool operator<(const const_iterator& other) const {
            return ptr_ < other.ptr_;
        }

        bool operator>(const const_iterator& other) const {
            return ptr_ > other.ptr_;
        }

        bool operator<=(const const_iterator& other) const {
            return ptr_ <= other.ptr_;
        }

        bool operator>=(const const_iterator& other) const {
            return ptr_ >= other.ptr_;
        }

    private:
        pointer ptr_ = nullptr;
    };

    simple_vector() noexcept = default;

    explicit simple_vector(size_t size)
        : data_(size), size_(size), capacity_(size) {
        for (size_t i = 0; i < size_; ++i) {
            new (data_.get() + i) T();
        }
    }

    simple_vector(size_t size, const T& value)
        : data_(size), size_(size), capacity_(size) {
        for (size_t i = 0; i < size_; ++i) {
            new (data_.get() + i) T(value);
        }
    }

    simple_vector(std::initializer_list<T> init)
        : data_(init.size()), size_(init.size()), capacity_(init.size()) {
        size_t i = 0;
        for (const T& item : init) {
            new (data_.get() + i) T(item);
            ++i;
        }
    }

    simple_vector(const simple_vector& other)
        : data_(other.size_), size_(other.size_), capacity_(other.size_) {
        for (size_t i = 0; i < size_; ++i) {
            new (data_.get() + i) T(other.data_[i]);
        }
    }

    simple_vector(simple_vector&& other) noexcept 
        : data_(std::move(other.data_)), size_(other.size_), capacity_(other.capacity_) {
        other.size_ = 0;
        other.capacity_ = 0;
    }

    ~simple_vector() {
        clear();
    }

    simple_vector& operator=(const simple_vector& rhs) {
        if (this != &rhs) {
            simple_vector tmp(rhs);
            swap(tmp);
        }
        return *this;
    }

    simple_vector& operator=(simple_vector&& rhs) noexcept {
        if (this != &rhs) {
            clear();
            data_ = std::move(rhs.data_);
            size_ = rhs.size_;
            capacity_ = rhs.capacity_;
            rhs.size_ = 0;
            rhs.capacity_ = 0;
        }
        return *this;
    }

    iterator begin() noexcept { return iterator(data_.get()); }
    iterator end() noexcept { return iterator(data_.get() + size_); }
    const_iterator begin() const noexcept { return const_iterator(data_.get()); }
    const_iterator end() const noexcept { return const_iterator(data_.get() + size_); }
    const_iterator cbegin() const noexcept { return const_iterator(data_.get()); }
    const_iterator cend() const noexcept { return const_iterator(data_.get() + size_); }

    void reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            raw_memory<T> new_data(new_capacity);
            for (size_t i = 0; i < size_; ++i) {
                new (new_data.get() + i) T(std::move(data_[i]));
                data_[i].~T();
            }
            data_ = std::move(new_data);
            capacity_ = new_capacity;
        }
    }

    void resize(size_t new_size) {
        if (new_size > capacity_) {
            reserve(new_size);
        }
        if (new_size > size_) {
            for (size_t i = size_; i < new_size; ++i) {
                new (data_.get() + i) T();
            }
        } else {
            for (size_t i = new_size; i < size_; ++i) {
                data_[i].~T();
            }
        }
        size_ = new_size;
    }

    void push_back(const T& value) {
        if (size_ >= capacity_) {
            size_t new_capacity = capacity_ ? capacity_ * 2 : 1;
            reserve(new_capacity);
        }
        new (data_.get() + size_) T(value);
        ++size_;
    }

    void push_back(T&& value) {
        if (size_ >= capacity_) {
            size_t new_capacity = capacity_ ? capacity_ * 2 : 1;
            reserve(new_capacity);
        }
        new (data_.get() + size_) T(std::move(value));
        ++size_;
    }

    void pop_back() {
        if (size_ > 0) {
            data_[size_ - 1].~T();
            --size_;
        }
    }

    iterator insert(const_iterator pos, const T& value) {
        return insert_impl(pos, value);
    }

    iterator insert(const_iterator pos, T&& value) {
        return insert_impl(pos, std::move(value));
    }

    iterator erase(const_iterator pos) {
        size_t offset = pos - cbegin();
        for (size_t i = offset; i < size_ - 1; ++i) {
            data_[i] = std::move(data_[i + 1]);
        }
        data_[size_ - 1].~T();
        --size_;
        return iterator(data_.get() + offset);
    }

    void clear() noexcept {
        for (size_t i = 0; i < size_; ++i) {
            data_[i].~T();
        }
        size_ = 0;
    }

    T& operator[](size_t index) noexcept { return data_[index]; }
    const T& operator[](size_t index) const noexcept { return data_[index]; }

    T& at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    const T& at(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    size_t size() const noexcept { return size_; }
    size_t capacity() const noexcept { return capacity_; }
    bool empty() const noexcept { return size_ == 0; }

    void swap(simple_vector& other) noexcept {
        data_.swap(other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    friend bool operator==(const simple_vector& lhs, const simple_vector& rhs) {
        if (lhs.size_ != rhs.size_) {
            return false;
        }
        for (size_t i = 0; i < lhs.size_; ++i) {
            if (lhs.data_[i] != rhs.data_[i]) {
                return false;
            }
        }
        return true;
    }

    friend bool operator!=(const simple_vector& lhs, const simple_vector& rhs) {
        return !(lhs == rhs);
    }

    friend bool operator<(const simple_vector& lhs, const simple_vector& rhs) {
        return std::lexicographical_compare(
            lhs.begin(), lhs.end(),
            rhs.begin(), rhs.end());
    }

    friend bool operator>(const simple_vector& lhs, const simple_vector& rhs) {
        return rhs < lhs;
    }

    friend bool operator<=(const simple_vector& lhs, const simple_vector& rhs) {
        return !(rhs < lhs);
    }

    friend bool operator>=(const simple_vector& lhs, const simple_vector& rhs) {
        return !(lhs < rhs);
    }

private:
    template <typename U>
    iterator insert_impl(const_iterator pos, U&& value) {
        size_t offset = pos - cbegin();
        if (size_ >= capacity_) {
            size_t new_capacity = capacity_ ? capacity_ * 2 : 1;
            reserve(new_capacity);
        }
        if (offset < size_) {
            new (data_.get() + size_) T(std::move(data_[size_ - 1]));
            for (size_t i = size_ - 1; i > offset; --i) {
                data_[i] = std::move(data_[i - 1]);
            }
            data_[offset].~T();
        }
        new (data_.get() + offset) T(std::forward<U>(value));
        ++size_;
        return iterator(data_.get() + offset);
    }

    raw_memory<T> data_;
    size_t size_ = 0;
    size_t capacity_ = 0;
};

} // namespace bmstu