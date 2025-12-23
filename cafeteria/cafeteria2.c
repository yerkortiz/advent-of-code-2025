#include <stdio.h>
#include <stdlib.h>

struct interval {
    long long lo;
    long long hi;
};

int compare_intervals(const void *a, const void *b) {
    struct interval *i1 = (struct interval *)a;
    struct interval *i2 = (struct interval *)b;
    
    if (i1->lo < i2->lo) return -1;
    if (i1->lo > i2->lo) return 1;
    return 0;
}

int main(int argc, char** argv) {
    char interval_line[100];
    struct interval intervals[10000];
    long long intervals_count = 0;
    while(fgets(interval_line, 100, stdin)) {
        struct interval current;
        if (sscanf(interval_line, "%lld-%lld", &current.lo, &current.hi) == 2) {
            intervals[intervals_count] = current;
            ++intervals_count;     
        }
    }

    qsort(intervals, intervals_count, sizeof(struct interval), compare_intervals);

    long long current = 0;
    long long fresh_ingredients = 0;
    for (long long i = 0; i < intervals_count; ++i) {
        if(current <= intervals[i].lo) current = intervals[i].lo;
        if(current <= intervals[i].hi) {
            fresh_ingredients += intervals[i].hi - current + 1;
            current = intervals[i].hi + 1;
        }
    }

    printf("fresh ingredients = %lld\n", fresh_ingredients);
    return 0;
}
