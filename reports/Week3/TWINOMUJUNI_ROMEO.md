AXIS MODULE

Project: C++ Data Visualization Library  
Module: Axis  
Member: TWINOMUJUNI ROMEO

Work Completed

I started working on the Axis module of the data visualization library.

The purpose of the Axis module is to control how values are placed on a graph and how the graph scale is calculated.

In axis.hpp, I created the Axis class and started defining the data that the class will store.

Currently, the class contains:

double min_value;
double max_value;

These variables are intended to store the lowest and highest values used on an axis.

I also identified the basic scale idea using:

Scale = (Highest Value - Lowest Value) / Number of divisions

This will later be used when calculating the spacing between axis values or tick marks.

I also created the corresponding axis.cpp file and prepared it for the implementation of the scaling function.

Current Progress

At the moment, axis.hpp contains the basic class structure, while axis.cpp has been created but the actual scaling logic has not yet been implemented.

The next step is to define the necessary public functions in axis.hpp and then implement those functions in axis.cpp.

Next Work

I plan to add functions that will:

set the minimum and maximum axis values

calculate the scale

determine divisions/tick values

later help map data values to positions on the graph

I will then test the Axis module using sample values to confirm that the calculated scale is correct.

Challenge

One challenge encountered was understanding how to separate the responsibilities of axis.hpp and axis.cpp.

I now understand that:

axis.hpp → defines what the Axis class contains and what functions are available

axis.cpp → contains the actual implementation of those functions

I am currently continuing with the scaling function implementation.