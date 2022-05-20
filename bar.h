/*
File: bar.h
Author: Harith Patel
Class: CS 251
Project 3 - Animated Bar Chart
Description: This file has a class which can be used to store
             data for a bar and create a bar.

Creative Component: Choose up to what date to show data upto.
        Usage: after running application.cpp when promted to enter date to enter
        enter the date. (i.e Enter date to show data upto(enter -1 to show all data): 1908)
        This would show all data for the data file upto 1908.
*/

#include <iostream>
#include <string>
#include "myrandom.h" // used in autograder, do not remove
using namespace std;

//
// Bar
//
class Bar {
 private:
    // Private member variables for a Bar object
    string bName;
    string bCategory;
    int bValue;

 public:

    // default constructor:
/* bar
 *
 * this function creates a bar object with default values
*/
    Bar() {
        bName = "";
        bCategory = "";
        bValue = 0;
    }

    //
    // a second constructor:
    //
    // Parameter passed in constructor Bar object.
    //
/* bar
 *
 * this function creates a bar object with values given as parameters
*/
    Bar(string name, int value, string category) {
        bName = name;
        bCategory = category;
        bValue = value;
    }

    // destructor:
    virtual ~Bar() {

    }

/* getName
 *
 * this function returns the name
*/
        string getName() const {
        return bName;
	}

/* getValue
 *
 * this function returns the value
*/
	int getValue() const {
        return bValue;
	}

/* getCategory
 *
 * this function returns the category
*/
	string getCategory() const {
        return bCategory; 
	}

	// operators
// this operator check if the value of the bar is less than the other bar.
	bool operator<(const Bar &other) const {
        return (bValue < other.getValue());
	}

// this operator checks if the value of the bar is less than or equal to the other bar.
	bool operator<=(const Bar &other) const {
        return (bValue <= other.getValue());
	}

// this operator check if the value of the bar is greater than the other bar.
	bool operator>(const Bar &other) const {
        return (bValue > other.getValue());
	}

// this operator checks if the value of the bar is greater than or equal to the other bar.
	bool operator>=(const Bar &other) const {
        return (bValue >= other.getValue());
	}
};

