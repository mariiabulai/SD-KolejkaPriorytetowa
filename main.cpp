#include "tablica.h"
#include "kopiec.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <numeric>

using namespace std;
using namespace std::chrono;

//Funkcja szablonowa uruchamiająca testy wydajności dla dowolnej kolejki priorytetowej
template<typename PQ>
void run_tests(PQ& queue, int size, int repeats, ofstream& output, int priority_range, const vector<int>& seeds) {
    long long total_insert = 0, total_find = 0, total_extract = 0;
    long long total_modify = 0, total_size = 0;

    //Iteracja po różnych seedach dla losowości
    for (int seed : seeds) {
        mt19937 rng(seed);  //Generator liczb pseudolosowych
        uniform_int_distribution<int> dist(1, priority_range);
        uniform_int_distribution<int> half_dist(0, size / 2 - 1);
        uniform_int_distribution<int> value_dist(1, size);
        vector<int> values(size);

        for (int& val : values)
            val = value_dist(rng); //Generowanie wartości elementów

        for (int r = 0; r < repeats; ++r) {
            queue.clear();

            auto t1 = high_resolution_clock::now();
            for (int i = 0; i < size; ++i)
                queue.insert(values[i], dist(rng));
            auto t2 = high_resolution_clock::now();
            total_insert += duration_cast<nanoseconds>(t2 - t1).count();

            t1 = high_resolution_clock::now();
            for (int i = 0; i < 100; ++i)
                queue.find_max();
            t2 = high_resolution_clock::now();
            total_find += duration_cast<nanoseconds>(t2 - t1).count() / 100;

            t1 = high_resolution_clock::now();
            for (int i = 0; i < 100; ++i)
                queue.extract_max();
            t2 = high_resolution_clock::now();
            total_extract += duration_cast<nanoseconds>(t2 - t1).count() / 100;

            t1 = high_resolution_clock::now();
            for (int i = 0; i < 100; ++i) {
                int idx = half_dist(rng);
                int new_prio = dist(rng);
                queue.modify_key(values[idx], new_prio);
            }
            t2 = high_resolution_clock::now();
            total_modify += duration_cast<nanoseconds>(t2 - t1).count() / 100;

            t1 = high_resolution_clock::now();
            for (int i = 0; i < 100; ++i)
                queue.return_size();
            t2 = high_resolution_clock::now();
            total_size += duration_cast<nanoseconds>(t2 - t1).count() / 100;
        }
    }
    //Obliczenie średnich czasów i zapis do pliku CSV
    int total_runs = repeats * seeds.size();
    output << size << ","
        << (total_insert / total_runs) / size << ","
        << total_find / total_runs << ","
        << total_extract / total_runs << ","
        << total_modify / total_runs << ","
        << total_size / total_runs << endl;
}

int main() {
    vector<int> sizes = { 10000, 20000, 30000, 40000, 50000,
                          60000, 70000, 80000, 90000, 100000 };
    int repeats = 10; 
    int multiplier = 10;
    vector<int> seeds = { 42, 1337, 2024, 77, 100, 256, 999, 888 }; //Randomowe seedy

    //Pliki wyjściowe CSV dla tablicy i kopca
    ofstream array_csv("array_results.csv");
    array_csv << "Size,Insert(ns),FindMax(ns),ExtractMax(ns),ModifyKey(ns),ReturnSize(ns)\n";

    ofstream heap_csv("heap_results.csv");
    heap_csv << "Size,Insert(ns),FindMax(ns),ExtractMax(ns),ModifyKey(ns),ReturnSize(ns)\n";

    //Testujemy każdą strukturę danych dla każdego rozmiaru
    for (int size : sizes) {
        int range = size * multiplier;

        Tablica apq;
        Kopiec hpq;

        cout << "Testing size: " << size << endl;

        run_tests(apq, size, repeats, array_csv, range, seeds);
        run_tests(hpq, size, repeats, heap_csv, range, seeds);
    }

    array_csv.close();
    heap_csv.close();

    cout << "Testy zakonczone. Wyniki zapisano do plikow CSV." << endl;
    return 0;
}

