
#ifndef _GRAPH_HPP_ 
#define _GRAPH_HPP_

#include <fstream>
#include <list>
using namespace std;  

// ****************** EDGE ****************** //
template <typename T>
struct Edge {
  T from;
  T to;
  int dist;
  Edge(T f, T t, int d): from(f), to(t), dist(d) {
  }
  bool operator<(const Edge<T>& e) const;
  bool operator>(const Edge<T>& e) const;
  template<typename U>
  friend std::ostream& operator<<(std::ostream& out, const Edge<U>& e);
};

template <typename T>
bool Edge<T>::operator<(const Edge<T>& e) const {
  return dist < e.dist;
}

template <typename T>
bool Edge<T>::operator>(const Edge<T>& e) const
{   
  return dist > e.dist;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Edge<T>& e) {
  out << e.from << " -- " << e.to << " (" << e.dist << ")";
  return out;
}

// ****************** Node ****************** //
template <typename T>
struct Node
{
  T * info;
  list <Edge<T>> edge;
  bool addEdge(const Edge<T>& e);
  bool rmvEdge(const Edge<T>& e);
  bool containsEdge(const Edge<T>& e);
  void deleteNode();
};

template <typename T>
bool Node<T>::containsEdge(const Edge<T>& e)
{
  for (auto it = edge.begin(); it != edge.end(); it++)
  {
    if ((*it).from == e.from && (*it).to == e.to)
      return true;
  }
  return false;
}

template <typename T>
bool Node<T>::addEdge(const Edge<T>& e)
{
  if (containsEdge(e))
    return false;
  edge.push_back(e);
  return true;
}

template <typename T>
bool Node<T>::rmvEdge(const Edge<T>& e)
{
  for (auto it = edge.begin(); it != edge.end(); it++)
  {
    if ((*it).from == e.from && (*it).to == e.to)
    {
      edge.erase(it);
      return true;
    }
  }
  return false;
}

template <typename T>
void Node<T>::deleteNode()
{
  edge.clear();
}

// ****************** Graph ****************** //
template <typename T>
class Graph {
  bool isDirected;
  list<Node<T>> nodes;

public:
  Graph(bool isDirectedGraph = true);
  ~Graph();
  bool contains(const T& info) const;
  bool addVtx(const T& info);
  bool rmvVtx(const T& info);
  bool addEdg(const T& from, const T& to, int distance);
  bool rmvEdg(const T& from, const T& to);
  list<T> dfs(const T& info) const;
  list<T> bfs(const T& info) const;
  list<Edge<T>> mst();
  
  bool print2DotFile(const char *filename) const;
  list<T> dijkstra(const T& from, const T& to);
};

template <typename T>
Graph<T>::Graph(bool isDirectedGraph)
{
  isDirected = isDirectedGraph;
}

template <typename T>
Graph<T>::~Graph()
{
  for (auto it = nodes.begin(); it != nodes.end(); it++)
  {
    delete it->info;
  }
}

template<typename T>
bool Graph<T>::contains(const T& info) const
{
  for (auto it = nodes.begin(); it != nodes.end(); it++)
  {
    if (*it->info == info)
      return true;
  }
  return false;
}

template<typename T>
bool Graph<T>::addVtx(const T& info)
{
  if (contains(info))
    return false;
  Node<T> n;
  n.info = new T(info);
  nodes.push_back(n);
  return true;
}

template<typename T>
bool Graph<T>::rmvVtx(const T& info)
{
  if (!contains(info))
    return false;
    
  nodes.remove_if([&info](Node<T> n) { return *n.info == info; }); // remove node with info
  
  for (auto it = nodes.begin(); it != nodes.end(); it++) // remove edges from all node with info
  {
    it->rmvEdge(Edge<T>(*it->info, info, 0));
  }
    
  return true;
}

