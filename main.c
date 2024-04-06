#include <stdio.h>
#include <stdlib.h>
#include "school.h"
#include "STD_Types.h"
#include "cmd_Handler.h"
#include "ShapeDraw.h"
#define max_students 1000




int main()
{
    int request;

    while(1)
    {


        menu();
        fflush(stdin);
        scanf("%d",&request);
        if(request==1)
        {
            Request1_Handling();

        }
        else if(request==2)
        {

            Request2_Handling();
        }
        else if(request==3)
        {
            Request3_Handling();
        }
        else if (request==4)
        {
            Request4_Handling();


        }
        else if(request==5)
        {
            Request5_Handling();
        }
        else if(request==6)
        {
            Request6_Handling();
        }
        else if(request==7)
        {
            Request7_Handling();
        }

        else
        {
            cmdGoToXY(45,26);
            printf("InValid Input");
        }
    }
    return 0;

}
