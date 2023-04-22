#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    FILE* fp = fopen("students.bin", "r");
 
    if (!fp)
        printf("Can't open file\n");
 
    else {
        int column = 0;
        char symbol;
        int count = 0;
        int gender = 0;
        char sub[2];
        int person = 0;
        while (fread(&symbol, sizeof(char), 1, fp) == 1) {
            while (!symbol) {
                fread(&symbol, sizeof(char), 1, fp);
            }
            if (column == 0) {
                int surname = symbol - '0';
                for (int i = 0; i < surname; ++i) {
                    fread(&symbol, sizeof(char), 1, fp);
                    while (!symbol) {
                        fread(&symbol, sizeof(char), 1, fp);
                    }
                }
                ++column;
            }
            if (column == 1) {
                for (int i = 0; i < 4; ++i) {
                    fread(&symbol, sizeof(char), 1, fp);
                    while (!symbol) {
                        fread(&symbol, sizeof(char), 1, fp);
                    }
                }
                ++column;
            }
            if (column == 2) {
                fread(&symbol, sizeof(char), 1, fp);
                while (!symbol) {
                    fread(&symbol, sizeof(char), 1, fp);
                }
                if (symbol == 'f') {
                    gender = 1;
                } else {
                    gender = 0;
                }
                ++column;
            }
            if (column == 3) {
                for (int i = 0; i < 2; ++i) {
                    fread(&symbol, sizeof(char), 1, fp);
                    while (!symbol) {
                        fread(&symbol, sizeof(char), 1, fp);
                    }
                }
                ++column;
            }
            if (column == 4) {
                fread(&symbol, sizeof(char), 1, fp);
                while (!symbol) {
                    fread(&symbol, sizeof(char), 1, fp);
                }
                sub[0] = symbol;
                ++column;
            }
            if (column == 5) {
                fread(&symbol, sizeof(char), 1, fp);
                while (!symbol) {
                    fread(&symbol, sizeof(char), 1, fp);
                }
                sub[1] = symbol;
                ++column;
            }
            if (column == 6) {
                fread(&symbol, sizeof(char), 1, fp);
                while (!symbol) {
                    fread(&symbol, sizeof(char), 1, fp);
                }
                if (gender == 1) {
                    if (symbol != sub[0] && symbol != sub[1] && sub[0] != sub[1]) {
                        ++count;
                    }
                }
                column = 0;
            }
        }
        fclose(fp);
        printf("%d\n", count);
    }
    return 0;
}
