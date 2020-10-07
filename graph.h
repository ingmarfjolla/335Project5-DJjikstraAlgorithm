// By: Ingmar Fjolla
//Professor Anita Raja
//Project Description : 
//PART 1 FOR TH
// In order to test your implementation, you will read a second text file (let us call it AdjacencyQueries1.txt) 
//that will contain a set of pair of vertices. Your program (name it CreateGraphAndTest.cc) will have to first create the graph by reading 
//it from text file Graph1.txt. It
// will then open the file AdjacencyQueries1.txt and for each pair of vertices in it, 
//your program will print whether the vertices are adjacent or not, and if they are, your program will print the weight 
//of the edge that connects them
//PART 2
////Using your graph implementation in Q1, implement Dijkstra’s Algorithm, using a priority queue (i.e.
//heap). Write a program that runs as follows: ./FindPaths <GRAPH_FILE> <STARTING_VERTEX>
//This program should use Dijkstra’s Algorithm to find the shortest paths from a given starting 
//vertex to all vertices in the graph file.

#ifndef GRAPH_H
#define GRAPH_H


#include "binary_heap.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include <limits>
#include <queue> 
#include <limits>
using namespace std; 


class Graph {
private: 
	//Contains necessary variables for adjacent vertices and the weight corresponding to the two connected vertices 
	struct Adjacent_V {
		int adj_id; //Contains the value of the adjacent vertex 
		double costs; //Contains the weight of the two connected vertices 

		//Setting the values in the parameter to the id of the adjacent vertex and the weight between the two connected vertices
		Adjacent_V(const int &Adjacent_name, const double &cost) {
			adj_id = Adjacent_name;
			costs = cost; 
		} 
	};
	//Contains necessary variables for vertices, such as the value of the vertex, the distance, indegrees, etc. that are needed for parts 1, 2, and 3  
	struct Vertex{
		int id; 
		bool known; 
		double distance; 
		int indegree = 0;
		Vertex* path_of_vertices;  
		vector<Adjacent_V> list_of_adj;  

		//Make each of the variables listed before into the values put in into the parameters 
		Vertex(const int &num_ver, const bool &check, const double &weight, const int indegrees,Vertex *paths){
			id = num_ver; 
			known = check; 
			distance = weight; 
			indegree = indegrees; 
			path_of_vertices = paths; 
		}
	};

	

	//This struct allows a comparison between two vertices inputted 
	//The distance of each vertex is compared 
	struct Comparison {
		bool operator() (const Vertex* vertex1, const Vertex* vertex2) const {
			//If the vertex1's distance is greater than the distance of vertex2, return true, otherwise return false 
			if (vertex1 -> distance > vertex2 -> distance) {
				return true;
			}
			else {
				return false; 
			}
		}
	};

	vector<Vertex*> vector_of_vertices; //Vector contains vertex pointers 
	
public:

//-----------------------------------BIG 5 FOR GRAPH------------------------------------------------
	//Constructor 
	Graph() {
	}

	//Destructor 
	~Graph() {
		//Going through the vector of vertices, delete all elements in the vector by deleting the value and then setting the pointer to nullpointer 
		for (size_t i = 1; i < vector_of_vertices.size(); i++) { //Goes through the vector of vertices by each element 
			delete vector_of_vertices[i]; //Delete the value of the element 
			vector_of_vertices[i] = nullptr; //Set the pointer to nullpointer 
		}
	}

	//Copy-Assignment
	Graph &operator= (const Graph &rhs)
	{
		Graph copy = rhs;
		swap(*this, copy);
		return *this;
	}

