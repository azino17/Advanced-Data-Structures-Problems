#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100

void dijkstra(int graph[MAX_VERTICES][MAX_VERTICES], int vertices, int source) {
    int dist[vertices];
    int visited[vertices];

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

        for (int v = 0; v < vertices; ++v) {
            if (!visited[v] && graph[minIndex][v] && dist[minIndex] != INT_MAX &&
                dist[minIndex] + graph[minIndex][v] < dist[v]) {
                dist[v] = dist[minIndex] + graph[minIndex][v];
            }
        }
    }

    printf("Shortest distances from source vertex %d:\n", source);
    for (int i = 0; i < vertices; ++i) {
        printf("Vertex %d: %d\n", i, dist[i]);
    }
}

void displayGraph(int graph[MAX_VERTICES][MAX_VERTICES], int vertices) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int choice, vertices, source;
    int graph[MAX_VERTICES][MAX_VERTICES];

    printf("Enter number of vertices (maximum %d): ", MAX_VERTICES);
    scanf("%d", &vertices);

    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            graph[i][j] = 0;
        }
    }

    do {
        printf("\n1. Add Edge\n");
        printf("2. Display Adjacency Matrix\n");
        printf("3. Find Shortest Paths\n");
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
                graph[u][v] = weight;
                graph[v][u] = weight;
                break;
            }
            case 2:
                displayGraph(graph, vertices);
                break;
            case 3: {
                printf("Enter source vertex: ");
                scanf("%d", &source);
                if (source < 0 || source >= vertices) {
                    printf("Invalid source vertex.\n");
                    break;
                }
                dijkstra(graph, vertices, source);
                break;
            }
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 4);

    return 0;
}
