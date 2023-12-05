#include <iostream>
#include <vector>
#include <memory.h>
#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define MAX_L 40
#define MAX_N 30
using namespace std;

struct knight {
    int y, x;
    int h, w;
    int power, damage;
    bool isDead;
};

knight knightPool[MAX_N + 5];

int L, N, Q;
int num, d;
bool canMove;
int map[MAX_L + 5][MAX_L + 5];
bool isTrap[MAX_L + 5][MAX_L + 5];
bool isWall[MAX_L + 5][MAX_L + 5];
bool visited[MAX_N + 5];
vector <int> v;

const int dy[4] = {-1, 0, 1, 0};
const int dx[4] = {0, 1, 0, -1};

bool isOutside(int y, int x) {
    if (x < 0 || x >= L || y < 0 || y >= L)
        return true;
    else
        return false;
}

void push(int n) {
    
    if (visited[n])
        return;
    
    visited[n] = true;
    v.push_back(n);
    int y = knightPool[n].y;
    int x = knightPool[n].x;
    int h = knightPool[n].h;
    int w = knightPool[n].w;
    
    if (d == 0) {
        int sy = y;
        int sx = x;
        for (int i = sx; i <= sx + w - 1; ++i) {
            int ny = sy + dy[d];
            int nx = i + dx[d];
            if (isOutside(ny, nx) || isWall[ny][nx]) {
                canMove = false;
                break;
            }
            if (map[ny][nx]) 
                push(map[ny][nx]);
        }
    }
    
    else if (d == 1) {
        int sy = y;
        int sx = x + w - 1;
        for (int i = y; i <= y + h - 1; ++i) {
            int ny = i + dy[d];
            int nx = sx + dx[d];
            if (isOutside(ny, nx) || isWall[ny][nx]) {
                canMove = false;
                break;
            }
            if (map[ny][nx]) 
                push(map[ny][nx]);
        }
    }
    
    else if (d == 2) {
        int sy = y + h - 1;
        int sx = x;
        for (int i = x; i <= x + w - 1; ++i) {
            int ny = sy + dy[d];
            int nx = i + dx[d];
            if (isOutside(ny, nx) || isWall[ny][nx]) {
                canMove = false;
                break;
            }
            if (map[ny][nx]) 
                push(map[ny][nx]);
        }
    }
    
    else if (d == 3) {
        int sy = y;
        int sx = x;
        for (int i = y; i <= y + h - 1; ++i) {
            int ny = i + dy[d];
            int nx = sx + dx[d];
            if (isOutside(ny, nx) || isWall[ny][nx]) {
                canMove = false;
                break;
            }
            if (map[ny][nx]) 
                push(map[ny][nx]);
        }
    }
}

void battle() {
    
    if (knightPool[num].isDead)
        return;
    
    memset(map, 0, sizeof(map));
    for (int i = 1; i <= N; ++i) {
        if (!knightPool[i].isDead) {
            int y = knightPool[i].y;
            int x = knightPool[i].x;
            for (int j = y; j <= y + knightPool[i].h - 1; ++j) {
                for (int k = x; k <= x + knightPool[i].w - 1; ++k) 
                    map[j][k] = i;
            }
        }
    }
    
    v.clear();
    canMove = true;
    memset(visited, false, sizeof(visited));
    push(num);
    
    if (!canMove)
        return;
        
    for (auto i : v) {
        knightPool[i].y += dy[d];
        knightPool[i].x += dx[d];
    }
    
    for (auto i : v) {
        if (i == num)
            continue;
        int y = knightPool[i].y;
        int x = knightPool[i].x;
    
        for (int j = y; j <= y + knightPool[i].h - 1; ++j) {
            for (int k = x; k <= x + knightPool[i].w - 1; ++k) {
                if (isTrap[j][k])
                    knightPool[i].damage++;
            }
        }
    }
    
    for (int i = 1; i <= N; ++i) {
        if (knightPool[i].damage >= knightPool[i].power)
            knightPool[i].isDead = true;
    }
}

int main() {
    
    fastio;
    cin >> L >> N >> Q;
    
    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < L; ++j) {
            cin >> map[i][j];
            if (map[i][j] == 1)
                isTrap[i][j] = true;
            else if (map[i][j] == 2)
                isWall[i][j] = true;
        }
    }
    
    for (int i = 1; i <= N; ++i) {
        int r, c, h, w, k;
        cin >> r >> c >> h >> w >> k;
        
        knightPool[i] = {r - 1, c - 1, h, w, k, 0, false};
    }
    
    for (int i = 0; i < Q; ++i) {
        cin >> num >> d;
        battle();
    }

    int ans = 0;
    for (int i = 1; i <= N; ++i) {
        if (!knightPool[i].isDead)
            ans += knightPool[i].damage;
    }
    
    cout << ans << '\n';
    
    return 0;
}