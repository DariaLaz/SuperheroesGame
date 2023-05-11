#pragma once
#include "Constants.h"
#include <iostream>
template <typename T>
class vector
{
	size_t _size = 0;
	size_t _capacity;
	T* _arr;
public:
	vector(size_t capacity = VectorConstants::DEF_CAPACITY);
	vector(const vector<T>& other);
	vector(vector<T>&& other);
	vector<T>& operator=(const vector<T>& other);
	vector<T>& operator=(vector<T>&& other);
	~vector();

	//ITERATORS 
	//Return iterator to beginning
	T* begin();
	//Return iterator to end 
	T* end();
	//Return const_iterator to beginning
	const T* begin() const;
	//Return const_iterator to end
	const T* end() const;

	//CAPACITY
	//Return size
	size_t size() const;
	//Change size
	void resize(size_t size);
	//Return size of allocated storage capacity
	size_t capacity() const;
	//Test whether vector is empty
	bool empty() const;
	//Request a change in capacity
	bool reserve(size_t capacity);
	//Shrink to fit
	void shrink_to_fit();

	//ELEMENT ACCESS
	//Access element
	const T& operator[](size_t idx) const;
	T& operator[](size_t idx);
	//Access element
	const T& at(size_t idx) const;
	T& at(size_t idx);
	//Access first element
	const T& front() const; //Calling this function on an empty container causes undefined behavior.
	T& front(); //Calling this function on an empty container causes undefined behavior.
	//Access last element
	const T& back() const; //Calling this function on an empty container causes undefined behavior.
	T& back(); //Calling this function on an empty container causes undefined behavior.
	//Access data - Returns a direct pointer to the memory array
	const T* data() const;
	T* data();

	//MODIFIERS
	//Assign vector content
	void assign(size_t n, const T& val); //first.assign (7,100); -> 7 ints with a value of 100
	//Add element at the end
	void push_back(const T& element);
	void push_back(T&& element);
	//Delete last element
	void pop_back();
	//Insert elements 
	T* insert(size_t idx, const T& val);
	T* insert(size_t idx, T&& val);
	//Erase elements
	T* erase(size_t idx);
	T* erase(size_t start, size_t end);
	//Swap content
	void swap(vector<T>& other);
	//Clear content
	void clear() noexcept;

	bool constains(const T& value) const;
	int find(const T& value) const;

	//RELATIONAL OPERATIONS
	friend bool operator==(const vector<T>& lhs, const vector<T>& rhs);
	friend bool operator!=(const vector<T>& lhs, const vector<T>& rhs);
	friend bool operator<(const vector<T>& lhs, const vector<T>& rhs);
	friend bool operator<=(const vector<T>& lhs, const vector<T>& rhs);
	friend bool operator>(const vector<T>& lhs, const vector<T>& rhs);
	friend bool operator>=(const vector<T>& lhs, const vector<T>& rhs);

private:
	void copyFrom(const vector<T>& other);
	void moveFrom(vector<T>&& other);
	void free();
};
template <class T>
void swap(vector<T>& first, vector<T>& second);

template <typename T>
void swap(T& v1, T& v2) {
	T temp(v1);
	v1 = v2;
	v2 = temp;
}

template <typename T>
bool operator==(const vector<T>& lhs, const vector<T>& rhs);
template <typename T>
bool operator!=(const vector<T>& lhs, const vector<T>& rhs);
template <typename T>
bool operator<(const vector<T>& lhs, const vector<T>& rhs);
template <typename T>
bool operator<=(const vector<T>& lhs, const vector<T>& rhs);
template <typename T>
bool operator>(const vector<T>& lhs, const vector<T>& rhs);
template <typename T>
bool operator>=(const vector<T>& lhs, const vector<T>& rhs);


//implementation

