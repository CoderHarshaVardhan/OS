#include <stdio.h>
#include <limits.h>

typedef struct {
    int processID;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
    int completionTime;
} Process;

void findWaitingTime(Process processes[], int n) {
    int completed = 0, currentTime = 0, minRemainingTime = INT_MAX;
    int shortest = 0, finishTime;
    int check = 0;

    while (completed != n) {
        for (int i = 0; i < n; i++) {
            if ((processes[i].arrivalTime <= currentTime) && (processes[i].remainingTime < minRemainingTime) && processes[i].remainingTime > 0) {
                minRemainingTime = processes[i].remainingTime;
                shortest = i;
                check = 1;
            }
        }

        if (check == 0) {
            currentTime++;
            continue;
        }

        processes[shortest].remainingTime--;

        minRemainingTime = processes[shortest].remainingTime;
        if (minRemainingTime == 0) {
            minRemainingTime = INT_MAX;
        }

        if (processes[shortest].remainingTime == 0) {
            completed++;
            check = 0;
            finishTime = currentTime + 1;

            processes[shortest].waitingTime = finishTime - processes[shortest].burstTime - processes[shortest].arrivalTime;

            if (processes[shortest].waitingTime < 0) {
                processes[shortest].waitingTime = 0;
            }

            processes[shortest].completionTime = finishTime;
        }
        currentTime++;
    }
}

void findTurnaroundTime(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaroundTime = processes[i].burstTime + processes[i].waitingTime;
    }
}

void printProcesses(Process processes[], int n) {
    int totalWaitingTime = 0, totalTurnaroundTime = 0;

    printf("ProcessID\tArrivalTime\tBurstTime\tWaitingTime\tTurnaroundTime\tCompletionTime\n");
    for (int i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].processID, processes[i].arrivalTime, processes[i].burstTime, processes[i].waitingTime, processes[i].turnaroundTime, processes[i].completionTime);
    }

    printf("Average Waiting Time: %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].processID = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime;
    }

    findWaitingTime(processes, n);
    findTurnaroundTime(processes, n);
    printProcesses(processes, n);

    return 0;
}
