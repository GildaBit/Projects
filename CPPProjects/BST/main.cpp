#include <iostream>
using namespace std;

class Data {
private:
    int value;
public:
    Data(int v) {
        value = v;
    }
    int getValue() {
        return value;
    }
    void setValue(int v) {
        value = v;
    }

    void print() {
        cout<<value;
    }
};

template <typename T> class Node {
private:
     T *data;
     Node<T>* leftChild;
     Node<T>* rightChild;
     Node<T>* parent;
public:
    Node() {
        data = 0;
        leftChild = nullptr;
        rightChild = nullptr;
        parent = nullptr;
    }
    Node(T* d, Node<T>* l, Node<T>* r, Node<T>* p) {
        data = d;
        leftChild = l;
        rightChild = r;
        parent = p;
    }
    void print() {
        data->print();
    }
    T* getData() {
        return data;
    }
    Node<T>* getRightChild() {
        return rightChild;
    }
    Node<T>* getLeftChild() {
        return leftChild;
    }
    Node<T>* getParent() {
        return parent;
    }
    void setData(T* d) {
        data = d;
    }
    void setRightChild(Node<T>* r) {
        rightChild = r;
    }
    void setLeftChild(Node<T>* l) {
        leftChild = l;
    }
    void setParent(Node<T>* p) {
        parent = p;
    }
};

