#pragma once

#include <algorithm>  // std::max
#include <utility>    // std::move
#include <stdexcept>  // std::out_of_range

namespace dsa {

template <typename T>
class Vector {

private:
    int cap{0};       // capacity of the array
    int sz{0};        // number of actual entries
    T* data{nullptr}; // pointer to array of elements

public:
    // empty - O(1)
    Vector() = default;
    
    // capacity - O(1)
    int capacity() const {
        return cap;
    }

    // elements stored
    int size() const {
        return sz;
    }
    
    // return (sz == 0)
    bool empty() const {
        return (sz == 0);
    }
    
    // unchecked access
    const T& operator[](int i) const { 
        return data[i];
    }
    T& operator[](int i) { 
        return data[i];
    }
    
    // checked access
    const T& at(int i) const {
        if (i < 0 || i >= sz) {
            throw std::out_of_range("Invalid Index");
        }
        return data[i];
    }
    T& at(int i) {
        if (i < 0 || i >= sz) {
            throw std::out_of_range("Invalid Index");
        }
        return data[i];
    }
    
    // first element
    const T& front() const { 
        if (sz == 0) {
            throw std::out_of_range("front on empty Vector");
        }
        return data[0];
    }
    T& front() {
        if (sz == 0) {
            throw std::out_of_range("front on empty Vector");
        }
        return data[0];
    }
    
    // last element
    const T& back() const { 
        if (sz == 0) {
            throw std::out_of_range("back on empty Vector");
        }
        return data[sz-1];
    }
    T& back() {
        if (sz == 0) {
            throw std::out_of_range("back on empty Vector");
        }
        return data[sz-1];
    }
    
    // insert at end
    void push_back(const T& elem){
        if (sz == cap) {
            reserve(std::max(1, 2 * cap));
        }
        data[sz] = elem;
        sz++;
    }

    // remove from end
    void pop_back() { 
        if (sz == 0) {
            throw std::out_of_range("pop_back on empty Vector");
        }
        sz--;
        shrink();
    }

    // insert at index
    void insert(int i, const T& elem){
        if (i < 0 || i > sz) {
            throw std::out_of_range("Invalid Index");
        }
        if (sz == cap) {
            reserve(std::max(1, 2 * cap));
        }
        for (int j = sz; j > i; --j) {
            data[j] = data[j - 1];
        }
        data[i] = elem;
        sz++;
    }

    // removes at index
    void erase(int i){
        if (i < 0 || i >= sz) {
            throw std::out_of_range("Invalid Index");
        }
        for (int j = i; j < sz - 1; j++) {
            data[j] = data[j + 1];
        }
        sz--;
        shrink();
    }

    // ensure capacity
    void reserve(int minimum){
        if (cap < minimum) {
            T* new_array = new T[minimum];
            for (int k = 0; k < sz; ++k) {
                new_array[k] = data[k];
            }
            delete[] data;
            data = new_array;
            cap = minimum;
        }
    }

    // nested iterator class
    class iterator {
        friend class Vector;
    private:
        Vector* vec;
        int ind;
    public:
        iterator(Vector* v=nullptr, int i=-1){
            vec=v; ind=i;
        }
        T& operator*() const {
            return vec->data[ind];
        }
        T* operator->() const {
            return &(vec->data[ind]); }
        iterator& operator++(){
            ind++; return *this;
        }
        iterator operator++(int){
            iterator old=*this; ind++; return old;
        }       
        iterator& operator--(){
            ind--; return *this;
        }       
        iterator operator--(int){
            iterator old=*this;
            ind--;
            return old;
        }       
        bool operator==(iterator rhs) const{
            return (vec==rhs.vec && ind==rhs.ind);
        }       
        bool operator!=(iterator rhs) const{
            return !(*this == rhs);
        }       
    };

    class const_iterator {
    private:
        const Vector* vec;
        int ind;
    public:
        const_iterator(const Vector* v=nullptr, int i=-1){
            vec=v; ind=i;
        }       
        const T& operator*() const {
            return vec->data[ind];
        }       
        const T* operator->() const {
            return &(vec->data[ind]);
        }       
        const_iterator& operator++(){
            ind++; return *this;
        }       
        const_iterator operator++(int){
            const_iterator old=*this;
            ind++;
            return old;
        }       
        const_iterator& operator--(){
            ind--;
            return *this;
        }       
        const_iterator operator--(int){
            const_iterator old=*this;
            ind--;
            return old;
        }       
        bool operator==(const_iterator rhs) const{
            return (vec==rhs.vec && ind==rhs.ind);
        }       
        bool operator!=(const_iterator rhs) const{
            return !(*this == rhs);
        }       
    };

    // iterator helpers
    iterator begin(){
        return iterator(this, 0);
    }
    iterator end(){
        return iterator(this, sz);
    }
    const_iterator begin() const {
        return const_iterator(this, 0);
    }
    const_iterator end() const {
        return const_iterator(this, sz);
    }

    iterator insert(iterator it, const T& elem){
        insert(it.ind, elem);
        return it;
    }
    iterator erase(iterator it){
        erase(it.ind);
        return it;
    }
    
private:
    void clone(const Vector& other){
        sz = other.sz;
        cap = other.cap;
        if (cap == 0) {
            data = nullptr;
        } else {
            data = new T[cap];
            for (int i = 0; i < sz; ++i) {
                data[i] = other.data[i];
            }
        }
    }
    void transfer(Vector& other){
        sz = other.sz;
        cap = other.cap;
        data = other.data;
        other.sz = 0;
        other.cap = 0;
        other.data = nullptr;
    }

public:
    // Copy constructor
    Vector(const Vector& other){
                clone(other); }

    // Copy assignment
    Vector& operator=(const Vector& other){
        if (this != &other) {
            delete[] data;
            clone(other);
        }
        return *this;
    }

    // Move constructor
    Vector(Vector&& other){
        transfer(other);
    }

    // Move assignment
    Vector& operator=(Vector&& other){
        if (this != &other) {
            delete[] data;
            transfer(other);
        }
        return *this;
    }

    ~Vector(){
        delete[] data; 
    }

    // helpers
    void reallocate(int new_cap){
        if (new_cap < sz) {
            throw std::out_of_range("new_cap must be >= size");
        }
        if (new_cap != cap) {
            T* new_array = new T[new_cap];
            for (int i = 0; i < sz; ++i) {
                new_array[i] = data[i];
            }
            delete[] data;
            data = new_array;
            cap = new_cap; 
        }
    }

    void shrink(){
        if (sz < cap / 4) {
            reallocate(std::max(1, cap / 2));
        }
    }
    
    void shrink_to_fit(){
        reallocate(std::max(1, sz));
    }
};

} // namespace dsa
