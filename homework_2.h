#include <iostream>
#include <cstring>
#include <utility>

namespace bmstu {

class string {
public:
    // Конструктор по умолчанию
    string() : size_(0), capacity_(16) {
        data_ = new char[capacity_];
        data_[0] = '\0'; // Пустая строка
    }

    // Конструктор от C-строки
    string(const char* str) {
        size_ = strlen(str);
        capacity_ = size_ + 1; // +1 для нуль-терминатора
        data_ = new char[capacity_];
        strcpy(data_, str);
    }

    // Копирующий конструктор
    string(const string& other) : size_(other.size_), capacity_(other.capacity_) {
        data_ = new char[capacity_];
        strcpy(data_, other.data_);
    }

    // Перемещающий конструктор
    string(string&& other) noexcept
        : size_(other.size_), capacity_(other.capacity_), data_(other.data_) {
        other.size_ = 0;
        other.capacity_ = 0;
        other.data_ = nullptr;
    }

    // Деструктор
    ~string() {
        delete[] data_;
    }

    // Оператор копирующего присваивания
    string& operator=(const string& other) {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = new char[capacity_];
            strcpy(data_, other.data_);
        }
        return *this;
    }

    // Оператор перемещающего присваивания
    string& operator=(string&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = other.data_;
            other.size_ = 0;
            other.capacity_ = 0;
            other.data_ = nullptr;
        }
        return *this;
    }

    // Оператор сложения
    friend string operator+(const string& left, const string& right) {
        string result;
        result.size_ = left.size_ + right.size_;
        result.capacity_ = result.size_ + 1;
        result.data_ = new char[result.capacity_];
        strcpy(result.data_, left.data_);
        strcat(result.data_, right.data_);
        return result;
    }

    // Оператор вывода
    friend std::ostream& operator<<(std::ostream& os, const string& obj) {
        os << obj.data_;
        return os;
    }

    // Оператор ввода
    friend std::istream& operator>>(std::istream& is, string& obj) {
        char buffer[1024]; // Предположим, что максимальная длина строки 1023 символа
        is >> buffer;
        obj = buffer;
        return is;
    }

    // Оператор += для другой строки
    string& operator+=(const string& other) {
        *this = *this + other;
        return *this;
    }

    // Оператор += для символа
    string& operator+=(char symbol) {
        string temp;
        temp.size_ = size_ + 1;
        temp.capacity_ = temp.size_ + 1;
        temp.data_ = new char[temp.capacity_];
        strcpy(temp.data_, data_);
        temp.data_[size_] = symbol;
        temp.data_[temp.size_] = '\0'; // Нуль-терминатор

        *this = std::move(temp);
        return *this;
    }

    // Оператор доступа по индексу
    char& operator[](size_t index) {
        return data_[index];
    }

    const char& operator[](size_t index) const {
        return data_[index];
    }

    // Метод для получения размера строки
    size_t size() const {
        return size_;
    }

    // Метод для получения C-строки
    const char* c_str() const {
        return data_;
    }

private:
    char* data_;
    size_t size_;
    size_t capacity_;
};

}
