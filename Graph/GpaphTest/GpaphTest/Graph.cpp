#include"Graph.h"
#include<iostream>
using std::cout;
using std::endl;
void GreatGraph(Graph* g, int ar[5][5])
{
	int i, j;
	Node* p;

	for (i = 0; i < g->amount; i++)
	{
		g->list[i].data = i + 1;		//头结点
		g->list[i].next = NULL;			//指针域赋初值
	}

	for (i = 0; i < g->amount; i++)
		for (j = g->amount - 1; j >= 0; j--)
			if (ar[i][j] != 0)				
			{
				p = (Node*)malloc(sizeof(Node));

				if (p)							//采用头插法
				{
					p->data = j + 1;
					p->next = g->list[i].next;
					p->weight = ar[i][j];		//边的权重

					g->list[i].next = p;
				}
			}
}

void DFS(Graph* G, int visit[], int d_node)
{
	int d;
	Node* p;

	cout << d_node << "    ";
	visit[d_node - 1] = 1;			//标记为已访问

	p = G->list[d_node - 1].next;	//转向下一个邻接点

	while (p)				//若p是NULL则说明节点周围没有邻接边		
	{								
		d = p->data;
		if (!visit[d-1])		//未访问时
			DFS(G, visit, d);
		p = p->next;
	}
}

void BFS(Graph* G, int visit[], int d_node)
{
	int d;
	Node* p;
	Queue Q;

	cout << d_node << "    ";
	visit[d_node-1] = 1;		//设置为访问过

	Push(&Q, d_node);		//入队
	while (!IsEmpty(&Q))	//队不为空
	{
		Del(&Q, &d);
		p = G->list[d - 1].next;
		
		while (p)
		{
			if (!visit[p->data-1])	//如果未被访问
			{
				cout << p->data << "    ";
				visit[p->data-1] = 1;	//标记为访问过
				Push(&Q, p->data);
			}
			p = p->next;
		}
	}
}

void DestroyGraph(Graph* G)
{
	int i;
	Node* pre,*p;

	for (i = 0; i < G->amount; i++)
	{
		p = G->list[i].next;
		while (p)
		{
			pre = p->next;
			free(p);
			p = pre;
		}
	}
	//若G是动态分配的，则需要  free(G);
}






//环形队列的方法定义
bool IsEmpty(Queue* q)	//通过判断rear和front是否相等来判断空
{
	return q->rear == q->front;
}

bool IsFull(Queue* q)	//通过判断队尾指针循环递增1时等于队首来判读满
{
	return (q->rear + 1) % MAXSIZE == q->front;
}

bool Push(Queue* q, int num)	//保留一个空位置存放队头指针,此时最大存放数目是MAXSIZE-1
{
	if (!IsFull(q))
	{
		q->rear = (q->rear + 1) % MAXSIZE;
		q->data[q->rear] = num;

		return true;
	}
	return false;
}

bool Del(Queue* q, int* x)
{
	if (!IsEmpty(q))
	{
		q->front = (q->front + 1) % MAXSIZE;
		*x = q->data[q->front];
		return true;
	}

	return false;
}