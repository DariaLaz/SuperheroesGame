#include "String.h"

String::String(const char* data) {
	setData(data);
}
String::String(const String& other) {
	copyFrom(other);
}
String& String::operator=(const String& other) {
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;

}
String& String::operator=(String&& other) noexcept {
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}
String::String(String&& other) noexcept {
	moveFrom(std::move(other));
}
String::~String() {
	free();
}

//ITERATORS
char& String::begin() {
	return getData()[0];
}
const char& String::begin() const {
	return data()[0];
}
char& String::end() {
	return getData()[length() - 1];
}
const char& String::end() const {
	return data()[length() - 1];
}

//CAPACITY
size_t String::length() const {
	if (isSSO())
	{
		return StringConstants::BUFF_SIZE - (_data.stack.buff[StringConstants::BUFF_SIZE - 1] + 1);
	}
	return _data.heap.size << 1 >> 1;
}
size_t String::capacity() const {
	if (isSSO())
	{
		return StringConstants::BUFF_SIZE - 1;
	}
	return _data.heap.capacity;
}
void String::clear() {
	free();
	onSSO(0);
}
bool String::empty() const {
	return length() == 0;
}
void String::shrink_to_fit() {
	if (isSSO())
	{
		return;
	}
	resize(_data.heap.size);
}

//ELEMENT ACCESS
const char& String::operator[](size_t idx) const {
	return at(idx);
}
char& String::operator[](size_t idx) {
	return at(idx);
}
const char& String::at(size_t idx) const {
	if (idx > length())
	{
		throw std::out_of_range("Out of range!");
	}
	return data()[idx];
}
char& String::at(size_t idx) {
	if (idx > length())
	{
		throw std::out_of_range("Out of range!");
	}
	return getData()[idx];
}
const char& String::back() const {
	return at(length() - 1);
}
char& String::back() {
	return at(length() - 1);
}
const char& String::front() const {
	return at(0);
}
char& String::front() {
	return at(0);
}

//MODIFIERS
void String::operator+=(const char* str) {
	char* newData = new char[length() + strlen(str) + 1];
	strcpy(newData, data());
	strcat(newData, str);
	setData(newData);
	delete[] newData;
}
void String::operator+=(const String& str) {
	operator+=(str.data());
}
void String::operator+=(String&& str) {
	operator+=(std::move(str.data()));
}
void String::append(const char* str) {
	operator+=(str);
}
void String::append(const String& str) {
	operator+=(str.data());
}
void String::append(String&& str) {
	operator+=(std::move(str.data()));
}
void String::push_back(char ch) {
	operator+=(&ch);
}
String& String::assign(const String& str) {
	setData(str.data());
	return *this;
}
String& String::assign(String&& str) noexcept {
	setData(std::move(str.data()));
	return *this;
}
String& String::assign(const char* str) {
	setData(str);
	return *this;
}
String& String::insert(size_t start, const String& str) {
	return insert(start, str.data());
}
String& String::insert(size_t start, String&& str) {
	return insert(start, std::move(str.data()));
}
String& String::insert(size_t start, const char* str) {
	if (start >= length())
	{
		throw std::out_of_range("Out of range!");
	}
	size_t size = length() + strlen(str);
	char* newData = new char[size + 1];
	const char* data = this->data();
	for (size_t i = 0; i < size; i++)
	{
		if (i != start)
		{
			newData[i] = *data++;
			continue;
		}
		while (*str)
		{
			newData[i++] = *str++;
		}
		i--;
	}
	newData[size] = '\0';

	setData(newData);
	delete[] newData;
	return *this;
}
void String::swap(String& str) {
	String temp = *this;
	*this = str;
	str = temp;
}
void String::pop_back() {
	getData()[length() - 1] = '\0';
	setSize(length() - 1);
}

//STRING OPERATIONS
const char* String::c_str() const {
	return data();
}
const char* String::data() const {
	if (isSSO())
	{
		return _data.stack.buff;
	}
	return _data.heap.ptr;
}
size_t String::copy(char* str, size_t len, size_t pos) const {
	str = std::move(subchar(pos, len));
	return len;
}
size_t String::copy(String& str, size_t len, size_t pos) const {
	str.setData(std::move(subchar(pos, len)));
	return len;
}
int String::find(const String& str, size_t pos) const {
	return find(str.data(), pos);
}
int String::find(const char* str, size_t pos) const {
	size_t size = length();

	if (str == nullptr || pos >= size)
	{
		throw std::out_of_range("Out of range!");
	}
	const char* data = this->data();
	size_t strLen = strlen(str);
	for (size_t i = 0; i < size - strLen; i++)
	{
		if (str[0] == data[i])
		{
			if (areTheSame(data, i, str))
			{
				return i;
			}
		}
	}
	return -1;
}
int String::rfind(const String& str, size_t pos) const {
	return rfind(str.data(), pos);
}
int String::rfind(const char* str, size_t pos) const {
	size_t size = length();
	if (pos >= size)
	{
		throw std::out_of_range("Out of range!");
	}
	int res = -1;
	while (true)
	{
		int curr = find(str, pos);
		if (curr == -1 || pos == size - 1)
		{
			return res;
		}
		res = curr;
		pos++;
	}
}
String String::substr(size_t pos, size_t len) const {
	return String(std::move(subchar(pos, len)));
}
char* String::subchar(size_t pos, size_t len) const {
	if (pos + len > length())
	{
		throw std::out_of_range("Out of range!");
	}
	char* res = new char[len + 1];
	const char* data = this->data();
	for (size_t i = 0; i < len; i++)
	{
		res[i] = data[i + pos];
	}
	res[len] = '\0';
	return res;
}
int String::compare(const String& str)const {
	return compare(str.data());
}
int String::compare(const char* str)const {
	return strcmp(data(), str);
}
int String::compare(String&& str)const {
	return compare(std::move(str.data()));
}

