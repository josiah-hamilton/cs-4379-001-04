#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#include "graph.h"

#ifndef NODES
    #define NODES 3
#endif

#ifndef MAXWEIGHT
    #define MAXWEIGHT 20
#endif
#ifndef EDGEODDS
    #define EDGEODDS 1  // 1:EDGEODDS probability of an edge during syntehsis.
#endif


int main(int argc, char** argv) {
    int n = NODES, chunksize;
    int i, j, k;
    int *Wo, *W, *colchunk, *rowchunk;
    int rank, rowrank, colrank;
    int size, rowsize, colsize;
    MPI_Status status;
    MPI_Comm rowcomm, colcomm;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    chunksize = n / (int)sqrt(size);
    MPI_Comm_split(MPI_COMM_WORLD,(int)(rank/chunksize),rank,&rowcomm);
    MPI_Comm_split(MPI_COMM_WORLD,(int)(rank%chunksize),rank,&colcomm);

#ifdef FULLGEN
    Wo = (int*) calloc(n*n, sizeof(int));
    W  = (int*) calloc(n*n, sizeof(int));

    //graphsynth(Wo, n, time(NULL),MAXWEIGHT,EDGEODDS);
    matrixsynth(Wo, n, time(NULL), MAXWEIGHT);

    for (i = 0; i < n*n; i++) {
        W[i] = 0;
    }
#else
    Wo = (int*) calloc(chunksize*chunksize,sizeof(int));
    W  = (int*) calloc(chunksize*chunksize,sizeof(int));
#endif
    colchunk = (int*) calloc(chunksize,sizeof(int));
    rowchunk = (int*) calloc(chunksize,sizeof(int));

    for (k = 0; k < n; k++) {
        MPI_Bcast(colchunk,chunksize,MPI_INT,(int)(k/chunksize),colcomm);
        MPI_Bcast(rowchunk,chunksize,MPI_INT,(int)(k/chunksize),rowcomm);
        for (i = 0; i < chunksize; i++) {
            for (j = 0; j < chunksize; j++) {
                //W[n*i+j] = min( Wo[n*i+j], Wo[n*i+k] + Wo[n*k+j]);
                W[chunksize*i+j] = min( Wo[chunksize*i+j], colchunk[i] + rowchunk[j]);
            }
        }

        for (i = 0; i < chunksize; i++) {
            for (j = 0; j < chunksize; j++) {
                Wo[chunksize*i+j] = W[chunksize*i+j];
            }
        }
    }

    MPI_Comm_free(&colcomm);
    MPI_Comm_free(&rowcomm);
    MPI_Finalize();
    return 0;
}

