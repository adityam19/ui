#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

struct Process {
    int pid;
    int at;    // arrival time
    int bt;    // burst time
    int pr;    // priority (lower = higher priority)
    int rem;   // remaining burst time
    int ft;    // finish time
    int tat;   // turnaround time
    int wt;    // waiting time
    bool started;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<Process> p(n);

    // -------------------------------
    // SIMPLE INPUT (one-by-one)
    // -------------------------------
    for (int i = 0; i < n; ++i) {
        p[i].pid = i + 1;

        cout << "\nEnter Arrival Time of P" << p[i].pid << ": ";
        cin >> p[i].at;

        cout << "Enter Burst Time of P" << p[i].pid << ": ";
        cin >> p[i].bt;

        cout << "Enter Priority of P" << p[i].pid << ": ";
        cin >> p[i].pr;

        p[i].rem = p[i].bt;
        p[i].ft = p[i].tat = p[i].wt = 0;
        p[i].started = false;
    }

    // Find earliest arrival time
    int current_time = numeric_limits<int>::max();
    for (int i = 0; i < n; ++i)
        current_time = min(current_time, p[i].at);

    int completed = 0;
    double total_tat = 0, total_wt = 0;

    // -------------------------------
    // PREEMPTIVE PRIORITY SIMULATION
    // -------------------------------
    while (completed < n) {

        int idx = -1;

        // Find highest-priority among arrived processes
        for (int i = 0; i < n; ++i) {
            if (p[i].rem > 0 && p[i].at <= current_time) {

                if (idx == -1) idx = i;
                else {
                    // priority check
                    if (p[i].pr < p[idx].pr) idx = i;

                    // tie-breaker: earlier arrival
                    else if (p[i].pr == p[idx].pr && p[i].at < p[idx].at) idx = i;

                    // tie-breaker: smaller PID
                    else if (p[i].pr == p[idx].pr && p[i].at == p[idx].at &&
                             p[i].pid < p[idx].pid) idx = i;
                }
            }
        }

        // If no process is available, move to next arrival
        if (idx == -1) {
            int next_at = numeric_limits<int>::max();
            for (int i = 0; i < n; ++i)
                if (p[i].rem > 0)
                    next_at = min(next_at, p[i].at);

            current_time = next_at;
            continue;
        }

        // Run the process for 1 time unit (preemptive)
        p[idx].rem -= 1;
        p[idx].started = true;

        // If process finishes now
        if (p[idx].rem == 0) {
            p[idx].ft = current_time + 1;
            p[idx].tat = p[idx].ft - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            total_tat += p[idx].tat;
            total_wt += p[idx].wt;

            completed++;
        }

        current_time++;
    }

    // -------------------------------
    // SORT BY PID for clean output
    // -------------------------------
    sort(p.begin(), p.end(), [](const Process &a, const Process &b) {
        return a.pid < b.pid;
    });

    // -------------------------------
    // OUTPUT                                 /(054,143,222,411)
    // -------------------------------
    cout << "\nPID\tAT\tBT\tPR\tFT\tTAT\tWT\n";
    for (int i = 0; i < n; ++i) {
        cout << p[i].pid << "\t" 
             << p[i].at << "\t" 
             << p[i].bt << "\t"
             << p[i].pr << "\t"
             << p[i].ft << "\t"
             << p[i].tat << "\t"
             << p[i].wt << "\n";
    }

    cout << "\nAverage Turnaround Time = " << total_tat / n << endl;
    cout << "Average Waiting Time    = " << total_wt / n << endl;

    return 0;
}
