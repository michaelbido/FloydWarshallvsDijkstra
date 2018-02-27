/* 
Compilation: g++ graphGeneratorLinear.cpp -o generatorLinear.out
Execution  : ./generatorLinear.out

Name       : Michael Bido-Chavez (euid: mb0501)

Dijkstra vs Floyd-Warshall Algo.
Graph generator
-----------------------------
Description:
This program will generate 30 complete graphs from sizes
50 to 1000, with linearly generated weights between each graph.
Each graph is weighted and has opposite edges.

All results will be output to files
-----------------------------
*/
#include <iostream>
#include <fstream>
#include <sstream>
//#include <cstdlib>
#include <stdlib.h>
#include <time.h>

using namespace std;

// create a class called matrix, containing the list each vertex points to
// this list will acts as the 2nd part of a 2D array, i.e. arr[][this]
class Matrix {
    private:
        int size;
        int *costList;
    public:
        Matrix() {}
        Matrix(int s) {
            size = s;
            costList = new int[s];
            for (int i = 0; i < s; i++) {
                costList[i] = 0;
            }
        }
        ~Matrix() {}
        int getListData(int i) {
            return costList[i];
        }
        void setListData(int i, int cost) {
            costList[i] = cost;
        }
};

int main(int argc, char *argv[])
{
    // to generate random values, the seed
    srand (time(NULL));
    // variable initalization
    int numOfNodes;
    int maxCost = 30;
    // lowest node and highest node are the possible amounts of nodes
    // in the graph. Meant to be from 50 to 1000
    int lowestNode = 50;
    int highestNode = 1000;
    int numberOfFiles = 30;
    ofstream myFile;
    // for each file
    for (int i = 0; i < numberOfFiles; i++) {
        // get 'i' number and change it to string, then use as file name
        ostringstream ss;
        ss << i+1;
        string fileName = ss.str() + "linear.txt";
        myFile.open(fileName.c_str());
        // generate a random number of nodes for the graph
        numOfNodes = lowestNode + rand() % (highestNode - lowestNode + 1);
        cout << "Number of Nodes " << numOfNodes << ", File name: " << fileName << endl;
        // initialize the matrix, acts as a 2D array
        int size = numOfNodes;
        Matrix *adjMatrix[size];
        for (int j = 0; j < size; j++) {
            adjMatrix[j] = new Matrix(size);
        }
        // write the size to the file
        myFile << "s ";
        myFile << size;
        myFile << "\n";

        int currentCost;
        // for each node in the graph, complete directed graph
        // add values to the matrix that grow linearly based on j, meaning that
        // the higher the node index, the higher the cost going outward from it
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                // get the value, times 4 to make costs bigger
                currentCost = (j+1)*4;
                if (!(k == j)) {
                    // add value to cost matrix
                    adjMatrix[j]->setListData(k,currentCost);
                    // output source, dest. and cost to file
                    myFile << "n ";
                    myFile << j;
                    myFile << " ";
                    myFile << k;
                    myFile << " ";
                    myFile << currentCost;
                    myFile << "\n";
                }
            }
        }
        // close the file
        myFile.close();
    }
    return 0;
}