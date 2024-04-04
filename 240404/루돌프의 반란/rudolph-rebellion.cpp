#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define MAX_S 30
using namespace std;

struct SANTA {
    int y, x;
    int stunned;
    bool is_out;
    int score;
};

SANTA S[MAX_S + 5];

struct POS { int dis; int y, x; int num; };
struct cmp {
    bool operator()(POS a, POS b) {
        if (a.dis == b.dis) {
            if (a.y == b.y) 
                return a.x < b.x;
            return a.y < b.y;
        }
        return a.dis > b.dis;
    }
};
struct cmp2 {
    bool operator()(POS a, POS b) {
        if (a.dis == b.dis)
            return a.num > b.num;
        return a.dis > b.dis;
    }
};

int Map[55][55];

int N, M, P, C, D;
int ry, rx;

// 상부터 시계방향
const int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};

void print_progress() {
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j)
            cout << Map[i][j] << ' ';
        cout << '\n';
    }
    cout << ry << ' ' << rx << '\n';
    for (int i = 1; i <= P; ++i) {
        cout << S[i].score << ' ';
    }
    cout << '\n';
}

int cal_dis(int y1, int x1, int y2, int x2) {
    int d1 = (y2 - y1) * (y2 - y1);
    int d2 = (x2 - x1) * (x2 - x1);
    
    return d1 + d2;
}

bool is_in_map(int y, int x) {
    if (y < 1 || y > N || x < 1 || x > N)
        return false;
    else
        return true;
}

void input() {
    cin >> N >> M >> P >> C >> D;
    cin >> ry >> rx;
    for (int i = 1; i <= P; ++i) {
        int num, y, x; cin >> num >> y >> x;
        S[num] = {y, x, 0, false, 0};
        
        Map[y][x] = num;
    }
}

void interaction_check(int y, int x, int dir, int num) {
    
    // 1. 맵 밖일 경우
    if (!is_in_map(y, x)) 
        S[num].is_out = true;
    
    // 2. 충돌 x
    else if (!Map[y][x]) {
        Map[y][x] = num;
        S[num].y = y; S[num].x = x;
    }
    
    // 3. 산타와 충돌 O
    else {
        int next_num = Map[y][x];
        Map[y][x] = num;
        S[num].y = y; S[num].x = x;
        
        int ny = y + dy[dir];
        int nx = x + dx[dir];
        
        interaction_check(ny, nx, dir, next_num);
    }
}

void rudolph_move() {
    
    priority_queue <POS, vector<POS>, cmp> pq;
    
    for (int i = 1; i <= P; ++i) {
        if (S[i].is_out) continue;
        
        int y = S[i].y; int x = S[i].x;
        int dis = cal_dis(ry, rx, y, x);
        
        pq.push({dis, y, x, i});
    }
    
    int sy = pq.top().y; int sx = pq.top().x;
    
    priority_queue <POS, vector<POS>, cmp> pq2;
    
    for (int i = 0; i < 8; ++i) {
        
        int ny = ry + dy[i];
        int nx = rx + dx[i];
        
        if (!is_in_map(ny, nx)) 
            continue;
        
        int dis = cal_dis(sy, sx, ny, nx);
        pq2.push({dis, ny, nx, i});
        
    }
    
    ry = pq2.top().y; rx = pq2.top().x;
    int dir = pq2.top().num;
    
    // 산타 충돌 체크
    if (Map[ry][rx]) {
        
        int s_num = Map[ry][rx];
        Map[ry][rx] = 0;
        
        // 1. C만큼 밀려남 && C만큼 점수 얻기 && 기절 
        int sny = ry + dy[dir] * C; 
        int snx = rx + dx[dir] * C;
        S[s_num].score += C;
        S[s_num].stunned = 2;
        
        // 2. 산타 상호작용 체크
        interaction_check(sny, snx, dir, s_num);
    }
}

void santa_move() {
    
    for (int i = 1; i <= P; ++i) {
        if (S[i].is_out || S[i].stunned) continue;
        
        int y = S[i].y; int x = S[i].x;
        int sd = cal_dis(y, x, ry, rx);
        
        priority_queue<POS, vector<POS>, cmp2> pq;
        
        for (int d = 0; d < 8; d += 2) {
            int ny = y + dy[d];
            int nx = x + dx[d];
            
            if (Map[ny][nx] || !is_in_map(ny, nx)) 
                continue;
                
            int dis = cal_dis(ry, rx, ny, nx);
            if (dis < sd) 
                pq.push({dis, ny, nx, d});
        }
        
        // 움직일 수 있다면
        if (!pq.empty()) {
            
            int ny = pq.top().y; int nx = pq.top().x;
            int d = pq.top().num;
            
            Map[y][x] = 0;
            
            // 1. 루돌프 충돌 체크  
            if (ny == ry && nx == rx) {
                
                S[i].score += D;
                S[i].stunned = 2;
                int nd = (d + 4) % 8;
                int nny = ny + dy[nd] * D;
                int nnx = nx + dx[nd] * D;
                
                interaction_check(nny, nnx, nd, i);
            }
            
            // 2. 산타 상호작용 체크 
            else
                interaction_check(ny, nx, d, i);
            
        }
        
        /* 움직일 수 없다면  
        else {
            
        }
        */
    }
}

void stun_decrease() {
    for (int i = 1; i <= P; ++i) {
        if (S[i].stunned) S[i].stunned--;
    }
}

void solve() {
    
    int turn = 1;
    while (turn <= M) {
        rudolph_move();
        //print_progress();
        santa_move();
        //print_progress();
        stun_decrease();
        
        bool can_iter = false;
        for (int i = 1; i <= P; ++i) {
            if (!S[i].is_out) {
                can_iter = true;
                break;
            }
        }
        
        if (!can_iter) 
            break;
        
        for (int i = 1; i <= P; ++i) {
            if (!S[i].is_out) S[i].score++;
        }
        
        turn++;
    }
}

void output() {
    for (int i = 1; i <= P; ++i) 
        cout << S[i].score << ' ';
    cout << '\n';
}


int main() {
    
    fastio;
    input();
    solve();
    output();
    
    return 0;
}