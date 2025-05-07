#pragma once
#include <iostream>

using namespace std;

class Kopiec {
public:
    struct Element {
        int value;
        int priority;
        int insertion_order;
        //Operator porównania: element z wyższym priorytetem lub wcześniejszym wstawieniem jest "większy"
        bool operator<(const Element& other) const;
    };
    Kopiec(int initialCapacity = 16);
    ~Kopiec();
    void insert(int value, int priority);
    int extract_max();
    int find_max();
    void modify_key(int value, int new_priority);
    int return_size() const;
    void clear();
    void resize();
    int find_index(int value);
private:
    int capacity;
    int size;
    int counter;
    Element* heap; //przechowuje elementy kopca
    void heapify_up(int index);
    void heapify_down(int index);
};

