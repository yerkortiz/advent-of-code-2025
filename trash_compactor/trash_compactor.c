#include <stddef.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    char line[10000];
    char operator_line[10000];
    long long numbers[1000][1000];
    char operators[1000];
    size_t rows = 0;
    size_t cols = 0;
    int op_count = 0;
    
    while(fgets(line, 10000, stdin)) {
        char *ptr = line;  
        int offset;
        int col = 0;
        
        while(sscanf(ptr, "%lld%n", &numbers[rows][col], &offset) == 1) {
            ptr += offset;  
            col++;
        }
        
        if (col > 0) {
            if (rows == 0) cols = col;
            rows++;
        } else {
            strcpy(operator_line, line);
        }
    }
    
    for (int i = 0; operator_line[i] != '\0' && operator_line[i] != '\n'; i++) {
        if (operator_line[i] == '+' || operator_line[i] == '*') {
            operators[op_count++] = operator_line[i];
        }
    }
    
    printf("%ld %ld %d\n", rows, cols, op_count);
   
    long long sum = 0;
    for(int i = 0; i < cols; ++i) {
        long long accumulator = 0;
        if (operators[i] == '*') accumulator = 1;
        for(int j = 0; j < rows; ++j) {
            if (operators[i] == '+') accumulator += numbers[j][i];
            else accumulator *= numbers[j][i];
        }
        sum += accumulator;
    }
    printf("grand total %lld \n", sum);
    return 0;
}
