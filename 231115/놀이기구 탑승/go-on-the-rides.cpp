#include <iostream>
#include <queue>
#include <cmath>
#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define MAX_N 20
#define MAX_N2 400
using namespace std;

struct POS {int likeCnt; int emptyCnt; int y, x;};
struct cmp {
    bool operator()(POS a, POS b) {
        if (a.likeCnt == b.likeCnt) {
            if (a.emptyCnt == b.emptyCnt) {
                if (a.y == b.y)
                    return a.x > b.x;
                return a.y > b.y;
            }
            return a.emptyCnt < b.emptyCnt;
        }
        return a.likeCnt < b.likeCnt;
    }
};

int n;
int ans;
int map[MAX_N + 5][MAX_N + 5];
int like[MAX_N2 + 5][4];

const int dy[4] = {-1, 0, 1, 0};
const int dx[4] = {0, 1, 0, -1};

void makeSeat(int num) {
    
    priority_queue <POS, vector<POS>, cmp> pq;
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int lCnt = 0, eCnt = 0;
            if (!map[i][j]) {
                for (int k = 0; k < 4; ++k) {
                    int ny = i + dy[k];
                    int nx = j + dx[k];
                    
                    if (ny < 0 || ny >= n || nx < 0 || nx >= n)
                        continue;
                    for (int l = 0; l < 4; ++l) {
                        if (map[ny][nx] == like[num][l]) {
                            lCnt++;
                            break;
                        }
                    }
                    if (!map[ny][nx])
                        eCnt++;
                }
                pq.push({lCnt, eCnt, i, j});
            }
        }
    }
    
    int y = pq.top().y;
    int x = pq.top().x;
    map[y][x] = num;
}

void calScore() {
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int sid = map[i][j];
            int cnt = 0;
            for (int k = 0; k < 4; ++k) {
                int ny = i + dy[k];
                int nx = j + dx[k];
                
                if (ny < 0 || ny >= n || nx < 0 || nx >= n)
                    continue;
                for (int l = 0; l < 4; ++l) {
                    if (map[ny][nx] == like[sid][l]) {
                        cnt++;
                        break;
                    }
                }
            }
            if (cnt)
                ans += pow(10, cnt - 1);
        }
    }
}

int main() {
    
    fastio;
    cin >> n;
    
    int len = n * n;
    for (int i = 0; i < len; ++i) {
        int num;
        cin >> num;
        for (int j = 0; j < 4; ++j) {
            cin >> like[num][j];
        }
        makeSeat(num);
    }
    
    calScore();
    
    cout << ans << '\n';
    
    return 0;
}