#include "calculate.h"

pDigit divide(pDigit first, pDigit second)
{
    pDigit digit = initializeDigit();
    int maxCount = first->afterSize > second->afterSize ? first->afterSize : second->afterSize;
    Num tmpFirst, tmpSecond;
    if((first->afterSize != 0) || (second->afterSize != 0))
    {
        if(first->beforeSize == 1)
        {
            int tmp = popNum(&(first->before));
            if(tmp == 0)
            {
                first->beforeSize = 0;
            }
            else
            {
                pushNum(&(first->before),tmp);
            }
        }

        if(second->beforeSize == 1)
        {
            int tmp = popNum(&(second->before));
            if(tmp == 0)
            {
                second->beforeSize = 0;
            }
            else
            {
                pushNum(&(second->before),tmp);
            }
        }

        if(first->afterSize > second->afterSize)
        {
            for(int i = 0; i < (first->afterSize-second->afterSize); i++)
            {
                pushNum(&tmpFirst, popNum(&(first->after)));
                pushNum(&tmpSecond, 0);
            }

            for(int i = 0; i < second->afterSize; i++)
            {
                pushNum(&tmpFirst, popNum(&(first->after)));
                pushNum(&tmpSecond, popNum(&(second->after)));
            }
        }
        else
        {
            for(int i = 0; i < (second->afterSize-first->afterSize); i++)
            {
                pushNum(&tmpFirst, 0);
                pushNum(&tmpSecond, popNum(&(second->after)));
            }

            for(int i = 0; i < first->afterSize; i++)
            {
                pushNum(&tmpFirst, popNum(&(first->after)));
                pushNum(&tmpSecond, popNum(&(second->after)));
            }
        }
        for(int i = 0; i < maxCount; i++)
        {
            pushNum(&(first->before), popNum(&(tmpFirst)));
            pushNum(&(second->before), popNum(&(tmpSecond)));
        }
        first->beforeSize += maxCount;
        second->beforeSize += maxCount;
        first->afterSize = 0;
        second->afterSize = 0;
    }

    int tmp = first->beforeSize - second->beforeSize;
    pDigit result = initializeDigit();
    pDigit sum = initializeDigit();

    if(tmp >= 0)
    {
        result->beforeSize = tmp + 1;
    }
    else
    {
        result->afterSize = (abs(tmp) - 1);
    }
    round(second, tmp);
//    printf("\nfirst: ");
//    returnValue(copyDigit(first));
    int count = 0;
    int posCount = 0;
    while(1)
//    for(int i = 0; i < 10; i++)
    {
        if(isSame(first, sum))
        {
            break;
        }

        else
        {
            int i = 0;
//            printf("\nsecond: ");
//            returnValue(copyDigit(second));
            for(;i < 9; i++)
            {
                if(isBig(plus(copyDigit(second), copyDigit(sum)), first))
                {
                    sum = plus(copyDigit(second), copyDigit(sum));
//                    printf("\nsum: ");
//                    returnValue(copyDigit(sum));
                }
                else
                {
                    if(isSame(first, plus(copyDigit(second), copyDigit(sum))))
                    {
                        sum = plus(copyDigit(second), copyDigit(sum));
                    }
                    break;
                }
            }
//            printf("\n\n");
            if(tmp < 0)
            {
                count++;
                pushNum(&(result->after), i);
                result->afterSize++;
            }
            else
            {
                posCount++;
                pushNum(&(result->before), i);
            }

            tmp--;
            round(second, -1);
        }
    }

//    printf("\n");
//    returnValue(copyDigit(first));
//    printf("\n");
//    returnValue(copyDigit(second));

//    while(1)
//    {
//
//    }

    pNum tmpNum = NULL;
    for(int i = 0; i < result->afterSize; i++)
    {
        if(i < count)
        {
            pushNum(&tmpNum, popNum(&(result->after)));
        }
        else
        {
            pushNum(&tmpNum, 0);
        }
    }

    for(int i = 0; i < result->afterSize; i++)
    {
        pushNum(&(result->after), popNum(&tmpNum));
    }

    if(result->beforeSize == 0)
    {
        pushNum(&(result->before), 0);
        result->beforeSize = 1;
    }

    for(int i = 0; i < (result->beforeSize - posCount); i++)
    {
        pushNum(&(result->before), 0);
    }

    return result;
}