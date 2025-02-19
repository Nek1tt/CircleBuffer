#include "CircleBuffer.h"

CircularBuffer::CircularBuffer() : cap(0), sizeBuf(0), head(0), tail(0), buffer(nullptr) {}

CircularBuffer::CircularBuffer(const CircularBuffer& cb) : buffer(cb.buffer), sizeBuf(cb.sizeBuf), cap(cb.cap), head(cb.head),
tail(cb.tail) 
{
	std::cout << FUNCTION_NAME << " (Copy Constructor)" << std::endl;
	
}

CircularBuffer::CircularBuffer(CircularBuffer&& cb) noexcept : buffer(std::move(cb.buffer)), cap(std::move(cb.cap)), 
sizeBuf(std::move(cb.sizeBuf)), head(std::move(cb.head)), tail(std::move(cb.tail))
{
	std::cout << FUNCTION_NAME << " (Move Constructor)" << std::endl;
}

CircularBuffer::CircularBuffer(int capacity) : cap(capacity), sizeBuf(0), head(0), tail(0) {
	this->buffer = new value_type[capacity];
}

CircularBuffer::CircularBuffer(int capacity, const value_type& elem) : cap(capacity), head(0), tail(0), sizeBuf(capacity) {
	
	this->buffer = new value_type[capacity];
	for (int i = 0; i < capacity; i++)
	{
		this->buffer[i] = elem;
	}
}

CircularBuffer::CircularBuffer(std::initializer_list<value_type> init_list)
	: cap(init_list.size()), sizeBuf(init_list.size()), head(init_list.size()), tail(0) {
	this->buffer = new value_type[cap];
	std::copy(init_list.begin(), init_list.end(), this->buffer);
}

value_type& CircularBuffer::operator[](int i) {
	return this->buffer[(this->tail + i) % this->cap];
}

const value_type& CircularBuffer::operator[](int i) const {
	return this->buffer[(this->tail + i) % this->cap];
}

value_type& CircularBuffer::at(int i)
{
	if (0 <= i && i < this->sizeBuf)
	{
		return this->buffer[(this->tail + i) % this->cap];
	}
	else
	{
		throw std::out_of_range("Index out of range");
	}
}

const value_type& CircularBuffer::at(int i) const
{
	if (0 <= i && i < this->sizeBuf)
	{
		return this->buffer[(this->tail + i) % this->cap];
	}
	else
	{
		throw std::out_of_range("Index out of range");
	}
}

value_type& CircularBuffer::front() 
{
	return this->buffer[this->tail];
}

value_type& CircularBuffer::back() 
{
	return this->buffer[(this->head - 1 + this->cap) % this->cap];
}

const value_type& CircularBuffer::front() const
{
	return this->buffer[this->tail];
}

const value_type& CircularBuffer::back() const
{
	return this->buffer[(this->head - 1 + this->cap) % this->cap];
}

value_type* CircularBuffer::linearize()
{
	if (is_linearized())
	{
		return this->buffer;
	}
	value_type* tempBuffer = new value_type[this->cap];
	for (int i = 0; i < this->sizeBuf; i++) {
		tempBuffer[i] = this->buffer[(this->tail + i) % this->cap];
	}
	delete[] this->buffer;
	this->buffer = tempBuffer;
	this->head = this->sizeBuf % this->cap;
	this->tail = 0;
	return this->buffer;
}

bool CircularBuffer::is_linearized() const
{
	if (this->tail == 0)
	{
		return true;
	}
	return false;
}

void CircularBuffer::rotate(int new_begin)
{
	linearize();
	this->head = (this->head + this->sizeBuf) % this->cap;
	this->tail = new_begin % this->cap;
}

int CircularBuffer::size() const
{
	return this->sizeBuf;
}

bool CircularBuffer::empty() const
{
	if (this->sizeBuf == 0)
	{
		return true;
	}
	return false;
}

bool CircularBuffer::full() const
{
	if (this->size() == this->capacity())
	{
		return true;
	}
	return false;
}

int CircularBuffer::reserve() const
{
	return this->cap - this->sizeBuf;
}

int CircularBuffer::capacity() const
{
	return this->cap;
}

void CircularBuffer::set_capacity(int new_capacity)
{
	if (new_capacity <= 0) {
		throw std::invalid_argument("New capacity must be greater than 0");
	}

	value_type* newBuffer = new value_type[new_capacity];
	int elements_to_copy;
	if (new_capacity <= sizeBuf)
	{
		elements_to_copy = new_capacity;
	}
	else
	{
		elements_to_copy = sizeBuf;
	}

	for (int i = 0; i < elements_to_copy; ++i) {
		newBuffer[i] = this->buffer[(this->tail + i) % this->cap];
	}

	delete[] this->buffer;
	this->buffer = newBuffer;
	this->cap = new_capacity;
	this->head = elements_to_copy % new_capacity;
	this->tail = 0;
	this->sizeBuf = elements_to_copy;
}

