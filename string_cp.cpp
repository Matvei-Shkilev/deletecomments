#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>


void text1(FILE *fp, FILE *fs, char symbol, char pred_symbol) {
    fprintf(fs, "%c", pred_symbol);
    fprintf(fs, "%c", symbol);
    while ((symbol = fgetc(fp)) != EOF) {
        fprintf(fs, "%c", symbol);
        if (symbol == '"' && pred_symbol != '\\') {
            break;
        }
        pred_symbol = symbol;
    }
}


void text2(FILE* fp, FILE* fs, char* pred_symbol, char* pred2_symbol) {
    char symbol;
    fprintf(fs, "%c", *pred_symbol);
    while ((symbol = fgetc(fp)) != EOF) {

        if (symbol == '\'' && *pred_symbol != '\\' && *pred2_symbol != '\\') {
            fprintf(fs, "%c", symbol);
            break;
        }

        *pred2_symbol = *pred_symbol;
        *pred_symbol = symbol;
    }
}


void skip_com(FILE* fp, int f_mult) {
    char symbol;
    char pred_symbol = 0;
    if (f_mult) {
        while ((symbol = fgetc(fp)) != EOF) {
            if (symbol == '/' && pred_symbol == '*') {
                break;
            }
            pred_symbol = symbol;
        }
    }
    else {
        while ((symbol = fgetc(fp)) != EOF) {   
            if (pred_symbol == '\\' && symbol == '\n') {
                fgetc(fp);
            }
            if (symbol == '\n') {
                break;
            }

            pred_symbol = symbol;
        }
    }
}




void check_str(FILE* fp, FILE* fs)
{
    char symbol = 0;
    char pred_symbol = 0;
    char pred2_symbol = 0;


    while (!feof(fp)) {
        pred2_symbol = pred_symbol;
        pred_symbol = symbol;
        symbol = fgetc(fp);
        if (symbol == '"' ){
            printf("%c %c", pred_symbol, symbol);
            text1(fp, fs, symbol, pred_symbol);
            pred_symbol = 0;
            continue;
        }
        if (pred_symbol == '/' && symbol == '/') {
            pred_symbol = 0;
            skip_com(fp, 0);
            continue;
        }
        if (symbol == '*' && pred_symbol == '/') {
            pred_symbol = 0;
            skip_com(fp, 1);
            continue;
        }
        if (symbol == '\'') {
            text2(fp, fs, &pred_symbol, &pred2_symbol);
            pred2_symbol = 0;
            continue;
        }
        if (pred_symbol != 0) {
            fprintf(fs, "%c", pred_symbol);
        }
        pred2_symbol = pred_symbol;
        pred_symbol = symbol;
    }
    
}

int main() {

    FILE* fs; 
    FILE* fp; 

    fs = fopen("test.wc", "w");
    fp = fopen("test.c", "r");

    check_str(fp, fs);

    fclose(fp);
    fclose(fs);

    return 0;
}
