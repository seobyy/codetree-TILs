#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define MAX_N 20
using namespace std;

struct POS { int num; int y, x; };

int n, m, k;
int team_cnt;
int turn;
int score;
int ans;

// 동 북 서 남   
const int dy[4] = {0, -1, 0, 1};
const int dx[4] = {1, 0, -1, 0};

int start_map[MAX_N + 5][MAX_N + 5];
int Map[MAX_N + 5][MAX_N + 5];
bool rail[MAX_N + 5][MAX_N + 5];
bool visited[MAX_N + 5][MAX_N + 5];

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
            if (x == 4) rail[i][j] = true;
            else if (x) start_map[i][j] = x;
        }
    }
}

bool is_in_map(int y, int x) {
    if (y < 1 || y > n || x < 1 || x > n) return false;
    else return true;
}

void init_map() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (start_map[i][j] == 1) {
                
                memset(visited, false, sizeof(visited));
                visited[i][j] = true;
                
                queue <POS> q;
                q.push({1, i, j});
                
                while (!q.empty()) {
                    
                    int num = q.front().num;
                    int y = q.front().y;
                    int x = q.front().x;
                    q.pop();
                    
                    //cout << num << ' ' << y << ' ' << x << '\n';
                    
                    Map[y][x] = num;
                    
                    for (int d = 0; d < 4; ++d) {
                        int ny = y + dy[d];
                        int nx = x + dx[d];
                        
                        if (!is_in_map(ny, nx))
                            continue;
                        if (visited[ny][nx])
                            continue;
                        
                        if (start_map[ny][nx]) {
                            visited[ny][nx] = true;
                            q.push({num + 1, ny, nx});
                            break;
                        }
                    }
                }
            }
        }
    }
}

void team_move() {
    
    int tmp[MAX_N + 5][MAX_N + 5];
    memset(tmp, 0, sizeof(tmp));
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (Map[i][j] == 1) { 
                
                int last_y = 0, last_x = 0;
                for (int d = 0; d < 4; ++d) {
                    int ny = i + dy[d];
                    int nx = j + dx[d];
                    
                    if (!is_in_map(ny, nx))
                        continue;
                    if (rail[ny][nx] && !Map[ny][nx]) {
                        last_y = ny; last_x = nx;
                        break;
                    }
                }
                
                memset(visited, false, sizeof(visited));
                visited[i][j] = true;
                
                queue <POS> q;
                q.push({1, i, j});
                
                while (!q.empty()) {
                    
                    int num = q.front().num;
                    int y = q.front().y;
                    int x = q.front().x;
                    q.pop();
                    
                    //cout << num << ' ' << y << ' ' << x << '\n';
                    
                    tmp[last_y][last_x] = num;
                    last_y = y; last_x = x;
                    
                    // 다음 꼬리 탐색
                    for (int d = 0; d < 4; ++d) {
                        int ny = y + dy[d];
                        int nx = x + dx[d];
                    
                        if (!is_in_map(ny, nx))
                            continue;
                        if (visited[ny][nx])
                            continue;
                        if (Map[ny][nx]) {
                            visited[ny][nx] = true;
                            q.push({num + 1, ny, nx});
                            break;
                        }
                    }
                }
            }
        }
    }
    memmove(Map, tmp, sizeof(Map));
}

void order_change(int y, int x, int num) {
    
    Map[y][x] = num;
    visited[y][x] = true;
    
    for (int i = 0; i < 4; ++i) {
        int ny = y + dy[i];
        int nx = x + dx[i];
        
        if (!is_in_map(ny, nx))
            continue;
        if (Map[ny][nx] && !visited[ny][nx]) {
            order_change(ny, nx, num + 1);
            return;
        }
    }
}

void ball_shot() {
    int d = ((turn - 1) / n) % 4;
    int index = turn % n;
    if (!index) index = n;
    
    // 좌 -> 우
    if (!d) {
        for (int j = 1; j <= n; ++j) {
            if (Map[index][j]) {
                int num = Map[index][j];
                score += num * num;
                memset(visited, false, sizeof(visited));
                order_change(index, j, 1);
                return;
            }
        }
    }
    // 아래 -> 위  
    else if (d == 1) {
        for (int i = n; i >= 1; --i) {
            if (Map[i][index]) {
                int num = Map[i][index];
                score += num * num;
                memset(visited, false, sizeof(visited));
                order_change(i, index, 1);
                return;
            }
        }
    }
    // 우 -> 좌  
    else if (d == 2) {
        for (int j = n; j >= 1; --j) {
            if (Map[index][j]) {
                int num = Map[index][j];
                score += num * num;
                memset(visited, false, sizeof(visited));
                order_change(index, j, 1);
                return;
            }
        }
    }
    // 위 -> 아래   
    else {
        for (int i = 1; i <= n; ++i) {
            if (Map[i][index]) {
                int num = Map[i][index];
                score += num * num;
                memset(visited, false, sizeof(visited));
                order_change(i, index, 1);
                return;
            }
        }
    }
}

void solve() {
    
    init_map();
    //print_progress();
    
    while (++turn <= k) {
        team_move();
        //print_progress();
        ball_shot();
        //print_progress();
    }
    
    ans = score;
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