#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int data;
    int height;
    struct Node *lchild,*rchild;

}*root=NULL;

int Nodeheight(struct Node *p)
{
    if (p==NULL)
    {
       return 0;
    }
    else{
        int hl=0,hr=0;
        if (p->lchild)
        {
           hl=Nodeheight(p->lchild);
}
        if (p->rchild)
        {
           hr=Nodeheight(p->rchild);
        }
       if (hl>hr)
       {
        return hl+1;
       }
       else{
        return hr+1;
       }
       
        }
        
    }

int BalanceFactor(struct Node *p){
     int hl=0,hr=0;
        if (p->lchild)
        {
           hl=Nodeheight(p->lchild);
}
        if (p->rchild)
        {
           hr=Nodeheight(p->rchild);
        }
      
    return hl-hr;
}
struct Node *LLRotation(struct Node *p){
    struct Node *pl=p->lchild;
    struct Node *plr=pl->rchild;
    pl->rchild=p;
    p->lchild=plr;

   p->height=Nodeheight(p);
   pl->height=Nodeheight(pl);

   if (root==p)
   {
    root=pl;
   }
   return pl;

}

struct Node *LRRotation(struct Node *p){
    struct Node *pl=p->lchild;
    struct Node *plr=pl->rchild;
    pl->rchild=plr->lchild;
    p->lchild=plr->rchild;

    plr->lchild=pl;
    plr->rchild=p;

   pl->height=Nodeheight(pl);
   p->height=Nodeheight(p);
 if (root==p)
   {
    root=plr;
   }
   return plr;
}
struct Node *RRRotation(struct Node *p){
    struct Node *pr=p->rchild;
    p->rchild=pr->lchild;
    pr->lchild=p;

    p->height=Nodeheight(p);
    pr->height=Nodeheight(pr);
if (root==p)
    {
        root=pr;
    }
    return pr;

}
struct Node *RLRotation(struct Node *p){
    struct Node *pr=p->rchild;
    struct Node *prl=pr->lchild;
    pr->lchild=prl->rchild;
    prl->rchild=pr;
    p->rchild=prl->lchild;
    prl->lchild=p;

    p->height=Nodeheight(p);
    pr->height=Nodeheight(pr);
    prl->height=Nodeheight(prl);

if (root==p)
{
    root=prl;

}
return prl;
}
struct Node *RInsert(struct Node *p,int key){
    struct Node *t=NULL;
    if (p==NULL)
    {
        t=(struct Node*)malloc(sizeof(struct Node));
        t->data=key;
        t->height=1;
        t->lchild=t->rchild=NULL;
        return t;
    }
    if (key<p->data)
    {
       p->lchild=RInsert(p->lchild,key);
    }
    else if(key>p->data){
        p->rchild=RInsert(p->rchild,key);
    }
    p->height=Nodeheight(p);
    if (BalanceFactor(p)==2 && BalanceFactor(p->lchild)==1)
    {
        return LLRotation(p);
    }
    else if (BalanceFactor(p)==2 && BalanceFactor(p->lchild)==-1)
    {
        return LRRotation(p);
    }
    else if (BalanceFactor(p)==-2 && BalanceFactor(p->rchild)==-1)
    {
        return RRRotation(p);
    }
    else if (BalanceFactor(p)==-2 && BalanceFactor(p->rchild)==1)
    {
        return RLRotation(p);
    }
    return p;
}

void Display(struct Node *p) {
    if (p != NULL) {//preorder
        printf("%d ", p->data);
        Display(p->lchild);
        Display(p->rchild);
    }
}

// Function to print nodes at a given level
void printGivenLevel(struct Node* root, int level) {
    if (root == NULL)
        return;
    if (level == 1)
        printf("%d ", root->data);
    else if (level > 1) {
        printGivenLevel(root->lchild, level - 1);
        printGivenLevel(root->rchild, level - 1);
    }
}

// Function to display level order traversal using recursion
void levelOrderRecursive(struct Node* root) {
    int h = Nodeheight(root);
    for (int i = 1; i <= h; i++)
        printGivenLevel(root, i);
}

// Function to display level order traversal without recursion
void levelOrderIterative(struct Node* root) {
    if (root == NULL)
        return;

    // Create an empty queue for level order traversal
    struct Node* queue[100]; // Assuming a maximum of 100 nodes in the tree
    int front = 0;
    int rear = 0;

    // Enqueue root and initialize height
    queue[rear++] = root;

    while (front < rear) {
        struct Node* node = queue[front++];

        printf("%d ", node->data);

        // Enqueue left child
        if (node->lchild != NULL)
            queue[rear++] = node->lchild;

        // Enqueue right child
        if (node->rchild != NULL)
            queue[rear++] = node->rchild;
    }
}


int main() {
    int choice, key;
    while (1) {
        printf("\nAVL Tree Operations:\n");
        printf("1. Insert\n");
        printf("2. Display Preorder Traversal\n");
        printf("3. Display Level Order (Recursive)\n");
        printf("4. Display Level Order (Iterative)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = RInsert(root, key);
                break;
            case 2:
                printf("Displaying AVL Tree:\n");
                Display(root);
                break;
            case 3:
                printf("Level Order Traversal (Recursive): ");
                levelOrderRecursive(root);
                printf("\n");
                break;
            case 4:
                printf("Level Order Traversal (Iterative): ");
                levelOrderIterative(root);
                printf("\n");
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }
}
