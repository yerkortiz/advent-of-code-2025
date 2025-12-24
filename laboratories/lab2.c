#include <stddef.h>
#include <stdio.h>
#include <string.h>

long long memo[1000][1000];

long long count_timelines(int r, int c, int rows, int cols, char grid[1000][1000]) {
    if (memo[r][c] != -1) return memo[r][c];

    for (int i = r + 1; i < rows; ++i) {
        if (grid[i][c] == '^') {
            long long left = 0;
            long long right = 0;

            if (c - 1 >= 0) {
                left = count_timelines(i, c - 1, rows, cols, grid);
            }
            if (c + 1 < cols) {
                right = count_timelines(i, c + 1, rows, cols, grid);
            }
            
            return memo[r][c] = left + right;
        }
    }

    return memo[r][c] = 1;
}

int main() {
    static char grid[1000][1000];
    int rows = 0;
    int cols = 0;

    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) memo[i][j] = -1;
    }

    while (rows < 1000 && fgets(grid[rows], 1000, stdin)) {
        grid[rows][strcspn(grid[rows], "\r\n")] = '\0';
        if (cols == 0) cols = strlen(grid[rows]);
        rows++;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 'S') {
                printf("%lld\n", count_timelines(i, j, rows, cols, grid));
                return 0;
            }
        }
    }

    return 0;
}
