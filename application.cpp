/*
File: application.cpp
Author: Harith Patel
Class: CS 251
Project 3 - Animated Bar Chart
Description: This file opens a data file then stores the data. The data then is animated
			 in the console.

Creative Component: Choose up to what date to show data upto.
        Usage: after running application.cpp when promted to enter date to enter
        enter the date. (i.e Enter date to show data upto(enter -1 to show all data): 1908)
        This would show all data for the data file upto 1908.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "barchartanimate.h"
using namespace std;


int main() {
	
	string filename = "movies.txt";
	string date;
	ifstream inFile(filename);
	string title;
	getline(inFile, title);
	string xlabel;
	getline(inFile, xlabel);
	string source;
	getline(inFile, source);

	BarChartAnimate bca(title, xlabel, source);
	cout << "Enter date to show data upto(enter -1 to show all data): ";
	cin >> date;
	
	// loop until end of the file is reached
	while (!inFile.eof()) {
		bca.addFrame(inFile);
	}

	if(date == "-1")
		bca.animate(cout, 12, -1);
	else
		bca.animate(cout, 12, 1, date);
	
    return 0;
}
