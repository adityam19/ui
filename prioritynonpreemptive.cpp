#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct Process {
    int pid;
    int at;
    int bt;
    int pr;
    int ft;
    int tat;
    int wt;
    bool done;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<Process> p(n);

    // ---- SIMPLIFIED INPUT (one value at a time) ----
    for (int i = 0; i < n; ++i) {
        p[i].pid = i + 1;

        cout << "\nEnter Arrival Time of P" << p[i].pid << ": ";
        cin >> p[i].at;

        cout << "Enter Burst Time of P" << p[i].pid << ": ";
        cin >> p[i].bt;

        cout << "Enter Priority of P" << p[i].pid << ": ";
        cin >> p[i].pr;

        p[i].done = false;
        p[i].ft = p[i].tat = p[i].wt = 0;
    }

    // ---- SORT BY ARRIVAL TIME ----
    sort(p.begin(), p.end(), [](const Process &a, const Process &b) {
        return a.at < b.at;
    });

    int completed = 0, current_time = 0;
    double total_tat = 0, total_wt = 0;

    if (n > 0) current_time = p[0].at;

    // ---- MAIN PRIORITY SCHEDULING LOOP ----
    while (completed < n) {
        int idx = -1;

        for (int i = 0; i < n; ++i) {
            if (!p[i].done && p[i].at <= current_time) {
                if (idx == -1 || p[i].pr < p[idx].pr ||
                   (p[i].pr == p[idx].pr && p[i].at < p[idx].at) ||
                   (p[i].pr == p[idx].pr && p[i].at == p[idx].at && p[i].pid < p[idx].pid))
                {
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            int next_at = INT_MAX;
            for (int i = 0; i < n; ++i)
                if (!p[i].done)
                    next_at = min(next_at, p[i].at);
            current_time = next_at;
            continue;
        }

        // Execute selected process
        current_time += p[idx].bt;
        p[idx].ft = current_time;
        p[idx].tat = p[idx].ft - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].done = true;

        total_tat += p[idx].tat;
        total_wt += p[idx].wt;
        completed++;
    }

    // ---- OUTPUT ---- / (031,174,262,315,523)
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
