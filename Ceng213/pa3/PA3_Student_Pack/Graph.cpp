#include "Graph.h"
#include "GraphExceptions.h"

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

void Graph::InsertVertex(const std::string& vertexName)
{
    int i, size = vertexList.size();

    for(i = 0; i < size; i++) 
    {
    	if(vertexList[i].name == vertexName) throw DuplicateVertexNameException();
    }

    GraphVertex new_vertex;
    new_vertex.name = vertexName;
    new_vertex.edgeCount = 0;

    vertexList.push_back(new_vertex);
}

bool Graph::ConnectVertices(const std::string& fromVertexName,
                            const std::string& toVertexName,
                            int weight)
{
    int i, sizeVertex = vertexList.size(), sizeEdge = edgeList.size(), fromIndex, toIndex;
    bool fromVertexIN = false, toVertexIN = false;

    for(i = 0; i < sizeVertex; i++) 
    {
    	if(vertexList[i].name == fromVertexName)
    	{
    		fromVertexIN = true;
    		fromIndex = i;
    	}

    	if(vertexList[i].name == toVertexName)
    	{
    		toVertexIN = true;
    		toIndex = i;
    	}
    }

    if(!fromVertexIN || !toVertexIN) throw VertexNotFoundException();

    if(vertexList[fromIndex].edgeCount == MAX_EDGE_PER_VERTEX || vertexList[toIndex].edgeCount == MAX_EDGE_PER_VERTEX) throw TooManyEdgeOnVertexExecption();

    if(fromIndex == toIndex) return false;

    for(i = 0; i < sizeEdge; i++)
    {
    	if(edgeList[i].vertexId0 == fromIndex && edgeList[i].vertexId1 == toIndex) return false;

        if(edgeList[i].vertexId1 == fromIndex && edgeList[i].vertexId0 == toIndex) return false;
    }

    GraphEdge new_edge;
    new_edge.vertexId0 = fromIndex;
    new_edge.vertexId1 = toIndex;
    new_edge.weight = weight;
    new_edge.masked = false;

    edgeList.push_back(new_edge);

    vertexList[fromIndex].edgeIds[vertexList[fromIndex].edgeCount] = edgeList.size() - 1;
    vertexList[fromIndex].edgeCount++;


    vertexList[toIndex].edgeIds[vertexList[toIndex].edgeCount] = edgeList.size() - 1;
    vertexList[toIndex].edgeCount++;

}

bool Graph::ShortestPath(std::vector<int>& orderedVertexIdList,
                         const std::string& from,
                         const std::string& to) const
{
    int i, vSize = vertexList.size(), toIndex, fromIndex, Id1, Id2, new_dist;
    bool toExists = false, fromExists = false;
    std::vector<int> previous(vSize, -1), distance(vSize, LARGE_NUMBER);
    std::priority_queue<DistanceVertexIdPair> queue;


    for(i = 0; i < vSize; i++)
    {
        if(vertexList[i].name == to)
        {
            toExists = true;
            toIndex = i;
        }

        else if(vertexList[i].name == from)
        {
            fromExists = true;
            fromIndex = i;
        }
    }

    if(!toExists || !fromExists) throw VertexNotFoundException();

    distance[fromIndex] = 0;

    for(i = 0; i < vSize; i++)
    {
        DistanceVertexIdPair tempDVIP(i, distance[i]);
        queue.push(tempDVIP);
    }

    while(!queue.empty())
    {
        GraphVertex currV;
        Id1 = queue.top().vId;
        currV = vertexList[Id1];
        queue.pop();

        for(i = 0; i < currV.edgeCount; i++)
        {
            GraphEdge currE = edgeList[currV.edgeIds[i]];
            if(!currE.masked)
            {
                if(currE.vertexId0 == Id1) Id2 = currE.vertexId1;
                else Id2 = currE.vertexId0;

                new_dist = distance[Id1] + currE.weight;

                if(new_dist < distance[Id2])
                {
                    std::priority_queue<DistanceVertexIdPair> temp;

                    distance[Id2] = new_dist;
                    previous[Id2] = Id1;

                    while(!queue.empty())
                    {
                        if(queue.top().vId == Id2)
                        {
                            DistanceVertexIdPair tempDVIP(Id2, new_dist);
                            temp.push(tempDVIP);
                        }
                        else temp.push(queue.top());
                        
                        queue.pop();
                    }

                    queue = temp;
                }
            }
        }
    }

    if(previous[toIndex] == -1) return false;

    i = toIndex;
    while(i != -1)
    {
        orderedVertexIdList.insert(orderedVertexIdList.begin(), i);
        i = previous[i];
    }

    return true;
}

