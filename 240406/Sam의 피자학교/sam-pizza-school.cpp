#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
using namespace std;

int n, k;
int row_size = 1, col_size;
int ans;

int arr[105];
int tmp[105][105];

void print_tmp() {
    for (int i = 0; i < row_size; ++i) {
        for (int j = 0; j < n; ++j) 
            cout << tmp[i][j] << ' ';
        cout << '\n';
    }
    cout << '\n';
}

void print_arr() {
    for (int i = 0; i < n; ++i)
        cout << arr[i] << ' ';
    cout << '\n' << '\n';
}

void input() {
    cin >> n >> k;
    col_size = n;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
}

void flour_add() {
    int m = *min_element(arr, arr + n);
    for (int i = 0; i < n; ++i) {
        if (arr[i] == m) arr[i]++;
    }
}

void dough_roll() {
    
    int width = 1; // 접을 부분의 너비
    int height = 1; // 도우의 높이
    int len = n;    // 도우의 총 너비  
    
    for (int j = 0; j < n; ++j) 
        tmp[height - 1][j] = arr[j];
    
    //print_tmp();
    while (height < len - width) {
        
        int tmp2[105][105];
        memset(tmp2, 0, sizeof(tmp2));
        
        // 바닥면
        for (int j = width; j < len; ++j) {
            tmp2[width][j - width] = tmp[height - 1][j];
        }
        
        // 차례로 윗면 쌓기 
        for (int j = width - 1; j >= 0; --j) {
            int y = width - j;
            for (int i = height - 1; i >= 0; --i)
                tmp2[width - y][height - 1 - i] = tmp[i][j];
        }
        
        int height_tmp = height;
        height = 1 + width;
        len -= width;
        width = height_tmp;
        
        memmove(tmp, tmp2, sizeof(tmp));
        
        row_size = height;
        col_size = len;
        //print_tmp();
    }
    
}

void dough_press() {
    
    int tmp2[105][105];
    memmove(tmp2, tmp, sizeof(tmp2));
    
    // 좌우방향   
    for (int i = 0; i < row_size; ++i) {
        for (int j = 0; j < col_size; ++j) {
            if (!tmp[i][j + 1]) break;
            
            if (tmp[i][j] >= tmp[i][j + 1]) {
                int gap = (tmp[i][j] - tmp[i][j + 1]) / 5;
                tmp2[i][j] -= gap;
                tmp2[i][j + 1] += gap;
            }
            else {
                int gap = (tmp[i][j + 1] - tmp[i][j]) / 5;
                tmp2[i][j] += gap;
                tmp2[i][j + 1] -= gap;
            }
        }
    }
    
    // 상하 방향   
    for (int j = 0; j < col_size; ++j) {
        for (int i = row_size - 1; i > 0; --i) {
            if (!tmp[i - 1][j]) continue;
            
            if (tmp[i][j] >= tmp[i - 1][j]) {
                int gap = (tmp[i][j] - tmp[i - 1][j]) / 5;
                tmp2[i][j] -= gap;
                tmp2[i - 1][j] += gap;
            }
            else {
                int gap = (tmp[i - 1][j] - tmp[i][j]) / 5;
                tmp2[i][j] += gap;
                tmp2[i - 1][j] -= gap;
            }
        }
    }
    
    memmove(tmp, tmp2, sizeof(tmp));
    
    //print_tmp();
    
    int cnt = 0;
    for (int j = 0; j < n; ++j) {
        for (int i = row_size - 1; i >= 0; --i) {
            if (!tmp[i][j]) continue;
            arr[cnt++] = tmp[i][j];
        }
    }
    
    //print_arr();
}

void dough_fold() {
    
    int tmp2[105][105];
    memset(tmp2, 0, sizeof(tmp2));
    
    // 1회
    int mid = n / 2;
    for (int j = mid; j < n; ++j) {
        tmp2[1][j - mid] = arr[j];
    }
    for (int j = mid - 1; j >= 0; --j) {
        tmp2[0][mid - 1 - j] = arr[j];    
    }
    
    col_size = mid;
    row_size = 2;
    memmove(tmp, tmp2, sizeof(tmp));
    //print_tmp();
    
    // 2회
    
    int tmp3[105][105];
    memset(tmp3, 0, sizeof(tmp3));

    int mid2 = mid / 2;
    for (int i = 0; i < mid2; ++i) {
        int j = mid2 - 1 - i;
        tmp3[0][i] = tmp2[1][j];
        tmp3[1][i] = tmp2[0][j];
        
        int j2 = mid2 + i;
        tmp3[2][i] = tmp2[0][j2];
        tmp3[3][i] = tmp2[1][j2];
    } 
    
    memmove(tmp, tmp3, sizeof(tmp));
    col_size = mid2;
    row_size = 4;
    
    //print_tmp();
}

bool ans_check() {
    int m = *min_element(arr, arr + n);
    int M = *max_element(arr, arr + n);
    if (M - m <= k) return true;
    else return false;
}

void solve() {
    int turn = 0;
    while (++turn) {
        flour_add();
        //print_arr();
        dough_roll();
        //print_tmp();
        dough_press();
        dough_fold();
        dough_press();
        //print_arr();
        if (ans_check())
            break;
        
    }
    ans = turn;
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