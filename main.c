#include <stdio.h>
#include "calculator.h"

int main(int argc, char* argv[])
{
    List list;
    initList(&list);
    // 423*3411.4312 여기서 실제와 조금 다르게 값이 출력됨.
//    char* str = "1+3";
    FILE* ifp = fopen(argv[1], "r");
    char* str = openFile(ifp);
    makePostfix(str, &list, NULL);
    free(str);
    pDigit digit = makeExpression(&list);
    returnValue(digit);
    printf("\n");
//    viewAll(&list);
}
