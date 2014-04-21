#include <vector>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <limits>
#include <queue>
#include <stack>

std::vector< std::vector<int> >  readGraph(std::string filename, int * numVert)
{
	std::ifstream ifs;
	ifs.open(filename.c_str(),std::ifstream::in);
	
	std::vector< std::vector<int> > vertices;
	int max_val = std::numeric_limits<int>::min();

	while(ifs.good())
	{
		std::vector<int> vert;
		vert.resize(2);
		ifs>>vert[0];
		ifs>>vert[1];
		max_val = std::max(max_val,vert[0]);
		max_val = std::max(max_val,vert[1]);
		std::cout<<vert[0]<<"\t";
		std::cout<<vert[1]<<std::endl;
		vert[0] = vert[0]-1; 
		vert[1] = vert[1]-1;
		vertices.push_back(vert);
	}
	ifs.close();
	
	(*numVert) = max_val;
	return vertices;
}


/////////////////////////* Undirected Graph API*/////////////////////
struct vertex {
	int id;
	int dist;
};

class Graph
{
	public:
		Graph();
		Graph(int numVertices);
		
		void addEdge(vertex v, vertex w);
		void addEdgeDAG(vertex v, vertex w);
		std::vector<vertex>& adjacency(int vid);
		
		int getDist(int vid);
		void setDist(int vid, int dist);
		int getMaxDistId(void);
		int getMaxDist(void);
		void printDist(void);
		
		int V(void);
		int E(void);
	private:
		std::vector< std::vector<vertex> > adjacency_list;	
		std::vector<int> dist_list;
};
Graph::Graph()
{
}
Graph::Graph(int numVertices)
{
	adjacency_list.resize(numVertices);
	dist_list.resize(numVertices);
	for(int i=0; i<numVertices; ++i)
		dist_list[i]=0;
}
void Graph::setDist(int vid,int dist)
{
	dist_list[vid]=dist;
}
int Graph::getDist(int vid)
{
	return dist_list[vid];
}
void Graph::printDist(void)
{
	std::cout<<"printing distances:\n";
	for(int i=0; i<dist_list.size(); ++i)
		std::cout<<dist_list[i]<<"\t";
	std::cout<<"\n";
}
int Graph::getMaxDistId(void)
{
	int max = std::numeric_limits<int>::min();
	int index = -1;
	for(int i=0; i<dist_list.size(); ++i)
	{
		if(max <= dist_list[i])
		{
			max = dist_list[i];
			index = i;
		}
	}
	return index;
}
int Graph::getMaxDist(void)
{
	int max = std::numeric_limits<int>::min();
	for(int i=0; i<dist_list.size(); ++i)
	{
		if(max <= dist_list[i])
		{
			max = dist_list[i];
		}
	}
	return max;
}

void Graph::addEdge(vertex v, vertex w)
{
	adjacency_list[v.id].push_back(w);
	adjacency_list[w.id].push_back(v);
}
void Graph::addEdgeDAG(vertex v, vertex w)
{
	adjacency_list[v.id].push_back(w);
}
int Graph::V(void)
{
	return adjacency_list.size();
}
int Graph::E(void)
{
	int numEdges = 0;
	for(int v=0; v<adjacency_list.size(); ++v)
		numEdges += adjacency_list[v].size();
		
	return numEdges/2;
}
std::vector<vertex>& Graph::adjacency(int v)
{
	return adjacency_list[v];
}
/////////////////////////* Processing Functions */////////////////////
int degree(Graph * G, int v)
{
	if(v<G->V())
		return G->adjacency(v).size();
	else
		return -1;
}
int maxDegree(Graph * G)
{
	int max_deg = -1;
	for(int v = 0; v<G->V(); ++v)
		max_deg = std::max(max_deg,degree(G,v));
	return max_deg;
}
float averageDegree(Graph * G)
{
	return (float)(2*G->E())/(float)G->V();
}
int numberOfSelfLoop(Graph * G)
{
	int numLoops = 0;
	for(int v = 0; v<G->V(); ++v)
		for(int i = 0; i<G->adjacency(v).size(); ++i)
			if(G->adjacency(v)[i].id == v)
				numLoops +=1;
	return numLoops/2;
}

/////////////////////////* Traversals */////////////////////
void recursiveDfs(Graph * G, int v, std::vector<bool> &visited)
{
	visited[v] = true;
	for(int i=0; i<G->adjacency(v).size(); ++i)
	{
		int w = G->adjacency(v)[i].id;
		if(!visited[w])
		{
			recursiveDfs(G,w,visited);
		}
	}
	std::cout<<v<<"\t";
}

//depth first search
void dfs(Graph * G, int v, std::vector<bool> &visited)
{
	visited[v] = true;
	std::stack<int> S;
	S.push(v);
	while(!S.empty())
	{
		int w = S.top();
		S.pop();
		for(int i=0; i<G->adjacency(w).size(); ++i)
		{
			int n = G->adjacency(w)[i].id;
			if(!visited[n])
				S.push(n);
		}
		visited[w] = true;
		std::cout<<w<<"\t";
	}
    std::cout<<"\n";
}

