#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)

using namespace std;

struct PEOPLE { 
    bool is_out;
    int y, x;
    int dis;
};

PEOPLE P[15];

// 상 하 좌 우      
const int dy[4] = {-1, 1, 0, 0};
const int dx[4] = {0, 0, -1, 1};

int N, M, K;
int exit_y, exit_x;
int ans;

int Map[15][15];

void print_progress() {
    cout << "exit: " << exit_y << ' ' << exit_x << '\n';
    for (int i = 1; i <= M; ++i) {
        if (!P[i].is_out)
            cout << P[i].y << ' ' << P[i].x << '\n';
    }
    cout << '\n';
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j)
            cout << Map[i][j] << ' ';
        cout << '\n';
    }
    cout << '\n';
}

void input() {
    cin >> N >> M >> K;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j)
            cin >> Map[i][j];
    }
    for (int i = 1; i <= M; ++i) {
        int y, x; cin >> y >> x;
        P[i] = { false, y, x, 0 };
    }
    cin >> exit_y >> exit_x;
}

int cal_dis(int y1, int x1, int y2, int x2) {
    int d1 = abs(y1 - y2);
    int d2 = abs(x1 - x2);
    
    return d1 + d2;
}

bool is_in_map(int y, int x) {
    if (y < 1 || y > N || x < 1 || x > N) return false;
    else return true;
}

void people_move() {
    
    for (int i = 1; i <= M; ++i) {
        
        if (P[i].is_out) continue;
        
        priority_queue <int, vector<int>, greater<int>> pq;
        
        int y = P[i].y; int x = P[i].x;
        int sd = cal_dis(y, x, exit_y, exit_x);
        
        // 4방향 탐색하여 출구와 가까운 방향 찾기  
        for (int d = 0; d < 4; ++d) {
            int ny = y + dy[d];
            int nx = x + dx[d];
            int nd = cal_dis(ny, nx, exit_y, exit_x);
            if (!is_in_map(ny, nx)) continue;
            if (Map[ny][nx]) continue;
            
            if (nd < sd) pq.push(d);
        }
        
        // 움직일 수 있는 상황이라면   
        if (!pq.empty()) {
            int dir = pq.top();
            P[i].y = y + dy[dir];
            P[i].x = x + dx[dir];
            P[i].dis++;
            if (P[i].y == exit_y && P[i].x == exit_x)
                P[i].is_out = true;
        }
    }
}

void rotate(int sy, int sx, int ey, int ex) {
    
    int tmp[15][15];
    memset(tmp, 0, sizeof(tmp));
    
    // 1. 시계방향 90도 회전 
    
    int tmp_y = exit_y, tmp_x = exit_x;
    vector <PEOPLE> v;
    
    for (int i = sy; i <= ey; ++i) {
        for (int j = sx; j <= ex; ++j) {
            tmp[sy + j - sx][ex - i + sy] = Map[i][j];
            
            //cout << i << ' ' << j << "->";
            //cout << sy + j - sx << ' ' << ex - i + sy << '\n';
            
            // 출구 좌표값 확인
            if (i == exit_y && j == exit_x) {
                tmp_y = sy + j - sx; tmp_x = ex - i + sy;
            }
            // 사람 좌표값 확인
            for (int k = 1; k <= M; ++k) {
                if (i == P[k].y && j == P[k].x) {
                    v.push_back({ false, sy + j - sx, ex - i + sy, k});
                    break;
                }
            }
            
        }
    }
    
    exit_y = tmp_y; exit_x = tmp_x;
    for (auto i : v) {
        int num = i.dis;
        P[num].y = i.y; P[num].x = i.x;
    }
    
    for (int i = sy; i <= ey; ++i) {
        for (int j = sx; j <= ex; ++j)
            Map[i][j] = tmp[i][j];
    }

    // 2. 1이상의 내구도 감소 
    for (int i = sy; i <= ey; ++i) {
        for (int j = sx; j <= ex; ++j) {
            if (Map[i][j] > 0) Map[i][j]--;
        }
    }
    
}

void maze_rotate() {
    
    // 가장 작은 정사각형 확인 
    int len = 0;
    int sy = 0, sx = 0, ey = 0, ex = 0;
    while (++len < N) {
        
        bool flag1 = false;
        bool flag2 = false;
        //cout << "len: " << len << '\n';
        
        for (int i = 1; i + len <= N; ++i) {
            for (int j = 1; j + len <= N; ++j) {
                
                sy = i; sx = j;
                ey = i + len; ex = j + len;
                
                flag1 = false; flag2 = false;
                for (int y = sy; y <= ey; ++y) {
                    for (int x = sx; x <= ex; ++x) {
                        
                        if (y == exit_y && x == exit_x)
                            flag1 = true;
                            
                        if (!flag2) {
                            for (int z = 1; z <= M; ++z) {
                                if (P[z].is_out) continue;
                            
                                if (y == P[z].y && x == P[z].x)
                                    flag2 = true;
                            }
                        }
                        
                    }
                }
                //cout << i << ' ' << j << ' ' << flag1 << ' ' << flag2 << '\n';
                if (flag1 && flag2) 
                    break;
                
            }
            if (flag1 && flag2) 
                    break;
        }
        
        if (flag1 && flag2) 
            break;    
    
    }
    
    //cout << sy << ' ' << sx << ' ' << ey << ' ' << ex << '\n';
    
    // 그 정사각형 회전
    rotate(sy, sx, ey, ex);
}

bool iter_check() {
    for (int i = 1; i <= M; ++i) {
        if (!P[i].is_out)
            return false;
    }
    return true;
}

void solve() {
    int turn = 0;
    //print_progress();
    while (++turn <= K) {
        //cout << "turn: " << turn << '\n';
        people_move();
        //print_progress();
        maze_rotate();
        //print_progress();
        if (iter_check()) 
            break;
    }
    for (int i = 1; i <= M; ++i) 
        ans += P[i].dis;
}

void output() {
    cout << ans << '\n';
    cout << exit_y << ' ' << exit_x << '\n';
}

int main() {
    
    fastio;
    input();
    solve();
    output();
    
    return 0;
}