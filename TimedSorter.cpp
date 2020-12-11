
#include "TimedSorter.hpp"
#include <chrono>
#include <vector>

#include <utility>

template <class T>
TimedSorter<T>::TimedSorter(long timeoutMilliseconds) : timeout(timeoutMilliseconds){}

template <class T>
void TimedSorter<T>::startTimer(){
  startTime = std::chrono::steady_clock::now();
}

template <class T>
void TimedSorter<T>::checkpointTimer(){
  currentTime = std::chrono::steady_clock::now();
  deltaT = currentTime - startTime;
}

template <class T>
bool TimedSorter<T>::timeExpired(long timeoutMilliseconds){
  return std::chrono::duration_cast<std::chrono::milliseconds>(deltaT).count() > timeoutMilliseconds;
}

template <class T>
long TimedSorter<T>::timeInMilliseconds()
{
return std::chrono::duration_cast<std::chrono::milliseconds>(deltaT).count();
}

template <class T>
bool isSorted(T array[], size_t n){
  for(int k = 1; k < n; k++){
    if(array[k] < array[k - 1]) return false;
  }
  return true;
}

template <class T>
long TimedSorter<T>::BubbleSort(T *array, size_t arraySize){
  if(isSorted(array,arraySize)) return 0;
  startTimer();

  long comparisons = 0;

  for (size_t i=0; i<arraySize-1; i++)
  {

    checkpointTimer();

    if (timeExpired(timeout)){
      return -1;
    }

    for (size_t j=0; j<arraySize-i-1; j++)
    {
      comparisons++;
      if (array[j] > array[j+1]){
        std::swap(array[j], array[j+1]);
      }
    }
  }
return comparisons;
// return timeInMilliseconds;
}

template <class T>
long TimedSorter<T>::SelectionSort(T *array, size_t arraySize){
  if(isSorted(array,arraySize)) return 0;
  startTimer();

  long comparisons = 0;

  int min;
  for(int k = 0; k < arraySize - 1; k++){

    checkpointTimer();

    if (timeExpired(timeout)){
      return -1;
    }
    min = k;
    for(int i = k + 1; i < arraySize; i++){
      comparisons++;
      if(array[i] < array[min]){
        std::swap(array[min], array[i]);
      }
    }
  }
  return comparisons;
}

template <class T>
long TimedSorter<T>::InsertionSort(T *array, size_t arraySize){
  if(isSorted(array,arraySize)) return 0;
  startTimer();

  long comparisons = 0;

  int current;
  int previous;
  for(int k = 1; k < arraySize; k++){
    current = array[k];
    previous = k - 1;

    checkpointTimer();

    if (timeExpired(timeout)){
      return -1;
    }
    while(previous >= 0 && array[previous] > current){
      comparisons++;
      array[previous + 1] = array[previous];
      previous = previous - 1;
    }
    array[previous + 1] = current;
  }
  return comparisons;
}

template <class T>
void merge(T arr[], int l, int m, int r, long &c){
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;

  T L[n1], R[n2];

  for(i = 0; i < n1; i++){
    L[i] = arr[i + l];
  }
  for(j = 0; j < n2; j++){
    R[j] = arr[m + 1 + j];
  }
  i = 0;
  j = 0;
  k = l;

  while(i < n1 && j < n2){
    if(L[i] <= R[j]){
      c++;
      arr[k] = L[i];
      i++;
    }else{
      c++;
      arr[k] = R[j];
      j++;
    }
    k++;
  }
  while(i < n1){
    arr[k] = L[i];
    i++;
    k++;
  }
  while(j < n2){
    arr[k] = R[j];
    j++;
    k++;
  }
}

template <class T>
long TimedSorter<T>::MergeSort(T *array, int l, int r, long c){
  if(isSorted(array, r + 1)) return 0;
  startTimer();

  if(l < r){
    c++;
    int mid =  (int)(l + (r - l)/2);
    checkpointTimer();
    if (timeExpired(timeout)){
      return -1;
    }
    MergeSort(array, l, mid, c);
    MergeSort(array, mid + 1, r, c);
    merge(array, l, mid, r, c);
  }
  return c;
}

template <class T>
int partition(T A[], int l, int r, long &c){
  T pivot = A[l];
  int left = l, right = r;
  while(left < right){
    while(A[right] > pivot) right--;
    while((left < right) && (A[left] <= pivot)) left++;
    if(left < right){
      c++;
      std::swap(A[left], A[right]);
    }
  }
    std::swap(A[l],A[right]);
    return right;
}

template <class T>
long TimedSorter<T>::QuickSort(T *array, int l, int r, long c){
  if(isSorted(array, r + 1)) return 0;
  if(c == 0) startTimer();
  if(l < r){
    checkpointTimer();

    if (timeExpired(timeout)){
      return -1;
    }
    c++;
    int pivotIndex = partition(array, l, r, c);

    QuickSort(array, l, pivotIndex - 1, c);
    QuickSort(array, pivotIndex + 1, r, c);
  }
  return c;
}
template <class T>
T getMax(T array[], int n){
  int max = array[0];
  for(int i = 1; i < n; i++){
    if(array[i] > max){
      max = array[i];
    }
  }
  return max;
}

template <class T>
long countSort(T array[], int n, int exp){
  int output[n];
  int i, count[10] = {0};
  long result = 0;
  for (i = 0; i < n; i++){
    result++;
    count[ (array[i]/exp)%10 ]++;
  }

  for (i = 1; i < 10; i++){
    result++;
    count[i] += count[i - 1];
    }
  for (i = n - 1; i >= 0; i--){
    result++;
    output[count[ (array[i]/exp)%10 ] - 1] = array[i];
    count[(array[i]/exp)%10 ]--;
    }
  for (i = 0; i < n; i++){
    array[i] = output[i];
    }
  return result;
}


template <class T>
long TimedSorter<T>::RadixSort(T *array, size_t arraySize){
  if(isSorted(array, arraySize)) return 0;
  startTimer();
  int max = getMax(array, arraySize);
  long comparisons = 0;
  for(int exponent = 1; max/exponent > 0; exponent *= 10){
    checkpointTimer();
    if (timeExpired(timeout)){
      return -1;
    }
    comparisons += countSort(array, arraySize, exponent);
  }
  return comparisons;
}

template <class T>
long TimedSorter<T>::ShellSort(T *array, size_t arraySize){
  if(isSorted(array, arraySize)) return 0;
  startTimer();
  long comparisons = 0;

  for(int gap = arraySize/2; gap > 0; gap /=2){

    checkpointTimer();

    if (timeExpired(timeout)){
      return -1;
    }

    for(int i = gap; i < arraySize; i++){
      T temp = array[i];

      int j;
      for(j = i; j >= gap && array[j - gap] > temp; j -= gap ){
        comparisons++;
        array[j] = array[j - gap];
      }
      array[j] = temp;
    }
  }
  return comparisons;
}



// explicit template instantiations
template class TimedSorter<int>;






/*#include "TimedSorter.hpp"

#include <chrono>
#include <utility>


TeimedSorter<T>::

template <typename T>
long TimedSorter<T>::BubbleSort(){
  startTimer();

  long comparisons = 0;

  for(size_t i = 0; i<arraySize-1; i++){
    checkpointTimer();

    if(timeExpired(timeout)){
      return -1;
    }

    for(size_t j = 0; j < arraySize-i-1; j++){
      comparisons++;
      if(array[j] > array[j+1]){
        std::swap(array[j], array[j + 1]);
      }
    }
  }
  return comparisons;
}
*/
