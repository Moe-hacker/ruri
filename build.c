#include <stdlib.h>

int main(void) {
    int ret = system("cc src/*.c src/easteregg/*.c -o ruri -lcap -lseccomp -lpthread");
    return ret == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
