#include <iostream>
using namespace std;

int main()
{

    int n = 6;
    // cin >> n;
    // int start[n], finish[n];
    int start[] = {1, 3, 0, 5, 8, 5};
    int finish[] = {2, 4, 6, 7, 9, 9};
    // for (int i = 0; i < n; i++)
    // {
    //     cin >> start[i];
    //     cin >> finish[i];
    // }
    int j;
    j = 0;
    cout << "Selected Activities:" << endl;
    cout<<"Activity: "<<0<<endl;
    int count = 0;
    for (int i = 1; i < n; i++)
    {
        if (start[i] >= finish[j])
        {
            count++;
            cout << "Activity: " << i << endl;
            j = i;
        }
    }
    cout << count+1 << endl;
}