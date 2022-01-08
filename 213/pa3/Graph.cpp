#include "Graph.h"
#include "GraphExceptions.h"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <queue>
#include <fstream>
#include <sstream>
#include <cstdlib>


// Literally do nothing here
// default constructors of the std::vector is enough
Graph::Graph()
{}

Graph::Graph(const std::string& filePath)
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    // Tokens
    std::string tokens[3];

    std::ifstream mapFile(filePath.c_str());
    // Read line by line
    std::string line;
    while (std::getline(mapFile, line))
    {
        // Empty Line Skip
        if(line.empty()) continue;
        // Comment Skip
        if(line[0] == '#') continue;

        // Tokenize the line
        int i = 0;
        std::istringstream stream(line);
        while(stream >> tokens[i]) i++;

        // Single token (Meaning it is a vertex)
        if(i == 1)
        {
            InsertVertex(tokens[0]);
        }
        // Exactly three tokens (Meaning it is an edge)
        else if(i == 3)
        {
            int weight = std::atoi(tokens[0].c_str());
            if(!ConnectVertices(tokens[1], tokens[2], weight))
            {
                std::cerr << "Duplicate edge on "
                          << tokens[0] << "-"
                          << tokens[1] << std::endl;
            }
        }
        else std::cerr << "Token Size Mismatch" << std::endl;
    }
}

void Graph::printVertices() {
    for (int i = 0; i < this->vertexList.size(); i++) {
        std::cout << this->vertexList[i].name << " ";
    }
    std::cout << std::endl;
}

GraphVertex *Graph::getVertex(const int &vertexId) {
    if (vertexId >= this->vertexList.size())
        return NULL;
    return &vertexList[vertexId];
}

GraphVertex *Graph::getVertex(const std::string &vertexName) {
    int vertexId = this->getVertexId(vertexName);
    if (vertexId == -1)
        return NULL;
    return &vertexList[vertexId];
}

int Graph::getVertexId(const std::string &vertexName) {
    for (int i = 0; i < this->vertexList.size(); i++) {
        if (this->vertexList[i].name == vertexName) 
            return i;
    }
    return -1;
}

GraphEdge *Graph::getEdge(const int &edgeId) {
    if (edgeId >= edgeList.size())
        return NULL;
    return &edgeList[edgeId];
}

GraphEdge *Graph::getEdge(const std::string &vertexName0, const std::string &vertexName1) {
    StringPair sp = StringPair(vertexName0, vertexName1);
    int edge_id = this->getEdgeId(sp);
    if (edge_id == -1)
        return NULL;
    return this->getEdge(edge_id);
}

int Graph::getEdgeId(const StringPair &vertexNames) {
    for (int i = 0; i < this->edgeList.size(); i++) {
        int v0 = this->edgeList[i].vertexId0;
        int v1 = this->edgeList[i].vertexId1;
        int v0_id = this->getVertexId(vertexNames.s0);
        int v1_id = this->getVertexId(vertexNames.s1);
        if (v0 == v0_id or v0 == v1_id) {
            if (v1 == v0_id or v1 == v1_id)
                return i;
        }
    }
    return -1;
}

void Graph::InsertVertex(const std::string& vertexName) {
    if (getVertex(vertexName))
        throw DuplicateVertexNameException();
    GraphVertex v;
    v.name = vertexName;
    v.edgeCount = 0;
    vertexList.push_back(v);
}

bool Graph::ConnectVertices(const std::string& fromVertexName,
                            const std::string& toVertexName,
                            int weight) {
    if (!getVertex(fromVertexName) or !getVertex(toVertexName)) 
        throw VertexNotFoundException();
    else if (fromVertexName == toVertexName)
        return false;
    else if (this->getEdge(fromVertexName, toVertexName))
        return false;

    GraphVertex *v0 = this->getVertex(fromVertexName);
    GraphVertex *v1 = this->getVertex(toVertexName);
    if (v0->edgeCount == MAX_EDGE_PER_VERTEX or v1->edgeCount == MAX_EDGE_PER_VERTEX) 
        throw TooManyEdgeOnVertexExecption();

    GraphEdge edge;
    edge.weight = weight;
    edge.masked = false;
    edge.vertexId0 = this->getVertexId(fromVertexName);
    edge.vertexId1 = this->getVertexId(toVertexName);

    int edge_id = edgeList.size();
    edgeList.push_back(edge);

    v0->edgeIds[v0->edgeCount++] = edge_id;
    v1->edgeIds[v1->edgeCount++] = edge_id;

    return true;
}

