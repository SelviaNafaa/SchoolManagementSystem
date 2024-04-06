#include <stdio.h>
#include <stdlib.h>
#include "school.h"
#include "STD_Types.h"
#include "cmd_Handler.h"
#include "ShapeDraw.h"
#include <unistd.h>
#define max_students 1000
#define TEXT_Green	    10U
#define TEXT_Red	    4U
#define TEXT_LYellow	14U


static student_t school_arr[max_students];
static int real_index=0;
static int exit_key,sec_req,check,student_ID,third_req;
static student_t *PointToStruct;
static char student_name[maxName];

void menu(void)
{
    cmdSetConsoleColour(TEXT_LYellow);
    ShapeDraw_Square(40,15,40,15);
    cmdResetConsoleColour();
    cmdSetConsoleColour(TEXT_Red);
    cmdGoToXY(45,18);
    printf("Press (1) To Add New Student\n");
    cmdGoToXY(45,19);
    printf("Press (2) To Edit Student\n");
    cmdGoToXY(45,20);
    printf("Press (3) To Print Student\n");
    cmdGoToXY(45,21);
    printf("Press (4) To Call person\n");
    cmdGoToXY(45,22);
    printf("Press (5) To Sort school\n");
    cmdGoToXY(45,23);
    printf("Press (6) To Remove Student\n");
    cmdGoToXY(45,24);
    printf("Press (7) To Print The Entire school\n");
    cmdGoToXY(45,25);
    cmdResetConsoleColour();
}

void scanString(char*str,int maxSize)
{
    int i;
    fflush(stdin);
    scanf("%c",str);
    for(i=1; i<maxSize-1&&str[i-1]!='\n'; i++)
    {
        scanf("%c",str+i);

    }
    str[i-1]=0;
    str[i]=0;

}

void add_student(int *Arr_index)
{
    int real_index=*Arr_index;
    printf("Enter name:");
    fflush(stdin);
    scanString(school_arr[real_index].name,maxName);

    printf("Enter location:");
    fflush(stdin);
    scanString(school_arr[real_index].location,maxLocation);

    school_arr[real_index].ID=real_index;

    printf("Enter age:");
    scanf("%d",&(school_arr[real_index].age));


    fflush(stdin);
    printf("Enter grade:");
    scanf("%c",&(school_arr[real_index].grade));

    printf("Enter Phone number:");
    fflush(stdin);
    scanString(school_arr[real_index].phone,maxPhone);

     printf("Name of student mother:");
      fflush(stdin);
      scanString(school_arr[real_index].mother.name,maxName);

      printf("Name of student father:");
      fflush(stdin);
      scanString(school_arr[real_index].father.name,maxName);

      printf("Enter mother Phone number:");
      fflush(stdin);
      scanString(school_arr[real_index].mother.phone,maxPhone);

      printf("Enter father Phone number:");
      fflush(stdin);
      scanString(school_arr[real_index].father.phone,maxPhone);

      printf("Enter mother work:");
      fflush(stdin);
      scanString(school_arr[real_index].mother.work,maxWork);

      printf("Enter father work:");
      fflush(stdin);
      scanString(school_arr[real_index].father.work,maxWork);
      printf("Enter number of sibling:");
      scanf("%d",&school_arr[real_index].numberOfSiblings);
      int sibNum=school_arr[real_index].numberOfSiblings;
      int i;
      school_arr[real_index].siblings=malloc(sizeof(siblings_t)*(sibNum));
      for(i=0;i<sibNum;i++)
      {

      printf("Enter %d sibling Name:",i+1);
      fflush(stdin);
      scanString(school_arr[real_index].siblings[i].name,maxName);
      printf("Enter %d sibling age:",i+1);
      scanf("%d",&(school_arr[real_index].siblings[i].age));

      }


    (*Arr_index)++;
}

