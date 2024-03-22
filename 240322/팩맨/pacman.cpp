#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
using namespace std;

struct POS { int sum; int d1, d2, d3; };

struct cmp {
    bool operator()(POS a, POS b) {
        if (a.sum == b.sum) {
            if (a.d1 == b.d1) {
                if (a.d2 == b.d2) 
                    return a.d3 > b.d3;
                return a.d2 > b.d2;
            }
            return a.d1 > b.d1;
        }
        return a.sum < b.sum;
    }
};

int m, t;
int py, px;
int ans;
vector <int> Map[5][5];
vector <int> egg[5][5];
bool visited[5][5];
int dead[5][5];

priority_queue <POS, vector<POS>, cmp> pq;

const int dy[9] = {0, -1, -1, 0, 1, 1, 1, 0, -1};
const int dx[9] = {0, 0, -1, -1, -1, 0, 1, 1, 1};

void input() {
    cin >> m >> t >> py >> px;
    for (int i = 0; i < m; ++i) {
        int y, x, d;
        cin >> y >> x >> d;
        Map[y][x].push_back(d);
    }
}

void monster_copy() {
    
    for (int i = 1; i <= 4; ++i) {
        for (int j = 1; j <= 4; ++j)
            egg[i][j].clear();
    }
    
    for (int i = 1; i <= 4; ++i) {
        for (int j = 1; j <= 4; ++j) {
            for (auto k : Map[i][j]) 
                egg[i][j].push_back(k);
        }
    }
    
}

void monster_move() {
    
    vector <int> tmp[5][5];
    
    for (int i = 1; i <= 4; ++i) {
        for (int j = 1; j <= 4; ++j) {
            for (auto d : Map[i][j]) {
                
                bool can_move = false;
                for (int k = 0; k < 8; ++k) {
                    
                    int dir = (d + k) % 8;
                    if (!dir) dir = 8;
                    
                    int ny = i + dy[dir];
                    int nx = j + dx[dir];
                    
                    if (ny < 1 || ny > 4 || nx < 1 || nx > 4)
                        continue;
                    if ((ny == py && nx == px) || dead[ny][nx])
                        continue;
                    
                    can_move = true;
                    tmp[ny][nx].push_back(dir);
                    break;
                }
                
                if (!can_move)
                    tmp[i][j].push_back(d);
                
            }
        }
    }
    
    for (int i = 1; i <= 4; ++i) {
        for (int j = 1; j <= 4; ++j)
            Map[i][j].clear();
    }
    
    for (int i = 1; i <= 4; ++i) {
        for (int j = 1; j <= 4; ++j){
            for (auto k : tmp[i][j]) 
                Map[i][j].push_back(k);
        }
    }

}

void dfs(int sum, int cnt, int y, int x, int d1, int d2, int d3) {
    
    if (cnt == 3) {
        pq.push({sum, d1, d2, d3});
        return;
    }
    
    for (int i = 1; i < 8; i += 2) {
            
        int ny = y + dy[i];
        int nx = x + dx[i];
            
        if (ny < 1 ||  ny > 4 || nx < 1 || nx > 4)
            continue;
        if (visited[ny][nx])
            continue;
        
        if (cnt == 0) d1 = i;
        else if (cnt == 1) d2 = i;
        else if (cnt == 2) d3 = i;
            
        int ns = sum + Map[ny][nx].size();
        visited[ny][nx] = true;
        dfs(ns, cnt + 1, ny, nx, d1, d2, d3);
        visited[ny][nx] = false;
    }
}

void pacman_move() {
    
    priority_queue <POS, vector<POS>, cmp> pq_tmp;
    pq = pq_tmp;
    memset(visited, false, sizeof(visited));
    
    visited[py][px] = true;
    dfs(0, 0, py, px, 0, 0, 0);
    
    int a1 = pq.top().d1;
    int a2 = pq.top().d2;
    int a3 = pq.top().d3;
    
    //cout << "dir: " << a1 << ' ' << a2 << ' ' << a3 << '\n';
    
    py += dy[a1]; px += dx[a1];
    if (Map[py][px].size() != 0) dead[py][px] = 3;
    Map[py][px].clear();
    
    py += dy[a2]; px += dx[a2];
    if (Map[py][px].size() != 0) dead[py][px] = 3;
    Map[py][px].clear();
    
    py += dy[a3]; px += dx[a3];
    if (Map[py][px].size() != 0) dead[py][px] = 3;
    Map[py][px].clear();
    
}

void dead_check() {
    for (int i = 1; i <= 4; ++i) {
        for (int j = 1; j <= 4; ++j) {
            if (dead[i][j])
                dead[i][j]--;
        }
    }
}

void egg_hatch() {
    for (int i = 1; i <= 4; ++i) {
        for (int j = 1; j <= 4; ++j) {
            for (auto k : egg[i][j]) 
                Map[i][j].push_back(k);
        }
    }
}

void print_progress() {
    for (int i = 1; i <= 4; ++i) {
        for (int j = 1; j <= 4; ++j) {
            if (Map[i][j].size()) {
                for (auto k : Map[i][j])
                    cout << i << ' ' << j << ' ' << k << '\n';
            }
        }
    }
    cout << '\n';
}

void solve() {
    while (t--) {
        //cout << t << ':' << '\n';
        monster_copy();
        //print_progress();
        monster_move();
        //print_progress();
        pacman_move();
        //print_progress();
        dead_check();
        //print_progress();
        egg_hatch();
        //print_progress();
    }
}

void output() {
    
    for (int i = 1; i <= 4; ++i) {
        for (int j = 1; j <= 4; ++j) 
            ans += Map[i][j].size();
    }
    
    cout << ans << '\n';
}

int main() {
    
    fastio;
    input();
    solve();
    output();

    return 0;
}