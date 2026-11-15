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
const int EMPTY = -1;     // NOT 0: key 0 is in the dataset
const int DELETED = -2;   // tombstone: keeps probe chains unbroken

const int FULL = -1;
const int DUPLICATE = -2;

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

    // Returns final slot, FULL, or DUPLICATE. Reuses the first tombstone
    // seen, but only after confirming the key isn't further along.
    int insert(int key, int &probes) {
        int home = hash(key);
        int firstTomb = -1;
        probes = 0;
        for (int j = 0; j < m; j++) {
            int idx = (home + j) % m;
            probes++;
            if (table[idx] == key) return DUPLICATE;
            if (table[idx] == DELETED) {
                if (firstTomb == -1) firstTomb = idx;
                continue;
            }
            if (table[idx] == EMPTY) {
                int target = (firstTomb != -1) ? firstTomb : idx;
                table[target] = key;
                return target;
            }
        }
        if (firstTomb != -1) { table[firstTomb] = key; return firstTomb; }
        return FULL;
    }

    // Skips over tombstones; stops only at a truly EMPTY slot.
    int search(int key, int &probes) const {
        int home = hash(key);
        probes = 0;
        for (int j = 0; j < m; j++) {
            int idx = (home + j) % m;
            probes++;
            if (table[idx] == EMPTY) return -1;
            if (table[idx] == key)   return idx;
        }
        return -1;
    }

    bool remove(int key) {
        int probes;
        int idx = search(key, probes);
        if (idx < 0) return false;
        table[idx] = DELETED;
        return true;
    }

    void display() const {
        cout << "\nSlot | Key\n-----+-----\n";
        for (int i = 0; i < m; i++) {
            cout << setw(4) << i << " | ";
            if (table[i] == EMPTY)        cout << "--";
            else if (table[i] == DELETED) cout << "DEL";
            else                          cout << table[i];
            cout << "\n";
        }
    }
};

void reportInsert(HashTable &ht, int key) {
    int probes;
    int slot = ht.insert(key, probes);
    cout << "insert(" << key << "): ";
    if (slot >= 0)              cout << "slot " << slot;
    else if (slot == DUPLICATE) cout << "rejected, DUPLICATE";
    else                        cout << "rejected, table FULL";
    cout << " after " << probes << " probe(s)\n";
}

void searchTest(const HashTable &ht, int key) {
    int probes;
    int slot = ht.search(key, probes);
    cout << "search(" << key << "): ";
    if (slot >= 0) cout << "found at slot " << slot;
    else           cout << "NOT found";
    cout << " after " << probes << " probe(s)\n";
}

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
        if (slot >= 0)              cout << setw(5) << slot;
        else if (slot == DUPLICATE) cout << "  DUP";
        else                        cout << " FULL";
        cout << " | " << probes << "\n";
    }
    cout << "Total probes: " << totalProbes
         << ", load factor: " << fixed << setprecision(2)
         << (double)N / TABLE_SIZE << "\n";
    ht.display();

    cout << "\n--- Search tests ---\n";
    searchTest(ht, data[0]);
    searchTest(ht, data[19]);
    searchTest(ht, 0);
    searchTest(ht, 50);
    searchTest(ht, 99);

    cout << "\n--- Duplicate key tests ---\n";
    reportInsert(ht, data[0]);
    reportInsert(ht, 0);

    cout << "\n--- Full table test (separate table, m = 5) ---\n";
    HashTable small(5);
    int extra[6] = {10, 15, 20, 25, 30, 35};
    for (int k : extra) reportInsert(small, k);
    small.display();

    cout << "\n--- Deletion test (tombstones) ---\n";
    // In the small table, 10,15,20,25,30 form one probe chain from slot 0.
    cout << "remove(15): " << (small.remove(15) ? "done" : "not found") << "\n";
    searchTest(small, 25);     // must still be found past the tombstone
    reportInsert(small, 25);   // must be rejected as duplicate, not reuse tombstone
    reportInsert(small, 40);   // should reuse the tombstone
    small.display();
    return 0;
}