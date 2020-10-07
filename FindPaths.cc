// By: Ingmar Fjolla
//Professor Anita Raja
//Project Description : 
//PART 2
//Using your graph implementation in Q1, implement Dijkstra’s Algorithm, using a priority queue (i.e.
//heap). Write a program that runs as follows: ./FindPaths <GRAPH_FILE> <STARTING_VERTEX>
//This program should use Dijkstra’s Algorithm to find the shortest paths from a given starting 
//vertex to all vertices in the graph file.



#include "graph.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream> 
using namespace std; 


int pathfindDriver(int argc, char **argv) {
    
    //Begin your code here. Feel free to add any helper functions or classes you need,
    //as long as we only have to call this function to run the specified assignment.
    const string graph_file (argv[1]);
	const int start_vertex = atoi(argv[2]);
	int vert_num; //Will hold the number of vertices in the file  
    int vertex; //Will hold vertex
    int adj_vertex; //Will hold the adjacent of the vertex
    double weight; //Will hold the weight between two vertices

    string db_line; //Creates a string that'll be used for getline and reading the file 
 	ifstream a_file(graph_file); //Open the file that is inputted 

 	a_file>> vert_num; //Reads in the vertex number at the top of the file 
 
    Graph graph_created(vert_num); //Creates a graph, with the size of the vertices in the file

	
	//While loop contains getline that reads line by line every item in the input 
	while(getline(a_file, db_line)) { 
 		stringstream hold; //Create a stringstream object called hold that'll be used for parsing 
    	hold.str(db_line); //Parses db_line that's used for getline  
    	hold >> vertex; //Vertex now holds the main vertex and we'll find the adjacents and weights in the next while loop

        //While loop reads in the adjacent vertex and the weight 
    	while(hold >> adj_vertex && hold >> weight) {
    		graph_created.InsertIntoVector(vertex, adj_vertex, weight); //Insert the adjacent and weight into the adjacent list of a vector and add it into the graph
    	}
    }
	graph_created.Dijkstra_Algorithm(start_vertex); //Goes through the function that finds the shortest path using the dijkstra algorithm

    return 0;
}

int main(int argc, char **argv) {
    if (argc != 3) {
		cout << "Usage: " << argv[0] << " <GRAPH_FILE>" << "<STARTING_VERTEX>" << endl;
		return 0;
    }

    pathfindDriver(argc, argv);

    return 0;
}