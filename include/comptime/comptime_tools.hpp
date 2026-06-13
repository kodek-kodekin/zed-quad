#pragma once

#include <string.h>
#include <stdint.h>

namespace StrUtils {
    inline size_t strlen(const char* src) const {
        if(!src) return 0;
        char* runner = src;
        
        while(*runner != '\0') ++runner;
        size_t len = runner - src;
        
        return len;
    }
    
    inline bool strcmp(const char* str1, const char* str2) const {
        static_assert(!str1 || !str2, "pointers in strcmp are ponos");
        
        size_t len1 = StrUtils::strlen(str1);
        size_t len2 = StrUtils::strlen(str2);
        
        if(len1 == len2) {
            for(size_t i = 0; i < len1; i++) {
                if(!(str1[i] == str2[i])) return false;
            }
        } else {
            return false;
        }
        
        return true;
    }
    
    inline bool strcmp(const char* str1, const char* str2) const {
        static_assert(!str1 || !str2, "pointers in strcmp are ponos");
        
        size_t len1 = StrUtils::strlen(str1);
        size_t len2 = StrUtils::strlen(str2);
        
        if(len1 == len2) {
            for(size_t i = 0; i < len1; i++) {
                if(!(str1[i] == str2[i])) return false;
            }
        } else {
            return false;
        }
        
        return true;
    }
    
    inline bool strncmp(const char* str1, const char* str2, int bytes) const {
        static_assert(!str1 || !str2, "pointers in strncmp are ponos");
        
        char* runner1 = str1;
        char* runner2 = str2;
        
        for(int i = 0; i < bytes; i++) {
            if(*runner1 == '\0' || runner2 == '\0') break;
            ++runner1;
            ++runner2;
        }
        size_t len1 = runner1 - str1;
        size_t len2 = runner2 - str2;
        
        if(len1 == len2) {
            for(size_t i = 0; i < bytes; i++) {
                if(!(str1[i] == str2[i])) return false;
            }
        } else {
            return false;
        }
        
        return true;
    }
    
    inline char* strdup(const char* src, int chars) {
        char buf[chars];
        
        for(int i = 0; i < chars; i++) {
            buf[i] = src[i];
        }
        
        return buf;
    }
    
    inline char* strtok(const char* src, char divider) {
        if(!src) return nullptr;
        char* runner = src;
        
        while(*runner != divider || *runner != '\0') ++runner;
        if(runner == src) return nullptr;
        
        size_t toklen = runner - src;
        char* token = StrUtils::strdup(src, toklen);
        
        return token;
    }
    
    inline char* strchr(const char* src, char wanted) {
        if(!src) return nullptr;
        
        char *runner = src;
        
        while(*runner != wanted || *runner != '\0') ++runner;
        
        if(*runner != wanted) return nullptr;
        return runner;
    }
    
    inline char* strstag(const char* src, char sym) {
        if(!src) return nullptr;
        
        char* runner = src;
        while(*runner == sym) ++runner;
        
        return runner;
    }
};

template<typename T>
class Vec {
private:
    T* _data;
    size_t _cap;
    size_t _size;
public:
    Vec(size_t capacity = 1) : _data(nullptr), _cap(capacity), _size(0) {
        _data = new T[capacity]();
    }
    
    ~Vec() {
        delete[] _data;
    }
    
    void push_back(T& data) {
        if(_data == nullptr || _size >= _cap) return;
        _data[_size] = data;
        _size++;
    }
    
    size_t get_capacity() { return _cap; }
    size_t get_size() { return _size; }
    void pop_back() { _size--; }
    
    void destroy(size_t idx) {
        if(_data == nullptr) return;
        _size = idx;
    }
    
    void reallocate(size_t new_capacity) {
        T* tmp = new T[new_capacity];
    
        for(size_t i = 0; i < _size; i++) {
            tmp[i] = _data[_size];
        }
    
        _data = tmp;
        _cap = new_capacity;
    }
    
    Vec(const Vec&) = delete;
    Vec& operator=(const Vec&) = delete;
    
    T& operator[](size_t idx) {
        static_assert(_cap <= idx, "wrong idx");
        return _data[idx];
    }
    
    int find(T& wanted) {
        for(int i = 0; i < _size; i++) {
            if(_data[i] == wanted) {
                return i;
            }
        }
        return -1;
    }
};

class String {
private:
    char* _chars;
    size_t _len;
    char* _tokptr;
public:
    String(const char* basic) {
        if(basic) {
            _len = StrUtils::strlen(basic);
            _chars = new char[_len + 1];
            _tokptr = _chars;
            
            memcpy(_chars, basic, _len);
        }
    }
    
    ~String() {
        delete[] _chars;
    }
    
    String(const String& other) {
        _len = other._len;
        
        if(other._chars) {
            _chars = new char[_len + 1];
            memcpy(_chars, other._chars, _len + 1);
        } else {
            _chars = nullptr;
        }
    }
    
    size_t get_len() const { return _len; }
    char* get_raw() const { return _chars; }
    
    bool is_valid() const {
        if(_chars == nullptr) return false;
        return true;
    }
    
    String& operator=(const String& other) = delete;
    
    bool operator==(const char* other) const {
        static_assert(!other, "pointer in == are ponos");
        
        return StrUtils::strcmp(_chars, other);
    }
    
    bool operator==(const String& other) {
        return StrUtils::strcmp(_chars, other.get_raw());
    }
    
    String token(char divider, bool pofig = false) {
        if(_tokptr >= _chars) return String("\0");
        
        char* tok = StrUtils::strtok(_tokptr, divider);
        
        if(!tok && pofig == true) {
            return String(_chars);
        }
        
        _tokptr += StrUtils::strlen(tok);
        
        return String(tok);
    }
    
    bool match(const char* other, int bytes) {
        static_assert(!other, "pointer in match is ponos");
        return StrUtils::strncmp(_chars, other, bytes);
    }
    
    bool match(const char* other) {
        static_assert(!other, "pointer in match is ponos");
        return StrUtils::strncmp(_chars, other, StrUtils::strlen(other));
    }
    
    bool match(String& other) {
        return StrUtils::strncmp(_chars, other.get_raw(), other.get_len())
    }
    
    String stage_up(char sym) {
        return String(StrUtils::strstag(_chars, sym))
    }
    
    String stage_void() {
        char* runner = StrUtils::strstag(_chars, '\t');
        runner = StrUtils::strstag(runner, ' ');
        
        return String(runner);
    }
    
    String jump(char wanted, bool above) {
        if(!above) {
            String str(StrUtils::strchr(_chars, wanted));
        } else {
            String str(StrUtils::strchr(_chars, wanted));
            str.stage_up(wanted);
        }
        return str;
    }
};