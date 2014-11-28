/**
 * A definition of a weighted digraph
 * used for CSE 331 Project 6.
 * Note that the digraph is immutable once created
 *
 * Written by James Daly
 * Completed by [Your Name]
 */
 
#ifndef WeightedDigraph_H
#define WeightedDigraph_H

#include<list>
#include<string>

class WeightedDigraph {
public:
	WeightedDigraph(const std::string& filename);
	~WeightedDigraph();
	
	WeightedDigraph(const WeightedDigraph&) = delete;
	WeightedDigraph& operator=(const WeightedDigraph&) = delete;
	
	int GetOrder() const { return numVertices; };
	int GetSize() const { return numArcs; };
	
	int GetOutDegree(int vertex) const;
	
	double GetArcWeight(int from, int to) const;
	double GetPathWeight(const std::list<int> & path) const;
	
	bool AreConnected(int from, int to) const;
	bool DoesPathExist(int from, int to) const;
	bool IsPathValid(const std::list<int> & path) const;
	
	std::list<int> FindMinimumWeightedPath(int from, int to) const;
	
private:
	int numVertices;
	int numArcs;
	// Put member data here
	
	void InsertArc(int from, int to, double weight);
};


#endif