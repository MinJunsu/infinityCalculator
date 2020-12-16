#include "calculate.h"
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

int emptyNum(pNum top)
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

int emptyOperand(pOperand top)
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

int emptyOperator(pOperator top)
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
    tmp->positive = true;
    return tmp;
}



pDigit makeExpression(pList list)
{
    pExpression seek = list->head->next;
    pOperand operand = NULL;
    pDigit digit = initializeDigit();
    pNum num = NULL;
    bool digitFlag = true;

    int lengthFlag = 0;
    int length[] = { 0, 0 };
    while(seek != list->tail)
    {
        int tmp = seek->num;
        if(0 <= tmp && tmp <= 9)
        {
            pushNum(&num, tmp);
            length[lengthFlag]++;
        }
        else if(tmp == 10)
        {
            digitFlag = false;
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
                digit->positive = digitFlag;
            }
            else
            {
                digit->afterSize = length[1];
                digit->after = num;
                digit->positive = digitFlag;
            }
            length[0] = 0;
            length[1] = 0;
            lengthFlag = 0;
            digitFlag = true;
            pushOperand(&operand, digit);
            digit = initializeDigit();
        }
        else
        {
            pDigit secondDigit = popOperand(&operand);
            pDigit firstDigit = popOperand(&operand);
//            returnValue(copyDigit(firstDigit));
//            printf(" ");
//            returnValue(copyDigit(secondDigit));
//            printf("   %C\n", tmp);
            pDigit tmpDigit;
            switch (tmp)
            {
                case 42:
                    tmpDigit = multiply(firstDigit, secondDigit);
                    if((firstDigit->positive + secondDigit->positive) == 1)
                    {
                        tmpDigit->positive = false;
                    }
                    else
                    {
                        tmpDigit->positive = true;
                    }
                    pushOperand(&operand, tmpDigit);
                    break;

                case 43:
                    if((firstDigit->positive + secondDigit->positive) == 1)
                    {
                        if(firstDigit->positive)
                        {
                            tmpDigit = minus(firstDigit, secondDigit);
                        }
                        else
                        {
                            tmpDigit = minus(secondDigit, firstDigit);
                        }
                    }
                    else
                    {
                        tmpDigit = plus(firstDigit, secondDigit);
                    }
                    pushOperand(&operand, tmpDigit);
                    break;

                case 45:
//                    printf("%d", isBig(firstDigit, secondDigit));
                    if(!(secondDigit->positive))
                    {
                        secondDigit->positive = true;
                        if(firstDigit->positive)
                        {
                            tmpDigit = plus(firstDigit, secondDigit);
                        }
                        else
                        {
                            tmpDigit = minus(secondDigit, firstDigit);
                        }
                    }
                    else
                    {
                        if(firstDigit->positive)
                        {
                            tmpDigit = minus(firstDigit, secondDigit);
                        }
                        else
                        {
                            tmpDigit = plus(firstDigit, secondDigit);
                            tmpDigit->positive = false;
                        }
                    }
                    pushOperand(&operand, tmpDigit);
                    break;

                case 47:
                    pushOperand(&operand, divide(firstDigit, secondDigit));
                    break;

            }
        }
        seek = seek->next;
//        free(seek->prev);
    }
    return popOperand(&operand);
}

pDigit copyDigit(pDigit digit)
{
    pDigit result = initializeDigit();
    pNum tmpBefore = NULL;
    pNum tmpAfter = NULL;

    for(int i = 0; i < digit->beforeSize; i++)
    {
        pushNum(&tmpBefore, popNum(&(digit->before)));
    }
    for(int i = 0; i< digit->afterSize; i++)
    {
        pushNum(&tmpAfter, popNum(&(digit->after)));
    }

    for(int i = 0; i < digit->beforeSize; i++)
    {
        int tmp = popNum(&tmpBefore);
        pushNum(&(digit->before), tmp);
        pushNum(&(result->before), tmp);
    }

    for(int i = 0; i < digit->afterSize; i++)
    {
        int tmp = popNum(&tmpAfter);
        pushNum(&(digit->after), tmp);
        pushNum(&(result->after), tmp);
    }

    result->beforeSize = digit->beforeSize;
    result->afterSize = digit->afterSize;
    result->positive = digit->positive;
    return  result;
}



