#pragma once
#include "airportGraph.h"
#include "person.h"
#include "heap.h"
#include <string>
#include <unordered_map>
#include <queue>

class safeCovid
{
    public:
      /**
      * Constructor that takes in a file to initialize graph
      * This will use a default Person instead of user-provided information
      * @param filename the name of the input file to establish vertices/edges
      */
      safeCovid(const std::string& filename);

      /**
      * Constructor that takes in a file to initialize graph
      * This will use custom Person generated by having a provided age
      * @param filename - Name of the input file to establish vertices/edges
      */
      safeCovid(const std::string& filename, person pers);


      /**
      * Return the graph of airports and flight paths
      * @return - airports and flight paths graph
      */
      Graph getAirportGraph();

      /**
      * Return the person object associated with each run
      * @return - person object for this specific run
      */
      person getPerson();

      /**
      * Set the person object associated with each run
      * @param age - age of the person
      */
      void setPerson(float age);


      /**
      * Generates all vertices based on airport data
      * @param filename - Name of the input file to establish vertices/edges
      */
      void initializeVertices(const std::string& filename);

      /**
      * Generates all edges based on airport data
      * @param filename - Name of the input file to establish vertices/edges
      */
      void initializeEdges(const std::string& filename);

      /**
      * Create labels for the edge that includes its start and end airport.
      */
      void initializeLabels();

      /**
      * Based on how COVID rates change between each airport,
      * the edge weight reflects the magnitude of this change.
      * A high positive weight indicates a strong increase in COVID rates,
      * a low negative weight indicates a small decrease in COVID rates
      */
      void initializeWeights();


      /**
      * Initializes a BFS traversal beginning at the starting location.
      * Without using weights, this will determine the quickest paths
      * to each airport from the starting location.
      * @param v - Vertex that indicated the airport where traversal begins.
      */
      void BFSstart(Vertex v);

      /**
      * Helper function for the BFS traversal.
      * This will check edges to determine where the traversal
      * has already gone, as well as update labels to ensure
      * which are discovery and cross edges in the graph.
      * @param v - Vertex that indicated the airport where traversal begins.
      */
      void BFS(Vertex v);


      /**
      * Uses a BFS to determine the quickest path from a starting location
      * to an end location. This does not take COVID rates into account
      * and provides purely the shortest path.
      * @param s - The starting airport
      * @param d - The destination airport
      * @return - vector where each entry is the IATA code for each airport along the path.
      */
      vector<std::string> getPathBFS(Vertex s, Vertex d);

      /**
      * Prints the result from the shortest path determined by a BFS traversal.
      * @param s - Starting airport
      * @param d - Destination airport
      */
      void printPathBFS(Vertex s, Vertex d);


      /**
      * Uses a BFS to determine the quickest path from a starting location
      * to an end location with a landmark that must be included.
      * This does not take COVID rates into account and provides purely the shortest path.
      * @param start - Starting airport
      * @param landmark - Landmark airport to visit along the way
      * @param destination - Destination airport
      * @return - vector where each entry is the IATA code for each airport along the path.
      */
      vector<std::string> getPathLandmarkBFS(Vertex start, Vertex landmark, Vertex destination);

      /**
      * Prints the result from the shortest path with a landmark determined by a BFS traversal.
      * @param start - Starting airport
      * @param landmark - Landmark airport to visit along the way
      * @param destination - Destination airport
      */
      void printLandmarkPathBFS(Vertex start, Vertex landmark, Vertex destination);


      /**
      * Generates a Single Source Shortest Path (SSSP) from a given vertex using Dijkstra's algorithm.
      * This will take the edge weights into account when traversing.
      * @param start - The vertex/airport to start from
      */
      void DijkstraSSSP(Vertex start);

      /**
      * Uses Dijkstra's algorithm to determine the safest path from a starting location
      * to an end location. This takes COVID rates into account and
      * provides the optimal path.
      * @param s - The starting airport
      * @param d - The destination airport
      * @return - vector where each entry is the IATA code for each airport along the path.
      */
      vector<std::string> getPathDijkstra(Vertex s, Vertex d);

      /**
      * Prints the result from the safest path determined by Dijkstra's algorithm.
      * @param start - Starting airport
      * @param dest - Destination airport
      */
      void printPathDijkstra(Vertex start, Vertex dest);

      /**
      * Uses Dijkstra's algorithm to determine the safest path from a starting location
      * to an end location. This does not take COVID rates into account and
      * provides purely the shortest path.
      * @param start - The starting airport
      * @param landmark - Landmark airport to visit along the way
      * @param dest - The destination airport
      * @return - vector where each entry is the IATA code for each airport along the path.
      */
      vector<std::string> getPathLandmarkDijkstra(Vertex start, Vertex landmark, Vertex destination);

      /**
      * Prints the result from the safest path with a landmark
      * determined by Dijkstra's algorithm.
      * @param start - Starting airport
      * @param landmark - Landmark airport to visit along the way
      * @param destination - Destination airport
      */
      void printLandmarkPathDijkstra(Vertex start, Vertex landmark, Vertex destination);

    private:
      Graph airportGraph;
      person person_;
      Vertex startVertex;

      // Variables for the BFS functions
      std::unordered_map<std::string, std::string> explore_vertices;
      std::unordered_map<std::string, std::string> explore_edges;
      std::unordered_map<std::string, std::string> pred_vertex;

      // Variables for Dijkstra algorithm
      Graph dijkstraGraph;
      std::map<Vertex, Vertex> p;
      std::map<Vertex, double> d;
};