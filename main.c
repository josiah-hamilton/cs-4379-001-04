#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "graph.h"

#ifndef NODES
    #define NODES 3
#endif

#ifndef MAXWEIGHT
    #define MAXWEIGHT 20
#endif
#ifndef EDGEODDS
    #define EDGEODDS 1  // 1-in-EDGEODDS probability of an edge
                         // during round of edge synthesis.
                         // All nodes are guaranteed to be connected
                         // At least once during second round
#endif


int main(int argc, char** argv) {
    int n = NODES;
    int i, j, k;
    int *Wo, *W;

    int rank;
    int size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    Wo = (int*) calloc(n*n, sizeof(int));
    W  = (int*) calloc(n*n, sizeof(int));

    //graphsynth(Wo, n, time(NULL),MAXWEIGHT,EDGEODDS);
    matrixsynth(Wo, n, time(NULL), MAXWEIGHT);

    for (i = 0; i < n*n; i++) {
        W[i] = 0;
    }

    for (k = 0; k < n; k++) {
#ifdef DEBUG
        fprintf(stderr, "Wo\n");
        printgraph(Wo,n);
#endif
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                W[n*i+j] = min( Wo[n*i+j], Wo[n*i+k] + Wo[n*k+j]);
#ifdef DEBUG
                fprintf(stderr, "W\n");
                printgraph(W,n);
#endif
            }
        }

        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                Wo[n*i+j] = W[n*i+j];
            }
        }
    }

    MPI_Finalize();
    return 0;
}
