
#include <time.h>
#include <iostream>
#include <fstream>

#include "TimedSorter.cpp"

int main(){
    std::cout << "Currently writing to output.csv" << std::endl;
  std::ofstream myfile;
  myfile.open("output.csv");
  for(int k = 0; k < 7; k++){
    if(k == 0) myfile << "Bubble Sort: ";
    else if(k == 1) myfile << "Insertion Sort: ";
    else if(k == 2) myfile << "Selection Sort: ";
    else if(k == 3) myfile << "Quick Sort: ";
    else if(k == 4) myfile << "Merge Sort: ";
    else if(k == 5) myfile << "Shell Sort: ";
    else myfile << "Radix Sort: ";

    for(size_t arraySize = 128; arraySize < 9000000; arraySize = arraySize * 2){

      TimedSorter<int> *mySorter = new TimedSorter<int>(arraySize);

      int* myArray = new int[arraySize];

      std::srand(time(NULL));
      for(int i = 0; i<arraySize; i++){
        //randomize array here
        int number = std::rand();
        myArray[i] = number;
      }
      long measurement;
      if(k == 0) measurement = mySorter->BubbleSort(myArray, arraySize);
      else if(k == 1) measurement = mySorter->InsertionSort(myArray, arraySize);
      else if(k == 2) measurement = mySorter->SelectionSort(myArray, arraySize);
      if(k == 3) measurement = mySorter->QuickSort(myArray, 0, arraySize - 1, 0);
      else if(k == 4) measurement = mySorter->MergeSort(myArray, 0, arraySize - 1, 0);
      else if(k == 5) measurement = mySorter->ShellSort(myArray, arraySize);
      else measurement = mySorter->RadixSort(myArray, arraySize);

      myfile << measurement << ", " << std::endl;

      if(measurement < 0){
        break;
      }

      delete mySorter;
      delete[] myArray;
    }
    myfile << "\n";
  }
  return 0;
}
