#include "SpaceRoute.h"


template <typename T>
SpaceRoute<T>::SpaceRoute() { // Constructor with default setup
    head = NULL;
    tail = NULL;
}

template <typename T>
SpaceRoute<T>::~SpaceRoute() {  // Destructor deleting nodes
    Node<T> * current = head;
    while (current) {
        Node<T> * next = current -> next;
        delete current;
        current = next;
    }
    head = NULL;
    tail = NULL;
}
template <typename T>
void SpaceRoute<T>::addWaypointAtBeginning(T& data) {
    Node<T> * newNode = new Node<T>(data);
    if (head == NULL) {
        head = tail = newNode;
    } else {
        newNode -> next = head;
        head -> prev = newNode;
        head = newNode;
    }
}

template <typename T>
void SpaceRoute<T>::addWaypointAtEnd(T& data) {
    Node<T> * newNode = new Node<T>(data);
    if (tail == NULL) {
        head = tail = newNode;
    } else {
        tail -> next = newNode;
        newNode -> prev = tail;
        tail = newNode;
    }
}

template <typename T>
void SpaceRoute<T>::addWaypointAtIndex(int index, T& data) {
    if (index == 0) {
        addWaypointAtBeginning(data);
        return;
    }
    Node<T> * current = head;
    int num = 0;
    while (current && num < index) {
        current = current -> next;
        num++;
    }
    if (!current) {
        addWaypointAtEnd(data);
    } else {
        Node<T> * newNode = new Node<T>(data);
        newNode -> next = current;
        newNode -> prev = current -> prev;
        if (current -> prev) {
            current -> prev -> next = newNode;
        } else {
            head = newNode;
        }
        current -> prev = newNode;
    }
}

template <typename T>
void SpaceRoute<T>::removeWaypointAtBeginning() {
    // checks if head is null
    if (!head) {
        return;
    }
    // creating temporary variable
    Node<T> * current = head;
    // setting to the next node
    head = head -> next;
    if (head) {
        head -> prev = NULL;
    } else {
        tail = NULL;
    }
    delete current;
}

template <typename T>
void SpaceRoute<T>::removeWaypointAtEnd() {
    if (!tail) {
        return;
    }
    Node<T> * current = tail;
    tail = tail -> prev;
    if (tail) {
        tail -> next = NULL;
    } else {
        head = NULL;
    }
    delete current;
}

template <typename T>
void SpaceRoute<T>::removeWaypointAtIndex(int index) {
    if (index == 0) {
        removeWaypointAtBeginning();
        return;
    }
    Node<T> * current = head;
    int num = 0;
    while (current && num < index) {
        current = current -> next;
        num++;
    }
    if (!current) {
        return;
    }
    if (current -> prev) {
        current -> prev -> next = current -> next;
    }
    if (current -> next) {
        current -> next -> prev = current -> prev;
    } else {
        tail = current -> prev;
    }
    delete current;
}

template <typename T>
void SpaceRoute<T>::traverseForward() {
    Node<T> * current = head;
    while (current) {
        current -> print();
        current = current -> next;
    }
    cout << endl;
}

template <typename T>
void SpaceRoute<T>::traverseBackward() {
    Node<T> * current = tail;
    while (current) {
        current -> print();
        current = current -> prev;
    }
    cout << endl;
}

template <typename T>
Node<T>* SpaceRoute<T>::getWaypoint(int index) {
    Node<T> * current = head;
    int currentIndex = 0;
    while (current != NULL && currentIndex < index) {
        current = current->next;
        currentIndex++;
    }
    return current;
}

template <typename T>
void SpaceRoute<T>::setWaypoint(int index, T& data) {
    Node<T> * current = getWaypoint(index);
    if (current != NULL) {
        current->data = data;
    }
}

