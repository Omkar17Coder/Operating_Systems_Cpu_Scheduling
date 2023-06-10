Priority Scheduling Primitive .

#include <iostream>    
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

using namespace std;

typedef pair<pair<string, int>, pair<int, int>> pd;
// {name,priority} {at,bt}

struct myComp
{
    constexpr bool operator()(
        pd &a,
        pd &b)
        const noexcept
    {
        return a.first.second < b.first.second;
    }
};

bool cmp(const pd &a, const pd &b)
{
    return a.second.first < b.second.first;
}

int main()
{
    int n;
    cin >> n;
    vector<pd> tasks;
    int a, b, c;
    for (int i = 0; i < n; i++)
    {
        cin >> a >> b >> c;
        string taskNo = "P" + to_string(i + 1);
        tasks.push_back({{taskNo, c}, {a, b}});
    }

    vector<pd> ganttChart;
    sort(tasks.begin(), tasks.end(), cmp);

    priority_queue<pd, vector<pd>, myComp> Data;
    int timer = 0;

    int last = -1;
    vector<pair<string, int>> TimeCompletion;

    while (last < n - 1 || !Data.empty())
    {
        for (int i = last + 1; i < n; i++)
        {
            if (tasks[i].second.first <= timer)
            {
                Data.push(tasks[i]);
                last = i;
            }
        }

        if (!Data.empty())
        {

            pd todo = Data.top();
            Data.pop();
            timer++;
            ganttChart.push_back(todo);
            todo.second.second -= 1;
            if (todo.second.second <= 0)
            {
                TimeCompletion.push_back({todo.first.first, timer});
            }
            else
            {
                Data.push(todo);
            }
        }

        else
        {
            timer++;
        }
    }
    cout << "Priority Schedulign Premtive" << endl;
    cout << "Printing the Gantt Chart: The Order of Instructins Exceutions:" << endl;
    int x=ganttChart.size();
    for (int i = 0; i < x; i++)
    {

        cout << ganttChart[i].first.first << endl;
    }

    int value;

    cout << "PID"
         << " "
         << "Arrival_Time"
         << " "
         << "Burst_Time "
         << "  "
         << "Completion"
         << "  WT"
         << "  RT" << endl;
    for (int i = 0; i < n; i++)
    {

        cout << ganttChart[i].first.first << "    " << ganttChart[i].second.first << "        " << ganttChart[i].second.second << "             " <<endl;
        
    }
    cout<<"Printing the completion time of each tasks:"<<endl;
    int z=TimeCompletion.size();
    for(int i=0;i<z;i++){
        cout<<TimeCompletion[i].first<<"   "<<TimeCompletion[i].second<<endl;
        
    }

    return 0;
}
