#include <stdio.h>

typedef  char   VertaxType;
typedef  int    ArcType;

#define INFINITY    65535

static char charrctor[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

static int  relatition[8][8] = 
{
	{0, 3, 6, 0, 0, 0, 0, 0},
	{3, 0, 0, 9, 7, 0, 0, 0},
	{6, 0, 0, 0, 0, 1, 4, 0},
	{0, 9, 0, 0, 0, 0, 0, 5},
	{0, 7, 0, 0, 0, 0, 0, 8},
	{0, 0, 1, 0, 0, 0, 2, 0},
	{0, 0, 0, 0, 0, 2, 0, 0},
	{0, 0, 0, 5, 8, 0, 0, 0}
};

class MGraph {
public:
	MGraph(int edge, int side);
	~MGraph();


public:
	void printVertax();
	void printArc();
	// Depth First Search
	void DFS(VertaxType Vertax, int i);
	void DFSTraverse();
private:

	int  edgenum;   // 当前图中的顶点数
	int  sidenum;   // 当前图中的边数
	VertaxType vertax[8]; // 顶点数组
	ArcType    arc[8][8];    // 邻接矩阵
};
 
MGraph::MGraph(int edge = 8, int side = 9):
	edgenum(edge),
	sidenum(side)
{
		int i, j;
		
		// 初始化顶点数组
		printf("初始化顶点数组\n");
		for (i = 0; i< 8; i++) {
			vertax[i] = charrctor[i];
		}
		
		// 清空邻接矩阵
		printf("清空邻接矩阵\n");
		for (i = 0; i < 8; ++i)
		{
			for (j = 0; j < 8; ++j) {
				arc[i][j] = INFINITY;
			}
		}
		
		// 初始化邻接矩阵
		printf("初始化邻接矩阵\n");
		for (i = 0; i< 8; i++) {
			for(j = 0; j< 8; j++) {
				arc[i][j] = relatition[i][j];
			}
		}
}

void MGraph::printVertax() {
		printf("打印Vertax\nVertax : ");
		for (int i = 0; i< 8; i++) {
			printf("%c ", vertax[i]);
		}
		printf("\n");
	
}
void MGraph::printArc() {
	int i, j;
	printf("打印Arc\nArc : \n");
	for (i = 0; i< 8;i++) {
		for(j = 0; j< 8; j++) {
			printf("%d ", arc[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

// Depth First Search
// 深度优先必须借助一个数组来记录顶点是否被遍历

bool visited[8];
void MGraph::DFS(VertaxType Vertax, int i) {
	// 第i 个顶点已经被遍历；
	visited[i] = true;
	printf("顶点：%c 被遍历\n", Vertax);
	for (int j = 0; j < 8; j++) {
		if (arc[i][j] > 0 && !visited[j]) {
			printf("%c 的下一个顶点是 %c\n", Vertax, vertax[j]);
			printf("%c--%c 度为%d\n", Vertax, vertax[j], arc[i][j]);
			DFS(vertax[j], j);
		}
	}
}

void MGraph::DFSTraverse() {
	// 初始化标记数组
	for (int i = 0; i < 8; i++) {
		visited[i] = false;
	}
	
	for (int i = 0; i< 8; i++) {
		if (!visited[i]) {
			DFS(vertax[i], i);
		}
	}
	printf("\n");
	
}
	
int main() {
		MGraph *Mgh = new MGraph();
		Mgh->printVertax();
		Mgh->printArc();
		Mgh->DFSTraverse();
	
}



















