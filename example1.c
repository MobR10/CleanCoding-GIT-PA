/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
} NODE;
/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa

typedef struct g
{
    int vertices;
    int *visited;
    struct Node **adjacentNode;
} GPH;

typedef struct s
{
    int index;
    int vertices;
    int *array;
} STK;

void checkAllocation(void *ptr)
{
    if(ptr==NULL)
    {
        puts("Memory allocation failed!");
        exit(1);
    }
}
NODE *createNode(int Data)
{
    NODE *new = (NODE *)malloc(sizeof(NODE));
    checkAllocation(new);
    new->data = Data;
    new->next = NULL;
    return new;
}

void addEdge(GPH *graph, int source, int destination)
{
    NODE *node = createNode(destination);
    node->next = graph->adjacentNode[source];
    graph->adjacentNode[source] = node;

    node = createNode(source);
    node->next = graph->adjacentNode[destination];
    graph->adjacentNode[destination] = node;
}

GPH *createGraph(int vertices)
{
    GPH *graph = (GPH *)malloc(sizeof(GPH));
    checkAllocation(graph);
    graph->vertices = vertices;
    graph->adjacentNode = (NODE **)malloc(sizeof(NODE*) * (long long unsigned int)vertices);
    checkAllocation(graph->adjacentNode);
    graph->visited = (int *)malloc(sizeof(int) * (long long unsigned int)vertices);
    checkAllocation(graph->visited);

    for (int i = 0; i < vertices; i++)
    {
        graph->adjacentNode[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

STK *createStack(int vertices)
{
    STK *stack = (STK *)malloc(sizeof(STK));
    stack->array = (int *)malloc((long long unsigned int) vertices * sizeof(int));
    stack->index = 0;
    stack->vertices = vertices;

    return stack;
}

void push(int data, STK *stack)
{
    stack->index = stack->index + 1;
    stack->array = (int *)realloc(stack->array, (long long unsigned int)stack->index * sizeof(int));
    stack->array[stack->index] = data;
}

void DFS(GPH *graph, STK *stack, int vertex)
{
    NODE *adjacencyList = graph->adjacentNode[vertex];
    graph->visited[vertex] = 1;
    printf("%d ", vertex);
    push(vertex, stack);
    while (adjacencyList != NULL)
    {
        int adjacentVertex= adjacencyList->data;
        if (graph->visited[vertex] == 0)
            DFS(graph, stack, vertex);
        adjacencyList = adjacencyList->next;
    }
}

void insertEdges(GPH *graph, int numberOfEdges, int vertices)
{
    int src, dest, i;
    printf("adauga %d munchii (de la 1 la %d)\n", numberOfEdges, vertices);
    for (i = 0; i < numberOfEdges; i++)
    {
        scanf("%d%d", &src, &dest);
        addEdge(graph, src, dest);
    }
}

void wipe(GPH *graph, int vertices)
{
    for (int i = 0; i < vertices; i++)
    {
        graph->visited[i] = 0;
    }
}

//0 sau 1 daca poate fi sau nu ajuns
int canBe(GPH *graph, int vertices, STK *stack1, STK *stack2)
{
    int canbe = 0;
    for (int i = 0; i < vertices; i++) // aici i tine loc de numar adica de restaurant
    {
        {for (int j = 0; j < 5; j++)
        }
        DFS(graph, stack1, i);
        wipe(graph, vertices);
        DFS(graph, stack2, j);
        for (int j = 0; j < vertices && !ans; j++)
            for (int i = 0; i < vertices && !ans; i++)
                if ((stack1->array[i] == j) && (stack2->array[j] == i))
                    canbe = 1;
    }
    return canBe;
}

int canReach(GPH *graph, int source, int destination) {
    // Perform DFS from the source vertex
    DFS(graph, NULL, source);

    // Check if the destination vertex was visited
    int result = graph->visited[destination];

    // Reset the visited array for future operations
    wipe(graph, graph->vertices);

    return result;
}

int main()
{

    int vertices;
    int edges;

    printf("cate noduri are graful?");
    scanf("%d", &vertices);

    printf("cate muchii are graful?");
    scanf("%d", &edges);

    GPH *graph = createGraph(vertices);

    STK *stack1 = createStack(2 * vertices);
    STK *stack2 = createStack(2 * vertices);

    insertEdges(graph, edges, vertices);

    canBe(graph, vertices, stack1, stack2);
}