void CircularBuffer::resize(int new_size, const value_type& item)
{
	if (new_size < 0)
	{
		throw std::invalid_argument("New size must be non-negative");
	}
	if (new_size > this->cap)
	{
		this->set_capacity(new_size);
	}
	if (new_size > this->sizeBuf)
	{
		for (int i = this->sizeBuf; i < new_size; i++)
		{
			this->buffer[(this->tail + i) % this->cap] = item;
		}
	}
	else if (new_size < this->sizeBuf)
	{
		this->tail = (this->head - new_size + this->cap) % this->cap;
	}
	this->sizeBuf = new_size;
	this->head = (this->tail + this->sizeBuf) % this->cap;
}

CircularBuffer& CircularBuffer::operator=(const CircularBuffer& cb)
{
	std::cout << FUNCTION_NAME << " (Copy Assignment)" << std::endl;
	if (this == &cb)
	{
		return *this;
	}
	delete[] this->buffer;
	this->cap = cb.cap;
	this->sizeBuf = cb.sizeBuf;
	this->head = cb.head;
	this->tail = cb.tail;
	this->buffer = new value_type[cb.cap];
	for (int i = 0; i < cb.cap; i++)
	{
		this->buffer[i] = cb.buffer[i];
	}
	return *this;
}

CircularBuffer& CircularBuffer::operator=(CircularBuffer&& cb) noexcept
{
	std::cout << FUNCTION_NAME << " (Move Assignment)" << std::endl;
	if (this != &cb)
	{
		delete[] this->buffer;
		this->cap = std::move(cb.cap);
		this->head = std::move(cb.head);
		this->tail = std::move(cb.tail);
		this->sizeBuf = std::move(cb.sizeBuf);
		this->buffer = std::exchange(cb.buffer, nullptr);
		cb.cap = 0;
		cb.head = 0;
		cb.tail = 0;
		cb.sizeBuf = 0;
	}
	return *this;
}

void CircularBuffer::swap(CircularBuffer& cb)
{
	std::swap(*this, cb);
}

void CircularBuffer::push_back(const value_type& item)
{
	if (this->full()) {
		this->tail = (this->tail + 1) % this->cap; 
	}
	else {
		this->sizeBuf++;
	}
	this->buffer[this->head] = item;
	this->head = (this->head + 1) % this->cap;
}

void CircularBuffer::push_front(const value_type& item)
{
	this->tail = (this->tail - 1 + this->cap) % this->cap;
	this->buffer[this->tail] = item;

	if (this->full()) {
		this->head = (this->head - 1 + this->cap) % this->cap;
	}
	else 
	{
		this->sizeBuf++;
	}
}

void CircularBuffer::pop_back()
{
	if (this->empty())
	{
		throw std::out_of_range("Buffer is empty");
	}
	this->head = (this->head - 1 + this->cap) % this->cap;
	this->sizeBuf--;
}

void CircularBuffer::pop_front()
{
	if (this->empty())
	{
		throw std::out_of_range("Buffer is empty");
	}
	this->tail = (this->tail + 1) % this->cap;
	this->sizeBuf--;
}



void CircularBuffer::insert(int pos, const value_type& item)
{
	if (pos < 0 || pos >= this->sizeBuf)
	{
		throw std::out_of_range("Index out of range");
	}
	this->buffer[(this->tail + pos) % this->cap] = item;
	if (!this->full())
	{
		this->sizeBuf++;
	}
}

void CircularBuffer::erase(int first, int last)
{
	if (this->empty())
	{
		throw std::out_of_range("buffer is empty");
	}
	for (int i = first; i < last; i++)
	{
		this->buffer[i] = NULL;
		this->sizeBuf--;
	}
}

void CircularBuffer::clear()
{
	this->head = 0;
	this->tail = 0;
	this->sizeBuf = 0;
	std::memset(this->buffer, NULL, this->cap * sizeof(value_type));
}


CircularBuffer& CircularBuffer::func2(CircularBuffer&& cb)
{
	std::cout << FUNCTION_NAME << std::endl;
	return cb;
}

bool operator==(const CircularBuffer& a, const CircularBuffer& b)
{
	if (a.size() != b.size())
	{
		return false;
	}
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i] != b[i])
		{
			return false;
		}
	}
	return true;
}

bool operator!=(const CircularBuffer& a, const CircularBuffer& b)
{
	if (a == b)
	{
		return false;
	}
	return true;
}

