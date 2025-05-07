#pragma once

#include <iostream>

using namespace std;

class Tablica {
public:
    struct Element {
        int value;
        int priority;
        int insertion_order;
    };
    Tablica(int initialCapacity = 16);
    ~Tablica();
    void insert(int value, int priority);
    int extract_max();
    int find_max();
    void modify_key(int value, int new_priority);
    void clear();
    void resize();
    int return_size() const;

private:
    Element* data;
    int capacity;
    int size;
    int counter;
};
