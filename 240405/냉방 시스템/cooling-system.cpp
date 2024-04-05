#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define MAX_N 20
using namespace std;

struct POS { int power; int y, x; };

int n, m, k;
int ans;

int air_con[MAX_N + 5][MAX_N + 5];
int Map[MAX_N + 5][MAX_N + 5];
bool office[MAX_N + 5][MAX_N + 5];
bool visited[MAX_N + 5][MAX_N + 5];

bool wall_row[MAX_N + 5][MAX_N + 5]; // 아래 -> 위방향의 wall
bool wall_col[MAX_N + 5][MAX_N + 5]; // 오 -> 왼방향의 wall

// 0 왼 위 오 아  
const int dy[5] = {0, 0, -1, 0, 1};
const int dx[5] = {0, -1, 0, 1, 0};

void print_progress() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j)
            cout << Map[i][j] << ' ';
        cout << '\n';
    }
    
    cout << '\n';
}

void input() {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int x; cin >> x;
            if (x == 1) office[i][j] = true;
            else if (x) air_con[i][j] = x - 1;
        }
    }
    for (int i = 0; i < m; ++i) {
        int y, x, s; cin >> y >> x >> s;
        if (!s) wall_row[y][x] = true;
        else wall_col[y][x] = true;
    }
}

bool is_in_map(int y, int x) {
    if (y < 1 || y > n || x < 1 || x > n)
        return false;
    else
        return true;
}

void air_con_move() {
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (air_con[i][j]) {
                
                int dir = air_con[i][j];
                int ny = i + dy[dir];
                int nx = j + dx[dir];
                
                memset(visited, false, sizeof(visited));
                queue <POS> q;
                q.push({5, ny, nx});
                
                while (!q.empty()) {
                    int p = q.front().power;
                    int y = q.front().y;
                    int x = q.front().x;
                    q.pop();
                    
                    if (visited[y][x]) continue;
                    visited[y][x] = true;
                    
                    Map[y][x] += p;
                    if (p == 1) continue;
                    
                    
                    // 왼
                    if (dir == 1) {
                        int ny = y; int nx = x - 1;
                        for (int k = 0; k < 3; ++k) {
                            if (!k) {
                                ny = y - 1;
                                if (!is_in_map(ny, nx)) continue;
                                if (!wall_row[y][x] && !wall_col[y - 1][x])
                                    q.push({p - 1, ny, nx});
                            }
                            else if (k == 1) {
                                ny = y;
                                if (!is_in_map(ny, nx)) continue;
                                if (!wall_col[y][x])
                                    q.push({p - 1, ny, nx});
                            }
                            else {
                                ny = y + 1;
                                if (!is_in_map(ny, nx)) continue;
                                if (!wall_row[y + 1][x] && !wall_col[y + 1][x])
                                    q.push({p - 1, ny, nx});
                            }
                        }
                    }
                    // 위
                    else if (dir == 2) {
                        int ny = y - 1; int nx = 0;
                        for (int k = 0; k < 3; ++k) {
                            if (!k) {
                                nx = x - 1;
                                if (!is_in_map(ny, nx)) continue;
                                if (!wall_col[y][x] && !wall_row[y][x - 1])
                                    q.push({p - 1, ny, nx});
                            }
                            else if (k == 1) {
                                nx = x;
                                if (!is_in_map(ny, nx)) continue;
                                if (!wall_row[y][x])
                                    q.push({p - 1, ny, nx});
                            }
                            else {
                                nx = x + 1;
                                if (!is_in_map(ny, nx)) continue;
                                if (!wall_col[y][x + 1] && !wall_row[y][x + 1])
                                    q.push({p - 1, ny, nx});
                            }
                        }
                    }
                    // 오  
                    else if (dir == 3) {
                        int ny = 0; int nx = x + 1;
                        for (int k = 0; k < 3; ++k) {
                            if (!k) {
                                ny = y - 1;
                                if (!is_in_map(ny, nx)) continue;
                                if (!wall_row[y][x] && !wall_col[y - 1][x + 1])
                                    q.push({p - 1, ny, nx});
                            }
                            else if (k == 1) {
                                ny = y;
                                if (!is_in_map(ny, nx)) continue;
                                if (!wall_col[y][x + 1])
                                    q.push({p - 1, ny, nx});
                            }
                            else {
                                ny = y + 1;
                                if (!is_in_map(ny, nx)) continue;
                                if (!wall_row[y + 1][x] && !wall_col[y + 1][x + 1])
                                    q.push({p - 1, ny, nx});
                            }
                        }
                    }
                    // 아
                    else {
                        int ny = y + 1; int nx = 0;
                        for (int k = 0; k < 3; ++k) {
                            if (!k) {
                                nx = x - 1;
                                if (!is_in_map(ny, nx)) continue;
                                if (!wall_col[y][x] && !wall_row[y + 1][x - 1])
                                    q.push({p - 1, ny, nx});
                            }
                            else if (k == 1) {
                                nx = x;
                                if (!is_in_map(ny, nx)) continue;
                                if (!wall_row[y + 1][x])
                                    q.push({p - 1, ny, nx});
                            }
                            else {
                                nx = x + 1;
                                if (!is_in_map(ny, nx)) continue;
                                if (!wall_col[y][x + 1] && !wall_row[y + 1][x + 1])
                                    q.push({p - 1, ny, nx});
                            }
                        }
                    }
                }
                
                //print_progress();
            }
        }
    }
}

void air_mix() {
    
    int tmp[25][25];
    memmove(tmp, Map, sizeof(tmp));
    
    // 1. 세로 방향  
    for (int j = 1; j <= n; ++j) {
        for (int i = 2; i <= n; ++i) {
            if (wall_row[i][j]) continue;
            
            if (Map[i][j] >= Map[i - 1][j]) {
                int gap = (Map[i][j] - Map[i - 1][j]) / 4;
                tmp[i][j] -= gap;
                tmp[i - 1][j] += gap;
            }
            else {
                int gap = (Map[i - 1][j] - Map[i][j]) / 4;
                tmp[i][j] += gap;
                tmp[i - 1][j] -= gap;
            }
            
        }
    }
    
    // 2. 가로 방향  
    for (int i = 1; i <= n; ++i) {
        for (int j = 2; j <= n; ++j) {
            if (wall_col[i][j]) continue;
            
            if (Map[i][j] >= Map[i][j - 1]) {
                int gap = (Map[i][j] - Map[i][j - 1]) / 4;
                tmp[i][j] -= gap;
                tmp[i][j - 1] += gap;
            }
            else {
                int gap = (Map[i][j - 1] - Map[i][j]) / 4;
                tmp[i][j] += gap;
                tmp[i][j - 1] -= gap;
            }
            
        }
    }
    
    memmove(Map, tmp, sizeof(Map));
}

void edge_decrease() {
    for (int i = 1; i < n; ++i) {
        if (Map[i][1]) Map[i][1]--;
    }
    for (int j = 1; j < n; ++j) {
        if (Map[n][j]) Map[n][j]--;
    }
    for (int i = n; i > 1; --i) {
        if (Map[i][n]) Map[i][n]--;
    }
    for (int j = n; j > 1; --j) {
        if (Map[1][j]) Map[1][j]--;
    }
}

bool ans_check() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (office[i][j] && Map[i][j] < k)
                return false;
        }
    }
    return true;
}

void solve() {
    int turn = 1;
    while (turn <= 100) {
        air_con_move();
        air_mix();
        //print_progress();
        edge_decrease();
        //print_progress();
        if (ans_check()) {
            ans = turn;
            return;
        }
        turn++;
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