#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Node {
    int vertex;
    int weight;
    struct Node* next;
};

struct Graph {
    int vertices;
    struct Node** adjList;
};

struct Node* createNode(int vertex, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

struct Graph* create(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vertices = vertices;
    graph->adjList = (struct Node**)malloc(vertices * sizeof(struct Node*));
    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
    }
    return graph;
}

void addEdge(struct Graph* graph, int v1, int v2, int weight) {
    struct Node* newNode = createNode(v2, weight);
    newNode->next = graph->adjList[v1];
    graph->adjList[v1] = newNode;
    newNode = createNode(v1, weight);
    newNode->next = graph->adjList[v2];
    graph->adjList[v2] = newNode;
}

void display(struct Graph* graph) {
    printf("Adjacency List is:\n");
    for (int i = 0; i < graph->vertices; i++) {
        struct Node* temp = graph->adjList[i];
        printf("Vertex %d: ", i);
        while (temp) {
            printf("(%d, %d) -> ", temp->vertex, temp->weight);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void primMST(struct Graph* graph) {
    int parent[graph->vertices]; // Array to store constructed MST
    int key[graph->vertices];    // Key values used to pick minimum weight edge in cut
    int mstSet[graph->vertices]; // To represent set of vertices not yet included in MST

    // Initialize all keys as INFINITE
    for (int i = 0; i < graph->vertices; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    // Always include first  vertex in MST.
    key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
    parent[0] = -1; // First node is always root of MST

    // The MST will have V vertices
    for (int count = 0; count < graph->vertices - 1; count++) {
        // Pick the minimum key vertex from the set of vertices not yet included in MST
        int u, min = INT_MAX;
        for (int v = 0; v < graph->vertices; v++)
            if (mstSet[v] == 0 && key[v] < min)
                min = key[v], u = v;

        // Add the picked vertex to the MST Set
        mstSet[u] = 1;

        // Update key value and parent index of the adjacent vertices of the picked vertex.
        // Consider only those vertices which are not yet included in MST
        struct Node* temp = graph->adjList[u];
        while (temp != NULL) {
            int v = temp->vertex;
            int weight = temp->weight;
            if (mstSet[v] == 0 && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
            }
            temp = temp->next;
        }
    }

    // Print the constructed MST
    printf("Edge   Weight\n");
    for (int i = 1; i < graph->vertices; i++)
        printf("%d - %d    %d \n", parent[i], i, key[i]);
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

    // Freeing memory
    for (int i = 0; i < vertices; i++) {
        struct Node* temp = graph->adjList[i];
        while (temp) {
            struct Node* prev = temp;
            temp = temp->next;
            free(prev);
        }
    }
    free(graph->adjList);
    free(graph);

    return 0;
}
