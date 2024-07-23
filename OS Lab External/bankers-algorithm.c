#include <stdio.h>
#include <stdbool.h>

#define NUM_PROCESSES 5
#define NUM_RESOURCES 3

int main() {
    // Number of processes and resources
    int n = NUM_PROCESSES;
    int m = NUM_RESOURCES;

    // Allocation Matrix
    int alloc[NUM_PROCESSES][NUM_RESOURCES] = {
        {0, 1, 0}, // P0
        {2, 0, 0}, // P1
        {3, 0, 2}, // P2
        {2, 1, 1}, // P3
        {0, 0, 2}  // P4
    };

    // MAX Matrix
    int max[NUM_PROCESSES][NUM_RESOURCES] = {
        {7, 5, 3}, // P0
        {3, 2, 2}, // P1
        {9, 0, 2}, // P2
        {2, 2, 2}, // P3
        {4, 3, 3}  // P4
    };

    // Available Resources
    int avail[NUM_RESOURCES] = {3, 3, 2};

    // Mark all processes as unfinished
    bool finish[NUM_PROCESSES] = {0};
    int safeSequence[NUM_PROCESSES];
    int need[NUM_PROCESSES][NUM_RESOURCES];

    // Calculate the Need matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int p = 0; p < n; p++) {
            if (!finish[p]) {
                bool canAllocate = true;
                for (int r = 0; r < m; r++) {
                    if (need[p][r] > avail[r]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    for (int r = 0; r < m; r++) {
                        avail[r] += alloc[p][r];
                    }
                    safeSequence[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("The system is not in a safe state\n");
            return 1;
        }
    }

    printf("The system is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < n; i++) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");

    return 0;
}
