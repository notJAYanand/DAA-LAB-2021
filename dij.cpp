#include <iostream>
using namespace std;
int count = 0;

struct AdjListNode
{
    int dest;
    int weight;
    struct AdjListNode *next;
};

struct AdjList
{

    struct AdjListNode *head;
};

struct Graph
{
    int V;
    struct AdjList *array;
};

struct AdjListNode *newAdjListNode(
    int dest, int weight)
{
    struct AdjListNode *newNode =
        (struct AdjListNode *)
            malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

struct Graph *createGraph(int V)
{
    struct Graph *graph = (struct Graph *)
        malloc(sizeof(struct Graph));
    graph->V = V;

    graph->array = (struct AdjList *)
        malloc(V * sizeof(struct AdjList));

    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}
void addEdge(struct Graph *graph, int src,int dest, int weight)
{

    struct AdjListNode *newNode =
        newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

struct MinHeapNode
{
    int v;
    int dist;
};

struct MinHeap
{

    int size;
    int capacity;
    int *pos;
    struct MinHeapNode **array;
};

struct MinHeapNode *newMinHeapNode(int v,int dist)
{
    struct MinHeapNode *minHeapNode =
        (struct MinHeapNode *)
            malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

struct MinHeap *createMinHeap(int capacity)
{
    struct MinHeap *minHeap =
        (struct MinHeap *)
            malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(
        capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =
        (struct MinHeapNode **)
            malloc(capacity *
                   sizeof(struct MinHeapNode *));
    return minHeap;
}
void swapMinHeapNode(struct MinHeapNode **a,
                     struct MinHeapNode **b)
{
    struct MinHeapNode *t = *a;
    *a = *b;
    *b = t;
}
void minHeapify(struct MinHeap *minHeap,
                int idx)
{
    count = count + 1;
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size &&
        minHeap->array[left]->dist <
            minHeap->array[smallest]->dist)
        smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right]->dist <
            minHeap->array[smallest]->dist)
        smallest = right;

    if (smallest != idx)
    {
        MinHeapNode *smallestNode =
            minHeap->array[smallest];
        MinHeapNode *idxNode =
            minHeap->array[idx];

        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        swapMinHeapNode(&minHeap->array[smallest],
                        &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

int isEmpty(struct MinHeap *minHeap)
{
    return minHeap->size == 0;
}

struct MinHeapNode *extractMin(struct MinHeap *minHeap)
{
    count = count + 1;
    if (isEmpty(minHeap))
        return NULL;

    struct MinHeapNode *root =
        minHeap->array[0];
    struct MinHeapNode *lastNode =
        minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;

    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

void decreaseKey(struct MinHeap *minHeap,int v, int dist)
{

    int i = minHeap->pos[v];
    minHeap->array[i]->dist = dist;

    while (i && minHeap->array[i]->dist <
                    minHeap->array[(i - 1) / 2]->dist)
    {
        minHeap->pos[minHeap->array[i]->v] =
            (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
        swapMinHeapNode(&minHeap->array[i],
                        &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
        count = count + 1;
    }
}

bool isInMinHeap(struct MinHeap *minHeap, int v)
{
    if (minHeap->pos[v] < minHeap->size)
        return true;
    return false;
}
void printArr(int dist[], int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}
void dijkstra(struct Graph *graph, int src)
{

    int V = graph->V;
    int dist[V];
    struct MinHeap *minHeap = createMinHeap(V);
    for (int v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }
    minHeap->array[src] =
        newMinHeapNode(src, dist[src]);
    minHeap->pos[src] = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);

    minHeap->size = V;
    while (!isEmpty(minHeap))
    {
        struct MinHeapNode *minHeapNode =
            extractMin(minHeap);
        int u = minHeapNode->v;
        struct AdjListNode *pCrawl =
            graph->array[u].head;
        while (pCrawl != NULL)
        {
            int v = pCrawl->dest;
            if (isInMinHeap(minHeap, v) &&
                dist[u] != INT_MAX &&
                pCrawl->weight + dist[u] < dist[v])
            {
                dist[v] = dist[u] + pCrawl->weight;
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
        count = count + 1;
    }
    printArr(dist, V);
}
int main()
{
    int V = 20;
    struct Graph *graph = createGraph(V);
    // 20 31
    addEdge(graph, 0, 4, 38);
    addEdge(graph, 2, 0, 38);
    addEdge(graph, 2, 4, 26);
    addEdge(graph, 3, 8, 50);
    addEdge(graph, 3, 14, 11);
    addEdge(graph, 4, 5, 42);
    addEdge(graph, 4, 14, 1);
    addEdge(graph, 4, 15, 5);
    addEdge(graph, 5, 7, 42);
    addEdge(graph, 5, 11, 27);
    addEdge(graph, 5, 17, 38);
    addEdge(graph, 6, 7, 47);
    addEdge(graph, 6, 10, 30);
    addEdge(graph, 6, 12, 5);
    addEdge(graph, 8, 12, 46);
    addEdge(graph, 8, 15, 20);
    addEdge(graph, 9, 1, 35);
    addEdge(graph, 9, 3, 31);
    addEdge(graph, 11, 7, 49);
    addEdge(graph, 12, 18, 12);
    addEdge(graph, 13, 7, 28);
    addEdge(graph, 13, 11, 12);
    addEdge(graph, 14, 0, 46);
    addEdge(graph, 15, 12, 28);
    addEdge(graph, 16, 12, 49);
    addEdge(graph, 16, 13, 18);
    addEdge(graph, 17, 2, 22);
    addEdge(graph, 17, 13, 25);
    addEdge(graph, 17, 15, 12);
    addEdge(graph, 18, 5, 15);
    addEdge(graph, 19, 18, 15);

    // 10 15

    // addEdge(graph, 0, 1, 4);
    // addEdge(graph, 0, 7, 8);
    // addEdge(graph, 1, 2, 8);
    // addEdge(graph, 1, 7, 11);
    // addEdge(graph, 2, 3, 7);
    // addEdge(graph, 2, 8, 2);
    // addEdge(graph, 2, 5, 4);
    // addEdge(graph, 3, 4, 9);
    // addEdge(graph, 3, 5, 14);
    // addEdge(graph, 4, 5, 10);
    // addEdge(graph, 5, 6, 2);
    // addEdge(graph, 6, 7, 1);
    // addEdge(graph, 6, 8, 6);
    // addEdge(graph, 7, 8, 7);
    // addEdge(graph, 9, 8, 5);

    //50 61

    // addEdge(graph,0 ,2 ,29);
    // addEdge(graph,1 ,20 ,25);
    // addEdge(graph,1 ,32 ,33);
    // addEdge(graph,2 ,18 ,23);
    // addEdge(graph,3 ,22 ,46);
    // addEdge(graph,6 ,25 ,5);
    // addEdge(graph,7 ,19 ,10);
    // addEdge(graph,8 ,17 ,20);
    // addEdge(graph,8 ,27 ,17);
    // addEdge(graph,9 ,26 ,16);
    // addEdge(graph,9 ,31 ,19);
    // addEdge(graph,10 ,0 ,1);
    // addEdge(graph,10 ,12 ,16);
    // addEdge(graph,10 ,43 ,35);
    // addEdge(graph,10 ,47 ,2);
    // addEdge(graph,11 ,38 ,40);
    // addEdge(graph,12 ,28 ,28);
    // addEdge(graph,13 ,34 ,29);
    // addEdge(graph,14 ,18 ,6);
    // addEdge(graph,14 ,43 ,11);
    // addEdge(graph,16 ,7 ,48);
    // addEdge(graph,17 ,6 ,39);
    // addEdge(graph,19 ,43 ,22);
    // addEdge(graph,20 ,34 ,33);
    // addEdge(graph,21 ,31 ,14);
    // addEdge(graph,22 ,32 ,42);
    // addEdge(graph,24 ,32 ,31);
    // addEdge(graph,25 ,31 ,38);
    // addEdge(graph,27 ,9 ,42);
    // addEdge(graph,27 ,48 ,7);
    // addEdge(graph,29 ,14 ,15);
    // addEdge(graph,29 ,41 ,8);
    // addEdge(graph,30 ,1 ,9);
    // addEdge(graph,30 ,14 ,32);
    // addEdge(graph,32 ,4 ,29);
    // addEdge(graph,32 ,12 ,18);
    // addEdge(graph,33 ,4 ,39);
    // addEdge(graph,34 ,17 ,3);
    // addEdge(graph,35 ,1 ,17);
    // addEdge(graph,36 ,31 ,18);
    // addEdge(graph,37 ,22 ,46);
    // addEdge(graph,37 ,32 ,17);
    // addEdge(graph,37 ,40 ,17);
    // addEdge(graph,37 ,46 ,12);
    // addEdge(graph,38 ,20 ,7);
    // addEdge(graph,38 ,41 ,7);
    // addEdge(graph,39 ,23 ,28);
    // addEdge(graph,39 ,27 ,15);
    // addEdge(graph,41 ,13 ,14);
    // addEdge(graph,42 ,7 ,6);
    // addEdge(graph,42 ,18 ,41);
    // addEdge(graph,42 ,41 ,20);
    // addEdge(graph,44 ,6 ,11);
    // addEdge(graph,44 ,32 ,26);
    // addEdge(graph,45 ,22 ,13);
    // addEdge(graph,46 ,12 ,6);
    // addEdge(graph,46 ,14 ,26);
    // addEdge(graph,46 ,20 ,34);
    // addEdge(graph,48 ,2 ,39);
    // addEdge(graph,48 ,23 ,8);
    // addEdge(graph,49 ,0 ,8);
    
    dijkstra(graph, 0);
    cout << endl;

    cout << "count = " << count << endl;
    return 0;
}