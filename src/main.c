#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>



typedef struct{
  float * point;
  int classification;
} ClassifiedPoint;

typedef struct{
  int classification;
  double distance;
} ClassifiedDistance;

/**
 * Calculating the Euclidean Distance
 * 
 * √((p1_1 - p2_1)^2 + (p1_2 - p2_2)^2 + ... + (p1_x - p2_x)^2))
 * 
 * Input Parameters: 
 *  dimensions: Count of Dimensions the Euklid should work
 *  point1: Array of float coordinates
 *  point2: Array of float coordinates
 * 
 *   * 
 */
double eukl_distance(int dimensions,float* point1, float* point2){
  double temp = 0;
  for(int i = 0; i < dimensions; i++){
     temp += pow(point1[i] - point2[i], 2.0);
  }
  return sqrt(temp);
}

/**
 * Comparator Function to Compare 2 Classified Distances by their Distance
 */
int compareCdistances(const void* a, const void* b){
  ClassifiedDistance d1 = *((ClassifiedDistance*) a);
  ClassifiedDistance d2 = *((ClassifiedDistance*) b);

  if(d1.distance == d2.distance) return 0;
  else if(d1.distance < d2.distance) return -1;
  else return 1;
}

/**
 * Sorting Function to Sort Array of ClassifiedDistances
 */
void sortCD(ClassifiedDistance* data, int size){
  qsort(data, size, sizeof(ClassifiedDistance), compareCdistances);
}

/**
 * Classification function K-Nearest-Neighbour
 * 
 * Input Parameters:
 *  dimensions: count of Dimensions the Knn works with
 *  trainedData: ClassifiedPoint Array of the Trained Data
 *  trainedSize: Size of the Trained Array
 *  toClassify: Float Array that represents the Point to be classified
 */

ClassifiedDistance* classify(int dimensions, const ClassifiedPoint* trainedData, int trainedSize, float* toClassify){


  ClassifiedDistance * distances = malloc(sizeof(ClassifiedDistance) * trainedSize);

  //Calculating the Euklid distance to every trained Datapoint
  for (int i = 0; i < trainedSize; i++)
  {
    ClassifiedDistance distance;
    distance.classification = (trainedData)[i].classification;
    distance.distance = eukl_distance(dimensions, (trainedData)[i].point, toClassify);
    distances[i] = distance;
  }

  //Sort the Calculated Distances
  sortCD(distances, trainedSize);

  return distances;
}


/**
 * Convert Line of CSV File to Classified Point
 * (Works with the Iris.csv format)
 * 
 * Iris.csv:  petalLength,petalWidth,sepalLength,sepalWidth,target(in int)
 * 
 * Input Parameters:
 *  inp: char* buffer wirh line of the file
 */
ClassifiedPoint* convertToIrisPoint(char* inp){
  ClassifiedPoint* point = malloc(sizeof(ClassifiedPoint));
  float * pos = malloc(4 * sizeof(float));
  //Petal Length
  pos[0] = strtof(strtok(inp, ","),NULL);
  //Petal Width
  pos[1] = strtof(strtok(NULL, ","),NULL);
  //Septal Length
  pos[2] = strtof(strtok(NULL, ","),NULL);
  //Septal Width
  pos[3] = strtof(strtok(NULL, ","),NULL);
  
  point->point = pos;
  //Target
  point->classification = atoi(strtok(NULL, ","));
  
  return point;
}


/**
 * Reading Data from the specified File
 * 
 * Input Parameter:
 *  filename: Path to File
 *  numOfLines: Number of Lines to Read
 *  ret: Array the Points schould be saved to
 */
void readTrainingData(char* filename, int numOfLines, ClassifiedPoint* ret){
  FILE* fileptr;
  
  fileptr = fopen(filename, "r");
  
  int bufferLen = 255;
  char buffer[bufferLen];
  
  int i = 0;
  while(fgets(buffer, bufferLen, fileptr) != NULL&&  i < numOfLines){
    ClassifiedPoint* p =  convertToIrisPoint(buffer);
    ret[i] = *p; 
    i++;
  }
  fclose(fileptr);
 
}





int main(int argc, char const *argv[])
{
  //Size of the Dataset to Train
  int trainDataSize = 149;
  //Definition of the Meaning of Classes
  char* classes[] = {
    /*CLASS 0:*/ "Iris-setosa",
    /*CLASS 1:*/ "Iris-versicolor",
    /*CLASS 2:*/ "Iris-virginica"
  };

  //Point that should be Classified
  float toClassify[4] = {5.7f,3.0f,5.2f,1.6f};
  //The K of KNN
  int K = 3;
  
  //Allocate Array to Store trained Data
  ClassifiedPoint *  trainData = malloc(sizeof(ClassifiedPoint) * trainDataSize);
  //Read the Trained Data from CSV- File and Store it into TrainData Array
  readTrainingData("iris.csv", trainDataSize, trainData);
  //Classify the Point you want to know of
  ClassifiedDistance * distances = classify(4, trainData, trainDataSize, toClassify);

  //Print the smallest K Results and Display them.
  for (size_t i = 0; i < K; i++)
  {
    printf("Result: %f %s\n",distances[i].distance, classes[distances[i].classification]);
  }
  return errno;
}