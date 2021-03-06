#include "airportGraph.h"

const Vertex Graph::InvalidVertex = "_SAFECOVIDINVALIDVERTEX";
const int Graph::InvalidWeight = INT_MIN;
const string Graph:: InvalidLabel = "_SAFECOVIDINVALIDLABEL";
const Edge Graph::InvalidEdge = Edge(Graph::InvalidVertex, Graph::InvalidVertex, Graph::InvalidWeight, Graph::InvalidLabel);

/**
 * Constructor to create an empty graph.
 * @param weighted - specifies whether the graph is a weighted graph or
 *  not
 */
Graph::Graph(bool weighted) : weighted(weighted),directed(false)
{
}

/**
 * Constructor to create an empty graph.
 * @param weighted - specifies whether the graph is a weighted graph or
 *  not
 * @param directed - specifies whether the graph is directed
 */
Graph::Graph(bool weighted, bool directed) : weighted(weighted),directed(directed)
{
}

/**
 * Gets all adjacent vertices to the parameter vertex.
 * @param source - vertex to get neighbors from
 * @return a vector of vertices
 */
vector<Vertex> Graph::getAdjacent(Vertex source) const
{
    auto lookup = adjacency_list.find(source);

    if(lookup == adjacency_list.end())
        return vector<Vertex>();

    else
    {
        vector<Vertex> vertex_list;
        unordered_map <Vertex, Edge> & map = adjacency_list[source];
        for (auto it = map.begin(); it != map.end(); it++)
        {
            vertex_list.push_back(it->first);
        }
        return vertex_list;
    }
}

/**
 * Returns one vertex in the graph. This function can be used
 *  to find a random vertex with which to start a traversal.
 * @return a vertex from the graph
 */
Vertex Graph::getStartingVertex() const
{
    return adjacency_list.begin()->first;
}

/**
 * Gets all vertices in the graph.
 * @return a vector of all vertices in the graph
 */
vector<Vertex> Graph::getVertices() const
{
    vector<Vertex> ret;

    for(auto it = adjacency_list.begin(); it != adjacency_list.end(); it++)
    {
        ret.push_back(it->first);
    }

    return ret;
}

/**
 * Gets an edge between two vertices.
 * @param source - one vertex the edge is connected to
 * @param destination - the other vertex the edge is connected to
 * @return - if exist, return the corresponding edge
 *         - if edge doesn't exist, return Edge()
 */
Edge Graph::getEdge(Vertex source , Vertex destination) const
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return Edge();
    Edge ret = adjacency_list[source][destination];
    return ret;
}

/**
 * Gets all the edges in the graph.
 * @return a vector of all the edges in the graph
 */
vector<Edge> Graph::getEdges() const
{
    if (adjacency_list.empty())
        return vector<Edge>();

    vector<Edge> ret;
    set<pair<Vertex, Vertex>> seen;

    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); it++)
    {
        Vertex source = it->first;
        for (auto its = adjacency_list[source].begin(); its != adjacency_list[source].end(); its++)
        {
            Vertex destination = its->first;
            if(seen.find(make_pair(source, destination)) == seen.end())
            {
                //this pair is never added to seen
                ret.push_back(its->second);
                seen.insert(make_pair(source,destination));
                if(!directed)
                {
                    seen.insert(make_pair(destination, source));
                }
            }
        }
    }

    return ret;
}

/**
 * Checks if the given vertex exists.
 * @return - if Vertex exists, true
 *         - if Vertex doesn't exist, return false
 */
bool Graph::vertexExists(Vertex v) const
{
    return assertVertexExists(v, "");
}

/**
 * Checks if edge exists between two vertices exists.
 * @return - if Edge exists, true
 *         - if Edge doesn't exist, return false
 */
bool Graph::edgeExists(Vertex source, Vertex destination) const
{
    return assertEdgeExists(source, destination, "");
}

/**
 * Sets the edge label of the edge between vertices u and v.
 * @param source - one vertex the edge is connected to
 * @param destination - the other vertex the edge is connected to
 * @return - if edge exists, set the label to the corresponding edge(if not directed, set the reverse one too), return edge with new label
 *         - if edge doesn't exist, return InvalidEdge
 */
Edge Graph::setEdgeLabel(Vertex source, Vertex destination, string label)
{
    if (assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    Edge new_edge(source, destination, e.getWeight(), label);
    adjacency_list[source][destination] = new_edge;

    if(!directed)
    {
        Edge new_edge_reverse(destination,source, e.getWeight(), label);
        adjacency_list[destination][source] = new_edge_reverse;
    }
    return new_edge;
}

/**
 * Gets the edge label of the edge between vertices u and v.
 * @param source - one vertex the edge is connected to
 * @param destination - the other vertex the edge is connected to
 * @return - if edge exists, return edge label
 *         - if edge doesn't exist, return InvalidLabel
 */
string Graph::getEdgeLabel(Vertex source, Vertex destination) const
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidLabel;
    return adjacency_list[source][destination].getLabel();
}

