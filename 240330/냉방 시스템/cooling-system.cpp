#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL) 
using namespace std;

struct POS { int power; int y, x;};

int n, m, k;
int ans;
int Map[25][25];

bool office[25][25];
bool wall1[25][25]; // 세로방향 wall
bool wall2[25][25]; // 가로방향 wall
int air_con[25][25];
bool visited[25][25];

// x 왼 위 오 아  
const int dy[5] = {0, 0, -1, 0, 1};
const int dx[5] = {0, -1, 0, 1, 0};

void print_map() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) 
            cout << Map[i][j] << ' ';
        cout << '\n';
    }
    cout << '\n';
}

void input() {
    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int x; cin >> x;
            if (x == 1) 
                office[i][j] = true;
            else if (x) 
                air_con[i][j] = x - 1;
        }
    }
    for (int i = 0; i < m; ++i) {
        int y, x, s;
        cin >> y >> x >> s;
        if (!s) 
            wall1[y - 1][x - 1] = true;
        else
            wall2[y - 1][x - 1] = true;
    }

}

bool is_in_map(int y, int x) {
    if (y < 0 || y >= n || x < 0 || x >= n)
        return false;
    else
        return true;
}

void air_con_move() {
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (air_con[i][j]) {
                
                memset(visited, false, sizeof(visited));
                
                int dir = air_con[i][j];
                
                int ny = i + dy[dir];
                int nx = j + dx[dir];
                
                queue <POS> q;
                q.push({5, ny, nx});
                
                while (!q.empty()) {
                    int p = q.front().power;
                    int y = q.front().y;
                    int x = q.front().x;
                    q.pop();
                    
                    if (!p)
                        continue;
                    if (visited[y][x])
                        continue;
                        
                    visited[y][x] = true;
                    
                    Map[y][x] += p;
                    
                    for (int k = 0; k < 3; ++k) {
                        if (!k) {
                            if (dir == 1) {
                                if (!wall1[y][x] && !wall2[y - 1][x]) {
                                    int ny = y - 1; int nx = x - 1;
                                    if (is_in_map(ny, nx))
                                        q.push({p - 1, ny, nx});
                                }
                            }
                            else if (dir == 2) {
                                if (!wall2[y][x] && !wall1[y][x - 1]) {
                                    int ny = y - 1; int nx = x - 1;
                                    if (is_in_map(ny, nx))
                                        q.push({p - 1, ny, nx});
                                }
                            }
                            else if (dir == 3) {
                                if (!wall1[y][x] && !wall2[y - 1][x + 1]) {
                                    int ny = y - 1; int nx = x + 1;
                                    if (is_in_map(ny, nx))
                                        q.push({p - 1, ny, nx});
                                }
                            }
                            else {
                                if (!wall2[y][x + 1] && !wall1[y + 1][x + 1]) {
                                    int ny = y + 1; int nx = x + 1;
                                    if (is_in_map(ny, nx))
                                        q.push({p - 1, ny, nx});
                                }
                            }
                        }
                        
                        else if (k == 1) {
                            if (dir == 1) {
                                if (!wall2[y][x]) {
                                    int ny = y; int nx = x - 1;
                                    if (is_in_map(ny, nx))
                                        q.push({p - 1, ny, nx});
                                }
                            }
                            else if (dir == 2) {
                                if (!wall1[y][x]) {
                                    int ny = y - 1; int nx = x;
                                    if (is_in_map(ny, nx))
                                        q.push({p - 1, ny, nx});
                                }
                            }
                            else if (dir == 3) {
                                if (!wall2[y][x + 1]) {
                                    int ny = y; int nx = x + 1;
                                    if (is_in_map(ny, nx))
                                        q.push({p - 1, ny, nx});
                                }
                            }
                            else {
                                if (!wall1[y + 1][x]) {
                                    int ny = y + 1; int nx = x;
                                    if (is_in_map(ny, nx))
                                        q.push({p - 1, ny, nx});
                                }
                            }
                        }
                        
                        else {
                            if (dir == 1) {
                                if (!wall2[y + 1][x] && wall1[y + 1][x]) {
                                    int ny = y + 1; int nx = x - 1;
                                    if (is_in_map(ny, nx))
                                        q.push({p - 1, ny, nx});
                                }
                            }
                            else if (dir == 2) {
                                if (!wall2[y][x + 1] && !wall1[y][x + 1]) {
                                    int ny = y - 1; int nx = x + 1;
                                    if (is_in_map(ny, nx))
                                        q.push({p - 1, ny, nx});
                                }
                            }
                            else if (dir == 3) {
                                if (!wall1[y + 1][x] && !wall2[y + 1][x + 1]) {
                                    int ny = y + 1; int nx = x + 1;
                                    if (is_in_map(ny, nx))
                                        q.push({p - 1, ny, nx});
                                }
                            }
                            else {
                                if (!wall2[y][x + 1] && !wall1[y + 1][x + 1]) {
                                    int ny = y + 1; int nx = x + 1;
                                    if (is_in_map(ny, nx))
                                        q.push({p - 1, ny, nx});
                                }
                            }
                        }
                        
                    }
                }
                
                //print_map();
            }
        }
    }
    
}

void air_mixed() {
    
    int tmp[25][25];
    memmove(tmp, Map, sizeof(tmp));
    
    // 1. 가로비교
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - 1; ++j) {
            int gap = abs(Map[i][j] - Map[i][j + 1]) / 4;
            if (Map[i][j] >= Map[i][j + 1]) {
                tmp[i][j] -= gap;
                tmp[i][j + 1] += gap;
            }
            else {
                tmp[i][j] += gap;
                tmp[i][j + 1] -= gap;
            }
        }
    }
    
    // 2. 세로비교
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n - 1; ++i) {
            int gap = abs(Map[i][j] - Map[i + 1][j]) / 4;
            if (Map[i][j] >= Map[i + 1][j]) {
                tmp[i][j] -= gap;
                tmp[i + 1][j] += gap;
            }
            else {
                tmp[i][j] += gap;
                tmp[i + 1][j] -= gap;
            }
        }
    }
    
    memmove(Map, tmp, sizeof(Map));
}

void edge_decrease() {
    // 왼쪽 변 
    for (int i = 0; i < n - 1; ++i) {
        if (Map[i][0]) Map[i][0]--;
    }
    // 아랫 변 
    for (int j = 0; j < n - 1; ++j) {
        if (Map[n - 1][j]) Map[n - 1][j]--;
    }
    // 오른쪽 변 
    for (int i = n - 1; i > 0; --i) {
        if (Map[i][n - 1]) Map[i][n - 1]--;
    }
    // 윗 변 
    for (int j = n - 1; j > 0; --j) {
        if (Map[0][j]) Map[0][j]--;
    }
}

bool ans_check() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (office[i][j]) {
                if (Map[i][j] < k)
                    return false;
            }
        }
    }
    return true;
}

void solve() {
    int t = 1;
    while (t <= 100) {
        
        //print_map();
        
        air_con_move();
        //print_map();
        air_mixed();
        //print_map();
        edge_decrease();
        //print_map();
        if (ans_check()) {
            ans = t;
            return;
        }
        t++;
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