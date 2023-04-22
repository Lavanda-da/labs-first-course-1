#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    FILE* fp = fopen("students2.csv", "r");
    FILE* out = fopen("students.bin", "r+b");
    int length = 0;
    char s;
    while (fread(&s, sizeof(char), 1, out) == 1) {
        ++length;
    }
    fseek(out, length, SEEK_CUR);
    int n = 100;
    char buffer[n];
    int row = 0;
    int column = 0;
    while (fgets(buffer, n, fp)) {
        column = 0;
        ++row;
        if (row == 1)
            continue;
        char surname[100];
        char count = '0';
        for (int i = 0; i < n; ++i) {
            if (buffer[i] == '\n') {
                break;
            }
            if (buffer[i] == ',') {
                ++column;
                continue;
            }
            if (column == 0) {
                ++count;
                surname[(count - '0') - 1] = buffer[i];
            }
            if (column == 1) { 
                if (count != -1) {
                    for (int i = count - '0'; i < 100; ++i) {
                        surname[i] = ' ';
                    }
                    fwrite(&count, sizeof(char), 1, out);
                    for (int i = 0; i < count - '0'; ++i) {
                        char symbol = surname[i];
                        fwrite(&symbol, sizeof(char), 1, out);
                    }
                    count = -1;
                }
                fwrite(&buffer[i], sizeof(char), 1, out);
            }
            if (column == 2) {
                fwrite(&buffer[i], sizeof(char), 1, out);
            }
            if (column == 3) {
                fwrite(&buffer[i], sizeof(char), 1, out);
            }
            if (column == 4) {
                fwrite(&buffer[i], sizeof(char), 1, out);
            }
            if (column == 5) {
                fwrite(&buffer[i], sizeof(char), 1, out);
            }
            if (column == 6) {
                fwrite(&buffer[i], sizeof(char), 1, out);
                break;
            }
        }
    }
    fclose(fp);
    fclose(out);
    return 0;
}
