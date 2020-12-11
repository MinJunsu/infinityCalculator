#include <stdio.h>
#include "calculator.h"

int main()
{
    List list;
    initList(&list);
    char* str = "233423541354.143543524352+2342314123413.34523453-321341241.12341234*3423121212.234523232323324324325423*(73729494719444.4239508234+41341312415454524.123787970473713980712477421675184631)";

//    char* str = "3.14(4-2)*5-((42-5)*2)";
    makePostfix(str, &list, NULL);
    makeExpression(&list);

    viewAll(&list);
}
