#include <stdio.h>
#include <stdlib.h>
typedef int BTDataType;
typedef struct BinaryTreeNode
{
	BTDataType data;
	struct BinaryTreeNode* left;
	struct BinaryTreeNode* right;
}BTNode;
BTNode* BuyNode(BTDataType x)
{
	BTNode* ret =(BTNode*)malloc(sizeof(BTNode));
	if (ret == NULL)
	{
		perror("malloc");
	}
	ret->data = x;
	ret->left = NULL;
	ret->right = NULL;
	return ret;
}
BTNode* CreatBinaryTree()
{
	BTNode* node1 = BuyNode(1);
	BTNode* node2 = BuyNode(2);
	BTNode* node3 = BuyNode(3);
	BTNode* node4 = BuyNode(4);
	BTNode* node5 = BuyNode(5);
	BTNode* node6 = BuyNode(6);

	node1->left = node2;
	node1->right = node4;
	node2->left = node3;
	node4->left = node5;
	node4->right = node6;
	return node1;
}
// 二叉树前序遍历-<根节点-左子树-右子树>-
void PreOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	printf("%d ", root->data);//先选择遇到根节点，遇到根节点之后再进入左子树
	PreOrder(root->left);//进入左子树
	PreOrder(root->right);//进入右子树
}
// 二叉树中序遍历
void InOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	InOrder(root->left);//先遍历左子树
	printf("%d ", root->data);//遍历完左子树后再访问节点内容
	InOrder(root->right);//访问完节点内容后再遍历右子树
}
// 二叉树后序遍历
void PostOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	PostOrder(root->left);
	PostOrder(root->right);
	printf("%d ", root->data);
}
void BTreeDestroy(BTNode* root)
{
	if (root == NULL)
	{
		return;
	}
	BTreeDestroy(root->left);
	BTreeDestroy(root->right);
	free(root);
	root = NULL;
}
BTNode* BTreeFind(BTNode*root,BTDataType x)//查找二叉树中某个值，某个节点
{
	if (root == NULL)
	{
		return NULL;
	}
	if (root->data == x)
	{
		return  root;
	}
	//找左子树中是否有x,在递归中带有比较判断的要记得保存这个变量，不然会很麻烦
	BTNode* lret = BTreeFind(root->left, x);
	if (lret)
	{
		return lret;
	}
	BTNode* rret = BTreeFind(root->right, x);
	if (rret)
	{
		return rret;
	}
	return NULL;

}
int KSize(BTNode* root, int k)//求第k层节点的个数
{
	if (root == NULL)
	{
		return 0;
	}
	if (k == 1)
	{
		return 1;
	}
	return KSize(root->left, k - 1) + KSize(root->right, k - 1);
}
int Size(BTNode* root)//求节点的所有个数
{
	if (root == NULL)
	{
		return 0;
	}
	return Size(root->left) + Size(root->right) + 1;
}
int Height(BTNode* root)//求二叉树的深度，高度
{
	if (root == NULL)
	{
		return 0;
	}
	int Lheight = Height(root->left);
	int Rheight = Height(root->right);
	return Lheight > Rheight ? Lheight + 1 : Rheight + 1;

}
typedef struct {
	int* a;
	int front;
	int rear;
	int k;
} MyCircularQueue;


MyCircularQueue* myCircularQueueCreate(int k)
{
	MyCircularQueue* queue = (MyCircularQueue*)malloc(sizeof(MyCircularQueue));
	queue->a = (int*)malloc(sizeof(int) * (k + 1));
	queue->front = queue->rear = 0;
	queue->k = k;
}

bool myCircularQueueIsEmpty(MyCircularQueue* obj)
{
	return obj->front == obj->rear;
}

bool myCircularQueueIsFull(MyCircularQueue* obj)
{
	return (obj->rear + 1) % (obj->k + 1) == obj->front;
	
}
bool myCircularQueueEnQueue(MyCircularQueue* obj, int value)
{
	if (myCircularQueueIsFull(obj))
	{
		return false;
	}
	else
	{
		obj->a[obj->rear++] = value;
		obj->rear %= obj->k + 1;
	}
}


bool myCircularQueueDeQueue(MyCircularQueue* obj)
{
	if (myCircularQueueIsEmpty(obj))
	{
		return false;
	}
	else
	{
		++obj->front;
		obj->front %= obj->k + 1;
	}
	
}

int myCircularQueueFront(MyCircularQueue* obj)
{
	if (myCircularQueueIsEmpty(obj))
	{
		return -1;
	}
	else
	{
		return obj->a[obj->front];
	}
}

int myCircularQueueRear(MyCircularQueue* obj)
{
	if (myCircularQueueIsEmpty(obj))
	{
		return -1;
	}
	else
	{
		return obj->a[(obj->rear - 1 + obj->k + 1) % (obj->k + 1)];
	}

}

void myCircularQueueFree(MyCircularQueue* obj)
{
	free(obj->a);
	free(obj);
}

/**
 * Your MyCircularQueue struct will be instantiated and called as such:
 * MyCircularQueue* obj = myCircularQueueCreate(k);
 * bool param_1 = myCircularQueueEnQueue(obj, value);

 * bool param_2 = myCircularQueueDeQueue(obj);

 * int param_3 = myCircularQueueFront(obj);

 * int param_4 = myCircularQueueRear(obj);

 * bool param_5 = myCircularQueueIsEmpty(obj);

 * bool param_6 = myCircularQueueIsFull(obj);

 * myCircularQueueFree(obj);
*/
int main()
{
	BTNode* root= CreatBinaryTree();
	PreOrder(root);
	printf("\n");
	InOrder(root);
	printf("\n");
	PostOrder(root);
	printf("\n");
	printf("Size:%d \n", Size(root));
	printf("KSize:%d \n", KSize(root,3));
	printf("Height:%d \n", Height(root));
	printf("地址:%p \n", BTreeFind(root,3));
	printf("地址:%p \n", BTreeFind(root, 20));

	return 0;
}