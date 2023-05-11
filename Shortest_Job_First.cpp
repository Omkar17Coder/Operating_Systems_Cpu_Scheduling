
// Final Shortest Job First ALgorithmn
// This is important 



#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

using namespace std;

typedef pair<string, pair<int, int>> pd;

struct myComp {
    const bool operator()(
        pair<string, pair<int, int>> const &a,
        pair<string, pair<int, int>> const &b)
        const noexcept
    {
        return a.second.second > b.second.second;
    }
};

bool cmp(const pair<string, pair<int, int>> &a, const pair<string, pair<int, int>> &b) {
    return a.second.first < b.second.first;
}

int main() {
    int n;
    cin >> n;

    vector<pair<string, pair<int, int>>> tasks;
    int a, b;
    for (int i = 0; i < n; i++) {
        cin >> a >> b;
        string taskNo = "P" + to_string(i + 1);
        tasks.push_back({taskNo, {a, b}});
    }

    vector<pair<string, pair<int, int>>> ganttChart;
    sort(tasks.begin(), tasks.end(), cmp);

    priority_queue<pd, vector<pd>, myComp> Data;

    vector<int> TimeCompletion;
    int lastProcessed = -1; 
    int timer = 0;

    while (lastProcessed < n - 1 || !Data.empty()) { 
        for (int i = lastProcessed + 1; i < n; i++) {
            if (tasks[i].second.first <= timer) {
                Data.push(tasks[i]);
               lastProcessed = i;
            }
        }

        
        if (!Data.empty()) {
            pd taskToDo = Data.top();
            Data.pop();
            ganttChart.push_back(taskToDo);
            timer += taskToDo.second.second;
            TimeCompletion.push_back(timer);
        } else {
            timer++;
        }
    }

    // Printing the values
    cout<<"Printing the Gantt Chart: The Order of Instructins Exceutions:"<<endl;
    \
    
    
    cout << "PID" << " " << "Arrival_Time" << " " << "Burst_Time " << "  " << "Time of Completion" << endl;
    for (int i = 0; i < n; i++) {
        cout << ganttChart[i].first << "    " << ganttChart[i].second.first << "        " << ganttChart[i].second.second << "             " << TimeCompletion[i] << endl;
    }
    return 0;
}
