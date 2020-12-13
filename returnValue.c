#include "calculator.h"
#include <stdio.h>

void returnValue(pDigit digit)
{
    pNum resultBefore = NULL;
    pNum resultAfter = NULL;

    for(int i = 0; i < digit->beforeSize; i++)
    {
        pushNum(&resultBefore, popNum(&(digit->before)));
    }
    for(int i = 0; i< digit->afterSize; i++)
    {
        pushNum(&resultAfter, popNum(&(digit->after)));
    }

    if(digit->afterSize == 0)
    {
        for(int i = 0; i < digit->beforeSize; i++)
        {
            printf("%d", popNum(&resultBefore));
        }
    }
    else
    {
        int i = 0;
        for(i; i < digit->beforeSize; i++)
        {
            printf("%d", popNum(&resultBefore));
        }
        printf(".");

        for(int j = 0; j < digit->afterSize; j++)
        {
            printf("%d", popNum(&resultAfter));
        }
    }
}