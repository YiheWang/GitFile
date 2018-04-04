//============================================================================
// Name        : Lab6.cpp
// Author      : Yihe Wang
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <cmath>
#include <climits>
#include <iomanip>
using namespace std;

class Signal{
	private:
		int length;
		double maxValue;
		double minValue;
		double average;
		vector<double> rawSignal;
		vector<double> modifiedSignal;
		void updatedAverageSignal(vector<double>);
		void updatedMaxSignal(vector<double>);
		void updatedMinSignal(vector<double>);
	public:
		Signal();
		Signal(int);
		Signal(string);
		~Signal();
		string getFileName(int);
		//void offsetFileSignal(double);//take offset factor as input
		//void scaleFileSignal(double);//take scale factor as input
		void getStatistics();
		void centeringSignal();
		void normalizeSignal();
		void sig_info();
		void operator+(double);
		void operator*(double);
		void save_file(string);
		void printSignal();
		double getMax() {return maxValue;};
		double getMin() {return minValue;};
		double getAverage() {return average;};
		double getLength() {return length;};
		void setMax(double num) {maxValue = num;};
		void setMin(double num) {minValue = num;};
		void setAverage(double num) {average = num;};
		void setLength(int num) {length = num;};
		double getIndexValue(int index) {return modifiedSignal[index];};
		void setIndexValue(double num, int index) {modifiedSignal[index] = num;};
};

Signal operator+(Signal &obj1, Signal &obj2);

void printHelp();

int main(int argc, char *argv[]) {
	int fileNumber;
	string options;
	int choice;
	Signal signal1;
	Signal signal2;
	Signal signal3;

	printHelp();
	//This is the case we do not enter something in the command line
	if(argc==1){
		cout<<"You did not enter the fileNumber! Please enter a fileNumber:";
		cin>>fileNumber;
		Signal signal(fileNumber);
		signal1 = signal;
		signal2 = signal;
	}
	else if(argc==3){
		if(argv[1][0]=='-'&&argv[1][1]=='n'&&isdigit(argv[2][0])){
			Signal signal(atoi(argv[2]));
			signal1 = signal;
			signal2 = signal;
			//printHelp()
		}
		else if(argv[1][0]=='-'&&argv[1][1]=='f'){
			Signal signal(argv[2]);
			signal1 = signal;
			signal2 = signal;
			//printHelp();
		}
		else{
			cout<<"Wrong format!"<<endl;
			printHelp();
			return 1;
		}
	}
	else{
		cout<<"Wrong format!"<<endl;
		printHelp();
	}

	do{
		cout<<"What you want to do with the signal? Enter a command:";
		cin>>options;
		if(options=="-o"){
			double offset;
			cout<<"Enter a offset number:";
			cin>>offset;
			signal2 + offset;
			signal2.printSignal();
		}//offset the signal
		else if(options=="-s"){
			double scale;
			cout<<"Enter a scale number:";
			cin>>scale;
			signal2 * scale;
			signal2.printSignal();
		}//scale the signal
		else if(options=="-S"){
			signal2.getStatistics();
			signal2.sig_info();
			signal2.printSignal();
		}
		else if(options=="-C"){
			signal2.centeringSignal();
			signal2.printSignal();
		}//get the max,min,average of the signal
		else if(options=="-N"){
			signal2.normalizeSignal();
			signal2.printSignal();
		}//normalize the signal
		else if(options=="-e"){
			break;
		}//end the program
		else if(options=="-h"){
			printHelp();
		}
		else{
			printHelp();
			cout<<"Wrong input format! Enter again:";
			//cin>>options;
		}//check error
	}while(options!="-e");

	signal3 = signal1 + signal2;

	cout<<"Here is the data for signal3:"<<endl;
	signal3.sig_info();
	signal3.printSignal();


	cout<<"Do you want to save the modified signal? Yes:1, No:0  :";
	cin>>choice;
	if(choice){
		string fileName;
		cout<<"Enter the name of the new file:";
		cin>>fileName;
		signal2.save_file(fileName);
	}//save file

	cout<<"Have a nice day!"<<endl;

	return 0;
}

Signal operator+(Signal &obj1, Signal &obj2)
{
	Signal obj3;
	obj1.getStatistics();
	obj2.getStatistics();
	if(obj1.getLength()!=obj2.getLength()){
		return obj3;
	}//only add when they have the same length
	else{
		obj3.setLength(obj2.getLength());
		obj3.setAverage(obj1.getAverage() + obj2.getAverage());
	}//add the average to get the new average

	if(obj1.getMax()>obj2.getMax()){
		obj3.setMax(obj1.getMax());
	}
	else{
		obj3.setMax(obj2.getMax());
	}//find the max value from two object

	int length = obj3.getLength(), i;
	for(i=0; i<length;++i){
		obj3.setIndexValue(obj1.getIndexValue(i)+obj2.getIndexValue(i),i);
	}//add all the value together

	return obj3;
}

string Signal::getFileName(int number)
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

Signal::Signal()
{
	string fileName = "Raw_data_01.txt";
	ifstream in;
	in.open(fileName);
	if(!in.is_open()){
		cout<<"File Raw_data_01.txt open error!"<<endl;
	}//check error

	char line[100] = {0};
	in.getline(line,sizeof(line),'\n');//read the first line

	double temp;
	while(!in.eof()){
		in>>temp;
		rawSignal.push_back(temp);
	}//write the signal into the vector
	modifiedSignal = rawSignal;
	length = modifiedSignal.size();
}

