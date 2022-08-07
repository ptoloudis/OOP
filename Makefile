
FLAGS = -Wall -g -std=c++11 -fsanitize=address 

build: Graph.hpp GraphUI.hpp
	g++ $(CFLAGS) GraphString.cpp -o gstr
	g++ $(CFLAGS) GraphStudent.cpp -o gstudent
	g++ $(CFLAGS) GraphInteger.cpp -o gint
	

bfs1:
	@./gstr < tests/bfs1.in > bfs1.out
	@diff -urN tests/bfs1.std bfs1.out > bfs1.diff
	
bfs2:
	@./gstr < tests/bfs2.in > bfs2.out 
	@diff -urN tests/bfs2.std bfs2.out > bfs3.diff
	
bfs3:
	@./gstr < tests/bfs3.in > bfs3.out 
	@diff -urN tests/bfs3.std bfs3.out > bfs3.diff
dfs1:
	@./gstr < tests/dfs1.in > dfs1.out
	@diff -urN tests/dfs1.std dfs1.out > dfs1.diff
dfs2:
	@./gstr < tests/dfs2.in > dfs2.out 
	@diff -urN tests/dfs2.std dfs2.out> dfs2.diff
dfs3:
	@./gstr < tests/dfs3.in > dfs3.out 
	@diff -urN tests/dfs3.std dfs3.out> dfs3.diff
mst1:
	@./gstr < tests/mst1.in > mst1.out
	@diff -urN tests/mst1.std mst1.out> mst1.diff
mst2:
	@./gstr < tests/mst2.in > mst2.out
	@diff -urN tests/mst2.std mst2.out> mst2.diff
mst3:
	@./gstudent < tests/mst3.in > mst3.out
	@diff -urN tests/mst3.std mst3.out> mst3.diff
dijkstra1:
	@./gstr < tests/dijkstra1.in > dijkstra1.out
	@diff -urN tests/dijkstra1.std dijkstra1.out> dijkstra1.diff
	
dijkstra2:
	@./gstr < tests/dijkstra2.in > dijkstra2.out
	@diff -urN tests/dijkstra2.std dijkstra2.out> dijkstra2.diff
	
dijkstra3:
	@./gstr < tests/dijkstra3.in > dijkstra3.out
	@diff -urN tests/dijkstra3.std dijkstra3.out> dijkstra3.diff
	
dijkstra4:
	@./gstudent < tests/dijkstra4.in > dijkstra4.out
	@diff -urN tests/dijkstra4.std dijkstra4.out> dijkstra4.diff

	
run: bfs1 bfs2 bfs3 dfs1 dfs2 dfs3 mst1 mst2 mst3 dijkstra1 dijkstra2 dijkstra3 dijkstra4