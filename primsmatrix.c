#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Graph {
    int vertices;
    int** adjMatrix;
};

struct Graph* create(int vertices) {
    int i;
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vertices = vertices;
    graph->adjMatrix = (int **)malloc(vertices * sizeof(int *));
    for (i = 0; i < vertices; i++) {
        graph->adjMatrix[i] = (int *)malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++)
            graph->adjMatrix[i][j] = 0; 
    }
    return graph;
}

void addEdge(struct Graph* graph, int v1, int v2, int weight) {
    graph->adjMatrix[v1][v2] = weight;
    graph->adjMatrix[v2][v1] = weight; 
}

void display(struct Graph* graph) {
    printf("Adjacency Matrix is:\n");
    for (int i = 0; i < graph->vertices; i++) {
        for (int j = 0; j < graph->vertices; j++) {
            printf("%d ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}


int minKey(int key[], int mstSet[], int numVertices) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < numVertices; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }

    return min_index;
}


void printMST(int parent[], struct Graph* graph) {
    printf("Edge   Weight\n");
    for (int i = 1; i < graph->vertices; i++) {
        printf("%d - %d    %d \n", parent[i], i, graph->adjMatrix[i][parent[i]]);
    }
}


void primMST(struct Graph* graph) {
    int parent[graph->vertices]; 
    int key[graph->vertices]; 
    int mstSet[graph->vertices]; 


    for (int i = 0; i < graph->vertices; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

   
    key[0] = 0;
    parent[0] = -1; 

    for (int count = 0; count < graph->vertices - 1; count++) {
        int u = minKey(key, mstSet, graph->vertices);
        mstSet[u] = 1; 

    
        for (int v = 0; v < graph->vertices; v++) {
        
            if (graph->adjMatrix[u][v] && mstSet[v] == 0 && graph->adjMatrix[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph->adjMatrix[u][v];
            }
        }
    }

    printMST(parent, graph);
}

int main() {
    int choice, v1, v2, weight, vertices;
    struct Graph* graph = NULL;

    printf("Enter number of vertices: ");
    scanf("%d", &vertices);

    graph = create(vertices);

    do {
        printf("\n1. Add Edge\n");
        printf("2. Display\n");
        printf("3. Find Minimum Spanning Tree using Prim's Algorithm\n");
        printf("4. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter vertices and weight: ");
                scanf("%d %d %d", &v1, &v2, &weight);
                if (v1 >= 0 && v1 < vertices && v2 >= 0 && v2 < vertices && weight >= 0) {
                    addEdge(graph, v1, v2, weight);
                } else {
                    printf("Invalid input.\n");
                }
                break;
            case 2:
                if (graph == NULL) {
                    printf("Create graph first!\n");
                    break;
                }
                display(graph);
                break;
            case 3:
                if (graph == NULL) {
                    printf("Create graph first!\n");
                    break;
                }
                printf("Minimum Spanning Tree using Prim's Algorithm:\n");
                primMST(graph);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 4);

    
    for (int i = 0; i < vertices; i++) {
        free(graph->adjMatrix[i]);
    }
    free(graph->adjMatrix);
    free(graph);

    return 0;
}
