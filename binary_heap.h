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
        int _size;
    public:
        BinaryHeap(): root(NULL), _size(0) {};
        int size() { return this->_size; };
        BinaryHeapNode<T> *push_back(T& el) {
            BinaryHeapNode<T>* node = new BinaryHeapNode<T>;
            node->el = el;
            // TODO: put in right position
            return node;
        };
        bool empty() {
            return this->_size == 0;
        };
        T& getMin() {
            if(this->empty())
                return root->el;
            //TODO: Code
            return root->el;
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
        BinaryHeapNode<T> *insert(T& el) {
            BinaryHeapNode<T>* node = this->push_back(el);
            update(node);
            return node;
        };
};

#endif
