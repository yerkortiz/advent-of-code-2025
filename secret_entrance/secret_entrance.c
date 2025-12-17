#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

const int lines_capacity = 16;
int line_length = 6;
const int match_count = 0;
const int max_value = 100;

int rotate_dial(int position, int rotation) {
    return ((max_value + position) % max_value + rotation) % max_value;
}

int main(int argc, char** argv) {
    char buffer[line_length]; 
    int rotation;
    int start = 50;
    int password = 0;

    while(fgets(buffer, line_length, stdin) != NULL) {
        switch(buffer[0]) {
            case 'L':
                rotation = -atoi(&buffer[1]);
                break;
            case 'R':
                rotation = atoi(&buffer[1]);
                break;
            default:
                continue;
        }
        
        if(rotation >= 0) {
            password = password + ((start + rotation) / max_value);
        } else {
            password = password + ((start - rotation) / max_value);
        }
        start = rotate_dial(start, rotation);
        if(start == 0) ++password;
    }

    printf("password = %d", password);
    return 0;
}
