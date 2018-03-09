//============================================================================
// Name        : Lab4_Part2.cpp
// Author      : Yihe Wang
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <cmath>
#include <climits>
using namespace std;

string getFileName(int);//take file number as input
string createFileName(int,string);
//create a new file name when operation is offset and scale
void offsetFileSignal(int, string,double);//take file name and command string
void scaleFileSignal(int, string,double);//take file name and command string
void renameAndCopyFile(int, string);//take raw file number and new file name
void getStatistics(int, string);//take raw file number and command string
void centeringSignal(int, string);//take raw file number and command string
void normalizeSignal(int, string);//take raw file number and command string

double getAverageSignal(string);//take filename
double getMaxSignal(string);//take filename
double getMinSignal(string);//take filename
void printFormat();

int main(int argc, char *argv[]) {


	int count = 1;
	int fileNumber;
	bool fileNumberExist = false;

	if(argc==2&&argv[1][0]=='-'&&argv[1][1]=='h'){
		cout<<"Help!"<<endl;
		printFormat();
	}//check if the case is help case
	else{
		while(argv[count]){
			if(argv[count][0]=='-'&&argv[count][1]=='n'){
				if(isdigit(argv[count+1][0])){
					fileNumber = atoi(argv[count+1]);
				}
				else{
					cout<<"Wrong format!"<<endl;
					printFormat();
					return 0;
				}
				fileNumberExist = true;
			}
			++count;
		}//use while loop to find file 
	}

	if(!fileNumberExist){
		cout<<"You have to enter the file number"<<endl;
		printFormat();
	}//if the file number not exist, the program can not continue

	count = 1;//initialize the count
	while(argv[count]){
		if(argv[count][0]=='-'&&argv[count][1]=='n'){
			count = count + 2;//skip the -n case
		}
		else if(argv[count][0]=='-'&&argv[count][1]=='o'){
			if(argv[count+1]==NULL){
				cout<<"Wrong format!"<<endl;
				printFormat();
				return 0;//check format
			}
			else if(isdigit(argv[count+1][0])){
				double offsetNumber = atoi(argv[count+1]);
				offsetFileSignal(fileNumber,"-o",offsetNumber);
				count = count + 2;
			}//This is the correct format, call offset function
			else{
				cout<<"Wrong format!"<<endl;
				printFormat();
				return 0;
			}//format wrong
		}
		else if(argv[count][0]=='-'&&argv[count][1]=='s'){
			if(argv[count+1]==NULL){
				cout<<"Wrong format"<<endl;
				printFormat();
				return 0;//check format
			}
			else if(isdigit(argv[count+1][0])){
				double scaleNumber = atoi(argv[count+1]);
				scaleFileSignal(fileNumber,"-s",scaleNumber);
				count = count + 2;
			}//This is the correct format, call the function
			else{
				cout<<"Wrong format!"<<endl;
				printFormat();
				return 0;
			}//format wrong
		}
		else if(argv[count][0]=='-'&&argv[count][1]=='r'){
			if(argv[count+1]==NULL){
				cout<<"Wrong format"<<endl;
				printFormat();
				return 0;
			}//check format
			else{
				renameAndCopyFile(fileNumber,argv[count+1]);
				count = count + 2;
			}//This is the correct format. call the function
		}
		else if(argv[count][0]=='-'&&argv[count][1]=='S'){
			getStatistics(fileNumber,"-S");
			++count;
		}// -S case, just call the function
		else if(argv[count][0]=='-'&&argv[count][1]=='C'){
			centeringSignal(fileNumber,"-C");
			++count;
		}// -C case, just call the function
		else if(argv[count][0]=='-'&&argv[count][1]=='N'){
			normalizeSignal(fileNumber,"-N");
			++count;
		}// -N case, just call the function
	}//end the while loop when argv equal to null

	cout<<"Have a nice day!"<<endl;
	/*offsetFileSignal(1,"-o",1);
	scaleFileSignal(1,"-s",2);
	renameAndCopyFile(1,"newFileName.txt");
	getStatistics(1,"-S");
	centeringSignal(1,"-C");
	normalizeSignal(1,"-N");*/

	return 0;
}

string getFileName(int number)
{
	string fileName;

	if(number>=0&&number<10){
		fileName = "Raw_data_0" + to_string(number) +".txt";
	}
	else{
		fileName = "Raw_data_" + to_string(number) +".txt";
	}//get the file name by the file number
	return fileName;
}

