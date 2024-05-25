#include <stdio.h>
#include <stdlib.h>

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

void addEdge(struct Graph* graph, int v1, int v2) {
    graph->adjMatrix[v1][v2] = 1;
    graph->adjMatrix[v2][v1] = 1;
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

void DFS(struct Graph* graph, int start, int* visited) {
    int stack[graph->vertices];
    int top = -1; 
    int current;

    stack[++top] = start; 
    visited[start] = 1; 
    

    printf("%d ", start); 

    while (top != -1) {
        current = stack[top--]; 
        for (int i = 0; i < graph->vertices; i++) {
            if (graph->adjMatrix[current][i] == 1 && visited[i] == 0) {
                printf("%d ", i); 
                visited[i] = 1; 
                stack[++top] = i; 
            }
        }
    }
}


void BFS(struct Graph* graph, int start, int* visited) {
    int queue[graph->vertices], front = -1, rear = -1;
    printf("%d ", start);
    visited[start] = 1;
    queue[++rear] = start;
    while (front != rear) {
        start = queue[++front];
        for (int j = 0; j < graph->vertices; j++) {
            if (graph->adjMatrix[start][j] == 1 && visited[j] == 0) {
                printf("%d ", j);
                visited[j] = 1;
                queue[++rear] = j;
            }
        }
    }
}

int main() {
    int choice, v1, v2, vertices;
    struct Graph* graph = NULL;

    printf("Enter number of vertices: ");
    scanf("%d", &vertices);

    graph = create(vertices);
    int visited[vertices];

    do {
        printf("\n1. Add Edge\n");
        printf("2. Display Adjacency Matrix\n");
        printf("3. DFS\n");
        printf("4. BFS\n");
        printf("5. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter vertices: ");
            scanf("%d %d", &v1, &v2);
            if (v1 >= 0 && v1 < vertices && v2 >= 0 && v2 < vertices) {
                addEdge(graph, v1, v2);
            } else {
                printf("Invalid vertices.\n");
            }
            break;
        case 2:
            printf("Display: ");
            display(graph);
            break;
        case 3:
            printf("Enter start vertex: ");
            scanf("%d", &v1);
            if (v1 >= 0 && v1 < vertices) {
                printf("DFS traversal is: ");
                for (int i = 0; i < vertices; i++) visited[i] = 0;
                DFS(graph, v1, visited);
            } else {
                printf("Invalid start vertex.\n");
            }
            break;
        case 4:
            printf("Enter start vertex: ");
            scanf("%d", &v1);
            if (v1 >= 0 && v1 < vertices) {
                printf("BFS traversal is: ");
                for (int i = 0; i < vertices; i++) visited[i] = 0;
                BFS(graph, v1, visited);
            } else {
                printf("Invalid start vertex.\n");
            }
            break;
        case 5:
            printf("Exit\n");
            break;
        default:
            printf("Invalid choice\n");
        }
    } while (choice != 5);

    // Free memory
    for (int i = 0; i < vertices; i++) {
        free(graph->adjMatrix[i]);
    }
    free(graph->adjMatrix);
    free(graph);

    return 0;
}
