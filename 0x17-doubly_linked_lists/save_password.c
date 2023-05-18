#include <stdio.h>
#include <string.h>

int main(void) {
    char password[] = "en C Pyfo neZ";

    FILE *file = fopen("100-password", "w");
    if (file != NULL) {
        fprintf(file, "%s", password);
        fclose(file);
    }

    return 0;
}
