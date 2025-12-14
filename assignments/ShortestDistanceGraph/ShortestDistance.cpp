/*
* CS236 - Advanced Data Structures and Algorithms
* Joshua Elijah
* 12-13-2025
	Assignment: Lab Assignment - Shortest Distance in Graph
	Brief: Write code that creates the graph given in the following figure (provided my assignment instructions) 
	*Find the shortest graph from:*
		1. Sandwich to Falmouth
		2. Sandwich to Chatham
		3. Falmouth to Orleans
	This is an Undirected graph, so edges should be one-way.
	Start from Falmouth or Sandwich and work your way from there.
*/

#include <iostream>
#include <unordered_map>	// Adjacency list 
#include <vector> 
#include <queue>			// BFS
#include <stack>			// path output
#include <string>
#include <unordered_set>	

using namespace std; 

/*
	A class representing an undirected graph.
*/
class UndirectedGraph {
private:
	// Maps each vertex to its neighboring vertices. 
	unordered_map<string, vector<string>> adjacencyList;

public: 
	
	void addVertex(const string& vertex) {
		// Accessing the key with [] will automatically insert key in to map if non-existent.  
		adjacencyList[vertex]; 
	}

	void addEdge(const string& v1, const string& v2) {
		adjacencyList[v1].push_back(v2); 
		adjacencyList[v2].push_back(v1);
	}

	bool getShortestPath(const string& start, const string& end, stack<string>& path) {
		// Stores where each vertex was discovered from
		unordered_map<string, string> predecessors; 

		// Run BFS to fill predecesors map 
		if (!bfs(start, end, predecessors)) {
			return false;	// No path found
		}

		// Trace path from end to start 
		string current = end; 
		while (current != "") {
			path.push(current);		// Push onto stack 
			current = predecessors[current];		// Move to predecessor
		}
		return true; 
	}

private:
	// Breadth-First Search (BFS) 
	bool bfs(const string& start, const string& end, unordered_map<string, string>& predecessors) {
		unordered_set<string> visited;		// Tracks visited vertices 
		queue<string> q;					// BFS queue

		// Start BFS at the starting vertex
		q.push(start); 
		visited.insert(start); 
		predecessors[start] = "";			// start has no predecessor

		while (!q.empty()) {
			string current = q.front(); 
			q.pop();

			// Visit all neighbors of the current vertex. 
			for (const auto& neighbor : adjacencyList[current]) {
				if (!visited.count(neighbor)) {
					visited.insert(neighbor); 
					predecessors[neighbor] = current;
					q.push(neighbor);

					// Stop BFS as soon as destination is found
					if (neighbor == end) {
						return true; 
					}
				}
			}
		}
		return false;	// End not reachable. 
	}
};

/*
*	Prints the shortest path using a stack
*/
void displayShortestPath(UndirectedGraph& graph, const string& start, const string& end) {
	stack<string> path; 
	if (graph.getShortestPath(start, end, path)) {
		// TODO: Print message "For the graph in the figure...
		cout << "For the graph in the figure the shortest path from "
			<< start << " to " << end << " is" << endl;

		// Display path vertices in order 
		while (!path.empty()) {
			cout << path.top() << endl;
			path.pop();
		}
		cout << endl;
	}
	else {
		// TODO: Print message for "No path exists from xx to yy." 
		cout << "No path exists from "
			<< start << " to " << end << endl;
	}

}

int main() {
	UndirectedGraph UDGraph; 

	// TODO: declare String variables for each city on the Map. 
	const string Provincetown = "Provincetown";
	const string Truro = "Truro";
	const string Orleans = "Orleans";
	const string Chatham = "Chatham";
	const string Barnstable = "Barnstable";
	const string Hyannis = "Hyannis";
	const string Sandwich = "Sandwich";
	const string Falmouth = "Falmouth";

	// TODO: add each vertex to UDGraph	UDGraph.addVertex(Provincetown); 
	UDGraph.addVertex(Provincetown);
	UDGraph.addVertex(Truro);
	UDGraph.addVertex(Orleans);
	UDGraph.addVertex(Chatham);
	UDGraph.addVertex(Barnstable);
	UDGraph.addVertex(Hyannis);
	UDGraph.addVertex(Sandwich);
	UDGraph.addVertex(Falmouth);

	// TODO: add each edge to UDGraph (UDGraph.addEdge)
	UDGraph.addEdge(Provincetown, Truro);
	UDGraph.addEdge(Truro, Orleans);
	UDGraph.addEdge(Orleans, Chatham);
	UDGraph.addEdge(Orleans, Barnstable);
	UDGraph.addEdge(Barnstable, Sandwich);
	UDGraph.addEdge(Barnstable, Hyannis); 
	UDGraph.addEdge(Chatham, Hyannis);
	UDGraph.addEdge(Hyannis, Falmouth);

	// TODO: employ shortest path method for each city pair
	displayShortestPath(UDGraph, Sandwich, Falmouth);
	displayShortestPath(UDGraph, Sandwich, Chatham); 
	displayShortestPath(UDGraph, Falmouth, Orleans);

	return 0;
}