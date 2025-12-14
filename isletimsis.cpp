#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;


struct Process {
    string id;
    int arrivalTime;
    int burstTime;
    string priority;

    int waitingTime;
    int turnaroundTime;
    int remainingTime;
    bool completed;
};


int priorityValue(string p) {
    if (p == "high") return 1;
    if (p == "normal") return 2;
    return 3;
}


vector<Process> readCSV(string filename) {
    vector<Process> processes;
    ifstream file(filename);
    string line;

    getline(file, line); // header

    while (getline(file, line)) {
        stringstream ss(line);
        Process p;
        string temp;

        getline(ss, p.id, ',');
        getline(ss, temp, ',');
        p.arrivalTime = stoi(temp);
        getline(ss, temp, ',');
        p.burstTime = stoi(temp);
        getline(ss, p.priority, ',');

        p.waitingTime = 0;
        p.turnaroundTime = 0;
        p.remainingTime = p.burstTime;
        p.completed = false;

        processes.push_back(p);
    }

    file.close();
    return processes;
}

//FCFS 
void FCFS(vector<Process> p) {
    int time = 0;
    float totalWT = 0, totalTAT = 0;

    cout << "\n--- FCFS ---\n";

    for (auto &pr : p) {
        if (time < pr.arrivalTime)
            time = pr.arrivalTime;

        pr.waitingTime = time - pr.arrivalTime;
        time += pr.burstTime;
        pr.turnaroundTime = pr.waitingTime + pr.burstTime;

        totalWT += pr.waitingTime;
        totalTAT += pr.turnaroundTime;

        cout << pr.id << " WT=" << pr.waitingTime
             << " TAT=" << pr.turnaroundTime << endl;
    }

    cout << "Avg WT: " << totalWT / p.size() << endl;
    cout << "Avg TAT: " << totalTAT / p.size() << endl;
}

// SJF NON-PREEMPTIVE
void SJF_NonPreemptive(vector<Process> p) {
    int time = 0, done = 0;
    float totalWT = 0, totalTAT = 0;
    int n = p.size();

    cout << "\n--- SJF (Non-Preemptive) ---\n";

    while (done < n) {
        int idx = -1, minBurst = 1e9;

        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].arrivalTime <= time &&
                p[i].burstTime < minBurst) {
                minBurst = p[i].burstTime;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        p[idx].waitingTime = time - p[idx].arrivalTime;
        time += p[idx].burstTime;
        p[idx].turnaroundTime = p[idx].waitingTime + p[idx].burstTime;
        p[idx].completed = true;

        totalWT += p[idx].waitingTime;
        totalTAT += p[idx].turnaroundTime;
        done++;

        cout << p[idx].id << " WT=" << p[idx].waitingTime
             << " TAT=" << p[idx].turnaroundTime << endl;
    }

    cout << "Avg WT: " << totalWT / n << endl;
    cout << "Avg TAT: " << totalTAT / n << endl;
}

// SRTF 
void SRTF(vector<Process> p) {
    int time = 0, done = 0;
    float totalWT = 0, totalTAT = 0;
    int n = p.size();

    cout << "\n--- SJF (Preemptive / SRTF) ---\n";

    while (done < n) {
        int idx = -1, minRT = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= time && p[i].remainingTime > 0 &&
                p[i].remainingTime < minRT) {
                minRT = p[i].remainingTime;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        p[idx].remainingTime--;
        time++;

        if (p[idx].remainingTime == 0) {
            done++;
            p[idx].turnaroundTime = time - p[idx].arrivalTime;
            p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;

            totalWT += p[idx].waitingTime;
            totalTAT += p[idx].turnaroundTime;

            cout << p[idx].id << " WT=" << p[idx].waitingTime
                 << " TAT=" << p[idx].turnaroundTime << endl;
        }
    }

    cout << "Avg WT: " << totalWT / n << endl;
    cout << "Avg TAT: " << totalTAT / n << endl;
}

// PRIORITY NON-PREEMPTIVE
void Priority_NonPreemptive(vector<Process> p) {
    int time = 0, done = 0;
    float totalWT = 0, totalTAT = 0;
    int n = p.size();

    cout << "\n--- Priority (Non-Preemptive) ---\n";

    while (done < n) {
        int idx = -1, best = 1e9;

        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].arrivalTime <= time &&
                priorityValue(p[i].priority) < best) {
                best = priorityValue(p[i].priority);
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        p[idx].waitingTime = time - p[idx].arrivalTime;
        time += p[idx].burstTime;
        p[idx].turnaroundTime = p[idx].waitingTime + p[idx].burstTime;
        p[idx].completed = true;

        totalWT += p[idx].waitingTime;
        totalTAT += p[idx].turnaroundTime;
        done++;

        cout << p[idx].id << " WT=" << p[idx].waitingTime
             << " TAT=" << p[idx].turnaroundTime << endl;
    }

    cout << "Avg WT: " << totalWT / n << endl;
    cout << "Avg TAT: " << totalTAT / n << endl;
}

// PRIORITY PREEMPTIVE
void Priority_Preemptive(vector<Process> p) {
    int time = 0, done = 0;
    float totalWT = 0, totalTAT = 0;
    int n = p.size();

    cout << "\n--- Priority (Preemptive) ---\n";

    while (done < n) {
        int idx = -1, best = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= time && p[i].remainingTime > 0 &&
                priorityValue(p[i].priority) < best) {
                best = priorityValue(p[i].priority);
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        p[idx].remainingTime--;
        time++;

        if (p[idx].remainingTime == 0) {
            done++;
            p[idx].turnaroundTime = time - p[idx].arrivalTime;
            p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;

            totalWT += p[idx].waitingTime;
            totalTAT += p[idx].turnaroundTime;

            cout << p[idx].id << " WT=" << p[idx].waitingTime
                 << " TAT=" << p[idx].turnaroundTime << endl;
        }
    }

    cout << "Avg WT: " << totalWT / n << endl;
    cout << "Avg TAT: " << totalTAT / n << endl;
}

//  ROUND ROBIN 
void RoundRobin(vector<Process> p, int quantum) {
    queue<int> q;
    int time = 0, done = 0;
    float totalWT = 0, totalTAT = 0;
    int n = p.size();

    cout << "\n--- Round Robin ---\n";

    for (int i = 0; i < n; i++)
        q.push(i);

    while (!q.empty()) {
        int i = q.front();
        q.pop();

        if (p[i].remainingTime > quantum) {
            p[i].remainingTime -= quantum;
            time += quantum;
            q.push(i);
        } else if (p[i].remainingTime > 0) {
            time += p[i].remainingTime;
            p[i].remainingTime = 0;
            done++;

            p[i].turnaroundTime = time - p[i].arrivalTime;
            p[i].waitingTime = p[i].turnaroundTime - p[i].burstTime;

            totalWT += p[i].waitingTime;
            totalTAT += p[i].turnaroundTime;

            cout << p[i].id << " WT=" << p[i].waitingTime
                 << " TAT=" << p[i].turnaroundTime << endl;
        }
    }

    cout << "Avg WT: " << totalWT / n << endl;
    cout << "Avg TAT: " << totalTAT / n << endl;
}



int main() {
    vector<Process> p;

    p = readCSV("case1.csv"); FCFS(p);
    p = readCSV("case1.csv"); SJF_NonPreemptive(p);
    p = readCSV("case1.csv"); SRTF(p);
    p = readCSV("case1.csv"); Priority_NonPreemptive(p);
    p = readCSV("case1.csv"); Priority_Preemptive(p);
    p = readCSV("case1.csv"); RoundRobin(p, 4);

    return 0;
}