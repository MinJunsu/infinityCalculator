#define _CRT_SECURE_NO_WARRINGS // fopen 보안 경고로 인한 컴파일 에러 방지
#include "calculator.h"

char* openFile(FILE* ifp)
{
    if(ifp == NULL)
    {
        printf("File not detected!\n");
        exit(0);
    }
    char* expr = NULL;
    char c;
    int size = 0;
    while(fscanf(ifp, "%c", &c) == 1) size++;
    expr = (char*)malloc(sizeof(char) * (size + 1));
    rewind(ifp);
    // 파일 읽었던 기록 지우고 다시 처음으로.
    int i = 0;
    while(fscanf(ifp, "%c", &c) == 1)
    {
        *(expr + i++) = c;
    }
    *(expr + i) = '\0';
    return expr;
}