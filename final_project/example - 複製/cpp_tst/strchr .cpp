#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "This is a c-style string";
    char *pch;
    pch = strchr(str, 's');
    while (pch != NULL) {
        printf("found at %d\n", pch-str+1);
        pch = strchr(pch+1, 's');
    }
    
    return 0;
}