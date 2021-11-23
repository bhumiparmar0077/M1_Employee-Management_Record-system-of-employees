#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//Used macro
#define maximum_year  9999
#define minumum_year  1900
#define maximumUname 30
#define maximumPassword  20
#define filename  "EmployeeRecordSystem.bin"
// Macro related to the Employees info
#define fname 50
#define empname 50
#define empaddress 300
#define fileheadersize  sizeof(sFileHeader)
//structure to store date
typedef struct
{
    int yyyy;
    int mm;
    int dd;
} Date;
typedef struct
{
    char uname[maximumUname];
    char pass[maximumPassword];
} sFileHeader;
//Elements of structure
typedef struct// to call in program
{
    char tatay[fname];// declare the character data type
    char ngalan_sang_empleyado[empname];// declare the character data type
    char address_sang_empleyado[empaddress];// declare the character data type
    Date petsa_nga_ngsulod_ang_empleyado;// declare the integer data type
    unsigned int empleyado_id; // declare the integer data type
    float empleyado_sweldo;
} s_EmployeesInfo;
//Align the message
void printMessageCenter(const char* message)
{
    int length =0;
    int position = 0;
    //calculate how many space need to print
    length = (78 - strlen(message))/2;
    printf("\t\t\t");
    for(position =0 ; position < length ; position++)
    {
        //print space
        printf(" ");
    }
    //print message
    printf("%s",message);
}
//Head message
void headMessage(const char *message)
{
   
}
//Display message
void welcomeMessage()
{
    headMessage("www.itsourcecode.com");
    printf("\n\n\n\n\n");
    printf("\n\t\t\t  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    printf("\n\t\t\t  +      ++++++++++++++++++++++++++++++++++++++++++++++++      +");
    printf("\n\t\t\t  +      +                                              +      +");
    printf("\n\t\t\t  +      +                                              +      +");
    printf("\n\t\t\t  +      + WELCOME TO EMPLOYEE RECORD MANAGEMENT SYSTEM +      +");
    printf("\n\t\t\t  +      +                                              +      +");
    printf("\n\t\t\t  +      +                                              +      +");
    printf("\n\t\t\t  +      ++++++++++++++++++++++++++++++++++++++++++++++++      +");
    printf("\n\t\t\t  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("\n\n\n\t\t\t Enter any key to continue.....");
    getch();
}
//Validate name
int isNameValid(const char *name)
{
    int validName = 1;
    int length = 0;
    int index = 0;
    length = strlen(name);
    for(index =0; index <length ; ++index)
    {
        if(!(isalpha(name[index])) && (name[index] != '\n') && (name[index] != ' '))
        {
            validName = 0;
            break;
        }
    }
    return validName;
}
// Function to check leap year.
//Function returns 1 if leap year
int  IsLeapYear(int year)
{
    return (((year % 4 == 0) &&
             (year % 100 != 0)) ||
            (year % 400 == 0));
}
// returns 1 if given date is valid.
int isValidDate(Date *validDate)
{
    //check range of year,month and day
    if (validDate->yyyy > maximum_year ||
            validDate->yyyy < minumum_year)
        return 0;
    if (validDate->mm < 1 || validDate->mm > 12)
        return 0;
    if (validDate->dd < 1 || validDate->dd > 31)
        return 0;
    //Handle feb days in leap year
    if (validDate->mm == 2)
    {
        if (IsLeapYear(validDate->yyyy))
            return (validDate->dd <= 29);
        else
            return (validDate->dd <= 28);
    }
    //handle months which has only 30 days
    if (validDate->mm == 4 || validDate->mm == 6 ||
            validDate->mm == 9 || validDate->mm == 11)
        return (validDate->dd <= 30);
    return 1;
}
// Add employee in list
void addEmployeeInDataBase()
{
    s_EmployeesInfo addEmployeeInfoInDataBase = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(filename,"ab+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    headMessage("ADD NEW EMPLOYEES");
    printf("\n\n\t\t\tENTER YOUR DETAILS BELOW:");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printf("\n\t\t\tEmployee ID  = ");
    fflush(stdin);
    scanf("%u",&addEmployeeInfoInDataBase.empleyado_id);
    do
    {
        printf("\n\t\t\tFather Name  = ");
        fflush(stdin);
        fgets(addEmployeeInfoInDataBase.tatay,fname,stdin);
        status = isNameValid(addEmployeeInfoInDataBase.tatay);
        if (!status)
        {
            printf("\n\t\t\tName contain invalid character. Please enter again.");
        }
    }
    while(!status);
    do
    {
        printf("\n\t\t\tEmployee Name  = ");
        fflush(stdin);
        fgets(addEmployeeInfoInDataBase.ngalan_sang_empleyado,empname,stdin);
        status = isNameValid(addEmployeeInfoInDataBase.ngalan_sang_empleyado);
        if (!status)
        {
            printf("\n\t\t\tName contain invalid character. Please enter again.");
        }
    }
    while(!status);
    do
    {
        printf("\n\t\t\tEmployee Address  = ");
        fflush(stdin);
        fgets(addEmployeeInfoInDataBase.address_sang_empleyado,fname,stdin);
        status = isNameValid(addEmployeeInfoInDataBase.address_sang_empleyado);
        if (!status)
        {
            printf("\n\t\t\tName contain invalid character. Please enter again.");
        }
    }
    while(!status);
    printf("\n\t\t\tEmployee Salary  = ");
    fflush(stdin);
    scanf("%f",&addEmployeeInfoInDataBase.empleyado_sweldo);
    do
    {
        //get date year,month and day from user
        printf("\n\t\t\tEnter date in format (day/month/year): ");
        scanf("%d/%d/%d",&addEmployeeInfoInDataBase.petsa_nga_ngsulod_ang_empleyado.dd,&addEmployeeInfoInDataBase.petsa_nga_ngsulod_ang_empleyado.mm,&addEmployeeInfoInDataBase.petsa_nga_ngsulod_ang_empleyado.yyyy);
        //check date petsa_nga_ngsulod_ang_empleyado
        status = isValidDate(&addEmployeeInfoInDataBase.petsa_nga_ngsulod_ang_empleyado);
        if (!status)
        {
            printf("\n\t\t\tPlease enter a valid date.\n");
        }
    }
    while(!status);
    fwrite(&addEmployeeInfoInDataBase,sizeof(addEmployeeInfoInDataBase), 1, fp);
    fclose(fp);
}
// search employee
void searchEmployee()
{
    int found = 0;
    int employeeId =0;
    s_EmployeesInfo addEmployeeInfoInDataBase = {0};
    FILE *fp = NULL;
    fp = fopen(filename,"rb");
    if(fp == NULL)
    {
        printf("\n\t\t\tFile is not opened\n");
        exit(1);
    }
    headMessage("SEARCH EMPLOYEE");
    //put the control on employee detail
    if (fseek(fp,fileheadersize,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while reading file\n");
        exit(1);
    }
    printf("\n\n\t\t\tEnter employee ID NO to search:");
    fflush(stdin);
    scanf("%u",&employeeId);
    while (fread (&addEmployeeInfoInDataBase, sizeof(addEmployeeInfoInDataBase), 1, fp))
    {
        if(addEmployeeInfoInDataBase.empleyado_id == employeeId)
        {
            found = 1;
            break;
        }
    }
    if(found)
    {
        printf("\n\t\t\tEmployee id = %d\n",addEmployeeInfoInDataBase.empleyado_id);
        printf("\n\t\t\tEmployee name = %s",addEmployeeInfoInDataBase.ngalan_sang_empleyado);
        printf("\t\t\tEmployee Salary = %f\n",addEmployeeInfoInDataBase.empleyado_sweldo);
        printf("\t\t\tFather Name = %s",addEmployeeInfoInDataBase.tatay);
        printf("\n\t\t\tEmployee Address = %s",addEmployeeInfoInDataBase.address_sang_empleyado);
        printf("\t\t\tEmployee Admission Date(day/month/year) =  (%d/%d/%d)",addEmployeeInfoInDataBase.petsa_nga_ngsulod_ang_empleyado.dd,
               addEmployeeInfoInDataBase.petsa_nga_ngsulod_ang_empleyado.mm, addEmployeeInfoInDataBase.petsa_nga_ngsulod_ang_empleyado.yyyy);
    }
    else
    {
        printf("\n\t\t\tNo Record");
    }
    fclose(fp);
    printf("\n\n\n\t\t\tPress any key to go to main menu.....");
    fflush(stdin);
    getchar();
}
// view employees function
void viewEmployee()
{
    int found = 0;
    s_EmployeesInfo addEmployeeInfoInDataBase = {0};
    FILE *fp = NULL;
    unsigned int countEmployee = 1;
    headMessage("VIEW EMPLOYEE DETAILS");
    fp = fopen(filename,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    if (fseek(fp,fileheadersize,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("Facing issue while reading file\n");
        exit(1);
    }
    //Print employee count
    printf("\n\t\t\tEmployee Count = %d\n\n",countEmployee);
    while (fread (&addEmployeeInfoInDataBase, sizeof(addEmployeeInfoInDataBase), 1, fp))
    {
        printf("\t\t\tEmployee id = %u\n",addEmployeeInfoInDataBase.empleyado_id);
        printf("\t\t\tEmployee Name = %s",addEmployeeInfoInDataBase.ngalan_sang_empleyado);
        printf("\t\t\tEmployee Salary = %f\n",addEmployeeInfoInDataBase.empleyado_sweldo);
        printf("\t\t\tFather Name = %s",addEmployeeInfoInDataBase.tatay);
        printf("\t\t\tEmployee Address = %s",addEmployeeInfoInDataBase.address_sang_empleyado);
        printf("\t\t\tEmployee Admission Date(day/month/year) =  (%d/%d/%d)\n\n",addEmployeeInfoInDataBase.petsa_nga_ngsulod_ang_empleyado.dd,
               addEmployeeInfoInDataBase.petsa_nga_ngsulod_ang_empleyado.mm, addEmployeeInfoInDataBase.petsa_nga_ngsulod_ang_empleyado.yyyy);
        found = 1;
        ++countEmployee;
    }
    fclose(fp);
    if(!found)
    {
        printf("\n\t\t\tNo Record");
    }
    printf("\n\n\t\t\tPress any key to go to main menu.....");
    fflush(stdin);
    getchar();
}
// Delete employee entry
void deleteEmployee()
{
    int found = 0;
    int employeeDelete = 0;
    sFileHeader fileHeaderInfo = {0};
    s_EmployeesInfo addEmployeeInfoInDataBase = {0};
    FILE *fp = NULL;
    FILE *tmpFp = NULL;
    headMessage("Delete employee Details");
    fp = fopen(filename,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    tmpFp = fopen("tmp.bin","wb");
    if(tmpFp == NULL)
    {
        fclose(fp);
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,fileheadersize, 1, fp);
    fwrite(&fileHeaderInfo,fileheadersize, 1, tmpFp);
    printf("\n\t\t\tEnter employee ID NO. for delete:");
    scanf("%d",&employeeDelete);
    while (fread (&addEmployeeInfoInDataBase, sizeof(addEmployeeInfoInDataBase), 1, fp))
    {
        if(addEmployeeInfoInDataBase.empleyado_id != employeeDelete)
        {
            fwrite(&addEmployeeInfoInDataBase,sizeof(addEmployeeInfoInDataBase), 1, tmpFp);
        }
        else
        {
            found = 1;
        }
    }
    (found)? printf("\n\t\t\tRecord deleted successfully....."):printf("\n\t\t\tRecord not found");
    fclose(fp);
    fclose(tmpFp);
    remove(filename);
    rename("tmp.bin",filename);
}
//function to update credential
void updateCredential(void)
{
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    unsigned char userName[maximumUname] = {0};
    unsigned char pass[maximumUname] = {0};
    headMessage("Update Credential");
    fp = fopen(filename,"rb+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,fileheadersize, 1, fp);
    if (fseek(fp,0,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while updating password\n");
        exit(1);
    }
    printf("\n\n\t\t\tNew Username:");
    fflush(stdin);
    fgets(userName,maximumUname,stdin);
    printf("\n\n\t\t\tNew Password:");
    fflush(stdin);
    fgets(pass,maximumPassword,stdin);
    strncpy(fileHeaderInfo.uname,userName,sizeof(userName));
    strncpy(fileHeaderInfo.pass,pass,sizeof(pass));
    fwrite(&fileHeaderInfo,fileheadersize, 1, fp);
    fclose(fp);
    printf("\n\t\t\tYour Password has been changed successfully");
    printf("\n\t\t\ttLogin Again:");
    fflush(stdin);
    getchar();
    exit(1);
}
//Display menu
void menu()
{
    int choice = 0;
    do
    {
        headMessage("MAIN MENU");
        printf("\n\t\t\tMAIN MENU\n\t\t\t\t\t ______________________________________________");
    printf("\n\t\t\t\t\t| [1] ADD EMPLOYEE                             |");
    printf("\n\t\t\t\t\t| _____________________________________________|");
    printf("\n\t\t\t\t\t| [2] SEARCH EMPLOYEE                          |");
    printf("\n\t\t\t\t\t| _____________________________________________|");
    printf("\n\t\t\t\t\t| [3] VIEW EMPLOYEE                            |");
    printf("\n\t\t\t\t\t| _____________________________________________|");
    printf("\n\t\t\t\t\t| [4] DELETE EMPLOYEE                          |");
    printf("\n\t\t\t\t\t| _____________________________________________|");
    printf("\n\t\t\t\t\t| [5] UPDATE PASSWORD                          |");
    printf("\n\t\t\t\t\t| _____________________________________________|");
    printf("\n\t\t\t\t\t| [0] EXIT                                     |\n\t\t\t\t\t________________________________________________\n\t\t\t\t\t\t\t\t");

        printf("\n\n\n\t\t\tPLEASE SELECT YOUR CHOICE IN THE ABOVE BOX: ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            addEmployeeInDataBase();
            break;
        case 2:
            searchEmployee();
            break;
        case 3:
            viewEmployee();
            break;
        case 4:
            deleteEmployee();
            break;
        case 5:
            updateCredential();
            break;
        case 0:
            printf("\n\n\n\t\t\t\tTHANK YOU FOR USING THIS SYSTEM !!!\n\n\n\n\n");
            exit(1);
            break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
        }                                            //Switch Ended
    }
    while(choice!=0);                                        //Loop Ended
}
//login password
void login()
{
    unsigned char userName[maximumUname] = {0};
    unsigned char pass[maximumPassword] = {0};
    int L=0;
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    headMessage("Login");
    fp = fopen(filename,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,fileheadersize, 1, fp);
    fclose(fp);
    do
    {
        printf("\n\n\n\t\t\t\tUsername:");
        fgets(userName,maximumUname,stdin);
        printf("\n\t\t\t\tPassword:");
        fgets(pass,maximumPassword,stdin);
        if((!strcmp(userName,fileHeaderInfo.uname)) && (!strcmp(pass,fileHeaderInfo.pass)))
        {
            menu();
        }
        else
        {
            printf("\t\t\t\tLogin Failed Enter Again Username & Password\n\n");
            L++;
        }
    }
    while(L<=3);
    if(L>3)
    {
        headMessage("Login Failed");
        printf("\t\t\t\tSorry,Unknown User.");
        getch();
        system("cls");
    }
}
//Check file exist or not
int isFileExists(const char *path)
{
    // Try to open file
    FILE *fp = fopen(path, "rb");
    int status = 0;
    // If file does not exists
    if (fp != NULL)
    {
        status = 1;
        // File exists hence close file
        fclose(fp);
    }
    return status;
}
void init()
{
    FILE *fp = NULL;
    int status = 0;
    const char defaultUsername[] ="aticleworld\n";
    const char defaultPassword[] ="aticleworld\n";
    sFileHeader fileHeaderInfo = {0};
    status = isFileExists(filename);
    if(!status)
    {
        //create the binary file
        fp = fopen(filename,"wb");
        if(fp != NULL)
        {
            //Copy default password
            strncpy(fileHeaderInfo.pass,defaultPassword,sizeof(defaultPassword));
            strncpy(fileHeaderInfo.uname,defaultUsername,sizeof(defaultUsername));
            fwrite(&fileHeaderInfo,fileheadersize, 1, fp);
            fclose(fp);
        }
    }
}
int main()
{
    init();
    welcomeMessage();
    login();
    return 0;
}
