#include <iostream>
using namespace std;



void merge(int* arr, int left, int mid, int right)
{

    int sub1=mid-left+1;
    int sub2=right-mid;

    int l[sub1],r[sub2]; // temp arrays
    int i,j,k;
    for(i=0;i<sub1;i++)
    {
        l[i]=arr[left+i];
    }                                                   // copy data to temp arrays
    for(j=0;j<sub2;j++)
    {
        r[j]=arr[mid+1+j];                
    }

    //ab wapas merge karna hoga l[],r[] ko
    // i index of sub1, j index of sub2 k main array ka index
    i=0; j=0; k=left; //init preset
    while(i<sub1 && j<sub2)
    {
        if(l[i] <= r[j]){
            arr[k]=l[i];        //chhota hai to left lar do
            i++;
        }
        else{
            arr[k]=r[j];        // nhi to right 
            j++;
        }
        k++;
    }
    while(i<sub1)
    {
        arr[k]=l[i];
        i++;            // left se waapas daalenge agar usme bacha hai to
        k++;
    }

    while(j<sub2)
    {
        arr[k]=r[j]; 
        j++; 
        k++;            // right ka agar usme hai to
    }
}

void mergeSort(int* arr,int l, int r)    // l begin, r end/high
{
    if(l<r)
    {
        int m= l+(r-l)/2;           

        mergeSort(arr,l,m);         // first aur second array ko sort kar liye
        mergeSort(arr,m+1,r);   

        merge(arr,l,m,r);
    }
}
int main()
{
    int n;
    cout<<"Enter size of array\n";
    cin>>n;
    int arr[n];
    
    for(int i=0;i<n;i++)
    {
    arr[i]=rand()%100;
    }
    //int arr[]={9,44,88,55,56,33};
    //int size= sizeof(arr) / sizeof(arr[0]);
    
    cout << "Given array is \n";

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }   

    mergeSort(arr, 0,n-1);

    cout << "\nSorted array is \n";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }   

    cout<<endl;
    return 0;        
}
