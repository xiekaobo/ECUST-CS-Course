#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<iostream>
#include<queue> 
typedef struct GNode *MGraph;
struct GNode{
    int Nv;
    int Ne;
    int G[100][100];
};
typedef struct ENode *Edge;
struct ENode{
    int V1,V2;
};
bool Visit[100]={false};
int A;
MGraph CreateGraph(int Vernum)
{
    int V,W;
    MGraph Graph;
    Graph=(MGraph)malloc(sizeof(struct GNode));
    Graph->Nv=Vernum;
    Graph->Ne=0;
    for(V=0;V<Graph->Nv;V++)
    {
        for(W=0;W<Graph->Nv;W++)
        {
            Graph->G[V][W]=0;
        }
    }
    return Graph;
}
void Insertedge(MGraph Graph,Edge E)
{
    Graph->G[E->V1][E->V2]=1;
    Graph->G[E->V2][E->V1]=1;
}
MGraph BuildGraph()
{
    MGraph Graph;
    Edge E;
    int Vv;
    int NV,i;
    scanf("%d",&NV);
    A=NV;
    Graph=CreateGraph(NV);
    scanf("%d",&(Graph->Ne));
    if(Graph->Ne!=0)
    {
        E=(Edge)malloc(sizeof(struct ENode));
        for(i=0;i<Graph->Ne;i++)
        {
            scanf("%d %d",&E->V1,&E->V2);
            Insertedge(Graph,E);
        }
    }
    return Graph;
}
void DFS(MGraph Graph, int V)
{
    int W;
    if(Visit[V]==false)
    {
        printf("%d ",V);
        Visit[V]=true;
    }
    for(W=0;W<Graph->Nv;W++)
    {
        if((Visit[W]==false)&&(Graph->G[V][W]==1)) DFS(Graph,W);
    }
}
void BFS(MGraph Graph,int V)
{
	int W;
	std::queue<int> q1;
	printf("%d ",V);
	Visit[V]=true;
	q1.push(V);
	while(!q1.empty())
	{
		for(W=0;W<Graph->Nv;W++)
    	{
	        if((Visit[W]==false)&&(Graph->G[q1.front()][W]==1)) 
	        {
	        	printf("%d ",W);
	        	Visit[W]=true;
	        	q1.push(W);
			}
    	}
		q1.pop();
	}
}
int main()
{
    MGraph G1;
    int i;
    G1=BuildGraph();
    for(i=0;i<A;i++)
    {
        if(Visit[i]==true) continue;
        else
        {
            printf("{");
            DFS(G1,i);
            printf("}\n");
        }
    }
    for(i=0;i<A;i++)
    {
    	Visit[i]=false;
	}
	for(i=0;i<A;i++)
	{
		if(Visit[i]==true) continue;
		else
		{
			printf("{");
			BFS(G1,i);
			printf("}\n");
		}
	}
    return 0;
}

