// =================================================================
//
// File: list.h
// Author: José Ricardo Rosales Castañeda
// Date: 24/09/2022
// 
// =================================================================
#ifndef LIST_H
#define LIST_H

#include <string>
#include <sstream>
#include "exception.h"
#include "header.h"

template <class T> class List;

// =================================================================
// Definition of the Node class
// =================================================================
template <class T>
class Node {
private:
	Node(T);
	Node(T, Node<T>*);

	T	    value;
	Node<T> *next;

	friend class List<T>;
};

// =================================================================
// Constructor. Initializes the value of the node. The variable next
// is initialized to null.
//
// @param val, stored value in the node.
// @complexity: O(1)
// =================================================================
template <class T>
Node<T>::Node(T val) : value(val), next(NULL) {
}

// =================================================================
// Constructor. Initializes both instance variables.
//
// @param val, stored value in the node.
// @param nxt, the next node.
// @complexity: O(1)
// =================================================================
template <class T>
Node<T>::Node(T val, Node* nxt) : value(val), next(nxt) {
}

// =================================================================
// Definition of the List class
// =================================================================
template <class T>
class List {
private:
	Node<T> *head;
	uint 	size;

public:
	List();
	~List();

	uint  length() const;
	bool empty() const;
	bool contains(T) const;
	void clear();
	std::string toString() const;

	T    front() const;
	T    last() const;
	T    get(uint) const;

	void push_front(T);
	void push_back(T);
	void insert_at(T, uint);

	T    pop_front();
	T 	 pop_back();
	T    remove_at(uint);

	long int  indexOf(T) const;
};

// =================================================================
// Constructor. Initializes both instance variables to zero.
// @complexity: O(1)
// =================================================================
template <class T>
List<T>::List() :head(NULL), size(0) {
}

// =================================================================
// Destructor. Remove all items from the list.
// @complexity: O(n)
// =================================================================
template <class T>
List<T>::~List() {
	clear();
}

// =================================================================
// Returns if the list is empty or not
//
// @returns true if the list is empty, false otherwise.
// @complexity: O(1)
// =================================================================
template <class T>
bool List<T>::empty() const {
	return (head == NULL);
}

// =================================================================
// Returns the number of items in the list.
//
// @returns size, the number of items in the list.
// @complexity: O(1)
// =================================================================
template <class T>
uint List<T>::length() const {
	return size;
}

// =================================================================
// Determines if an item is in the list.
//
// @returns true if val is in the list, false otherwise
// @complexity: O(n)
// =================================================================
template <class T>
bool List<T>::contains(T val) const {
	Node<T> *p;

	p = head;
	while (p != NULL) {
		if(p->value == val) {
			return true;
		}
		p = p->next;
	}
	return false;
}

// =================================================================
// Remove all items from the list.
// @complexity: O(n)
// =================================================================
template <class T>
void List<T>::clear() {
	Node<T> *p, *q;

	p = head;
	while (p != NULL){
		q = p->next;
		delete p;
		p = q;
	}

	head = NULL;
	size = 0;
}

