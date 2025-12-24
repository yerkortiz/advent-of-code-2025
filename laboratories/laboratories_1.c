#include <stddef.h>
#include <stdio.h>
#include <string.h>

long long count_beams(int rows, int cols, char grid[1000][1000], int x, int y) {
    long long beam_count = 0;
    int points_buffer[30000][2];
    int buffer_size = 0, front = 0, tail = 0;
    int capacity = 30000;

    points_buffer[tail][0] = x;
    points_buffer[tail][1] = y;
    tail = (tail + 1) % capacity;
    buffer_size++;

    while(buffer_size > 0) {
        int r = points_buffer[front][0];
        int c = points_buffer[front][1];
        front = (front + 1) % capacity;
        buffer_size--;

        if (grid[r][c] == '^') {
            beam_count++;
            grid[r][c] = 'X';
            if (c - 1 >= 0) {
                points_buffer[tail][0] = r;
                points_buffer[tail][1] = c - 1;
                tail = (tail + 1) % capacity;
                buffer_size++;
            }
            if (c + 1 < cols) {
                points_buffer[tail][0] = r;
                points_buffer[tail][1] = c + 1;
                tail = (tail + 1) % capacity;
                buffer_size++;
            }
            continue; 
        }

        for (int i = r + 1; i < rows; ++i) {
            if (grid[i][c] == '^') {
                beam_count++;
                grid[i][c] = 'X';
                if (c - 1 >= 0) {
                    points_buffer[tail][0] = i;
                    points_buffer[tail][1] = c - 1;
                    tail = (tail + 1) % capacity;
                    buffer_size++;
                }
                if (c + 1 < cols) {
                    points_buffer[tail][0] = i;
                    points_buffer[tail][1] = c + 1;
                    tail = (tail + 1) % capacity;
                    buffer_size++;
                }
                break;
            } else if (grid[i][c] == 'X') {
                break;
            }
        }
    }
    return beam_count;
}

int main(int argv, char** argc) {
    static char grid[1000][1000];
    int rows = 0, cols = 0;
    while(rows < 1000 && fgets(grid[rows], 1000, stdin)) {
        grid[rows][strcspn(grid[rows], "\r\n")] = '\0';
        if (cols == 0) cols = strlen(grid[rows]);
        ++rows;
    }
    
    int start_points[10][2];
    int start_points_count = 0;
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j) {
            if(grid[i][j] == 'S') {
                start_points[start_points_count][0] = i;
                start_points[start_points_count][1] = j;
                start_points_count++;
            }
        }
    }

    while(start_points_count > 0) {
        int x = start_points[start_points_count - 1][0];
        int y = start_points[start_points_count - 1][1];
        printf("%lld\n", count_beams(rows, cols, grid, x, y));
        start_points_count--;
    }
    return 0;
}
