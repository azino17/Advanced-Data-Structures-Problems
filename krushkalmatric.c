#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Graph {
    int vertices;
    int** adjMatrix;
};

struct Edge {
    int src, dest, weight;
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

// Kruskal's algorithm
int find(int parent[], int i) {
    if (parent[i] == i)
        return i;
    return find(parent, parent[i]);
}

void unionSet(int parent[], int x, int y) {
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
}

int myComp(const void* a, const void* b) {
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight - b1->weight;
}

void kruskalMST(struct Graph* graph) {
    int V = graph->vertices;
    int totalEdges = 0;
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (graph->adjMatrix[i][j] != 0) {
                totalEdges++;
            }
        }
    }

    struct Edge* edges = (struct Edge*)malloc(totalEdges * sizeof(struct Edge));
    int edgeIndex = 0;
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (graph->adjMatrix[i][j] != 0) {
                edges[edgeIndex].src = i;
                edges[edgeIndex].dest = j;
                edges[edgeIndex].weight = graph->adjMatrix[i][j];
                edgeIndex++;
            }
        }
    }

    qsort(edges, totalEdges, sizeof(struct Edge), myComp);

    int parent[V];
    for (int v = 0; v < V; ++v)
        parent[v] = v;

    printf("Edge   Weight\n");
    for (int i = 0; i < totalEdges; ++i) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int weight = edges[i].weight;

        int x = find(parent, u);
        int y = find(parent, v);

        if (x != y) {
            printf("%d - %d    %d \n", u, v, weight);
            unionSet(parent, x, y);
        }
    }
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
        printf("3. Find Minimum Spanning Tree using Kruskal's Algorithm\n");
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
                printf("Minimum Spanning Tree using Kruskal's Algorithm:\n");
                kruskalMST(graph);
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
