#include "tablica.h"
#include <algorithm>
#include <iostream>

using namespace std;

Tablica::Tablica() : counter(0) {}

void Tablica::insert(int value, int priority) {
    data.push_back({ value, priority, counter++ });
}

int Tablica::extract_max() {
    if (data.empty()) return INT_MIN; //Sprawdzenie, jeśli tablica pusta, zostaje zwrócona minimalną wartość int

    //element o najwyższym priorytecie (jeśli kilka, to najwcześniej dodany)
    auto it = max_element(data.begin(), data.end(),
        [](const Element& a, const Element& b) {
            return a.priority < b.priority ||
                (a.priority == b.priority && a.insertion_order > b.insertion_order);
        });
    int val = it->value;  //Zapisywanie wartości maksymalnego elementu
    data.erase(it);       //usuwanie go z tablicy
    return val;           //zwrócenie wartości
}

//bez usuwania
int Tablica::find_max() {
    if (data.empty()) return INT_MIN;
    auto it = max_element(data.begin(), data.end(),
        [](const Element& a, const Element& b) {
            return a.priority < b.priority ||
                (a.priority == b.priority && a.insertion_order > b.insertion_order);
        });
    return it->value;
}

void Tablica::modify_key(int value, int new_priority) {
    for (auto& el : data) {
        if (el.value == value) {
            el.priority = new_priority;
            return;
        }
    }
}

int Tablica::return_size() const {
    return data.size();
}

void Tablica::clear() {
    data.clear();
    data.reserve(100000);  //Rezerwuje miejsce na 100000 elementów, by uniknąć częstych alokacji
    counter = 0; //Resetuje licznik kolejności wstawiania
}