//private
void String::copyFrom(const String& other) {
	if (other.isSSO())
	{
		strcpy(_data.stack.buff, other._data.stack.buff);
	}
	else
	{
		strcpy(_data.heap.ptr, other._data.heap.ptr);
		_data.heap.capacity = other._data.heap.capacity;
		_data.heap.size = other._data.heap.size;
	}
}
void String::moveFrom(String&& other) {
	if (other.isSSO())
	{
		strcpy(_data.stack.buff, other._data.stack.buff);
		_data.stack.buff[StringConstants::BUFF_SIZE - 1] = other._data.stack.buff[StringConstants::BUFF_SIZE - 1];
	}
	else
	{
		_data.heap.ptr = other._data.heap.ptr;
		other._data.heap.ptr = nullptr;
		_data.heap.capacity = other._data.heap.capacity;
		_data.heap.size = other._data.heap.size;
	}
}
void String::free() {
	if (!isSSO())
	{
		delete[] _data.heap.ptr;
	}
	_data.heap.size = 0;
}

void String::resize(size_t capacity) {
	char* arr = new char[capacity + 1];
	for (size_t i = 0; i < _data.heap.size; i++)
	{
		arr[i] = _data.heap.ptr[i];
	}
	delete[] _data.heap.ptr;
	_data.heap.ptr = arr;
}
char* String::getData() {
	if (isSSO())
	{
		return _data.stack.buff;
	}
	return _data.heap.ptr;
}
void String::setData(const char* data) {
	free();
	if (!data)
	{
		data = "\0";
	}
	size_t size = strlen(data);
	if (size >= StringConstants::BUFF_SIZE)
	{
		_data.heap.capacity = StringConstants::DEF_CAPACITY;
		while (_data.heap.capacity < size)
		{
			_data.heap.capacity *= 2;
		}
		if (isSSO())
		{
			_data.heap.ptr = nullptr;
		}
		resize(_data.heap.capacity);
		offSSO();
		_data.heap.size |= size;
		strcpy(_data.heap.ptr, data);
	}
	else
	{
		strcpy(_data.stack.buff, data);
		onSSO(size);
	}
}

bool String::isSSO() const {
	return (_data.stack.buff[StringConstants::BUFF_SIZE - 1] & (1 << 7)) == 0;
}
void String::onSSO(size_t n) {
	_data.stack.buff[StringConstants::BUFF_SIZE - 1] = 0;
	_data.stack.buff[StringConstants::BUFF_SIZE - 1] |= (StringConstants::BUFF_SIZE - n - 1);
}
void String::offSSO() {
	_data.stack.buff[StringConstants::BUFF_SIZE - 1] = 0;
	_data.stack.buff[StringConstants::BUFF_SIZE - 1] |= (1 << 7);
}
void String::setSize(size_t size) {
	if (isSSO())
	{
		_data.stack.buff[StringConstants::BUFF_SIZE - 1] = 0;
		_data.stack.buff[StringConstants::BUFF_SIZE - 1] |= (StringConstants::BUFF_SIZE - size - 1);
	}
	else
	{
		_data.heap.size++;
	}
}


String operator+(const String& lhs, const String& rhs) {
	String res(lhs);
	res += rhs;
	return res;
}
void swap(String& lhs, String& rhs) {
	lhs.swap(rhs);
}

//RELATIONAL OPERATORS
bool operator==(const String& lhs, const String& rhs) {
	return lhs.compare(rhs) == 0;
}
bool operator!=(const String& lhs, const String& rhs) {
	return !operator==(lhs, rhs);
}
bool operator<(const String& lhs, const String& rhs) {
	return lhs.compare(rhs) < 0;
}
bool operator<=(const String& lhs, const String& rhs) {
	return operator==(lhs, rhs) || operator<(lhs, rhs);
}
bool operator>(const String& lhs, const String& rhs) {
	return !(operator<=(lhs, rhs));
}
bool operator>=(const String& lhs, const String& rhs) {
	return operator==(lhs, rhs) || operator>(lhs, rhs);
}

std::ostream& operator<<(std::ostream& os, const String& str) {
	return os << str.data();
}
std::istream& operator>>(std::istream& is, String& str) {
	char buff[1024];
	is >> buff;
	str.setData(buff);
	return is;
}






bool areTheSame(const char* main, size_t pos, const char* substr) {
	while (*substr)
	{
		if (main[pos++] != *substr++)
		{
			return false;
		}
	}
	return true;
}