#include "calculate.h"

pDigit multiply(pDigit first, pDigit second)
{
    if((first->beforeSize + first->afterSize) < (second->beforeSize + second->afterSize))
    {
        pDigit tmp = first;
        first = second;
        second = tmp;
    }

    pDigit sum = initializeDigit();
    for(int i = 0; i < second->afterSize; i++)
    {
        sum = plus(mul(copyDigit(first), popNum(&(second->after)), -(second->afterSize - i)), copyDigit(sum));
//        returnValue(copyDigit(sum));
//        printf("\n");
    }
    for(int i = 0; i < second->beforeSize; i++)
    {
//        printf("dd : %d\n", i);
        sum = plus(mul(copyDigit(first), popNum(&(second->before)), i), copyDigit(sum));
//        returnValue(copyDigit(sum));
//        printf("\n");
//        printf("\n");
//        sum = plus(mul(copyDigit(first), popNum(&(second->before)), i), sum);
    }
    return sum;
}

pDigit mul(pDigit digit, int x, int under)
{
    pNum back = NULL;
    pNum front = NULL;
    pDigit result = initializeDigit();
    int new;

    if(under > 0)
    {
        pNum tmpNum = NULL;
        if(digit->afterSize != 0)
        {
            for(int i = 0; i < digit->afterSize; i++)
            {
                pushNum(&tmpNum, popNum(&(digit->after)));
            }

            for(int i = 0; i < digit->afterSize; i++)
            {
                if(i < under)
                {
                    pushNum(&(digit->before), popNum(&tmpNum));
                }
                else
                {
                    pushNum(&(digit->after), popNum(&tmpNum));
                }
            }
        }
        else
        {
            for(int i = 0; i < under; i++)
            {
                pushNum(&(digit->before), 0);
            }
        }
        digit->beforeSize += under;
        digit->afterSize -= under;
    }

    else if (under < 0)
    {
        pNum tmpNum = NULL;
        if(digit->afterSize != 0)
        {
            for(int i = 0; i < digit->afterSize; i++)
            {
                pushNum(&tmpNum, popNum(&(digit->after)));
            }
            for(int i = 0; i < abs(under); i++)
            {
                if(digit->beforeSize > i)
                {
                    pushNum(&tmpNum, popNum(&(digit->before)));
                }
                else
                {
                    pushNum(&tmpNum, 0);
                }
            }
            for(int i = 0; i < (digit->afterSize + abs(under)); i++)
            {
                pushNum(&(digit->after), popNum(&tmpNum));
            }
        }
        else
        {
            for(int i = 0; i < abs(under); i++)
            {
                int tmp = popNum(&(digit->before));
                pushNum(&tmpNum, tmp);
            }
            for(int i = 0; i < abs(under); i++)
            {
                pushNum(&(digit->after), popNum(&tmpNum));
            }
        }
        digit->beforeSize -= abs(under);
        digit->afterSize += abs(under);
    }

    if(digit->beforeSize < 0)
    {
        digit->beforeSize = 0;
    }
    if(digit->afterSize < 0)
    {
        digit->afterSize = 0;
    }

//    printf("\n\nbefore : %d, after : %d\n", digit->beforeSize, digit->afterSize);
//    printf("\n\ndigit: ");
//    returnValue(digit);
//    printf("\n\n");

    int afterSize = digit->afterSize;
    int carry = 0;
    bool flag = false;
    if(x != 0)
    {
        for(int i= 0; i < digit->afterSize; i++)
        {
            new = (popNum(&(digit->after)) * x) + carry;
            carry = new / 10;
            new = new - (carry * 10);
            if(new != 0)
            {
                flag = true;
                pushNum(&back, new);
            }
            else
            {
                if(flag)
                {
                    pushNum(&back, new);
                }
                else
                {
                    afterSize--;
                }
            }
        }
        for(int i = 0; i < digit->beforeSize; i++)
        {
            new = (popNum(&(digit->before)) * x) + carry;
            carry = new / 10;
            new = new - (carry * 10);

            pushNum(&front, new);
        }

        if(carry != 0)
        {
            pushNum(&front, carry);
            digit->beforeSize++;
        }

        pNum resultBefore = NULL;
        pNum resultAfter = NULL;

        for(int i = 0; i < digit->beforeSize; i++)
        {
            pushNum(&resultBefore, popNum(&front));
        }
        for(int i = 0; i < afterSize; i++)
        {
            int tmp = popNum(&back);
            pushNum(&resultAfter, tmp);
        }

        result->beforeSize = digit->beforeSize;
        result->afterSize = afterSize;
        result->before = resultBefore;
        result->after = resultAfter;
    }

//    printf("result : ");
//    returnValue(result);
//    printf("\n");


    return result;
}