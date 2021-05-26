#ifndef LIST_H
#define LIST_H
#include <string>

template<class T>
class list {
private:
	class nodeList;
	nodeList* _head;
	int _size;
public:
	list();
	~list();
	T pop();
	T pop(int);
	void push(T value);
	int getSize();
	void sort();
	std::string getString();
	const T operator[](const int index) const;
	//friend bool operator==(const T &val1, const T& val2);
};

template <class T>
class list<T>::nodeList {
private:
	T _value;
	nodeList* _next;
public:
	nodeList() : _next(nullptr) {};
	nodeList(T value, nodeList* next) :
		_value(value), _next(next) {}
	T getValue() {
		return _value;
	}
	void setValue(T value) {
		_value = value;
	}
	nodeList* getNext() {
		return _next;
	}
	void setNext(nodeList* next) {
		_next = next;
	}
};


// methods list

template <class T>
list<T>::list() : _head(nullptr), _size(0) {}




template<class T>
list<T>::~list()
{
	while (_size > 0)
		this->pop();
}



template <class T>
T list<T>::pop() {
	if (_size == 0)
		throw;
	if (_size == 1) {
		T tempNextVal = _head->getValue();
		delete _head;
		_head = nullptr;
		this->_size = 0;
		return tempNextVal;
	}
	nodeList* temp = _head;
	while (temp->getNext()->getNext() != nullptr) temp = temp->getNext();
	T tempNextVal = temp->getNext()->getValue();
	delete temp->getNext();
	_size--;
	temp->setNext(nullptr);
	return tempNextVal;
}



template <class T>
T list<T>::pop(int index) {
	if (_size == 1 || _size == 0 || index == _size - 1) {
		return this->pop();
	}
	if (index == 0) {
		nodeList* temp = _head->getNext();
		T tempvalue = _head->getValue();
		_head = temp;
		_size--;
		return tempvalue;
	}
	nodeList* temp = _head;
	for (int i = 0; i < index - 1; i++)
		temp = temp->getNext();
	T tempNextVal = temp->getNext()->getValue();
	nodeList* tempNext = temp->getNext()->getNext();
	_size--;
	temp->setNext(tempNext);
	return tempNextVal;
}



template <class T>
void list<T>::push(T value) {
	if (_size == 0) {
		_head = new nodeList(value, nullptr);
		_size++;
		return;
	}
	nodeList* temp = _head;
	while (temp->getNext() != nullptr) temp = temp->getNext();
	temp->setNext(new nodeList(value, nullptr));
	_size++;
	return;
}



template <class T>
int list<T>::getSize() {
	return _size;
}



template <class T>
void list<T>::sort() { 
	if (_size == 1 || _size == 0)
		return;
	nodeList* temp = _head;
	bool f = false;
	for (int i = 0; i < _size - 1; i++) {
		temp = _head;
		f = false;
		for (int j = 0; j < _size - 1 - i; j++) {
			if ((temp->getValue()).cost > (temp->getNext()->getValue()).cost) {
				T tempVal = temp->getValue();
				temp->setValue(temp->getNext()->getValue());
				temp->getNext()->setValue(tempVal);
				f = true;
			}
			temp = temp->getNext();
		}
		if (!f)
			return;
	}
}


template <class T>
std::string list<T>::getString() { 
	nodeList* temp = _head;
	std::string _out = "";
	while (temp != NULL) {
		_out += temp->getValue() + '0';
		temp = temp->getNext();
	}
	return _out;
}



template <class T>
const T list<T>::operator[](const int index) const {
	nodeList* it = _head;
	if (index < 0 || index > _size)
		throw;
	for (int i = 0; i < index; i++) {
		it = it->getNext();
	}
	return it->getValue();
}

#endif