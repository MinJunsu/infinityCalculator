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

pDigit makeExpression(pList list)
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
    return popOperand(&operand);
}

pNum beforeCal(pNum max, pNum min, int max_before, int min_before, bool carry, bool* result)
{
    pNum before = NULL;
//    while (max_before != 0 && min_before == 0)
//    {
//        int new = popNum(&max);
//        if (carry)
//        {
//            new++;
//            carry = false;
//        }
//        if ((new / 10) >= 1)
//        {
//            carry = true;
//            new = new - 10;
//        }
//        pushNum(&before, new);
//        max_before--;
//    }
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

    // first와 second의 size를 int형으로 저장한다.
    int firstBeforesize = first->beforeSize;
    int secondBeforesize = second->beforeSize;
    int firstAftersize = first->afterSize;
    int secondAftersize = second->afterSize;

    bool carry = false;
    int resultFlag = 0;

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
pDigit multiply(pDigit first, pDigit second)
{
    pDigit result = initializeDigit();

    return result;
}

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
        printf("123");

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