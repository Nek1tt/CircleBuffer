#pragma once
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <algorithm>
#include <utility>
#include <string_view>

#if defined(_MSC_VER)
#define FUNCTION_NAME __FUNCSIG__
#else
#define FUNCTION_NAME __PRETTY_FUNCTION__
#endif

typedef char value_type;

class CircularBuffer {
	value_type* buffer;

public:
	CircularBuffer();
	~CircularBuffer() = default;
	CircularBuffer(const CircularBuffer& cb);
	CircularBuffer(CircularBuffer&& cb) noexcept;

	//������������ ����� �������� �������.
	explicit CircularBuffer(int capacity);
	//������������ ����� �������� �������, ������� ��������� ��� ��������� elem.
	CircularBuffer(int capacity, const value_type& elem);

	CircularBuffer(std::initializer_list<value_type> init_list);


	//������ �� �������. �� ��������� ������������ �������.
	value_type& operator[](int i);
	const value_type& operator[](int i) const;

	//������ �� �������. ������ ������� ���������� � ������ ��������� �������.
	value_type& at(int i);
	const value_type& at(int i) const;

	value_type& front(); //������ �� ������ �������.
	value_type& back();  //������ �� ��������� �������.
	const value_type& front() const;
	const value_type& back() const;

	//������������ - �������� ��������� ����� ���, ��� ��� ������ �������
	//������������ � ������ �������������� ������. ���������� ��������� 
	//�� ������ �������.
	value_type* linearize();
	//���������, �������� �� ����� ���������������.
	bool is_linearized() const;
	//�������� ����� ���, ��� �� �������� ������� �������� ������� 
	//� �������� new_begin.
	void rotate(int new_begin);
	//���������� ���������, ���������� � ������.
	int size() const;
	bool empty() const;
	//true, ���� size() == capacity().
	bool full() const;
	//���������� ��������� ����� � ������.
	int reserve() const;
	//������� ������
	int capacity() const;

	void set_capacity(int new_capacity);
	//�������� ������ ������.
	//� ������ ����������, ����� �������� ����������� ��������� item.
	void resize(int new_size, const value_type& item = value_type());
	//�������� ������������.
	CircularBuffer& operator=(const CircularBuffer& cb);

	//�������� �����������
	CircularBuffer& operator=(CircularBuffer&& cb) noexcept;

	//���������� ���������� ������ � ������� cb.
	void swap(CircularBuffer& cb);

	//��������� ������� � ����� ������. 
	//���� ������� ������ ������ ����� ��� �������, �� ��������������
	//������ ������� ������ (�.�., ����� �����������). 
	void push_back(const value_type& item = value_type());
	//��������� ����� ������� ����� ������ ��������� ������. 
	//���������� push_back, ����� ���������� ��������� ������� ������.
	void push_front(const value_type& item = value_type());
	//������� ��������� ������� ������.
	void pop_back();
	//������� ������ ������� ������.
	void pop_front();

	//��������� ������� item �� ������� pos. ������� ������ �������� ����������.
	void insert(int pos, const value_type& item = value_type());
	//������� �������� �� ������ � ��������� [first, last).
	void erase(int first, int last);
	//������� �����.
	void clear();

	CircularBuffer& func2(CircularBuffer&& cb);

private:
	size_t cap;
	size_t sizeBuf;
	size_t head;
	size_t tail;
};

template <typename T>
CircularBuffer func1(T&& cb);


bool operator==(const CircularBuffer& a, const CircularBuffer& b);
bool operator!=(const CircularBuffer& a, const CircularBuffer& b);

template <typename T>
CircularBuffer func1(T&& cb)
{
	std::cout << FUNCTION_NAME << std::endl;
	return std::forward<T>(cb);
}
