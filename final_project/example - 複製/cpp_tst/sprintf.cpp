#include <stdio.h>

int main() {
    char buf[128] = {0};
    const char str[] = "hello world";
    char c = 'a';
    int num = 123;
    float f = 5.4321f;

    sprintf(buf, "string: %s\n", str);
    printf("%s", buf);

    sprintf(buf, "character: %c\n", c);
    printf("%s", buf);

    sprintf(buf, "integer: %d\n", num);
    printf("%s", buf);

    sprintf(buf, "float: %f\n", f);
    printf("%s", buf);

    return 0;
}


//while (strchr("\t ", codePtr) != NULL) codePtr++;
// strchr("\t ", codePtr)