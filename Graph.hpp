#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <iostream>
#include <string>
#include <vector>

#include "GraphBase.hpp"

using namespace std;

class Edge 
{
	public:
		string dist1, dist2;
		unsigned long weight;
		Edge();
		~Edge();

};

class Graph : public GraphBase
{
	public:
		friend class Edge;
		
		vector<std::string> vertexList;
		vector<Edge*> vertexEdge;
		
		void addVertex(std::string label);
		void removeVertex(std::string label);
		void addEdge(std::string label1, std::string label2, unsigned long weight);	
		void removeEdge(std::string label1, std::string label2);
		unsigned long shortestPath(std::string startLabel, std::string endLabel, vector<std::string> &path);
		void findPath(map<std::string, std::string> startLabel, std::string endLabel, vector<std::string> &path);

};
#endif
