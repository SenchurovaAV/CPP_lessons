#ifndef VARRAY
#define VARRAY

#include <cstddef>
#include <iostream>
#include <exception>

const size_t S = 13;

const double End = 0;

template <class T>
class vArray 
{
public:
    vArray();
    vArray(const size_t &n);
    ~vArray();

    void                Del_size();
    void                Change_Size(const size_t &n);
    void                Push(const T& val);

    const size_t&       GetSize() const;
    const size_t&       GetCur() const;

     void operator+=    (const vArray<T> &m_array);
     void operator=     (const vArray<T> &m_array);
//     void operator+     (const vArray<T> array, const vArray<T>& m_array);
     template <typename IO> 
     friend             std::istream &operator>>(std::istream &stream, vArray<IO> &arr);
     template <typename IO> 
     friend             std::istream &operator>>(std::istream &stream, vArray<IO> &arr);

private:
    T *mas;
    size_t cur;
    size_t size;

};

template<typename T>
vArray<T> operator+(const vArray<T>& array, const vArray<T>& array_);

template<typename T>
vArray<T>::vArray() : cur(S), size(0) 
{
    mas = new T[cur];
}    

template<typename T>
vArray<T>::vArray(const size_t &n): cur(n), size(0) {
    mas = new T[cur];
}

template<typename T>
vArray<T>::~vArray() {
    cur = 0;
    size = 0;
    delete[] mas;
}

template<typename T>
void vArray<T>::Change_Size(const size_t& n) {
    cur = n;
    T* newMas = new T[cur];
    if (n > cur) {
        for(int i = 0; i < size; ++i) {
            newMas[i] = mas[i];
        }
    } else if (n < cur) {
        for(int i = 0; i < cur; ++i) {
            newMas[i] = mas[i];
        }
    }
    delete[] mas;
    mas = newMas;
}

template<typename T>
const size_t& vArray<T>::GetSize() const {
    return size;
}

template<typename T>
const size_t& vArray<T>::GetCur() const {
    return cur;
}

template<typename T>
void vArray<T>::Push(const T &val) {
    if (cur == size)
        this->Del_size();
    mas[size++] = val;
}

template<typename T>
void vArray<T>::Del_size() {
    if (cur != 0){
        cur <<= 2;
    } else {
        cur = 1;
    }

    T *newMas = new T[cur];
    for (int i = 0; i < size; ++i) {
        newMas[i] = mas[i];
    }
    delete[] mas;
    mas = newMas;
}

template<typename T>
void vArray<T>::operator+=(const vArray<T>& m_array) {
    for(int i = 0; i < m_array.GetSize(); ++i) {
        this->Push(m_array[i]);
    }
}

template<typename T>
vArray<T> operator+(const vArray<T>& array, const vArray<T>& m_array) {
    vArray<T> NewvArray = vArray<T>(array.GetSize() + m_array.GetSize());
    for(int i = 0; i < array.GetSize(); ++i){
        NewvArray.Push(array[i]);
    }
    for(int i = 0; i < m_array.GetSize(); ++i){
        NewvArray.Push(m_array[i]);
    }
    return NewvArray;

 }   

template<typename T>
void vArray<T>::operator=(const vArray<T>& m_array) {
    size = m_array.size;
    cur = m_array.cur;
    delete[] mas;
    mas = new T[cur];
    for(int i = 0; i < size; ++i) {
        mas[i] = m_array[i];
    }
}

template<typename IO>
std::ostream &operator<<(std::ostream &stream, const vArray<IO>& array) {
    for (int i = 0; i < array.GetSize(); ++i) {
        stream << array[i] << ' ';
    }
    return stream;
}

template<typename IO>
std::istream &operator>>(std::istream& stream, vArray<IO>& array) {
    size_t i = 0;
    Q c;
    stream >> c;
    while (c != End) {
        if (array.GetCur() == i) {
            array.Del_size();
        }
        array[i] = c;
        stream >> c;
        ++i;
    }
    array.size = i;
    return stream;
}


#endif //VARRAY_H 