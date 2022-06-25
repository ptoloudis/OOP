#include <iostream>

#include "Graph.hpp"
using namespace std;

bool Edge::operator<(const Edge<T>& e) const
{    
    if (this.dist < e.dist)
        return true;
    else
        return false;   
}

bool Edge::operator>(const Edge<T>& e) const
{   
    if (this.dist > e.dist)
        return true;
    else
        return false;
}

Graph::Graph(bool isDirectedGraph = true)
{
    this.isDirected = isDirectedGraph;
}

Graph::~Graph()
{
    nodes::iterator it;
    for (it = g.begin(); it != g.end(); ++it)
        delete it.info;
}