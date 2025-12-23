#include <math.h>
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
    
    long long sum = 0;
    for(int j = cols - 1; j >= 0; --j) {
        size_t largest_size = (size_t) floor(log10(numbers[0][j])) + 1;
        for(int i = 0; i < rows; ++i) {
            if ((size_t) floor(log10(numbers[i][j])) + 1 > largest_size) 
                largest_size = (size_t) floor(log10(numbers[i][j])) + 1;
        }

        while(largest_size > 1) {
            long long operand = 0;
            for(int i = 0; i < rows; ++i) {
                if ((size_t) floor(log10(numbers[i][j])) + 1 != largest_size) continue;
                operand = (operand * 10) + (numbers[i][j] % 10);
                numbers[i][j] /= 10;
            }
            printf("operand at col %d, of large %ld is %lld\n", j, largest_size, operand);
            --largest_size;
        }
    }

    printf("grand total %lld \n", sum);
    return 0;
}

