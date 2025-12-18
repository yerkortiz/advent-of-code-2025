#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

bool is_invalid_id(long long a) {
    long long large = floor(log10(a)) + 1;
    long long digits[large];
    long long i = large - 1;
    if (large % 2 == 1) return false;

    while (a != 0) {
        digits[i] = a % 10;
        a /= 10;
        --i;
    }
    
    long long lo = 0;
    long long mid = large/2;
    while (lo < large/2) {
        if (digits[lo] != digits[mid]) return false;
        lo++;
        mid++;
    }
    return true;
}

bool is_invalid_id3(long long a) {
    size_t large = floor(log10(a)) + 1;
    long long *digits = malloc(sizeof(long long) * large);
    int i = large - 1;

    while (a != 0) {
        digits[i] = a % 10;
        a /= 10;
        --i;
    }

    int k = 1;
    while(k <= large/2) {
        int lo = 0;
        int hi = k;
        bool invalid = true;
        for(int i = 0; i <= large - 1 - k; ++i) {
            while(lo < hi) {
                if(digits[lo] != digits[hi + lo]) {
                    invalid = false;
                    break;
                }
                ++lo;
            }
            if (invalid == false) break;
            lo = i + 1;
        }
        if(invalid == true) {
            return true;
        }
        ++k;
    }
    return false;
}

bool is_invalid_id2(long long a) {
    size_t large = floor(log10(a)) + 1;
    long long *digits = malloc(sizeof(long long) * large);
    int i = large - 1;
    while (a != 0) {
        digits[i] = a % 10;
        a /= 10;
        --i;
    }
    
    int k = 1;
    while(k <= large/2) {
        if (large % k != 0) {   
            ++k;
            continue;
        }
        
        bool invalid = true;
        for(int i = k; i < large; ++i) {   
            if(digits[i] != digits[i % k]) {   
                invalid = false;
                break;
            }
        }
        
        if(invalid == true) {
            free(digits);   
            return true;
        }
        ++k;
    }
    free(digits);   
    return false;
}
void test_f(int n) {
    printf("number %d %d\n", n, is_invalid_id2(n));
}

int main(int argc, char** argv) {
    char line[100000];
    fgets(line, sizeof(line), stdin);

    char *ptr = line;
    long long start, end;
    int offset;

    long long sum = 0;
    while (sscanf(ptr, "%lld-%lld%n", &start, &end, &offset) == 2) {
        printf("Rango: %lld - %lld\n", start, end);

        long k = start;
        while(k <= end) {
            if(is_invalid_id2(k)){
                printf("invalid id %ld\n", k);
                sum += k;
            }
            ++k;
        }
    
        ptr += offset;      

        if (*ptr == ',') ptr++; 
        if (*ptr == '\n' || *ptr == '\0') break;
    }

    printf("%lld\n", sum);

//    test_f(1);
//    test_f(2);
//    test_f(11);
//    test_f(13);
//    test_f(15);
//    test_f(22);
//    test_f(2222);
//    test_f(1234);
//    test_f(12121212);
//    test_f(1313);
//    test_f(123123123);
//    test_f(123123122);
//    test_f(123123777);

    return 0;
}
