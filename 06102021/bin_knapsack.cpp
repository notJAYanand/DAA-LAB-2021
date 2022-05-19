#include <iostream>
using namespace std;

//int count=0;
int max(int a, int b)
{
    return (a > b) ? a : b;
}

int bin_knapSack(int W, int wt[], int val[], int n)
{
    int i, w;
    int K[n+1][W+1];
    for (i = 0; i <= n; i++)
    {
        for (w = 0; w <= W; w++)
        {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (wt[i - 1] <= w)
                K[i][w] = max(K[i - 1][w - wt[i - 1]]+ val[i - 1] , K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        //count+=1; 
        }
        
    }
    return K[n][W];

}

int main()
{
    int wt[] = {5,3,4,2};
    int val[] = {60,50,70,30};    
    int W = 5;
    int n = sizeof(val) / sizeof(val[0]);

    cout <<"Maximised Profit= " <<bin_knapSack(W, wt, val, n)<<endl;
    //cout<<"Count: "<<count<<endl;
    return 0;
}