void printStr(char*str)
{
    int i;

    for(i=0; str[i]; i++)
    {

        printf("%c",str[i]);
    }


}
void print_student(student_t *PointToStruct)
{
    cmdGoToXY(50,1);
    printf("ID                 :%d\n\n",PointToStruct->ID);
    cmdGoToXY(50,2);
    printf("Name               : %s\n",PointToStruct->name);
    cmdGoToXY(50,3);
    printf("Location           : %s\n",PointToStruct->location);
    cmdGoToXY(50,4);
    printf("Age                : %d\n\n",PointToStruct->age);
    cmdGoToXY(50,5);
    printf("Grade              : %c\n",PointToStruct->grade);
    cmdGoToXY(50,6);
    printf("Phone              : %s\n",PointToStruct->phone);
    cmdGoToXY(50,7);
    printf("Mother Name        : %s\n",PointToStruct->mother.name);
    cmdGoToXY(50,8);
    printf("Mother Phone Number: %s\n",PointToStruct->mother.phone);
    cmdGoToXY(50,9);
    printf("Mother Work        : %s\n",PointToStruct->mother.work);
    cmdGoToXY(50,10);
    printf("father Name        : %s\n",PointToStruct->father.name);
    cmdGoToXY(50,11);
    printf("father Phone Number: %s\n",PointToStruct->father.phone);
    cmdGoToXY(50,12);
    printf("father Work        : %s\n",PointToStruct->father.work);

    int sib_num=PointToStruct->numberOfSiblings;
    int i,k=13;
    for(i=0; i<sib_num; i++)
    {
        cmdGoToXY(50,k++);
        printf("Sibling %d Name    : %s\n",i+1,PointToStruct->siblings->name);
        cmdGoToXY(50,k++);
        printf("Sibling %d Age     : %d\n",i+1,PointToStruct->siblings->age);
    }


}

void swapStuct(student_t *str1,student_t *str2)
{
    student_t temp;

    temp=*str1;
    *str1=*str2;
    *str2=temp;
}
int comp2Strings(char *str1,char*str2)
{
    int i;
    char c1,c2;
    for(i=0; str1[i]||str2[i]; i++)
    {
        c1=str1[i];
        c2=str2[i];
        if(c1>='A'&&c1<='Z')
        {
            c1=c1-'A'+'a';
        }
        if(c2>='A'&&c2<='Z')
        {
            c2=c2-'A'+'a';
        }
        if(c1>c2)
        {
            return 1;
        }
        else if(c2>c1)
        {
            return -1;
        }
    }
    return 0;
}
void sortByName(void)
{
    int i,j,temp;

    for(i=0; i<real_index; i++)
    {

        for(j=0; j<real_index-1-i; j++)
        {
            if(comp2Strings(school_arr[j].name,school_arr[j+1].name)==1)
            {
                swapStuct(school_arr+j,school_arr+j+1);
                temp=school_arr[j].ID;
                school_arr[j].ID=school_arr[j+1].ID;
                school_arr[j+1].ID=temp;
            }
        }
    }


}
void sortByAge(void)
{
    int i,j,temp;

    for(i=0; i<real_index; i++)
    {

        for(j=0; j<real_index-1-i; j++)
        {
            if(school_arr[j].age>school_arr[j+1].age)
            {
                swapStuct(school_arr+j,school_arr+j+1);
                temp=school_arr[j].ID;
                school_arr[j].ID=school_arr[j+1].ID;
                school_arr[j+1].ID=temp;
            }
        }
    }
}


void sortByGrade(void)
{
    int i,j,temp;
    char c1,c2;

    for(i=0; i<real_index; i++)
    {

        for(j=0; j<real_index-1-i; j++)
        {
            c1=school_arr[j].grade;
            c2=school_arr[j+1].grade;
            if(c1>='A'&&c1<='Z')
            {
                c1=c1-'A'+'a';
            }
            if(c2>='A'&&c2<='Z')
            {
                c2=c2-'A'+'a';
            }
            if(c1>c2)
            {
                swapStuct(school_arr+j,school_arr+j+1);
                temp=school_arr[j].ID;
                school_arr[j].ID=school_arr[j+1].ID;
                school_arr[j+1].ID=temp;
            }
        }
    }
}


