#include <stdio.h>

typedef struct {
    int burst_time;
    int remaining_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    int arrival_time;
} Process;

void calculateTimes(Process processes[], int n) {
    int completed = 0, current_time = 0;

    while (completed != n) {
        int min_priority = 10000, shortest = -1;

        for (int j = 0; j < n; j++) {
            if (processes[j].arrival_time <= current_time && processes[j].remaining_time > 0 && processes[j].priority < min_priority) {
                min_priority = processes[j].priority;
                shortest = j;
            }
        }

        if (shortest == -1) {
            current_time++;
            continue;
        }

        processes[shortest].remaining_time--;

        if (processes[shortest].remaining_time == 0) {
            completed++;
            int finish_time = current_time + 1;
            processes[shortest].waiting_time = finish_time - processes[shortest].burst_time - processes[shortest].arrival_time;
            if (processes[shortest].waiting_time < 0) processes[shortest].waiting_time = 0;
        }
        current_time++;
    }

    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].burst_time + processes[i].waiting_time;
    }
}

void printProcesses(Process processes[], int n) {
    printf("Process\tBurst Time\tPriority\tArrival Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, processes[i].burst_time, processes[i].priority, processes[i].arrival_time, processes[i].waiting_time, processes[i].turnaround_time);
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];
    printf("Enter the burst time, priority, and arrival time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d - Burst Time: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("Process %d - Priority: ", i + 1);
        scanf("%d", &processes[i].priority);
        printf("Process %d - Arrival Time: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    calculateTimes(processes, n);
    printProcesses(processes, n);

    return 0;
}
