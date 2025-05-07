#pragma once
#include <vector>
#include <iostream>

using namespace std;

class Kopiec {
private:
    struct Element {
        int value;
        int priority;
        int insertion_order;
        //Operator porównania: element z wyższym priorytetem lub wcześniejszym wstawieniem jest "większy"
        bool operator<(const Element& other) const;
    };
    vector<Element> heap; //Wektor przechowujący elementy kopca
    int counter;

    void heapify_up(int index);
    void heapify_down(int index);
    int find_index(int value);

public:
    Kopiec();
    void insert(int value, int priority);
    int extract_max();
    int find_max();
    void modify_key(int value, int new_priority);
    int return_size() const;
    void clear();
};

