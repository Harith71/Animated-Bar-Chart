/*
File: barchartanimate.h
Author: Harith Patel
Class: CS 251
Project 3 - Animated Bar Chart
Description: This file has a class which can be used to read in data from a file
             which is stored into barcharts. These barcharts are then able to be 
             animated in the console with colors to show the data.

Creative Component: Choose up to what date to show data upto.
        Usage: after running application.cpp when promted to enter date to enter
        enter the date. (i.e Enter date to show data upto(enter -1 to show all data): 1908)
        This would show all data for the data file upto 1908.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <map> 
#include <vector>
#include <unistd.h>
#include "myrandom.h" // used in autograder, do not remove
#include "barchart.h"
  
using namespace std;

//
// BarChartAnimate
//
class BarChartAnimate {
 private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, bars, to store a list of
    // BarCharts.  As a result, you must also keep track of the number of
    // elements stored (size) and the capacity of the array (capacity).
    // This IS dynamic array, so it must expand automatically, as needed.
    //
    BarChart* barcharts;  // pointer to a C-style array
    int size;
    int capacity;
    int color = 0;
    string title;
    string xlabel;
    string source;
    map<string, string> colorMap;

/* addColor
 *
 * this function gets the next availabe color in the color vector and sets the color
 * for the catergory passed into the function.
*/
    void addColor(string category) {
        // check if color for category isn't already added to the map 
        if(!colorMap.count(category)) {
            if(color == 7) 
                color = 0;
            colorMap.emplace(pair<string, string> (category, COLORS[color])); 
            color++;
        }
    }

/* parseFile
 *
 * this function reads data from a file and creates a barchart object with the
 * data.
*/
    void parseFile(BarChart& b, ifstream& file, int bars) {
        string line, name, value, category, frame;
        
        for(int i = 0; i < bars; i++) {
            getline(file, line);
            // get index of where the frame ends
            int commaPos = line.find(',');

            if (i == 0) 
                frame = line.substr(0, commaPos);
            
            // remove the frame from the string
            line.erase(0, commaPos + 1);
            // find the index of where the name ends
            commaPos = line.find(',');

            name = line.substr(0, commaPos);

            // remove name from the string
            line.erase(0, name.size() + 1);
            line.erase(0, line.find(',') + 1);

            // get value for the bar from the string
            value = line.substr(0, line.find(','));
            // remove value from the string
            line.erase(0, line.find(',') + 1);

            category = line;
            addColor(category);
            b.addBar(name, stoi(value), category);
        }
        b.setFrame(frame);
    }

/* resize
 *
 * this function doubles the memory to store barcharts when the arrays runs out 
 * of memory.
*/
    void resize() {
        capacity = capacity * 2;
        // new c array with double the memory
        BarChart* nBarcharts = new BarChart[capacity];

        // add all barcharts into the new c array
        for(int i = 0; i < size; i++) {
            nBarcharts[i] = barcharts[i];
        }

        delete[] barcharts;
        barcharts = nBarcharts;
    }

 public:

    // a parameterized constructor:
    // Like the ourvector, the barcharts C-array should be constructed here
    // with a capacity of 4.
/* BarChartAnimate
 *
 * this function creates a BarChartAnimate object with values passed in as parameters
 * and creates a dynamic c array to store barcharts.
*/
    BarChartAnimate(string title, string xlabel, string source) {
        capacity = 4;
        size = 0;
        barcharts = new BarChart[capacity];
        this->title = title;
        this->xlabel = xlabel;
        this->source = source;
    }

    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated
    // by BarChartAnimate.
    //
    virtual ~BarChartAnimate() {
        delete[] barcharts;
    }

    // addFrame:
    // adds a new BarChart to the BarChartAnimate object from the file stream.
    // if the barcharts has run out of space, double the capacity (see
    // ourvector.h for how to double the capacity).
    // See application.cpp and handout for pre and post conditions.
    void addFrame(ifstream &file) {
        string line;
        getline(file, line);   
        getline(file, line);

        if(line.size() == 0) return;

        // get number of bars to store in a barchart
        int bars = stoi(line);
        BarChart b(bars);
        // function to parse data from file and store in barchart
        parseFile(b, file, bars);

        if(size >= capacity)
            resize();

        barcharts[size] = b;
        size++;
    }

    // animate:
    // this function plays each frame stored in barcharts. 
	void animate(ostream &output, int top, int endIter) {
		unsigned int microsecond = 50000;
        int frames = endIter;

        if(endIter == -1)
            frames = size;
        
        if(endIter > size) {
            frames = size;
        }

        // iterate through all the barcharts
        for(int i = 0; i < frames; i++) {
            output << CLEARCONSOLE;
            output <<  BLACK << title << endl;
            output << BLACK << source << endl;
            barcharts[i].graph(output, colorMap, top);
            output << BLACK << xlabel << endl;
            output << BLACK << "Frame: " << barcharts[i].getFrame() << endl;
            // pause for 150,000 microseconds so the animation can be seen in the terminal
            usleep(3 * microsecond);
        }
	}

    // animate:
    // this function plays each frame stored in barcharts upto date specified by 
    // frame_date parameter.
    // creative component function
    void animate(ostream &output, int top, int endIter, string frame_date) {
		unsigned int microsecond = 50000;
        int found = 0;
        // find if barchart with date given is stored.
        for (int i = 0; i < size; i++) {
            if (barcharts[i].getFrame() == frame_date) {
                // get postion of the barchart
                endIter = i + 1;
                found = 1;
                break;
            }
        }

        if(found == 0) {
            cout << frame_date << " is not found" << endl;
            return;
        }

        int frames = endIter;

        // loop through barcharts upto the postion of the barchat with the date given.
        for(int i = 0; i < frames; i++) {
            output << CLEARCONSOLE;
            output <<  BLACK << title << endl;
            output << BLACK << source << endl;
            barcharts[i].graph(output, colorMap, top);
            output << BLACK << xlabel << endl;
            output << BLACK << "Frame: " << barcharts[i].getFrame() << endl;
            usleep(3 * microsecond);
        }
	}

    //
    // Public member function.
    // Returns the size of the BarChartAnimate object.
    //
    int getSize(){
        return size;  
    }

    //
    // Public member function.
    // Returns BarChart element in BarChartAnimate.
    // This gives public access to BarChart stored in the BarChartAnimate.
    // If i is out of bounds, throw an out_of_range error message:
    // "BarChartAnimate: i out of bounds"
    //
    BarChart& operator[](int i){
        if(i >= capacity) {
            throw out_of_range("BarCharts: Out of range");
        }
        
        return barcharts[i];
    }
};