int editByID(int id)
{
    if(id>=0&&id<real_index)
    {

        cmdClearScreen();
        cmdSetConsoleColour(TEXT_LYellow);
        ShapeDraw_Square(0,0,18,2);
        cmdResetConsoleColour();

        cmdSetConsoleColour(TEXT_Red);
        cmdGoToXY(1,1);
        printf("Edit Student By ID\n\n");
        cmdResetConsoleColour();
        cmdSetConsoleColour(TEXT_Green);
        cmdGoToXY(30,0);
        printf("Student %d ",id);
        cmdGoToXY(30,1);
        printf("Old Informations:");
        cmdResetConsoleColour();
        print_student(school_arr+id);
        cmdGoToXY(0,3);
        printf("Enter new information:\n");
        add_student(&id);
        cmdSetConsoleColour(TEXT_Green);
        cmdGoToXY(30,0);
        printf("Student with Id %d ",id-1);
        cmdGoToXY(30,1);
        printf("New Informations:");
        cmdResetConsoleColour();
        print_student(school_arr+id-1);
        return 1;
    }

    return 0;


}
int editByName(char*str)
{
    int i;
    for(i=0; i<real_index; i++)
    {

        if(comp2Strings(school_arr[i].name,str)==0)
        {

            cmdClearScreen();
            cmdSetConsoleColour(TEXT_LYellow);
            ShapeDraw_Square(0,0,20,2);
            cmdResetConsoleColour();

            cmdSetConsoleColour(TEXT_Red);
            cmdGoToXY(1,1);
            printf("Edit Student By Name\n\n");
            cmdResetConsoleColour();
            cmdSetConsoleColour(TEXT_Green);
            cmdGoToXY(30,0);
            printf("Student %s ",str);
            cmdGoToXY(30,1);
            printf("Old Informations:");
            cmdResetConsoleColour();
            print_student(school_arr+i);
            cmdGoToXY(0,3);
            printf("Enter new Informations:\n");
            add_student(&i);
            cmdSetConsoleColour(TEXT_Green);
            cmdGoToXY(30,0);
            printf("Student %s ",str);
            cmdGoToXY(30,1);
            printf("New Informations:");
            cmdResetConsoleColour();
            print_student(school_arr+i-1);
            return 1;
        }

    }
    return 0;
}
int removeStudentByID(int id)
{
    int i;
    if(id>=0&&id<real_index)
    {
        for(i=id; i<real_index; i++)
        {
            school_arr[i]=school_arr[i+1];
            (school_arr[i].ID)--;
        }
        real_index--;
        return 1;

    }
    return 0;

}
int removeStudentByName(char*str)
{
    int i;
    for(i=0; i<real_index; i++)
    {
        if(comp2Strings(school_arr[i].name,str)==0)
        {

            return removeStudentByID(school_arr[i].ID);
        }
    }
    return 0;
}
void delay(int num)
{
    volatile int i=0;
    while(i<num)
    {
        i++;
    }
}
void makingCall(char*str)
{
    volatile int j=0;
    cmdGoToXY(20,10);
    printf("Calling %s",str);
 while(j<5)
 {

     printf(".");
     sleep(1);
     printf(".");
     sleep(1);
     printf(".");
     sleep(1);

     printf("\b\b\b   ");
     sleep(1);
   printf("\b\b\b");

     j++;
 }
  cmdClearScreen();
  printf("\n\n");
  cmdGoToXY(5,4);
  cmdSetConsoleColour(TEXT_Green);
  printf("No Respond\n\n");
  cmdResetConsoleColour();





}
int callPersonByPhoneNum(char *str,int who)
{
    int i;
    if(who==1)
    {
        for(i=0; i<real_index; i++)
        {
            if(comp2Strings(school_arr[i].phone,str)==0)
            {

                makingCall(str);


            }


            return 1;
        }

        return 0;

    }
    else if(who==2)
    {
        for(i=0; i<real_index; i++)
        {
            if(comp2Strings(school_arr[i].mother.phone,str)==0)
            {
                makingCall(str);
                return 1;
            }
        }
        return 0;

    }
    else if(who==3)
    {
        for(i=0; i<real_index; i++)
        {
            if(comp2Strings(school_arr[i].father.phone,str)==0)
            {
                makingCall(str);

                return 1;
            }
        }
        return 0;

    }
    else
    {
        return 0;
    }



}
int callPersonByName(char *str,int who)
{
    int i;
    if(who==1)
    {
        for(i=0; i<real_index; i++)
        {
            if(comp2Strings(school_arr[i].name,str)==0)
            {

                makingCall(str);



                return 1;
            }

        }

        return 0;

    }
    else if(who==2)
    {
        for(i=0; i<real_index; i++)
        {
            if(comp2Strings(school_arr[i].mother.name,str)==0)
            {
                makingCall(str);

                return 1;
            }
        }
        return 0;

    }
    else if(who==3)
    {
        for(i=0; i<real_index; i++)
        {
            if(comp2Strings(school_arr[i].father.name,str)==0)
            {
                makingCall(str);

                return 1;
            }
        }
        return 0;

    }
    else
    {
        return 0;
    }



}
void printALLTogether(student_t *PointToStruct)
{



    int i;
    for(i=0; i<real_index; i++)
    {
        printf("+-------------------------+-------------------------+\n");
        printf("| student  %d              | Values                  |\n",PointToStruct[i].ID+1);
        printf("+-------------------------+-------------------------+\n");
        printf("| ID                      | %-24d|\n", PointToStruct[i].ID);
        printf("| Name                    | %-24s|\n", PointToStruct[i].name);
        printf("| Location                | %-24s|\n", PointToStruct[i].location);
        printf("| Age                     | %-24d|\n", PointToStruct[i].age);
        printf("| Grade                   | %-24c|\n", PointToStruct[i].grade);
        printf("| Phone                   | %-24s|\n", PointToStruct[i].phone);
        printf("| Mother Name             | %-24s|\n", PointToStruct[i].mother.name);
        printf("| Mother Phone Number     | %-24s|\n", PointToStruct[i].mother.phone);
        printf("| Mother Work             | %-24s|\n", PointToStruct[i].mother.work);
        printf("| Father Name             | %-24s|\n", PointToStruct[i].father.name);
        printf("| Father Phone Number     | %-24s|\n", PointToStruct[i].father.phone);
        printf("| Father Work             | %-24s|\n", PointToStruct[i].father.work);

        int sib_num = PointToStruct[i].numberOfSiblings;
        int j;
        for (j = 0; j < sib_num; j++)
        {
            printf("| Sibling %d Name         | %-24s|\n", i+1, PointToStruct[i].siblings[j].name);
            printf("| Sibling %d Age          | %-24d|\n", i+1, PointToStruct[i].siblings[j].age);
        }
    }
    printf("+-------------------------+-------------------------+\n\n\n");


}


