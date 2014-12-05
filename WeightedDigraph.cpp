/*
 * A definition of a weighted digraph
 * Completed by Michael H. Wright
 */

#include "WeightedDigraph.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <sstream>
#include <limits>
#include <unordered_map>

using namespace std;

/**
 * Constructs the digraph from a file.
 * You may add any additional construction to this section.
 */
WeightedDigraph::WeightedDigraph(const string& filename) : numVertices(0), numArcs(0) {
	ifstream in(filename);
	if(!in.is_open()) {
		cerr << "cannot open file!" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	string line;
	getline(in, line);
	istringstream vertexStream(line);
	vertexStream >> numVertices;
	
  // Data structures for constructing bool matrix

  // Iterate through length of list, insert "false" into vector of bools
  // that signal whether or not path is visited
  for (auto itr = 0; itr != numVertices; itr++)
  {
    boolVec.push_back(0);
  }

  // Iterate through length and insert "false" lists into matrix
  for (auto itr = 0; itr != numVertices; itr++)
  {
    boolMatrix.push_back(boolVec);
  }

  // Iterate through length and insert "false" lists into matrix
  for (auto itr = 0; itr != numVertices; itr++)
  {
    pathMaps.push_back(emptyMap);
  }

  while(getline(in,line)) {
    istringstream iss(line);
    int u, v;
    float weight;
    iss >> u >> v >> weight;
    InsertArc(u, v, weight);
  }
}

/**
 * Destructor
 * You can do any needed cleanup here.
 */
WeightedDigraph::~WeightedDigraph() {
  // Intentionally left empty
  // You may do any needed cleanup here
}

/**
 * Inserts a weighted arc into the digraph.
 * This is the sole mutator of this class and it is private
 * so the digraph is immutable once created.
 */
void WeightedDigraph::InsertArc(int from, int to, double weight) {
  boolMatrix[from][to] = 1;      
  //DEBUG 
  cout << "From the bool Matrix: " << boolMatrix[from][to] << endl;
  for (auto elem : boolMatrix)
  {
    for (auto thing : elem)
      cout << thing << ' ';
    cout << endl;
  }
  std::pair<int, double> weightedPath (to, weight);
  pathMaps[from].insert (weightedPath);

  numArcs++;
}

/**
 * Finds the number of arcs leading out of the given vertex
 */
int WeightedDigraph::GetOutDegree(int vertex) const { 
  int outDegree = 0;
  vector<bool> vertexPaths = boolMatrix[vertex];
  for (auto elem : vertexPaths)
  {
    if (elem)
      outDegree++;
  }
  return outDegree;
}

/**
 * Finds the weight of the arc between the two vertices
 * Returns infinity if there is no such arc
 */
double WeightedDigraph::GetArcWeight(int from, int to) const {
  if (boolMatrix[from][to])
  {
  auto found = pathMaps[from].find(to);
  double arcWeight = found->second;
  return arcWeight;
  }

  else
    return numeric_limits<double>::infinity();
}

/**
 * Finds the sum weight of the given path.
 * Returns infinity if the path is broken.
 */
double WeightedDigraph::GetPathWeight(const list<int> & path) const {
  // TODO
  double cumWeight = 0;
  for (auto elem = path.begin(); elem != path.end(); elem++)
  {
    cumWeight += *elem;
  }
  return numeric_limits<double>::infinity();;
}

/**
 * Checks whether an arc exists between two vertices.
 */
bool WeightedDigraph::AreConnected(int from, int to) const {
  auto found = pathMaps[from].find(to); 
  if (found != pathMaps[from].end())
  {
    return true;
  }

  else if (from == to)
  { 
    return true;
  }

  else if (pathMaps[from].size() == 0)
    return false;

  else
    return false;
}

/**
 * Determines whether a path between the two vertices exists.
 */
bool WeightedDigraph::DoesPathExist(int from, int to) const {
  bool *visited = new bool[numVertices];
  int head = from, tail = to;
  std::unordered_map<int, double> availablePaths = pathMaps[head];

  cout << "Entering DPE for " << from << ':' << to << ". Checking boolMatrix for presense. boolMatrix[from][to] = " << boolMatrix[from][to] << "." << endl;

  // Check whether the two verticies are connected
  if (AreConnected(from, to))
  {
    return true;
  }

  else
  {
    //You can use either DFS or BFS approach
    int startNode = from;

    for(auto i = 0; i != numVertices; i++)
    {
      visited[i] = false;
    }

    // Queue for list
    std::list<int> queue;

    // Visit start and add it to queue
    visited[startNode] = true;
    queue.push_back(startNode);

    while ( ! queue.empty() )
    {
      // Dequeue a vertex and print it
      startNode = queue.front();
      cout << "The start node is: " << startNode << ". ";
      queue.pop_front();

      for(auto iter = pathMaps[startNode].begin(); iter != pathMaps[startNode].end(); ++iter)
      {
        cout << "Looking at startNode: " << startNode << ". ";
        if (AreConnected(startNode, to))
        {
          return true;
        }

        else if(pathMaps[startNode].size() == 0)
        {
          return false;
        }

        else if (! visited[iter->first])
        {
          visited[iter->first] = true;
          queue.push_back(iter->first);
        }
        // if the node has already been visited, end the search 
        else if (visited[iter->first])
        {
          return false;
        }
      }
    }
  }
}



/**
 * Checks whether the given path goes over existing arcs.
 */
bool WeightedDigraph::IsPathValid(const list<int> & path) const {
  // TODO
  return false;//(DoesPathExist(*path.begin(), *path.end()));
}

/**
 * Finds a path of minimum weight between the two nodes.
 * The behavior is undefined if no such path exists
 * (you may assume that such a path does exist).
 */
list<int> WeightedDigraph::FindMinimumWeightedPath(int from, int to) const {
  vector<int> previous;
  vector<double> minDistance;
  
  const double maxWeight = std::numeric_limits<double>::infinity();
  minDistance.clear();
  minDistance.resize(numVertices, maxWeight);
  minDistance[from] = 0;
  previous.clear();
  previous.resize(numVertices, -1);

  std::set<std::pair<int, double> > vertexQueue;
  vertexQueue.insert(std::make_pair(from, minDistance[from]));

  while (! vertexQueue.empty() )
  {
    auto distance = vertexQueue.begin()->second;
    auto u = vertexQueue.begin()->first;
    vertexQueue.erase(vertexQueue.begin());
    auto neighbors = pathMaps[u];
    for ( auto i = neighbors.begin(); i != neighbors.end(); i++)
    {
      auto v = i->first;
      auto weight = i->second;
      auto distanceThroughU = distance + weight;
      if (distanceThroughU < minDistance[v])
      {
        vertexQueue.erase(std::make_pair(v, minDistance[v]));
        minDistance[v] = distanceThroughU;
        previous[v] = u;
        vertexQueue.insert(std::make_pair(v, minDistance[v]));
        cout << "u:v -> " << u << ':' << v;
        cout << endl;
      }
    }
  }
  std::list<int> path;
  auto vertex = to;
  path.push_front(to);
  bool foundPath = false;
  while (! foundPath)
  {
    vertex = previous[vertex];
    path.push_front(vertex);
    if (vertex == from)
      foundPath = true;
  }
  for (auto elem : previous)
    cout << elem << ',';
  cout << endl;
  return path;
}
