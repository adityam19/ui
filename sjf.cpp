#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int pid;
    int AT;
    int BT;
    int FT;
    int TAT;
    int WT;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "Arrival Time of P" << i+1 << ": ";
        cin >> p[i].AT;
        cout << "Burst Time of P" << i+1 << ": ";
        cin >> p[i].BT;
    }

    // Step 1: Sort by arrival time
    sort(p.begin(), p.end(), [](Process a, Process b){
        return a.AT < b.AT;
    });

    int completed = 0, t = 0;
    vector<bool> done(n, false);

    // Step 2: SJF Non-Preemptive Loop
    while (completed < n) {

        int idx = -1;
        int minBT = 1e9;

        // Step 2a: Pick the process with smallest BT among arrived ones
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].AT <= t && p[i].BT < minBT) {
                minBT = p[i].BT;
                idx = i;
            }
        }

        // Step 3: CPU is idle
        if (idx == -1) {
            t++;
            continue;
        }

        // Step 4: Execute process fully (Non-preemptive)
        t += p[idx].BT;
        p[idx].FT  = t;
        p[idx].TAT = p[idx].FT - p[idx].AT;
        p[idx].WT  = p[idx].TAT - p[idx].BT;

        done[idx] = true;
        completed++;
    }

    // Step 5: Display output / 1 3 2 4 1 2 4 4 
    cout << "\nPID\tAT\tBT\tFT\tTAT\tWT\n";
    float avgTAT = 0, avgWT = 0;

    for (auto &pr : p) {
        avgTAT += pr.TAT;
        avgWT += pr.WT;

        cout << pr.pid << "\t" << pr.AT << "\t" << pr.BT
             << "\t" << pr.FT << "\t" << pr.TAT << "\t" << pr.WT << "\n";
    }

    cout << "\nAverage TAT = " << avgTAT / n;
    cout << "\nAverage WT  = " << avgWT / n << "\n";

    return 0;
}