string createFileName(int number, string operation)
{
	string fileName;

	//create the file name by judging the command string
	if(operation=="-o"){
		if(number>=0&&number<10){
			fileName = "Offset_data_0" + to_string(number) +".txt";
		}
		else{
			fileName = "Offset_data_" + to_string(number) +".txt";
		}
	}
	else if(operation=="-s"){
		if(number>=0&&number<10){
			fileName = "Scale_data_0" + to_string(number) +".txt";
				}
		else{
			fileName = "Scale_data_" + to_string(number) +".txt";
		}
	}
	else if(operation=="-S"){
		if(number>=0&&number<10){
			fileName = "Statistics_data_0" + to_string(number) +".txt";
				}
		else{
			fileName = "Statistics_data_" + to_string(number) +".txt";
		}
	}
	else if(operation=="-C"){
		if(number>=0&&number<10){
			fileName = "Centered_data_0" + to_string(number) +".txt";
				}
		else{
			fileName = "Centered_data_" + to_string(number) +".txt";
		}
	}
	else if(operation=="-N"){
		if(number>=0&&number<10){
			fileName = "Normalized_data_0" + to_string(number) +".txt";
				}
		else{
			fileName = "Normalized_data_" + to_string(number) +".txt";
		}
	}

	return fileName;
}

void offsetFileSignal(int number, string operation, double offset)
{
	string inFileName = getFileName(number);
	string outFileName = createFileName(number,operation);
	ifstream in;
	ofstream out;
	in.open(inFileName);
	out.open(outFileName);//get the file name and open file
	if(!in.is_open()){
		cout<<"open source file "<<inFileName<<"error!"<<endl;
		return;
	}
	if(!out.is_open()){
		cout<<"open source file "<<outFileName<<"error!"<<endl;
		return;
	}//check if file open wrong

	char length[20];
	char line[1024] = {0};
	in.getline(line,sizeof(line),'\n');//read the first line
	stringstream word(line);//seperate  the first line by whitespace

	word>>length;
	out<<atof(length)<<" ";
	out<<offset<<endl;//The first line of output file

	while(!in.eof()){
		in.getline(line,sizeof(line),'\n');
		out<<atof(line)+offset<<endl;
	}//read the file until end

	in.close();
	out.close();
}

void scaleFileSignal(int number, string operation, double scale)
{
	string inFileName = getFileName(number);
	string outFileName = createFileName(number,operation);
	ifstream in;
	ofstream out;
	in.open(inFileName);
	out.open(outFileName);//get the file name and open the file
	if(!in.is_open()){
		cout<<"open source file "<<inFileName<<" error!"<<endl;
		return;
	}
	if(!out.is_open()){
		cout<<"open source file "<<outFileName<<" error!"<<endl;
		return;
	}//check if file open wrong

	char length[20];
	char line[1024] = {0};
	in.getline(line,sizeof(line),'\n');//read the first line
	stringstream word(line);//seperate  the first line by whitespace

	word>>length;
	out<<atof(length)<<" ";
	out<<scale<<endl;//This is the first line of the output file

	while(!in.eof()){
		in.getline(line,sizeof(line),'\n');
		out<<atof(line)*scale<<endl;
	}//read the file until end

	in.close();
	out.close();
}

void renameAndCopyFile(int number, string fileName)
{
	string inFileName = getFileName(number);
	string outFileName = fileName;

	ifstream in;
	ofstream out;
	in.open(inFileName);
	out.open(outFileName);//get the file name and open file
	if(!in.is_open()){
		cout<<"open source file "<<inFileName<<"error!"<<endl;
		return;
	}
	if(!out.is_open()){
		cout<<"open source file "<<outFileName<<"error!"<<endl;
		return;
	}//check if the file open wrong

	char length[20];
	char max[20];
	char line[1024] = {0};
	in.getline(line,sizeof(line),'\n');//read the first line
	stringstream word(line);//seperate  the first line by whitespace

	word>>length;
	word>>max;
	out<<atof(length)<<" ";
	out<<atof(max)<<endl;
	while(!in.eof()){
		in.getline(line,sizeof(line),'\n');
		out<<atof(line)<<endl;
	}//read the file until end, copy them to the output file

	in.close();
	out.close();
}

void getStatistics(int number, string operation)
{
	string inFileName = getFileName(number);
	string outFileName = createFileName(number,operation);
	//cout<<inFileName<<outFileName<<endl;
	ofstream out;
	out.open(outFileName);
	if(!out.is_open()){
		cout<<"open source file "<<outFileName<<"error!"<<endl;
		return;
	}

	double average = getAverageSignal(inFileName);
	double max = getMaxSignal(inFileName);//get the average and max

	out<<average<<" ";
	out<<max<<endl;//put them in the output file

	out.close();
}

