/* 
Compilation: g++ dijkstraFloyd.cpp -o algo.out
Execution  : ./algo.out <filename>

Name       : Michael Bido-Chavez (euid: mb0501)

Dijkstra vs Floyd-Warshall Algo.
Solution generator and benchmark
-----------------------------
Description:
This program will generate the solution to the 
all pairs shortest path program for a given graph by
using Dijkstra's algorithm and the Floyd-Warshall algorithm
and then compare the two via a CPU-time counter.

All results will be output to files
-----------------------------
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <stdlib.h>

#define INF 20000000

using namespace std;
// class matrix to store each row of the cost matrix
// instanced as an array of matrix
class Matrix {
    private:
        int size;
        int *costList;
        bool isDist;
    public:
        Matrix() {}
        // for regular matrix
        Matrix(int s) {
            size = s;
            costList = new int[s];
            for (int i = 0; i < s; i++) {
                costList[i] = 0;
            }
        }
        // for Floyd-Warshall matrix
        Matrix(int s, bool t) {
            size = s;
            costList = new int[s];
            for (int i = 0; i < s; i++) {
                costList[i] = INF;
            }
            isDist = t;
        }
        ~Matrix() {}

        int getListData(int i) {
            return costList[i];
        }
        void setListData(int i, int cost) {
            costList[i] = cost;
        }


};

void Dijkstra(Matrix *[], int, int);
void FloydWarshall(Matrix *[], int);

int main(int argc, char *argv[])
{
    // checks if the arg count is correct
    // comment this out if testing files 30 at a time
    if (argc != 2) {
        cerr << "usage: ./algo [inputfile]" << endl;
        exit(2);
    }
    // an array of pointers
    Matrix **adjMatrix;
    int size;
    // int numberOfFiles = 30;
    int numberOfFiles = 1;

    string input;
    string buffer;
    ifstream myFile;

    ofstream outputFile;
    outputFile.open("outputData.csv");
    // outputFile.open("outputDataRandom.csv");
    // outputFile.open("outputDataLinear.csv");
    outputFile << "size,dijkstra,floydwarshall" << endl;
    // for all files
    for (int i = 0; i < numberOfFiles; i++) {
        // used to iterate through 30 generated files,
        // change number of files above to 30, and then uncomment this block that has code
        /*
        // get 'i' number and change it to string, then use as file name
        ostringstream ss;
        ss << i+1;
        // for automated looping, uncomment ".txt" line for files with random edges
        // **or, uncommment the "linear.txt" line for files with linearly growning edges
        string fileName = ss.str() + ".txt";
        // string fileName = ss.str() + "linear.txt";
        myFile.open(fileName.c_str());
        */

        // to open file from command line arg, comment this out if using 30 generated files at once
        myFile.open(argv[1]);

        cout << endl << "Processing input file. Running Algoritms...";

        if (myFile.is_open()) {
            while (getline(myFile,input)) {
                // delimit the string based on spaces, into a vector
                stringstream ss(input);
                vector<string> parts;
                while (ss >> buffer) {
                    parts.push_back(buffer);
                }
                // if the file is defining graph size
                // define size of adj. cost matrix
                if (parts[0] == "s") {
                    // string conversion and initialize matrix
                    int num = atoi(parts[1].c_str());
                    size = num;
                    outputFile << size << ",";
                    // intiailize the 2D array
                    adjMatrix = new Matrix*[num];
                    // cout << parts[1] << endl;
                    for (int i = 0; i < num; i++) {
                        adjMatrix[i] = new Matrix(num);
                    }
                }   
                // if the file is defining an edge in the graph
                // populate adj. cost matrix
                else if (parts[0] == "n") {
                    int from = atoi(parts[1].c_str());
                    int to = atoi(parts[2].c_str());
                    int cost = atoi(parts[3].c_str());
                    adjMatrix[from]->setListData(to, cost);
                }
                else {
                    cerr << "File format incorrect, please check comments!" << endl;
                    myFile.close();
                    exit(3);
                }
            }
            myFile.close();
        }
        else {
            cerr << "There was a problem with opening the file" << endl;
            exit(1);
        }
        // print out adj matrix results
        // for (int i = 0; i < size; i++) {
        //     for (int j = 0; j < size; j++) {
        //         cout << " " << adjMatrix[i]->getListData(j);
        //     }
        //     cout << endl;
        // }   

        // add timer starter for dijkstras
        clock_t endDijkstra;
        clock_t endFloyd;
        // start timer for dijsktra
        clock_t startTime = clock();
        // format file for djikstra output
        ofstream outFile;
        outFile.open("finalCostMatrix.txt", fstream::out | fstream::app);
        outFile << "----------------------- Dijkstra -----------------------" << endl;
        outFile.close();
        // loop for all nodes for dijkstras
        for (int i = 0; i < size; i++) {
            Dijkstra(adjMatrix, i, size);
        }
        // get start and end time difference
        endDijkstra = clock() - startTime;
        
        startTime = clock();
        // add timer start for floyd warshall, get time difference
        FloydWarshall(adjMatrix, size);
        endFloyd = clock() - startTime;
        // store results into csv to add to spreadsheet
        outputFile << (float)endDijkstra/(CLOCKS_PER_SEC/1000) << ",";
        outputFile << (float)endFloyd/(CLOCKS_PER_SEC/1000) << endl;
        // output messages about files
        cout << " finished." << endl;
        cout << "The performance output file is called outputData.csv" << endl;
        cout << "Dijkstra and Floyd-Warshall final matrix output file is called finalCostMatrix.txt\n" << endl;

    }
    outputFile.close();

    return 0;
}

