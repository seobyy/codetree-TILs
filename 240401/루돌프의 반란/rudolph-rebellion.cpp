#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
using namespace std;

// 상방향 부터 시계방향
const int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};

struct SANTA { int y, x; int score; int stunned; bool is_out; };
SANTA S[35];

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
    bool operator() (POS a, POS b) {
        if (a.dis == b.dis)
            return a.num > b.num;
        return a.dis > b.dis;
    }
};

int N, M, P, C, D;
int ry, rx;

int Map[55][55];

void print_map() {
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j)
            cout << Map[i][j] << ' ';
        cout << '\n';
    }
    
    cout << ry << ' ' << rx << '\n';
}

void input() {
    cin >> N >> M >> P >> C >> D;
    cin >> ry >> rx;
    for (int i = 1; i <= P; ++i) {
        int num, y, x;
        cin >> num >> y >> x;
        Map[y][x] = num;
        S[num] = { y, x, 0, 0, false };
    }
}

int cal_dis(int y1, int x1, int y2, int x2) {
    int d1 = (y1 - y2) * (y1 - y2);
    int d2 = (x1 - x2) * (x1 - x2);
    return d1 + d2;
}

bool is_in_map(int y, int x) {
    if (y < 1 || y > N || x < 1 || x > N)
        return false;
    else
        return true;
}

void interaction_check(int y, int x, int dir, int num) {
    
    // 1. 나간 경우
    if (!is_in_map(y, x)) {
        S[num].is_out = true;
    }
    
    // 2. 충돌 x 
    else if (!Map[y][x]) {
        Map[y][x] = num;
        S[num].y = y; S[num].x = x;
    }
    
    // 3. 충돌  
    else {
        int c_num = Map[y][x];
        Map[y][x] = num; 
        S[num].y = y; S[num].x = x;
        
        int ny = y + dy[dir];
        int nx = x + dx[dir];
        interaction_check(ny, nx, dir, c_num);
    
    }
}

void rudolph_move() {
    
    // 1. 이동
    // 1-1. 가장 가까운 산타 체크
    priority_queue <POS, vector<POS>, cmp> pq;
    for (int i = 1; i <= P; ++i) {
        if (!S[i].is_out) {
            int d = cal_dis(ry, rx, S[i].y, S[i].x);
            pq.push({d, S[i].y, S[i].x, i});
        }
    }
    int num = pq.top().num;
    
    // 1-2. 산타를 향해 이동
    priority_queue <POS, vector<POS>, cmp> pq2;
    for (int i = 0; i < 8; ++i) {
        int ny = ry + dy[i];
        int nx = rx + dx[i];
        
        if (!is_in_map(ny, nx)) continue;
        
        int d = cal_dis(ny, nx, S[num].y, S[num].x);
        pq2.push({d, ny, nx, i});
    }
    
    ry = pq2.top().y;
    rx = pq2.top().x;
    int dir = pq2.top().num;
    
    // 2. 충돌 체크
    if (Map[ry][rx]) {
        int n = Map[ry][rx];
        Map[ry][rx] = 0;
        
        S[n].score += C;
        S[n].stunned = 2;
        
        int ny = ry + dy[dir] * C;
        int nx = rx + dx[dir] * C;
        
        interaction_check(ny, nx, dir, n); 
        
    }
}

void santa_move() {
    
    for (int i = 1; i <= P; ++i) {
        if (!S[i].stunned && !S[i].is_out) {
            int y = S[i].y; int x = S[i].x;
            int sd = cal_dis(y, x, ry, rx);
            
            priority_queue <POS, vector<POS>, cmp2> pq;
            
            for (int d = 0; d < 8; d += 2) {
                int ny = y + dy[d];
                int nx = x + dx[d];
                
                if (!is_in_map(ny, nx)) continue;
                if (Map[ny][nx]) continue;
                
                //cout << i << ": " << ny << ' ' << nx << ' ' << d << '\n';
                
                int dis = cal_dis(ny, nx, ry, rx);
                pq.push({dis, ny, nx, d});
            }
            
            if (!pq.empty()) {
                if (pq.top().dis < sd) {
                    
                    int ny = pq.top().y;
                    int nx = pq.top().x;
                    int d = pq.top().num;
                    
                    Map[y][x] = 0;
                    
                    // 1. 루돌프와 충돌일 경우
                    if (ny == ry && nx == rx) {
                        S[i].score += D;
                        S[i].stunned = 2;
                        int nd = (d + 4) % 8;
                        
                        int nny = ny + dy[nd] * D;
                        int nnx = nx + dx[nd] * D;
                        
                        // 2. 상호작용
                        interaction_check(nny, nnx, nd, i);
                        
                    }
                    else {
                        Map[ny][nx] = i;
                        S[i].y = ny; S[i].x = nx;
                    }
                }
            }
            
            
            
            //print_map();
        }
    }
}

void decrease_stun() {
    for (int i = 1; i <= P; ++i) {
        if (S[i].stunned) S[i].stunned--;
    }
}

bool end_check() {
   for (int i = 1; i <= N; ++i) {
       for (int j = 1; j <= N; ++j) {
           if (Map[i][j])
                return false;
       }
   }
   return true;
}

void solve() {
    int turn = 1;
    while (turn <= M) {
        //print_map();
        rudolph_move();
        //print_map();
        santa_move();
        //print_map();
        decrease_stun();
        
        
        // 7.게임 종료 단계
        if (end_check()) 
            return;
        else {
            for (int i = 1; i <= P; ++i) {
                if (!S[i].is_out) S[i].score++;
            }
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