#include "tablica.h"
#include <iostream>

using namespace std;

Tablica::Tablica(int initialCapacity) {
    data = new Element[initialCapacity];
    capacity = initialCapacity;
    size = 0;
    counter = 0;
}

Tablica::~Tablica() {
    delete[] data;
}

void Tablica::insert(int value, int priority) {
    if (size == capacity)
        resize();

    data[size].value = value;
    data[size].priority = priority;
    data[size].insertion_order = counter++;
    size++;
}

int Tablica::extract_max() {
    if (size == 0) return INT_MIN; //Sprawdzenie, jeśli tablica pusta, zostaje zwrócona minimalną wartość int

    //element o najwyższym priorytecie (jeśli kilka, to najwcześniej dodany)
    int max_index = 0;
    for (int i = 1; i < size; ++i) {
        if (data[i].priority > data[max_index].priority ||
            (data[i].priority == data[max_index].priority &&
                data[i].insertion_order < data[max_index].insertion_order)) {
            max_index = i;
        }
    }

    int val = data[max_index].value;
    // Usuwanie elementu przez przesunięcie reszty
    for (int i = max_index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
    size--;
    return val;
}

//bez usuwania
int Tablica::find_max() {
    if (size == 0) return INT_MIN;
    int max_index = 0;
    for (int i = 1; i < size; ++i) {
        if (data[i].priority > data[max_index].priority ||
            (data[i].priority == data[max_index].priority &&
                data[i].insertion_order < data[max_index].insertion_order)) {
            max_index = i;
        }
    }
    return data[max_index].value;
}

void Tablica::modify_key(int value, int new_priority) {
    for (int i = 0; i < size; ++i) {
        if (data[i].value == value) {
            data[i].priority = new_priority;
            return;
        }
    }
}

int Tablica::return_size() const {
    return size;
}

void Tablica::clear() {
    size = 0;
    counter = 0; //Resetuje licznik kolejności wstawiania
}

void Tablica::resize() {
    capacity *= 2;
    Element* newData = new Element[capacity];
    for (int i = 0; i < size; ++i)
        newData[i] = data[i];
    delete[] data;
    data = newData;
}
