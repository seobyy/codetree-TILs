#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
using namespace std;

struct POS { int num; int y, x; };

int n, m, k;
int turn;
int score;
int ans;

// 동 북 서 남    
const int dy[4] = {0, -1, 0, 1};
const int dx[4] = {1, 0, -1, 0};

int start_map[25][25];
int Map[25][25];
int tmp[25][25];
bool rail[25][25];
bool visited[25][25];

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
            if (x) {
                rail[i][j] = true;
                if (x != 4) start_map[i][j] = x;
            }
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
                
                visited[i][j] = true;
                
                queue <POS> q;
                q.push({1, i, j});
                
                while (!q.empty()) {
                    
                    int num = q.front().num;
                    int y = q.front().y;
                    int x = q.front().x;
                    int origin = start_map[y][x];
                    q.pop();
                    
                    Map[y][x] = num;
                    if (origin == 3)
                        break;
                
                    for (int d = 0; d < 4; ++d) {
                        int ny = y + dy[d];
                        int nx = x + dx[d];
                        
                        if (!is_in_map(ny, nx))
                            continue;
                        if (visited[ny][nx])
                            continue;
                            
                        if (origin == 1) {
                            if (start_map[ny][nx] && start_map[ny][nx] != 3) {
                                visited[ny][nx] = true;
                                q.push({num + 1, ny, nx});
                                break;
                            }
                        }
                        else {
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
}

void team_move() {
    
    memset(tmp, 0, sizeof(tmp));
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (Map[i][j] == 1) {
                
                // 나아갈 곳 탐색 
                int last_y = 0, last_x = 0;
                for (int d = 0; d < 4; ++d) {
                    int ny = i + dy[d];
                    int nx = j + dx[d];
                    
                    if (!is_in_map(ny, nx))
                        continue;
                    if (rail[ny][nx] && Map[ny][nx] != 2) {
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
                    
                    int origin = Map[y][x];
                    tmp[last_y][last_x] = num;
                    last_y = y; last_x = x;
                    
                    // 다음 탐색  
                    for (int d = 0; d < 4; ++d) {
                        int ny = y + dy[d];
                        int nx = x + dx[d];
                        
                        if (!is_in_map(ny, nx))
                            continue;
                        if (visited[ny][nx])
                            continue;
                            
                        if (Map[ny][nx] == origin + 1) {
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

void head_to_tail_change(int y, int x) {
    
    memmove(tmp, Map, sizeof(tmp));
    
    // 머리를 찾고 
    int ty = 0, tx = 0;
    
    memset(visited, false, sizeof(visited));
    visited[y][x] = true;
    
    queue <POS> q;
    q.push({0, y, x});
    
    int team_cnt = 0;
    while (!q.empty()) {
        
        int y = q.front().y;
        int x = q.front().x;
        q.pop();
        
        int num = Map[y][x];
        team_cnt = max(team_cnt, num);
        
        if (num == 1) {
            ty = y; tx = x;
        }
        
        for (int d = 0; d < 4; ++d) {
            int ny = y + dy[d];
            int nx = x + dx[d];
            
            if (!is_in_map(ny, nx))
                continue;
            if (visited[ny][nx])
                continue;
            
            if (Map[ny][nx]) {
                visited[ny][nx] = true;
                q.push({0, ny, nx});
            }
        }
    }
    
    // 머리부터 꼬리로 가면서 방향 전환 
    memset(visited, false, sizeof(visited));
    visited[ty][tx] = true;
    
    queue <POS> q2;
    q2.push({team_cnt, ty, tx});
    
    while (!q2.empty()) {
        int num = q2.front().num;
        int y = q2.front().y;
        int x = q2.front().x;
        q2.pop();
        
        tmp[y][x] = num;
        int origin = Map[y][x];
        
        if (num == 1)
            break;
        
        // 머리 -> 꼬리 이동 
        for (int d = 0; d < 4; ++d) {
            int ny = y + dy[d];
            int nx = x + dx[d];
            
            if (!is_in_map(ny, nx))
                continue;
            if (visited[ny][nx])
                continue;
            
            if (Map[ny][nx] == origin + 1) {
                visited[ny][nx] = true;
                q2.push({num - 1, ny, nx});
                break;
            }
        }
    }
    
    memmove(Map, tmp, sizeof(Map));    
}



void ball_shot() {
    
    int d = ((turn - 1) / n) % 4;
    int index = turn % n;
    if (!index) index = n;
    int index2 = n + 1 - index;
    
    // 좌 -> 우 
    if (!d) {
        for (int j = 1; j <= n; ++j) {
            if (Map[index][j]) {
                int num = Map[index][j];
                score += num * num;
                head_to_tail_change(index, j);
                break;
            }
        }
    }
    // 아래 -> 위
    else if (d == 1) {
        for (int i = n; i >= 1; --i) {
            if (Map[i][index]) {
                int num = Map[i][index];
                score += num * num;
                head_to_tail_change(i, index);
                break;
            }
        }
    }
    // 우 -> 좌 
    else if (d == 2) {
        for (int j = n; j >= 1; --j) {
            if (Map[index2][j]) {
                int num = Map[index2][j];
                score += num * num;
                head_to_tail_change(index2, j);
                break;
            }
        }
    }
    // 위 -> 아래   
    else {
        for (int i = 1; i <= n; ++i) {
            if (Map[i][index2]) {
                int num = Map[i][index2];
                score += num * num;
                head_to_tail_change(i, index2);
                break;
            }
        }
    }
}

void solve() {
    init_map();
    //print_progress();
    while (++turn <= k) {
        //cout << "turn: " << turn << '\n';
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