#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "graph.h"




int main(){
    _GRAPH_ graph;
    char fileName[30];
    scanf("%s", fileName);
    readGraphFromTxt(fileName, &graph);
    printGraph(&graph);
    printAllGraphNodeNumber(&graph);

    for (int i=0; i<graph.vc; i++)
        printf("\nAddr of Node %d : %d", graph.node[i]->nodeNumber ,  &graph.node[i] );

    int nodeNum1, nodeNum2, *Path;
    printf("\nEnter Start node Number: ");
    scanf(" %d" , &nodeNum1);
    printf("Enter the ending node Number: ");
    scanf(" %d" , &nodeNum2);

    if(nodeNum1<0 || graph.vc<=nodeNum1)
        puts("Invalid Start Node Number. ");
    else if(nodeNum2<0 || graph.vc<=nodeNum2)
        puts("Invalid End Node Number. ");
    else if((Path=BreadthFirstSearch(&graph , &graph.node[nodeNum2], &graph.node[nodeNum1])) !=NULL){
        puts("Nodes are connected.");
        size_t i=0;
        while(1){
            printf("\n%d ", Path[i]);
            if(Path[i]==nodeNum2)   break;
            i++;
        }
        int lengthOfShortestPath = i;
        printf("\nLength of shortest Path: %d\n", lengthOfShortestPath);
        publishShortestPathGraph(&graph, Path, lengthOfShortestPath);
    } else puts("Not Connected.");

    puts("\nCounting Pieces...");
    printf("Pieces: %d\n", countPiecesAndPublish(&graph));

    puts("\n....Deallocating all reserved memory....\n");
    free(Path);
    freeGraph(&graph);
    return 0;
}