bool Graph::ShortestPath(std::vector<int>& orderedVertexIdList,
                         const std::string& from,
                         const std::string& to) const {
   /* GraphVertex *v0 = this->getVertex(from);
    GraphVertex *v1 = this->getVertex(to);

    if (!v0 or !v1)
        throw VertexNotFoundException();

    int v0_id = this->getVertexId(from);
    int v1_id = this->getVertexId(to);

    // Initializing path table
    std::vector<DistanceVertexIdPair> pathTable;
    for (int i = 0; i < this->vertexList.size(); i++) {
        if (i == v0_id)
            DistanceVertexIdPair entry = DistanceVertexIdPair(-1, 0);
        else 
            DistanceVertexIdPair entry = DistanceVertexIdPair(-1, LARGE_NUMBER);
        pathTable.push_back(entry);
    }

    std::priority_queue<DistanceVertexIdPair> pq;
    DistanceVertexIdPair start = DistanceVertexIdPair(v0_id, 0);
    pq.push(start);

    while (!pq.empty()) {
        int v_id = pq.pop();
        GraphVertex *v = this->getVertex(v_id);
        for (int i = 0; i < v->edgeCount; i++) {
            GraphEdge *edge = this->getEdge(v->edgeIds[i]);
            if (edge->masked)
                continue;
            int neighbor_id = (v_id != edge->vertexId0) ? edge->vertexId0 : edge->vertexId1;
            DistanceVertexIdPair path_to_neighbor = DistanceVertexIdPair(v_id, edge->weight);
            if (path_to_neighbor < pathTable[neighbor_id])
                pathTable[neighbor_id] = path_to_neighbor;
            DistanceVertexIdPair next = DistanceVertexIdPair(neighbor_id, edge->weight);
            pq.push(next);
            edge->masked = true;
        }
    }

    int prev = v1_id;
    while (prev != v0_id) {
        if (prev == -1) {
            orderedVertexIdList.clear();
            return false;
        }
        orderedVertexIdList.insert(orderedVertexIdList.begin(), prev);
        DistanceVertexIdPair path_to_prev = pathTable[prev];
        prev = path_to_prev.vId;
    }

    return true;*/
}

int Graph::MultipleShortPaths(std::vector<std::vector<int> >& orderedVertexIdList,
                              const std::string& from,
                              const std::string& to,
                              int numberOfShortestPaths)
{
    // TODO
}

void Graph::MaskEdges(const std::vector<StringPair>& vertexNames)
{
    for (int i = 0; i < vertexNames.size(); i++) {
        StringPair sp = vertexNames[i];
        GraphEdge* edge = this->getEdge(sp.s0, sp.s1);
        edge->masked = true;
    }
}

void Graph::UnMaskEdges(const std::vector<StringPair>& vertexNames)
{
    for (int i = 0; i < vertexNames.size(); i++) {
        StringPair sp = vertexNames[i];
        GraphEdge* edge = this->getEdge(sp.s0, sp.s1);
        edge->masked = false;
    }
}

void Graph::UnMaskAllEdges()
{
    for (int i = 0; i < edgeList.size(); i++) {
        edgeList[i].masked = false;
    }
}

void Graph::MaskVertexEdges(const std::string& name)
{
    GraphVertex *v = this->getVertex(name);
    for (int i = 0; i < v->edgeCount; i++) {
        GraphEdge *edge = this->getEdge(v->edgeIds[i]);
        edge->masked = true;
    }
}

void Graph::UnMaskVertexEdges(const std::string& name)
{
    GraphVertex *v = this->getVertex(name);
    for (int i = 0; i < v->edgeCount; i++) {
        GraphEdge *edge = this->getEdge(v->edgeIds[i]);
        edge->masked = false;
    }
}

void Graph::ModifyEdge(const std::string& vName0,
                       const std::string& vName1,
                       float newWeight)
{
    GraphVertex *v0 = this->getVertex(vName0);
    GraphVertex *v1 = this->getVertex(vName1);
    if (!v0 or !v1)
        throw VertexNotFoundException();

    GraphEdge *edge = this->getEdge(vName0, vName1);
    if (edge != NULL)
        edge->weight = newWeight;
}