template<typename T> vector<T>::vector(size_t capacity) {
	_capacity = capacity;
	_size = 0;
	_arr = new T[capacity];
}
template<typename T> vector<T>::vector(const vector<T>& other) {
	copyFrom(other);
}
template<typename T> vector<T>::vector(vector<T>&& other) {
	moveFrom(std::move(other));
}
template<typename T> vector<T>& vector<T>::operator=(const vector<T>& other) {
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
template<typename T> vector<T>& vector<T>::operator=(vector<T>&& other) {
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}
template<typename T> vector<T>::~vector() {
	free();
}

//ITERATORS 
template<typename T> T* vector<T>::begin() {
	return &_arr[0];
}
template<typename T> T* vector<T>::end() {
	return &_arr[_size - 1];
}
template<typename T> const T* vector<T>::begin() const {
	return &_arr[0];
}
template<typename T> const T* vector<T>::end() const {
	return &_arr[_size - 1];
}

//CAPACITY
template<typename T> size_t vector<T>::size() const {
	return _size;
}
template<typename T> void vector<T>::resize(size_t capacity) {
	T* arr = new T[capacity];
	for (size_t i = 0; i < _size; i++)
	{
		arr[i] = _arr[i];
	}
	delete[] _arr;
	_arr = arr;
	_capacity = capacity;
}
template<typename T> size_t vector<T>::capacity() const {
	return _capacity;
}
template<typename T> bool vector<T>::empty() const {
	return _size == 0;
}
template<typename T> bool vector<T>::reserve(size_t capacity) {
	resize(capacity);
}
template<typename T> void vector<T>::shrink_to_fit() {
	resize(_size);
}

//ELEMENT ACCESS
template<typename T> const T& vector<T>::operator[](size_t idx) const {
	if (idx >= _size)
	{
		throw std::out_of_range("Out of range!");
	}
	return *&_arr[idx];
}
template<typename T> T& vector<T>::operator[](size_t idx) {
	if (idx >= _size)
	{
		throw std::out_of_range("Out of range!");
	}
	return _arr[idx];
}
template<typename T> const T& vector<T>::at(size_t idx) const {
	if (idx >= _size)
	{
		throw std::out_of_range("Out of range!");
	}
	return &_arr[idx];
}
template<typename T> T& vector<T>::at(size_t idx) {
	if (idx >= _size)
	{
		throw std::out_of_range("Out of range!");
	}
	return &_arr[idx];
}
template<typename T> const T& vector<T>::front() const {
	return &_arr[0];
}
template<typename T> T& vector<T>::front() {
	return &_arr[0];
}
template<typename T> const T& vector<T>::back() const {
	return &_arr[_size - 1];
}
template<typename T> T& vector<T>::back() {
	return &_arr[_size - 1];
}
template<typename T> const T* vector<T>::data() const {
	return &_arr;
}
template<typename T> T* vector<T>::data() {
	return _arr;
}

//MODIFIERS
template<typename T> void vector<T>::assign(size_t n, const T& val) {
	if (_size + n > _capacity)
	{
		while (_size + n > _capacity)
		{
			_capacity *= 2;
		}
		resize(_capacity);
	}
	for (size_t i = 0; i < n; i++)
	{
		_arr[_size++] = val;
	}
}
template<typename T> void vector<T>::push_back(const T& element) {
	if (_size == _capacity)
	{
		resize(_capacity * 2);
	}
	_arr[_size++] = element;
}
template<typename T> void vector<T>::push_back(T&& element) {
	if (_size == _capacity)
	{
		resize(_capacity * 2);
	}
	_arr[_size++] = std::move(element);
}
template<typename T> void vector<T>::pop_back() {
	_size--;
	if (_capacity / 4 > _size)
	{
		resize(_capacity / 2);
	}
}
template<typename T> T* vector<T>::insert(size_t idx, const T& val) {
	if (idx >= _size)
	{
		throw std::out_of_range("Out of range!");
	}
	if (_size == _capacity)
	{
		resize(_capacity * 2);
	}
	for (int i = _size; i > idx; i--)
	{
		_arr[i] = _arr[i - 1];
	}
	_arr[idx] = val;
	_size++;

	return _arr[idx];
}
template<typename T> T* vector<T>::insert(size_t idx, T&& val) {
	if (idx >= _size)
	{
		throw std::out_of_range("Out of range!");
	}
	if (_size == _capacity)
	{
		resize(_capacity * 2);
	}
	for (int i = _size; i > idx; i--)
	{
		_arr[i] = std::move(_arr[i - 1]);
	}
	_arr[idx] = std::move(val);
	_size++;

	return &_arr[idx];
}
template<typename T> T* vector<T>::erase(size_t idx) {
	if (idx >= _size)
	{
		throw std::out_of_range("Out of range!");
	}

	for (size_t i = idx; i < _size - 1; i++)
	{
		_arr[i] = _arr[i + 1];
	}
	_size--;
	if (_capacity / 4 > _size)
	{
		resize(_capacity / 2);
	}

	if (idx >= _size)
	{
		idx = _size - 1;
	}

	return &_arr[idx];
}
template<typename T> T* vector<T>::erase(size_t start, size_t end) { // [first, last)
	if (start >= _size || end >= _size || start > end)
	{
		throw std::out_of_range("Out of range!");
	}
	for (size_t i = 0; i < (end - start); i++)
	{
		if (end + i < _size)
		{
			_arr[start + i] = _arr[end + i];
		}
	}
	_size -= (end - start);
	if (_capacity / 4 > _size)
	{
		while (_capacity / 4 > _size)
		{
			_capacity /= 2;
		}
		resize(_capacity);
	}
	if (end >= _size)
	{
		end = _size - 1;
	}

	return &_arr[end];
}
template<typename T> void vector<T>::swap(vector<T>& other) {
	vector temp = *this;
	*this = other;
	other = temp;
}
template<typename T> void vector<T>::clear() noexcept {
	_size = 0;
	_capacity = VectorConstants::DEF_CAPACITY;
	delete[] _arr;
	_arr = new T[VectorConstants::DEF_CAPACITY];
}

//RELATIONAL OPERATIONS
template<typename T> bool operator==(const vector<T>& lhs, const vector<T>& rhs) {
	if (lhs.size() != lhs.size())
	{
		return false;
	}
	for (size_t i = 0; i < lhs.size(); i++)
	{
		if (lhs[i] != rhs[i])
		{
			return false;
		}
	}
	return true;
}
template<typename T> bool operator!=(const vector<T>& lhs, const vector<T>& rhs) {
	return !(operator==(lhs, rhs));
}
template<typename T> bool operator<(const vector<T>& lhs, const vector<T>& rhs) {
	size_t idx = 0;
	while (true)
	{
		if (idx == lhs.size() && idx != rhs.size())
		{
			return true;
		}
		if (idx != lhs.size() && idx == rhs.size())
		{
			return false;
		}

		if (lhs[idx] != rhs[idx])
		{
			return (lhs[idx] < rhs[idx]);
		}
		idx++;
	}
}
template<typename T> bool operator<=(const vector<T>& lhs, const vector<T>& rhs) {
	return operator<(lhs, rhs) || operator==(lhs, rhs);
}
template<typename T> bool operator>(const vector<T>& lhs, const vector<T>& rhs) {
	return !(operator<=(lhs, rhs));
}
template<typename T> bool operator>=(const vector<T>& lhs, const vector<T>& rhs) {
	return operator>(lhs, rhs) || operator==(lhs, rhs);
}

//private
template<typename T> void vector<T>::copyFrom(const vector<T>& other) {
	_size = other.size();
	_capacity = other.capacity();
	_arr = new T[_capacity];
	for (size_t i = 0; i < _size; i++)
	{
		_arr[i] = other._arr[i];
	}
}
template<typename T> void vector<T>::moveFrom(vector<T>&& other) {
	_size = other.size();
	_capacity = other.capacity();
	_arr = other._arr;
	other._arr = nullptr;
}
template<typename T> void vector<T>::free() {
	delete[] _arr;
	_size = 0;
}


template<typename T> bool vector<T>::constains(const T& value) const {
	for (size_t i = 0; i < _size; i++)
	{
		if (_arr[i] == value)
		{
			return true;
		}
	}
	return false;
}
template<typename T> int vector<T>::find(const T& value) const {
	for (size_t i = 0; i < _size; i++)
	{
		if (_arr[i] == value)
		{
			return i;
		}
	}
	return -1;
}
