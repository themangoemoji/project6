/*
 * A definition of a weighted digraph
 * Completed by Michael H. Wright
 */

#include "WeightedDigraph.h"

#include <iostream>
#include <vector>
#include <fstream>
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
	
	// TODO : You can initialize your data structure here.

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
  // TODO
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
  // TODO
  return numeric_limits<double>::infinity();
}

/**
 * Finds the sum weight of the given path.
 * Returns infinity if the path is broken.
 */
double WeightedDigraph::GetPathWeight(const list<int> & path) const {
  // TODO
  return numeric_limits<double>::infinity();;
}

/**
 * Checks whether an arc exists between two vertices.
 */
bool WeightedDigraph::AreConnected(int from, int to) const {
  // TODO
  return false;
}

/**
 * Determines whether a path between the two vertices exists.
 */
bool WeightedDigraph::DoesPathExist(int from, int to) const {
  int head = from, tail = to;
  bool pathsExhausted = false;
  std::unordered_map<int, double> availablePaths = pathMaps[head];
  cout << "Entering DPE for " << from << ':' << to << ". Checking boolMatrix for presense. boolMatrix[from][to] = " << boolMatrix[from][to] << "." << endl;
  if (boolMatrix[from][to])
  {
    return true;
  }

  else
  {
    //traverse    
    while (! pathsExhausted)       
    {
      cout << "No direct connection, ";
      // Looking at the available paths from our head (originally 'from')
      availablePaths = pathMaps[head];
      if (availablePaths.size() != 0)
      {
        // If the 'to' is within the available paths
        
        for (auto path : availablePaths)
        {
          tail = path.first;
          cout << "Looking for new at head:tail " << head << ':' << tail << ". ";
          if (boolMatrix[tail][to])
            return true;
        }
        // otherwise, iterate again, looking through a new list
        head = tail;
        for (auto path : pathMaps[head])
        {
          cout << "Connection not in availPaths, looking at head:tail " << head << ':' << tail << '.' << endl;
          tail = path.first;
          DoesPathExist(head, to);
        }
      }
      // no paths from head, return false
      else
      {
        // Trivial
        cout << "No paths from " << head << ".";
        pathsExhausted = true;
        return false;
        break;
      }
    }
  }
  return false;
}

/**
 * Checks whether the given path goes over existing arcs.
 */
bool WeightedDigraph::IsPathValid(const list<int> & path) const {
  // TODO
  return (DoesPathExist(*path.begin(), *path.end()));
}

/**
 * Finds a path of minimum weight between the two nodes.
 * The behavior is undefined if no such path exists
 * (you may assume that such a path does exist).
 */
list<int> WeightedDigraph::FindMinimumWeightedPath(int from, int to) const {
  // TODO
  return list<int>();
}
