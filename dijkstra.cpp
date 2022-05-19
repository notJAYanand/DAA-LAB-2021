#include <bits/stdc++.h>
using namespace std;

const int inf = 1e7;

int main()
{
    int count=0;
    int n,m;

    cin>>n>>m;
    vector<int> dist(n+1,inf);
    vector<vector<pair<int,int>>> graph(n+1);
    
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;

        // u=rand()%10;
        // v=rand()%10;
        // w=rand()%10;
        graph[u].push_back({v,w});
        graph[v].push_back({u,w});


    }
    // for(int i=0;i<m;i++){
    //     cout<<u<<" "<<v<<" "<<w<<endl;
    // }    
    int source = 0;
    cin>>source;

    dist[source]=0;
    set<pair<int,int>> s;
    s.insert({0,source});
    //{wt,vertex}
    while(!s.empty())
    {
        auto x=*(s.begin());
        s.erase(x);
        for(auto it: graph[x.second])
        {
            if(dist[it.first]>dist[x.second]+it.second)
            {
                s.erase({dist[it.first],it.first});
                dist[it.first]=dist[x.second]+it.second;
                s.insert({dist[it.first],it.first});
                //count++;
            }
            //count++;
        }
        count++;

    }
    for(int i=1;i<=n;i++)
    {
        if(dist[i]<inf)
        {
            cout<<dist[i]<<" ";
        }
    }
    cout<<endl;
    cout<<"count= "<<count;
    
}