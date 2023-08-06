/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    /* Your code here! */
    /* initialize to set all to unvisited */
    for(Vertex& v : graph.getVertices()){
        graph.setVertexLabel(v, "unvisited");
    }
    for(Edge& e : graph.getEdges()){
        graph.setEdgeLabel(e.dest,e.source, "unvisited");
    }

    /* Use BFS to search for edge with minimus weight */
    int ret = -1;
    Edge Min;
    queue<Vertex> q;
    Vertex start = graph.getVertices()[0];
    graph.setVertexLabel(start, "visited");
    q.push(start);

    while(!q.empty()){
        Vertex v = q.front();
        q.pop();
        for(Vertex& v_adj : graph.getAdjacent(v)){
            if(graph.getVertexLabel(v_adj) == "unvisited" || graph.getEdgeLabel(v, v_adj) == "unvisited"){
                graph.setVertexLabel(v_adj, "visited");
                graph.setEdgeLabel(v, v_adj, "visited");
                q.push(v_adj);
                if(ret < 0 || graph.getEdgeWeight(v, v_adj) <= ret){
                    ret = graph.getEdgeWeight(v, v_adj);
                    Min = graph.getEdge(v, v_adj);
                }
            }
        }
    }
    graph.setEdgeLabel(Min.source, Min.dest, "MIN");
    return ret;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    /* Your code here! */
    /* initialize to set all to unvisited */
    for(Vertex& v : graph.getVertices()){
        graph.setVertexLabel(v, "unvisited");
    }
    for(Edge& e : graph.getEdges()){
        e.label = "unvisited";
    }
    unordered_map<Vertex, Vertex> parent;
    unordered_map<Vertex, int> distance;
    distance[start] = 0;

    /* Use BFS to find the shortest path */
    queue<Vertex> q;
    graph.setVertexLabel(start, "visited");
    q.push(start);

    while(!q.empty()){
        Vertex v = q.front();
        q.pop();
        for(Vertex& v_adj : graph.getAdjacent(v)){
            if(graph.getVertexLabel(v_adj) == "unvisited" || graph.getEdgeLabel(v, v_adj) == "unvisited"){
                graph.setVertexLabel(v_adj, "visited");
                graph.setEdgeLabel(v, v_adj, "visited");
                q.push(v_adj);
                parent[v_adj] = v;
                distance[v_adj] = distance[v] + 1;
            }
        }
    }

    /* label the MINPATH */
    Vertex v = end;
    while(v != start){
        graph.setEdgeLabel(v, parent[v], "MINPATH");
        v = parent[v];
    }

    return distance[end];
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    /* Your code here! */
    int index = 0;
    unordered_map<Vertex, int> MAP;
    for(Vertex& v : graph.getVertices()){
        MAP[v] = index++;
    }
    vector<Edge> edges = graph.getEdges();
    std::sort(edges.begin(), edges.end());

    /* use disjointsets to find the MST */
    DisjointSets MST;
    MST.addelements(graph.getVertices().size());

    unsigned ct = 0;
    while(ct < graph.getVertices().size() - 1){
        Edge edge = edges[0];
        edges.erase(edges.begin());
        if(MST.find(MAP[edge.dest]) != MST.find(MAP[edge.source])){
            graph.setEdgeLabel(edge.dest, edge.source, "MST");
            MST.setunion(MAP[edge.dest], MAP[edge.source]);
            ct++;
        }
    }
}

