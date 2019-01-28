#include "Graph.hpp"
#include <queue>
#include <string>
#include <math.h>

using namespace std;

//Construction
Edge::Edge()
{
	dist1 = "";
	dist2 = "";
	weight = 0;
}

//Deconstruction
Edge::~Edge(){}

//add Vertex
void Graph::addVertex(std::string label)
{
	vertexList.push_back(label); //add label into vertex vector
}

//remove vertex
void Graph::removeVertex(string label)
{
	Edge *newEdge = new Edge(); //create a new edge

	for (unsigned long i = 0; i < vertexList.size(); i++)
	{
		if (vertexList[i] == label)
		{
			vertexList.erase(vertexList.begin() + i); //remove the first edge
			
			for (unsigned int j = 0; j < vertexEdge.size(); j++)
			{
				newEdge = vertexEdge[j];
				if ((newEdge -> dist1 == label) || (newEdge -> dist2 == label))
				{
					vertexEdge.erase(vertexEdge.begin() + j); //remove the second edge
				}
			}
		}
	}
}

//add Egde
void Graph::addEdge(std::string label1, std::string label2, unsigned long weight)
{
	Edge *newEdge = new Edge(); //create a new edge
	
	//labeling 
	newEdge -> dist1 = label1; 
	newEdge -> dist2 = label2;
	newEdge -> weight = weight;
	vertexEdge.push_back(newEdge); //add edge into vertexEdge vector
}

//remove edge
void Graph::removeEdge(std::string label1, std::string label2)
{
	Edge *newEdge = new Edge(); //create a new edge
	
	for (unsigned long i = 0; i < vertexEdge.size(); i++)
	{
		newEdge = vertexEdge[i];
		if ((newEdge -> dist1 == label1) && (newEdge -> dist2 == label2))
		{
			vertexEdge.erase(vertexEdge.begin() + i); //create the edge
		}
	}
}

//shorsted path 
unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, vector<std::string> &path)
{
	priority_queue<pair<unsigned long, std::string>, vector<pair<unsigned long, std::string>>, greater<pair<unsigned long, std::string>>> thePath;

	map<std::string, unsigned long> distance; //a map to hold distance
	map<string, string> vertices; //a map to hold vertices
	
	for (const auto label : vertexList)
	{
		distance[label] = INFINITY; //distance could be infinity
		vertices[label] = "STOP";
	}
	
	thePath.push(make_pair(0, startLabel)); //first label has distance of 0
	distance[startLabel] = 0; //first label has distance of 0

	while (!thePath.empty())
	{
		std::string temp = thePath.top().second;
		thePath.pop(); //pop value off

		std::string str2;

		for (auto curr : vertexEdge)
		{
			if (curr -> dist1 == temp)
			{
				str2 = curr -> dist2;
			}
			else if (curr -> dist2 == temp)
			{
				str2 = curr->dist1;
			}
			else{continue;}

			unsigned long weight = curr -> weight;

			if (distance[str2] > (distance[temp] + weight))
			{
				vertices[str2] = temp;
				distance[str2] = distance[temp] + weight;
				thePath.push(make_pair(distance[str2], str2));
			}
		}
	}
	
	path.push_back(startLabel);
	findPath(vertices, endLabel, path);

	return distance[endLabel];
}

//find the best path
void Graph::findPath(map<std::string, std::string> startLabel, std::string endLabel, vector<std::string> &path)
{
	if (startLabel[endLabel] == "STOP")
	{
		return;
	}
	
	findPath(startLabel, startLabel[endLabel], path); //creating path

	path.push_back(endLabel);
}
