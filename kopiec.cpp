#include "kopiec.h"
#include <iostream>

//porównywanie priorytetów
bool Kopiec::Element::operator<(const Element& other) const {
    return priority < other.priority ||
        (priority == other.priority && insertion_order > other.insertion_order);
}

Kopiec::Kopiec(int initialCapacity) {
    heap = new Element[initialCapacity];
    capacity = initialCapacity;
    size = 0;
    counter = 0;
}

Kopiec::~Kopiec() {
    delete[] heap;
}

void Kopiec::resize() {
    capacity *= 2;
    Element* newKopiec = new Element[capacity];
    for (int i = 0; i < size; ++i)
        newKopiec[i] = heap[i];
    delete[] heap;
    heap = newKopiec;
}

void Kopiec::insert(int value, int priority) {
    if (size == capacity)
        resize();

    heap[size] = { value, priority, counter++ };
    heapify_up(size);
    size++;
}

int Kopiec::extract_max() {
    if (size == 0) return INT_MIN;

    int val = heap[0].value;
    heap[0] = heap[size - 1];
    size--;
    heapify_down(0);
    return val;
}

int Kopiec::find_max() {
    if (size == 0) return INT_MIN;
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
    return size;
}

void Kopiec::clear() {
    size = 0;
    counter = 0;
}

void Kopiec::heapify_up(int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (!(heap[parent] < heap[i])) break; //jeśli rodzic nie jest mniejszy, zakończyć
        //zamienić miejscami z rodzicem
        Element temp = heap[i];
        heap[i] = heap[parent];
        heap[parent] = temp;
        i = parent;
    }
}

void Kopiec::heapify_down(int i) {
    while (true) {
        int left = 2 * i + 1, right = 2 * i + 2, largest = i;

        //Sprawdzenia czy lewe 'dziecko' jest większe
        if (left < size && heap[largest] < heap[left]) largest = left;

        //Sprawdzenie czy prawe dziecko jest większe
        if (right < size && heap[largest] < heap[right]) largest = right;

        if (largest == i) break; //Jeśli największy to i, zakończenie
         //Zamienić miejscami z większym dzieckiem
        Element temp = heap[i];
        heap[i] = heap[largest];
        heap[largest] = temp;
        i = largest; //Kontynuować dla nowej pozycji
    }
}

int Kopiec::find_index(int value) {
    for (int i = 0; i < size; ++i)
        if (heap[i].value == value) return i;
    return -1;
}
