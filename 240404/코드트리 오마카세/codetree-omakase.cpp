#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define MAX_N 15'000
using namespace std;

struct SEATS { int pos; int to_eat; };
SEATS S[MAX_N + 5];

int L, Q;
int name_cnt;
int st, et;

priority_queue <int, vector<int>, greater<int>> pq[MAX_N + 5];
unordered_map <string, int> name_index;

void belt_move() {
    
    if (!st)
        return;
    
    for (int i = 1; i <= name_cnt; ++i) {
        
        int time_gap = et - st;
        priority_queue <int, vector<int>, greater<int>> tmp;
        
        while (!pq[i].empty()) {
            int n = S[i].to_eat;
            int j = pq[i].top();
            pq[i].pop();
            
            j += time_gap;
            if (n && j >= S[i].pos) 
                S[i].to_eat--;
            
            else 
                tmp.push(j % L);
            
        }
        
        pq[i] = tmp;
        
    }
}

void print_progress() {
    cout << "et: " << et << '\n';
    for (int i = 1; i <= name_cnt; ++i) {
        cout << i << ": " << S[i].pos << ' ' << S[i].to_eat << '\n';
    }
    for (int i = 1; i <= name_cnt; ++i) {
        while (!pq[i].empty()) {
            cout << pq[i].top() << ' ';
            pq[i].pop();
        }
        cout << '\n';
    }
    //cout << '\n';
}


int main() {
    
    fastio;
    cin >> L >> Q;
    
    for (int i = 0; i < Q; ++i) {
        int cmd; cin >> cmd;
        if (cmd == 100) {
            int t, x; string name;
            cin >> t >> x >> name;
            st = et; et = t;
            
            belt_move();
            
            if (!name_index[name]) name_index[name] = ++name_cnt;
            
            int n = name_index[name];
            pq[n].push(x);
            
            //print_progress();
        }
        
        else if (cmd == 200) {
            int t, x, n; string name;
            cin >> t >> x >> name >> n;
            st = et; et = t;
            
            belt_move();
            
            
            if (!name_index[name]) name_index[name] = ++name_cnt;
            
            int ni = name_index[name];
            S[ni] = { x, n };
            
            
            //print_progress();
        }
        
        else {
            int t;
            cin >> t;
            st = et; et = t;
            
            belt_move();
            
            //print_progress();
            
            int a = 0, b = 0;
            for (int i = 1; i <= name_cnt; ++i) {
                if (S[i].to_eat) a++;
                b += pq[i].size();
            }
            
            cout << a << ' ' << b << '\n';
        }
        
    }
    
    return 0;
}