	//Copy Constructor 
	//Setting the size of the vector of vertices to the size of the rhs's vector of vertices, in the parameters
	Graph (const Graph &rhs): vector_of_vertices(rhs.vector_of_vertices.size()) { 

		//For each element in the vector of vertices in rhs, create a new vertex object 
		for(size_t i = 1; i < rhs.vector_of_vertices.size(); i++) {
			//Copy each element and vertex info into vector of vertices from rhs
			vector_of_vertices[i] = new Vertex(
				rhs.vector_of_vertices[i] -> id,
				rhs.vector_of_vertices[i] -> known,
				rhs.vector_of_vertices[i] -> distance, 
				rhs.vector_of_vertices[i] -> indegree, 
				rhs.vector_of_vertices[i] -> path_of_vertices);
			//Copy the list of adjacencies for each vertex from rhs into the list of adjacencies of each vertex in a vector of vertices 
			this -> vector_of_vertices[i] -> list_of_adj = rhs.vector_of_vertices[i] -> list_of_adj;
		}
	}

	//One-Parameter Constructor 
	//Make the vector of vertices the size of ver_num + 1, given in the parameter 
	Graph (const int & ver_num): vector_of_vertices(ver_num + 1) {
		//indegrees is set to infinity 
		size_t indegrees = numeric_limits<int>::max();

		//While going through the vector, who's now the size of ver_num + 1, do the following: 
		for (size_t i = 1; i < ver_num + 1; i++) {
			//Create new vertex objects , the id of which is i (each number from 1 to ver_num+1,), setting known to false, distance is infinite
			//indegree is set to zero, the path is set nullpointer 
			vector_of_vertices[i] = new Vertex (i, false, indegrees, 0,nullptr);
		}
	}



	//Insert the adajcents into the vertex's vector of adjacents 
	void InsertIntoVector (int &vertexx, int &adjacent_vertex, double &costs) {
		Adjacent_V adjacent(adjacent_vertex, costs); //Creating an adjacent object, containing data members from adjacent_v 
		vector_of_vertices[vertexx] -> list_of_adj.push_back(adjacent); //The adjacents are put into a vertex's list of adjacent vertices 
	}

	//Checks to see if the two vertices put into the parameter are adjacents 
	void CheckIfAdjacent(int &vertex1, int &vertex2) {
		bool check = false; //Sets check to false, it'll be used to check if the vertices are adjacent 
		double weight = 0; //Weight is set to zero
		//This for loop goes through the list of adjacents for the vertex input into the parameter 
		for (size_t i = 0; i < vector_of_vertices[vertex1] -> list_of_adj.size(); i++)
		{
			//If any of the vertices in vertex1's list of adjacents is equal to vertex2, set check to true, indicating it is an adjacent 
			if (vector_of_vertices[vertex1] -> list_of_adj[i].adj_id == vertex2)
			{
				weight = vector_of_vertices[vertex1] -> list_of_adj[i].costs; //Weight is accounted for, to be used in the print function 
				check = true;
				break; //Break out of the for loop if the two vertices are adjacent 
			}
		}
		PrintAdjacent(vertex1, vertex2, check, weight); //Prints out whether the two vertices are connected or not 
	}

	//Taking parameters: vertex1, vertex2, check, and weight 
	//Prints if the two vertices are connected or not
	//Uses the boolean and the weight 
	void PrintAdjacent(int &vertex1, int &vertex2, bool check, double weight) {
		//If check is true, display that the two vertices are connected and display their weight 
		if (check == true) {
			cout << vertex1 <<" "<< vertex2 <<": connected " << weight << std::endl;
		}
		else {
			//If check is false, display that they're not connected 
			cout << vertex1 <<" "<< vertex2 <<": not_connected " << std::endl;
		}
	}

	//Prints all the adjacent vertices for the vertices stored in the vector of vertices 
	void PrintAdjVector() {
		//Goes through each vertex in the vector 
		for (size_t i = 1; i < vector_of_vertices.size(); i++) {
			//Go through each element of the list of adjacents of a vertex in the vector of vertices 
			for (size_t j = 0; i < vector_of_vertices[i] -> list_of_adj.size(); j++) {
				//Prints out the elements in the list of adjacent of a vertex
				cout << vector_of_vertices[i] -> list_of_adj[j].adj_id << " ";
			}
			cout << endl;
		}
	}

