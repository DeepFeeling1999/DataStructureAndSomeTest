#include<stdbool.h>
typedef struct node
{
	char s_data;
	struct node* Lchild;
	struct node* Rchild;

}BNode;
typedef BNode* Tree;

bool CreatTree(char ar[], Tree tree)
{
	if (!ar)
		return false;
	else
	{

	}
}
bool IsEmpty(Tree tree);

void PreorderTraversal(Tree tree);
void InorderTraversal(Tree tree);
void PostorderTraversal(Tree tree);