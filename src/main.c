#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLASSIFICATION_COUNT 3

typedef struct{
  float * point;
  int classification;
} ClassifiedPoint;

typedef struct{
  int classification;
  double distance;
} ClassifiedDistance;


double eukl_distance(int dimensions,float* point1, float* point2){
  double temp = 0;
  for(int i = 0; i < dimensions; i++){
     temp += pow(point1[i] - point2[i], 2.0);
  }
  return sqrt(temp);
}

int compareCdistances(const void* a, const void* b){
  ClassifiedDistance d1 = *((ClassifiedDistance*) a);
  ClassifiedDistance d2 = *((ClassifiedDistance*) b);

  if(d1.distance == d2.distance) return 0;
  else if(d1.distance < d2.distance) return -1;
  else return 1;
}


void sortCD(ClassifiedDistance* data, int size){
  qsort(data, size, sizeof(ClassifiedDistance), compareCdistances);
}


ClassifiedDistance* classify(int dimensions, const ClassifiedPoint** trainedData, int trainedSize, float* toClassify){


  ClassifiedDistance * distances = malloc(sizeof(ClassifiedDistance) * trainedSize);
  for (int i = 0; i < trainedSize; i++)
  {
    ClassifiedDistance distance;
    distance.classification = (*trainedData)[i].classification;

    distance.distance = eukl_distance(dimensions, (*trainedData)[i].point, toClassify);
    distances[i] = distance;
  }
  
  sortCD(distances, trainedSize);

  return distances;
}





ClassifiedPoint* convertToIrisPoint(char* inp){
  ClassifiedPoint* point = malloc(sizeof(ClassifiedPoint));
  float * pos = malloc(4 * sizeof(float));
  pos[0] = strtof(strtok(inp, ","),NULL);
  pos[1] = strtof(strtok(NULL, ","),NULL);
  pos[2] = strtof(strtok(NULL, ","),NULL);
  pos[3] = strtof(strtok(NULL, ","),NULL);
  
  //TODO: Could go Wrong
  point->point = pos;

  
  point->classification = atoi(strtok(NULL, ","));
  
  return point;
}



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
}





int main(int argc, char const *argv[])
{

  int trainDataSize = 140;
  
  float toClassify[4] = {5.7f,3.0f,5.2f,1.6f}; 
  
  ClassifiedPoint *  trainData = malloc(sizeof(ClassifiedPoint) * trainDataSize);
  
  readTrainingData("iris.csv", trainDataSize, trainData);

  ClassifiedDistance * distances = classify(4, &trainData, trainDataSize, toClassify);


  char* colors[] = {
    "Iris-setosa",
    "Iris-versicolor",
    "Iris-virginica"
  };



  for (size_t i = 0; i < 3; i++)
  {
        printf("Result: %f %s\n",distances[i].distance, colors[distances[i].classification]);
  }
  



  return 0;
}










