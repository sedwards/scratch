#include <stdio.h>
#include <string.h>

//normal structure declaration
struct student_str 
{
	char name[30];
	int age;
};

//structur declaration with typedef
typedef struct {
	char name[30];
	int age;
}employee_str;

//main code
int main()
{
    
	//declare structure variable for student_str
	struct student_str std;
	//declare structure variable for employee_str
	employee_str emp;
	
	//assign values to std 
	strcpy(std.name, "Amit Shukla");
	std.age = 21;
	
	//assign values to emp
	strcpy(emp.name, "Abhishek Jain");
	emp.age = 27;
	
	//print std and emp structure 
	printf("Student detail:\n");
	printf("Name: %s\n",std.name);
	printf("Age: %d\n",std.age);
	
	printf("Employee detail:\n");
	printf("Name: %s\n",emp.name);
	printf("Age: %d\n",emp.age);	
	
	return 0;
}
