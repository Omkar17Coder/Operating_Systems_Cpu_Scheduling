// First Come FIRST SERVE


#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

bool cmp(const pair<string,pair<int,int>> &a , const pair<string,pair<int,int>> &b ){
    return a.second.first < b.second.first;
}

int main() {
    int n;
    cin >> n;

    vector<pair<string,pair<int,int>>> tasks;
    int a, b;
    for(int i=0; i<n; i++){
        cin >> a >> b;
        string taskNo = "P" + to_string(i+1);
        tasks.push_back({taskNo,{a,b}});
    }

    sort(tasks.begin(),tasks.end(),cmp);

    vector<pair<string,pair<int,int>>> ganttChart;
    vector<int> timeCompletion;
    int time = 0;
    for(int i=0; i<n; i++){
        time += tasks[i].second.second;
        string name = tasks[i].first;
        timeCompletion.push_back(time);
        ganttChart.push_back({tasks[i].first,{tasks[i].second.first,tasks[i].second.second}});
    }

    vector<int> turnAroundTime;
    for(int i=0; i<n; i++){
        int value = timeCompletion[i] - tasks[i].second.first;
        turnAroundTime.push_back(value);
    }
    
    
    // Printing the values
    
    
    
    cout<<"PID"<<" "<<"Arrival Time"<<" "<<"Burst Time "<<"  "<<"Time of timeCompletion"<<endl;
    for(int i=0;i<n;i++){
        cout<<tasks[i].first<<" "<<tasks[i].second.first<<"  "<<tasks[i].second.second<<"  "<<timeCompletion[i]<<endl;
        
    }
    return 0;
}

