#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <math.h>

#define MAX 4
#define MIN 2

typedef struct node {
	int val[MAX+1], count;
	struct node *link[MAX+1];
}ctype,*BtreePtr;

void initTree(BtreePtr *B);
void insert(BtreePtr *B,int val);
BtreePtr createNode(int val);
BtreePtr addAfterMid(BtreePtr *B,int val);
int insertSorted(BtreePtr *B,int val);
void split(BtreePtr *root,BtreePtr *B);
//BtreePtr *getPrev(BtreePtr *root,int val);
void printTree(BtreePtr B);

int main() {
	BtreePtr root;
	int val, ch;
	
	initTree(&root);
	insert(&root,8);
	insert(&root,9);
	insert(&root,10);
	insert(&root,11);
	insert(&root,15);
	insert(&root,16);
	insert(&root,17);
	insert(&root,18);printf("%d\n",root->val[1]);
	insert(&root,20);
	insert(&root,23);
	insert(&root,40);
	insert(&root,43);
	insert(&root,50);
	insert(&root,53);
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
    int x,y;
    if((*B)->count>mid){
    	
    temp=(BtreePtr)calloc(1,sizeof(ctype));
		if(temp!=NULL){
		    
			for(x=mid+1;x<(*B)->count;x++){
				temp->val[temp->count]=(*B)->val[x];
				temp->link[temp->count++]=(*B)->link[x];
			}
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
	BtreePtr *trav,*prevNode;
	int x,pos;
	
	if(*B==NULL){
		*B=createNode(val);
	}else{
		prevNode=trav=B;
		while(*trav!=NULL){
			for(x=0;x<(*trav)->count&&(*trav)->val[x]<val;x++){}
			prevNode=trav;
			trav=&(*trav)->link[x];
		}
	
		insertSorted(prevNode,val);
		if((*prevNode)->count>MAX){
			split(B,prevNode);
		}
	}
}

int insertSorted(BtreePtr *B,int val)
{
	int x,numEl;
	for(x=0;x<(*B)->count&&(*B)->val[x]<val;x++){}
	numEl=(*B)->count-x;
	memcpy((*B)->val+x+1,(*B)->val+x,sizeof(int)*numEl);
	memcpy((*B)->val+x+1,(*B)->val+x,sizeof(BtreePtr)*numEl);	
	(*B)->count++;
	(*B)->val[x]=val;
	//(*B)->link[x]=NULL;
	
	return x;
}

void split(BtreePtr *root,BtreePtr *NodeSplit)
{
	int mid,val;
	mid=ceil(MAX/2);//midian element
	
	val=(*NodeSplit)->val[mid];

	BtreePtr *trav,*currNode,temp;
	int x=0,pos;
	
	while((*NodeSplit)->count>MAX){
	if((*root)->count==MAX+1){
		temp=createNode(val);
		temp->link[1]=addAfterMid(root,mid);
		(*root)->count=mid;
		temp->link[0]=*root;
		
		//(*root)->count=mid-1;//remove after mid
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
	/*
	int mid,pos;
	BtreePtr *prevNode,*right;
	mid = ceil(MAX);
	prevNode=getPrev(root,(*B)->val[mid]);
    
    right=createNode(0);//dummy value
    memmove((*right)->val,(*B)->val+mid+1,sizeof(int)*(MAX-mid-1));
    memmove((*right)->link,(*B)->link+mid+1,sizeof(BtreePtr)*(MAX-mid-1));
    (*right)->count=MAX-mid-1;
    
    (*B)->count-=mid-1;
    
   	pos=insertSorted(prevNode,(*prevNode)->val[mid]);
	(*prevNode)->link[pos]=*right;
	*/
}

/*
BtreePtr *getPrev(BtreePtr *root,int val)
{
    BtreePtr *trav,*prev;
    int x=0;
    trav=root;
    
    while((*trav)->val[0]<=val&&(*trav)->val[(*trav)->count-1]>=val){
        
    for(x=0;x<(*trav)->count&&(*trav)->val[x]<val;x++){}
        prev=trav;
        trav=&(*trav)->link[x];
    }
    return prev;
}
*/

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