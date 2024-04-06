#define maxName 22
#define maxLocation 20
#define maxPhone 11
#define maxWork 15
typedef struct
{
    char name[maxName];
    char phone[maxPhone];
    char work[maxWork];



}parant_t;
typedef struct
{
    char name[maxName];
    int age;

}siblings_t;
typedef struct
{
    int ID;
    char name[maxName];
    char location[maxLocation];
    int age;
    char grade;
    char phone[maxPhone];
    parant_t mother;
    parant_t father;
    int numberOfSiblings;
    siblings_t *siblings;

}student_t;


void menu(void);
void add_student(int *real_index);
void print_student(student_t * PointToStruct);
void scanString(char*str,int maxSize);
void printStr(char*str);
void printALLTogether(void);
void swapStuct(student_t *str1,student_t *str2);
int comp2Strings(char *str1,char*str2);
void sortByName(void);
void sortByAge(void);
void sortByGrade(void);
int editByID(int id);
int editByName(char*str);
int removeStudentByID(int id);
int removeStudentByName(char*str);
int callPersonByName(char *str,int who);
int callPersonByPhoneNum(char *str,int who);
void makingCall(char*str);
void Request1_Handling(void);
void Request2_Handling(void);
void Request3_Handling(void);
void Request4_Handling(void);
void Request5_Handling(void);
void Request6_Handling(void);
void Request7_Handling(void);

