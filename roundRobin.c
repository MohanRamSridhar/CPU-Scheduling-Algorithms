#include <stdio.h>

int main() {
    int n, i, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int burst_time[n], remaining_time[n], waiting_time[n], turnaround_time[n], priority[n];
    printf("Enter the burst time and priority for each process:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d - Burst Time: ", i + 1);
        scanf("%d", &burst_time[i]);
        printf("Process %d - Priority: ", i + 1);
        scanf("%d", &priority[i]);
        remaining_time[i] = burst_time[i];
    }

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    int complete = 0, current_time = 0;
    while (complete != n) {
        int highest_priority = __INT_MAX__;
        int index = -1;

        for (i = 0; i < n; i++) {
            if (remaining_time[i] > 0 && priority[i] < highest_priority) {
                highest_priority = priority[i];
                index = i;
            }
        }

        if (index == -1) {
            current_time++;
            continue;
        }

        if (remaining_time[index] > quantum) {
            current_time += quantum;
            remaining_time[index] -= quantum;
        } else {
            current_time += remaining_time[index];
            waiting_time[index] = current_time - burst_time[index];
            remaining_time[index] = 0;
            complete++;
        }
    }

    for (i = 0; i < n; i++) {
        turnaround_time[i] = burst_time[i] + waiting_time[i];
    }

    printf("\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i], priority[i], waiting_time[i], turnaround_time[i]);
    }

    float avg_waiting_time = 0, avg_turnaround_time = 0;
    for (i = 0; i < n; i++) {
        avg_waiting_time += waiting_time[i];
        avg_turnaround_time += turnaround_time[i];
    }
    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);

    return 0;
}
