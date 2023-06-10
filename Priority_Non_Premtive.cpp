// Priority Scheduling Non Preemptive .


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

    // All tasks sorted in ascending oreder,
    // Since this is non premtive scheduling
    // We need to  need to insert the tasks into the job pool
    // queue which is sorted in highes ordert based on the pririty
    // Since at any moment the the competition is among the priprity

    priority_queue<pd, vector<pd>, myComp> Data;
    int timer = 0;

    int last = -1;
    vector<int>TimeCompletion;

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
            pd todo=Data.top();
            Data.pop();
            ganttChart.push_back(todo);
            timer+=todo.second.second;
            TimeCompletion.push_back(timer);
            
            }

        else
        {
            timer++;
        }
    }

// Printing the values:
 cout<<"Priority Scheduling Non-Premtive "<<endl;
    cout<<"Printing the Gantt Chart: The Order of Instructins Exceutions:"<<endl;
     for(int i=0;i<n;i++){
       
        cout<<ganttChart[i].first.first<<endl;
        
    }

    int value;
    
    cout << "PID" << " " << "Arrival_Time" << " " << "Burst_Time " << "  " << "Completion" << "  WT"<<"  RT"<<endl;
    for (int i = 0; i < n; i++) {
      
       value=TimeCompletion[i]-ganttChart[i].second.second;
        
        cout << ganttChart[i].first.first << "    " << ganttChart[i].second.first << "        " << ganttChart[i].second.second << "             " << TimeCompletion[i] <<"         "<< TimeCompletion[i]-ganttChart[i].second.second<<"      "<<value<<endl;
    }

}
