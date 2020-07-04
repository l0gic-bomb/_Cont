// 18.01.2019

#include <string>
#pragma once

class MyString
{
private:
	char* str;
	size_t size;
public:
	MyString(); // default constructor
	MyString(const char* str); // constructor with parametrs 
	MyString(const MyString& obj); // copy constructor
	MyString(MyString&& other) noexcept; // move constructor 
	~MyString(); // destructor

	MyString& operator=(const MyString& obj);
	MyString operator+(const MyString& obj);

	bool operator==(const MyString& obj);
	bool operator!=(const MyString& obj);
	char& operator[](int index);

	int size_str();
	void Display();
	
};

