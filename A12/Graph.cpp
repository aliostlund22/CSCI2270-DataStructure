//
//  Cities.cpp
//  ZombieGraph
//
//  Copyright © 2017 Ali Ostlund. All rights reserved.
//

#include "Cities.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <limits.h> // algorithm helper

#include <iomanip>
#include <stdlib.h>
#include <queue>
#include <stack>

using namespace std;

Cities::Cities() {}
Cities::~Cities() {}


void Cities::loadCities(ifstream &dataFile){


    string input, word;
    int num = 0;

    
    if (!dataFile.is_open()) {
        cout << "file error" << endl;
        return;
    }
    
    if (getline(dataFile, input)) {  // fetch first line of cities
        istringstream line( input );
        getline (line, word, ','); // skip "cities"
        while (getline (line, word, ',')) {
            Info[cityCount].cityName = word;
            cityInfo[cityCount].district = -1;
            //cout << word << endl; // debug
            cityCount++;
        }
    }
    //cout << cityCount << endl;  // debug
    
    
    // load graph
    int i=0, ii=0;
    while (getline(dataFile, input)) {
        ii=0;
        istringstream line( input );
        getline (line, word, ','); // skip "city name"
        while (getline (line, word, ',')) {
            int dist=0;
            istringstream ( word ) >> num;
            dist = num;
            graph[i][ii] = dist;
            //cout << num << " * ";  // debug
            ii++;
        }
        i++;
        //cout << endl;  // debug
    }
    
    // printGraph();  // debug
    
    dataFile.close();

}

/* ********************************************************** */

void Cities::printGraph(){
    
    //print graph - DEBUG
    for (int x=0; x < cityCount; x++) {
        cout << cityInfo[x].district << ":" << cityInfo[x].cityName << ":";
        for (int y=0; y < cityCount; y++) {
            int val = graph[x][y];
            cout << val << " * ";
        }
        cout << endl;
    }
    for (int x=0; x < cityCount; x++) {
        cout << cityInfo[x].district << ":" << cityInfo[x].cityName << ":";
        for (int y=0; y < cityCount; y++) {
            int val = graph[x][y];
            if (val > 0) {
                cout << cityInfo[y].cityName << "(" << y << "-" << graph[x][y] << ")" << " * ";
            }
        }
        cout << endl;
    }
}



/* ********************************************************** */
// 1:Boston->Boulder**Chicago

void Cities::printVerticies(){
    
    for (int x=0; x < cityCount; x++) {
        bool iM=false;
        cout << cityInfo[x].district << ":" << cityInfo[x].cityName << "->";
        for (int y=0; y < cityCount; y++) {
            int val = graph[x][y];
            if (val > 0) {
                if (iM==true) cout << "**";
                cout << cityInfo[y].cityName;
                iM=true;
            }
        }
        cout << endl;
    }
}

/* ********************************************************** */
void Cities::printCities(){
    
    if (cityCount==0) return;
    for (int j=0; j<cityCount; j++) {
        cout << cityInfo[j].cityName << endl;
    }
}

/* ********************************************************** */
void Cities::findDistricts(){
    
    // Flood­fill approach
    
    districtCount=0;
    
    if (cityCount == 0) return;
    
    // Initialize M to be the adjacency matrix
    bool seen[cityCount]; // which vertices have been visited
    int n = cityCount; // number of vertices

    // BFS flood­fill
    for( int v=0; v<n; v++) seen[v] = false; // set all vertices to be "unvisited"
    
    //seen[s] = true;
    for (int i=0; i<cityCount; i++) {  // added loop to hit all verticies, to find any/all districts
        queue<int> q; // The BFS queue to represent the visited set
        
        if (seen[i] != true) {
            
            seen[i] = true;
        
            //DoColouring( s, some_color );
            districtCount++;
            cityInfo[i].district=districtCount;
            q.push(i);
            
            while (!q.empty()) {
                int u=q.front(); // get first un­touched vertex
                q.pop();
                for(int v=0; v<n; v++) {  //
                    if(!seen[v] && graph[u][v]>0 ) { // not seen, and an edge ( > 0 )
                        seen[v] = true;
                        //DoColouring( v, some_color );
                        cityInfo[v].district=districtCount;
                        q.push(v);
                    }
                }
            }
        }
    }
    
    // print districts
    //cout << "city district count" << districtCount << endl;
    for (int j=0; j<cityCount; j++) {
        cout << cityInfo[j].cityName << ":" << cityInfo[j].district << endl;
    }
}

// A C / C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph
// http://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/



// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree

int Cities::minDistance(int dist[], bool sptSet[])
{
    int V=cityCount;
    
    // Initialize min value
    int min = INT_MAX, min_index=0;
    
    for (int v = 0; v < V; v++) {
        if (sptSet[v] == false && dist[v] <= min) {
            min = dist[v], min_index = v;
        }
    }
    return min_index;
}


/* ********************************************************** */

