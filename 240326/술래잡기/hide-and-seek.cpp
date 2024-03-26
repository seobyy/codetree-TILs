#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define MAX_N 99
using namespace std;

// 1 우 2 하 3 좌 4 상
const int dy[5] = {0, 0, 1, 0, -1};
const int dx[5] = {0, 1, 0, -1, 0};

int n, m, h, k;
int ty, tx, td;
int turn = 1;
int ans;
bool check;

vector <int> Map[MAX_N + 5][MAX_N + 5];
bool tree[MAX_N + 5][MAX_N + 5];
int tag_dir1[MAX_N + 5][MAX_N + 5];
int tag_dir2[MAX_N + 5][MAX_N + 5];

void input() {
    cin >> n >> m >> h >> k;
    for (int i = 0; i < m; ++i) {
        int x, y, d; 
        cin >> y >> x >> d;
        Map[y - 1][x - 1].push_back(d);
    }
    for (int i = 0; i < h; ++i) {
        int y, x; cin >> y >> x;
        tree[y - 1][x - 1] = true;
    }
}

void make_tagger_dir() {
    
    int i = 0, j = 0;
    tag_dir1[i][j] = 4;
    tag_dir2[i][j] = 2;
    while (1) {
        bool can_move = false;
        while (i + 1 < n && !tag_dir1[i + 1][j] ) {
            i++;
            tag_dir1[i][j] = 4;
            if (i == n - 1 || tag_dir1[i + 1][j]) tag_dir2[i][j] = 1;
            else tag_dir2[i][j] = 2;
            can_move = true;
        }
        while (j + 1 < n && !tag_dir1[i][j + 1]) {
            j++;
            tag_dir1[i][j] = 3;
            tag_dir2[i][j] = 1;
            if (j == n - 1 || tag_dir2[i][j + 1]) tag_dir2[i][j] = 4;
            can_move = true;
        }
        while (i - 1 >= 0 && !tag_dir1[i - 1][j]) {
            i--;
            tag_dir1[i][j] = 2;
            if (!i || tag_dir1[i - 1][j]) tag_dir2[i][j] = 3;
            else tag_dir2[i][j] = 4;
            can_move = true;
        }
        while (j - 1 >= 0 && !tag_dir1[i][j - 1]) {
            j--;
            tag_dir1[i][j] = 1;
            if (!j || tag_dir1[i][j - 1]) tag_dir2[i][j] = 2;
            else tag_dir2[i][j] = 3;
            can_move = true;
        }
        
        if (!can_move)
            break;
    }
    
    ty = n / 2; tx = n / 2;
    td = tag_dir1[ty][tx];
    
}

void runner_move() {
    
    vector <int> tmp[MAX_N + 5][MAX_N + 5];
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            
            int dis = abs(i - ty) + abs(j - tx);
            if (dis > 3)
                continue;
            
            for (auto k : Map[i][j]) {
                
                int ny = i + dy[k];
                int nx = j + dx[k];
                
                if (ny < 0 || ny >= n || nx < 0 || nx >= n) {
                    int dir = (k + 2) % 4;
                    if (!dir) dir = 4;
                    
                    int ny2 = i + dy[dir];
                    int nx2 = j + dx[dir];
                    
                    if (ny2 == ty && nx2 == tx)
                        tmp[i][j].push_back(dir);
                    else
                        tmp[ny2][nx2].push_back(dir);
                    
                }
                
                else {
                    if (ny == ty && nx == tx)
                        tmp[i][j].push_back(k);
                    else
                        tmp[ny][nx].push_back(k);
                }
                
            }
        }
    }
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            Map[i][j].clear();
    }
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (auto k : tmp[i][j])
                Map[i][j].push_back(k);
        }
    }
    
}

void tagger_move() {
    
    ty += dy[td];
    tx += dx[td];
    
    if (!check && ty == 0 && tx == 0) 
        check = !check;
    else if (check && ty == n / 2 && tx == n / 2)
        check = !check;
    
    if (!check) td = tag_dir1[ty][tx];
    else td = tag_dir2[ty][tx];
}

void tagger_catch() {
    for (int i = 0; i < 3; ++i) {
        int ny = ty + dy[td] * i;
        int nx = tx + dx[td] * i;
        
        if (!tree[ny][nx] && Map[ny][nx].size()) {
            ans += turn * Map[ny][nx].size();
            Map[ny][nx].clear();
        }
    }
}

void print_dir() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            cout << tag_dir1[i][j];
        cout << '\n';
    }
    cout << '\n';
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            cout << tag_dir2[i][j];
        cout << '\n';
    }
    cout << '\n';
}


void solve() {
    make_tagger_dir();
    //print_dir();
    
    while (turn <= k) {
        runner_move();
        /*
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (auto k : Map[i][j]) {
                    cout << i << ' ' << j << ' ' << k << '\n';
                }
            }
        }
        */
        tagger_move();
        //cout << ty << ' ' << tx << '\n';
        tagger_catch();
        
        turn++;
    }
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