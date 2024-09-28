#ifndef FIVE_H
#define FIVE_H
#include<string>
#include<initializer_list>
#include<algorithm>
#include<stdexcept>
#include<exception>
#include<iostream>

class Five{
    public:
        Five();
        Five(const size_t& n, unsigned char t = 0);
        Five(const std::initializer_list< unsigned char > &t);
        Five(const std::string& s);

        Five(const Five& other);
        Five(Five&& other) noexcept;
        virtual ~Five() noexcept;

        size_t get_size() const;
        unsigned char* get_data() const;

        Five& operator=(const Five& other);
        Five& operator+=(const Five& other);
        Five& operator-=(const Five& other);

        bool operator==(const Five& other) const;
        bool operator<(const Five& other) const;
        bool operator>(const Five& other) const;
        bool operator!=(const Five& other) const;


    private:
        unsigned char* data;
        size_t size;
        void normalize();
};

std::ostream& operator<<(std::ostream& os, const Five& num);

#endif