void Cities::findShortestPath(string &city1, string &city2) {

   //  Shortest path in unweighted graph

    int colour[128]; // 0 is white, 1 is gray and 2 is black
    int d[128]; // d[v] is the distance from source to v
    int pi[128]; // pi[v] is the parent of v in the shortest path from source to v
    int n=cityCount; // number of vertices

    // ... Initialize M to be the adjacency matrix
    queue<int> q;
    stack<int> q2; // The BFS queue to represent the visited set
    
    int iCity1 = findCityIndex (city1);  // return
    int iCity2 = findCityIndex (city2);  // return

    int s=iCity1; // the source vertex
    
    if (cityCount==0) return;
    
    if ((iCity1 < 0) || (iCity2 < 0)) {
        cout << "Error ---> invalid city name - case sensitive" << endl;
        printCities();
        return;
    }
    
    if (cityInfo[iCity1].district != cityInfo[iCity2].district) {
        cout << "No safe path between cities" << endl;
        return;
    }
    
    // BFS shortest­path
    const int Inf=INT_MAX; // Infinity!!
    for(int v=0; v<n; v++) {
        colour[v]= 0; // set all vertices to be "unvisited"
        d[v]=Inf; // distance is Infinity initially, meaning "cannot be reached"
        pi[v]=1; // ­1 is not a vertex, meaning "no parent so far"
    }
    
    // Initializing properties of the source vertex
    colour[s]=1;
    d[s]=0; // distance from s to itself is 0
    pi[s]=1;  // no parent for source vertex
    
    q.push(s);
    while (!q.empty()) {
        int u=q.front(); // get first un­touched vertex
        q.pop();
    
        for(int v=0; v<n; v++) {
            if(colour[v]==0 && graph[u][v]>0) { // (u,v) is edge, v is white
                colour[v]=1;
                d[v]=d[u]+1; // one more edge used, increment distance by 1
                pi[v]=u; // using edge (u,v), so parent of v is u
                q.push(v);
            }
        }
        colour[u]=2;
    }
    //for (int i=0; i<cityCount; i++) {
    //    cout << i << " " << colour[i] << " " << d[i] << " " << pi[i] << endl;
    //}
    
    // build path  - d is hops to source, pi is parent
    int parent = pi[iCity2];
    int edgeC = 0;
    q2.push(iCity2);
    //cout<< "push" << iCity2 << endl;
    if (iCity1 != iCity2) edgeC++;
    while (parent != iCity1) {
        q2.push(parent);
        //cout<< "push" << parent << endl;
        parent = pi[parent];
        edgeC++;
    }
    // print 2, Boulder, Boston, Chicago
    cout << edgeC << "," << cityInfo[parent].cityName << ",";

    while (!q2.empty()) {
        int nextC = q2.top(); // next
        //cout<< "pop" << nextC << endl;
        q2.pop();
        cout <<cityInfo[nextC].cityName;
        if (nextC != iCity2) cout << ",";
    }
    cout << endl;

}


int Cities::findCityIndex (string &city) {
    
    int index = -1;
    
    for (int x=0; x < cityCount; x++) {
        if (city == cityInfo[x].cityName) index = x;
    }
    
    return index;
    
}


/* ********************************************************** */

// extra

void Cities::findShortestDistrance(){

    int V=cityCount;
    int dist[V];     // The output array.  dist[i] will hold the shortest
    // distance from src to i
    
    bool sptSet[V]; // sptSet[i] will true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized
    
    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
    
    // Distance of source vertex from itself is always 0
    dist[0] = 0;  // ****** 0 for now
    
    // Find shortest path for all vertices
    for (int count = 0; count < V-1; count++)
    {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in first iteration.
        int u = minDistance(dist, sptSet);
        
        // Mark the picked vertex as processed
        sptSet[u] = true;
        
        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++)
            
            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v]>0 && dist[u] != INT_MAX
                && dist[u]+graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                
                //cout << "hello" << endl;
                //cout << dist[v] << " " << dist[u] << " " << graph[u][v] << endl;
                //cout << v << ":" << u << endl;
                
            }
    }
    
    // print the constructed distance array
 //   printSolution(dist, V);
    
 //   100, Boulder, Boston, Chicago
    
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; i++) {
        if ((dist[i] > 0) && (dist[i] < INT_MAX))
            cout << dist[i] << ", " << cityInfo[i].cityName << endl;
            // printf("%d \t\t %d\n", i, dist[i]);
    }
    for (int i = 0; i < V; i++) {
        printf("%d \t\t %d\n", i, sptSet[i]);
    }

}  // Dijkstra’s


void Cities::doRoadTrip(){}

/*
 
 
 
 
 // A C / C++ program for Dijkstra's single source shortest path algorithm.
 // The program is for adjacency matrix representation of the graph
 // http://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/
 
 


// Number of vertices in the graph
#define V 9

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree

int minDistance(int dist[], bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index=0;
    
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    
    return min_index;
}

// A utility function to print the constructed distance array
int printSolution(int dist[], int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; i++) {
        printf("%d \t\t %d\n", i, dist[i]);
    }
    return 0;
}


// Funtion that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
 
void dijkstra(int graph[V][V], int src)
{
    int dist[V];     // The output array.  dist[i] will hold the shortest
    // distance from src to i
    
    bool sptSet[V]; // sptSet[i] will true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized
    
    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
    
    // Distance of source vertex from itself is always 0
    dist[src] = 0;
    
    // Find shortest path for all vertices
    for (int count = 0; count < V-1; count++)
    {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in first iteration.
        int u = minDistance(dist, sptSet);
        
        // Mark the picked vertex as processed
        sptSet[u] = true;
        
        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++)
            
            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u]+graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
    
    // print the constructed distance array
    printSolution(dist, V);
}



 
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    
    // Let us create the example graph discussed above
    int graph[V][V] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
        {4, 0, 8, 0, 0, 0, 0, 11, 0},
        {0, 8, 0, 7, 0, 4, 0, 0, 2},
        {0, 0, 7, 0, 9, 14, 0, 0, 0},
        {0, 0, 0, 9, 0, 10, 0, 0, 0},
        {0, 0, 4, 14, 10, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 1, 6},
        {8, 11, 0, 0, 0, 0, 1, 0, 7},
        {0, 0, 2, 0, 0, 0, 6, 7, 0}
    };
    
    dijkstra(graph, 1);
    
    return 0;
    
    
}
 */





