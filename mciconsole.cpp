#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>


int main() {
    for (;;) {
        char* line = readline("mci: ");
        if (!line) {
            break;
        }

        const int resultSize = 4096;
        char result[resultSize + 1] = {0};
        MCIERROR error = mciSendString(line, result, resultSize, NULL);
        if (error) {
            char str[resultSize + 1] = {0};
            if (!mciGetErrorString(error, str, resultSize)) {
                strcpy(str, "Unknown Error");
            }
            printf("Error: code %d -- %s\n", error, str);
        } else if (result[0]) {
            printf("Result: %s\n", result);
        }

        free(line);
    }
}
