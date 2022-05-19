#include <iostream>
using namespace std;

int main()
{
    int n;
    cin>>n;
    int t=n/2;
    if(n%2==0 && t%2==0 || t==3 || t==4)
    {
        cout<<"YES"<<endl;
    }
    else
    cout<<"NO"<<endl;
}