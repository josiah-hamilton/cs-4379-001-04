#include<stdio.h>
#include<stdlib.h> // rand(), srand()
#include<time.h>
#include "graph.c"

// in this source, graphs are represented by contiguous adjacency matrices
// rather than graph[i][j], we index graph[n*i+j] and ar very aware of n-bounds

void matrixsynth(int*, int, time_t, int);
void graphsynth(int*, int, time_t, int, int);
void printgraph(int*, int);
int minimum(int*, int);
int min(int, int);
