#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>

#define INF 20000000

using namespace std;

class Matrix {
    private:
        int size;
        int *costList;
        bool isDist;
    public:
        Matrix() {}
        Matrix(int s) {
            size = s;
            costList = new int[s];
            for (int i = 0; i < s; i++) {
                costList[i] = 0;
            }
        }
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

// void Dijkstra(Matrix *[], int );
// void FloydWarshall(Matrix *[], int);

int main(int argc, char *argv[])
{
    Matrix **adjMatrix;
    // vector<Matrix> adjMatrix;
    int size;
    // cout << "test";
    string input;
    string buffer;
    ifstream myFile("1.txt");
    if (myFile.is_open()) {
        while (getline(myFile,input)) {
            // delimit the string based on spaces, into a vector
            stringstream ss(input);
            vector<string> parts;
            while (ss >> buffer) {
                parts.push_back(buffer);
            }
            // if the file is defining graph size
            if (parts[0] == "s") {
                // string conversion and initialize matrix
                int num = atoi(parts[1].c_str());
                size = num;
                adjMatrix = new Matrix*[num];
                // cout << parts[1] << endl;
                for (int i = 0; i < num; i++) {
                    adjMatrix[i] = new Matrix(num);
                }
            }   
            // if the file is defining an edge in the graph
            else if (parts[0] == "n") {
                int from = atoi(parts[1].c_str());
                int to = atoi(parts[2].c_str());
                int cost = atoi(parts[3].c_str());
                adjMatrix[from]->setListData(to, cost);
            }
        }
        myFile.close();
    }
    else {
        cerr << "There was a problem with opening the file" << endl;
        exit(1);
    }

    // for (int i = 0; i < size; i++) {
    //     for (int j = 0; j < size; j++) {
    //         cout << " " << adjMatrix[i]->getListData(j);
    //     }
    //     cout << endl;
    // }

    // running the floyd warshall Algo
    cout << "0 ";
    
    cout << "1 ";
    Matrix *dist[size];
    // initialize the dist matrix to INF
    for (int i = 0; i < size; i++) {
        dist[i] = new Matrix(size, true);
        // for each vertex, at dist [v][v] = 0
        dist[i]->setListData(i,0);
    }
    cout << "2 ";
    // set the edges for the dist matrix, for all verticies
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (adjMatrix[i]->getListData(j) != 0) {
                //dist[i]->setListData(j, adjMatrix[i]->getListData(j));
            }
        }
    }
    // cout << "3 ";
    // // apply the floyd warshall algorithm
    // for (int i = 0; i < size; i++) {
    //     for (int j = 0; j < size; j++) {
    //         for (int k = 0; k < size; k++) {
    //             if (dist[i]->getListData(j) > dist[i]->getListData(k) + dist[k]->getListData(j)){
    //                 dist[i]->setListData(j, dist[i]->getListData(k) + dist[k]->getListData(j));
    //             }
    //         }
    //     }
    // }

    // // print the results
    // for (int i = 0; i < size; i++) {
    //     for (int j = 0; j < size; j++) {
    //         cout << " " << dist[i]->getListData(j);
    //     }
    //     cout << endl;
    // }

    return 0;
}


// void Dijkstra(Matrix *m[], int source) 
// {



//     return;
// }

// void FloydWarshall(Matrix *m[], int size)
// {
//     cout << "1 ";
//     Matrix *dist[size];
//     // initialize the dist matrix to INF
//     for (int i = 0; i < size; i++) {
//         dist[i] = new Matrix(size, true);
//         // for each vertex, at dist [v][v] = 0
//         dist[i]->setListData(i,0);
//     }
//     cout << "2 ";
//     // set the edges for the dist matrix, for all verticies
//     for (int i = 0; i < size; i++) {
//         for (int j = 0; j < size; i++) {
//             if (m[i]->getListData(j) != 0) {
//                 dist[i]->setListData(j, m[i]->getListData(j));
//             }
//         }
//     }
//     cout << "3 ";
//     // apply the floyd warshall algorithm
//     for (int i = 0; i < size; i++) {
//         for (int j = 0; j < size; j++) {
//             for (int k = 0; k < size; k++) {
//                 if (dist[i]->getListData(j) > dist[i]->getListData(k) + dist[k]->getListData(j)){
//                     dist[i]->setListData(j, dist[i]->getListData(k) + dist[k]->getListData(j));
//                 }
//             }
//         }
//     }

//     // print the results
//     for (int i = 0; i < size; i++) {
//         for (int j = 0; j < size; j++) {
//             cout << " " << dist[i]->getListData(j);
//         }
//         cout << endl;
//     }
// }