void centeringSignal(int number, string operation)
{
	string inFileName = getFileName(number);
	double average = getAverageSignal(inFileName);
	string outFileName = createFileName(number,operation);

	ifstream in;
	ofstream out;
	in.open(inFileName);
	out.open(outFileName);//get the file name and open the file
	if(!in.is_open()){
		cout<<"open source file "<<inFileName<<"error!"<<endl;
		return;
	}
	if(!out.is_open()){
		cout<<"open source file "<<outFileName<<"error!"<<endl;
		return;
	}//check error

	char length[20];
	char max[20];
	char line[1024] = {0};
	in.getline(line,sizeof(line),'\n');//read the first line
	stringstream word(line);//seperate  the first line by whitespace

	word>>length;
	word>>max;
	out<<atof(length)<<" ";
	out<<atof(max)<<endl;//This is the first line of output file
	while(!in.eof()){
		in.getline(line,sizeof(line),'\n');
		out<<atof(line)-average<<endl;
	}//read the file until end

	in.close();
	out.close();
}

void normalizeSignal(int number, string operation)
{
	string inFileName = getFileName(number);
	double average = getAverageSignal(inFileName);
	double max = getMaxSignal(inFileName);
	double min = getMinSignal(inFileName);
	string outFileName = createFileName(number,operation);

	ifstream in;
	ofstream out;
	in.open(inFileName);
	out.open(outFileName);//get the filename and open the file
	if(!in.is_open()){
		cout<<"open source file "<<inFileName<<"error!"<<endl;
		return;
	}
	if(!out.is_open()){
		cout<<"open source file "<<outFileName<<"error!"<<endl;
		return;
	}//check error

	char length[20];
	char max1[20];
	char line[1024] = {0};
	in.getline(line,sizeof(line),'\n');//read the first line
	stringstream word(line);//seperate  the first line by whitespace

	word>>length;
	word>>max1;
	out<<atof(length)<<" ";
	out<<atof(max1)<<endl;//This is the first line of output file
	while(!in.eof()){
		in.getline(line,sizeof(line),'\n');
		out<<(atof(line)-min)/(max-min)<<endl;
	}//read the file until end

	in.close();
	out.close();
}

double getAverageSignal(string fileName)
{
	ifstream in;
	in.open(fileName);
	if(!in.is_open()){
		cout<<"File open error!"<<endl;
	}

	char length[20];
	char line[1024] = {0};
	double total = 0;
	double average;
	in.getline(line,sizeof(line),'\n');//read the first line
	stringstream word(line);//seperate  the first line by whitespace

	word>>length;

	double temp;
	while(!in.eof()){
		in.getline(line,sizeof(line),'\n');
		temp = atof(line);
		total = total + temp;
	}//read the file until end
	average = total/atof(length);

	in.close();
	return average;
}

double getMaxSignal(string fileName)
{
	ifstream in;
	in.open(fileName);
	if(!in.is_open()){
		cout<<"File open error!"<<endl;
	}

	char line[1024] = {0};
	double max = INT_MIN;//define a infinite small number
	in.getline(line,sizeof(line),'\n');//read the first line
	stringstream word(line);//seperate  the first line by whitespace

	double temp;
	while(!in.eof()){
		in.getline(line,sizeof(line),'\n');
		temp = atof(line);
		if(max<temp){
			max = temp;
		}
	}//read the file until end to find the max

	in.close();
	return max;
}

double getMinSignal(string fileName)
{
	ifstream in;
	in.open(fileName);
	if(!in.is_open()){
		cout<<"File open error!"<<endl;
	}

	char line[1024] = {0};
	double min = INT_MAX;// define a infinite big number
	in.getline(line,sizeof(line),'\n');//read the first line
	stringstream word(line);//seperate  the first line by whitespace

	double temp;
	while(!in.eof()){
		in.getline(line,sizeof(line),'\n');
		temp = atof(line);
		if(min>temp){
			min = temp;
		}
	}//read the file until end to find the min

	in.close();
	return min;
}

void printFormat()
{
	cout<<"Here is the different options:"<<endl;
	cout<<"-n        File number(value needed)"<<endl;
	cout<<"-o        Offset value(value needed)"<<endl;
	cout<<"-s        Scale factor(value needed)"<<endl;
	cout<<"-r        Rename files(value needed)"<<endl;
	cout<<"-S        Get statistics(value needed)"<<endl;
	cout<<"-C        Center the signal(value needed)"<<endl;
	cout<<"-N        Normalize signal(value needed)"<<endl;
	cout<<"-h        Help(display how the program should be called)"<<endl;
	cout<<"Here is a sample :"<<endl;
	cout<<"./My_Lab4_program -n 3 -o 2.5 -r NewName"<<endl;
	//print all the stuff about format
}