Signal::Signal(int fileNumber)
{
	string fileName = getFileName(fileNumber);
	ifstream in;
	in.open(fileName);
	if(!in.is_open()){
		cout<<"File "<<fileName<<" open error!"<<endl;
	}//check error

	char line[100] = {0};
	in.getline(line,sizeof(line),'\n');//read the first line

	double temp;
	while(!in.eof()){
		in>>temp;
		rawSignal.push_back(temp);
	}//write signal into vector
	modifiedSignal = rawSignal;
	length = modifiedSignal.size();
}

Signal::Signal(string fileName)
{
	ifstream in;
	in.open(fileName);
	if(!in.is_open()){
		cout<<"File "<<fileName<<" open error!"<<endl;
	}//check error

	char line[100] = {0};
	in.getline(line,sizeof(line),'\n');//read the first line

	double temp;
	while(!in.eof()){
		in>>temp;
		rawSignal.push_back(temp);
	}//write signal into vector
	modifiedSignal = rawSignal;
	length = modifiedSignal.size();
}

Signal::~Signal()
{
	rawSignal.clear();
	modifiedSignal.clear();
}

void Signal::operator+(double offset)
{
	int i;
	for(i=0;i<length;++i){
		modifiedSignal[i] = modifiedSignal[i] + offset;
	}//add the offset number to each signal
	getStatistics();
}

void Signal::operator*(double scale)
{
	int i;
	for(i=0;i<length;++i){
		modifiedSignal[i] = modifiedSignal[i] * scale;
	}//multiple the scale number to each signal
	getStatistics();
}

void Signal::getStatistics()
{
	updatedMaxSignal(modifiedSignal);
	updatedMinSignal(modifiedSignal);
	updatedAverageSignal(modifiedSignal);//update the min,max,average
}

void Signal::centeringSignal()
{
	*this + (-this->average);
	getStatistics();
	//modifiedSignal + (-average);//call the operator +
}

void Signal::normalizeSignal()
{
	*this + (-this->minValue);
	*this * (1/(this->maxValue - this->minValue));
	getStatistics();
	//(Signal + (-minValue))*(1/(maxValue - minValue));
}
void Signal::updatedAverageSignal(vector<double> vector)
{
	int i = 0;
	double total = 0;
	for(i=0;i<(int)modifiedSignal.size();++i){
		total = total + vector[i];
	}//use for loop to get the total

	average = (double)total/i;//get average
}

void Signal::updatedMaxSignal(vector<double> vector)
{
	int i;
	maxValue = INT_MIN;
	for(i=0;i<(int)modifiedSignal.size();++i){
		if(vector[i]>maxValue){
			maxValue = vector[i];
		}//use for loop to get max
	}
}

void Signal::updatedMinSignal(vector<double> vector)
{
	int i;
	minValue = INT_MAX;
	for(i=0;i<(int)modifiedSignal.size();++i){
		if(vector[i]<minValue){
			minValue = vector[i];
		}//use for loop to get min
	}
}

void Signal::sig_info()
{
	cout<<"Length of the signal is "<<length<<endl;
	cout<<"Maximum of the signal is "<<maxValue<<endl;
	cout<<"Minimum of the signal is "<<minValue<<endl;
	cout<<"Average of the signal is "<<average<<endl;
	//print all the stuff out
}

void Signal::save_file(string fileName)
{
	getStatistics();//update the min, max , average
	ofstream out;
	out.open(fileName);
	if(!out.is_open()){
		cout<<"File "<<fileName<<" open error!"<<endl;
	}

	int i = 0;
	out<<length<<" ";
	out<<maxValue<<endl;//write the length and max value in the first line
	for(i=0;i<(int)modifiedSignal.size();++i){
		out<<setprecision(4)<<setiosflags(ios_base::fixed)<<modifiedSignal[i]<<endl;
	}
}

void Signal::printSignal()
{
	int i = 0;
	for(i=0;i<(int)modifiedSignal.size();++i){
		cout<<setprecision(4)<<setiosflags(ios_base::fixed)<<modifiedSignal[i]<<endl;
	}//use for loop to print the vector out
}

void printHelp()
{
	cout<<"Here is the different options:"<<endl;
	cout<<"These two are for command line only"<<endl;
	cout<<"-n        File number(value needed)"<<endl;
	cout<<"-f        File name(fileName needed)"<<endl;
	cout<<"There following are for operation choices"<<endl;
	cout<<"-o        Offset value(value needed)"<<endl;
	cout<<"-s        Scale factor(value needed)"<<endl;
	//cout<<"-r        Rename files(value needed)"<<endl;
	cout<<"-S        Get statistics(value needed)"<<endl;
	cout<<"-C        Center the signal(value needed)"<<endl;
	cout<<"-N        Normalize signal(value needed)"<<endl;
	cout<<"-h        Help(display how the program should be called)"<<endl;
	cout<<"-e        End the program"<<endl;
	cout<<"Here is two sample for command line:"<<endl;
	cout<<"./My_Lab4_program -n 3 "<<endl;
	cout<<"./My_Lab4_program -f fileName.txt "<<endl;
}
