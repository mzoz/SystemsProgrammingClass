#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char * argv){
    char goodbye[100] = "Goodbye cruel world!asdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfxzcvzxcvzxcvzxcvzxcvzxcvzxcvzxxcvzxcvzxcqwerqwerqwerqwerqwer";
    char *p = goodbye;

    while(*p){
        printf("%c", toupper(*p));
        p++;
    }
}