int Graph::MultipleShortPaths(std::vector<std::vector<int> >& orderedVertexIdList,
                              const std::string& from,
                              const std::string& to,
                              int numberOfShortestPaths)
{
    int i, j, vSize = vertexList.size(), toIndex, fromIndex, Id1, Id2, new_dist, numberOfPaths = 0;
    bool toExists = false, fromExists = false;
    GraphEdge *biggest, placeHolder;
    placeHolder.weight = 0;

    for(i = 0; i < vSize; i++)
    {
        if(vertexList[i].name == to)
        {
            toExists = true;
            toIndex = i;
        }

        else if(vertexList[i].name == from)
        {
            fromExists = true;
            fromIndex = i;
        }
    }

    if(!toExists || !fromExists) throw VertexNotFoundException();

    UnMaskAllEdges();

    for(j = 0; j < numberOfShortestPaths; j++)
    {
        std::vector<int> previous(vSize, -1), distance(vSize, LARGE_NUMBER), path;
        std::priority_queue<DistanceVertexIdPair> queue;
        biggest = &placeHolder;

        distance[fromIndex] = 0;

        for(i = 0; i < vSize; i++)
        {
            DistanceVertexIdPair tempDVIP(i, distance[i]);
            queue.push(tempDVIP);
        }

        while(!queue.empty())
        {
            GraphVertex currV;
            Id1 = queue.top().vId;
            currV = vertexList[Id1];
            queue.pop();

            for(i = 0; i < currV.edgeCount; i++)
            {
                GraphEdge currE = edgeList[currV.edgeIds[i]];

                if(!currE.masked)
                {
                    if(currE.vertexId0 == Id1) Id2 = currE.vertexId1;
                    else Id2 = currE.vertexId0;

                    new_dist = distance[Id1] + currE.weight;

                    if(new_dist < distance[Id2])
                    {
                        std::priority_queue<DistanceVertexIdPair> temp;

                        distance[Id2] = new_dist;
                        previous[Id2] = Id1;

                        while(!queue.empty())
                        {
                            if(queue.top().vId == Id2)
                            {
                                DistanceVertexIdPair tempDVIP(Id2, new_dist);
                                temp.push(tempDVIP);
                            }
                            else temp.push(queue.top());
                            
                            queue.pop();
                        }

                        queue = temp;
                    }
                }
            }
        }

        if(previous[toIndex] == -1) break;


        i = toIndex;
        while(i != -1)
        {
            int temp0 = i, temp1 = previous[i];
            GraphEdge tempEdge;

            path.insert(path.begin(), i);

            if(temp1 != -1)
            {
                int k;
                for(k = 0; k < edgeList.size(); k++)
                {
                    if(edgeList[k].vertexId0 == temp0 && edgeList[k].vertexId1 == temp1)
                    {
                        if(edgeList[k].weight > biggest -> weight)
                        {
                            biggest = &edgeList[k];
                            break;
                        }
                    }

                    else if(edgeList[k].vertexId0 == temp1 && edgeList[k].vertexId1 == temp0)
                    {
                        if(edgeList[k].weight > biggest -> weight)
                        {
                            biggest = &edgeList[k];
                            break;
                        }
                    }
                }
            }

            i = previous[i];
        }

        if(orderedVertexIdList.size() != 0 && orderedVertexIdList.back() == path) break;

        orderedVertexIdList.push_back(path);
        numberOfPaths++;
        biggest -> masked = true;
    }

    return numberOfPaths;
}

void Graph::MaskEdges(const std::vector<StringPair>& vertexNames)
{
    int i, j, sizeE = edgeList.size(), sizeP = vertexNames.size();
    bool edgeFound = false;

    for(i = 0; i < sizeP; i++)
    {
        for(j = 0; j < sizeE; j++)
        {
            if(vertexList[edgeList[j].vertexId0].name == vertexNames[i].s0 && vertexList[edgeList[j].vertexId1].name == vertexNames[i].s1)
            {
                edgeList[j].masked = true;
                edgeFound = true;
            }
            else if(vertexList[edgeList[j].vertexId1].name == vertexNames[i].s0 && vertexList[edgeList[j].vertexId0].name == vertexNames[i].s1)
            {
                edgeList[j].masked = true;
                edgeFound = true;
            }
        }

        if(!edgeFound) throw VertexNotFoundException();
    }
}

