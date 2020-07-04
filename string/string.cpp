#include "MyString.h"
#include <string>
#include <iostream>

MyString::MyString()
{
	std::cout << "Default constructor call" << std::endl;
	str = nullptr;
	size = 0;
}

MyString::MyString(const char* str)
{
	std::cout << "Constructor with parametrs call" << std::endl;
	this->size = strlen(str);
	this->str = new char[size + 1];
	for (size_t i = 0; i < size; ++i)
		this->str[i] = str[i];
	this->str[size] = '\0';
}

MyString::MyString(const MyString& obj)
{
	std::cout << "Copy constructor call" << std::endl;
	this->size = strlen(obj.str);
	this->str = new char[size + 1];
	for (size_t i = 0; i < size; ++i)
		this->str[i] = obj.str[i];
	this->str[size] = '\0';
}

MyString::MyString(MyString&& other) noexcept
{
	std::cout << "Move constructor call" << std::endl;
	this->size = other.size;
	this->str = other.str;
	other.str = nullptr;
}

MyString::~MyString()
{
	delete[] this->str;
}

MyString& MyString::operator=(const MyString& obj)
{
	if (this->str != nullptr)
		delete[] this->str;
	this->size = strlen(obj.str);
	this->str = new char[size + 1];
	for (size_t i = 0; i < size; ++i)
		this->str[i] = obj.str[i];
	this->str[size] = '\0';
	return *this;
}

MyString MyString::operator+(const MyString& obj)
{
	MyString concat;
	concat.size = this->size + strlen(obj.str);
	concat.str = new char[concat.size + 1];
	size_t i = 0;
	for (; i < this->size; ++i)
		concat.str[i] = this->str[i];
	for (size_t j = 0; j < obj.size; ++j, ++i)
		concat.str[i] = obj.str[j];
	concat.str[concat.size] = '\0';
	return concat;
}

bool MyString::operator==(const MyString& obj)
{
	bool str = (this->str = obj.str)? true: false;
	return str;
}

bool MyString::operator!=(const MyString& obj)
{
	return !(this->operator == (obj));
}

char& MyString::operator[](int index)
{
	return this->str[index];
}

int MyString::size_str()
{
	return size;
}

void MyString::Display()
{
	std::cout << str << "\t" << size << std
		::endl;
}







