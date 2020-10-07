// By: Ingmar Fjolla
//Professor Anita Raja
//Project Description : 
// In order to test your implementation, you will read a second text file (let us call it AdjacencyQueries1.txt) 
//that will contain a set of pair of vertices. Your program (name it CreateGraphAndTest.cc) will have to first create the graph by reading 
//it from text file Graph1.txt. It
// will then open the file AdjacencyQueries1.txt and for each pair of vertices in it, 
//your program will print whether the vertices are adjacent or not, and if they are, your program will print the weight 
//of the edge that connects them

#include "graph.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream> 
using namespace std; 

//Parameters: the adjacent file and the graph created in creatgraphandtest function
//Reads in the adjacent file and 
void CheckAdjacent (string adjacent_file, Graph graph_created) {
    int v; //Contains the first vertex
    int adj_vertex; //Contains the second vertex, aka the adjacent vertex, will be compared to the first 

    string db_line;
    ifstream second_file(adjacent_file); //Opens the adjacent file

    //While going through the file, do the following:
    while(getline(second_file, db_line)) {
        stringstream hold; //Create a stringstream object called hold that'll be used for parsing
        hold.str(db_line); //Parses db_line that's used for getline 

        //While loop reads in the two vertices 
        while(hold >> v && hold >> adj_vertex) {
            graph_created.CheckIfAdjacent(v, adj_vertex); //Checks if the two are adjacent 
        }
    }
} 

int graphTestDriver(int argc, char **argv) {
    
    //Begin your code here. Feel free to add any helper functions or classes you need,
    //as long as we only have to call this function to run the specified assignment.
    const string graph_filename = argv[1];
  	const string query_filename = argv[2];
    int vert_num; //Will hold the number of vertices in the file  
    int vertex; //Will hold vertex
    int adj_vertex; //Will hold the adjacent of the vertex
    double weight; //Will hold the weight between two vertices

    string db_line; //Creates a string that'll be used for getline and reading the file 
    ifstream a_file(graph_filename); //Open the file that is inputted 
    
    a_file>>vert_num; //Reads in the vertex number at the top of the file 
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

    CheckAdjacent(query_filename, graph_created); //Read the adjacent file, put in the graph_created as the parameter for the function
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 3) {
		cout << "Usage: " << argv[0] << " <GRAPH_File>" << "<ADJACENCY_QUERYFILE>" << endl;
		return 0;
    }

    graphTestDriver(argc, argv);

    return 0;
}