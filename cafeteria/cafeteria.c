#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool in_range(long long lo_ranges[], long long hi_ranges[], long long range_count, long long ingredient){
    for(long long i = 0; i < range_count; ++i) {
        if(lo_ranges[i] <= ingredient && hi_ranges[i] >= ingredient) return true;
    }
    return false;
}
int main() {
    long long lo_ranges[1000];
    long long hi_ranges[1000];
    long long available_ingredients[1000];
    
    long long range_count = 0;
    long long ingredient_count = 0;
    
    char line[100];
    
    while (fgets(line, sizeof(line), stdin) != NULL) {
        if (line[0] == '\n') break;          
        long long a, b;
        if (sscanf(line, "%lld-%lld", &a, &b) == 2) {
            lo_ranges[range_count] = a;
            hi_ranges[range_count] = b;
            range_count++;
        }
    }
    
    long long fresh_ingredient_count = 0;

    while (fgets(line, sizeof(line), stdin) != NULL) {
        long long num;
        if (sscanf(line, "%lld", &num) == 1) {
            available_ingredients[ingredient_count] = num;
        } else {
            break;
        }
        if (in_range(lo_ranges, hi_ranges, range_count, available_ingredients[ingredient_count])) {
            ++fresh_ingredient_count;
        }
        ++ingredient_count;
    }
    
    printf("%lld\n", fresh_ingredient_count);
    return 0;
}
