#include <iostream>
using namespace std; 

void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 


int partition (int arr[], int low, int high)
{ 
    int pivot = arr[high];
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far
    for (int j = low; j<=high-1; j++) 
    { 
        if (arr[j] < pivot) // If curr element< pivot 
        { 
            i++; // increment index of smaller element 
            swap(&arr[i], &arr[j]);   
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 


void quickSort(int arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        
        int pi = partition(arr, low, high); /* pi is partitioning index, arr[pi] is now at right place */
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); //sorting both parts on left of pivot and right recursively
    } 
} 

void printArray(int arr[], int size) 
{ 
    int i; 
    for (i=0; i<size; i++){ 
        cout << arr[i] << " ";
    } 
    cout << endl; 
} 


int main() 
{
    int n;
    int arr[n];
    cout<<"enter no. of elemants"<<endl;
    cin>>n;
    for(int i=0; i<n; i++) 
    {
        arr[i]=rand()%100;
    }
    cout<<"Given Array: "<<endl;
    for (int i=0; i<n; i++)
    {
        cout << arr[i] << " ";
    }    
    quickSort(arr, 0, n - 1); 
    cout << "\nSorted array: \n";   
    printArray(arr, n); 
    return 0; 
}