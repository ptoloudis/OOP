
#ifndef _GRAPH_HPP_ 
#define _GRAPH_HPP_

#include <fstream>
#include <bits/stdc++.h>
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
bool Edge<T>::operator<(const Edge<T>& e) const 
{
  return dist < e.dist;
}

template <typename T>
bool Edge<T>::operator>(const Edge<T>& e) const
{   
  return dist > e.dist;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Edge<T>& e) 
{
  out << e.from << " -- " << e.to << " (" << e.dist << ")";
  return out;
}


// ****************** Node ****************** //
template <typename T>
struct Node
{
  T * info;
  list <Edge<T>> edge;
  int id;

  Node(T * i, int id): info(i), id(id) {
  }
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


// ****************** UNION ****************** //
struct Union
{
  int *parent, *rnk;
  int n;

  // Constructor.
  Union(int n)
  {
    // Allocate memory
    this->n = n;
    parent = new int[n+1];
    rnk = new int[n+1];

    // Initially, all vertices are in
    // different sets and have rank 0.
    for (int i = 0; i <= n; i++)
    {
      rnk[i] = 0;

      //every element is parent of itself
      parent[i] = i;
    }
  }
  
  // Find the parent of a node 'u'
  // Path Compression
  int find(int u)
  {
    /* Make the parent of the nodes in the path
    from u--> parent[u] point to parent[u] */
    if (u != parent[u])
      parent[u] = find(parent[u]);
    return parent[u];
  }

