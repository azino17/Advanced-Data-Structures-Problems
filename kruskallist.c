#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Node {
    int dest;
    int weight;
    struct Node* next;
};

struct Graph {
    int vertices;
    struct Node** adjList;
};

struct Edge {
    int src, dest, weight;
};

struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vertices = vertices;
    graph->adjList = (struct Node**)malloc(vertices * sizeof(struct Node*));
    for (int i = 0; i < vertices; ++i)
        graph->adjList[i] = NULL;
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest, int weight) {
    // Add an edge from src to dest
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    // Add an edge from dest to src as it's an undirected graph
    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = src;
    newNode->weight = weight;
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

void display(struct Graph* graph) {
    printf("Adjacency List is:\n");
    for (int v = 0; v < graph->vertices; ++v) {
        printf("Vertex %d -> ", v);
        struct Node* current = graph->adjList[v];
        while (current != NULL) {
            printf("(%d, %d) ", current->dest, current->weight);
            current = current->next;
        }
        printf("\n");
    }
}

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
        struct Node* current = graph->adjList[i];
        while (current != NULL) {
            totalEdges++;
            current = current->next;
        }
    }

    struct Edge* edges = (struct Edge*)malloc(totalEdges * sizeof(struct Edge));
    int edgeIndex = 0;
    for (int i = 0; i < V; i++) {
        struct Node* current = graph->adjList[i];
        while (current != NULL) {
            edges[edgeIndex].src = i;
            edges[edgeIndex].dest = current->dest;
            edges[edgeIndex].weight = current->weight;
            edgeIndex++;
            current = current->next;
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

    graph = createGraph(vertices);

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

    // Free allocated memory
    for (int v = 0; v < vertices; ++v) {
        struct Node* current = graph->adjList[v];
        while (current != NULL) {
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->adjList);
    free(graph);

    return 0;
}
