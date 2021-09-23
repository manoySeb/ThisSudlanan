// Searching a key on a B-tree in C

#include <stdio.h>
#include <stdlib.h>

#define MAX 3
#define MIN 2

typedef struct BTreeNode {
  int val[MAX + 1], count;
  struct BTreeNode *link[MAX + 1];
}*BtreePtr;

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

// Create a node
BtreePtr createNode(int val, BtreePtr child, BtreePtr root) {
  BtreePtr newNode;

  newNode = (BtreePtr)malloc(sizeof(struct BTreeNode));
  newNode->val[1] = val;
  newNode->count = 1;
  newNode->link[0] = root;
  newNode->link[1] = child;
  return newNode;
}

// Insert node
void insertNode(int val, int pos, BtreePtr node, BtreePtr child) {
  int j;

  for(j = node->count; j > pos; j--) {
    node->val[j + 1] = node->val[j];
    node->link[j + 1] = node->link[j];
  }
  node->val[j + 1] = val;
  node->link[j + 1] = child;
  node->count++;
}

// Split node
void splitNode(int val, int *pval, int pos, BtreePtr node, BtreePtr child, BtreePtr *newNode) {
  int median, j;

  if (pos > MIN)
    median = MIN + 1;
  else
    median = MIN;

  *newNode = (BtreePtr)malloc(sizeof(struct BTreeNode));
  
  for(j = median + 1; j <= MAX; j++) {
    (*newNode)->val[j - median] = node->val[j];
    (*newNode)->link[j - median] = node->link[j];
  }
  node->count = median;
  (*newNode)->count = MAX - median;

  if (pos <= MIN) {
    insertNode(val, pos, node, child);
  } else {
    insertNode(val, pos - median, *newNode, child);
  }
  *pval = node->val[node->count];
  (*newNode)->link[0] = node->link[node->count];
  node->count--;
}

// Set the value
int setValue(int val, int *pval, BtreePtr node, BtreePtr *child) {
  int pos;
  if (node == NULL) {
    *pval = val;
    *child = NULL;
    return 1;
  }

  if (val < node->val[1]) {
    pos = 0;
  } else {
    for (pos = node->count;
       (val < node->val[pos] && pos > 1); pos--)
      ;
    if (val == node->val[pos]) {
      printf("Duplicates are not permitted\n");
      return 0;
    }
  }
  if (setValue(val, pval, node->link[pos], child)) {
    if (node->count < MAX) {
      insertNode(*pval, pos, node, *child);
    } else {
      splitNode(*pval, pval, pos, node, *child, child);
      return 1;
    }
  }
  return 0;
}

// Insert the value
void insert(int val, BtreePtr root) {
  int flag, i;
  BtreePtr child;

  flag = setValue(val, &i, root, &child);
  if (flag){
    root = createNode(i, child, root);
  }
}

// Search node
void search(int val, int *pos, BtreePtr myNode) {
  if (!myNode) {
    return;
  }

  if (val < myNode->val[1]) {
    *pos = 0;
  } else {
    for (*pos = myNode->count; (val < myNode->val[*pos] && *pos > 1); (*pos)--){
      if (val == myNode->val[*pos]) {
        printf("%d is found", val);
        return;
      }
    }
  }
  search(val, pos, myNode->link[*pos]);

  return;
}

// Traverse then print the nodes
void traversal(BtreePtr myNode) {
  int i;
  if (myNode) {
    for (i = 0; i < myNode->count; i++) {
      traversal(myNode->link[i]);
      printf("%d ", myNode->val[i + 1]);
    }
    traversal(myNode->link[i]);
  }
}