  // Union by rank
  void merge(int x, int y)
  {
    x = find(x), y = find(y);

    /* Make tree with smaller height
    a subtree of the other tree */
    if (rnk[x] > rnk[y])
      parent[y] = x;
    else // If rnk[x] <= rnk[y]
      parent[x] = y;

    if (rnk[x] == rnk[y])
      rnk[y]++;
  }
};


// ****************** Graph ****************** //
template <typename T>
class Graph {
  bool isDirected;
  list<Node<T>> nodes;
  int n;

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
  n = 0;
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
  Node<T> x(new T(info), n);
  nodes.push_back(x);
  n++;
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
bool Graph<T>::addEdg(const T& from, const T& to, int distance)
{
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
bool Graph<T>::rmvEdg(const T& from, const T& to)
{
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
bool find(const T& info, list<T> l)
{
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
  list<T> tmp;
  toVisit.push_back(info);
  while(!toVisit.empty()){
    T curr = toVisit.front();
    toVisit.pop_front();
    if(!find(curr, visited)){
      visited.push_back(curr);
      for(auto it = nodes.begin(); it != nodes.end(); it++){
        if(*it->info == curr){
          for(auto it2 = nodes.begin(); it2 != nodes.end(); it2++){
            if(!find(*it2->info, visited)){
              for(auto it3 = it->edge.begin(); it3 != it->edge.end(); it3++){
                if(it3->to == *it2->info){
                  tmp.push_back(*it2->info);
                }
              }
            }
          }
        }
      }
      toVisit.insert(toVisit.begin(), tmp.begin(), tmp.end());
      tmp.clear();
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
          for(auto it2 = nodes.begin(); it2 != nodes.end(); it2++){
            if(!find(*it2->info, visited)){
              for(auto it3 = it->edge.begin(); it3 != it->edge.end(); it3++){
                if(it3->to == *it2->info){
                  toVisit.push_back(*it2->info);
                }
              }
            }
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
list<Edge<T>> Graph<T>::mst()
{
  list <Edge<T>> all;
  list <Edge<T>> res;
  for(auto it = nodes.begin(); it != nodes.end(); it++){
    for(auto it2 = it->edge.begin(); it2 != it->edge.end(); it2++){
      all.push_back(*it2);
    }
  }
  all.sort();

  Union ds(nodes.size());

  int i, u, v, set_u, set_v;
  for(auto it = all.begin(); it != all.end(); it++){
    // for the first edge
    i = 0;
    for(auto it2 = nodes.begin(); it2 != nodes.end(); it2++){
      if(*it2->info == it->from){
        break;
      }
      i++;
    }
    u = i;

    // for the second edge
    i = 0;
    for(auto it2 = nodes.begin(); it2 != nodes.end(); it2++){
      if(*it2->info == it->to){
        break;
      }
      i++;
    }
    v = i;

    set_u = ds.find(u);
    set_v = ds.find(v);
    if (set_u != set_v){
      ds.merge(set_u, set_v);
      res.push_back(*it);
    }
  }

  return res;
}

template<typename T>
bool Graph<T>::print2DotFile(const char *filename) const
{
  ofstream out;
  try{
    string file(filename);
    file.append(".dot");
    out.open(file);
    if (isDirected)
    {
      out << "digraph G {" << endl;
      int i = 0;
      for (auto it = nodes.begin(); it != nodes.end(); it++)
      {
        out << " " << i << " [label=\""<< *it->info <<"\"];" << endl;
        for (auto it2 = it->edge.begin(); it2 != it->edge.end(); it2++)
        {
          out << " " << i << "  ->  " << it2->to << " [label=" << it2->dist << "];" << endl;
        }
        i++;
      }
      out << "}" << endl;
      out.close();
    }
    else
    {
      out << "graph G {" << endl;
      int i = 0;
      for (auto it = nodes.begin(); it != nodes.end(); it++)
      {
        out << " " << i << " [label=\""<< *it->info <<"\"];" << endl;
        for (auto it2 = it->edge.begin(); it2 != it->edge.end(); it2++)
        {
          out << " " << i << "  --  " << it2->to << " [label=" << it2->dist << "];" << endl;
        }  
        i++;
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

template<typename T>
list<T> Graph<T>::dijkstra(const T& from, const T& to)
{
  list<T> res;
  if(!this->contains(from) || !this->contains(to))
    return res;

  int dist[this->nodes.size()];
  bool visited[this->nodes.size()];
  int parent[this->nodes.size()];

  for(int i = 0; i <(int) this->nodes.size(); i++){
    dist[i] = INT_MAX;
    visited[i] = false;
    parent[i] = -1;
  }

  int i = 0;
  for(auto it = nodes.begin(); it != nodes.end(); it++){
    if(*it->info == from){
      break;
    }
    i++;
  }

  dist[i] = 0;
  for (int j = 0; j < (int) this->nodes.size(); j++)
  {
    int min = INT_MAX;
    int u= 0;
    for (int v = 0; v < (int) this->nodes.size(); v++)
    {
      if (!visited[v] && dist[v] < min)
      {
        min = dist[v];
        u = v;
      }
    }
    visited[u] = true;
    typename list<Node<T>>::iterator ptr;
    ptr = this->nodes.begin();
    advance(ptr, u);

    
    int v = 0;
    for(auto it = nodes.begin(); it != nodes.end(); it++){
      if(!visited[v]){
        for(auto it2 = ptr->edge.begin(); it2 != ptr->edge.end(); it2++){
          if(it2->to == *it->info){
            if (dist[u] + it2->dist < dist[v])
            {
              dist[v] = dist[u] + it2->dist;
              parent[v] = u;
            }
          }
        }
      }
      v++;
    }
  }

  int j = 0;
  for(auto it = nodes.begin(); it != nodes.end(); it++){
    if(*it->info == to){
      break;
    }
    j++;
  }


  // print the path
  typename list<Node<T>>::iterator ptr;
  ptr = this->nodes.begin();
  if (parent[j] == -1){
    return res;
  }
  while (j != i)
  {
    ptr = this->nodes.begin();
    advance(ptr, j);
    res.push_back(*ptr->info);
    j = parent[j];
    if(j == -1)
      break;
  }
  if(j != -1){
    ptr = this->nodes.begin();
    advance(ptr, j);
    res.push_back(*ptr->info);
  }
  else{
    res.clear();
  }
  return res;
}


#endif
