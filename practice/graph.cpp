#include<iostream>
#include<vector>
#include<list>
#include<algorithm>
using namespace std;

class Edge
{
    public:
    int DestinationVertexID;
    int weight;

    Edge(){}
    Edge(int destID,int w)
    {
        DestinationVertexID = destID;
        weight = w;
    }
    void setEdgeValues(int destID,int w)
    {
        DestinationVertexID = destID;
        weight = w;        
    }
    void setWeight(int w)
    {
        weight = w;
    }
    int getVertexID()
    {
        return DestinationVertexID;
    }
    int getWeight(){
        return weight;
    }

};


class Vertex{
    public:
    int state_id;
    string state_name;
    list<Edge>Edgelist;

    Vertex(){}
    Vertex(int id,string sname)
    {
        state_id = id;
        state_name=sname;
    }

    int getStateID(){
        return state_id;
    }
    string getStateName()
    {
        return state_name;
    }
    void setID(int id)
    {
        state_id= id;

    }
    void setStateName(string sname)
    {
        state_name= sname;
    }
    list<Edge> getEdgelist(){
        return Edgelist;
    }

};

class Graph{
    public:
    vector<Vertex> Vertices;

    //all operations
};

int main()
{
    
    //edge e1
    //e1.setValue()
}