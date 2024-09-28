#include "../include/Five.h"


void validate_num(const unsigned char c){
    if(c < '0' || c > '4') throw std::invalid_argument("Digits must be between 0 and 4");
};

unsigned char* allocate_memory(size_t size){
    unsigned char* p = new(std::nothrow) unsigned char[size]{0};
    if(!p) throw std::bad_alloc();

    return p;
};

void Five::normalize() {
    size_t i = 0;
    while (i < size && data[i] == '0') ++i;
    if (i == size) {
        size = 1;
        data[0] = '0';
    } else {
        size -= i;
        unsigned char* new_data = new unsigned char[size];
        std::copy(data + i, data + i + size, new_data);
        delete[] data;
        data = new_data;
    }
};

Five::Five() : size{1}, data{nullptr} {
    data = allocate_memory(size);
    data[0] = '0';
};

Five::Five(const size_t& n, unsigned char t) : size{n}, data{nullptr} {
    if (n == 0) throw std::invalid_argument("Size cannot be a zero");
    validate_num(t);
    data = allocate_memory(size);
    std::fill(data, data + size, t);
};

Five::Five(const std::initializer_list< unsigned char > &t) : size{t.size()}, data{nullptr} { 
    if(t.size() == 0) throw std::invalid_argument("Initializer list cannot be empty");
    for(auto c : t){
        validate_num(c);
    }
    data = allocate_memory(size);
    std::copy(t.begin(), t.end(), data);
};

Five::Five(const std::string &s) : size{s.size()}, data{nullptr} {
    if(s.size() == 0) throw std::invalid_argument("String cannot be empty");
    for(unsigned char c : s){
        validate_num(c);
    }
    data = allocate_memory(size);
    std::copy(s.begin(), s.end(), data);
};

Five::Five(const Five& other) : size{other.get_size()}, data{nullptr} {
    if(size == 0) throw std::invalid_argument("Size cannot be a zero");
    data = allocate_memory(size);
    std::copy(other.get_data(), other.get_data() + size, data);
}

Five::Five(Five&& other) noexcept : size{other.get_size()}, data{other.get_data()} {
    other.size = 0;
    other.data = nullptr;
}

Five::~Five() noexcept {
    delete[] data;
    data = nullptr;
    size = 0;
}

size_t Five::get_size() const {
    return size;
};

unsigned char* Five::get_data() const {
    return data;
};

Five& Five::operator=(const Five& other) {
    if (this == &other) return *this;

    delete[] data;

    size = other.get_size();
    data = allocate_memory(size);
    std::copy(other.get_data(), other.get_data() + size, data);
    
    return *this;
};

Five& Five::operator+=(const Five& other) {
    size_t max_size = std::max(size, other.get_size()) + 1;
    unsigned char* result = allocate_memory(max_size);

    size_t remains{0};

    for(size_t i{0}; i < max_size; ++i){
        size_t sum = remains;
        if (i < size) sum += data[size - 1 - i] - '0';
        if (i < other.size) sum += other.data[other.size - 1 - i] - '0';

        result[max_size - 1 - i] = (sum % 5) + '0';
        remains = sum / 5;
    }

    delete[] data;

    size = max_size;
    data = result;
    normalize();

    return *this;
};

Five& Five::operator-=(const Five& other) {
    if (*this < other) throw std::invalid_argument("Result of substraction if negative");

    size_t max_size = size;
    unsigned char* result = allocate_memory(max_size);
    int borrow{0};

    for (size_t i = 0; i < max_size; ++i) {
        int diff = borrow;
        if (i < size) diff += data[size - 1 - i] - '0';
        if (i < other.size) diff -= other.data[other.size - 1 - i] - '0';

        if (diff < 0) {
            diff += 5;
            borrow = -1;
        } else {
            borrow = 0;
        }

        result[max_size - 1 - i] = diff + '0';
    }

    delete[] data;

    size = max_size;
    data = result;

    normalize();
    return *this;

};

bool Five::operator==(const Five& other) const {
    if (size != other.get_size()) return false;
    for(size_t i{0}; i < size; ++i){
        if (data[i] != other.get_data()[i]) return false;
    }
    return true;
}

bool Five::operator!=(const Five& other) const {
    return !(*this == other);
}

bool Five::operator<(const Five& other) const {
    if (size < other.get_size()) {
        return true;
    } else  if(size > other.get_size()) { return false; }

    for(size_t i{0}; i < size; ++i){
        if(data[i] < other.get_data()[i]) {
            return true;
        } else if(data[i] > other.get_data()[i]) { return false; }
    }
    return false;
}

bool Five::operator>(const Five& other) const {
    return ((*this != other) && !(*this < other));
}


std::ostream& operator<<(std::ostream& os, const Five& num) {
    for (size_t i = 0; i < num.get_size(); ++i) {
        os << num.get_data()[i];
    }
    return os;
}