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
    std::cout << "Printing vertices" << std::endl;
    for (int i = 0; i < this->vertexList.size(); i++) {
        std::cout << this->vertexList[i].name << std::endl;
        for (int j = 0; j < this->vertexList[i].edgeCount; j++) {
            std::cout << this->vertexList[i].edgeIds[j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Printed vertices." << std::endl;
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

int Graph::getVertexId(const std::string &vertexName) const {
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

GraphEdge *Graph::getEdge(const int &vertexId1, const int &vertexId2) {
    for (int i = 0; i < this->edgeList.size(); i++) {
        int v1 = this->edgeList[i].vertexId0;
        int v2 = this->edgeList[i].vertexId1;
        if (v1 == vertexId1 or v1 == vertexId2) {
            if (v2 == vertexId1 or v2 == vertexId2)
                return this->getEdge(i);
        }
    }
    return NULL;
}

GraphEdge Graph::getEdgeFromVertexIds(const int &vertexId1, const int &vertexId2) {
    GraphEdge result;
    for (int i = 0; i < this->edgeList.size(); i++) {
        int v1 = this->edgeList[i].vertexId0;
        int v2 = this->edgeList[i].vertexId1;
        if (v1 == vertexId1 or v1 == vertexId2) {
            if (v2 == vertexId1 or v2 == vertexId2)
                result = this->edgeList[i];
        }
    }
    return result;
}

int Graph::getEdgeId(const int &vertexId1, const int &vertexId2) const {
    for (int i = 0; i < this->edgeList.size(); i++) {
        int v1 = this->edgeList[i].vertexId0;
        int v2 = this->edgeList[i].vertexId1;
        if (v1 == vertexId1 or v1 == vertexId2) {
            if (v2 == vertexId1 or v2 == vertexId2)
                return i;
        }
    }
    return -1;
}

int Graph::getEdgeId(const StringPair &vertexNames) const {
    int v1_id = this->getVertexId(vertexNames.s0);
    int v2_id = this->getVertexId(vertexNames.s1);
    return this->getEdgeId(v1_id, v2_id);
}

std::vector<int> Graph::getNeighbors(const int &vertexId) {
    if (vertexId == -1)
        throw VertexNotFoundException();
    std::vector<int> result;
    GraphVertex *vertex = this->getVertex(vertexId);
    for (int i = 0; i < vertex->edgeCount; i++)
        result.push_back(vertex->edgeIds[i]);
    return result;
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
    int source_id = this->getVertexId(from);
    int target_id = this->getVertexId(to);

    if (source_id == -1 or target_id == -1)
        throw VertexNotFoundException();

    // Initializing path table & pq
    std::priority_queue<DistanceVertexIdPair> pq;
    DistanceVertexIdPair start_entry = DistanceVertexIdPair(source_id, 0);
    pq.push(start_entry);

    std::vector<int> dist;
    std::vector<int> prev;
    std::vector<bool> visited;

    for (int i = 0; i < this->vertexList.size(); i++) {
        if (i == source_id) 
            dist.push_back(0);
        else 
            dist.push_back(LARGE_NUMBER);
        visited.push_back(false);
        prev.push_back(-1);
    }

    while (!pq.empty()) {
        DistanceVertexIdPair dv_pair = pq.top(); pq.pop();
        int u_id = dv_pair.vId;
        GraphVertex u = this->vertexList[u_id];
        for (int e = 0; e < u.edgeCount; e++) {
            int e_id = u.edgeIds[e];
            GraphEdge edge = this->edgeList[e_id];
            int v_id = (edge.vertexId0 == u_id) ? edge.vertexId1 : edge.vertexId0;
            if (visited[v_id] or edge.masked) 
                continue;
            int alt = dist[u_id] + edge.weight;
            if (alt < dist[v_id]) {
                dist[v_id] = alt;
                prev[v_id] = u_id;
                DistanceVertexIdPair entry = DistanceVertexIdPair(v_id, alt);
                pq.push(entry);
            }
        }
        visited[u_id] = true;
    }

    int prev_vertex_id = target_id;
    while (prev_vertex_id != -1) {
        orderedVertexIdList.insert(orderedVertexIdList.begin(), prev_vertex_id);
        prev_vertex_id = prev[prev_vertex_id];
    }

    return true;
}

int Graph::MultipleShortPaths(std::vector<std::vector<int> >& orderedVertexIdList,
                              const std::string& from,
                              const std::string& to,
                              int numberOfShortestPaths)
{
    this->UnMaskAllEdges();
    bool shortest_path_exists;
    std::vector<std::vector<int> > n_shortest_paths;
    std::vector<int> current_shortest_path;
    shortest_path_exists = this->ShortestPath(current_shortest_path, from, to);
    orderedVertexIdList.push_back(current_shortest_path);

    int i = 1;
    while (i < numberOfShortestPaths && shortest_path_exists) {
        // Mask the highest weighted edge on the last found path
        std::pair<int, int> highest_weighted_edge(-1, 0);
        for (int j = 0; j < current_shortest_path.size() - 1; j++) {
            int u_id = current_shortest_path[j];
            int v_id = current_shortest_path[j+1];
            int e_id = this->getEdgeId(u_id, v_id);
            int current_weight = this->edgeList[e_id].weight;
            if (highest_weighted_edge.second < current_weight) {
                highest_weighted_edge.first = e_id;
                highest_weighted_edge.second = current_weight;
            }
        }
        this->edgeList[highest_weighted_edge.first].masked = true;

        current_shortest_path.clear();
        shortest_path_exists = this->ShortestPath(current_shortest_path, from, to);
        orderedVertexIdList.push_back(current_shortest_path);
        i++;
    }

    this->UnMaskAllEdges();
    return orderedVertexIdList.size();
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

    if (v0 and v1) {
        GraphEdge *edge = this->getEdge(v0->name, v1->name);
        if (edge != NULL)
            edge->weight = newWeight;
    }
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
    if (orderedVertexIdList.size() == 0)
        return 0;

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