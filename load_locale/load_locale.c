#include <windows.h>
#include <stdio.h>


#define OUTPUT_SIZE 500
#define MIN_ID 101
#define MAX_ID 0x540


void shift_single(char* input) {
    // We shift away the current character
    const int length = strlen(input);
    if (length == 0) return;
    memmove(input, input + 1, length - 1);
    input[length - 1] = '\0';
}

void shift_all(char* input, char x) {
    char* tmp = NULL;
    while ((tmp = strchr(input, x)) != NULL) {
        shift_single(tmp);
    }
}



void replace_all(char* input, char x, char y) {
    int length = strlen(input);
    for (int i = 0; i < length; i++) {
        if (input[i] == x) {
            input[i] = y;
        }
    }
}

int main () {
    char output[OUTPUT_SIZE];
    output[0] = '\0';

    HMODULE mod = LoadLibraryA("../LANG/en-US.dll");
    if (mod == NULL) {
        printf("Error Loading DLL: %ld\n", GetLastError());
        return 1;
    }
    //const char* text = "test \"hello\" boo";
    //memcpy(output, text, strlen(text));
    //shift_all(output, '"');
    //printf("'%s'", output);
    //return 0;
    printf("[\n");
    for (int i = MIN_ID; i < MAX_ID; i++) {
        int count = LoadStringA(mod, i, output, OUTPUT_SIZE);
        // printf("Read Count: %d\n", count);
        if (count == 0) {
            //printf("%d %x Error Loading String: %d\n", i, i, GetLastError());
            continue;
        }

        for (unsigned char j = 127; j < 255; j++) {
            shift_all(output, j);
        }
    
        // Dunno how many of these replacements are needed.
        replace_all(output, ' ', '_');
        replace_all(output, 0x08, 'b');
        replace_all(output, '-', '_');
        shift_all(output, 0xff);
        shift_all(output, '\'');
        shift_all(output, '"');
        shift_all(output, '\n');
        shift_all(output, '\t');
        shift_all(output, '!');
        shift_all(output, '?');
        shift_all(output, '.'); 

        // We don't use hexadecimal here because my gson script failed to parse it
        // We put the _%x as a suffix to defend against duplicates.
        printf("{ \"id\": %d, \"text\": \"%s_%x\" }", i, output, i);
        if (i < MAX_ID-3) {
            printf(",\n");
        }
        //printf("%d %x  '%s'\n", i, i, ioutput);
    }
    printf("]");
    return 0;
}

