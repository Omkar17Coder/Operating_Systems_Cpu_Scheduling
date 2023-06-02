#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool Compare(const vector<int>& currAva, const vector<pair<string, pair<vector<int>, vector<int>>>>& Process, int counter) {
    const vector<int>& my = Process[counter].second.second;
    int n = currAva.size();

    for (int i = 0; i < n; i++) {
        if (currAva[i] < my[i]) {
            return false;
        }
    }

    return true;
}

void Allot(vector<int>& currAva, const vector<pair<string, pair<vector<int>, vector<int>>>>& Process, int counter) {
    const vector<int>& allocated = Process[counter].second.first;
    int m = currAva.size();

    for (int i = 0; i < m; i++) {
        currAva[i] += allocated[i];
    }
}

int main() {
    int n, m;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the number of resources: ";
    cin >> m;

    vector<int> resource(m);
    cout << "Enter the maximum availability for each resource: ";
    for (int i = 0; i < m; i++) {
        cin >> resource[i];
    }

    vector<int> currAva = resource;

    vector<pair<string, pair<vector<int>, vector<int>>>> Process(n);

    for (int i = 0; i < n; i++) {
        string task = "P" + to_string(i + 1);

        cout << "Enter the allocated resources for process " << task << ": ";
        vector<int> allocated(m);
        for (int j = 0; j < m; j++) {
            cin >> allocated[j];
            currAva[j] -= allocated[j];
        }

        cout << "Enter the maximum required resources for process " << task << ": ";
        vector<int> maxreq(m);
        for (int j = 0; j < m; j++) {
            cin >> maxreq[j];
        }

        vector<int> request(m);
        for (int j = 0; j < m; j++) {
            request[j] = maxreq[j] - allocated[j];
        }

        Process[i] = make_pair(task, make_pair(allocated, request));
    }

    // All input done

    vector<string> ans;
    
    cout<<"All input sdone"<<endl;


    bool flag1 = false;
    bool flag2 = true;
    int counter = 0;
    int maincounter = 0;
     int ProcessSize = Process.size();
    while (Process.size() != 0) {
        int x = Process.size();

        maincounter = 0;
        counter=0;

        for (int i = 0; i < x; i++) {
            bool check = Compare(currAva, Process, counter);
            if (check) {
                // True means we can complete the process
                flag1 = true;
                Allot(currAva, Process, counter);
                ans.push_back(Process[counter].first);
                Process.erase(Process.begin()+counter);
                ProcessSize--;

                cout << "Allotted the Process " << Process[counter].first << endl;
                cout << endl;
                
                break;

            } 
           else {
                maincounter++;
                counter++;
            
            }
        }

        if (maincounter == x) {
            cout << "Deadlock detected." << endl;
            flag2 = false;
            break;
        }
         ProcessSize = Process.size();
    }

    
        cout << "No deadlock detected." << endl;
        cout << "Execution sequence: ";
        for (int i = 0; i < ans.size(); i++) {
            cout << ans[i];
            if (i != ans.size() - 1) {
                cout << " -> ";
            }
        }
     
        cout << endl;
    cout<<"Coding Done";


    return 0;
}