/**
 * Gets the weight of the edge between two vertices.
 * @param source - one vertex the edge is connected to
 * @param destination - the other vertex the edge is connected to
 * @return - if edge exists, return edge wright
 *         - if doesn't, return InvalidWeight
 */
double Graph::getEdgeWeight(Vertex source, Vertex destination) const
{
    if (!weighted)
        error("can't get edge weights on non-weighted graphs!");

    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidWeight;
    return adjacency_list[source][destination].getWeight();
}

/**
 * Inserts a new vertex into the graph and initializes its label as "".
 * @param v - the name for the vertex
 */
void Graph::insertVertex(Vertex v)
{
    // will overwrite if old stuff was there
    removeVertex(v);
    // make it empty again
    adjacency_list[v] = unordered_map<Vertex, Edge>();
}

/**
 * Removes a given vertex from the graph.
 * @param v - the vertex to remove
 * @return - if v exists, return v
 *         - if not, return InvalidVertex;
 */
Vertex Graph::removeVertex(Vertex v)
{

    if (adjacency_list.find(v) != adjacency_list.end())
    {
        if(!directed){
            for (auto it = adjacency_list[v].begin(); it != adjacency_list[v].end(); it++)
            {
                Vertex u = it->first;
                adjacency_list[u].erase(v);
            }
            adjacency_list.erase(v);
            return v;
        }

        adjacency_list.erase(v);
        for(auto it2 = adjacency_list.begin(); it2 != adjacency_list.end(); it2++)
        {
            Vertex u = it2->first;
            if (it2->second.find(v)!=it2->second.end())
            {
                it2->second.erase(v);
            }
        }
        return v;
    }

    return InvalidVertex;
}

/**
 * Inserts an edge between two vertices.
 * A boolean is returned for use with the random graph generation.
 * Hence, an error is not thrown when it fails to insert an edge.
 * @param source - one vertex the edge is connected to
 * @param destination - the other vertex the edge is connected to
 * @return whether inserting the edge was successful
 */
bool Graph::insertEdge(Vertex source, Vertex destination)
{
    if(adjacency_list.find(source)!= adjacency_list.end()
    && adjacency_list[source].find(destination)!= adjacency_list[source].end())
    {
        //edge already exists
        return false;
    }

    if(adjacency_list.find(source)==adjacency_list.end())
    {
        adjacency_list[source] = unordered_map<Vertex, Edge>();
    }
        //source vertex exists
    adjacency_list[source][destination] = Edge(source, destination);
    if(!directed)
    {
        if(adjacency_list.find(destination)== adjacency_list.end())
        {
            adjacency_list[destination] = unordered_map<Vertex, Edge>();
        }
        adjacency_list[destination][source] = Edge(source, destination);
    }

    return true;
}

/**
 * Removes the edge between two vertices.
 * @param source - one vertex the edge is connected to
 * @param destination - the other vertex the edge is connected to
 * @return - if edge exists, remove it and return removed edge
 *         - if not, return InvalidEdge
 */
Edge Graph::removeEdge(Vertex source, Vertex destination)
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    adjacency_list[source].erase(destination);
    // if undirected, remove the corresponding edge
    if(!directed)
    {
        adjacency_list[destination].erase(source);
    }
    return e;
}

/**
 * Sets the weight of the edge between two vertices.
 * @param source - one vertex the edge is connected to
 * @param destination - the other vertex the edge is connected to
 * @param weight - the weight to set to the edge
 * @return - if edge exists, set edge weight and return  edge with new weight
 *         - if not, return InvalidEdge
 */
