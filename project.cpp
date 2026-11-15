// =============================================================
// PRN: 148 (even)
// Scenario: Student marks (values 0-99)
// Seed S = 0148 -> v[i] = (148 + 13*i) % 100, i = 0..19
// Hash function: Division method, h(k) = k % m, m = 23 (prime)
// Collision strategy: Linear probing, probe j -> (h(k) + j) % m
// =============================================================
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

const int N = 20;
const int SEED = 148;
const int TABLE_SIZE = 23;
const int EMPTY = -1;   // NOT 0: key 0 is in the dataset

void generateDataset(int v[]) {
    for (int i = 0; i < N; i++)
        v[i] = (SEED + 13 * i) % 100;
}

class HashTable {
    vector<int> table;
    int m;
public:
    HashTable(int size) : table(size, EMPTY), m(size) {}

    int hash(int key) const { return key % m; }

    // No collision handling yet: report collision and skip the key
    bool insert(int key) {
        int idx = hash(key);
        if (table[idx] != EMPTY) {
            cout << "  COLLISION: key " << key << " -> slot " << idx
                 << " already holds " << table[idx] << " (key skipped)\n";
            return false;
        }
        table[idx] = key;
        return true;
    }

    void display() const {
        cout << "\nSlot | Key\n-----+-----\n";
        for (int i = 0; i < m; i++) {
            cout << setw(4) << i << " | ";
            if (table[i] == EMPTY) cout << "--";
            else cout << table[i];
            cout << "\n";
        }
    }
};

int main() {
    int data[N];
    generateDataset(data);
    HashTable ht(TABLE_SIZE);

    int stored = 0;
    for (int i = 0; i < N; i++)
        if (ht.insert(data[i])) stored++;

    cout << "\nStored " << stored << " of " << N << " keys\n";
    ht.display();
    return 0;
}