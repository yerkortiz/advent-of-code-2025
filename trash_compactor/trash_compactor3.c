#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ROWS 100
#define MAX_COLS 8000

typedef __int128_t int128;

void print_u128(int128 n) {
    if (n == 0) { printf("0"); return; }
    char buf[128];
    int i = 0;
    while (n > 0) {
        buf[i++] = (char)((n % 10) + '0');
        n /= 10;
    }
    while (i--) putchar(buf[i]);
}

void solve() {
    static char grid[MAX_ROWS][MAX_COLS];
    int r = 0, max_c = 0;

    while (r < MAX_ROWS && fgets(grid[r], MAX_COLS, stdin)) {
        grid[r][strcspn(grid[r], "\r\n")] = '\0';
        int len = (int)strlen(grid[r]);
        if (len > max_c) max_c = len;
        r++;
    }

    if (r < 2) return;

    int128 grand_total = 0;
    int128 values[MAX_COLS];
    int v_idx = 0;
    char *operators = grid[r - 1];

    for (int col = max_c - 1; col >= 0; col--) {
        char val_str[MAX_ROWS];
        int p = 0;

        for (int i = 0; i < r - 1; i++) {
            if (col < (int)strlen(grid[i]) && isdigit(grid[i][col])) {
                val_str[p++] = grid[i][col];
            }
        }
        val_str[p] = '\0';

        if (p == 0) {
            v_idx = 0;
            continue;
        }

        values[v_idx++] = (int128)strtoull(val_str, NULL, 10);

        char op = (col < (int)strlen(operators)) ? operators[col] : ' ';

        if (op == '+' || op == '*') {
            if (v_idx > 0) {
                int128 res = (op == '+') ? 0 : 1;
                for (int k = 0; k < v_idx; k++) {
                    if (op == '+') res += values[k];
                    else res *= values[k];
                }
                grand_total += res;
            }
            v_idx = 0;
        }
    }

    printf("Grand Total: ");
    print_u128(grand_total);
    printf("\n");
}

int main() {
    solve();
    return 0;
}
