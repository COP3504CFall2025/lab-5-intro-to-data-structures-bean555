// main.cpp: Leave IFDEF guards; compile locally with flag -DMAIN.
#ifdef MAIN

#include "ABDQ.hpp"
#include "ABQ.hpp"
#include "ABS.hpp"
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include "LLDQ.hpp"
#include "LLQ.hpp"
#include "LLS.hpp"
#include <iostream>

template<typename T>
void printData(T* arr, size_t currentSize);
void testLinkedList();
void testABS();
void testABQ();
void testLLS();
void testLLQ();
void testLLDQ();
void testABDQ();

int main() {

    // Testing files:
    std::cout << "testing LinkedList" << std::endl;
    testLinkedList();
    //testABS();
    //testABQ();
    std::cout << "testing LLS" << std::endl;
    testLLS();
    std::cout << "testing LLQ" << std::endl;
    testLLQ();
    std::cout << "testing LLDQ" << std::endl;
    testLLDQ();
    //testABDQ();

    return 0;
}

template<typename T>
void printData(T* arr, size_t currentSize) {
    for (size_t i = 0; i < currentSize; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void testLinkedList() {
    // Testing LinkedList class implementation
    // Creating and filling list 1 (testing default constructor, addTail()
    std::cout << "\nCreating & filling list 1." << std::endl;
    LinkedList<int> list1;
    for (int i = 0; i < 5; i ++) {
        list1.addTail(i);
    }
    // Test accessors: getHead(), getTail()
    std::cout << "Head of list 1: " << list1.getHead() << std::endl;
    std::cout << "Tail of list 1: " << list1.getTail() << std::endl;
    // Printing list 1 forwards and backwards
    std::cout << "Printing list 1 forwards: " << std::endl;
    list1.printForward();
    std::cout << "Printing list 1 backwards: " << std::endl;
    list1.printReverse();
    std::cout << "List 1 node count: " << list1.getCount() << std::endl << std::endl;

    // Testing copy constructor
    std::cout << "Creating list 2: copying list 1." << std::endl;
    LinkedList<int> list2(list1);
    std::cout << "List 2 node count: " << list2.getCount() << std::endl << std::endl;
    std::cout << "Printing list 2 forwards: " << std::endl;
    list2.printForward();
    std::cout << "List 2 node count: " << list2.getCount() << std::endl << std::endl;

    // Testing addHead(), removeHead(), removeTail()
    std::cout << "Adding -1, -2 to the front of list 2:" << std::endl;
    list2.addHead(-1);
    list2.addHead(-2);
    std::cout << "Printing list 2 forwards: " << std::endl;
    list2.printForward();
    std::cout << "Removing the front of list 2:" << std::endl;
    list2.removeHead();
    std::cout << "Printing list 2 forwards: " << std::endl;
    list2.printForward();
    std::cout << "Removing the end 2 items of list 2:" << std::endl;
    list2.removeTail();
    list2.removeTail();
    std::cout << "Printing list 2 forwards: " << std::endl;
    list2.printForward();

    // Test: Move constructor
    std::cout << "Creating list 3: move constructing from list 2." << std::endl;
    LinkedList<int> list3(std::move(list2));
    std::cout << "List 3 node count: " << list3.getCount() << std::endl << std::endl;
    std::cout << "Printing list 3 forwards: " << std::endl;
    list3.printForward();
    std::cout << "List 3 node count: " << list3.getCount() << std::endl << std::endl;
    std::cout << "Printing (now-empty) list 2 forwards: " << std::endl;
    list2.printForward();
    std::cout << "List 2 node count: " << list2.getCount() << std::endl << std::endl;

    // Test: Move assignment
    std::cout << "Assigning list 1: moving list 3 contents." << std::endl;
    list1 = std::move(list3);
    std::cout << "Printing list 1 forwards: " << std::endl;
    list1.printForward();
    std::cout << "Printing (now-empty) list 3 forwards: " << std::endl;
    list3.printForward();
    std::cout << "List 3 node count: " << list3.getCount() << std::endl << std::endl;

    // Test: Copy assignment
    std::cout << "\nCreating & filling list 4." << std::endl;
    LinkedList<int> list4;
    for (int i = 10; i < 50; i+=10) {
        list4.addTail(i);
    }
    std::cout << "Printing list 4 forwards: " << std::endl;
    list4.printForward();
    std::cout << "Copy assigning list 1 list 4's contents." << std::endl;
    list1 = list4;
    std::cout << "Printing list 1 forwards: " << std::endl;
    list1.printForward();

    // Clearing lists
    std::cout << "\nClearing list 1." << std::endl;
    list1.clear();
    std::cout << "Printing empty list 1: " << std::endl;
    list1.printForward();
    std::cout << "List 1 node count: " << list1.getCount() << std::endl;
    std::cout << "Clearing list 2." << std::endl;
    list2.clear();
    std::cout << "Printing empty list 2: " << std::endl;
    list2.printForward();
    std::cout << "List 2 node count: " << list2.getCount() << std::endl << std::endl;
    std::cout << "Clearing list 3." << std::endl;
    list3.clear();
    std::cout << "Clearing list 4." << std::endl;
    list4.clear();
}
/*
void testABS() {
    // Testing ABS class implementation
    // Pushing, popping, peeping, getters
    std::cout << "Constructing & filling ABS 1." << std::endl;
    ABS<int> arrayBasedStack1;
    for (size_t i = 0; i < 3; ++i) {
        arrayBasedStack1.push(static_cast<int>(i));
        std::cout << "Peeking at ABS 1: " << arrayBasedStack1.peek() << std::endl;
    }
    std::cout << "Size of ABS 1: " << arrayBasedStack1.getSize() << std::endl;
    std::cout << "Capacity of ABS 1: " << arrayBasedStack1.getMaxCapacity() << std::endl;
    std::cout << "\nAdding elements: " << std::endl;
    for (size_t i = 3; i < 6; ++i) {
        arrayBasedStack1.push(static_cast<int>(i));
        std::cout << "Peeking at ABS 1: " << arrayBasedStack1.peek() << std::endl;
    }
    std::cout << "Size of ABS 1: " << arrayBasedStack1.getSize() << std::endl;
    std::cout << "Capacity of ABS 1: " << arrayBasedStack1.getMaxCapacity() << std::endl;
    std::cout << "\nPopping elements: " << std::endl;
    std::cout << "Removed from ABS 1: " << arrayBasedStack1.pop() << std::endl;
    std::cout << "Removed from ABS 1: " << arrayBasedStack1.pop() << std::endl;
    std::cout << "Removed from ABS 1: " << arrayBasedStack1.pop() << std::endl;
    std::cout << "Removed from ABS 1: " << arrayBasedStack1.pop() << std::endl;
    std::cout << "Peeking at ABS 1: " << arrayBasedStack1.peek() << std::endl;
    std::cout << "Size of ABS 1: " << arrayBasedStack1.getSize() << std::endl;
    std::cout << "Capacity of ABS 1: " << arrayBasedStack1.getMaxCapacity() << std::endl;
    std::cout << "\nData pointer for ABS 1: " << arrayBasedStack1.getData() << std::endl;

    // Big 5 testing
    std::cout << "Copy constructing ABS 2 from ABS 1." << std::endl;
    ABS<int> arrayBasedStack2 = arrayBasedStack1;
    printData<int>(arrayBasedStack2.getData(), arrayBasedStack2.getSize());
    std::cout << "Popping element from ABS 2." << std::endl;
    arrayBasedStack2.pop();
    printData<int>(arrayBasedStack2.getData(), arrayBasedStack2.getSize());
    std::cout << "Move constructing ABS 3 from ABS 2." << std::endl;
    ABS<int> arrayBasedStack3 = std::move(arrayBasedStack2);
    printData<int>(arrayBasedStack3.getData(), arrayBasedStack3.getSize());
    std::cout << "Copy assigning ABS 2 from ABS 1." << std::endl;
    arrayBasedStack2 = arrayBasedStack1;
    printData<int>(arrayBasedStack2.getData(), arrayBasedStack2.getSize());
    std::cout << "Pushing to ABS 2." << std::endl;
    arrayBasedStack2.push(5);
    printData<int>(arrayBasedStack2.getData(), arrayBasedStack2.getSize());
    std::cout << "Move assigning ABS 1 from ABS 2." << std::endl;
    arrayBasedStack1 = std::move(arrayBasedStack2);
    printData<int>(arrayBasedStack1.getData(), arrayBasedStack1.getSize());
}

void testABQ() { // Peek has issue?
    // Testing ABQ class implementation
    // Enqueue, dequeue, peeping, getters
    std::cout << "Constructing & filling ABQ 1." << std::endl;
    ABQ<int> arrayBasedQueue1;
    for (size_t i = 0; i < 3; ++i) {
        arrayBasedQueue1.enqueue(static_cast<int>(i));
    }
    printData<int>(arrayBasedQueue1.getData(), arrayBasedQueue1.getSize());

    std::cout << "Size of ABQ 1: " << arrayBasedQueue1.getSize() << std::endl;
    std::cout << "Capacity of ABQ 1: " << arrayBasedQueue1.getMaxCapacity() << std::endl;
    std::cout << "\nAdding elements: " << std::endl;
    for (size_t i = 3; i < 6; ++i) {
        arrayBasedQueue1.enqueue(static_cast<int>(i));
    }
    printData<int>(arrayBasedQueue1.getData(), arrayBasedQueue1.getSize());
    std::cout << "Size of ABQ 1: " << arrayBasedQueue1.getSize() << std::endl;
    std::cout << "Capacity of ABQ 1: " << arrayBasedQueue1.getMaxCapacity() << std::endl;
    std::cout << "\nPopping elements: " << std::endl;
    std::cout << "Removed from ABQ 1: " << arrayBasedQueue1.dequeue() << std::endl;
    std::cout << "Removed from ABQ 1: " << arrayBasedQueue1.dequeue() << std::endl;
    std::cout << "Removed from ABQ 1: " << arrayBasedQueue1.dequeue() << std::endl;
    std::cout << "Removed from ABQ 1: " << arrayBasedQueue1.dequeue() << std::endl;
    // Peeking returning wrong element
    std::cout << "Peeking at ABQ 1: " << arrayBasedQueue1.peek() << std::endl;
    std::cout << "Size of ABQ 1: " << arrayBasedQueue1.getSize() << std::endl;
    std::cout << "Capacity of ABQ 1: " << arrayBasedQueue1.getMaxCapacity() << std::endl;

    std::cout << "\nData pointer for ABQ 1: " << arrayBasedQueue1.getData() << std::endl;


    // Big 5 testing
    for (size_t i = 10; i < 50; i+=10) {
        arrayBasedQueue1.enqueue(static_cast<int>(i));
    }
    std::cout << "Copy constructing ABQ 2 from ABQ 1." << std::endl;
    ABQ<int> arrayBasedQueue2 = arrayBasedQueue1;
    printData<int>(arrayBasedQueue2.getData(), arrayBasedQueue2.getSize());
    std::cout << "Move constructing ABQ 3 from ABQ 2." << std::endl;
    ABQ<int> arrayBasedQueue3 = std::move(arrayBasedQueue2);
    printData<int>(arrayBasedQueue3.getData(), arrayBasedQueue3.getSize());
    std::cout << "Copy assigning ABQ 2 from ABQ 1." << std::endl;
    arrayBasedQueue2 = arrayBasedQueue1;
    printData<int>(arrayBasedQueue2.getData(), arrayBasedQueue2.getSize());
    std::cout << "Move assigning ABQ 1 from ABQ 2." << std::endl;
    arrayBasedQueue1 = std::move(arrayBasedQueue2);
    printData<int>(arrayBasedQueue1.getData(), arrayBasedQueue1.getSize());
}
*/
void testLLS() {
    // Testing LLS class implementation
    // Pushing, popping, peeping, getters
    std::cout << "Constructing & filling LLS 1." << std::endl;
    LLS<int> linkedListStack1;
    for (size_t i = 0; i < 5; ++i) {
        linkedListStack1.push(static_cast<int>(i));
        std::cout << "Peeking at LLS 1: " << linkedListStack1.peek() << std::endl;
    }
    std::cout << "Size of LLS 1: " << linkedListStack1.getSize() << std::endl;
    std::cout << "\nPopping elements: " << std::endl;
    std::cout << "Removed from LLS 1: " << linkedListStack1.pop() << std::endl;
    std::cout << "Removed from LLS 1: " << linkedListStack1.pop() << std::endl;
    std::cout << "Peeking at LLS 1: " << linkedListStack1.peek() << std::endl;
    std::cout << "Size of LLS 1: " << linkedListStack1.getSize() << std::endl;

    // Big 5 testing
    std::cout << "\nCopy constructing LLS 2 from LLS 1." << std::endl;
    LLS<int> linkedListStack2 = linkedListStack1;
    std::cout << "Popping element from LLS 2." << std::endl;
    linkedListStack2.pop();
    std::cout << "Move constructing LLS 3 from LLS 2." << std::endl;
    LLS<int> linkedListStack3 = std::move(linkedListStack2);
    std::cout << "Copy assigning LLS 2 from LLS 1." << std::endl;
    linkedListStack2 = linkedListStack1;
    std::cout << "Pushing to LLS 2." << std::endl;
    linkedListStack2.push(5);
    std::cout << "Move assigning LLS 1 from LLS 2." << std::endl;
    linkedListStack1 = std::move(linkedListStack2);
}

void testLLQ() {
    // Testing LLQ class implementation
    // Enqueue, dequeue, peeping, getters
    std::cout << "Constructing & filling LLQ 1." << std::endl;
    LLQ<int> linkedListQueue1;
    for (size_t i = 0; i < 5; ++i) {
        linkedListQueue1.enqueue(static_cast<int>(i));
    }
    std::cout << "Size of LLQ 1: " << linkedListQueue1.getSize() << std::endl;
    std::cout << "\nPopping elements: " << std::endl;
    std::cout << "Removed from LLQ 1: " << linkedListQueue1.dequeue() << std::endl;
    std::cout << "Removed from LLQ 1: " << linkedListQueue1.dequeue() << std::endl;
    std::cout << "Peeking at LLQ 1: " << linkedListQueue1.peek() << std::endl;
    std::cout << "Size of LLQ 1: " << linkedListQueue1.getSize() << std::endl;

    // Big 5 testing
    std::cout << "\nCopy constructing LLQ 2 from LLQ 1." << std::endl;
    LLQ<int> linkedListQueue2 = linkedListQueue1;
    std::cout << "Popping element from LLQ 2." << std::endl;
    linkedListQueue2.dequeue();
    std::cout << "Move constructing LLQ 3 from LLQ 2." << std::endl;
    LLQ<int> linkedListQueue3 = std::move(linkedListQueue2);
    std::cout << "Copy assigning LLQ 2 from LLQ 1." << std::endl;
    linkedListQueue2 = linkedListQueue1;
    std::cout << "Pushing to LLQ 2." << std::endl;
    linkedListQueue2.dequeue();
    std::cout << "Move assigning LLQ 1 from LLQ 2." << std::endl;
    linkedListQueue1 = std::move(linkedListQueue2);
}

void testLLDQ() {
    // Testing LLDQ class implementation
    // pushFront, pushBack, popFront, popBack, front, back, getter
    std::cout << "Constructing & filling LLDQ 1 from the front." << std::endl;
    LLDQ<int> linkedListDeque1;
    for (size_t i = 0; i < 5; ++i) {
        linkedListDeque1.pushFront(static_cast<int>(i));
        std::cout << "Peeking at LLDQ 1 front: " << linkedListDeque1.front() << std::endl;
    }
    std::cout << "Size of LLDQ 1: " << linkedListDeque1.getSize() << std::endl;
    std::cout << "\nPopping elements from the front: " << std::endl;
    std::cout << "Removed from LLDQ 1: " << linkedListDeque1.popFront() << std::endl;
    std::cout << "Removed from LLDQ 1: " << linkedListDeque1.popFront() << std::endl;
    std::cout << "Peeking at LLDQ 1 front: " << linkedListDeque1.front() << std::endl;
    std::cout << "Size of LLDQ 1: " << linkedListDeque1.getSize() << std::endl;
    std::cout << "\nConstructing & filling LLDQ 2 from the back." << std::endl;
    LLDQ<int> linkedListDeque2;
    for (size_t i = 0; i < 5; ++i) {
        linkedListDeque2.pushBack(static_cast<int>(i));
        std::cout << "Peeking at LLDQ 2 back: " << linkedListDeque2.back() << std::endl;
    }
    std::cout << "Size of LLDQ 2: " << linkedListDeque2.getSize() << std::endl;
    std::cout << "\nPopping elements from the back: " << std::endl;
    std::cout << "Removed from LLDQ 2: " << linkedListDeque2.popBack() << std::endl;
    std::cout << "Removed from LLDQ 2: " << linkedListDeque2.popBack() << std::endl;
    std::cout << "Peeking at LLDQ 2 back: " << linkedListDeque2.back() << std::endl;
    std::cout << "Size of LLDQ 2: " << linkedListDeque2.getSize() << std::endl;

    // Big 5 testing
    std::cout << "\nCopy constructing LLDQ 3 from LLDQ 1." << std::endl;
    LLDQ<int> linkedListDeque3 = linkedListDeque1;
    std::cout << "Popping element from back of LLDQ 2." << std::endl;
    linkedListDeque3.popBack();
    std::cout << "Move constructing LLDQ 4 from LLDQ 2." << std::endl;
    LLDQ<int> linkedListDeque4 = std::move(linkedListDeque2);
    std::cout << "Copy assigning LLDQ 2 from LLDQ 1." << std::endl;
    linkedListDeque2 = linkedListDeque1;
    std::cout << "Pushing 5 to front of LLDQ 2." << std::endl;
    linkedListDeque2.pushFront(5);
    std::cout << "Move assigning LLDQ 1 from LLDQ 2." << std::endl;
    linkedListDeque1 = std::move(linkedListDeque2);
}
/*
void testABDQ() {
    // Testing ABDQ class implementation
    // Pushing front/back, accessing front/back, ensureCapacity, shrinkIfNeeded, getSize
    std::cout << "Constructing & filling ABDQ 1 from the front." << std::endl;
    ABDQ<int> arrayBasedDeque1;
    for (size_t i = 0; i < 5; ++i) {
        arrayBasedDeque1.pushFront(static_cast<int>(i));
        std::cout << "Peeking at ABDQ 1 front: " << arrayBasedDeque1.front() << std::endl;
    }
    std::cout << "Size of ABDQ 1: " << arrayBasedDeque1.getSize() << std::endl;
    std::cout << "Capacity of ABDQ 1: " << arrayBasedDeque1.getCapacity() << std::endl;
    std::cout << "\nPopping elements from the front: " << std::endl;
    std::cout << "Removed from ABDQ 1: " << arrayBasedDeque1.popFront() << std::endl;
    std::cout << "Removed from ABDQ 1: " << arrayBasedDeque1.popFront() << std::endl;
    std::cout << "Peeking at ABDQ 1 front: " << arrayBasedDeque1.front() << std::endl;
    std::cout << "Size of ABDQ 1: " << arrayBasedDeque1.getSize() << std::endl;
    std::cout << "Capacity of ABDQ 1: " << arrayBasedDeque1.getCapacity() << std::endl;
    std::cout << "\nConstructing & filling ABDQ 2 from the back." << std::endl;
    ABDQ<int> arrayBasedDeque2;
    for (size_t i = 0; i < 10; ++i) {
        arrayBasedDeque2.pushBack(static_cast<int>(i));
        std::cout << "Peeking at ABDQ 2 back: " << arrayBasedDeque2.back() << std::endl;
    }
    std::cout << "Size of ABDQ 2: " << arrayBasedDeque2.getSize() << std::endl;
    std::cout << "Capacity of ABDQ 2: " << arrayBasedDeque2.getCapacity() << std::endl;
    std::cout << "\nPopping elements from the back: " << std::endl;
    std::cout << "Removed from ABDQ 2: " << arrayBasedDeque2.popBack() << " " << arrayBasedDeque2.popBack() << " " << arrayBasedDeque2.popBack() << " " << arrayBasedDeque2.popBack() << " " << arrayBasedDeque2.popBack() << " " << arrayBasedDeque2.popBack() << " " << std::endl;
    std::cout << "Size of ABDQ 2: " << arrayBasedDeque2.getSize() << std::endl;
    arrayBasedDeque2.shrinkIfNeeded();
    std::cout << "Shrinking ABDQ 2 if needed, capacity: " << arrayBasedDeque2.getCapacity() << std::endl;
    arrayBasedDeque2.ensureCapacity();
    std::cout << "Ensuring capacity of ABDQ 2, capacity: " << arrayBasedDeque2.getCapacity() << std::endl;

    // Big 5 testing
    std::cout << "\nCopy constructing ABDQ 3 from ABDQ 1." << std::endl;
    ABDQ<int> arrayBasedDeque3 = arrayBasedDeque1;
    std::cout << "Popping element from back of ABDQ 2." << std::endl;
    arrayBasedDeque3.popBack();
    std::cout << "Move constructing ABDQ 4 from ABDQ 2." << std::endl;
    ABDQ<int> arrayBasedDeque4 = std::move(arrayBasedDeque2);
    std::cout << "Copy assigning ABDQ 2 from ABDQ 1." << std::endl;
    arrayBasedDeque2 = arrayBasedDeque1;
    std::cout << "Pushing 5 to front of ABDQ 2." << std::endl;
    arrayBasedDeque2.pushFront(5);
    std::cout << "Move assigning ABDQ 1 from ABDQ 2." << std::endl;
    arrayBasedDeque1 = std::move(arrayBasedDeque2);
}
*/
#endif