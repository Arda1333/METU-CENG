#include "Graph.h"
#include "GraphExceptions.h"
#include <iostream>

int main()
{
    int i, j;
    Graph g;
    std::vector<std::vector<int> > paths;
    std::string from = "S", to = "Z";


    g.InsertVertex("S");
    g.InsertVertex("Y");
    g.InsertVertex("Z");
    g.InsertVertex("T");
    /*g.InsertVertex("E");
    g.InsertVertex("F");
    g.InsertVertex("G");
    g.InsertVertex("H");
    g.InsertVertex("I");
    g.InsertVertex("J");*/

    g.ConnectVertices("S", "Y", 4);
    g.ConnectVertices("Y", "Z", 2);
    g.ConnectVertices("S", "Z", 7);
    g.ConnectVertices("S", "T", 10);
    g.ConnectVertices("T", "Y", 3);
    /*g.ConnectVertices("C", "G", 6);
    g.ConnectVertices("F", "H", 7);
    g.ConnectVertices("G", "I", 8);
    g.ConnectVertices("H", "J", 9);
    g.ConnectVertices("I", "J", 4);
    g.ConnectVertices("A", "J", 18);*/

    g.MultipleShortPaths(paths, from, to, 3);

    for(i = 0; i < paths.size(); i++)
    {
        g.PrintPath(paths[i], true);
        std::cout << g.TotalWeightInBetween(paths[i]) << std::endl;
    }

    /*try
    {
        g.ConnectVertices("A", "J", 9);
    }
    catch(const TooManyEdgeOnVertexExecption& e)
    {
        std::cout << e.what() << '\n';
    }
    */

    return 0;
}