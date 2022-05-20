/*
File: barchart.h
Author: Harith Patel
Class: CS 251
Project 3 - Animated Bar Chart
Description: This file has a class which is used to create a barchart
             in which bar objects are added into.

Creative Component: Choose up to what date to show data upto.
        Usage: after running application.cpp when promted to enter date to enter
        enter the date. (i.e Enter date to show data upto(enter -1 to show all data): 1908)
        This would show all data for the data file upto 1908.
*/

#include <iostream>
#include <algorithm>
#include <map>
#include "myrandom.h" // used in autograder, do not remove
#include "bar.h"

using namespace std;

// Constants used for bar chart animation.  You will primarily
// use these in barchartanimate.h, but you might find some useful here.
const string BOX = "\u29C8";
const string CLEARCONSOLE = "\033[2J";

// Color codes for Mimir (light mode)

const string RED("\033[1;36m");
const string PURPLE("\033[1;32m");
const string BLUE("\033[1;33m");
const string CYAN("\033[1;31m");
const string GREEN("\033[1;35m");
const string GOLD("\033[1;34m");
const string BLACK("\033[1;37m");
const string RESET("\033[0m");
const vector<string> COLORS = {RED, PURPLE, BLUE, CYAN, GREEN, GOLD, BLACK};

// Color codes for Replit (dark mode terminal)
/*
const string CYAN("\033[1;36m");
const string GREEN("\033[1;32m");
const string GOLD("\033[1;33m");
const string RED("\033[1;31m");
const string PURPLE("\033[1;35m");
const string BLUE("\033[1;34m");
const string WHITE("\033[1;37m");
const string RESET("\033[0m");
const vector<string> COLORS = {CYAN, GREEN, GOLD, RED, PURPLE, BLUE, WHITE};
*/

//
// BarChart
//
class BarChart {
 private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, bars, to store a list of
    // Bars.  As a result, you must also keep track of the number of elements
    // stored (size) and the capacity of the array (capacity).  This is not a
    // dynamic array, so it does not expand.
    //
    Bar* bars;  // pointer to a C-style array
    int capacity;
    int size;
    string bcFrame;

 public:
    // default constructor:
/* barChart
 *
 * this function creates a barchart object with default values
*/
    BarChart() {
        capacity = 0;
        size = 0;
        bcFrame = "";
        bars = nullptr;  
    }

    // parameterized constructor:
    // Parameter passed in determines memory allocated for bars.
/* barChart
 *
 * this function creates a barchart object that can store n bars;
*/
    BarChart(int n) {
        bars = new Bar[n];
        capacity = n;
        size = 0;
        bcFrame = "";
    }

    //
    // copy constructor:
    //
    // Called automatically by C++ to create an BarChart that contains
    // a copy of an existing BarChart.  Example: this occurs when passing
    // BarChart as a parameter by value.
    //
/* barChart
 *
 * this function creates a barchart object with value from another barchart object.
*/
    BarChart(const BarChart& other) {
        capacity = other.capacity;
        size = other.size;
        bars = new Bar[other.capacity];
        bcFrame = other.bcFrame;
        
        // get values of all other barchar and set them equal to it.
        for (int i = 0; i < other.size; i++) {
            bars[i] = other.bars[i];
        }
    }
    //
    // copy operator=
    //
    // Called when you assign one BarChart into another, i.e. this = other;
    //
/* barChart
 *
 * this function sets the values of the bartchart to values of the other barchart.
*/
    BarChart& operator=(const BarChart& other) {
        if (this == &other)
            return *this;

        delete[] bars;
        capacity = other.capacity;
        size = other.size;
        bars = new Bar[other.capacity];
        bcFrame = other.bcFrame;

        // get values of all other barchar and set them equal to it.
        for (int i = 0; i < other.size; i++) {
            bars[i] = other.bars[i];
        }
        return *this;
    }

    // clear
    // frees memory and resets all private member variables to default values.
/* clear
 *
 * this function deallocates the memory used to store bars and sets everything to 
 * default values.
*/
    void clear() {
        delete[] bars;
        bars = nullptr;
        size = 0;
        capacity = 0;
        bcFrame = "";
    }

    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated by the
    // BarChart.
    //
/* barChart
 *
 * this destructor deallocates the memory used to store bars and sets everything to 
 * default values.
*/
    virtual ~BarChart() {
        delete[] bars;  
    }
    
/* setFrame
 *
 * this function sets the value of the frame to the string parameter.
*/
    void setFrame(string frame) {
        bcFrame = frame;
    }
    
    // getFrame()
    // Returns the frame of the BarChart oboject.
    string getFrame() {
        return bcFrame;
    }

    // addBar
    // adds a Bar to the BarChart.
    // returns true if successful
    // returns false if there is not room
    bool addBar(string name, int value, string category) {
        if(size >= capacity) return false;
        Bar b = Bar(name, value, category);
        bars[size] = b;
        size++;
        return true;
    }
    
    // getSize()
    // Returns the size (number of bars) of the BarChart object.
    int getSize() {
        return size;
    }
    
    // operator[]
    // Returns Bar element in BarChart.
    // This gives public access to Bars stored in the Barchart.
    // If i is out of bounds, throw an out_of_range error message:
    // "BarChart: i out of bounds"
    Bar& operator[](int i) {
        if(i >= capacity) {
            throw out_of_range("Out of range");
        }
        return bars[i];
    }
    
    // dump
    // Used for printing the BarChart object.
    // Recommended for debugging purposes.  output is any stream (cout,
    // file stream, or string stream).
    void dump(ostream &output) {
        // sort bars into descending order.
        sort(bars, bars + size, greater<Bar>());
        output << "frame: " << bcFrame << endl;

        // iterate through all the bars
        for(int i = 0; i < size; i++) {
            string name = bars[i].getName();
            int value = bars[i].getValue();
            string category = bars[i].getCategory();
            output << name << " " << value << " " << category << endl;
        }
    }
    
    // graph
    // Used for printing out the bar.
    // output is any stream (cout, file stream, string stream)
    // colorMap maps category -> color
    // top is number of bars you'd like plotted on each frame (top 10? top 12?)
    void graph(ostream &output, map<string, string> &colorMap, int top) {
    	int lenMax = 60;  // this is number of BOXs that should be printed
                          // for the top bar (max value)
        string color;
        double barLength;
        
        // sort bars into descending order.
        sort(bars, bars + size, greater<Bar>());

        if(size < top || top <= 0) {
            top = size;
        }

        // iterate through all the bars
        for(int i = 0; i < top; i++) {
            string barstr = "";
            Bar b = bars[i];
            string category = b.getCategory();
            // calculate how many boxes to print for the bar
            // based on value compared to the largest bar value
            barLength = ((double)b.getValue() / bars[0].getValue()) * lenMax;
            int bl = (int) barLength;
            color = BLACK;

            // check if there is a color for the category in the map
            if(colorMap.count(category)) {
                color = colorMap.find(category)->second;
            }

            // add boxes to string based on the length for the bar.
            for(int i = 0; i < bl; i++) {
                barstr += BOX;
            }
            output << color << barstr << " " << b.getName() << " " << b.getValue() << endl;
        } 
    }
};