template <typename T> class BinarySearchTree {
private:
    Node<T>* root;
    int numberOfElements;
    int height;
public:
    BinarySearchTree<T>() {
        root = nullptr;
        numberOfElements = 0;
        height = 0;
    }
    BinarySearchTree<T>(T* r) {
        root = new Node<T>(r, nullptr, nullptr, nullptr);
        numberOfElements = 1;
        height = 1;
    }
    ~BinarySearchTree(){
        clear(root);
        height = 0;
        numberOfElements = 0;
    }
    void clear(Node<T>* n) {
        if(n->getLeftChild() != nullptr) {
            clear(n->getLeftChild());
        }
        if(n->getRightChild() != nullptr) {
            clear(n->getRightChild());
        }
        delete n;
        n = NULL;
    }
    Node<T>* getRoot() {
        return root;
    }
    int getNumberOfElements() {
        return numberOfElements;
    }
    int getHeight() {
        return height;
    }
    void setRoot(Node<T>* r) {
        root = r;
    }
    void setNumberOfElements(int n) {
        numberOfElements = n;
    }
    void setHeight(int h) {
        height = h;
    }

    void print() {
        print(root);
        cout<<endl;
    }

    void print(Node<T>* n) {
        n->print();
        cout<< " ";
        if(n->getLeftChild() != nullptr) {
            print(n->getLeftChild());
        }
        if(n->getRightChild() != nullptr) {
            print(n->getRightChild());
        }
    }

    void insertElement(T* data) {
        if(root->getData() == nullptr) {
            Node<T>* n = new Node<T>(data, nullptr, nullptr, nullptr);
            root = n;
            return;
        }
        Node<T>* curr = root;
        int h = 1;
        while(curr != nullptr) {
            if(data->getValue() < curr->getData()->getValue()) {
                if(curr->getLeftChild() == nullptr) {
                    curr->setLeftChild(new Node<T>(data, nullptr, nullptr, curr));
                    curr->getLeftChild()->setParent(curr);
                    curr = nullptr;
                } else {
                    curr = curr->getLeftChild();
                }
                h++;
            } else if(data->getValue() > curr->getData()->getValue()) {
                if(curr->getRightChild() == nullptr) {
                    curr->setRightChild(new Node<T>(data, nullptr, nullptr, curr));
                    curr->getRightChild()->setParent(curr);
                    curr = nullptr;
                } else {
                    curr = curr->getRightChild();
                }
                h++;
            }
        }
        height = h;
        numberOfElements++;
    }

    void deleteElement(T* data) {
        Node<T>* curr = root;
        while(curr != nullptr) {
            if(curr->getData()->getValue() == data->getValue()) {
                if(curr->getLeftChild() == nullptr && curr->getRightChild() == nullptr) { //no children
                    if(curr->getParent() == nullptr) { //Node is root
                        delete root;
                        curr = nullptr;
                        numberOfElements--;
                    } else if(curr->getParent()->getLeftChild() == curr) {
                        curr->getParent()->setLeftChild(nullptr);
                        delete curr;
                        curr = nullptr;
                        numberOfElements--;
                    } else {
                        curr->getParent()->setRightChild(nullptr);
                        delete curr;
                        curr = nullptr;
                        numberOfElements--;
                    }
                } else if(curr->getRightChild() == nullptr) { //left child exists
                    if(curr->getParent() == nullptr) { //deleting root
                        root = curr->getLeftChild();
                        delete curr;
                        curr = nullptr;
                        numberOfElements--;
                    } else if(curr->getParent()->getLeftChild() == curr) {
                        curr->getParent()->setLeftChild(curr->getLeftChild());
                        curr->getLeftChild()->setParent(curr->getParent());
                        delete curr;
                        curr = nullptr;
                        numberOfElements--;
                    } else {
                        curr->getParent()->setRightChild(curr->getLeftChild());
                        curr->getLeftChild()->setParent(curr->getParent());
                        delete curr;
                        curr = nullptr;
                        numberOfElements--;
                    }
                } else if(curr->getLeftChild() == nullptr) { //right child exists
                    if(curr->getParent() == nullptr) { //deleting root
                        root = curr->getRightChild();
                        delete curr;
                        curr = nullptr;
                        numberOfElements--;
                    } else if(curr->getParent()->getLeftChild() == curr) {
                        curr->getParent()->setLeftChild(curr->getRightChild());
                        curr->getRightChild()->setParent(curr->getParent());
                        delete curr;
                        curr = nullptr;
                        numberOfElements--;
                    } else {
                        curr->getParent()->setRightChild(curr->getRightChild());
                        curr->getRightChild()->setParent(curr->getParent());
                        delete curr;
                        curr = nullptr;
                        numberOfElements--;
                    }
                } else { //two children
                    //find successor (leftmost child of right subtree
                    Node<T>* successor = curr->getLeftChild();
                    while(successor->getRightChild() != nullptr) {
                        successor = successor->getRightChild();
                    }
                    numberOfElements--;
                    T* sucData = successor->getData();
                    numberOfElements++;
                    deleteElement(sucData);
                    curr->setData(sucData);
                }
                return;
            } else if(curr->getData()->getValue() < data->getValue()) {
                curr = curr->getRightChild();
            } else {
                curr = curr->getLeftChild();
            }
        }
        cout<<data->getValue()<<" does not exist in the tree" <<endl;
        return; //Node not found
    }
    void findSmallest() {
        Node<T>* smallest = root;
        while(smallest->getLeftChild() != nullptr) {
            smallest = smallest->getLeftChild();
        }
        smallest->print();
        cout<<" is the smallest element" << endl;
    }

    void findBiggest() {
        Node<T>* biggest = root;
        while(biggest->getRightChild() != nullptr) {
            biggest = biggest->getRightChild();
        }
        biggest->print();
        cout<< " is the biggest element" << endl;
    }

    void printAscending(Node<T>* n) {
        if(n->getLeftChild() != nullptr) {
            printAscending(n->getLeftChild());
        }
        n->print();
        cout<< " ";
        if(n->getRightChild() != nullptr) {
            printAscending(n->getRightChild());
        }
    }

    void sortDescending() {
        printDescending(root);
        cout<<endl;
    }

    void printDescending(Node<T>* n) {
        if(n->getRightChild() != nullptr) {
            printDescending(n->getRightChild());
        }
        n->print();
        cout<< " ";
        if(n->getLeftChild() != nullptr) {
            printDescending(n->getLeftChild());
        }
    }

    void sortAscending() {
        printAscending(root);
        cout<<endl;
    }

    void findKthElement(int k) {
        vector<Node<T>*> *v = new  vector<Node<T> *>();
        convertToVector(v, root);
        if(k <= numberOfElements) {
            cout<<"The element at " << k << " is ";
            v->at(k-1)->print();
            cout<<endl;
        } else {
            cout<<"The element at "<< k <<" is not in the tree"<<endl;
        }
    }


    void convertToVector(vector<Node<T>*> *v,Node<T>* n) {
        if(n->getLeftChild() != nullptr) {
            convertToVector(v, n->getLeftChild());
        }
        v->push_back(n);
        if(n->getRightChild() != nullptr) {
            convertToVector(v, n->getRightChild());
        }
    }

    BinarySearchTree<T>* balanceTree() {
        vector<Node<T>*> *v = new vector<Node<T>*>();
        convertToVector(v, root);
        BinarySearchTree<Data>* newBST = new BinarySearchTree<Data>(nullptr);
        convertToTree(newBST, v, 0, numberOfElements-1);
        return newBST;
    }

    void convertToTree(BinarySearchTree<T> *b, vector<Node<T>*> *v, int start, int end) {
        if(start > end) {
            return;
        }
        int mid = (start + end)/2;
        b->insertElement(v->at(mid)->getData());
        convertToTree(b, v, start, mid-1);
        convertToTree(b, v, mid+1, end);
    }
};

int main() {
    int a[] = {10,45,23,67,89,34,12,99};
    Data* newData = new Data(a[0]);
    BinarySearchTree<Data>* newBST = new BinarySearchTree<Data>(newData);
    for(int i=1;i< (sizeof(a)/sizeof(int));i++)
    {
        newData = new Data(a[i]);
        newBST->insertElement(newData);
    }
    newBST->print();
//    newBST = newBST->balanceTree();
//    newBST->print();
    newBST->findSmallest();
    newBST->findBiggest();
    newData = new Data(10);
    newBST->deleteElement(newData); // delete root
    newBST->print();
    newData = new Data(45);
    newBST->deleteElement(newData); //delete with two children
    newBST->print();
    newData = new Data(12);
    newBST->deleteElement(newData); //delete with one child
    newBST->print();
    newData = new Data(10);
    newBST->deleteElement(newData); // delete a number that doesnt exist. What will you print?
    newBST->print();
    newBST->findKthElement(1); //first element
    newBST->findKthElement(newBST->getNumberOfElements()); //last element
    newBST->findKthElement(3); // some element in between
    newBST->findKthElement(7); // Edge case where item does not exist. What will you print?
    newBST->findSmallest();
    newBST->findBiggest();
    newBST->sortAscending();
    newBST->sortDescending();
    return 0;
}