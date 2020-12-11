
#include <chrono>

template <class T>
class TimedSorter{

private:

  std::chrono::steady_clock::time_point startTime;
  std::chrono::steady_clock::time_point currentTime;
  std::chrono::steady_clock::duration deltaT;

  void startTimer();
  void checkpointTimer();
  bool timeExpired(long timeoutMilliseconds);
  long timeInMilliseconds();

  long timeout;






public:
  TimedSorter(long timeoutMilliseconds);

  // all sorts return -1 if timeout
  //positive number of millis otherwise

  long BubbleSort(T *array, size_t arraySize);

  long InsertionSort(T *array, size_t arraySize);

  long SelectionSort(T *array, size_t arraySize);

  long MergeSort(T *array, int l, int r, long c);

  long QuickSort(T *array, int l, int r, long c);

  long RadixSort(T *array, size_t arraySize);

  long ShellSort(T *array, size_t arraySize);
};
