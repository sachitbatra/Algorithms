#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Edge
{
	int src, dest, weight;
};

struct Graph
{
	int V, E;

	struct Edge* edge;
};

struct subset
{
	int parent;
	int rank;
};

void drawGraph(struct Graph* graph);
void drawTree(struct Edge *array, int numVertices);
void drawClusters(struct Graph* graph, int numClusters, struct Edge *array, int arrayBound, struct Edge min_edge);
int find(struct subset subsets[], int i);
void Union(struct subset subsets[], int x, int y);
int edgeComp(const void* a, const void* b);
void KruskalMST(struct Graph* graph);
void clustering(struct Graph* graph, int numClusters);

int main()
{
	int numVertices, numEdges;
	printf("Enter the number of vertices in the graph: ");
	scanf("%d", &numVertices);

    printf("Enter the number of edges in the graph: ");
    scanf("%d", &numEdges);

    struct Graph* inputGraph = (struct Graph*)malloc(sizeof(struct Graph));
    inputGraph->V = numVertices;
	inputGraph->E = numEdges;
	inputGraph->edge = (struct Edge*)malloc(numEdges * sizeof(struct Edge));

    for (int i=0; i<numEdges; i++)
    {
        int source, dest, weight;
        printf("Enter source vertex of edge %d: ", (i+1));
        scanf("%d", &source);
        printf("Enter destination vertex of edge %d: ", (i+1));
        scanf("%d", &dest);
        printf("Enter weight of edge %d: ", (i+1));
        scanf("%d", &weight);
        inputGraph->edge[i].src = source;
        inputGraph->edge[i].dest = dest;
        inputGraph->edge[i].weight = weight;
    }

    drawGraph(inputGraph);
	KruskalMST(inputGraph);

	system("dot -Tpng inputGraph.dot -o InputGraph.png");
	system("dot -Tpng spanningTree.dot -o MinimumSpanningTree.png");

	system("del /f inputGraph.dot");
	system("del /f spanningTree.dot");

	int numClusters;
    printf("Enter the number of clusters: ");
    scanf("%d", &numClusters);
    clustering(inputGraph, numClusters);

    system("dot -Tpng clusters.dot -o KClustering.png");
    system("del /f clusters.dot");

	return 0;

	system("InputGraph.png");
	system("MinimumSpanningTree.png");
	system("KClustering.png");
}

void drawGraph(struct Graph* graph)
{
    FILE *fileOp = fopen("inputGraph.dot", "w");
    fprintf(fileOp, "digraph BST\n{\n");
    fprintf(fileOp, "label = \"Input Graph\"\n");

    for (int i=0; i<graph->E; i++)
    {
        fprintf(fileOp, "%c -> %c [dir=none, label=\"%d\"];\n", (graph->edge[i].src + 65), (graph->edge[i].dest + 65), graph->edge[i].weight);
    }

    fprintf(fileOp, "\n}");
    fclose(fileOp);
}

void drawTree(struct Edge *array, int numVertices)
{
    FILE *fileOp = fopen("spanningTree.dot", "w");
    fprintf(fileOp, "digraph BST\n{\n");
    fprintf(fileOp, "label = \"Minimum Spanning Tree\"\n");

    for (int i=0; i<(numVertices - 1); i++)
    {
        fprintf(fileOp, "%c -> %c [dir=none, label=\"%d\"];\n", (array[i].src + 65), (array[i].dest + 65), array[i].weight);
    }

    fprintf(fileOp, "\n}");
    fclose(fileOp);
}

void drawClusters(struct Graph* graph, int numClusters, struct Edge *array, int arrayBound, struct Edge min_edge)
{
    FILE *fileOp = fopen("clusters.dot", "w");
    fprintf(fileOp, "digraph BST\n{\n");
    fprintf(fileOp, "label = \"%d Clusters\"\n", numClusters);

    for (int i=0; i<graph->V; i++)
    {
        fprintf(fileOp, "%c [color = \"blue\"];", (i + 65));
    }

    for (int i=0; i<=arrayBound; i++)
    {
        fprintf(fileOp, "%c -> %c [dir=none, label=\"%d\"];\n", (array[i].src + 65), (array[i].dest + 65), array[i].weight);
    }

    if (min_edge.weight != -1)
    {
        fprintf(fileOp, "%c -> %c [dir=none, label=\"Spacing: %d\" style=\"dashed\"];\n", (min_edge.src + 65), (min_edge.dest + 65), min_edge.weight);
    }

    fprintf(fileOp, "\n}");
    fclose(fileOp);
}

int find(struct subset subsets[], int i)
{
	if (subsets[i].parent != i)
    {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }

	return subsets[i].parent;
}

void Union(struct subset subsets[], int x, int y)
{
	int xroot = find(subsets, x);
	int yroot = find(subsets, y);

	if (subsets[xroot].rank < subsets[yroot].rank)
    {
        subsets[xroot].parent = yroot;
    }

	else if (subsets[xroot].rank > subsets[yroot].rank)
    {
        subsets[yroot].parent = xroot;
    }

	else
	{
		subsets[yroot].parent = xroot;
		subsets[xroot].rank++;
	}
}

int edgeComp(const void* a, const void* b)
{
	struct Edge* a1 = (struct Edge*)a;
	struct Edge* b1 = (struct Edge*)b;
	return a1->weight < b1->weight;
}

void KruskalMST(struct Graph* graph)
{
	int V = graph->V;
	struct Edge *result = (struct edge*)malloc((V-1) * sizeof(struct Edge));
	int resultIndex = 0;
	int inputIndex = 0;

	qsort(graph->edge, graph->E, sizeof(graph->edge[0]), edgeComp);

	struct subset *subsets = (struct subset*) malloc( V * sizeof(struct subset) );

	for (int v = 0; v < V; ++v)
	{
		subsets[v].parent = v;
		subsets[v].rank = 0;
	}

	while (resultIndex < V - 1)
	{
		struct Edge next_edge = graph->edge[inputIndex++];

		int x = find(subsets, next_edge.src);
		int y = find(subsets, next_edge.dest);

		if (x != y)
		{
			result[resultIndex++] = next_edge;
			Union(subsets, x, y);
		}
	}

    drawTree(result, graph->V);

	return;
}

void clustering(struct Graph* graph, int numClusters)
{
    int clusters = graph->V;

    if ((numClusters > clusters) || (numClusters < 1))
    {
        printf("Invalid number of clusters.\n");
        return;
    }

	int V = graph->V;
    struct Edge *result = (struct edge*)malloc((V-1) * sizeof(struct Edge));
	int resultIndex = 0;
	int inputIndex = 0;

	qsort(graph->edge, graph->E, sizeof(graph->edge[0]), edgeComp);

	struct subset *subsets = (struct subset*) malloc( V * sizeof(struct subset) );

	for (int v = 0; v < V; ++v)
	{
		subsets[v].parent = v;
		subsets[v].rank = 0;
	}

	while (clusters != numClusters)
	{
		struct Edge next_edge = graph->edge[inputIndex++];

		int x = find(subsets, next_edge.src);
		int y = find(subsets, next_edge.dest);

		if (x != y)
		{
			result[resultIndex++] = next_edge;
			Union(subsets, x, y);
			clusters--;
		}
	}
	resultIndex--;

    struct Edge min_edge;
    min_edge.weight = -1;

    while (inputIndex < graph->E)
    {
        struct Edge next_edge = graph->edge[inputIndex++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        if (x != y)
        {
            min_edge = next_edge;
            break;
        }
    }

	drawClusters(graph, numClusters, result, resultIndex, min_edge);
    return;
}
