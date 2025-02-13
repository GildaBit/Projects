#include <iostream>
using namespace std;

template <typename T> class Node{
private:
    T* data;
    Node<T>* leftChild;
    Node<T>* rightChild;
    Node<T>* parent;
    int height;
public:
    Node<T>() {
        data = 0;
        leftChild = nullptr;
        rightChild = nullptr;
        parent = nullptr;
        height = NULL;
    }
    Node<T>(T* data) {
        this->data = data;
        leftChild = nullptr;
        rightChild = nullptr;
        parent = nullptr;
        height = 0;
    }
    Node<T>(T* data, Node<T>* parent) {
        this->data = data;
        leftChild = nullptr;
        rightChild = nullptr;
        this->parent = parent;
        height = this->parent->getHeight() + 1;
    }
    void print() {
        data->print();
    }

    bool compare(T* other) {
        return data->compare(other);
    }

    T* getData() {
        return data;
    }
    Node<T>* getLeftChild() {
        return leftChild;
    }

    Node<T>* getRightChild() {
        return rightChild;
    }

    Node<T>* getParent() {
        return parent;
    }

    void setData(T* data) {
        this->data = data;
    }
    void setLeftChild(Node<T>* leftChild) {
        this->leftChild = leftChild;
    }
    void setRightChild(Node<T>* rightChild) {
        this->rightChild = rightChild;
    }
    void setParent(Node<T>* parent) {
        this->parent = parent;
    }
    int getHeight() {
        return height;
    }
    void setHeight(int height) {
        this->height = height;
    }

};

class Data {
private:
    int sourceVertex;
    int destinationVertex;
    int edgeCost;
public:
//    Data() {
//        sourceVertex = NULL;
//        destinationVertex = NULL;
//        edgeCost = NULL;
//    }
//    Data(int sourceVertex) {
//        this->sourceVertex = sourceVertex;
//        destinationVertex = NULL;
//        edgeCost = NULL;
//    }
    Data(int sourceVertex, int destinationVertex, int edgeCost) {
        this->sourceVertex = sourceVertex;
        this->destinationVertex = destinationVertex;
        this->edgeCost = edgeCost;
    }
    void print() {
        cout << sourceVertex << " - " << destinationVertex << " -> " << edgeCost;
    }

    bool compare(Data* other) { //returns if this edgecost is bigger than the compared one
        return edgeCost >= other->getEdgeCost();
    }

    int getSourceVertex() {
        return sourceVertex;
    }
    int getDestinationVertex() {
        return destinationVertex;
    }
    int getEdgeCost() {
        return edgeCost;
    }
    void setSourceVertex(int sourceVertex) {
        this->sourceVertex = sourceVertex;
    }
    void setDestinationVertex(int destinationVertex) {
        this->destinationVertex =destinationVertex;
    }
    void setEdgeCost(int edgeCost) {
        this->edgeCost = edgeCost;
    }
};

