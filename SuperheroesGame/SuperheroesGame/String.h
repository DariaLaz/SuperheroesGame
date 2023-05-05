#pragma once
#pragma warning(disable: 4996)
#include "Constants.h"
#include <iostream>

namespace {
	union Data {
		struct {
			char buff[StringConstants::BUFF_SIZE];
		} stack;
		struct {
			char* ptr = nullptr;
			size_t capacity = StringConstants::DEF_CAPACITY;
			size_t size = 0;
		} heap;
		Data() : stack() {};
	};
}

class String
{
	Data _data;
public:
	String(const char* data = nullptr);
	String(const String& other);
	String& operator=(const String& other);
	String& operator=(String&& other) noexcept;
	String(String&& other) noexcept;
	~String();

	//ITERATORS
	//Return iterator to beginning
	char& begin();
	const char& begin() const;
	//Return iterator to end
	char& end();
	const char& end() const;

	//CAPACITY
	//Return length of string 
	size_t length() const;
	//Return size of allocated storage
	size_t capacity() const;
	//Clear string
	void clear();
	//Test if string is empty
	bool empty() const;
	//Shrink to fit
	void shrink_to_fit();

	//ELEMENT ACCESS
	//Get character of string
	const char& operator[](size_t idx) const;
	char& operator[](size_t idx);
	const char& at(size_t idx) const;
	char& at(size_t idx);
	//Access last character
	const char& back() const;
	char& back();
	//Access first character
	const char& front() const;
	char& front();

	//MODIFIERS
	//Append to string
	void operator+=(const char* str);
	void operator+=(const String& str);
	void operator+=(String&& str);
	void append(const char* str);
	void append(const String& str);
	void append(String&& str);
	//Append character to string
	void push_back(char ch);
	//Assign content to string
	String& assign(const String& str);
	String& assign(String&& str) noexcept;
	String& assign(const char* str);
	//Insert into string
	String& insert(size_t start, const String& str);
	String& insert(size_t start, String&& str);
	String& insert(size_t start, const char* str);
	//Swap string values
	void swap(String& str);
	//Delete last character
	void pop_back();

	//STRING OPERATIONS
	//Get string data
	const char* c_str() const;
	const char* data() const;
	//Copy sequence of characters from string
	size_t copy(char* str, size_t len, size_t pos = 0) const;
	size_t copy(String& str, size_t len, size_t pos = 0) const;
	//Find content in string
	int find(const String& str, size_t pos = 0) const;
	int find(const char* str, size_t pos = 0) const;
	//Find last occurrence of content in string
	int rfind(const String& str, size_t pos = 0) const;
	int rfind(const char* str, size_t pos = 0) const;
	//Generate substring
	String substr(size_t pos, size_t len) const;
	char* subchar(size_t pos, size_t len) const;
	//Compare strings
	int compare(const String& str) const;//0 -> equal; -1 -> <; 1 -> >
	int compare(const char* str)const;
	int compare(String&& str)const;

	//Extract string from stream
	friend std::ostream& operator<<(std::ostream& os, const String& str);
	//Insert string into stream
	friend std::istream& operator>>(std::istream& is, String& str);

	bool isSSO() const;

private:
	void copyFrom(const String& other);
	void moveFrom(String&& other);
	void free();

	String(size_t size);

	//Resize string
	void resize(size_t capacity);
	//Get string data
	char* getData();
	//set data
	void setData(const char*);
	void setSize(size_t size);
	void onSSO(size_t n);
	void offSSO();

};

String operator+(const String& lhs, const String& rhs);
void swap(String& lhs, String& rhs);

//RELATIONAL OPERATORS
bool operator==(const String& lhs, const String& rhs);
bool operator!=(const String& lhs, const String& rhs);
bool operator<(const String& lhs, const String& rhs);
bool operator<=(const String& lhs, const String& rhs);
bool operator>(const String& lhs, const String& rhs);
bool operator>=(const String& lhs, const String& rhs);

std::ostream& operator<<(std::ostream& os, const String& str);
std::istream& operator>>(std::istream& is, String& str);


bool areTheSame(const char* main, size_t pos, const char* substr);