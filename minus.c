#include "calculate.h"

pDigit minus(pDigit first, pDigit second)
{
    pDigit result = initializeDigit();

    if(first->beforeSize < second->beforeSize)
    {
        pDigit tmp = first;
        first = second;
        second = tmp;
    }
    else if(first->beforeSize == second->beforeSize)
    {
        pNum pFirst = first->before, pSecond = second->before;
        pNum firstTmp = NULL; pNum secondTmp = NULL;
        int firstNum, secondNum;

        for(int i = 0; i < first->beforeSize; i++)
        {
            firstNum = popNum(&(first->before));
            secondNum = popNum(&(second->before));
            pushNum(&firstTmp, firstNum);
            pushNum(&secondTmp, secondNum);
        }

        for(int i = 0; i < first->beforeSize; i++)
        {
            pushNum(&(first->before), popNum(&firstTmp));
            pushNum(&(second->before), popNum(&secondTmp));
        }


        if(firstNum < secondNum)
        {
            pDigit tmp = first;
            first = second;
            second = tmp;
        }
    }

    int beforeSize = max(first->beforeSize, second->beforeSize);
    int afterSize = max(first->afterSize, second->afterSize);
    int carry=0;
    int a, b;
    pNum pfirst, psecond,presult;

    pfirst = first->after;
    psecond = second->after;
    presult = result->after;

    for (int i = 0; i < afterSize; i++) {
        if (afterSize - i > first->afterSize) {
            a = 0;
        }
        else {
            a = pfirst->num;
            pfirst = pfirst->next;
        }

        if (afterSize - i > second->afterSize) {
            b = 0;
        }
        else {
            b = psecond->num;
            psecond = psecond->next;
        }

        if (a - carry < b) {
            a = 10 + a - carry - b;
            carry = 1;
        }
        else {
            a = a - carry - b;
            carry = 0;
        }

        if (presult == NULL) {
            presult = malloc( sizeof( Num ) );
            presult->num = a;
            presult->next = NULL;
            result->after = presult;
        }
        else {
            presult->next = malloc( sizeof( Num ) );
            presult->next->num = a;
            presult->next->next = NULL;
            presult = presult->next;
        }
        result->afterSize++;
    }

    pfirst = first->before;
    psecond = second->before;
    presult = result->before;

    for (int i = 0; i < beforeSize; i++) {
        if (i >= first->beforeSize) {
            a = 0;
        }
        else {
            a = pfirst->num;
            pfirst = pfirst->next;
        }

        if (i >= second->beforeSize) {
            b = 0;
        }
        else {
            b = psecond->num;
            psecond = psecond->next;
        }

        if (a - carry < b) {
            a = 10 + a - carry - b;
            carry = 1;
        }
        else {
            a = a - carry - b;
            carry = 0;
        }

        if (presult == NULL) {
            presult = malloc( sizeof( Num ) );
            presult->num = a;
            presult->next = NULL;
            result->before = presult;
        }
        else {
            presult->next = malloc( sizeof( Num ) );
            presult->next->num = a;
            presult->next->next = NULL;
            presult = presult->next;
        }
        result->beforeSize++;
    }

    int end = result->afterSize;
    for (int i = 0; i < end; i++) {
        if (result->after->num == 0) {
            pNum temp = result->after->next;
            free( result->after );
            result->after = temp;
            result->afterSize--;
        }
        else {
            break;
        }
    }

    end = result->beforeSize;
    pNum lastNonZero = NULL;
    pNum cur = result->before;
    for (int i = 0; i < end; i++) {
        if (cur != NULL && cur->num != 0) {
            lastNonZero = cur;
        }
        cur = cur->next;
    }

    while (lastNonZero != NULL) {
        pNum temp = lastNonZero->next;
        lastNonZero->next = NULL;
        if (lastNonZero->num == 0) {
            free( lastNonZero );
            result->beforeSize--;
        }
        lastNonZero = temp;
    }

    //    printf("\n first beforeSize : %d, secondSize : %d \n", first->beforeSize, first->afterSize);
    //    printf(" second beforeSize : %d, secondSize : %d \n", second->beforeSize, second->afterSize);
    return result;
}