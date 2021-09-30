#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <math.h>

#define MAX 3
#define MIN 2

<<<<<<< HEAD
typedef struct BTreeNode {
  int val[MAX + 1], count;
  struct BTreeNode *link[MAX + 1];
}*BtreePtr;

// Initialize Btree
void initBtree(BtreePtr *Tree);
// Create a node
BtreePtr createNode(int val, BtreePtr child, BtreePtr root);
// Insert node
void insertNode(int val, int pos, BtreePtr node, BtreePtr child);
// Split node
void splitNode(int val, int *pval, int pos, BtreePtr node, BtreePtr child, BtreePtr *newNode);
// Set the value
int setValue(int val, int *pval, BtreePtr node, BtreePtr *child);
// Insert the value
void insert(int val, BtreePtr root);
// Search node
void search(int val, int *pos, BtreePtr myNode);
// Traverse then print the nodes
void traversal(BtreePtr myNode);

int main() {
  int val, ch;
  BtreePtr root;
  initBtree(&root);

  insert(8,root);
  insert(9,root);
  insert(10,root);
  insert(11,root);
  insert(15,root);
  insert(16,root);
  insert(17,root);
  insert(18,root);
  insert(20,root);
  insert(23,root);

  traversal(root);

  printf("\n");
  search(11, &ch, root);
}

// Initialize Btree
void initBtree(BtreePtr *Tree){
  *Tree = NULL;
}

// Create a node
BtreePtr createNode(int val, BtreePtr child, BtreePtr root) {
  BtreePtr newNode;
=======
typedef struct node {
	int val[MAX], count;
	struct node *link[MAX+1];
}ctype,*BtreePtr;

typedef enum boolean {TRUE, FALSE};

void initTree(BtreePtr *B);
void insert(BtreePtr *B,int val);
BtreePtr createNode(int val);
BtreePtr addAfterMid(BtreePtr *B,int val);
void insertSorted(BtreePtr *B,int val, int x);
void split(BtreePtr *root,BtreePtr *B);
void search(BtreePtr B, int val);
void printTree(BtreePtr B);
>>>>>>> ce795843aa0a9d53fb3d7c12e11d43c0f15c626c

int main() {
	BtreePtr root;
	int val, ch;
	
	initTree(&root);
	insert(&root,5);
	insert(&root,10);
	insert(&root,15);
	insert(&root,4);
	insert(&root,11);
	insert(&root,6);
	insert(&root,13);
/* */
	printTree(root);
 
	printf("\n");
	//search(11, &ch, root);
}

//initialize tree
void initTree(BtreePtr *B)
{
	*B=NULL;
}


BtreePtr addAfterMid(BtreePtr *B,int mid)
{
    BtreePtr temp=NULL;
    int x,numEl;
    if((*B)->count>mid){
    	
    temp=(BtreePtr)calloc(1,sizeof(ctype));
		if(temp!=NULL){
		    numEl=(*B)->count-mid-1;
		    memcpy(temp->val,(*B)->val+mid+1,sizeof(int)*numEl);
		    memcpy(temp->link,(*B)->link+mid+1,sizeof(BtreePtr)*numEl);
			temp->count=numEl;
		}
	}
	return temp;
}

BtreePtr createNode(int val)
{
    BtreePtr temp;
    temp=(BtreePtr)calloc(1,sizeof(ctype));
		if(temp!=NULL){
			temp->count=1;
			temp->val[0]=val;
		}
	return temp;
}

// Insert the value
void insert(BtreePtr *B,int val) {
	BtreePtr *trav,*currNode;
	int x;
	
	if(*B==NULL){
		*B=createNode(val);
	}else{
		currNode=trav=B;
		while(*trav!=NULL){
			for(x=0;x<(*trav)->count&&(*trav)->val[x]<val;x++){}
			currNode=trav;
			trav=&(*trav)->link[x];
		}
	
		insertSorted(currNode,val,x);
		if((*currNode)->count>=MAX){
			split(B,currNode);
		}
	}
}

void insertSorted(BtreePtr *B,int val,int x)
{
	int numEl;
	numEl=(*B)->count-x;
	memcpy((*B)->val+x+1,(*B)->val+x,sizeof(int)*numEl);
	memcpy((*B)->val+x+1,(*B)->val+x,sizeof(BtreePtr)*numEl);	
	(*B)->count++;
	(*B)->val[x]=val;
	
}

void split(BtreePtr *root,BtreePtr *NodeSplit)
{
	int mid,val;
	mid=ceil(MAX-2/2);//median element
	
	val=(*NodeSplit)->val[mid];

	BtreePtr *trav,*currNode,temp;
	int x=0;
	
	while((*NodeSplit)->count>=MAX){
		if((*root)->count==MAX){
			temp=createNode(val);
			temp->link[1]=addAfterMid(root,mid);
			(*root)->count=mid;
			temp->link[0]=*root;
			
			*root=temp;
		}else{
		currNode=trav=root;
		while(trav!=NodeSplit){
			for(x=0;x<(*trav)->count&&(*trav)->val[x]<val;x++){}
			currNode=trav;
			trav=&(*trav)->link[x];
		}
	
		(*currNode)->val[x]=val;
		(*currNode)->link[x+1]=addAfterMid(NodeSplit,mid);
		(*currNode)->count++;
		(*NodeSplit)->count=mid;//remove aftermid
		NodeSplit=currNode;
		}
	}
}


void printTree(BtreePtr B)
{
	int x;
	
	if(B!=NULL){
		for(x=0;x<B->count;x++){
			printf("index %d:%d\t",x,B->val[x]);
			printTree(B->link[x]);
		}
		puts("\n");
		printTree(B->link[x]);
	}
}

void search(BtreePtr B, int val)
{
  int pos, x, count;

  while (B != NULL)
  {
    count = B->count;
    for (x=0; x < B->count; x++)
    printf(" %d",B->val[x]);
    printf("\n");
    for(pos = 0; pos < count && val > val_arr[pos]; pos++){
      if (pos < count && val == B->val[pos]){
      printf("Key %d found in position %d of last dispalyed
      node\n", val, x);
      }
    }
    B = B->link[pos];
  }
  printf("Key %d is not available\n",key);
}
