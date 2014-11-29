/**
 * A definition of a weighted digraph
 * used for CSE 331 Project 6
 * Written by James Daly
 * Completed by Michael H. Wright
 */

#include "WeightedDigraph.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>

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

  // Push back an empty iterator to our adjList so that we can index positions with vectors
  for (auto itr = 0; itr != numVertices; itr++)
  {
    nodeIters.push_back(itr->begin());
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
  cout << "From the bool Matrix: " << boolMatrix[from][to] << endl;
  //DEBUG 
  for (auto elem : boolMatrix)
  {
    for (auto thing : elem)
      cout << thing << ' ';
    cout << endl;
  }
  numArcs++;
  // TODO
}

/**
 * Finds the number of arcs leading out of the given vertex
 */
int WeightedDigraph::GetOutDegree(int vertex) const { 
  // TODO
  return 0;
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
  // Used to terminate full cycle
  bool pathFound = false;
  bool newHeadFound = false;
  list<int> currentCycle;  
  list<int> subcycle;  
  list<int>::iterator currentCycleItr;
  list<int>::iterator subcycleItr;

  // These are the indecies of the start and end of a path
  // These will also be used to set the bool values of the matrix
  int compareEnd = 99999;
  std::list<int> pathList;  

  if (boolMatrix[from][to]) 
    return true;

  // If the direct path does not exist, traverse to look for another path
  else 
  {
    while (from != to)
    {
      if (! boolMatrix[from][*nodeIters[from]])
      {
        // Add the path to the current list, 
        // set paths to true (indicates they have been traversed)
        to = *nodeIters[from];
        if (nodeIters[from] != adjList[from].end())
          subcycle.push_back(from);

        auto holdStart = *nodeIters[from]; 
        //std::advance(nodeIters[from], 1);
        if (nodeIters[from] != adjList[from].end())
          nodeIters[from]++;
        from = holdStart;
        //from = *nodeIters[tempStart];
        to = *nodeIters[from];
        compareEnd = from;

        if (compareEnd == to) 
        {
          subcycle.push_back(from);     
        }

      }
      // There was not a valid path from the start node
      else
      {
        // Increment pointer to next possible start node for next iteration through adjList
        // Do this only if the next to would not point to the end of the list
        if(nodeIters[from] != adjList[from].end())
        {
          nodeIters[from]++;
          to = *nodeIters[from];

        }
        // If the path points to the end of the list,
        // Increment head nodes (from currentCycle) until 
        // we find a successful path
        else
        {
          newHeadFound = false;
          while ( ! newHeadFound)
          {
            currentCycleItr++;
            if (to == from)
            {
              //cout << "FIN BETCH" << endl;
              pathsExhausted = true;
              from = to;
              break;
            }
            from = *currentCycleItr;
            if(nodeIters[from] != adjList[from].end())
            {
              to = *nodeIters[from];
              newHeadFound = true;
            }
            compareEnd = 999999;
            to = from; 
            // Done, bitchz
          }
        }
      }
    }// of while    
    if (from == to)
      return true;
  }
  return false;
}

/**
 * Checks whether the given path goes over existing arcs.
 */
bool WeightedDigraph::IsPathValid(const list<int> & path) const {
  // TODO
  return false;
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
