#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

template <class T>
struct BinaryHeapNode {
    T& el;
    BinaryHeapNode *p, *l, *r;
};

template <class T>
class BinaryHeap {
    private:
        BinaryHeapNode<T> *root;
        int size;
    public:
        BinaryHeap(): root(NULL), size(0) {};
        BinaryHeapNode<T> *push_back(T& el) {
            BinaryHeapNode<T>* node = new BinaryHeapNode<T>;
            node->el = el;
            // TODO: put in right position
            return node;
        };
        bool empty() {
            return this->size == 0;
        };
        T& pop() {
            if(this->empty())
                return root->el;
            //TODO: Code
            return root->el;
        };
        void update(BinaryHeapNode<T> *node) {
            node = NULL;
        };
};

#endif
