#include <stdio.h>

typedef struct {
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
} Process;

void sortProcessesByPriority(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].priority > processes[j].priority) {
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

void calculateWaitingTime(Process processes[], int n) {
    processes[0].waiting_time = 0;
    for (int i = 1; i < n; i++) {
        processes[i].waiting_time = processes[i - 1].waiting_time + processes[i - 1].burst_time;
    }
}

void calculateTurnaroundTime(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
    }
}

void printProcesses(Process processes[], int n) {
    printf("Process\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, processes[i].burst_time, processes[i].priority, processes[i].waiting_time, processes[i].turnaround_time);
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];
    printf("Enter the burst time and priority for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d - Burst Time: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("Process %d - Priority: ", i + 1);
        scanf("%d", &processes[i].priority);
    }

    sortProcessesByPriority(processes, n);
    calculateWaitingTime(processes, n);
    calculateTurnaroundTime(processes, n);
    printProcesses(processes, n);

    return 0;
}
