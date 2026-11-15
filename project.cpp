// =============================================================
// PRN: 148 (even)
// Scenario: Student marks (values 0-99)
// Seed S = 0148 -> v[i] = (148 + 13*i) % 100, i = 0..19
// Hash function: Division method, h(k) = k % m, m = 23 (prime)
// Collision strategy: Linear probing, probe j -> (h(k) + j) % m
// =============================================================
#include <iostream>
#include <iomanip>
using namespace std;

const int N = 20;
const int SEED = 148;
const int TABLE_SIZE = 23;

void generateDataset(int v[]) {
    for (int i = 0; i < N; i++)
        v[i] = (SEED + 13 * i) % 100;
}

// Division method
int hashDivision(int key, int m) {
    return key % m;
}

int main() {
    int data[N];
    generateDataset(data);

    cout << "Home slots with m = " << TABLE_SIZE << "\n";
    cout << " i | Key | h(k)\n";
    for (int i = 0; i < N; i++)
        cout << setw(2) << i << " | " << setw(3) << data[i]
             << " | " << setw(4) << hashDivision(data[i], TABLE_SIZE) << "\n";
    return 0;
}