	//For testing purposes, prints all the vertices in the vector of vertices 
	void PrintVectorOfVertices() {
		//Goes through each vertex in the vector 
		for (size_t i = 1; i < vector_of_vertices.size(); i++) {
			cout << vector_of_vertices[i] -> id << " " << endl; //Display each value of the vertex in the vector
		}
	}


//part 2 60 points Dijkstra’s Algorithm

	//Prints the shortest path for the path of vertices
	void ShortestPath(Vertex *vertex) {
		//The base case: if the path of vertices isnt nullpointer, do a recursive call 
		if (vertex -> path_of_vertices != nullptr) {
			ShortestPath(vertex -> path_of_vertices); 
		}
		//Prints out the value of the vertex
		cout << vertex -> id << " ";
	}

	//Prints out the path and the cost, extending from Dijkstra's algorithm 
	void PrintingForAlgorithm() {
		//Goes through the vector of vertices 
		for (size_t i = 1; i < vector_of_vertices.size(); i++) {
			//Prints out the id of the vertex 
			cout << vector_of_vertices[i] -> id << ": ";
			double weight_of_shortest_path = vector_of_vertices[i] -> distance; //Contains the weight of the path 
			 

			//If the weight of the shortest path is not infinite, print out the cost 
			if (weight_of_shortest_path != numeric_limits<int>::max()) {
				//cout << vector_of_vertices[i] -> id << ": ";
				ShortestPath(vector_of_vertices[i]); //Recursively call the function to find the shortest path
				cout << "cost: " << weight_of_shortest_path << endl;
			}
			//Else, print out "No path"
			else {
				cout <<"not_possible"<< endl;
			}

		}
	}
//std::fixed<< std::setprecision(1)<<
	//Goes through the Dijkstra algorithm using priority queue 
	//Takes in a number in the parameter, the vertex at its position in vector of vertices is used 
	void Dijkstra_Algorithm(const int &vertex) {
		vector_of_vertices[vertex] -> distance = 0; //Make the vertex at the position's distance equal to zero 
		priority_queue <Vertex*, vector<Vertex*>, Comparison> dij_pq; //create a priority queue that takes in a vertex pointer, a vector of pointer vertices, and comparison(compares two vertices)
		dij_pq.push(vector_of_vertices[vertex]); //Pushes the the vertex from the vector of vertices into the priority queue 

		//While the priority queue is not empty 
		while (!(dij_pq.empty())) {
			Vertex  *vert = dij_pq.top(); //Created a vertex pointer that contains the first element in the priority queue, aka the top  
			dij_pq.pop(); //Removes the first element in the priority queue 
			vert -> known = true; //Changes that vertex's known to true 

			//Going through vert's vector of adjacents, and doing the following: 
			for (size_t i = 0; i < vert -> list_of_adj.size(); i++) {
				int vert_id = vert -> list_of_adj[i].adj_id; //Creating a new variable, called vert_id that holds the value of the adjacent vertex at the givem value 
				Vertex *unk_v = vector_of_vertices[vert_id]; //Creating a new vertex pointer that is equal to the address of the vertex at the position given by vert_id, which holds the value of the adjacent 

				//If the new vertex pointer's known is false, do the following 
				if (unk_v -> known == false) {
					double cost = vert -> list_of_adj[i].costs; //Create a new variable that contains the cost/weight between the two vertices 

					//if the total of the vertex's distance plus the cost is less than the distance of the new vertex's distance(gotten from the position, from which was recieved by the vertex's vector of adjacents), do the following: 
					if (vert -> distance + cost < unk_v -> distance) {
						unk_v -> distance = vert -> distance + cost; //The distance of the new vertex is set to the total of the vertex's distance and cost 
						unk_v -> path_of_vertices = vert; //The path of the new vertex is set to the vertex, vert
					}

					dij_pq.push(unk_v); //Push that new vertex into the priority queue 
				}
			}
		}
		PrintingForAlgorithm(); //Prints the path and costs from the algorithm 
	}
	


	
};

#endif /*Graph*/