#include <stdio.h>

int get_max_joltage(int bank[], int large) {
    int first = 0;
    printf("large %d\n", large);
    for(int i = 1; i < large - 1; ++i) {
        if (bank[i] > bank[first]) 
            first = i;
    }

    int second = first + 1;

    for(int i = second + 1; i < large; ++i) {
        if (bank[i] > bank[second]) 
            second = i;
    }
    return bank[first] * 10 + bank[second];
}

long long get_max_joltage2(int bank[], int large, int k) {
    int batteries[k];
    batteries[0] = 0;
    int i = 0;
    while(i < k) {
        for(int j = batteries[i] + 1; j < large - (k - i - 1) ; ++j) {
            if(bank[batteries[i]] < bank[j]) {
                batteries[i] = j;
            }
        }
        ++i;
        batteries[i] = batteries[i - 1] + 1;
    }

    long long max_joltage = 0;
    for(int i = 0; i < k; ++i) {
        max_joltage += bank[batteries[i]];
        max_joltage *= 10;
    }
    return max_joltage/10;
}

int main(int argc, char** argv) {
    char line[1000];
    long long sum = 0;
    while (fgets(line, sizeof(line), stdin) != NULL) {
        char *ptr = line;
        int bank[1000];
        int i = 0;
        while (*ptr != '\0' && *ptr != '\n') {
            int digit = *ptr - '0';
            bank[i++] = digit;
            ptr++;
        }
        sum += get_max_joltage2(bank, i, 12);
    }
    printf("max joltage \n%lld\n", sum);
    return 0;
}
