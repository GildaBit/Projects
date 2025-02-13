#include <iostream>

using namespace std;

//Data Class: This is what goes inside your Node
class Process {
public:
    string processName;
    int totalTime;
    Process (string processName, int totalTime){
        //Fill contructor here
        this->processName = processName;
        this->totalTime = totalTime;
    }
    void updateRunTime(int quantumCycle) {
        //write method to update totalTime after each quantum cycle.
        totalTime-=quantumCycle;
    }
    void print () {
        //write print method to print the name of the process and the time left
        std::cout << "process " << processName << ": " << totalTime << " seconds";
    }
};

// Node Class: Node for the DoublyLinkedList
template <typename T> class Node {
public:
    T *data;
    Node<T> *next;
    Node<T> *prev;
    Node (T *data) {
        this->data = data;
        next = nullptr;
        prev = nullptr;
    }
    void print () {
        data->print ();
    }
};

//CircularDoublyLinkedList Class: Container for Nodes
template <typename T> class CircularDLL {
private:
    Node<T> *curr;
    int length;
public:
    Node<T> *head;
    // Constructor
    CircularDLL(T *data) {
        //Write constructor for the DLL here
        head = new Node<T>(data);
        head->next = head;
        head->prev = head;
        curr = head;
        length = 1;
    }

    //Destructor
    ~CircularDLL() {
        //Write code for destructor here
        Node<T> *temp = head;
        while(head!=nullptr) {
            head = head->next;
            delete temp;
            temp = head;
            length--;
        }
    }

    void printList() {
        //Write code to print the list here.
        if(isEmpty()) {
            return;
        }
        int counter = 1;
        std::cout<< counter << ". ";
        head->print();
        std::cout<<std::endl;
        Node<T> *temp = head->next;
        while(temp != head) {
            counter++;
            std::cout<< counter << ". ";
            temp->print();
            std::cout<<std::endl;
            temp = temp->next;
        }
    }

    //Insert a process
    void insertProcess(T *data) {
        //write code to insert process here
        if(length == 0) {
            head = new Node<T>(data);
            head->next = head;
            head->prev = head;
            curr = head;
            length = 1;
        } else if(length == 1) {
            head->next = new Node<T>(data);
            head->prev = head->next;
            curr = head->next;
            curr->prev = head;
            curr->next = head;
            length = 2;
        } else {
            curr->next = new Node<T>(data);
            curr->next->prev = curr;
            curr->next->next = head;
            curr = curr->next;
            head->prev = curr;
            length++;
        }
    }

    //Delete a Process
    void deleteProcess(T *data) {
        //write code to delete process here
        if(length == 1) {
            if(head->data == data) {
                delete head;
                length = 0;
            }
        } else {
            Node<T> *temp = head;
            do {
                Node<T> *temp2 = temp->next;
                if(temp->data == data) {
                        temp->prev->next = temp->next;
                        temp->next->prev = temp->prev;
                        delete temp;
                        length--;
                        return;
                }
                temp = temp2;
            } while(temp != head);
        }
    }

    bool isEmpty() {
        if(length==0) {
            return true;
        }
        return false;
    }
};

int main() {
    int quantumTime;
    std::cout<<"enter a quantum time: ";
    cin>>quantumTime;
    std::cout<<"Populating with processes" << std::endl << std::endl;
    Process *p1 = new Process("A", 10);
    Process *p2 = new Process("B", 12);
    Process *p3 = new Process("C", 8);
    Process *p4 = new Process("D", 5);
    Process *p5 = new Process("E", 10);
    CircularDLL<Process> *list = new CircularDLL<Process>(p1);
    list->insertProcess(p2);
    list->insertProcess(p3);
    list->insertProcess(p4);
    list->insertProcess(p5);
    list->printList();
    int counter = 1;
    while(!list->isEmpty()) {
        char choice = 'Y';
        while(choice != 'N') {
            std::cout<<"Add a new process? (enter Y/N)";
            std::cin >> choice;
            std::cout << endl;
            if(choice == 'Y') {
                string name;
                int processTime;
                std::cout << "Enter new process name: ";
                std::cin >> name;
                std::cout << "Enter total process time: ";
                std::cin >> processTime;
                list->insertProcess(new Process(name, processTime));
                std::cout << "Process added." << std::endl << std::endl;
            }
        }
        cout << "Running cycle " << counter << endl;
        cout << "After cycle " << counter << " - " << counter*quantumTime << " second elapses - state of processes is as follows: " << endl << endl;
        counter++;
        if(!(list->isEmpty())) {
            Node<Process> *temp = list->head;
            do {
                temp->data->updateRunTime(quantumTime);
                temp = temp->next;
            } while(temp != list->head);
            temp = list->head;
            int c = 0;
            do {
                c++;
                Node<Process> *temp2 = temp->next;
                if(temp->data->totalTime <= 0) {
                    if(temp == list->head) {
                        list->head = list->head->next;
                        c=0;
                    }
                    list->deleteProcess(temp->data);

                }
                temp = temp2;

            } while((temp != list->head || c==0) &&!(list->isEmpty()));
            list->printList();
        }
    }
    std::cout << "All processes are completed.";
    return 0;
}