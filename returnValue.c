#include "calculator.h"

void returnValue(pDigit digit)
{
    // 새롭게 저장할 pNum을 초기화 해준다.
    pNum resultBefore = NULL;
    pNum resultAfter = NULL;
//    printf("before : %d, after : %d", digit->beforeSize, digit->afterSize);
    // 만약 숫자가 음수면 - 를 추가 시켜준다.
    if(!(digit->positive))
    {
        printf("-");
    }

    // 스택형태의 숫자를 정상적으로 출력하기 위해 뒤집어주는 과정
    for(int i = 0; i < digit->beforeSize; i++)
    {
        pushNum(&resultBefore, popNum(&(digit->before)));
    }
    for(int i = 0; i< digit->afterSize; i++)
    {
        pushNum(&resultAfter, popNum(&(digit->after)));
    }

    // 만약 뒤에 자리가 없다면
    if(digit->afterSize == 0)
    {
        // 단순히 정수열만 출력하고
        for(int i = 0; i < digit->beforeSize; i++)
        {
            printf("%d", popNum(&resultBefore));
        }
        printf(".0");
    }
    else
    {
        // 아니면 뒤에 자리수도 출력해준다.
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