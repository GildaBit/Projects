#include <iostream>

using namespace std;

// Data Class : Holds all the data that goes inside the Node
class Data {
public:
    int value;
    string name;
    Data(int value, string name) {
        this->value = value;
        this->name = name;
    }
    void print() {

        cout << value << " " << endl;
        cout << name << " " << endl;
    }
};

// Node Class : Node for the LinkedList
template <typename T> class Node {
public:
    T *value;
    /* star in front of variable name is to store a pointer: *;
     * ampersand in front of variable name is to get address from value: &;
     * */
    Node<T> *next;

    Node(T *value) { //new keyword calls constructor
        this->value = value;
        next = nullptr;
    }
    void print() { value->print(); }
};

//LinkedList Class : Container for Nodes
template <typename T> class LinkedList {
private:
    Node<T> *head;
    Node<T> *tail;
    int length;

public:
// Constructor
    LinkedList(T *value) {
        Node<T> *newNode = new Node<T>(value);
        head = newNode;
        tail = newNode;
        length = 1;
    }

//Destructor
    ~LinkedList() { // ~ + name of class to call destructor
    //Destructor gets rid of memory space you create since C++ doesn't
    //have an automated garbage collector
        Node<T> *temp = head;
        while (head) {
            head = head->next;
            delete temp; //delete keyword gets rid of the node that is currently the head
            temp = head;
        }
    }

    void printList() {
        Node<T> *temp = head;
        while (temp != nullptr) {
            temp->print();
            temp = temp->next;
        }
    }

//get and set
    Node<T>* getHead() {
        if (head == nullptr) {
            cout << "Head: nullptr" << endl;
        } else {
            cout << "Head: " << head->value << endl;
        }
        return head;
    }

    Node<T>* getTail() {
        if (tail == nullptr) {
            cout << "Tail: nullptr" << endl;
        } else {
            cout << "Tail: " << tail->value << endl;
        }
        return tail;
    }

    int getLength() { cout << "Length: " << length << endl; return length;}

    Node<T> *get(int index) {
        if (index < 0 || index >= length)
            return nullptr;
        Node<T> *temp = head;
        for (int i = 0; i < index; ++i) {
            temp = temp->next;
        }
        return temp;
    }

    bool set(int index, T *value) {
        Node<T> *temp = get(index);
        if (temp) {
            temp->value = value;
            return true;
        }
        return false;
    }

//All insert methods
//Insert at end
    void append(T *value) {
        Node<T> *newNode = new Node<T>(value);
        if (length == 0) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        length++;
    }

//Insert at beginning

    void prepend(T *value) {
        Node<T> *newNode = new Node<T>(value);
        if (length == 0) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        length++;
    }

//Insert at Index

    bool insert(int index, T *value) {
        if (index < 0 || index > length)
            return false;
        if (index == 0) {
            prepend(value);
            return true;
        }
        if (index == length) {
            append(value);
            return true;
        }
        Node<T> *newNode = new Node<T>(value);
        Node<T> *temp = get(index - 1);
        newNode->next = temp->next;
        temp->next = newNode;
        length++;
        return true;
    }

//All delete Methods
//Delete Tail

    void deleteLast() {
        if (length == 0)
            return;
        Node<T> *temp = head;
        if (length == 1) {
            head = nullptr;
            tail = nullptr;
        } else {
            Node<T> *pre = head;
            while (temp->next) {
                pre = temp;
                temp = temp->next;
            }
            tail = pre;
            tail->next = nullptr;
        }
        delete temp;
        length--;
    }

//Delete Head

    void deleteFirst() {
        if (length == 0)
            return;
        Node<T> *temp = head;
        if (length == 1) {
            head = nullptr;
            tail = nullptr;
        } else {
            head = head->next;
        }
        delete temp;
        length--;
    }

//Delete at Index

    void deleteNode(int index) {
        if (index < 0 || index >= length)
            return;
        if (index == 0)
            return deleteFirst();
        if (index == length - 1)
            return deleteLast();

        Node<T> *prev = get(index - 1);
        Node<T> *temp = prev->next;

        prev->next = temp->next;
        delete temp;
        length--;
    }
};

//Main Program

int main() {
//creating data object
    Data *d1 = new Data(10, "a");
    // creates a Data pointer that refers to the Data memory
    // slot created with the new keyword referring to the Data class constructor

//Creating Linked List
    LinkedList<Data> *ll1 = new LinkedList<Data>(d1);

//Calling operations on Linked List
    ll1->printList();
    //-> is how a pointer is able to access the methods of the object it points to

    return 0;
}