#pragma once

#include <vector>
#include <iostream>

using namespace std;

class Tablica {
private:
    struct Element {
        int value;
        int priority;
        int insertion_order;
    };
    vector<Element> data;
    int counter;

public:
    Tablica();
    void insert(int value, int priority);
    int extract_max();
    int find_max();
    void modify_key(int value, int new_priority);
    int return_size() const;
    void clear();
};
