#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ROWS 100
#define MAX_COLS 8000

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

    unsigned long long grand_total = 0;
    unsigned long long values[MAX_COLS];
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

        values[v_idx++] = strtoull(val_str, NULL, 10);

        char op = (col < (int)strlen(operators)) ? operators[col] : ' ';

        if (op == '+' || op == '*') {
            if (v_idx > 0) {
                unsigned long long res = (op == '+') ? 0 : 1;
                for (int k = 0; k < v_idx; k++) {
                    if (op == '+') res += values[k];
                    else res *= values[k];
                }
                grand_total += res;
            }
            v_idx = 0;
        }
    }

    printf("Grand Total: %llu\n", grand_total);
}

int main() {
    solve();
    return 0;
}
