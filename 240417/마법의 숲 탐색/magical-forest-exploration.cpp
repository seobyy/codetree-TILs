#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
using namespace std;

struct POS { bool exit_check; int num; int y, x; };

int R, C, K;
int sy, sx, exit_d;
int s_num;
int ans;

int spaceship[75][75];
bool is_exit[75][75];
bool visited[75][75];

// 북 동 남 서  
const int dy[4] = {-1, 0, 1, 0};
const int dx[4] = {0, 1, 0, -1};

void input() {
    cin >> R >> C >> K;
}

void print_map() {
    
    for (int i = 1; i <= R; ++i) {
        for (int j = 1; j <= C; ++j) {
            cout << spaceship[i][j] << ' ';
        }
        cout << '\n';
    } 
    cout << '\n';
    for (int i = 1; i <= R; ++i) {
        for (int j = 1; j <= C; ++j) {
            cout << is_exit[i][j] << ' ';
        }
        cout << '\n';
    } 
    cout << '\n';
    
}

bool can_go_pos(int y, int x) {
    
    
    // 왼, 오 만 check
    if (y == -1) {
        if (x - 1 < 1 || x + 1 > C) return false;
        else return true;
        
    }
    
    // 왼 오, 아래 check
    else if (y == 0) {
        if (x - 1 < 1 || x + 1 > C) return false;
        
        if (spaceship[y + 1][x]) return false;
        else return true;
    }
    
    // 위빼고 check
    else if (y == 1) {
        if (spaceship[y][x]) return false;
        
        for (int d = 1; d < 4; ++d) {
            int ny = y + dy[d];
            int nx = x + dx[d];
            
            if (ny < 1 || ny > R || nx < 1 || nx > C) return false;
            if (spaceship[ny][nx]) return false;
        }
        
        return true;
    }
    
    // 다 check
    else {
        
        if (y < 1 || y > R || x < 1 || x > C) return false;
        if (spaceship[y][x]) return false;
        
        for (int d = 0; d < 4; ++d) {
            int ny = y + dy[d];
            int nx = x + dx[d];
            
            if (ny < 1 || ny > R || nx < 1 || nx > C) return false;
            if (spaceship[ny][nx]) return false;
        }
        
        return true;
    }
}

void mark_map(int y, int x) {
    
    if (y == 0 || y == -1) {
        memset(spaceship, 0, sizeof(spaceship));
        memset(is_exit, false, sizeof(is_exit));
        return;
    }
    
    
    spaceship[y][x] = s_num;
    for (int i = 0; i < 4; ++i) {
        int ny = y + dy[i];
        int nx = x + dx[i];
        
        spaceship[ny][nx] = s_num;
    }
    
    int ey = y + dy[exit_d];
    int ex = x + dx[exit_d];
    
    is_exit[ey][ex] = true;
}

void gravity() {
    
    while (1) {
        if (sy == R - 1) {
            mark_map(sy, sx);
            break;
        }
        
        int ny = 0, nx = 0;
        for (int i = 0; i < 3; ++i) {
            
            if (!i) {
                ny = sy + 1; nx = sx;
                if (can_go_pos(ny, nx)) 
                    break;
            }
            
            else if (i == 1) {
                ny = sy; nx = sx - 1;
                if (can_go_pos(ny, nx)) {
                    ny = sy + 1;
                    if (can_go_pos(ny, nx)) {
                        exit_d = ((exit_d - 1) + 4) % 4;
                        break;
                    }
                }
            }
            
            else {
                ny = sy; nx = sx + 1;
                if (can_go_pos(ny, nx)) {
                    ny = sy + 1;
                    if (can_go_pos(ny, nx)) {
                        exit_d = (exit_d + 1) % 4;
                        break;
                    }
                    
                    else {
                        mark_map(sy, sx);
                        return;
                    }
                }
                else {
                    mark_map(sy, sx);
                    return;
                }
                
            }
            
        }
        
        sy = ny; sx = nx;
    }
}

void robot_move() {
    
    if (!sy || sy == -1)
        return;
    
    memset(visited, false, sizeof(visited));
    visited[sy][sx] = true;
    
    queue <POS> q;
    q.push({false, spaceship[sy][sx], sy, sx});
    
    int max_y = 0;
    
    while (!q.empty()) {
        bool e = q.front().exit_check;
        int n = q.front().num;
        int y = q.front().y;
        int x = q.front().x;
        q.pop();
        
        max_y = max(max_y, y);
        
        for (int i = 0; i < 4; ++i) {
            int ny = y + dy[i];
            int nx = x + dx[i];
            
            if (ny < 1 || ny > R || nx < 1 || nx > C)
                continue;
            if (visited[ny][nx])
                continue;
            
            // 출구일 경우
            if (e) {
                if (spaceship[ny][nx]) {
                    visited[ny][nx] = true;
                    q.push({is_exit[ny][nx], spaceship[ny][nx], ny, nx});
                }
            }
            
            else {
                if (spaceship[ny][nx] == n) {
                    visited[ny][nx] = true;
                    q.push({is_exit[ny][nx], n, ny, nx});
                }
            }
            
        }
    
    }
    
    ans += max_y;
    
    
}

void solve() {
    for (s_num = 1; s_num <= K; ++s_num) {
        cin >> sx >> exit_d;
        sy = -1;
        
        gravity();
        
        //print_map();
        
        robot_move();
        
        //cout << "turn" << s_num << ": " << ans << '\n'; 
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