template<typename T>
bool Graph<T>::addEdg(const T& from, const T& to, int distance){
  if(!contains(from) || !contains(to))
    return false;
  
  if(isDirected){
    Edge<T> e(from, to, distance);
    for (auto it = nodes.begin(); it != nodes.end(); it++)
    {
      if(*it->info == from){
        if(it->containsEdge(e))
          return false;
        else{        
          it->addEdge(e);
          return true;
        }
      }
    }
  }
  else{
    Edge<T> e(from, to, distance);
    Edge<T> e2(to, from, distance);
    for (auto it = nodes.begin(); it != nodes.end(); it++)
    {
      if (*it->info == from){
        if(it->containsEdge(e))
          return false;
        else{        
          it->addEdge(e);
        }
      }
      if (*it->info == to){
        if(it->containsEdge(e2))
          return false;
        else{        
          it->addEdge(e2);
        }
      }
    }
  }

  return true;
}

template<typename T>
bool Graph<T>::rmvEdg(const T& from, const T& to){
  if(!contains(from) || !contains(to))
    return false;
  
  if(isDirected){
    Edge<T> e(from, to, 0);
    for (auto it = nodes.begin(); it != nodes.end(); it++)
    {
      if(*it->info == from){
        if(!it->containsEdge(e))
          return false;
        else{        
          it->rmvEdge(e);
          return true;
        }
      }
    }
  }
  else{
    Edge<T> e(from, to, 0);
    Edge<T> e2(to, from, 0);
    for (auto it = nodes.begin(); it != nodes.end(); it++)
    {
      if (*it->info == from){
        if(!it->containsEdge(e))
          return false;
        else{        
          it->rmvEdge(e);
        }
      }
      if (*it->info == to){
        if(!it->containsEdge(e2))
          return false;
        else{        
          it->rmvEdge(e2);
        }
      }
    }
  }

  return true;
}

template<typename T>
bool find(const T& info, list<T> l){
  for (auto it = l.begin(); it != l.end(); it++)
  {
    if (*it == info)
      return true;
  }
  return false;
}

template<typename T>
list<T> Graph<T>::dfs(const T& info) const
{
  list<T> res;
  if(!this->contains(info))
    return res;
  
  list<T> visited;
  list<T> toVisit;
  toVisit.push_back(info);
  while(!toVisit.empty()){
    T curr = toVisit.back();
    toVisit.pop_back();
    if(!find(curr, visited)){
      visited.push_back(curr);
      for(auto it = nodes.begin(); it != nodes.end(); it++){
        if(*it->info == curr){
          for(auto it2 = it->edge.begin(); it2 != it->edge.end(); it2++){
            if(!find(it2->to, visited))
              toVisit.push_back((*it2).to);
          }
        }
      }
    }
  }
  for(auto it = visited.begin(); it != visited.end(); it++){
    res.push_back(*it);
  }
  return res;
}

template<typename T>
list<T> Graph<T>::bfs(const T& info) const
{
  list<T> res;
  if(!this->contains(info))
    return res;
  
  list<T> visited;
  list<T> toVisit;
  toVisit.push_back(info);
  while(!toVisit.empty()){
    T curr = toVisit.front();
    toVisit.pop_front();
    if(!find(curr, visited)){
      visited.push_back(curr);
      for(auto it = nodes.begin(); it != nodes.end(); it++){
        if(*it->info == curr){
          for(auto it2 = it->edge.begin(); it2 != it->edge.end(); it2++){
            if(!find(it2->to, visited))
              toVisit.push_back((*it2).to);
          }
        }
      }
    }
  }
  for(auto it = visited.begin(); it != visited.end(); it++){
    res.push_back(*it);
  }
  return res;
}





template<typename T>
bool Graph<T>::print2DotFile(const char *filename) const
{
  ofstream out;
  try{
    out.open(filename);
    out << "digraph G {" << endl;
    if (isDirected)
    {
      for (auto it = nodes.begin(); it != nodes.end(); it++)
      {
        out << " " << *it->info << endl;
        for (auto it2 = it->edge.begin(); it2 != it->edge.end(); it2++)
        {
          out << "  ->  " << it2->to << " [" << it2->dist << "]" << endl;
        }
      }
      out << "}" << endl;
      out.close();
    }
    else
    {
      for (auto it = nodes.begin(); it != nodes.end(); it++)
      {
        out << " " << *it->info << endl;
        for (auto it2 = it->edge.begin(); it2 != it->edge.end(); it2++)
        {
          out << "  --  " << it2->to << " [" << it2->dist << "]"<< endl;
        }  
      }
      out << "}" << endl;
      out.close();
    }
    return true;
  }
  catch(...){
    return false;
  }
}

#endif
