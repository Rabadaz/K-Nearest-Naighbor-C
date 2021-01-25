# K-Nearest-Neighbor C Implementation

This Project Implements the KNN Algorithm in C

## The KNN Algorithm
  Simple Lazy-Learing Algorithm to get going with Machine Learning
### How does it work
  1. Claculate all the Euclidean Distances to the Trained Points
  2. Sort them by the Distance Asccending
  3. Filter out the smallest N Values

### Euclidean Distance
  Is used to Calulate the Distance between 2 Points in a Multidimensional Room:
 
    √((p1_1 - p2_1)^2 + (p1_2 - p2_2)^2 + ... + (p1_x - p2_x)^2))


## How To use it?

  Build the knn Binary:

    make build

  Run the knn:

      make run
  
  Clean the Project:

    make clean

  1. To Specify the DataSet, you have to Change the "convertToIrisPoint" Function to match your File Format
  2. Change the trainDataSize Var to specify how many Lines should be loaded
  3. Change the classes Array to change the meaning of the Classes
  4. Change the "toClassify" Array to set the Point that should be classified
  5. Change the K to Specify how many of the Naighbours should be looked at