// breadth first search
void bfs(Graph * G, int v, std::vector<bool> &visited)
{
	visited[v] = true;
	std::queue<int> Q;
	Q.push(v);
	G->setDist(v,0);
	
	while(!Q.empty())
	{
		int w = Q.front();
		Q.pop();
		int wdist = G->getDist(w);
		for(int i=0; i<G->adjacency(w).size(); ++i)
		{
			int n = G->adjacency(w)[i].id;
			if(!visited[n])
			{
				Q.push(n);
				G->setDist(n,wdist+1);
			}
		}
		visited[w] = true;
		std::cout<<w<<"\t";
	}
    std::cout<<"\n";
	
}

///////////////////////// Algorithms and Interview Questions/////////////////////
/*
The eccentricity ecc(v) of v in G is the greatest distance from v to any other node. easy

The radius rad(G) of G is the value of the smallest eccentricity. 

The diameter diam(G) of G is the value of the greatest eccentricity. done below

The center of G is the set of nodes v such that ecc(v)=rad(G), once diameter is found (find the vertices with half the diameter)
*/
int diameter(Graph * G)
{
	std::vector<bool> visited;
	visited.resize(G->V());
	for(int i=0; i<visited.size(); ++i)
		visited[i]=false;
	
	bfs(G,4,visited);
	for(int i=0; i<visited.size(); ++i)
			visited[i]=false;	
	bfs(G,G->getMaxDistId(),visited);
	
	

	return G->getMaxDist();
}


/*	DAG: 
	Shortest directed cycle. Given a digraph G, find a directed cycle with the minimum number of edges. The running time of your algorithm should be at most proportional to V(E+V) and use space proportional to E+V
*/

// returns length (number of edges)
int shortestDirectedCycle(Graph * G, int v)
{
	std::vector<bool> visited;
	std::vector<int> index; // index of vertex (if visited) in the stack, otherwise -1
	visited.resize(G->V());
	index.resize(G->V());
	for(int i=0; i<G->V(); ++i)
	{
		visited[i] = false;	
		index[i] = -1;
	}
	
	int length = G->V()+1;
	
	// run modified DFS
	bool visted_all = false;
	while(!visted_all)
	{
		visited[v] = true;		// start at some vertex
		std::stack<int> S;
		S.push(v);
		while(!S.empty())
		{
			int w = S.top();
			S.pop();
			for(int i=0; i<G->adjacency(w).size(); ++i)
			{
				int n = G->adjacency(w)[i].id;
				if(!visited[n])
				{
					S.push(n);
					index[n] = (int)S.size();	
					std::cout<<index[n] <<"\t";
				}
				else if(visited[n] && index[n]!=-1 )				// basically checks if vertex is already in the stack and it being visited again then it is a loop
				{
					std::cout<<"found vertex: " <<n+1<<"\n";
					length = std::min(length, ((int)S.size() - index[n]));				
				}
			}
			visited[w] = true;
// 			std::cout<<w<<"\t";
		}
		std::cout<<"\n";	

		// reset indices
		for(int j=0; j<index.size(); ++j)
			index[j] = -1;
					
		// check if all vertices have been visited
		for(int k = 0; k<visited.size(); ++k)
		{
			if(visited[k]){
				visted_all = true;
			}
			else
			{
				visted_all = false;
				v = k;				// my vertices are int from 0-> G->V() -1
				break;
			}
		}
	}
	
	return length;
}

int main(int argc, const char* argv[])
{
	std::string filename = argv[1];
	std::cout<<"reading file: "<<filename<<std::endl;
	std::vector< std::vector<int> > vertices;
	int numVertices = 0;
	vertices = readGraph(filename,&numVertices);
	std::cout<<"number of edges: "<<vertices.size()<<std::endl;
	std::cout<<"number of vertices: "<<numVertices<<std::endl;
	
	// Let's create our graph 
	Graph * G = new Graph(numVertices);
	
	for(int i = 0; i<vertices.size(); ++i)
	{
		vertex v,w;
		v.id = vertices[i][0];
		w.id = vertices[i][1];		
		v.dist = -1;
		w.dist = -1;
		//G->addEdge(v,w);
		G->addEdgeDAG(v,w);
	}
	
	std::cout<<"shortest directed cycle: "<< shortestDirectedCycle(G,4) << std::endl;
	
// 	std::cout<<"degree of 5: "<<degree(G,5)<<std::endl;
// 	std::cout<<"max degree: "<<maxDegree(G)<<std::endl;
// 	std::cout<<"average degree: "<<averageDegree(G)<<std::endl;
// 	std::vector<bool> visited;
// 	visited.resize(G->V());
// 	for(int i=0; i<G->V(); ++i)
// 		visited[i] = false;
	
// 	recursiveDfs(G,4,visited);
// 	std::cout<<"\n";
// 	for(int i=0; i<G->V(); ++i)
// 		visited[i] = false;
// 	G->printDist();
// 	bfs(G,4,visited);
// 	G->printDist();
// 	
// 	std::cout<<"Graph diameter: "<< diameter(G) << std::endl;
	
// 	for(int i=0; i<G->V(); ++i)
// 		visited[i] = false;	
// 	dfs(G,4,visited);
	
	return 1;
}



