#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100

struct Node {
    int dest;
    int weight;
    struct Node* next;
};

struct Graph {
    int vertices;
    struct Node** adjList;
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

void dijkstra(struct Graph* graph, int source) {
    int vertices = graph->vertices;
    int dist[vertices];
    int visited[vertices];

    // Initialize distances and visited array
    for (int i = 0; i < vertices; ++i) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }
    dist[source] = 0;

    for (int count = 0; count < vertices - 1; ++count) {
        int minDist = INT_MAX, minIndex = -1;
        for (int v = 0; v < vertices; ++v) {
            if (!visited[v] && dist[v] < minDist) {
                minDist = dist[v];
                minIndex = v;
            }
        }

        visited[minIndex] = 1;

        struct Node* current = graph->adjList[minIndex];
        while (current != NULL) {
            int v = current->dest;
            int weight = current->weight;
            if (!visited[v] && dist[minIndex] != INT_MAX &&
                dist[minIndex] + weight < dist[v]) {
                dist[v] = dist[minIndex] + weight;
            }
            current = current->next;
        }
    }

    printf("Shortest distances from source vertex %d:\n", source);
    for (int i = 0; i < vertices; ++i) {
        printf("Vertex %d: %d\n", i, dist[i]);
    }
}

void displayGraph(struct Graph* graph) {
    printf("Adjacency List:\n");
    for (int i = 0; i < graph->vertices; ++i) {
        printf("Vertex %d -> ", i);
        struct Node* current = graph->adjList[i];
        while (current != NULL) {
            printf("(%d, %d) ", current->dest, current->weight);
            current = current->next;
        }
        printf("\n");
    }
}

int main() {
    int choice, vertices, source;
    struct Graph* graph = NULL;

    printf("Enter number of vertices (maximum %d): ", MAX_VERTICES);
    scanf("%d", &vertices);

    graph = createGraph(vertices);

    do {
        printf("\n1. Add Edge\n");
        printf("2. Display Adjacency List\n");
        printf("3. Find Shortest Paths using Dijkstra's Algorithm\n");
        printf("4. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int u, v, weight;
                printf("Enter vertices and weight of the edge: ");
                scanf("%d %d %d", &u, &v, &weight);
                if (u < 0 || u >= vertices || v < 0 || v >= vertices) {
                    printf("Invalid vertices.\n");
                    break;
                }
                addEdge(graph, u, v, weight);
                break;
            }
            case 2:
                displayGraph(graph);
                break;
            case 3: {
                printf("Enter source vertex: ");
                scanf("%d", &source);
                if (source < 0 || source >= vertices) {
                    printf("Invalid source vertex.\n");
                    break;
                }
                dijkstra(graph, source);
                break;
            }
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
