/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/

#include <stdlib.h>
#include <stdio.h>

struct node
{
    int restaurant;
    struct node *next;
};
typedef struct node Node;
/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa

struct graph
{
    int vertices;
    int *visited;
    Node **adjacentList;
};
typedef struct graph Graph;
struct stack
{
    int index;
    int capacity;
    int *array;
};
typedef struct stack Stack;

void checkAllocation(void *ptr)
{
    if (ptr == NULL)
    {
        puts("Memory allocation failed!");
        exit(1);
    }
}
Node *createNode(int restaurant)
{
    Node *new = (Node *)malloc(sizeof(Node));
    new->restaurant = restaurant;
    new->next = NULL;
    return new;
}

// adauga muchiile corespunzatoare restaurantelor in lista de adiacenta
void addEdge(Graph *graph, int source, int destination)
{
    Node *node = createNode(destination);
    checkAllocation(node);
    node->next = graph->adjacentList[source];
    graph->adjacentList[source] = node;

    node = createNode(source);
    node->next = graph->adjacentList[destination];
    graph->adjacentList[destination] = node;
}

// creeaza un graf neorientat de restaurante
Graph *createGraph(int vertices)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    checkAllocation(graph);
    graph->vertices = vertices;
    graph->adjacentList = (Node **)malloc(sizeof(Node *) * (long long unsigned int)(vertices+1));
    checkAllocation(graph->adjacentList);
    graph->visited = (int *)malloc(sizeof(int) * (long long unsigned int)(vertices+1));
    checkAllocation(graph->visited);

    for (int i = 1; i <= vertices; i++)
    {
        graph->adjacentList[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

Stack *createStack(int capacity)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->array = (int *)malloc((long long unsigned int)capacity * sizeof(int));
    stack->index = -1;
    stack->capacity = capacity;

    return stack;
}

// adauga un restaurant in varful stivei
void push(int vertex, Stack *stack)
{
    stack->index = stack->index + 1;
    stack->array[stack->index] = vertex;
}

// algoritmul de parcurgere a grafului
void DFS(Graph *graph, Stack *stack, int vertex)
{
    Node *adjacencyList = graph->adjacentList[vertex];
    graph->visited[vertex] = 1;
    //printf("%d\n", vertex);
    push(vertex, stack);
    while (adjacencyList != NULL)
    {
        int adjacentVertex = adjacencyList->restaurant;
        if (graph->visited[adjacentVertex] == 0)
            DFS(graph, stack, adjacentVertex);
        adjacencyList = adjacencyList->next;
    }
}

// functie de pregatire pentru a adauga muchiile
void insertEdges(Graph *graph, int numberOfEdges, int vertices)
{
    int src, dest, i;
    printf("adauga %d munchii (de la 1 la %d)\n", numberOfEdges, vertices);
    for (i = 0; i < numberOfEdges; i++)
    {
        scanf("%d%d", &src, &dest);
        addEdge(graph, src, dest);
    }
}

// reseteaza vectorul de noduri vizitate
void wipe(Graph *graph)
{
    for (int i = 1; i <= graph->vertices ; i++)
    {
        graph->visited[i] = 0;
    }
}

// teoretic, codul asta ar vrea sa verifice daca exista macar un drum care are 2 noduri comune, ceea ce nu e scopul enuntat la primul comentariu, asa ca
// fac functia corecta mai jos
// void canbe(GPH *g, int nrv, Stack *s1, Stack *s2)// 0 sau 1 daca poate fi sau nu ajuns
// {
//     int *canbe = calloc(5, sizeof(int));
//     for (int i = 0; i < nrv; i++) // aici i tine loc de numar adica de restaurant{for (int j = 0; j < 5; j++)
//         {
//             DFS(g, s1, i);
//             wipe(g, nrv);
//             DFS(g, s2, j);
//             for (int j = 0; j < nrv && !ans; j++)
//             for (int i = 0; i < nrv && !ans; i++)
//             if ((s1->arr[i] */== j) && (s2->arr[j] == i))
//             canbe = 1;
//                     }*/
//                 }

// 0 sau 1 daca poate fi sau nu ajuns  de la nodul sursa la destinatie
int canReach(Graph *graph, int src, int dest, Stack *stack)
{
    if(src<0 || src > graph->vertices)
        {
            puts("Restaurantul sursa nu exista in evidenta.");
        }
    else if (dest<0 || dest > graph->vertices)
    {
        puts("Restaurantul destinatie nu exista in evidenta.");
    }
    else
    {
        DFS(graph, stack, src);

    for (int i = 0; i <= stack->index; i++)
    {
        if (stack->array[i] == dest)
        {
            wipe(graph);
            return 1;
        }
    }

    wipe(graph);
    }
    return 0;
}

int main()
{

    int vertices;
    int edges;

    printf("cate noduri are graful?");
    scanf("%d", &vertices);

    printf("cate muchii are graful?");
    scanf("%d", &edges);

    Graph *graph = createGraph(vertices);

    Stack *stack1 = createStack(2 * vertices);

    insertEdges(graph, edges, vertices);

    printf("%d", canReach(graph, 1, 4, stack1));
}
