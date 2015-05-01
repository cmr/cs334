CC = clang++
FLAGS = -g -Wall
DFLAGS =
INPUT_FILE = in_graph.txt
BFS_FILE = out_bfs.txt
DFS_FILE = out_dfs.txt
GRAPH_SIZE = 5
SOURCE = make_graph.cpp bfs_graph.cpp dfs_graph.cpp
EXECS = test_make_graph test_bfs test_dfs

all: test_make_graph test_bfs test_dfs run_make run_bfs run_dfs

run_make:
	./test_make_graph $(GRAPH_SIZE) $(INPUT_FILE); dot -Tps $(INPUT_FILE) -o in.ps

run_bfs:
	./test_bfs $(INPUT_FILE) $(BFS_FILE); dot -Tps $(BFS_FILE) -o out_bfs.ps

run_dfs:
	./test_dfs $(INPUT_FILE) $(DFS_FILE); dot -Tps $(DFS_FILE) -o out_dfs.ps

test_make_graph: make_graph.cpp
	$(CC) $(FLAGS) $(DFLAGS) -o test_make_graph make_graph.cpp

test_bfs: bfs_graph.cpp
	$(CC) $(FLAGS) $(DFLAGS) -o test_bfs bfs_graph.cpp

test_dfs: dfs_graph.cpp
	$(CC) $(FLAGS) $(DFLAGS) -o test_dfs dfs_graph.cpp

clean:
	rm -f $(EXECS)