void Graph::UnMaskEdges(const std::vector<StringPair>& vertexNames)
{
    int i, j, sizeE = edgeList.size(), sizeP = vertexNames.size();
    bool edgeFound = false;

    for(i = 0; i < sizeP; i++)
    {
        for(j = 0; j < sizeE; j++)
        {
            if(vertexList[edgeList[j].vertexId0].name == vertexNames[i].s0 && vertexList[edgeList[j].vertexId1].name == vertexNames[i].s1)
            {
                edgeList[j].masked = false;
                edgeFound = true;
            }
            else if(vertexList[edgeList[j].vertexId1].name == vertexNames[i].s0 && vertexList[edgeList[j].vertexId0].name == vertexNames[i].s1)
            {
                edgeList[j].masked = false;
                edgeFound = true;
            }
        }

        if(!edgeFound) throw VertexNotFoundException();
    }
}

void Graph::UnMaskAllEdges()
{
    int i, size = edgeList.size();

    for(i = 0; i < size; i++) edgeList[i].masked = false;
}

void Graph::MaskVertexEdges(const std::string& name)
{
    int i, size = vertexList.size();
    GraphVertex vertex;
    bool found = false;

    for(i = 0; i < size; i++)
    {
        if(vertexList[i].name == name)
        {
            vertex = vertexList[i];
            found = true;
            break;
        }
    }

    if(!found) throw VertexNotFoundException();

    for(i = 0; i < vertex.edgeCount; i++) edgeList[vertex.edgeIds[i]].masked = true;
}

void Graph::UnMaskVertexEdges(const std::string& name)
{
    int i, size = vertexList.size();
    GraphVertex vertex;
    bool found = false;

    for(i = 0; i < size; i++)
    {
        if(vertexList[i].name == name)
        {
            vertex = vertexList[i];
            found = true;
            break;
        }
    }

    if(!found) throw VertexNotFoundException();

    for(i = 0; i < vertex.edgeCount; i++) edgeList[vertex.edgeIds[i]].masked = false;
}

void Graph::ModifyEdge(const std::string& vName0,
                       const std::string& vName1,
                       float newWeight)
{
    int i, j, size = vertexList.size();
    GraphVertex vertex0, vertex1;
    bool v1found = false, v2found = false;

    for(i = 0; i < size; i++)
    {
        if(vertexList[i].name == vName0)
        {
            vertex0 = vertexList[i];
            v1found = true;
        }

        else if(vertexList[i].name == vName1)
        {
            vertex1 = vertexList[i];
            v2found = true;
        }
    }

    if(!v1found || !v2found) throw VertexNotFoundException();

    for(i = 0 ; i < vertex0.edgeCount; i++)
    {
        for(j = 0; j < vertex1.edgeCount; j++)
            {
                if(vertex0.edgeIds[i] == vertex1.edgeIds[j]) edgeList[vertex0.edgeIds[i]].weight = newWeight;
            }
    }
}

void Graph::ModifyEdge(int vId0, int vId1,
                       float newWeight)
{
    if((vId0 < 0 || vId1 < 0) || (vId0 >= vertexList.size() || vId1 >= vertexList.size())) return;

    int i, j;
    GraphVertex vertex0 = vertexList[vId0], vertex1 = vertexList[vId1];

    for(i = 0 ; i < vertex0.edgeCount; i++)
    {
        for(j = 0; j < vertex1.edgeCount; j++)
            {
                if(vertex0.edgeIds[i] == vertex1.edgeIds[j]) edgeList[vertex0.edgeIds[i]].weight = newWeight;
            }
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
    if(vertexId < 0 || vertexId >= vertexList.size()) return "";

    return vertexList[vertexId].name;
}

int Graph::TotalWeightInBetween(std::vector<int>& orderedVertexIdList)
{
    int i, j, size = orderedVertexIdList.size(), sizeE = edgeList.size(), Index0, Index1, total = 0;
    bool edgeExists;

    for(i = 0; i < size - 1; i++)
    {
        edgeExists = false;
        Index0 = orderedVertexIdList[i];
        Index1 = orderedVertexIdList[i + 1];
        
        if(Index0 < 0 || Index1 < 0 || Index0 >= vertexList.size() || Index1 >= vertexList.size()) throw VertexNotFoundException();

        for(j = 0 ; j < sizeE; j++)
        {
            if(edgeList[j].vertexId0 == Index0 && edgeList[j].vertexId1 == Index1)
            {
                total += edgeList[j].weight;
                edgeExists = true;
                break;
            }

            else if(edgeList[j].vertexId0 == Index1 && edgeList[j].vertexId1 == Index0)
            {
                total += edgeList[j].weight;
                edgeExists = true;
                break;
            }

        }

        if(!edgeExists) return -1;
    }

    return total;
}