#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define MAX_N 15'000
using namespace std;

struct SEATS { int pos; int to_eat; };
SEATS S[MAX_N + 5];

int L, Q;
int name_cnt;
int st, et;

vector <int> v[MAX_N + 5];
unordered_map <string, int> name_index;

void belt_move() {
    
    if (!st)
        return;
    
    for (int i = 1; i <= name_cnt; ++i) {
        
        int time_gap = et - st;
        vector <int> tmp1;
        vector <int> tmp2;
        
        for (auto j : v[i]) {
            int n = S[i].to_eat;
            j += time_gap;
            if (n && j >= S[i].pos) {
                S[i].to_eat--;
                continue;
            }
            else {
                if (j >= L) tmp2.push_back(j % L);
                else tmp1.push_back(j);
            }
            
            
        }
        v[i].clear();
        for (auto j : tmp1) v[i].push_back(j);
        for (auto j : tmp2) v[i].push_back(j);
        
    }
}

void print_progress() {
    cout << "et: " << et << '\n';
    for (int i = 1; i <= name_cnt; ++i) {
        cout << i << ": " << S[i].pos << ' ' << S[i].to_eat << '\n';
    }
    for (int i = 1; i <= name_cnt; ++i) {
        for (auto j : v[i])
            cout << j << ' ';
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
            
            //print_progress();
            if (!name_index[name]) name_index[name] = ++name_cnt;
            
            int n = name_index[name];
            v[n].push_back(x);
        }
        
        else if (cmd == 200) {
            int t, x, n; string name;
            cin >> t >> x >> name >> n;
            st = et; et = t;
            
            belt_move();
            
            //print_progress();
            
            if (!name_index[name]) name_index[name] = ++name_cnt;
            
            int ni = name_index[name];
            S[ni] = { x, n };
            
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
                b += v[i].size();
            }
            
            cout << a << ' ' << b << '\n';
        }
        
    }
    
    return 0;
}