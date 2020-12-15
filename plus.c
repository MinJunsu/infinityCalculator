#include "calculate.h"

pNum beforeCal(pNum max, pNum min, int max_before, int min_before, bool carry, bool* result)
{
    pNum before = NULL;
    while (max_before != 0)
    {
        int tmpbefore;
        if(min_before > 0)
        {
            tmpbefore = popNum(&max) + popNum(&min);
        }
        else
        {
            tmpbefore = popNum(&max);
        }
        if (carry)
        {
            tmpbefore++;
            carry = false;
        }
        if ((tmpbefore / 10) >= 1)
        {
            carry = true;
            tmpbefore = tmpbefore - 10;
        }
        pushNum(&before, tmpbefore);
        max_before--;
        min_before--;
    }

    if(max_before == 0)
    {
        if (carry)
        {
            pushNum(&before, 1);
        }
    }
    *result = carry;
    return before;
}

pNum afterCal(pNum max, pNum min, int max_after, int min_after, bool* result)
{
    pNum after = NULL;
    bool carry = false;
    //연산해야 할 상대 숫자가 없으면 그 수를 그대로 스택에 쌓는다.
    while (max_after != min_after)
    {
        int new = popNum(&max);
        pushNum(&after, new);
        max_after--;
    }
    //그 외의 경우 연산해야 할 수가 없을 때까지 더하기 연산
    while (max_after != 0)
    {
        int tmpafter = popNum(&max) + popNum(&min);
        if (carry)
        {
            tmpafter++;
            carry = false;
        }
        if ((tmpafter / 10) >= 1)
        {
            carry = true;
            tmpafter = tmpafter - 10;
        }
        pushNum(&after, tmpafter);

        max_after--;
        min_after--;
    }

    *result = carry;
    return after;
}

pDigit plus(pDigit first, pDigit second)
{
    pNum before = NULL;
    pNum after = NULL;
    int beforeSize = 0;
    int afterSize = 0;
    pDigit result = initializeDigit();
    if(first->positive)
    {
        result->positive = true;
    }
    else
    {
        result->positive = false;
    }

//    printf("first: ");
//    returnValue(copyDigit(first));
//    printf(", second: ");
//    returnValue(copyDigit(second));
//    printf("\n");
//
//    printf("first b : %d, first a: %d", first->beforeSize, first->afterSize);
//    printf(" second b : %d, second a: %d\n", second->beforeSize, second->afterSize);

    if((first->beforeSize == 0) && (first->afterSize == 0))
    {
        return second;
    }
    if((second->beforeSize == 0) && (second->afterSize == 0))
    {
        return first;
    }

    int firstBeforesize = first->beforeSize;
    int secondBeforesize = second->beforeSize;
    int firstAftersize = first->afterSize;
    int secondAftersize = second->afterSize;

    bool carry = false;
    bool resultFlag = 0;

    int maxAftersize;
    int maxBeforesize;

    //size 비교 후 더하기 연산, 결과값 size 측정
    if (firstAftersize > secondAftersize)
    {
        maxAftersize = firstAftersize;
        after = afterCal(first->after, second->after, firstAftersize, secondAftersize, &carry);
        if(firstBeforesize > secondBeforesize)
        {
            maxBeforesize = firstBeforesize;
            before = beforeCal(first->before, second->before, firstBeforesize, secondBeforesize, carry, &resultFlag);
        }
        else
        {
            maxBeforesize = secondBeforesize;
            before = beforeCal(second->before, first->before, secondBeforesize, firstBeforesize, carry, &resultFlag);
        }
    }
    else
    {
        maxAftersize = secondAftersize;
        after = afterCal(second->after, first->after, secondAftersize, firstAftersize, &carry);
        if (firstBeforesize > secondBeforesize)
        {
            maxBeforesize = firstBeforesize;
            before = beforeCal(first->before, second->before, firstBeforesize, secondBeforesize, carry, &resultFlag);
        }
        else
        {
            maxBeforesize = secondBeforesize;
            before = beforeCal(second->before, first->before, secondBeforesize, firstBeforesize, carry, &resultFlag);
        }
    }

    //결과값 size 설정
    afterSize = maxAftersize;
    if (resultFlag)
    {
        beforeSize = maxBeforesize + 1;
    }
    else
    {
        beforeSize = maxBeforesize;
    }

    pNum resultBefore = NULL;
    pNum resultAfter = NULL;

    for (int i = 0; i < afterSize; i++)
    {
        int new = popNum(&after);
        pushNum(&resultAfter, new);
    }
    for (int i = 0; i < beforeSize; i++)
    {
        int new = popNum(&before);
        pushNum(&resultBefore, new);
    }


    result->beforeSize = beforeSize;
    result->afterSize = afterSize;
    result->before = resultBefore;
    result->after = resultAfter;

    return result;
}