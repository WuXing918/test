#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
#define GRAPH_VNODE_NUM 10

typedef char ArcNodeInfo; // 弧信息的类型
typedef int VNodeInfo; // 节点信息的类型

//弧节点
struct ArcNode {
 	int num; // 弧距离节点的位置
	ArcNode* next; // 指向下一个弧的指针
	ArcNodeInfo info; // 弧的信息
};

struct VNode {
	VNodeInfo info; // 节点信息
	ArcNode* firstedge;	 // 指向第一条弧的指针
};

// AdjList is an array type not an pointer type
//typedef VNode AdjList[GRAPH_VNODE_NUM];
typedef VNode AdjList;



class ALGraph {
public:
	ALGraph(int n, int e);
	~ALGraph();
	void ALGraph_Create();

private:
	AdjList adjlist[10];
	int n,e; 
};

ALGraph::ALGraph(int n, int e):n(n), e(e){
	// adjlist is an array type not a pointer type
	// adjlist = (AdjList)malloc(sizeof(VNode) * GRAPH_VNODE_NUM);
}
ALGraph::~ALGraph(){}
void ALGraph::ALGraph_Create(){
	// init the VNode 
	for (int i = 0; i < n; i++) {
		fflush(stdin);  
		cout << "please input the VNode info:" << endl;
		adjlist[i].info = getchar();
		adjlist[i].firstedge = NULL;
	}
	// init the ArcNode



}


int main() 
{
	ALGraph * Graph = new ALGraph(4,5);
	if (NULL != Graph) {
		cout << sizeof(Graph) << endl;
	}
	Graph->ALGraph_Create();	
}
