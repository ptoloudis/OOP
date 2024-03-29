
#ifndef _GRAPH_UI_
#define _GRAPH_UI_

#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
template <typename T>
int graphUI() {
  
  string option, line;
  int distance;
  bool digraph = false;
  
  cin >> option;
  if(!option.compare("digraph"))
    digraph = true;
  Graph<T> g(digraph);
  
  while(true) {
    
    std::stringstream stream;
    cin >> option;
    
    if(!option.compare("av")) {
      getline(std::cin, line);
      stream << line;
      T vtx(stream);
      if(g.addVtx(vtx))
        cout << "av " << vtx << " OK\n";
      else
        cout << "av " << vtx << " NOK\n";
    }
    else if(!option.compare("rv")) {
      getline(std::cin, line);
      stream << line;
      T vtx(stream);
      if(g.rmvVtx(vtx))
        cout << "rv " << vtx << " OK\n";
      else
        cout << "rv " << vtx << " NOK\n";
    }
    else if(!option.compare("ae")) {
      getline(std::cin, line);
      stream << line;
      T from(stream);
      T to(stream);
      stream >> distance;

      if(g.addEdg(from, to, distance))
        cout << "ae " << from << " " << to << " OK\n";
      else
        cout << "ae " << from << " " << to << " NOK\n";
      
    }
    else if(!option.compare("re")) {
      getline(std::cin, line);
      stream << line;
      T from(stream);
      T to(stream);

      if(g.rmvEdg(from, to))
        cout << "re " << from << " " << to << " OK\n";
      else
        cout << "re " << from << " " << to << " NOK\n";
      
    }
    else if(!option.compare("dot")) {
      getline(std::cin, line);
      line = line.replace(line.find_first_of(" "), 1, "");
      stream << line;
      if(g.print2DotFile(stream.str().c_str())){
        pid_t pid = fork();
        if(pid == 0) {
          string in = stream.str().append(".dot");
          string out = stream.str().append(".png");
          execlp("dot", "dot", "-Tpng", in.c_str(), "-o", out.c_str(), nullptr);
        }
        else if(pid > 0) {
          cout << "dot " << stream.str() << " OK\n";
        }
        else {
          cout << "dot " << stream.str() << " NOK\n";
        }
      }
      else
        cout << "dot " << stream.str() << " NOK\n";      
    }
    else if(!option.compare("bfs")) {
      getline(std::cin, line);
      stream << line;
      T vtx(stream);
      list<T> l = g.bfs(vtx);
      cout << "\n----- BFS Traversal -----\n";
      for(auto it = l.begin()++; it != l.end(); it++ ) {
        if (it == l.begin())
          cout << *it;
        else
          cout << " -> " << *it;
      }
      cout << "\n-------------------------\n";
    }
    else if(!option.compare("dfs")) {
      getline(std::cin, line);
      stream << line;
      T vtx(stream);
      list<T> l = g.dfs(vtx);
      cout << "\n----- DFS Traversal -----\n";
      for(auto it = l.begin()++; it != l.end(); it++ ) {
        if (it == l.begin())
          cout << *it;
        else
          cout << " -> " << *it;
      }
      cout << "\n-------------------------\n";
    }
    else if(!option.compare("dijkstra")) {
      getline(std::cin, line);
      stream << line;
      T from(stream);
      T to(stream);

      list<T> l;
      l = g.dijkstra(from, to);
      cout << "Dijkstra (" << from << " - " << to <<"): ";
      for(auto it = l.rbegin(); it != l.rend(); it++ ) {
        if (it == l.rbegin())
          cout << *it;
        else
          cout << ", " << *it;
      }
      cout << endl;
    }
    else if(!option.compare("mst")) {
      int sum = 0;
      list<Edge<T>> l = g.mst();
      cout << "\n--- Min Spanning Tree ---\n";
      for(auto it = l.begin()++; it != l.end(); it++ ) {
        cout << it->from << " -- " << it->to << " (" << it->dist << ")" << endl;
        sum += it->dist;
      }
      cout << "MST Cost: " << sum << endl;
    }
    else if(!option.compare("q")) {
      cerr << "bye bye...\n";
      return 0;
    }
    else if(!option.compare("#")) {
      string line;
      getline(cin,line);
      cerr << "Skipping line: " << line << endl;
    }
    else {
      cout << "INPUT ERROR\n";
      return -1;
    }
  }
  return -1;  
}

#endif
