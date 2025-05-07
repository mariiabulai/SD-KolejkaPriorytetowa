#include "kopiec.h"
#include <algorithm>
#include <iostream>

//porównywanie priorytetów
bool Kopiec::Element::operator<(const Element& other) const {
    return priority < other.priority ||
        (priority == other.priority && insertion_order > other.insertion_order);
}

Kopiec::Kopiec() : counter(0) {}

void Kopiec::insert(int value, int priority) {
    heap.push_back({ value, priority, counter++ });
    heapify_up(heap.size() - 1);
}

int Kopiec::extract_max() {
    if (heap.empty()) return INT_MIN;
    int val = heap[0].value;
    heap[0] = heap.back();
    heap.pop_back();
    heapify_down(0);
    return val;
}

int Kopiec::find_max() {
    if (heap.empty()) return INT_MIN;
    return heap[0].value;
}

void Kopiec::modify_key(int value, int new_priority) {
    int index = find_index(value);
    if (index == -1) return;

    int old_priority = heap[index].priority;
    heap[index].priority = new_priority;

    //W zależności od tego, czy priorytet wzrósł czy zmalał, trzeba wykonać odpowiedni heapify
    if (new_priority > old_priority)
        heapify_up(index);
    else
        heapify_down(index);
}

int Kopiec::return_size() const {
    return heap.size();
}

void Kopiec::clear() {
    heap.clear();
    counter = 0;
}

void Kopiec::heapify_up(int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (!(heap[parent] < heap[i])) break; //jeśli rodzic nie jest mniejszy, zakończyć
        swap(heap[parent], heap[i]);     //zamienić miejscami z rodzicem
        i = parent;
    }
}

void Kopiec::heapify_down(int i) {
    int size = heap.size();
    while (true) {
        int left = 2 * i + 1, right = 2 * i + 2, largest = i;

        //Sprawdzenia czy lewe 'dziecko' jest większe
        if (left < size && heap[largest] < heap[left]) largest = left;

        //Sprawdzenie czy prawe dziecko jest większe
        if (right < size && heap[largest] < heap[right]) largest = right;

        if (largest == i) break; //Jeśli największy to i, zakończenie
        std::swap(heap[i], heap[largest]); //Zamienić miejscami z większym dzieckiem
        i = largest; //Kontynuować dla nowej pozycji
    }
}

int Kopiec::find_index(int value) {
    for (int i = 0; i < heap.size(); ++i)
        if (heap[i].value == value) return i;
    return -1;
}
