#include "calculator.h"
#include <stdlib.h>
#include <stdio.h>

pNum getNum(int num)
{
    Num nullNode = { 0, NULL };
    pNum tmp = malloc(sizeof(Num));
    if(tmp)
    {
        *tmp = nullNode;
        tmp->num = num;
        return tmp;
    }
    return NULL;
}

int pushNum(pNum* top, int num)
{
    pNum new = getNum(num);
    if(new)
    {
        new->next = *top;
        *top = new;
        return 1;
    }
    return 0;
}

inline int emptyNum(pNum top)
{
    return (top == NULL);
}

int popNum(pNum* top)
{
    if (!emptyNum(*top))
    {
        pNum tmp = *top;
        int result = tmp->num;
        *top = tmp->next;
        free(tmp);
        return result;
    }
    return -1;
}


pOperand getOperand(pDigit digit)
{
    Operand nullNode = { NULL, NULL };
    pOperand tmp = malloc(sizeof(Operand));
    if(tmp)
    {
        *tmp = nullNode;
        tmp->digit = digit;
        return tmp;
    }
    return NULL;
}

int pushOperand(pOperand* top, pDigit digit)
{
    pOperand new = getOperand(digit);
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

pDigit popOperand(pOperand* top)
{
    if (!emptyOperand(*top))
    {
        pOperand tmp = *top;
        pDigit result = tmp->digit;
        *top = tmp->next;
        free(tmp);
        return result;
    }
    return NULL;
}

pOperator getOperator(char op)
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

pExpression getExpression(int num)
{
    Expression nullNode = { 0, NULL, NULL };
    pExpression tmp = malloc(sizeof(Expression));
    if(tmp)
    {
        *tmp = nullNode;
        tmp->num = num;
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

void initList(pList list)
{
    list->head = getExpression(0);
    list->tail = getExpression(0);
    list->head->next = list->tail;
    list->tail->prev = list->head;
}

void addExpression(pList list, int num)
{
    pExpression new = getExpression(num);
    new->prev = list->tail->prev;
    new->next = list->tail;
    list->tail->prev->next = new;
    list->tail->prev = new;
}

void viewAll(pList list)
{
    pExpression seek = list->head->next;

    while(seek != list->tail)
    {
        printf("%d ", seek->num);
        seek = seek->next;
    }
}

pDigit initializeDigit()
{
    pDigit tmp = malloc(sizeof(Digit));
    tmp->before = NULL;
    tmp->beforeSize = 0;
    tmp->after = NULL;
    tmp->afterSize = 0;
    return tmp;
}

void makeExpression(pList list)
{
    pExpression seek = list->head->next;
    pOperand operand = NULL;
    pDigit digit = initializeDigit();
    pNum num = NULL;

    int i = 0;
    int lengthFlag = 0;
    int length[] = { 0, 0 };
    while(seek != list->tail)
    {
        int tmp = seek->num;
        printf("%d ", tmp);
        if(0 <= tmp && tmp <= 9)
        {
            pushNum(&num, tmp);
            length[lengthFlag]++;
        }
        else if(tmp == 46)
        {
            digit->beforeSize = length[0];
            digit->before = num;
            num = NULL;
            lengthFlag = 1;
        }
        else if(tmp == -1)
        {
            if(digit->beforeSize == 0)
            {
                digit->beforeSize = length[0];
                digit->before = num;
            }
            else
            {
                digit->afterSize = length[1];
                digit->after = num;
            }
            length[0] = 0;
            length[1] = 0;
            lengthFlag = 0;
            pushOperand(&operand, digit);
            digit = initializeDigit();
        }
        else
        {
            pDigit secondDigit = popOperand(&operand);
            pDigit firstDigit = popOperand(&operand);
            switch (tmp)
            {
                case 42:
                    pushOperand(&operand, multiply(firstDigit, secondDigit));
                    break;

                case 43:
                    pushOperand(&operand, plus(firstDigit, secondDigit));
                    break;

                case 45:
                    pushOperand(&operand, minus(firstDigit, secondDigit));
                    break;

                case 47:
                    pushOperand(&operand, divide(firstDigit, secondDigit));
                    break;

            }
        }
        seek = seek->next;
//        free(seek->prev);
    }
}

pDigit multiply(pDigit first, pDigit second)
{
//    printf("\n first beforeSize : %d, secondSize : %d \n", first->beforeSize, first->afterSize);
//    printf(" second beforeSize : %d, secondSize : %d \n", second->beforeSize, second->afterSize);
    return first;
}

pDigit plus(pDigit first, pDigit second)
{
    pNum before = NULL;
    pNum after = NULL;
    int beforeSize = 0;
    int afterSize = 0;
    pDigit result = initializeDigit();

    // before 및 after에 pushNum(&before, num), pushNum(&after, num) 을 사용하여 넣어주고 각 자리수를 늘려서 계산해주시면 됩니다.
    printf("\nfirst beforeSize : %d, secondSize : %d\n", first->beforeSize, first->afterSize);
    printf("second beforeSize : %d, secondSize : %d\n", second->beforeSize, second->afterSize);

    printf("\nfirstNumber : ");
    for(int i = 0; i < first->beforeSize; i++)
    {
        printf("%d ", popNum(&(first->before)));
    }
    printf(" . ");
    for(int i = 0; i< first->afterSize; i++)
    {
        printf("%d ", popNum(&(first->after)));
    }

    printf("\nsecondNumber : ");
    for(int i = 0; i < second->beforeSize; i++)
    {
        printf("%d ", popNum(&(second->before)));
    }
    printf(" . ");
    for(int i = 0; i < second->afterSize; i++)
    {
        printf("%d ", popNum(&(second->after)));
    }
    printf("\n\n");

    result->beforeSize = beforeSize;
    result->afterSize = afterSize;
    result->before = before;
    result->after = after;

    return result;
}

pDigit minus(pDigit first, pDigit second)
{
//    printf("\n first beforeSize : %d, secondSize : %d \n", first->beforeSize, first->afterSize);
//    printf(" second beforeSize : %d, secondSize : %d \n", second->beforeSize, second->afterSize);
    return first;
}

pDigit divide(pDigit first, pDigit second)
{
//    printf("\n first beforeSize : %d, secondSize : %d \n", first->beforeSize, first->afterSize);
//    printf(" second beforeSize : %d, secondSize : %d \n", second->beforeSize, second->afterSize);
    return first;
}

void makePostfix(char* str, pList pList, pOperator Operator)
{
    int i = 0;
    List list = *pList;
    pOperator topOperator = Operator;

    while(1)
    {
        int flag = 0;

        if(str[i] == NULL)
        {
            while(!emptyOperator(topOperator))
            {
                addExpression(&list, popOperator(&topOperator));
            }
            break;
        }

        if(str[i] == 46)
        {
            addExpression(&list, str[i]);
        }

        else if((48 <= str[i] && str[i] <= 57))
        {
            addExpression(&list, str[i] - '0');
            if(!((48 <= str[i+1] && str[i+1] <= 57) || (str[i+1] == 46)))
            {
                addExpression(&list, -1);
            }
        }

        else if((str[i] == 40) || (str[i] == 41) || (str[i] == 42) || (str[i] == 43) || (str[i] == 45) || (str[i] == 47))
        {
            flag = 3;
            if(emptyOperator(topOperator))
            {
                pushOperator(&topOperator, str[i]);
            }
            else
            {
                char tmp = popOperator(&topOperator);
                if(str[i] == 41) // )가 나올 때, 우선 순위 1번
                {
                    if((48 <= str[i+1] && str[i+1] <= 57))
                    {
//                        addExpression(&list, -1);
                    }

                    if(tmp != 40)
                    {
                        addExpression(&list, tmp);
                    }

                    while(popOperator(&topOperator) != 40)
                    {
                        addExpression(&list, popOperator(&topOperator));
                    }
                }
                else if((str[i] == 42) || (str[i] == 47)) // * / 나올 때, 우선 순위 2번
                {
                    if((tmp == 43) || (tmp == 45) || (tmp == 40))
                    {
                        pushOperator(&topOperator, tmp);
                        pushOperator(&topOperator, str[i]);
                    }
                    else
                    {
                        addExpression(&list, tmp);
                        pushOperator(&topOperator, str[i]);
                    }
                }
                else if((str[i] == 43) || (str[i] == 45)) // + - 나올 때, 우선 순위 3번
                {

                    if(tmp == 40)
                    {
                        pushOperator(&topOperator, tmp);
                        pushOperator(&topOperator, str[i]);
                    }
                    else
                    {
                        addExpression(&list, tmp);
                        pushOperator(&topOperator, str[i]);
                    }
                }
                else
                {
                    if(i != 0)
                    {
                        if((48 <= str[i-1] && str[i-1] <= 57))
                        {
                            if((tmp == 43) || (tmp == 45) || (tmp == 40))
                            {
                                pushOperator(&topOperator, tmp);
                                pushOperator(&topOperator, str[i]);
                            }
                            else
                            {
                                addExpression(&list, tmp);
                                pushOperator(&topOperator, str[i]);
                            }
                        }
                        else
                        {
                            pushOperator(&topOperator, tmp);
                            pushOperator(&topOperator, str[i]);
                        }
                    }
                }
            }
        }
        i++;
    }
}