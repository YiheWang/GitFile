//============================================================================
// Name        : Lab5.cpp
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
		double getAverageSignal(vector<double>);
		double getMaxSignal(vector<double>);
		double getMinSignal(vector<double>);
	public:
		Signal();
		Signal(int);
		Signal(string);
		~Signal();
		string getFileName(int);
		void offsetFileSignal(double);//take offset factor as input
		void scaleFileSignal(double);//take scale factor as input
		void getStatistics();
		void centeringSignal();
		void normalizeSignal();
		void sig_info();
		void save_file(string);
		void printSignal();

};

void printHelp();

int main(int argc, char *argv[]) {
	int fileNumber;
	string options;
	int choice;

	printHelp();
	//This is the case we do not enter something in the command line
	if(argc==1){
		cout<<"You did not enter the fileNumber! Please enter a fileNumber:";
		cin>>fileNumber;
		Signal signal(fileNumber);
		do{
			cout<<"What you want to do with the signal? Enter a command:";
			cin>>options;//enter a file number
			if(options=="-o"){
				double offset;
				cout<<"Enter a offset number:";
				cin>>offset;
				signal.offsetFileSignal(offset);
				signal.printSignal();
			}//offset the signal
			else if(options=="-s"){
				double scale;
				cout<<"Enter a scale number:";
				cin>>scale;
				signal.scaleFileSignal(scale);
				signal.printSignal();
			}//scale the signal
			else if(options=="-S"){
				signal.getStatistics();
				signal.sig_info();
				signal.printSignal();
			}//get the max, min ,average for the signal
			else if(options=="-C"){
				signal.centeringSignal();
				signal.printSignal();
			}//centering the signal
			else if(options=="-N"){
				signal.normalizeSignal();
				signal.printSignal();
			}//normalize the signal
			else if(options=="-h"){
				printHelp();
			}
			else if(options=="-e"){
				break;
			}//end the options
			else{
				printHelp();
				cout<<"Wrong input format! Enter again:";
				//cin>>options;
			}//check format error
		}while(options!="-e");

		cout<<"Do you want to save the modified signal? Yes:1, No:0  :";
		cin>>choice;
		if(choice){
			string fileName;
			cout<<"Enter the name of the new file:";
			cin>>fileName;
			signal.save_file(fileName);
		}//save the signal into new file
	}
	else if(argc==3){
		if(argv[1][0]=='-'&&argv[1][1]=='n'&&isdigit(argv[2][0])){
			Signal signal(atoi(argv[2]));
			//printHelp();
			do{
				cout<<"What you want to do with the signal? Enter a command:";
				cin>>options;
				if(options=="-o"){
					double offset;
					cout<<"Enter a offset number:";
					cin>>offset;
					signal.offsetFileSignal(offset);
					signal.printSignal();
				}//offset the signal
				else if(options=="-s"){
					double scale;
					cout<<"Enter a scale number:";
					cin>>scale;
					signal.scaleFileSignal(scale);
					signal.printSignal();
				}//scale the signal
				else if(options=="-S"){
					signal.getStatistics();
					signal.sig_info();
					signal.printSignal();
				}//get min, max, average of the signal
				else if(options=="-C"){
					signal.centeringSignal();
					signal.printSignal();
				}//centering the signal
				else if(options=="-N"){
					signal.normalizeSignal();
					signal.printSignal();
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

			cout<<"Do you want to save the modified signal? Yes:1, No:0  :";
			cin>>choice;
			if(choice){
			string fileName;
			cout<<"Enter the name of the new file:";
			cin>>fileName;
			signal.save_file(fileName);
			}//save the signal into new file
		}
		else if(argv[1][0]=='-'&&argv[1][1]=='f'){
			Signal signal(argv[2]);
			//printHelp();
			do{
				cout<<"What you want to do with the signal? Enter a command:";
				cin>>options;
				if(options=="-o"){
					double offset;
					cout<<"Enter a offset number:";
					cin>>offset;
					signal.offsetFileSignal(offset);
					signal.printSignal();
				}//offset the signal
				else if(options=="-s"){
					double scale;
					cout<<"Enter a scale number:";
					cin>>scale;
					signal.scaleFileSignal(scale);
					signal.printSignal();
				}//scale the signal
				else if(options=="-S"){
					signal.getStatistics();
					signal.sig_info();
					signal.printSignal();
				}
				else if(options=="-C"){
					signal.centeringSignal();
					signal.printSignal();
				}//get the max,min,average of the signal
				else if(options=="-N"){
					signal.normalizeSignal();
					signal.printSignal();
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

			cout<<"Do you want to save the modified signal? Yes:1, No:0  :";
			cin>>choice;
			if(choice){
				string fileName;
				cout<<"Enter the name of the new file:";
				cin>>fileName;
				signal.save_file(fileName);
			}//save file
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

	cout<<"Have a nice day!"<<endl;

	return 0;
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
	length = 0;
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
}

Signal::Signal(int fileNumber)
{
	length = 0;
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
}

Signal::Signal(string fileName)
{
	length = 0;
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
}

Signal::~Signal()
{
	rawSignal.clear();
	modifiedSignal.clear();
}

void Signal::offsetFileSignal(double offsetNumber)
{
	int i;
	for(i=0;i<(int)modifiedSignal.size();++i){
		modifiedSignal[i] = modifiedSignal[i] + offsetNumber;
 	}//add the offset number to each signal
}
void Signal::scaleFileSignal(double scaleNumber)
{
	int i;
	for(i=0;i<(int)modifiedSignal.size();++i){
		modifiedSignal[i] = scaleNumber * modifiedSignal[i];
 	}//mutiple the scale number with each signal
}

void Signal::getStatistics()
{
	length = modifiedSignal.size();
	maxValue = getMaxSignal(modifiedSignal);
	minValue = getMinSignal(modifiedSignal);
	average = getAverageSignal(modifiedSignal);//update the min,max,average
}

void Signal::centeringSignal()
{
	getStatistics();
	int i;
	for(i=0;i<(int)modifiedSignal.size();++i){
		modifiedSignal[i] = modifiedSignal[i] - average;
	 }//centering the all the signal
}

void Signal::normalizeSignal()
{
	getStatistics();
	int i;
	for(i=0;i<(int)modifiedSignal.size();++i){
		modifiedSignal[i] = (modifiedSignal[i] - minValue)/(maxValue - minValue);
	}//normalize all the signal
}

double Signal::getAverageSignal(vector<double> vector)
{
	int i = 0;
	double total = 0;
	for(i=0;i<(int)modifiedSignal.size();++i){
		total = total + vector[i];
	}//use for loop to get the total

	average = (double)total/i;//get average
	return average;
}

double Signal::getMaxSignal(vector<double> vector)
{
	int i;
	maxValue = INT_MIN;
	for(i=0;i<(int)modifiedSignal.size();++i){
		if(vector[i]>maxValue){
			maxValue = vector[i];
		}//use for loop to get max
	}

	return maxValue;
}

double Signal::getMinSignal(vector<double> vector)
{
	int i;
	minValue = INT_MAX;
	for(i=0;i<(int)modifiedSignal.size();++i){
		if(vector[i]<minValue){
			minValue = vector[i];
		}//use for loop to get min
	}

	return minValue;
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
