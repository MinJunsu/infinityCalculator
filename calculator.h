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

pOperator getOperator(char op);
int pushOperator(pOperator* top, char op);
inline int emptyOperator(pOperator top);
char popOperator(pOperator* top);
void insertExpression(pExpression* head, int num);
void initList(pList list);
void addExpression(pList list, int num);
void viewAll(pList list);
void makePostfix(char* str, pList list, pOperator topOperator);