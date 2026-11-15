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

    // Linear probing. Returns final slot, or -1 if the table is full.
    int insert(int key, int &probes) {
        int home = hash(key);
        probes = 0;
        for (int j = 0; j < m; j++) {
            int idx = (home + j) % m;     // wrap around
            probes++;
            if (table[idx] == EMPTY) {
                table[idx] = key;
                return idx;
            }
        }
        return -1;                        // checked all m slots
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

    cout << "Inserting dataset (m = " << TABLE_SIZE << ")\n";
    cout << " i | Key | Home | Final | Probes\n";
    int totalProbes = 0;
    for (int i = 0; i < N; i++) {
        int probes;
        int slot = ht.insert(data[i], probes);
        totalProbes += probes;
        cout << setw(2) << i << " | " << setw(3) << data[i] << " | "
             << setw(4) << ht.hash(data[i]) << " | ";
        if (slot >= 0) cout << setw(5) << slot;
        else           cout << " FULL";
        cout << " | " << probes << "\n";
    }
    cout << "Total probes: " << totalProbes
         << ", load factor: " << fixed << setprecision(2)
         << (double)N / TABLE_SIZE << "\n";
    ht.display();
    return 0;
}