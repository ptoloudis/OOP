
#ifndef _GRAPH_HPP_ 
#define _GRAPH_HPP_

#include <list>

template<typename T>
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

template<typename T>
std::ostream& operator<<(std::ostream& out, const Edge<T>& e) {
  out << e.from << " -- " << e.to << " (" << e.dist << ")";
  return out;
}

template <typename T>
struct node
{
  T * info;
  list<struct Edge> edge;
};


template <typename T>
class Graph {
  bool isDirected;
  list<struct node> nodes;

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


#endif
