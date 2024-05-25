#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Graph {
    int numVertices;
    struct Node** adjacencyList;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Error: memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    if (graph == NULL) {
        printf("Error: memory allocation failed\n");
        exit(1);
    }
    graph->numVertices = numVertices;

    graph->adjacencyList = (struct Node**)malloc(numVertices * sizeof(struct Node*));
    if (graph->adjacencyList == NULL) {
        printf("Error: memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < numVertices; i++) {
        graph->adjacencyList[i] = NULL;
    }

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjacencyList[src];
    graph->adjacencyList[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjacencyList[dest];
    graph->adjacencyList[dest] = newNode;
}

void BFS(struct Graph* graph, int startVertex) {
    int* visited = (int*)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; i++) {
        visited[i] = 0; 
    }

    int queue[graph->numVertices];
    int front = 0, rear = -1;

    visited[startVertex] = 1;
    queue[++rear] = startVertex;

    printf("BFS Traversal: ");
    while (front <= rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        struct Node* temp = graph->adjacencyList[currentVertex];
        while (temp != NULL) {
            int adjVertex = temp->data;
            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                queue[++rear] = adjVertex;
            }
            temp = temp->next;
        }
    }
    printf("\n");
    free(visited);
}

void DFS(struct Graph* graph, int startVertex) {
    int* visited = (int*)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; i++) {
        visited[i] = 0; 
    }

    int stack[graph->numVertices];
    int top = -1;

    stack[++top] = startVertex;

    printf("DFS Traversal: ");
    while (top != -1) {
        int currentVertex = stack[top--];

        if (!visited[currentVertex]) {
            visited[currentVertex] = 1;
            printf("%d ", currentVertex);

            struct Node* temp = graph->adjacencyList[currentVertex];
            while (temp != NULL) {
                int adjVertex = temp->data;
                if (!visited[adjVertex]) {
                    stack[++top] = adjVertex;
                }
                temp = temp->next;
            }
        }
    }
    printf("\n");
    free(visited);
}

void displayAdjacencyList(struct Graph* graph) {
    printf("Adjacency List:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        struct Node* temp = graph->adjacencyList[i];
        printf("Vertex %d:", i);
        while (temp != NULL) {
            printf(" -> %d", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    int choice, numVertices, src, dest;
    struct Graph* graph = NULL;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Create Graph\n");
        printf("2. Add Edge\n");
        printf("3. Display Adjacency List\n");
        printf("4. BFS Traversal\n");
        printf("5. DFS Traversal\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the number of vertices: ");
                scanf("%d", &numVertices);
                graph = createGraph(numVertices);
                break;
            case 2:
                if (graph == NULL) {
                    printf("Create graph first!\n");
                    break;
                }
                printf("Enter the src and dest: ");
                scanf("%d %d", &src, &dest);
                if (src < 0 || src >= graph->numVertices || dest < 0 || dest >= graph->numVertices) {
                    printf("Invalid vertices\n");
                    break;
                }
                addEdge(graph, src, dest);
                break;
            case 3:
                if (graph == NULL) {
                    printf("Create graph first!\n");
                    break;
                }
                displayAdjacencyList(graph);
                break;
            case 4:
                if (graph == NULL) {
                    printf("Create graph first!\n");
                    break;
                }
                printf("Enter the starting vertex for BFS: ");
                scanf("%d", &src);
                if (src < 0 || src >= graph->numVertices) {
                    printf("Invalid vertex\n");
                    break;
                }
                BFS(graph, src);
                break;
            case 5:
                if (graph == NULL) {
                    printf("Create graph first!\n");
                    break;
                }
                printf("Enter the starting vertex for DFS: ");
                scanf("%d", &src);
                if (src < 0 || src >= graph->numVertices) {
                    printf("Invalid vertex\n");
                    break;
                }
                DFS(graph, src);
                break;
            case 6:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
