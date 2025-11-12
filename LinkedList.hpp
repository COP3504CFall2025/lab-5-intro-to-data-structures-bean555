#pragma once
#include <iostream>
using namespace std;



template <typename T>
class LinkedList {
	struct Node {
		T data;
		Node* prev;
		Node* next;
	};
public:
	// Behaviors
	void printForward() const {
		Node* stepper = head;
		while (stepper != nullptr) {
			std::cout << stepper->data << std::endl;
			stepper = stepper->next;
		}
	}
	void printReverse() const {
		Node* stepper = tail;
		while (stepper != nullptr) {
			std::cout << stepper -> data << std::endl;
			stepper = stepper->prev;
		}
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const {return count;}
	Node* getHead() {return head;}
	const Node* getHead() const{return head;}
	Node* getTail() {return tail;}
	const Node* getTail() const {return tail;}

	// Insertion
	void addHead(const T& data) {
		if (head == nullptr) {
			head = new Node{data, nullptr, nullptr};
			tail = head;
			head->data = data;
		}
		else {
			Node* newTemp = new Node{data, nullptr, head};
			head = newTemp;
		}
		count++;

	}
	void addTail(const T& data) {
		if (head == nullptr) {
			head = new Node{data, nullptr, nullptr};
			tail = head;
		}
		else {
			Node* newTemp = new Node{data, tail, nullptr};
			tail->next = newTemp;
			tail = newTemp;
		}
		count++;
	}

	// Removal
	bool removeHead() {
		if (head == nullptr) return false;
		if (count == 1) {
			tail = nullptr;
			delete head;
			count--;
			return true;
		}
		head = head->next; // pos error like mem leak
		delete head->prev;
		head->prev = nullptr;
		count--;
		return true;
	}
	bool removeTail() {
		if (count == 0) return false;
		if (count == 1) {
			tail = nullptr;
			delete head;
			count--;
			return true;
		}
		Node* newTemp = tail->prev;
		newTemp->next = nullptr;
		delete tail;
		tail = newTemp;
		count--;
		return true;
	}
	void clear() {
		while (removeHead()){}
	}
	// Operators: move and copy
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
		if (this == other) return *this;
		head = other.head;
		tail = other.tail;
		count = other.count;
		// prevent memleaks
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
		return *this;
	}

	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
		// setup and destruction of what was previously held by this
		if (this == &rhs) return this;
		clear();
		head = nullptr;
		tail = nullptr;
		count = rhs.count;

		// coppying over the data
		Node* stepper = rhs.head;
		while (stepper != nullptr){
			addTail(stepper->data);
			stepper = stepper->next;
		}
		// removing any possible mem leaks of data (like removing dangling pointers)
		return *this;
	}

	// constructors (default, copy, move, and destructor
	// Construction/Destruction
	LinkedList() { // default
		head = nullptr;
		tail = nullptr;
		count = 0;
	}

	LinkedList(const LinkedList<T>& list) { // copy constructor
		head = nullptr;
		tail = nullptr;
		count = 0;

		Node* temp = list.head;
		while (temp != nullptr) {
			addTail(temp->data);
			temp = temp->next;
		}

	}
	LinkedList(LinkedList<T>&& other) noexcept { // move con
		head = other.head;
		tail = other.tail;
		count = other.count;

		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	}
	~LinkedList() {
		clear();
	}

private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;

};
