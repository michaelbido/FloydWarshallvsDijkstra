Michael Bido-Chavez
euid: mb0501

Term Project CSCE4110
Fall 2017

—————————————————————
Files

Open/decompress the BidoAlgoF17.zip file. Here is what 
is inside the .zip file:

dijkstraFloyd.cpp
graphGenerator.cpp
graphGeneratorLinear.cpp
compile.sh
README.txt
collectedData (a directory with example data)

—————————————————————
—————————————————————
Description

The purpose of this project is to compare the performance of these two 
algorithms in solving the all pairs shortest path algorithm. 

This will generate the graphs necessary for comparable data.

This will generate the solution to the all pairs shortest path program
for a given graph by using Dijkstra's algorithm and the Floyd-Warshall 
algorithm and then compare the two via a CPU-time counter.

All results will be output to files.

Each file has further comments to understand functionality.
—————————————————————
—————————————————————
How to Compile

Place all files within the same directory in the cse01.cse.unt.edu 
machine, and then enter that directory. Then, type the following:

g++ graphGenerator.cpp -o generator.out
g++ graphGeneratorLinear.cpp -o generatorLinear.out
g++ dijkstraFloyd.cpp -o algo.out

Alternatively, you can run attached 'compile.sh' file. This is much easier.
—————————————————————
_____________________
Graph File Format

The graph file contains two types of lines, the size of the graph and the
edges within the graph

At the very top of the file, denote the size of the graph by the following:

s 'verticies in graph'

Following this, to define edges between verticies in a graph, denote 
the edges by the following format:

n 'source vertex index' 'dest. vertex index' 'cost/weight of edge'

Indexes start at zero. To be safe, only use complete graphs.
_____________________
—————————————————————
How to Execute

To generate 30 graphs of varying sizes with randomly weighted edges, type:

./generator.out

To generate 30 graphs of varying sizes with linearly generated weighted edges, type:

./generatorLinear.out

To execute the Dijkstra/Floyd-Warshall program to generate the solution and time performance, type:

./algo.out 'filename'

Upon completion of successful execution, all of these will generate files in your current directory.

—————————————————————
—————————————————————
Useful Sources for This Program

http://www.cse.unt.edu/~4110S001/dijk.pdf
http://www.cse.unt.edu/~4110S001/dp_floyd.pdf
https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm#Algorithm

—————————————————————