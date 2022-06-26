
#ifndef _GRAPH_UI_
#define _GRAPH_UI_

#include <iostream>
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
      
    }
    else if(!option.compare("re")) {

    }
    else if(!option.compare("dot")) {
      getline(std::cin, line);
      line = line.replace(line.find_first_of(" "), 1, "");
      stream << line;
      g.print2DotFile(stream.str().c_str());
      
    }
    else if(!option.compare("bfs")) {
      
      cout << "\n----- BFS Traversal -----\n";
      
      cout << "\n-------------------------\n";
    }
    else if(!option.compare("dfs")) {
      
      cout << "\n----- DFS Traversal -----\n";
      
      cout << "\n-------------------------\n";
    }
    else if(!option.compare("dijkstra")) {
      getline(std::cin, line);
      stream << line;
      T from(stream);
      T to(stream);

      cout << "Dijkstra (" << from << " - " << to <<"): ";
      
    }
    else if(!option.compare("mst")) {
      int sum = 0;
      cout << "\n--- Min Spanning Tree ---\n";
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
