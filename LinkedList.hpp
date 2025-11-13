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
		while (stepper) {
			std::cout << stepper->data << std::endl;
			stepper = stepper->next;
		}
	}
	void printReverse() const {
		Node* stepper = tail;
		while (stepper) {
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
	/*
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
	*/
	void addHead(const T& data) {
		if (count == 0) {
			head = new Node;
			head->prev = nullptr;
			head->next = nullptr;
			tail = head;
			head->data = data;
			count++;
		}
		else {
			Node* newHead = new Node;
			newHead->data = data;
			head->prev = newHead;
			newHead->prev = nullptr;
			newHead->next = head;
			head = newHead;
			count++;
		}
	}
	void addTail(const T& data) {
		if (count == 0) {
			tail = new Node;
			tail->next = nullptr;
			tail->prev = nullptr;
			head = tail;
			tail->data = data;
			count++;
		}
		else {
			Node* newTail = new Node;
			newTail->data = data;
			tail->next = newTail;
			newTail->next = nullptr;
			newTail->prev = tail;
			tail = newTail;
			count++;
		}
	}



	// Removal
	bool removeHead() {
		if (count == 0) return false;
		if (head && count == 1) {
			tail = nullptr;
			delete head;
			head = nullptr;
			count--;
			return true;
		}
		Node* newTemp = head->next;
		newTemp->prev = nullptr;
		delete head;
		head = newTemp;
		count--;
		return true;
	}
	bool removeTail() {
		if (count == 0) return false;
		if (tail && count == 1) {
			head = nullptr;
			delete tail;
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
		count = 0;
	}
	// Operators: move and copy
	LinkedList& operator=(LinkedList&& other) noexcept {
		if (this == &other) return *this;
		head = other.head;
		tail = other.tail;
		count = other.count;
		// prevent memleaks
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
		return *this;
	}

	LinkedList& operator=(const LinkedList& rhs) {
		// setup and destruction of what was previously held by this
		if (this == &rhs) return *this;
		clear();
		head = nullptr;
		tail = nullptr;
		count = 0;

		// coppying over the data
		Node* stepper = rhs.head;
		while (stepper != nullptr){
			addTail(stepper->data);
			stepper = stepper->next;
		}
		count = rhs.count;
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

	LinkedList(const LinkedList& list) { // copy constructor
		head = nullptr;
		tail = nullptr;
		count = 0;

		Node* temp = list.head;
		while (temp != nullptr) {
			addTail(temp->data);
			temp = temp->next;
		}

		count = list.count;
	}
	LinkedList(LinkedList&& other) noexcept { // move con
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
