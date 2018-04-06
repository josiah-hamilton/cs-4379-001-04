int minimum(int* nums, int n) {
    int min = nums[0], i;
    for (i = 0; i < n; i++) {
        if (nums[i] < min) {
            min = nums[i];
        }
    }
    return min;
}

int min(int a, int b) {
    return (a<b) ? a : b;
}

void graphsynth(int *edge, int n, time_t seed, int maxweight, int edgeodds) {
    srand(seed);
    int i, j;
    for (i = 0; i < n; i++) {
        edge[n*i+i] = 0;                 // assume no edges contain one node
        for (j = 1; j < i; j++) {
            int exist  = rand() % edgeodds + 1;
            int weight = rand() % maxweight + 1;
            if ( exist > 1 ) { 
                edge[n*i+j] = 0;
                edge[n*j+i] = 0;
            } else if (j != i) {
                edge[n*i+j] = weight;
                edge[n*j+i] = weight;
            }
        }
    }
    // check that all nodes are connected at least once
    for (i = 0; i < n; i++) {
        int connected = 0;
        for (j = 0; (j < i) && (connected == 0); j++) {
            if (edge[n*i+j] > connected) {
                connected = edge[n*i+j];
            }
        }
        if (connected == 0) {
            // edge[i][random not i] = random
            j = i;
            while (j == i ) {
                j = rand()%n;
            }
            int weight = rand() % maxweight + 1;
            edge[n*i+j] = weight;
            edge[n*j+i] = weight;
        }
    }
}

void matrixsynth(int *edge, int n, time_t seed, int maxweight) {
    srand(seed);
    int i;
    for (i = 0; i < n*n; i++) {
        int weight = rand() % maxweight + 1;
        edge[i] = weight;
    }
}

void printgraph(int *edge, int n) {
    int i;
#ifdef DEBUG
    for (i = 0; i < n; i++) {
        fprintf(stderr,"\t%d",i);
    }
    fprintf(stderr,"\n_");
    for (i = 0; i < n; i++) {
        fprintf(stderr,"________",i);
    }
    fprintf(stderr,"\n");
    for (i = 0; i < n; i++) {
        fprintf(stderr,"%d|\t",i);
        int j;
        for (j = 0; j < n; j++) {
            fprintf(stderr,"%d\t",edge[n*i+j]);
        }
        fprintf(stderr,"\n");
    }
#else
    for (i = 0; i < n; i++) {
        printf("\t%d",i);
    }
    printf("\n_");
    for (i = 0; i < n; i++) {
        fprintf(stderr,"________",i);
    }
    printf("\n");
    for (i = 0; i < n; i++) {
        printf("%d|\t",i);
        int j;
        for (j = 0; j < n; j++) {
            printf("%d\t",edge[n*i+j]);
        }
        printf("\n");
    }
#endif
}

