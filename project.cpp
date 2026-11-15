// =============================================================
// PRN: 148 (even)
// Scenario: Student marks (values 0-99)
// Seed S = 0148 -> v[i] = (148 + 13*i) % 100, i = 0..19
// Hash function: Division method, h(k) = k % m, m = 23 (prime)
// Collision strategy: Linear probing, probe j -> (h(k) + j) % m
// =============================================================
#include <iostream>
using namespace std;

const int N = 20;
const int SEED = 148;

void generateDataset(int v[]) {
    for (int i = 0; i < N; i++)
        v[i] = (SEED + 13 * i) % 100;
}

int main() {
    int data[N];
    generateDataset(data);

    cout << "Personalized dataset (student marks):\n";
    for (int i = 0; i < N; i++)
        cout << "v[" << i << "] = " << data[i] << "\n";
    return 0;
}