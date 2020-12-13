#define bool   _Bool
#define false  0
#define true   1

typedef struct expression
{
    int num;
    struct expression* prev;
    struct expression* next;
} Expression, *pExpression;

typedef struct list
{
    pExpression head;
    pExpression tail;
} List, *pList;

typedef struct operator
{
    char operator;
    struct operator* next;
} Operator, *pOperator;

typedef struct num
{
    int num;
    struct num* next;
} Num, *pNum;

typedef struct digit
{
    int beforeSize;
    int afterSize;
    struct num* before;
    struct num* after;
} Digit, *pDigit;

typedef struct operand
{
    struct digit* digit;
    struct operand* next;
} Operand, *pOperand;



pNum getNum(int num);
int pushNum(pNum* top, int op);
inline int emptyNum(pNum top);
int popNum(pNum* top);
pOperand getOperand(pDigit digit);
int pushOperand(pOperand* top, pDigit digit);
inline int emptyOperand(pOperand top);
pDigit popOperand(pOperand* top);
pOperator getOperator(char op);
int pushOperator(pOperator* top, char op);
inline int emptyOperator(pOperator top);
char popOperator(pOperator* top);
void insertExpression(pExpression* head, int num);
void initList(pList list);
void addExpression(pList list, int num);
void viewAll(pList list);
void makePostfix(char* str, pList list, pOperator topOperator);
pDigit makeExpression(pList list);
pDigit multiply(pDigit first, pDigit second);
pDigit plus(pDigit first, pDigit second);
pDigit minus(pDigit first, pDigit second);
pDigit divide(pDigit first, pDigit second);