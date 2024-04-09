#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define MAX_L 40
using namespace std;

struct KNIGHT { 
    bool is_out; 
    int y, x; 
    int h, w; 
    int start_power, current_power;
};
KNIGHT K[35];

// 위 오 아 왼  
const int dy[4] = {-1, 0, 1, 0};
const int dx[4] = {0, 1, 0, -1};

int L, N, Q;
int id, d; 
int ans;

bool can_push;
vector <int> v;

int Map[MAX_L + 5][MAX_L + 5];
bool wall[MAX_L + 5][MAX_L + 5];
bool trap[MAX_L + 5][MAX_L + 5];

void print_progress() {
    for (int i = 1; i <= L; ++i) {
        for (int j = 1; j <= L; ++j)
            cout << Map[i][j] << ' ';
        cout << '\n';
    }
    for (int i = 1; i <= N; ++i) {
        cout << "i: " << K[i].current_power << '\n';
    }
    cout << '\n';
}

void input() {
    cin >> L >> N >> Q;
    for (int i = 1; i <= L; ++i) {
        for (int j = 1; j <= L; ++j) {
            int x; cin >> x;
            if (x == 1) trap[i][j] = true;
            else if (x == 2) wall[i][j] = true;
        }
    }
    for (int i = 1; i <= N; ++i) {
        int r, c, h, w, k; cin >> r >> c >> h >> w >> k;
        K[i] = { false, r, c, h, w, k, k};
    }
}

bool is_in_map(int y, int x) {
    if (y < 1 || y > L || x < 1 || x > L) return false;
    else return true;
}

void make_map() {
    memset(Map, 0, sizeof(Map));
    for (int n = 1; n <= N; ++n) {
        if (K[n].is_out) continue;
        
        int sy = K[n].y; int sx = K[n].x;
        int ey = sy + K[n].h - 1; int ex = sx + K[n].w - 1;
        
        for (int i = sy; i <= ey; ++i) {
            for (int j = sx; j <= ex; ++j)
                Map[i][j] = n;
        }
    }
}

void knight_push(int num) {
    
    if (!can_push)
        return;
    v.push_back(num);
    
    int sy = K[num].y; int sx = K[num].x;
    int ey = sy + K[num].h - 1; int ex = sx + K[num].w - 1;
    
    // 위
    if (!d) {
        int ny = sy - 1;
        unordered_set <int> tmp;
        for (int j = sx; j <= ex; ++j) {
            if (!is_in_map(ny, j) || wall[ny][j]) {
                can_push = false;
                return;
            }
            else if (Map[ny][j]) tmp.insert(Map[ny][j]);
        }
        for (auto k : tmp) 
            knight_push(k);
    }
    // 오
    else if (d == 1) {
        int nx = ex + 1;
        unordered_set <int> tmp;
        for (int i = sy; i <= ey; ++i) {
            if (!is_in_map(i, nx) || wall[i][nx]) {
                can_push = false;
                return;
            }
            else if (Map[i][nx]) tmp.insert(Map[i][nx]);
        }
        for (auto k : tmp) 
            knight_push(k);
    }
    // 아
    else if (d == 2) {
        int ny = ey + 1;
        unordered_set <int> tmp;
        for (int j = sx; j <= ex; ++j) {
            if (!is_in_map(ny, j) || wall[ny][j]) {
                can_push = false;
                return;
            }
            else if (Map[ny][j]) tmp.insert(Map[ny][j]);
        }
        for (auto k : tmp) 
            knight_push(k);
    } 
    // 왼
    else {
        int nx = sx - 1;
        unordered_set <int> tmp;
        for (int i = sy; i <= ey; ++i) {
            if (!is_in_map(i, nx) || wall[i][nx]) {
                can_push = false;
                return;
            }
            else if (Map[i][nx]) tmp.insert(Map[i][nx]);
        }
        for (auto k : tmp) 
            knight_push(k);
    }
}

void knight_move(int num) {
    
    // 1. 좌표값 갱신
    K[num].y = K[num].y + dy[d]; K[num].x = K[num].x + dx[d];
    
    int sy = K[num].y; int sx = K[num].x;
    int ey = sy + K[num].h - 1; int ex = sx + K[num].w - 1;
    
    // 2. 데미지 받기
    if (num == id)
        return;
    int res = 0;
    for (int i = sy; i <= ey; ++i) {
        for (int j = sx; j <= ex; ++j) {
            if (trap[i][j]) res++;
        }
    }
    
    K[num].current_power -= res;
    if (K[num].current_power <= 0)
        K[num].is_out = true;
        
}

void solve() {
    
    for (int cmd = 0; cmd < Q; ++cmd) {
        cin >> id >> d;
        //cout << "turn: " << cmd << '\n';
        if (!K[id].is_out) {
            
            v.clear();
            can_push = true;
            make_map();
            
            //print_progress();
            
            
            knight_push(id);
            
            //cout << "can move: " << can_push << '\n';
            
            
            if (can_push) {
                for (auto j : v) 
                    knight_move(j);
            } 
            
        }
    }
    //make_map();
    //print_progress();
    // 생존된 기사들의 총 받은 데미지 합  
    for (int i = 1; i <= N; ++i) {
        if (!K[i].is_out)
            ans += K[i].start_power - K[i].current_power; 
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