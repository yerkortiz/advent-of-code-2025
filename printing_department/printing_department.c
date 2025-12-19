#include <stdio.h>
#include <string.h>

int count_paper_rolls(int x, int y, char grid[200][200], int rows, int columns) {
    int neighborhood[8][2] = {
        {-1,-1}, 
        {-1, 0}, 
        {-1, 1}, 
        {0, 1}, 
        {1, 1}, 
        {1, 0}, 
        {1, -1}, 
        {0, -1}
    };

    int roll_count = 0;
    for(int i = 0; i < 8; ++i) {
        if (neighborhood[i][0] + x < 0 || neighborhood[i][1] + y < 0) continue;
        if (neighborhood[i][0] + x >= columns || neighborhood[i][1] + y >= rows) continue;
        if (grid[neighborhood[i][0] + x][neighborhood[i][1] + y] == '@') ++roll_count;
    }
    return roll_count;
} 

int main(int argc, char** argv) {
    char grid[200][200];  
    int rows = 0;
    int cols = 0;
    
    while (fgets(grid[rows], sizeof(grid[rows]), stdin) != NULL) {
        grid[rows][strcspn(grid[rows], "\n")] = '\0';
        
        if (rows == 0) {
            cols = strlen(grid[rows]);
        }
        
        rows++;
    }

    int total_rolls = 0;
    while (1) {
        char grid_copy[200][200];
        int roll_accesses = 0;
        for(int i = 0; i < rows; ++i) {
            for(int j = 0; j < cols; ++j) {
                grid_copy[i][j] = grid[i][j];
                if (grid[i][j] == '@' && count_paper_rolls(i, j, grid, rows, cols) < 4) {
                    grid_copy[i][j] = '.';
                    ++roll_accesses;
                }
            }
        }
        memcpy(grid, grid_copy, sizeof(grid));
        total_rolls += roll_accesses;
        if(roll_accesses == 0) break;
    }
    printf("%d\n", total_rolls);

    return 0;
}