template <typename T> class BinaryHeap{
private:
    Node<T>* root;
    int numberOfElements;
    int height;
    Node<T>* pos;
    Node<T>* recent;

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

    void setPos(Node<T>* n, bool f) {
        if(f) {
            return;
        }
        if(numberOfElements == (pow(2, height) - 1)) {
            Node<T>* temp = root;
            while(temp->getLeftChild() != nullptr) {
                temp = temp->getLeftChild();
            }
            pos = temp;
            height++;

        }
        else {
            if((n->getHeight() == this->height - 1) && ((n->getLeftChild() == nullptr) || (n->getRightChild() == nullptr))) {
                pos = n;
                f = true;
                return;
            }

            if(n->getRightChild() != nullptr) {
                setPos(n->getRightChild(), f);
            }
            if(n->getLeftChild() != nullptr) {
                setPos(n->getLeftChild(), f);
            }

        }
    }

    void setRecent(Node<T>* n, bool f) {
        if(f) {
            return;
        }
        if(numberOfElements == (pow(2, height-1) - 1)) {
            Node<T>* temp = root;
            while(temp->getRightChild() != nullptr) {
                temp = temp->getRightChild();
            }
            recent = temp;
            height--;

        }
        else {
            if(n->getHeight() == height) {
                recent = n;
                f = true;
                return;
            }
            if(n->getLeftChild() != nullptr) {
                setRecent(n->getLeftChild(), f);
            }
            if(n->getRightChild() != nullptr) {
                setRecent(n->getRightChild(), f);
            }

        }
    }

    void heapify(Node<T>* n) {
        while(!(n->compare(n->getParent()->getData()))) {
            //checks if n<parent
            Node<T>* temp = n;
            T* d = n->getData();
            n->setData(n->getParent()->getData());
            n->getParent()->setData(d);
            n = n->getParent();
            if(n == root){
                return;
            }
        }
    }


    void downHeap(Node<T>* n) {
        while((n->getRightChild() != nullptr) && (n->getLeftChild() != nullptr)) {
            if(n->getLeftChild()->compare(n->getRightChild()->getData())) {
                //if right data is smaller than left
                T* temp = n->getData();
                n->setData(n->getRightChild()->getData());
                n->getRightChild()->setData(temp);
                n = n->getRightChild();
            } else {
                T* temp = n->getData();
                n->setData(n->getLeftChild()->getData());
                n->getLeftChild()->setData(temp);
                n = n->getLeftChild();
            }
        }
        if(n->getRightChild() != nullptr) {
            //if right data is smaller than left
            T* temp = n->getData();
            n->setData(n->getRightChild()->getData());
            n->getRightChild()->setData(temp);
        } else if(n->getLeftChild() != nullptr) {
            T* temp = n->getData();
            n->setData(n->getLeftChild()->getData());
            n->getLeftChild()->setData(temp);
        }
    }
public:
    BinaryHeap<T>() {
        root = nullptr;
        numberOfElements = 0;
        height = 0;
    }
    BinaryHeap<T>(Node<T>* root) {
        this->root = root;
        pos = root;
        numberOfElements = 1;
        height = 1;
    }
    ~BinaryHeap<T>(){
        clear(root);
        height = 0;
        numberOfElements = 0;
    }

    void insertElement(T* data) {
        Node<T> *inserted = new Node<T>(data);
        if (root == nullptr) {
            inserted->setHeight(1);
            root = inserted;
            height = 1;
            numberOfElements = 1;
            recent = inserted;
            setPos(root, false);
        } else {
            if (pos->getLeftChild() == nullptr) {
                pos->setLeftChild(inserted);
                inserted->setParent(pos);
                inserted->setHeight(inserted->getParent()->getHeight() + 1);
                heapify(inserted);
                recent = inserted;
                numberOfElements++;
                setPos(root, false);
            } else if (pos->getRightChild() == nullptr) {
                pos->setRightChild(inserted);
                inserted->setParent(pos);
                inserted->setHeight(inserted->getParent()->getHeight() + 1);
                heapify(inserted);
                recent = inserted;
                numberOfElements++;
                setPos(root, false);
            }
        }
    }
    Data* deleteElement() {
        Data* d;
        if(numberOfElements == 0) {
            return nullptr;
        }
        if(recent == root) {
            d = recent->getData();
            root = nullptr;
            height = 0;
            numberOfElements = 0;
            pos = nullptr;
            return d;
        } else {
            setRecent(root, false);
            d = root->getData();
            root->setData(recent->getData());
            downHeap(root);
            if(recent->getParent()->getLeftChild() == recent) {
                recent->getParent()->setLeftChild(nullptr);
            } else if(recent->getParent()->getRightChild() == recent) {
                recent->getParent()->setRightChild(nullptr);
            }
            recent->setParent(nullptr);
            delete recent;
            numberOfElements--;
            setRecent(root, false);
            return d;
        }
    }
    void print(Node<T>* n) {
        if(numberOfElements == 0) {
            cout<<"it's empty" <<endl;
            return;
        }
        n->print();
        cout<< " " << endl;
        if(n->getLeftChild() != nullptr) {
            print(n->getLeftChild());
        }

        if(n->getRightChild() != nullptr) {
            print(n->getRightChild());
        }
    }
    Node<T>* getRoot() {
        return root;
    }
    Node<T>* getPos() {
        return pos;
    }
    int getNumberOfELements() {
        return numberOfElements;
    }
    int getHeight() {
        return height;
    }
    void setRoot(Node<T>* root) {
        this->root = root;
    }
    void setNumberOfElements(int numberOfElements) {
        this->numberOfElements = numberOfElements;
    }
    void setHeight(int height) {
        this->height = height;
    }
    Node<T>* getRecent() {
        return recent;
    }
};

const int VERTEXCOUNT = 5;

void runPrims(int G[VERTEXCOUNT][VERTEXCOUNT], BinaryHeap<Data>* binHeap){
    bool visited[VERTEXCOUNT];
    memset(visited, false, sizeof(visited));
    int numEdges = 0;
    visited[0] = true;
    while(numEdges < VERTEXCOUNT - 1) {
        Data* min;
        for(int i = 0; i <VERTEXCOUNT; i++) {
            if(visited[i]) {
                for(int j = 0; j<VERTEXCOUNT; j++) {
                    if((!visited[j]) && G[i][j] != 0) {
                        Data* d = new Data(i, j, G[i][j]);
                        binHeap->insertElement(d);
                    }
                }
            }
        }
        min = binHeap->deleteElement();
        min->print();
        cout<<endl;
        visited[min->getDestinationVertex()] = true;
        while(binHeap->getRoot()!=nullptr) {
            binHeap->deleteElement();
        }
        numEdges++;
    }
}

int main() {
    BinaryHeap<Data>* b = new BinaryHeap<Data>();
    int G[VERTEXCOUNT][VERTEXCOUNT] =
                  {{0, 3, 65, 0, 0},
                   {3, 0, 85, 20, 45},
                   {65, 85, 0, 41, 77},
                   {0, 20, 41, 0, 51},
                   {0, 45, 77, 51, 0}};
    cout<<"MST for the graph:"<<endl;
    runPrims(G, b);
    cout<<endl<<"ALL MY TESTING:" <<endl<<endl<<"inserting the full tree"<<endl;
    for(int i = 0; i < VERTEXCOUNT; i++) {
        for(int j = 0; j < VERTEXCOUNT; j++) {
            string s = to_string(G[i][j]);
            if(s!="0") {
                Data* d = new Data(i, j, G[i][j]);
                b->insertElement(d);
            }
        }
    }
    b->print(b->getRoot());
    cout<<endl<<"list of all elements to be deleted:"<<endl;
    while(b->getRoot()!=nullptr) {
        cout<<"next to be deleted: ";
        b->deleteElement()->print();
        cout<<endl;
    }
    return 0;
}