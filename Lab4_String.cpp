//============================================================================
// Name        : Lab4.cpp
// Author      : Yihe Wang
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


// IMPORTANT NOTE: YOU MAY NEED TO COMPILE ADDING THE FOLLOWING FLAG: -std=c++11
//                 OR: -std=c++0x
// Example:  g++ Lab4_strings.cpp -o Lab4_strings -std=c++11
//      or:  g++ Lab4_strings.cpp -o Lab4_strings -std=c++0

#include <iostream>
#include <string>
using namespace std;

int main()
{
	string s1;
	string s2(s1);
	string s3(5,'A');
	string s4("Steve Rogers");
	string s5 = "Tony Stark";
	string s6;


	if(s1.empty()&&s2.empty()){
		cout << "\nEnter a name of super hero in Marvel movies:" << endl;
		getline(cin,s1);
		cout << "\nEnter another name of super hero in Marvel movies:" << endl;
		getline(cin,s2);
		cout<<s1<<" and "<<s2<<" are both super heros in Marvel movies"<<endl;
	}

	cout<<"The number of characters in "<<s5<<" is "<<s5.size()<<endl;

	if(isspace(s4[5])){
		cout<<"The 5th position of s4 is a whitespace"<<endl;
	}
	else
		cout<<"The 5th position of s4 is not a whitespace"<<endl;

	s1 = s4;
	s2 = s5;
	s3 = s1 + " and " + s2;
	int count=0;
	cout<<"There are ";
	for(auto i:s3){
		if(ispunct(i)){
			++count;
		}
	}


	if(s1==s4){
		cout<<s1<<" is Captain America"<<endl;
	}

	if(!(s2!=s5)){
		cout<<s2<<" is Iron Man"<<endl;
	}

	cout<<s3<< "  stand in opposite sides in Captian America 3"<<endl;

	if(s1<s2){
		cout<<s1<<" is lower than "<<s2<<" from Dictionary Ordering"<<endl;
	}
	else if(s1>s3){
		cout<<s1<<" is bigger than "<<s3<<" from Dictionary Ordering"<<endl;
	}

	int digcount=0;
	//int wspacecount=0;
	int letcount=0;
	//int punction=0;

	cout<<"Please enter a string with digits, punctuation characters, letters and whitespace:"<<endl;
	getline(cin,s6);
	for(auto i:s6){
		if(isalpha(i)){
			++letcount;
		}//count the letters in the string
		else if(isdigit(i)){
			++digcount;
		}//count the digits in the string

	}
	cout<<"The number of letters in the string is:"<<letcount<<endl;
	cout<<"The number of digits in the string is:"<<digcount<<endl;
	//print out word here

	cout<<"The string after upper and lower letters is:";
	for(auto i:s6){
			if(isupper(i)){
				i= tolower(i);
				cout<<i;
			}//lower the upper letter
			else if(islower(i)){
				i= toupper(i);
				cout<<i;
			}//upper the lower letter
			else{
				cout<<i;
			}
	}
	cout<<endl;

	cout<<"The string after replace whitespace with '.' is:";
	for(auto i:s6){
			if(isspace(i)){
				i = '.';
				cout<<i;
			}//replace the whitespace with "."
			else{
				cout<<i;
			}
	}
	cout<<endl;

	int puncCount=0;
	cout<<"The words in the s6 is ";
	for(auto i:s6){
		if(isspace(i)){
			++puncCount;
		}
	}
	cout<<++puncCount;

// ****************************************************************************
// Use "Range for" loops (L7_Ex6_Strings.cpp) and operations in table 7.3 to:
// 1) Count the number of letters in your input line above;
// 2) Count the number of digits;
// 3) Count the number of words (may be separated by white spaces, dots, etc.);

// 4) change the case of the letters (upper to lowercase and vice-versa).
// 5) Replace any whitespace with a dot ('.').
// Print the converted text in 4) and 5)
// ****************************************************************************

	return 0;
}
