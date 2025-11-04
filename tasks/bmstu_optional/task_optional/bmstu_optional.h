#pragma once
#include <cstdint>
#include <cstring>
#include <iterator>
#include <ostream>
#include <exception>
#include <utility>

namespace bmstu
{
    struct nullptr_t
    {
        explicit constexpr nullptr_t(int) noexcept {}
    };

    class bad_optional_access : public std::exception {
    public:
        const char* what() const noexcept override { return "Bad optional access"; }
    };

    template <typename T>
    class optional
    {
    public:
        optional() = default;
        
        optional(const T& value)
        {
            is_initialized_ = true;
            new (&data_[0]) T(value);
        }

        optional(T&& value)
        {
            is_initialized_ = true;
            new (&data_[0]) T(std::move(value));
        }
        
        optional(optional&& other) : is_initialized_(other.is_initialized_)
        {
            if (other.is_initialized_) {
                new (&data_[0]) T(std::move(other.value()));
            }
        }

        optional(const optional& other) : is_initialized_(other.is_initialized_)
        {
            if (other.is_initialized_) {
                new (&data_[0]) T(other.value());
            }
        }

        optional& operator=(const optional& other) {
            if (this != &other) {
                if (other.is_initialized_) {
                    if (is_initialized_) {
                        value() = other.value();
                    } else {
                        new (&data_[0]) T(other.value());
                        is_initialized_ = true;
                    }
                } else {
                    reset();
                }
            }
            return *this;
        }

        optional& operator=(optional&& other) {
            if (this != &other) {
                if (other.is_initialized_) {
                    if (is_initialized_) {
                        value() = std::move(other.value());
                    } else {
                        new (&data_[0]) T(std::move(other.value()));
                        is_initialized_ = true;
                    }
                } else {
                    reset();
                }
            }
            return *this;
        }

        bool has_value() const { return is_initialized_; }

        void reset()
        {
            if (is_initialized_)
            {
                value().~T();
                is_initialized_ = false;
            }
        }
        
        T& value()
        {
            if (!is_initialized_)
            {
                throw bad_optional_access();
            }
            return *reinterpret_cast<T*>(&data_[0]);
        }

        const T& value() const
        {
            if (!is_initialized_)
            {
                throw bad_optional_access();
            }
            return *reinterpret_cast<const T*>(&data_[0]);
        }

        ~optional() { reset(); }

        // Operators
        T& operator*() & { 
            return value();
        }

        const T& operator*() const& {
            return value();
        }

        T&& operator*() && {
            return std::move(value());
        }

        T* operator->() {
            return &value();
        }

        const T* operator->() const {
            return &value();
        }

        template <typename... Args>
        void emplace(Args&&... args)
        {
            reset();
            new(&data_[0]) T(std::forward<Args>(args)...);
            is_initialized_ = true;
        }

        // Utility functions
        explicit operator bool() const noexcept {
            return is_initialized_;
        }

        T value_or(const T& default_value) const {
            return is_initialized_ ? value() : default_value;
        }

        T value_or(T&& default_value) const {
            return is_initialized_ ? value() : std::move(default_value);
        }

    private:
        alignas(T) uint8_t data_[sizeof(T)];
        bool is_initialized_ = false;
    };
} // namespace bmstu