// =================================================================
// String representation of the elements in the list.
//
// @returns a string containing all the elements of the list.
// @complexity: O(n)
// =================================================================
template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Node<T> *p;

	p = head;
	aux << "[";
	while (p != NULL) {
		aux << p->value;
		if (p->next != NULL) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

// =================================================================
// Returns the first item in the list.
//
// @returns the object T at the beginning of the list.
// @throws NoSuchElement, if the list is empty.
// @complexity: O(1)
// =================================================================
template <class T>
T List<T>::front() const {
	if (empty()) {
		throw NoSuchElement();
	}

	return head->value;
}

// =================================================================
// Returns the last item in the list.
//
// @returns the object T at the end of the list.
// @throws NoSuchElement, if the list is empty.
// @complexity: O(n)
// =================================================================
template <class T>
T List<T>::last() const {
	Node<T> *p;

	if (empty()) {
		throw NoSuchElement();
	}

	p = head;
	while (p->next != NULL) {
		p = p->next;
	}
	return p->value;
}

// =================================================================
// Returns the element that is in the position indicated by index.
//
// @returns the element in index
// @throws IndexOutOfBounds, if index >= size.
// @complexity: O(n)
// =================================================================
template <class T>
T List<T>::get(uint index) const {
	T aux;
	uint i;
	Node<T> *p;

	if (index >= size) {
		throw IndexOutOfBounds();
	}

	p = head;
	for (i = 0; i < index; i++) {
		p = p->next;
	}
	aux = p->value;
	return aux;
}

// =================================================================
// Add an item to the beginning of the list. Increase the size of
// the list.
// @complexity: O(1)
// =================================================================
template <class T>
void List<T>::push_front(T val) {
	Node<T> *q;

	q = new Node<T>(val);
	q->next = head;
	head = q;
	size++;
}

// =================================================================
// Add an item to the end of the list. Increase the size of
// the list.
// @complexity: O(n)
// =================================================================
template <class T>
void List<T>::push_back(T val) {
	Node<T> *p, *q;

	if (empty()) {
		push_front(val);
		return;
	}

	p = head;
	while (p->next != NULL) {
		p = p->next;
	}

	q = new Node<T>(val);
	q->next = p->next;
	p->next = q;
	size++;
}

// =================================================================
// Add an element in index (0 <= index <= size). The element that
// was in that position is shifted to the right.
//
// @throws IndexOutOfBounds, if index > size.
// @complexity: O(n)
// =================================================================
template <class T>
void List<T>::insert_at(T val, uint index) {
	Node<T> *p, *q;

	if (index > size) {
		throw IndexOutOfBounds();
	}

	if (index == 0) {
		push_front(val);
		return;
	}

	p = head;
	while (index > 1) {
		p = p->next;
		index--;
	}

	q = new Node<T>(val);
	q->next = p->next;
	p->next = q;
	size++;
}

// =================================================================
// Delete the item at the beginning of the list.
//
// @returns the element that was at the beginning of the list.
// @throws NoSuchElement if the list is empty
// @complexity: O(1)
// =================================================================
template <class T>
T List<T>::pop_front() {
	T val;
	Node<T> *p;

	if (empty()) {
		throw NoSuchElement();
	}

	p = head;

	head = p->next;
	val = p->value;

	delete p;
	size--;
	return val;
}

// =================================================================
// Delete the item at the end of the list.
//
// @returns the element that was at the end of the list.
// @throws NoSuchElement if the list is empty
// @complexity: O(n)
// =================================================================
template <class T>
T List<T>::pop_back() {
	Node<T> *p, *q;
	T val;

	if (empty()) {
		throw NoSuchElement();
	}

	if (size == 1) {
		return pop_front();
	}

	q = NULL;
	p = head;
	while (p->next != NULL) {
		q = p;
		p = p->next;
	}

	q->next = p->next;
	val = p->value;

	delete p;
	size--;

	return val;
}

// =================================================================
// Delete the element found in index (0 <= index <size).
//
// @returns the element that was in index.
// @throws IndexOutOfBounds, if index >= size.
// @complexity: O(n)
// =================================================================
template <class T>
T List<T>::remove_at(uint index) {
	T aux;
	Node<T> *p, *q;

	if (index >= size) {
		throw IndexOutOfBounds();
	}

	if (index == 0) {
		return pop_front();
	}

	q = NULL;
	p = head;
	while (index > 0) {
		q = p;
		p = p->next;
		index--;
	}

	q->next = p->next;
	aux = p->value;

	delete p;
	size--;

	return aux;
}

// =================================================================
// Returns the position of an item in the list.
//
// @returns the position of an item in the list, -1 otherwise.
// @throws IndexOutOfBounds, if index >= size.
// @complexity: O(n)
// =================================================================
template <class T>
long int List<T>::indexOf(T val) const {
	Node<T> *p;
	long int i;

	p = head;
	i = 0;
	while (p != NULL) {
		if (p->value == val) {
			return i;
		}
		p = p->next;
		i++;
	}
	return -1;
}

#endif /* LIST_H */
