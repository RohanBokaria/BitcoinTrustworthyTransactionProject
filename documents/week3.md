# Development Log (Date: 10/12/22 -- 10/18/22)

## Weekly Goals
Our weekly goals were to read in our dataset and set up our classes.
## Specific Tasks Completed (and by who)
Siddharth set up the repository and package structure as well as created the CMake files necessary to build our code. Together we met up and set up our header file and cpp file. We then were able to program a method to read in our data from the dataset. We tested that it worked in main and Siddharth committed the code.
## Problems Encountered 
One of the problems encountered was that the the data wasn't being read in unless the absolute path was being used. We fixed this by asking on discord and using the relative path from the main to the csv file and this worked. The next issue was that some of the algorithms that we suggested may not work in the case of a negative cycle. So we need to identify whether there are negative cycles within our graph and come up with a plan to tackle the issue if there is one.
## Plans for next week
The plans for next week are to find and implement an algorithim to determine negative cycles and decide what to do if there is one. Furthermore, we would like to come up with some test data for a graph that is easier to visualize to ensure our methods are working as they should.

## Optional: Questions for mentor