void makePostfix(char* str, pList pList, pOperator Operator)
{
    int i = 0;
    List list = *pList;
    pOperator topOperator = Operator;

    while(1)
    {
        int flag = 0;
        if(str[i] == '\0')
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
            if(emptyOperator(topOperator))
            {
                if(str[i] == 40)
                {
                    if((i != 0) && (48 <= str[i-1] && str[i-1] <= 57))
                    {
                        pushOperator(&topOperator, 42);
                    }
                }
                pushOperator(&topOperator, str[i]);
            }
            else
            {
                char tmp = popOperator(&topOperator);
                if(str[i] == 41) // )�� ���� ��, �켱 ���� 1��
                {
                    if(tmp != 40)
                    {
                        addExpression(&list, tmp);
                        while(popOperator(&topOperator) != 40)
                        {
                            addExpression(&list, popOperator(&topOperator));
                        }
                    }

                    if((48 <= str[i+1] && str[i+1] <= 57))
                    {
                        pushOperator(&topOperator, 42);
                    }
                }
                else if((str[i] == 42) || (str[i] == 47)) // * / ���� ��, �켱 ���� 2��
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
                else if((str[i] == 43) || (str[i] == 45)) // + - ���� ��, �켱 ���� 3��
                {
                    if((str[i-1] == 40) && (str[i] == 45))
                    {
                        addExpression(&list, 10);
                        pushOperator(&topOperator, tmp);
                    }
                    else
                    {
                        if(tmp == 40)
                        {
                            pushOperator(&topOperator, tmp);
                            pushOperator(&topOperator, str[i]);
                        }
                        else
                        {
//                            printf("%C", tmp);
                            addExpression(&list, tmp);
                            pushOperator(&topOperator, str[i]);
                        }
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
                                pushOperator(&topOperator, 42);
                                pushOperator(&topOperator, str[i]);
                            }
                            else
                            {
                                pushOperator(&topOperator, tmp);
                                pushOperator(&topOperator, 42);
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

bool isBig(pDigit first, pDigit second)
{
    bool flag = false;

    if(first->beforeSize < second->beforeSize)
    {
        flag = true;
    }
    else if(first->beforeSize == second-> beforeSize)
    {
        pNum firstTmp = NULL; pNum secondTmp = NULL;
        int firstNum, secondNum;
        if(first->afterSize > second->afterSize)
        {
            flag = false;
            for(int i = 0; i < (first->afterSize - second->afterSize); i++)
            {
                pushNum(&firstTmp, popNum(&(first->after)));
            }
        }
        else
        {
            flag = true;
            for(int i = 0; i < (second->afterSize - first->afterSize); i++)
            {
                pushNum(&second, popNum(&(second->after)));
            }
        }

        for(int i = 0; i < first->afterSize; i++)
        {
            firstNum = popNum(&(first->after));
            secondNum = popNum(&(second->after));
            if(firstNum < secondNum)
            {
                flag = true;
            }
            else if(firstNum > secondNum)
            {
                flag = false;
            }
            pushNum(&firstTmp, firstNum);
            pushNum(&secondTmp, secondNum);
        }

        if(first->afterSize > second->afterSize)
        {
            for(int i = 0; i < (first->afterSize - second->afterSize); i++)
            {
                pushNum(&firstTmp, popNum(&(first->after)));
            }
            for(int i = 0; i < second->afterSize; i++)
            {
                pushNum(&(first->after), popNum(&firstTmp));
                pushNum(&(second->after), popNum(&secondTmp));
            }
        }
        else
        {
            for(int i = 0; i < (second->afterSize - first->afterSize); i++)
            {
                pushNum(&second, popNum(&(second->after)));
            }
            for(int i = 0; i < first->afterSize; i++)
            {
                pushNum(&(first->after), popNum(&firstTmp));
                pushNum(&(second->after), popNum(&secondTmp));
            }
        }

        firstTmp = NULL; secondTmp = NULL;
        for(int i = 0; i < first->beforeSize; i++)
        {
            firstNum = popNum(&(first->before));
            secondNum = popNum(&(second->before));
            if(firstNum < secondNum)
            {
                flag = true;
            }
            else if(firstNum > secondNum)
            {
                flag = false;
            }
            pushNum(&firstTmp, firstNum);
            pushNum(&secondTmp, secondNum);
        }
        for(int i = 0; i < first->beforeSize; i++)
        {
            pushNum(&(first->before), popNum(&firstTmp));
            pushNum(&(second->before), popNum(&secondTmp));
        }
    }
    return flag;
}