
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
  bool contains(const T& info);
  bool addVtx(const T& info);
  bool rmvVtx(const T& info);
  bool addEdg(const T& from, const T& to, int distance);
  bool rmvEdg(const T& from, const T& to);
  list<T> dfs(const T& info) const;
  list<T> bfs(const T& info) const;
  list<Edge<T>> mst();
  
  void print2DotFile(const char *filename) const;
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
bool Graph<T>::contains(const T& info)
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
    for (auto it2 = it->edge.begin(); it2 != it->edge.end(); it2++)
      if ((*it2).from == info || (*it2).to == info)
        it->rmvEdge(*it2);
    
  return true;
}


template<typename T>
void Graph<T>::print2DotFile(const char *filename) const
{
  ofstream out;
  out.open(filename);
  out << "digraph G {" << endl;
  if (isDirected)
  {
    for (auto it = nodes.begin(); it != nodes.end(); it++)
    {
      out << " " << *it->info << endl;
      for (auto it2 = it->edge.begin(); it2 != it->edge.end(); it2++)
      {
        out << "  ->  " << it2->to << " " << endl;
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
        out << "  --  " << it2->to << " " << endl;
      }  
    }
    out << "}" << endl;
    out.close();
  }
}

#endif
