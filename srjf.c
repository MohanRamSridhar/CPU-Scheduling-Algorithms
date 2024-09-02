#include <stdio.h>
#include <limits.h>

int findShortestRemainingTime(int remaining_time[], int n, int current_time, int arrival_time[]) {
    int min_time = INT_MAX;
    int shortest = -1;
    for (int i = 0; i < n; i++) {
        if (arrival_time[i] <= current_time && remaining_time[i] < min_time && remaining_time[i] > 0) {
            min_time = remaining_time[i];
            shortest = i;
        }
    }
    return shortest;
}

int main() {
    int n, i;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int burst_time[n], arrival_time[n], remaining_time[n], waiting_time[n], turnaround_time[n];
    printf("Enter the burst time and arrival time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d - Burst Time: ", i + 1);
        scanf("%d", &burst_time[i]);
        printf("Process %d - Arrival Time: ", i + 1);
        scanf("%d", &arrival_time[i]);
        remaining_time[i] = burst_time[i];
    }

    int complete = 0, current_time = 0, shortest;
    int finish_time;
    while (complete != n) {
        shortest = findShortestRemainingTime(remaining_time, n, current_time, arrival_time);
        if (shortest == -1) {
            current_time++;
            continue;
        }

        remaining_time[shortest]--;

        if (remaining_time[shortest] == 0) {
            complete++;
            finish_time = current_time + 1;
            waiting_time[shortest] = finish_time - burst_time[shortest] - arrival_time[shortest];
            if (waiting_time[shortest] < 0) {
                waiting_time[shortest] = 0;
            }
            turnaround_time[shortest] = finish_time - arrival_time[shortest];
        }
        current_time++;
    }

    printf("\nProcess\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i], arrival_time[i], waiting_time[i], turnaround_time[i]);
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