//dijkstra's algo.
void Dijkstra(Matrix *m[], int source, int size) 
{
    ofstream outFile;
    outFile.open("finalCostMatrix.txt", fstream::out | fstream::app);
    // s, the set of visited verticies
    bool s[size];

    int *dist = new int[size];
    // initialize s(empty) and dist, from the adj. matrix
    for (int i = 0; i < size; i++) {
        s[i] = false;
        dist[i] = m[source]->getListData(i);
    }
    // put the starting node into s, plus the distance
    s[source] = true;
    dist[source] = 0;
    // for all verticies not in s
    for (int i = 0; i < size; i++) {
        // this section chooses among those not in S
        // and that have the lowest distance from the current vertex
        int low = INF;
        int lowPos;
        for (int j = 0; j < size; j++) {
            if (!s[j] && dist[j] <= low) {
                low = dist[j];
                lowPos = j;
            }
        }
        if (!s[lowPos]) {
            // add the lowest one to the set S, which is the variable u
            s[lowPos] = true;
            // determine the paths from the current vertex u
            for (int j = 0; j < size; j++) {
                // if the new path is shorter than the distance path
                if (!s[j] && dist[j] > dist[lowPos] + m[j]->getListData(lowPos)) {
                    // then update any distances
                    dist[j] = dist[lowPos] + m[j]->getListData(lowPos);
                }
            }
        }
    }

    // print the results to file 
    for (int i = 0; i < size; i++) {
        outFile << dist[i] << " ";
    }
    outFile << endl;

    outFile.close();
    // free the memory
    delete[] dist;

    return;
}
// the floyd-warshall algo.
void FloydWarshall(Matrix *m[], int size)
{

    Matrix *dist[size];
    // initialize the dist matrix to INF
    for (int i = 0; i < size; i++) {
        dist[i] = new Matrix(size, true);
        // for each vertex, at dist [v][v] = 0
        dist[i]->setListData(i,0);
    }
    // set the edges for the dist matrix, for all verticies
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (m[i]->getListData(j) != 0) {
                dist[i]->setListData(j, m[i]->getListData(j));
            }
        }
    }
    // apply the floyd warshall algorithm
    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (dist[i]->getListData(j) > dist[i]->getListData(k) + dist[k]->getListData(j)){
                    dist[i]->setListData(j, dist[i]->getListData(k) + dist[k]->getListData(j));
                }
            }
        }
    }
    // output results into file in format
    ofstream outFile;
    outFile.open("finalCostMatrix.txt", fstream::out | fstream::app);
    outFile << "-------------------- Floyd-Warshall --------------------" << endl;
    // print the results to file
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            outFile << " " << dist[i]->getListData(j);
        }
        outFile << endl;
    }
    outFile.close();

    // free the memory
    for (int i = 0; i < size; i++) {
        delete dist[i];
    }
}

// http://www.cse.unt.edu/~4110S001/dijk.pdf
// http://www.cse.unt.edu/~4110S001/dp_floyd.pdf
// https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm#Algorithm