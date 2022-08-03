
FLAGS = -Wall -g -std=c++11 -fsanitize=address 

build: Graph.hpp GraphUI.hpp
	@ date +%s > _time_.txt
	@ echo "Building..."
	g++ $(CFLAGS) GraphString.cpp -o gstr
	g++ $(CFLAGS) GraphStudent.cpp -o gstudent
	g++ $(CFLAGS) GraphInteger.cpp -o gint
	@ echo "Build time: "  $$(($$(date +%s) - $$(cat _time_.txt)))
	@ rm _time_.txt

bfs1:
	@./gstr < tests/bfs1.in > bfs1.out
	@diff -urN tests/bfs1.std bfs1.out > h.diff
	@ echo "BFS1: " $$($$(size h.diff))
bfs2:
	@./gstr < tests/bfs2.in > bfs2.out 
	@diff -urN tests/bfs2.std bfs2.out > h.diff
	@ echo "BFS2: " $$($$(size h.diff))
bfs3:
	@./gstr < tests/bfs3.in > bfs3.out 
	@diff -urN tests/bfs3.std bfs3.out > h.diff
	@ echo "BFS3: " $$($$(size h.diff))
dfs1:
	@./gstr < tests/dfs1.in > dfs1.out
	@diff -urN tests/dfs1.std dfs1.out > h.diff
	@ echo "DFS1: " $$($$(size h.diff))
dfs2:
	@./gstr < tests/dfs2.in > dfs2.out 
	@diff -urN tests/dfs2.std dfs2.out> h.diff
	@ echo "DFS1: " $$($$(size h.diff))
dfs3:
	@./gstr < tests/dfs3.in > dfs3.out 
	@diff -urN tests/dfs3.std dfs3.out> h.diff
	@ echo "DFS1: " $$($$(size h.diff))
mst1:
	@./gstr < tests/mst1.in > mst1.out
	@diff -urN tests/mst1.std mst1.out> h.diff
	@ echo "DFS1: " $$($$(size h.diff))
mst2:
	@./gstr < tests/mst2.in > mst2.out
	@diff -urN tests/mst2.std mst2.out> h.diff
	@ echo "DFS1: " $$($$(size h.diff))
mst3:
	@./gstudent < tests/mst3.in > mst3.out
	@diff -urN tests/mst3.std mst3.out> h.diff
	@ echo "DFS1: " $$($$(size h.diff))
dijkstra1:
	@./gstr < tests/dijkstra1.in > dijkstra1.out
	@diff -urN tests/dijkstra1.std dijkstra1.out> h.diff
	@ echo "DFS1: " $$($$(size h.diff))
dijkstra2:
	@./gstr < tests/dijkstra2.in > dijkstra2.out
	@diff -urN tests/dijkstra2.std dijkstra2.out> h.diff
	@ echo "DFS1: " $$($$(size h.diff))
dijkstra3:
	@./gstr < tests/dijkstra3.in > dijkstra3.out
	@diff -urN tests/dijkstra3.std dijkstra3.out> h.diff
	@ echo "DFS1: " $$($$(size h.diff))
dijkstra4:
	@./gstudent < tests/dijkstra4.in > dijkstra4.out
	@diff -urN tests/dijkstra4.std dijkstra4.out> h.diff
	@ echo "DFS1: " $$($$(size h.diff))
	
run: bfs1 bfs2 bfs3 dfs1 dfs2 dfs3 mst1 mst2 mst3 dijkstra1 dijkstra2 dijkstra3 dijkstra4

ha:
	@ date +%s > _time_.txt
	@ echo "RUN..."
	@ make run
	@ echo "RUN time: "  $$(($$(date +%s) - $$(cat _time_.txt)))
	@ rm _time_.txt
	@ echo "Done!"
