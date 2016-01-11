//
//  crg.c
//  Create random graph with edge type
//
//  Created by 张宇彤 on 15/9/24.
//  Copyright (c) 2015年 张宇彤. All rights reserved.
//

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define NodeCount 100
#define TypeCount 5
#define Edges NodeCount*(NodeCount-1)/2
#define P 0.5
#define Filenum 100
long int matrix[NodeCount][NodeCount];
long long int linkq[Edges];

char etype[TypeCount] = {'a','b','c','d','e'};

struct timeval tptime;

char RandomEtype(){
    gettimeofday(&tptime, NULL);
    srand((int)tptime.tv_usec);
    
    return etype[rand()%TypeCount];
}

long long int MatrixFromSequence(long int matrix[NodeCount][NodeCount], long long int *sequence, long int n, FILE *fp){
    long long int esum,count;
    count = esum = 0;
    for (long int i = 0; i < n - 1; i++) {
        for (long int j = i + 1; j < n; j++) {
            if (sequence[count]) {
                matrix[i][j] = 1;
                esum++;
                fprintf(fp, "%ld  %ld  %c\n", i, j, RandomEtype());
            }
            else matrix[i][j] = 0;
            count++;
        }
        
    }
    
    return esum;
}

int RandomSequence(long long int *sequence, float p, long long int len){
    for (int i = 0; i < len; i++) {
        gettimeofday(&tptime, NULL);
        srand((int)tptime.tv_usec);
        sequence[i] = rand()%10 + 1 <= 10*p ? 1 : 0;
    }
    return 1;
}

int main(int argc, const char * argv[]) {
    
    long long int edges;
    long long int i,j;
    int f;
    char filename[20];
    FILE *fp;
    
    for(i = 0; i < Edges; i++){
        linkq[i] = 0;
    }
    
    for (i = 0; i < NodeCount; i++) {
        for (j = 0; j < NodeCount; j++) {
            matrix[i][j] = 0;
        }
        
    }
    
    for (f = 0; f < Filenum; f++) {
        sprintf(filename, "file_edges/%d.edges",f);
        
        fp = fopen(filename, "w");
        
        RandomSequence(linkq, P, Edges);
        edges = MatrixFromSequence(matrix, linkq, NodeCount, fp);
        
        printf("%d edges: %lld / %d\n", f, edges, Edges);
        
        fclose(fp);
    }
    return 0;
}
