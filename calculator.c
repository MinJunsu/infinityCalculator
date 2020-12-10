#include "calculator.h"
#include <stdlib.h>
#include <stdio.h>

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

void insertExpression(pExpression* head, int num)
{
    pExpression* tmp = head;
    while((*tmp)->next != NULL)
    {
        *tmp = (*tmp)->next;
    }

    pExpression new = getExpression(num);
    new->prev = *tmp;
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
            flag = 1;
        }

        else if((48 <= str[i] && str[i] <= 57))
        {
            addExpression(&list, str[i] - '0');
            flag = 2;
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
                        addExpression(&list, -1);
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

        if(str[i+1] == 40)
        {
            if(flag == 1)
            {
                printf("Error\n");
                return 0;
            }
            else if(flag == 2)
            {
                addExpression(&list, -1);
                str[i] = "*";
                continue;
            }
        }
        else if((str[i+1] == 42) || (str[i+1] == 43) || (str[i+1] == 45) || (str[i+1] == 47))
        {
            addExpression(&list, -1);
        }

        if(str[i] == 41)
        {
            if((48 <= str[i+1] && str[i+1] <= 57))
            {
                addExpression(&list, -1);
                str[i] = "*";
                continue;
            }
        }
        i++;
    }
}