#include <stdio.h>
#include <stdlib.h>
#include "calculator.h"

pOperand getOperand(int num)
{
    Operand nullNode = { 0, NULL };
    pOperand tmp = malloc(sizeof(Operand));
    if(tmp)
    {
        *tmp = nullNode;
        tmp->num = num;
        return tmp;
    }
    return NULL;
}

int pushOperand(pOperand* top, int num)
{
    pOperand new = getOperand(num);
    if(new)
    {
        new->next = *top;
        *top = new;
        return 1;
    }
    return 0;
}

inline int emptyOperand(pOperand top)
{
    return (top == NULL);
}

int popOperand(pOperand* top)
{
    if (!emptyOperand(*top))
    {
        pOperand tmp = *top;
        int result = tmp->num;
        *top = tmp->next;
        free(tmp);
        return result;
    }
    return -2;
}

pOperand getOperator(char op)
{
    Operator nullNode = { 0, NULL };
    pOperator tmp = malloc(sizeof(Operator));
    if(tmp)
    {
        *tmp = nullNode;
        tmp->operator = op;
        return tmp;
    }
    return NULL;
}

int pushOperator(pOperator* top, char op)
{
    pOperator new = getOperator(op);
    if(new)
    {
        new->next = *top;
        *top = new;
        return 1;
    }
    return 0;
}

inline int emptyOperator(pOperator top)
{
    return (top == NULL);
}

char popOperator(pOperator* top)
{
    if (!emptyOperator(*top))
    {
        pOperator tmp = *top;
        char result = tmp->operator;
        *top = tmp->next;
        free(tmp);
        return result;
    }
    return -1;
}

int main()
{
    char* str = "233423541354.143543524352+2342314123413.34523453-321341241.12341234*3423121212.234523232323324324325423*(73729494719444.4239508234+41341312415454524.123787970473713980712477421675184631)";

    int i = 0;
    pOperand topOperand = NULL;
    pOperand topOperator = NULL;
    while(1)
    {
        if(str[i] == NULL)
        {
            break;
        }

        if(str[i] == 46)
        {
            pushOperand(&topOperand, -1);
        }

        else if((48 <= str[i] && str[i] <= 57))
        {
            pushOperand(&topOperand, str[i] - '0');
        }

        else if((str[i] == 42) || (str[i] == 43) || (str[i] == 45) || (str[i] == 47))
        {
            pushOperator(&topOperator, str[i]);
        }



        i++;
    }

    for(int i = 0; i < 5; i++)
    {
        printf("%C", popOperator(&topOperator));
    }

}