void Request1_Handling(void)
{
    cmdClearScreen();
    cmdSetConsoleColour(TEXT_LYellow);
    ShapeDraw_Square(0,0,18,2);
    cmdResetConsoleColour();

    cmdSetConsoleColour(TEXT_Red);
    cmdGoToXY(1,1);
    printf("Adding New Student\n\n");
    cmdResetConsoleColour();


    add_student(&real_index);
    PointToStruct=school_arr+real_index-1;
    cmdClearScreen();

    cmdSetConsoleColour(TEXT_LYellow);
    ShapeDraw_Square(0,0,45,2);
    cmdResetConsoleColour();

    cmdSetConsoleColour(TEXT_Red);
    cmdGoToXY(1,1);
    printf("Student Added With The Flowing Information:\n\n");
    cmdResetConsoleColour();
    cmdGoToXY(50,0);
    print_student(PointToStruct);

    cmdSetConsoleColour(TEXT_Red);
    printf("\nEnter Any Key To Exit");
    cmdResetConsoleColour();

    fflush(stdin);
    scanf("%d",&exit_key);
    cmdClearScreen();
}
void Request2_Handling(void)
{
    cmdClearScreen();
    cmdSetConsoleColour(TEXT_LYellow);
    ShapeDraw_Square(0,0,35,4);
    cmdResetConsoleColour();

    cmdGoToXY(1,1);
    cmdSetConsoleColour(TEXT_Red);
    printf("Press (1) To Edit Student By Name");
    cmdGoToXY(1,2);
    printf("Press (2) To Edit Student By ID");
    cmdGoToXY(1,3);
    cmdResetConsoleColour();
    scanf("%d",&sec_req);
    if(sec_req==1)
    {
        cmdClearScreen();
        cmdSetConsoleColour(TEXT_LYellow);
        ShapeDraw_Square(0,0,20,2);
        cmdResetConsoleColour();

        cmdSetConsoleColour(TEXT_Red);
        cmdGoToXY(1,1);
        printf("Edit Student By Name\n\n");
        cmdResetConsoleColour();

        printf("Enter Student Name:");
        scanString(student_name,maxName);
        check=editByName(student_name);
        if(check==0)
        {
            cmdSetConsoleColour(TEXT_Green);
            printf("Wrong Name {%s} Student Not Exist",student_name);
            cmdResetConsoleColour();
        }
        else if(check==1)
        {
            cmdSetConsoleColour(TEXT_Green);
            printf("Student Information Edited successfully");
            cmdResetConsoleColour();

        }



    }
    else if(sec_req==2)
    {
        cmdClearScreen();
        cmdSetConsoleColour(TEXT_LYellow);
        ShapeDraw_Square(0,0,18,2);
        cmdResetConsoleColour();

        cmdSetConsoleColour(TEXT_Red);
        cmdGoToXY(1,1);
        printf("Edit Student By ID\n\n");
        cmdResetConsoleColour();

        printf("Enter Student ID:");
        scanf("%d",&student_ID);
        check=editByID(student_ID);
        if(check==0)
        {
            cmdSetConsoleColour(TEXT_Green);
            printf("Wrong ID {%d} Student Not Exist",student_ID);
            cmdResetConsoleColour();
        }
        else if(check==1)
        {
            cmdSetConsoleColour(TEXT_Green);
            printf("Student Information Edited successfully");
            cmdResetConsoleColour();


        }

    }
    else
    {
         cmdGoToXY(1,5);
        printf("InValid Input");
    }

    cmdSetConsoleColour(TEXT_Red);
    printf("\nEnter Any Key To Exit");
    cmdResetConsoleColour();

    fflush(stdin);
    scanf("%d",&exit_key);
    cmdClearScreen();

}
void Request3_Handling(void)
{
    cmdClearScreen();
    cmdSetConsoleColour(TEXT_LYellow);
    ShapeDraw_Square(0,0,35,4);
    cmdResetConsoleColour();

    cmdGoToXY(1,1);
    cmdSetConsoleColour(TEXT_Red);
    printf("Press (1) To Enter Student Name");
    cmdGoToXY(1,2);
    printf("Press (2) To Enter Student ID");
    cmdGoToXY(1,3);
    cmdResetConsoleColour();
    scanf("%d",&sec_req);
    if(sec_req==1)
    {
        cmdClearScreen();
        printf("\n\nEnter Student Name:");
        scanString(student_name,maxName);
        int i,flag=1;
        for(i=0; i<real_index; i++)
        {
            if(comp2Strings(school_arr[i].name,student_name)==0)
            {
                flag=0;
                cmdClearScreen();
                cmdSetConsoleColour(TEXT_LYellow);
                ShapeDraw_Square(0,0,35,3);
                cmdResetConsoleColour();

                cmdGoToXY(1,1);
                cmdSetConsoleColour(TEXT_Red);
                printf("Student {%s} Informations ",student_name);
                cmdResetConsoleColour();
                print_student(school_arr+i);
                break;

            }
        }

        if(flag)
        {
            cmdSetConsoleColour(TEXT_Green);
            printf("Wrong Name {%s} Student Not Exist",student_name);
            cmdResetConsoleColour();

        }


    }
    else if(sec_req==2)
    {
        cmdClearScreen();
        printf("\n\nEnter Student ID:");
        scanf("%d",&student_ID);

        if(student_ID>=0&&student_ID<real_index)
        {

            cmdClearScreen();
            cmdSetConsoleColour(TEXT_LYellow);
            ShapeDraw_Square(0,0,35,3);
            cmdResetConsoleColour();

            cmdGoToXY(1,1);
            cmdSetConsoleColour(TEXT_Red);
            printf("Student with ID {%d} Informations ",student_ID);
            cmdResetConsoleColour();
            print_student(school_arr+student_ID);


        }

        else
        {
            cmdSetConsoleColour(TEXT_Green);
            printf("Wrong ID {%d} Student Not Exist",student_ID);
            cmdResetConsoleColour();

        }


    }
    else
    {
        cmdGoToXY(1,5);
        printf("InValid Input");
    }

    cmdSetConsoleColour(TEXT_Red);
    printf("\nEnter Any Key To Exit");
    cmdResetConsoleColour();

    fflush(stdin);
    scanf("%d",&exit_key);
    cmdClearScreen();

}
void Request4_Handling(void)
{
    cmdClearScreen();
    cmdSetConsoleColour(TEXT_LYellow);
    ShapeDraw_Square(0,0,35,5);
    cmdResetConsoleColour();
    cmdGoToXY(1,1);
    cmdSetConsoleColour(TEXT_Red);
    printf("Press (1) To call Student");
    cmdGoToXY(1,2);
    printf("Press (2) To Call Student's mother");
    cmdGoToXY(1,3);
    printf("Press (3) To Call Student's father\n");
    cmdResetConsoleColour();
    cmdGoToXY(1,4);
    scanf("%d",&sec_req);
    if(sec_req<=0||sec_req>=4)
    {
        printf("\nInValid Input");
        cmdSetConsoleColour(TEXT_Red);
        printf("\nEnter Any Key To Exit");
        cmdResetConsoleColour();

        fflush(stdin);
        scanf("%d",&exit_key);
        cmdClearScreen();
    }
    else
    {


    cmdClearScreen();
    cmdSetConsoleColour(TEXT_LYellow);
    ShapeDraw_Square(0,0,35,4);
    cmdResetConsoleColour();
    cmdGoToXY(1,1);
    cmdSetConsoleColour(TEXT_Red);
    printf("Press (1) To Enter Name");
    cmdGoToXY(1,2);
    printf("Press (2) To Enter Phone Number");
    cmdResetConsoleColour();
    cmdGoToXY(1,3);
    scanf("%d",&third_req);
    if(third_req==1)
    {

        cmdClearScreen();
        cmdSetConsoleColour(TEXT_LYellow);
        ShapeDraw_Square(0,0,25,2);
        cmdResetConsoleColour();
        cmdGoToXY(1,1);
        cmdSetConsoleColour(TEXT_Red);
        printf("You Are Making Phone Call");
        cmdResetConsoleColour();
        cmdGoToXY(1,4);
        printf("Enter Name:");
        scanString(student_name,maxName);
        check=callPersonByName(student_name,sec_req);
        if(check==0)
        {
            cmdSetConsoleColour(TEXT_Green);
            printf("Wrong Name {%s} Student Not Exist",student_name);
            cmdResetConsoleColour();
        }


    }
    else if(third_req==2)
    {

        cmdClearScreen();
        cmdSetConsoleColour(TEXT_LYellow);
        ShapeDraw_Square(0,0,25,2);
        cmdResetConsoleColour();
        cmdGoToXY(1,1);
        cmdSetConsoleColour(TEXT_Red);
        printf("You Are Making Phone Call");
        cmdResetConsoleColour();
        cmdGoToXY(1,4);
        char Phone[11];
        printf("Enter Phone Number:");
        scanString(Phone,maxPhone);
        check=callPersonByPhoneNum(Phone,sec_req);
        if(check==0)
        {
            cmdSetConsoleColour(TEXT_Green);
            printf("Note: {%s} Number Not Exist In Your DataBase\n",Phone);
            cmdResetConsoleColour();
            makingCall(Phone);
        }

    }
    else
    {
        cmdGoToXY(1,5);
        printf("InValid Input");
    }

    cmdSetConsoleColour(TEXT_Red);
    printf("\nEnter Any Key To Exit");
    cmdResetConsoleColour();

    fflush(stdin);
    scanf("%d",&exit_key);
    cmdClearScreen();
    }

}
void Request5_Handling(void)
{
    cmdClearScreen();
    cmdSetConsoleColour(TEXT_LYellow);
    ShapeDraw_Square(0,0,28,5);
    cmdResetConsoleColour();
    cmdGoToXY(1,1);
    cmdSetConsoleColour(TEXT_Red);
    printf("Press (1) To Sort By Name\n");
    cmdGoToXY(1,2);
    printf("Press (2) To Sort By Age\n");
    cmdGoToXY(1,3);
    printf("Press (3) To Sort By Grade\n");
    cmdResetConsoleColour();
    cmdGoToXY(1,4);
    scanf("%d",&sec_req);
    if(sec_req==1)
    {
        sortByName();
        cmdGoToXY(10,7);
        cmdSetConsoleColour(TEXT_Green);
        printf("School Sorted By Name Print The Hall school To see Informations After Sorting");
        cmdResetConsoleColour();


    }
    else if(sec_req==2)
    {
        sortByAge();
        cmdGoToXY(10,7);
        cmdSetConsoleColour(TEXT_Green);
        printf("School Sorted By Age Print The Hall school To see Informations After Sorting");
        cmdResetConsoleColour();

    }
    else if(sec_req==3)
    {
        sortByGrade();
        cmdGoToXY(10,7);
        cmdSetConsoleColour(TEXT_Green);
        printf("School Sorted By Grade Print The Hall school To see Informations After Sorting");
        cmdResetConsoleColour();

    }
    else
    {
         cmdGoToXY(1,6);
        printf("InValid Input");
    }

    cmdSetConsoleColour(TEXT_Red);
    printf("\n\nEnter Any Key To Exit");
    cmdResetConsoleColour();

    fflush(stdin);
    scanf("%d",&exit_key);
    cmdClearScreen();

}
void Request6_Handling(void)
{
    cmdClearScreen();
    cmdSetConsoleColour(TEXT_LYellow);
    ShapeDraw_Square(0,0,32,4);
    cmdResetConsoleColour();
    cmdGoToXY(1,1);
    cmdSetConsoleColour(TEXT_Red);
    printf("Press (1) To Enter Name");
    cmdGoToXY(1,2);
    printf("Press (2) To Enter ID");
    cmdResetConsoleColour();
    cmdGoToXY(1,3);
    scanf("%d",&sec_req);
   if(sec_req==1)
    {

        cmdClearScreen();
        cmdSetConsoleColour(TEXT_LYellow);
        ShapeDraw_Square(0,0,37,3);
        cmdResetConsoleColour();
        cmdGoToXY(1,1);
        cmdSetConsoleColour(TEXT_Red);
        printf("You Are Deleting Student Informations");
        cmdResetConsoleColour();
        cmdGoToXY(1,5);
        printf("Enter Name:");
        scanString(student_name,maxName);
        check=removeStudentByName(student_name);
        if(check==1)
        {
        cmdGoToXY(10,7);
        cmdSetConsoleColour(TEXT_Green);
        printf("Student {%s} Informations deleted Successfully",student_name);
        cmdResetConsoleColour();

        }
        else
        {
        cmdGoToXY(10,7);
        cmdSetConsoleColour(TEXT_Green);
        printf("Wrong Name {%s} Student Not Exist",student_name);
        cmdResetConsoleColour();

        }


    }
    else if(sec_req==2)
    {

        cmdClearScreen();
        cmdSetConsoleColour(TEXT_LYellow);
        ShapeDraw_Square(0,0,37,3);
        cmdResetConsoleColour();
        cmdGoToXY(1,1);
        cmdSetConsoleColour(TEXT_Red);
        printf("You Are Deleting Student Informations");
        cmdResetConsoleColour();
        cmdGoToXY(1,5);
        printf("Enter ID:");
        scanf("%d",&student_ID);
        check=removeStudentByID(student_ID);
        if(check==1)
        {
        cmdGoToXY(10,7);
        cmdSetConsoleColour(TEXT_Green);
        printf("Student with ID {%d} Informations deleted Successfully",student_ID);
        cmdResetConsoleColour();

        }
        else
        {
        cmdGoToXY(10,7);
        cmdSetConsoleColour(TEXT_Green);
        printf("Wrong ID {%d} Student Not Exist",student_ID);
        cmdResetConsoleColour();

        }
    }
    else
    {
        cmdGoToXY(1,6);
        printf("InValid Input");
    }

    cmdSetConsoleColour(TEXT_Red);
    printf("\n\nEnter Any Key To Exit");
    cmdResetConsoleColour();

    fflush(stdin);
    scanf("%d",&exit_key);
    cmdClearScreen();


}
void Request7_Handling(void)

{
    cmdClearScreen();
    cmdSetConsoleColour(TEXT_LYellow);
    ShapeDraw_Square(0,0,25,2);
    cmdResetConsoleColour();
    cmdGoToXY(1,1);
    cmdSetConsoleColour(TEXT_Red);
    printf("Print The Entire School");
    cmdResetConsoleColour();

    if (real_index>0)
    {
        cmdGoToXY(0,4);
        printALLTogether(school_arr);
    }
    else
    {
       cmdGoToXY(5,4);
        cmdSetConsoleColour(TEXT_Green);
        printf("School Has No Students To Print\n\n");
        cmdResetConsoleColour();

    }
    cmdSetConsoleColour(TEXT_Red);
    printf("\nEnter Any Key To Exit");
    cmdResetConsoleColour();

    fflush(stdin);
    scanf("%d",&exit_key);
    cmdClearScreen();

}