void Graph::ModifyEdge(int vId0, int vId1,
                       float newWeight)
{
    GraphVertex *v0 = this->getVertex(vId0);
    GraphVertex *v1 = this->getVertex(vId1);

    if (!v0 or !v1)
        throw VertexNotFoundException();

    GraphEdge *edge = this->getEdge(v0->name, v1->name);
    if (edge != NULL)
        edge->weight = newWeight;
}

void Graph::PrintAll() const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    for(size_t i = 0; i < vertexList.size(); i++)
    {
        const GraphVertex& v = vertexList[i];
        std::cout << v.name << "\n";
        for(int j = 0; j < v.edgeCount; j++)
        {
            int edgeId = v.edgeIds[j];
            const GraphEdge& edge = edgeList[edgeId];
            // Skip printing this edge if it is masked
            if(edge.masked)
                continue;

            // List the all vertex names and weight
            std::cout << "-" << std::setfill('-')
                             << std::setw(2) << edge.weight
                             << "-> ";
            int neigVertexId = (static_cast<int>(i) == edge.vertexId0)
                                 ? edge.vertexId1
                                 : edge.vertexId0;
            std::cout << vertexList[neigVertexId].name << "\n";
        }
    }
    // Reset fill value because it "sticks" to the std out
    std::cout << std::setfill(' ');
    std::cout.flush();
}

void Graph::PrintPath(const std::vector<int>& orderedVertexIdList,
                      bool sameLine) const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this file !       //
    // ============================= //
    for(size_t i = 0; i < orderedVertexIdList.size(); i++)
    {
        int vertexId = orderedVertexIdList[i];
        if(vertexId >= static_cast<int>(vertexList.size()))
            throw VertexNotFoundException();

        const GraphVertex& vertex = vertexList[vertexId];
        std::cout << vertex.name;
        if(!sameLine) std::cout << "\n";
        // Only find and print the weight if next is available
        if(i == orderedVertexIdList.size() - 1) break;
        int nextVertexId = orderedVertexIdList[i + 1];
        if(nextVertexId >= static_cast<int>(vertexList.size()))
            throw VertexNotFoundException();

        // Find the edge between these two vertices
        int edgeId = INVALID_INDEX;
        if(vertexId     < static_cast<int>(vertexList.size()) &&
           nextVertexId < static_cast<int>(vertexList.size()))
        {
            // Check all of the edges of vertex
            // and try to find
            const GraphVertex& fromVert = vertexList[vertexId];
            for(int i = 0; i < fromVert.edgeCount; i++)
            {
                int eId = fromVert.edgeIds[i];
                // Since the graph is not directional
                // check the both ends
                if((edgeList[eId].vertexId0 == vertexId &&
                    edgeList[eId].vertexId1 == nextVertexId)
                ||
                   (edgeList[eId].vertexId0 == nextVertexId &&
                    edgeList[eId].vertexId1 == vertexId))
                {
                    edgeId = eId;
                    break;
                }
            }
        }
        if(edgeId != INVALID_INDEX)
        {
            const GraphEdge& edge = edgeList[edgeId];
            std::cout << "-" << std::setfill('-')
                      << std::setw(2)
                      << edge.weight << "->";
        }
        else
        {
            std::cout << "-##-> ";
        }
    }
    // Print endline on the last vertex if same line is set
    if(sameLine) std::cout << "\n";
    // Reset fill value because it "sticks" to the std out
    std::cout << std::setfill(' ');
    std::cout.flush();
}

int Graph::TotalVertexCount() const
{
    return vertexList.size();
}

int Graph::TotalEdgeCount() const
{
    return edgeList.size();
}

std::string Graph::VertexName(int vertexId) const
{
    return vertexList[vertexId].name;
}

int Graph::TotalWeightInBetween(std::vector<int>& orderedVertexIdList)
{
    int total = 0;
    
    for(int i = 0; i < orderedVertexIdList.size()-1; i++) {
        int id0 = orderedVertexIdList[i];
        int id1 = orderedVertexIdList[i+1];
        GraphVertex *v0 = this->getVertex(id0);
        GraphVertex *v1 = this->getVertex(id1);

        GraphEdge* edge = this->getEdge(v0->name, v1->name);
        total += edge->weight;
    }

    return total;
}