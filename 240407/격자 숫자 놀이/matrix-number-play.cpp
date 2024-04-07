#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
using namespace std;

int r, c, k;
int row_size = 3, col_size = 3;

int ans;
int A[105][105];
int cnt[105];

bool cmp(int a, int b) {
    if (cnt[a] == cnt[b])
        return a < b;
    return cnt[a] < cnt[b];
}

void print_progress() {
    for (int i = 1; i <= row_size; ++i) {
        for (int j = 1; j <= col_size; ++j)
            cout << A[i][j] << ' ';
        cout << '\n';
    }
    cout << '\n';
}

void input() {
    cin >> r >> c >> k;
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 3; ++j)
            cin >> A[i][j];
    }
}

void row_sort() {
    
    for (int i = 1; i <= row_size; ++i) {
        
        memset(cnt, 0, sizeof(cnt));
        
        int max_num = 0;
        for (int j = 1; j <= col_size; ++j) {
            if (A[i][j]) cnt[A[i][j]]++;
            max_num = max(max_num, A[i][j]);
        }
        
        vector <int> v1;
        for (int j = 1; j <= max_num; ++j) {
            if (cnt[j]) v1.push_back(j);
        }
        sort(v1.begin(), v1.end(), cmp);
        
        int c = 1;
        for (auto j : v1) {
            if (c == 101) break;
            A[i][c++] = j;
            A[i][c++] = cnt[j];
        }
        
        for (int j = c; j <= col_size; ++j)
            A[i][j] = 0;
        
        
        col_size = max(col_size, c);
    }
}

void col_sort() {
    
    for (int j = 1; j <= col_size; ++j) {
        
        memset(cnt, 0, sizeof(cnt));
        
        int max_num = 0;
        for (int i = 1; i <= row_size; ++i) {
            if (A[i][j]) cnt[A[i][j]]++;
            max_num = max(max_num, A[i][j]);
        }
        
        vector <int> v1;
        for (int i = 1; i <= max_num; ++i) {
            if (cnt[i]) v1.push_back(i);
        }
        sort(v1.begin(), v1.end(), cmp);
        
        int c = 1;
        for (auto i : v1) {
            if (c == 101) break;
            A[c++][j] = i;
            A[c++][j] = cnt[i];
        }
        
        for (int i = c; i <= row_size; ++i)
            A[i][j] = 0;
        
        
        row_size = max(row_size, c);
        
    }
}

void solve() {
    int turn = 0;
    //print_progress();
    while (++turn <= 100) {
        if (row_size >= col_size) 
            row_sort();
        else 
            col_sort();
        
        //print_progress();        
        if (A[r][c] == k) {
            ans = turn;
            return;
        }
    }
    ans = -1;
}

void output() {
    cout << ans << '\n';
}

int main() {
    
    fastio;
    input();
    solve();
    output();
    
    return 0;
}