Edge Graph::setEdgeWeight(Vertex source, Vertex destination, double weight)
{
    if (assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    //std::cout << "setting weight: " << weight << std::endl;
    Edge new_edge(source, destination, weight, e.getLabel());
    adjacency_list[source][destination] = new_edge;

    if(!directed)
        {
            Edge new_edge_reverse(destination,source, weight, e.getLabel());
            adjacency_list[destination][source] = new_edge_reverse;
        }

    return new_edge;
}

/**
 * Returns whether a given vertex exists in the graph.
 * @param v - the vertex to check
 * @param functionName - the name of the calling function to return
 *  in the event of an error
 */
bool Graph::assertVertexExists(Vertex v, string functionName) const
{
    if (adjacency_list.find(v) == adjacency_list.end())
    {
        if (functionName != "")
            error(functionName + " called on nonexistent vertices");
        return false;
    }
    return true;
}

/**
 * Returns whether the edge exists in the graph.
 * @param source - one vertex
 * @param destination - another vertex
 * @param functionName - the name of the calling function to return
 *  in the event of an error
 */
bool Graph::assertEdgeExists(Vertex source, Vertex destination, string functionName) const
{
    if(assertVertexExists(source,functionName) == false)
        return false;
    if(adjacency_list[source].find(destination)== adjacency_list[source].end())
    {
        if (functionName != "")
            error(functionName + " called on nonexistent edge " + source + " -> " + destination);
        return false;
    }

    if(!directed)
    {
        if (assertVertexExists(destination,functionName) == false)
            return false;
        if(adjacency_list[destination].find(source)== adjacency_list[destination].end())
        {
            if (functionName != "")
                error(functionName + " called on nonexistent edge " + destination + " -> " + source);
            return false;
        }
    }
    return true;
}


bool Graph::isDirected() const
{
    return directed;
}


void Graph::clear()
{
    adjacency_list.clear();
}


/**
 * Prints a graph error and quits the program.
 * The program is exited with a segfault to provide a stack trace.
 * @param message - the error message that is printed
 */
void Graph::error(string message) const
{
    cerr << "\033[1;31m[Graph Error]\033[0m " + message << endl;
}

/**
 * Creates a name for snapshots of the graph.
 * @param title - the name to save the snapshots as
 */
void Graph::initSnapshot(string title)
{
    picNum = 0;
    picName = title;
}

/**
 * Saves a snapshot of the graph to file.
 * initSnapshot() must be run first.
 */
void Graph::snapshot()
{
    std::stringstream ss;
    ss << picNum;
    string newName = picName + ss.str();
    savePNG(newName);
    ++picNum;
}

/**
 * Prints the graph to stdout.
 */
void Graph::print() const
{
    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); ++it)
    {
        cout << it->first << endl;
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
        {
            std::stringstream ss;
            ss << it2->first;
            string vertexColumn = "    => " + ss.str();
            vertexColumn += " " ;
            cout << std::left << std::setw(26) << vertexColumn;
            string edgeColumn = "edge label = \"" + it2->second.getLabel()+ "\"";
            cout << std::left << std::setw(26) << edgeColumn;
            if (weighted)
                cout << "weight = " << it2->second.getWeight();
            cout << endl;
        }
        cout << endl;
    }
}

/**
 * Saves the graph as a PNG image.
 * @param title - the filename of the PNG image
 */
void Graph::savePNG(string title) const
{
    std::ofstream neatoFile;
    string filename = "images/" + title + ".dot";
    neatoFile.open(filename.c_str());

    if (!neatoFile.good())
        error("couldn't create " + filename + ".dot");

    neatoFile
        << "strict graph G {\n"
        << "\toverlap=\"false\";\n"
        << "\tdpi=\"1300\";\n"
        << "\tsep=\"1.5\";\n"
        << "\tnode [fixedsize=\"true\", shape=\"circle\", fontsize=\"7.0\"];\n"
        << "\tedge [penwidth=\"1.5\", fontsize=\"7.0\"];\n";

    vector<Vertex> allv = getVertices();
    //lambda expression
    sort(allv.begin(), allv.end(), [](const Vertex& lhs, const Vertex& rhs) {
        return stoi(lhs.substr(3)) > stoi(rhs.substr(3));
    });

    int xpos1 = 100;
    int xpos2 = 100;
    int xpos, ypos;
    for (auto it : allv) {
        string current = it;
        neatoFile
            << "\t\""
            << current
            << "\"";
        if (current[1] == '1') {
            ypos = 100;
            xpos = xpos1;
            xpos1 += 100;
        }
        else {
            ypos = 200;
            xpos = xpos2;
            xpos2 += 100;
        }
        neatoFile << "[pos=\""<< xpos << "," << ypos <<"\"]";
        neatoFile << ";\n";
    }

    neatoFile << "\tedge [penwidth=\"1.5\", fontsize=\"7.0\"];\n";

    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); ++it)
    {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
        {
            string vertex1Text = it->first;
            string vertex2Text = it2->first;

            neatoFile << "\t\"" ;
            neatoFile << vertex1Text;
            neatoFile << "\" -- \"" ;
            neatoFile << vertex2Text;
            neatoFile << "\"";

            string edgeLabel = it2->second.getLabel();
            if (edgeLabel == "WIN") {
                neatoFile << "[color=\"blue\"]";
            } else if (edgeLabel == "LOSE") {
                neatoFile << "[color=\"red\"]";
            } else {
                neatoFile << "[color=\"grey\"]";
            }
            if (weighted && it2->second.getWeight() != -1)
                neatoFile << "[label=\"" << it2->second.getWeight() << "\"]";

            neatoFile<< "[constraint = \"false\"]" << ";\n";
        }
    }

    neatoFile << "}";
    neatoFile.close();
    string command = "neato -n -Tpng " + filename + " -o " + "images/" + title
                     + ".png 2> /dev/null";
    int result = system(command.c_str());


    if (result == 0) {
        cout << "Output graph saved as images/" << title << ".png" << endl;
    } else {
        cout << "Failed to generate visual output graph using `neato`. Install `graphviz` or `neato` to generate a visual graph." << endl;
    }

    string rmCommand = "rm -f " + filename + " 2> /dev/null";
    system(rmCommand.c_str());
}
