#include <iostream>
#include <string>
using namespace std;

template <typename T>
class Node {
public:
    T& data;
    Node* next;
    Node* prev;

    Node(T& d) : data(d), next(nullptr), prev(nullptr) {}
    void print() { cout << data << " "; }
};

class CelestialNode {
private:
    string name;
    double distance_from_earth;
    string mission_log;

public:
    CelestialNode(const string& n, double d, const string& log);
    const string& getName() const;
    double getDistance() const;
    const string& getMissionLog() const;
    void print() const { cout << name << " (" << distance_from_earth << " AU) - " << mission_log << endl; }
};

template <typename T>
class SpaceRoute {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    SpaceRoute() {
        head = NULL;
        tail = NULL;
    }// Constructor
    ~SpaceRoute() {
        Node<T> * current = head;
        while (current) {
            Node<T> * next = current -> next;
            delete current;
            current = next;
        }
        head = NULL;
        tail = NULL;
    }// Destructor

    void addWaypointAtBeginning(T& data) {
        Node<T> * newNode = new Node<T>(data);
        if (head != NULL) {
            head = tail = newNode;
        } else {
            newNode -> next = head;
            head -> prev = newNode;
            head = newNode;
        }
    }

    void addWaypointAtEnd(T& data) {
        Node<T> * newNode = new Node<T>(data);
        if (tail != NULL) {
            head = tail = newNode;
        } else {
            tail -> next = newNode;
            newNode -> prev = tail;
            tail = newNode;
        }
    }

    void addWaypointAtIndex(int index, T& data) {
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
            newNode -> next = current -> next;
            newNode -> prev = current;
            if (current -> next) {
                current -> next -> prev = newNode;
            } else {
                tail = newNode;
            }
            current -> next = newNode;
        }
    }

    void removeWaypointAtBeginning() {
        if (!head) {
            return;
        }
        Node<T> * current = head;
        head = head -> next;
        if (head) {
            head -> prev = NULL;
        } else {
            tail = NULL;
        }
        delete current;
    }

    void removeWaypointAtEnd() {
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

    void removeWaypointAtIndex(int index) {
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

    void traverseForward() {
        Node<T> * current = head;
        while (current) {
            cout << current -> data;
            current = current -> next;
        }
        cout << endl;
    }

    void traverseBackward() {
        Node<T> * current = tail;
        while (current) {
            cout << current -> data;
            current = current -> prev;
        }
        cout << endl;
    }

    Node<T>* getWaypoint(int index) {
        Node<T> * current = head;
        int currentIndex = 0;
        while (current != NULL && currentIndex < index) {
            current = current->next;
            currentIndex++;
        }
        return current;
    }

    void setWaypoint(int index, T& data) {
        Node<T> * current = getWaypoint(index);
        if (current != NULL) {
            current->data = data;
        }
    }

    void print(){

        Node<T>* current = head;
        while (current) {
            current->print();
            current = current->next;
        }
        cout << endl;
    }

};