/*parcurgerge  graf cu DFS/BFS*/

// Imi cer scuze in avans
//  nu te iert

#include <stdlib.h>
#include <stdio.h>

struct node
{
    int data;
    struct node *next;
};
typedef struct node Node;

struct graph
{
    int vertices;
    int *visited;
    Node **adjacencyList;
};
typedef struct graph Graph;

/// utils
void checkAllocation(void *ptr)
{
    if (ptr == NULL)
    {
        puts("Memory allocation failed!");
        exit(1);
    }
}
Node *createNode(int data)
{
    Node *new =(Node*) malloc(sizeof(Node));
    checkAllocation(new);
    new->data = data;
    new->next = NULL;
    return new;
}
Graph *createGraph(int vertices)
{
    Graph *graph =(Graph*) malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->adjacencyList =(Node**) malloc((unsigned long long int)(vertices+1) * sizeof(Node *));

    graph->visited =(int*) malloc(sizeof(int) * (unsigned long long int)(vertices+1));
    for (int i = 1; i <= vertices; i++)
    {
        graph->adjacencyList[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void addEdge(Graph *graph, int source, int destination)
{
    Node *node = createNode(destination);
    node->next = graph->adjacencyList[source];
    graph->adjacencyList[source] = node;

    node = createNode(source);
    node->next = graph->adjacencyList[destination];
    graph->adjacencyList[destination] = node;
}

void insertEdges(Graph *graph, int edges)
{
    int src, dest, i;
    printf("adauga %d muchii (de la 1 la %d)\n", edges, graph->vertices);
    for (i = 0; i < edges; i++)
    {
        scanf("%d%d", &src, &dest);
        addEdge(graph, src, dest);
    }
}
/// bfs utils
int isEmpty(Node *queue)
{
    return queue == NULL;
}

void enqueue(Node **queue, int data)
{
    Node *new_node = createNode(data);

    if (isEmpty(*queue))
        *queue = new_node;
    else
    {
        Node *temp = (*queue);
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

int dequeue(Node **queue)
{
    int data = (*queue)->data;
    Node *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

void printGraph(Graph *graph)
{
    int i;
    for (i = 1; i <= graph->vertices; i++)
    {
        Node *adjacencyList = graph->adjacencyList[i];
        printf("%d: ",i);
        while (adjacencyList)
        {
            printf("%d ", adjacencyList->data);
            adjacencyList= adjacencyList->next;
        }
        printf("\n");
    }
}

void printQueue(Node *queue)
{
    while (queue != NULL)
    {
        printf("%d ", queue->data);
        queue =queue->next;
    }
}

void wipeVisitedList(Graph *graph)
{
    for (int i = 1;i <= graph->vertices; i++)
    {
        graph->visited[i] = 0;
    }
}
// parcurgeri
void DFS(Graph *graph, int currentVertex)
{
    Node *adjacencyList = graph->adjacencyList[currentVertex];

    graph->visited[currentVertex] = 1;
    printf("%d->", currentVertex);

    while (adjacencyList != NULL)
    {
        int neighbour = adjacencyList->data;

        if (graph->visited[neighbour] == 0)
        {
            DFS(graph, neighbour);
        }
        adjacencyList = adjacencyList->next;
    }
}

void BFS(Graph *graph, int start)
{
    Node *queue = NULL;

    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!isEmpty(queue))
    {
        int current = dequeue(&queue);
        printf("%d ", current);

        Node *adjacencyList = graph->adjacencyList[current];

        while (adjacencyList)
        {
            int neighbour = adjacencyList->data;

            if (graph->visited[neighbour] == 0)
            {
                graph->visited[neighbour] = 1;
                enqueue(&queue, neighbour);
            }
            adjacencyList = adjacencyList->next;
        }
    }
}

int main()
{

    int vertices;
    int edges;
    int startingVertex;

    printf("cate noduri are graful?");
    scanf("%d", &vertices);

    printf("cate muchii are graful?");
    scanf("%d", &edges);

    Graph *graph = createGraph(vertices);

    insertEdges(graph,edges);

    printf("de unde plecam in DFS?");
    scanf("%d", &startingVertex);

    printf("parcurgere cu DFS:");
    DFS(graph, startingVertex);

    wipeVisitedList(graph);
    printf("\n");

    printf("de unde plecam in BFS?");
    scanf("%d", &startingVertex);

    printf("parcurgere cu BFS:");
    BFS(graph, startingVertex);

    return 0;
}
