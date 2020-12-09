typedef struct operand
{
    int num;
    struct operand* next;
} Operand, *pOperand;

typedef struct operator
{
    char operator;
    struct operator* next;
} Operator, *pOperator;
