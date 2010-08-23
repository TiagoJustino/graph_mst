#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <vector>

using std::vector;

template <class T>
class BinaryHeap;

template <class T>
class BinaryHeapNode {
    private:
        int pos;
    public:
        T& el;
        BinaryHeapNode(T& _el): el(_el) {};
    friend class BinaryHeap<T>;
};

template <class T>
class BinaryHeap {
    private:
        vector<BinaryHeapNode<T>*> heap;
    public:
        BinaryHeap(){};

        ~BinaryHeap() {
            typename vector<BinaryHeapNode<T>*>::iterator i;
            for(i = this->heap.begin(); i < this->heap.end(); ++i)
                delete *i;
        }

        int size() { return this->heap.size(); };

        bool empty() {
            return this->heap.empty();
        };

        T& getMin() {
            return this->heap[0]->el;
        };

        BinaryHeapNode<T>* push_back(T& el) {
            BinaryHeapNode<T>* p = new BinaryHeapNode<T>(el);
            this->heap.push_back(p);
            return p;
        };

        BinaryHeapNode<T>* update(BinaryHeapNode<T>* p) {
            return p;
        };

        T& pop() {
            BinaryHeapNode<T>* p = this->heap[0];
            T& e = this->heap[0]->el;
            this->heap[0] = this->heap[this->heap.size() - 1];
            this->heap.pop_back();
            delete p;
            this->heap[0]->pos = 0;
            this->update(this->heap[0]);
            return e;
        };

        BinaryHeapNode<T>* insert(T& el) {
            return this->update(this->push_back(el));
        };
};

#endif
