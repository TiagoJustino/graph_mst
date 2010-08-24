#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <functional>
#include <vector>

using std::vector;

template <class T>
class BinaryHeap;

template <class T>
class BinaryHeapNode {
    private:
        int pos;
    public:
        T el;
        BinaryHeapNode(T _el): el(_el) {};
    friend class BinaryHeap<T>;
};

template <class T>
class BinaryHeap {
    private:
        vector<BinaryHeapNode<T>*> heap;
        void change(int a, int b) {
            BinaryHeapNode<T>* t;
            t = heap[a];
            heap[a] = heap[b];
            heap[b] = t;
            heap[a]->pos = a;
            heap[b]->pos = b;
        };

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

        BinaryHeapNode<T>* push_back(T el) {
            BinaryHeapNode<T>* p = new BinaryHeapNode<T>(el);
            p->pos = this->heap.size();
            this->heap.push_back(p);
            return p;
        };

        // n * 2 + 1 and n * 2 + 2 are the sons
        // if(n) ( n - 1 ) / 2 if the parent
        BinaryHeapNode<T>* update(BinaryHeapNode<T>* p) {
            if(p->pos) {
                BinaryHeapNode<T>* parent = this->heap[( p->pos - 1 ) / 2];
                if(p->el < parent->el) {
                    this->change(p->pos, parent->pos);
                    return update(p);
                }
            }
            unsigned int s, l = p->pos * 2 + 1, r = p->pos * 2 + 2;
            if(l >= this->heap.size()) return p;
            if(r >= this->heap.size())
                s = l;
            else {
                if(this->heap[r]->el < this->heap[l]->el)
                    s = r;
                else
                    s = l;
            }
            BinaryHeapNode<T>* son = this->heap[s];
            if(son->el < p->el) {
                this->change(son->pos, p->pos);
                return update(p);
            }
            return p;
        };

        T pop() {
            BinaryHeapNode<T>* p = this->heap[0];
            T e = this->heap[0]->el;
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
