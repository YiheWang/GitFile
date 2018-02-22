//============================================================================
// Name        : lab2.cpp
// Author      : Yihe Wang
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <cmath>
using namespace std;

unsigned long FactorialOfNumber(unsigned short);
int LeapYear(int);
int Maximum(double,double);
float DivisionOfTwoNumbers(int,int);
void PrintArray(int *);
int *ArithmeticOperation(unsigned short,int *);
//To transform decimal number into binary number using arithmetic operation
int *BitwiseOperation(unsigned short, int *);
//To transform decimal number into binary number using bitwise operation


int main() {
	cout<<"Welcome to section 1!"<<endl;
	char choice;

	do{
	cout<<"\nPlease make a choose:\na.Factorial of a number\n"
			"b.Leap year or not\nc.Maximum\nd.Division of two number\ne.Exit"<<endl;
	//display the choices for user
	cin>>choice;

	switch(choice){
		//choice a
		case 'a':
			unsigned short num;
			cout<<"Please enter a number bigger than 0 and less than 12:"<<endl;
			cin>>num;//number input

			//error check
			while(num>12){
				cout<<"Error! Please enter a number bigger than 0 and less than 12:"<<endl;
				cin>>num;
			}

			//call the function to calculate the result
			cout<<"The factorial of "<<num<<" is "<<FactorialOfNumber(num)<<endl;
			break;
		case 'b':
			//case b
			int year;
			cout<<"\nPlease enter a year:"<<endl;
			cin>>year;//number input

			if(LeapYear(year))
				cout<<year<<" is a leap year."<<endl;//leap year
			else
				cout<<year<<" is not a leap year."<<endl;//not a leap year
			break;
		case 'c':
			//case c
			double num1,num2;
			cout<<"\nPlease enter two number:"<<endl;
			cin>>num1>>num2;//number input

			if(Maximum(num1,num2))
				cout<<num1<<" is bigger than "<<num2<<endl;//num1 is bigger
			else
				cout<<num1<<" is less than "<<num2<<endl;//num2 is bigger
			break;
		case 'd':
			float num3,num4;
			cout<<"\nPlease enter two number:"<<endl;
			cin>>num3>>num4;//number input

			if(!num4){
				cout<<"\nError! Second number can not be zero,enter second number again:"<<endl;
				cin>>num4;//number input
			}
			cout<<"The division of "<<num3<<" "<<num4<<" is "
					<<DivisionOfTwoNumbers(num3,num4)<<endl;//call the function to display result
			break;
		case 'e':
			break;
	}
	getchar();
	}while(choice!='e');//exit when choose e
	cout<<"test"<<endl;

	do{
		int choice;
		char method;
		int *binary=(int* )malloc(sizeof(int)*50);
		//malloc space for the array

		cout<<"Please choose a method to convert decimal number to binary number:"<<endl;
		cout<<"a: Using arithmetic operations:+,-,*,/,%\n"
				"b: Using bitwise operations:&,|,^,<<,>>,~\n"
				"c: exit"<<endl;
		cin>>method;// ask the user to make choice and input

		while(method!='a'&&method!='b'){
			cout<<"Error! Please choose a method to convert decimal number to binary number:"<<endl;
			cout<<"a: Using arithmetic operations:+,-,*,/,%\n"
				"b: Using bitwise operations:&,|,^,<<,>>,~\n"
				"c: exit"<<endl;
			cin>>method;// ask the user to make choice and input
		}

		if(method=='a'){
			//method of arithmetic operations
			unsigned short number;

			cout<<"Please enter a decimal number:"<<endl;
			cin>>number;

			binary=ArithmeticOperation(number,binary);
			//call the function to convert decimal number into binary
			PrintArray(binary);
			//print out the number store in array
		}
		else if(method=='b'){
			//method of bitwise operations
			unsigned short number;

			cout<<"Please enter a decimal number:"<<endl;
			cin>>number;

			binary=BitwiseOperation(number,binary);
			//call the function to convert decimal number into binary
			PrintArray(binary);
			//print out the number store in array
		}
		else
			break;

		cout<<"Do you want run the program again? yes:1, no:0 :"<<endl;
		cin>>choice;

		while(choice!=1&&choice!=2){
			cout<<"Invalid choice! Do you want run the program again? yes:1, no:0 :"<<endl;
			cin>>choice;
		}//use loop to run it again
		if(!choice)
			break;//end the loop when choose 0
	}while(1);
	
	cout<<This is a command<<endl;

	return 0;
}

unsigned long FactorialOfNumber(unsigned short num)
{
	if(num<=0)
		return 1;
	else
		return num*FactorialOfNumber(num-1);
		//use recursion to call the function itself to get the result
}

int LeapYear(int year)
{
	if((year%400==0&&year%3200!=0)||(year%4==0&&year%100!=0))
		//to judge if this year is a leap year
		return 1;//leap year
	else
		return 0;//not a leap year
}

int Maximum(double num1,double num2)
{
	if(num1>num2)
		return 1;//num1 bigger
	else
		return 0;//num2 bigger
}

float DivisionOfTwoNumbers(int num1,int num2)
{
	return static_cast <float>(num1)/static_cast<float>(num2);//use float to cast the number
}

int *ArithmeticOperation(unsigned short number, int *array)
{
	int remainder;
	int result=number;
	int i=49;//store the digit from the end of array

	while(result!=1){
		remainder=result%2;
		result=result/2;
		array[i]=remainder;//keep the remainder
		--i;
	}
	array[i]=result;

	return array;
}
void PrintArray(int *array)
{
	int i;
	for(i=34;i<50;++i)
		printf("%d",array[i]);//print number store in array from 34 to 50

	printf("\n");
}

int *BitwiseOperation(unsigned short number, int *array)
{
	int i;
	unsigned short compare;
	int j=49;
	for(i=0;i<16;++i){
		compare=pow(2,i);//binary number is power of 2

		if(number&compare)//compare each digit of binary number
			array[j--]=1;//digit is 1
		else
			array[j--]=0;//digit is 0
	}

	return array;
}

