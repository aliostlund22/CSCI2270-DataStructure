//Alison Ostlund
//I added a counter in each function that would iterate each time a loop ran.
//With smaller arrays quick sort or insertion sort will be the fastest, due to the least iterations.
//With larger arrays insertion sort is significantly faster.

#include <iostream>
#include <stdlib.h>
using namespace std;

int quickSortCount = 0;
int selectSortCount = 0;
int insertSortCount = 0;
int bubbleSortCount = 0;
void quickSort(int arr[], int left, int right) {
    int i = left, j = right;
    int tmp;
    int pivot = arr[(left + right) / 2];

    /* partition */
    while (i <= j) {
        quickSortCount++;
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    };

    /* recursion */
    if (left < j)
        quickSort(arr, left, j);
    if (i < right)
        quickSort(arr, i, right);
}

void selectSort(int arr[], int n) {

  int index_min_value;
  int temp;
  for (int i=0; i<n-1; i++) {
  // outer loop tracks the sorted portion of the list
    index_min_value = i; //set index_min_value to the current index of array
    for (int j=i+1; j < n; j++) // inner loop finds the next smallest value
    {
      selectSortCount++;
      if (arr[j] < arr[index_min_value])
        index_min_value = j;

    }
    if (index_min_value != i) {
      temp = arr[i];
      arr[i] = arr[index_min_value];
      arr[index_min_value] = temp;
    }
  }
}

void insertionSort (int arr[], int length) {
  int j, temp;
  for (int i = 0; i < length; i++)  {
      j = i;
      while (j > 0 && arr[j] < arr[j-1])
      { // move elements over until find the position for next element
        insertSortCount++;
        temp = arr[j];
        arr[j] = arr[j-1];
        arr[j-1] = temp;
        j--;
      }
  }
}

void swap(int *xp, int *yp) {
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}
void bubbleSort(int arr[], int n) {

  int i, j;
  for (i = 0; i < n-1; i++) {// Last i elements are already in place
    for (j = 0; j < n-i-1; j++){
      bubbleSortCount++;
      if (arr[j] > arr[j+1]){
        swap(&arr[j], &arr[j+1]);
      }
    }
  }
}


void printList(int arr[], int length){
  for (int i = 0; i<length; i++){
    cout<<arr[i]<<" ";
  }
  cout<<endl;
}

int main(){
  //HINT: You should place a counter into each algorithm to see how many time each of them run. Then you can compare them easier.
  //You should use the given print statements for better organization.

  int myArray1[] = {12, 13, 5, 4, 7, 18, 9 };
  int myArray2[] = {12, 13, 5, 4, 7, 18, 9 };
  int myArray3[] = {12, 13, 5, 4, 7, 18, 9 };
  int myArray4[] = {12, 13, 5, 4, 7, 18, 9 };

  cout << endl;
  cout << " ======== Small array ======= " << endl;
  cout << endl;

  cout<<"My original small array is: "<<endl;
  printList(myArray1,7);

  //selectSort
  selectSort(myArray1,7);
  cout<<"When ordered with selectSort, after "<<selectSortCount<<" operations the result is: "<<endl;
  printList(myArray1,7);

  //insertionSort
  insertionSort(myArray2,7);
  cout<<"When ordered with insertionSort, after "<<insertSortCount<<" operations the result is: "<<endl;
  printList(myArray2,7);

  //bubbleSort
  bubbleSort(myArray3,7);
  cout<<"When ordered with bubbleSort, after "<<bubbleSortCount<<" operations the result is: "<<endl;
  printList(myArray3,7);

  //quickSort
  quickSort(myArray4,0,6);
  cout<<"When ordered with quickSort, after "<<quickSortCount<<" operations the result is: "<<endl;
  printList(myArray4,7);

  cout << endl;
  cout << " ======== Large array ======= " << endl;
  cout << endl;

  int YUGE[1000];
  for(int i = 0; i < 1000; i++){
    YUGE[i] = rand();
  }

  //Begin with large arrays; test with each case and use the same print statements.
  selectSortCount, bubbleSortCount, insertSortCount, quickSortCount = 0;
  //selectSort
  selectSort(YUGE,1000);
  cout<<"When ordered with selectSort, after "<<selectSortCount<<" operations it is sorted."<<endl;
  //insertionSort
  insertionSort(YUGE,1000);
  cout<<"When ordered with insertionSort, after "<<insertSortCount<<" operations it is sorted"<<endl;

  //bubbleSort
  bubbleSort(YUGE,1000);
  cout<<"When ordered with bubbleSort, after "<<bubbleSortCount<<" operations it is sorted"<<endl;

  //quickSort
  quickSort(YUGE,0,999);
  cout<<"When ordered with quickSort, after "<<quickSortCount<<" operations it is sorted"<<endl;




  return 0;
}
