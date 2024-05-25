#include<stdio.h>
#include<stdlib.h>

struct Node
{
int data;
struct Node *lchild;
struct Node *rchild;
};

struct Node *Insert(struct Node *root,int key){
    if (root==NULL)
    {
        root=(struct Node *)malloc(sizeof(struct Node));
        root->data=key;
        root->lchild=NULL;
        root->rchild=NULL;
        return root;

    }
    if (key<root->data)
    {
        root->lchild=Insert(root->lchild,key);
    }
    else if(key>root->data)
    {
        root->rchild=Insert(root->rchild,key);
    }
    else{
        printf("duplicate element %d is found",key);
        exit (1);
    }
    
    
}

void Inorder(struct Node *p){
    if (p!=NULL)
    {
        Inorder(p->lchild);
        printf(" %d",p->data);
        Inorder(p->rchild);
    }
    
}
void InorderR(struct Node *p){
    if (p==NULL)
    {
    printf("Tree is Empty");
    return;
    }
    struct Node *stack[100];
    int top=-1;
    struct Node *t=p;

    while (t!=NULL || top!=-1)
    {
        while(t!=NULL){
            stack[++top]=t;
            t=t->lchild;
        }
        if (top!=-1)
        {
            t=stack[top--];
            printf("%d ",t->data);
            t=t->rchild;
            
        }
        
    }
    
    
}

void PreorderR(struct Node *p){
    if (p==NULL)
    {
    printf("Tree is Empty");
    return;
    }
    struct Node *stack[100];
    int top=-1;
    struct Node *t=p;

    while (t!=NULL || top!=-1)
    {
        while(t!=NULL){
           printf("%d ",t->data);
           stack[++top]=t;
            t=t->lchild;
             
        }
        if (top!=-1)
        {
            t=stack[top--];
            
            t=t->rchild;
            
        }
        
    }
    
    
}

void PostorderR(struct Node *p){
    if (p==NULL)
    {
    printf("Tree is Empty");
    return;
    }
    struct Node *stack[100];
    int top=-1;
    struct Node *t=p;
    struct Node *a=NULL;

    while (t!=NULL || top!=-1)
    {
        while(t!=NULL){
           
           stack[++top]=t;
            t=t->lchild;
             
        }
        t=stack[top];
        if (t->rchild==NULL || t->rchild==a)
        {
            printf("%d ",t->data);
            top--;
            a=t;
            t=NULL;
        }
        else{
            t=t->rchild;
        }
        
    }
    
    
}



void Preorder(struct Node *p){
    if (p!=NULL)
    {
        printf("%d ",p->data);
        Preorder(p->lchild);
        Preorder(p->rchild);
    }
    
    
}

void Postorder(struct Node *p){
    if (p!=NULL)
    {
        Postorder(p->lchild);
        Postorder(p->rchild);
        printf("%d ",p->data);
    }
    
}

int Height(struct Node *root){
    int x,y;
    if (root==NULL)
    {
        return -1;
    }
    x=Height(root->lchild);
    y=Height(root->rchild);
    if (x>y)
    {
       return x+1;
    }
    else{
        return y+1;
    }
}

struct Node *Inpre(struct Node *root){
    while (root!=NULL && root->rchild!=NULL)
    {
      root=root->rchild;
    }
    return root;
    
}
struct Node *Insucc(struct Node *root){
    while (root!=NULL && root->lchild!=NULL)
    {
      root=root->lchild;
    }
    return root;
    
}


struct Node *Delete(struct Node *root, int key) {
    struct Node *temp;
    if (root == NULL) {
        printf("Element not found\n");
        return root;
    }
    if (key < root->data) {
        root->lchild = Delete(root->lchild, key);
    } else if (key > root->data) {
        root->rchild = Delete(root->rchild, key);
    } else {
        if (root->lchild == NULL && root->rchild == NULL) {
            free(root);
            return NULL;
        } else if (Height(root->lchild) > Height(root->rchild)) {
            temp = Inpre(root->lchild);
            root->data = temp->data;
            root->lchild = Delete(root->lchild, temp->data);
        } else {
            temp = Insucc(root->rchild);
            root->data = temp->data;
            root->rchild = Delete(root->rchild, temp->data);
        }
    }
    return root;
}

int countNodes(struct Node* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countNodes(root->lchild) + countNodes(root->rchild);
}

// Function to count the number of leaf nodes in the tree
int countLeafNodes(struct Node* root) {
    if (root == NULL) {
        return 0;
    }
    if (root->lchild == NULL && root->rchild == NULL) {
        return 1;
    }
    return countLeafNodes(root->lchild) + countLeafNodes(root->rchild);
}

void displayLeafNodes(struct Node* root) {
    if (root != NULL) {
        if (root->lchild == NULL && root->rchild == NULL) {
            printf("%d ", root->data);
        }
        displayLeafNodes(root->lchild);
        displayLeafNodes(root->rchild);
    }
}

void mirror(struct Node* root) {
    if (root == NULL) {
        return;
    }
    struct Node* temp;

    // Recursively mirror the left and right subtrees
    mirror(root->lchild);
    mirror(root->rchild);

    // Swap the left and right children
    temp = root->lchild;
    root->lchild = root->rchild;
    root->rchild = temp;
}

void displayMirrorImage(struct Node* root) {
    if (root != NULL) {
        displayMirrorImage(root->rchild);
        printf("%d ", root->data);
        displayMirrorImage(root->lchild);
    }
}


void levelOrderwithoutRecursion(struct Node* root) {
    if (root == NULL) {
        return;
    }

    struct Node* queue[100]; // Assume a maximum of 100 nodes
    int front = 0;
    int rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        struct Node* current = queue[front++];
        printf("%d ", current->data);

        if (current->lchild != NULL) {
            queue[rear++] = current->lchild;
        }
        if (current->rchild != NULL) {
            queue[rear++] = current->rchild;
        }
    }
}

void printGivenLevel(struct Node* root, int level) {
    if (root == NULL) {
        return;
    }
    if (level == 1) {
        printf("%d ", root->data);
    } else if (level > 1) {
        printGivenLevel(root->lchild, level - 1);
        printGivenLevel(root->rchild, level - 1);
    }
}

void levelOrderRecursive(struct Node* root) {
    int h = Height(root) + 1; // +1 because Height function returns the height as depth - 1
    for (int i = 1; i <= h; i++) {
        printGivenLevel(root, i);
    }
}

int main(){
    struct Node *root=NULL;
    int *element;
   int size;
   printf("Enter the numner of elements");
   scanf("%d",&size);
   element=(int *)malloc(size * sizeof(int));
   printf("Enter %d elements",size);
   for (int i = 0; i < size; ++i)
   {
   
    scanf("%d",&element[i]);
   }
   for (int i = 0; i < size; ++i)
   {
   root=Insert(root,element[i]);
   
   }
   
int n;
    
   do{
    printf("Binary Search Tree Operations:\n");
    printf("1. Preorder Traversal:\n");
    printf("2. Preorder without Rec:\n");
    printf("3. Post order Traversal:\n");
    printf("4. Post order Traversal Without Rec:\n");
    printf("5. Inorder Traversal:\n");
    printf("6. Inorder without Rec:\n");
    printf("7. Delete:\n");
    printf("8. Display Height:\n");
    printf("9. Count Leaf Nodes:\n");
    printf("10. Count total number of Nodes:\n");
    printf("11. Display Leaf Nodes:\n");
    printf("12. Display Mirror Image:\n");
    printf("13. Display Level Order with Recursion:\n");
    printf("14. Display Level Order without Rec:\n");
    printf("15. Exit\n");

    printf("enter choice");
    scanf("%d",&n);
    
   switch (n)
    {
    case 1:
        printf("Preorder Traversal: ");
        Preorder(root);
        printf("\n");
        break;
    case 2:
        printf("Preorder Traversal without Rec: ");
        PreorderR(root);
        printf("\n");
        break;
    case 3:
        printf("Postorder Traversal: ");
        Postorder(root);
        printf("\n");
        break;
    case 4:
        printf("Postorder Traversal without rec: ");
        PostorderR(root);
        printf("\n");
        break;
    case 5:
        printf("Inorder Traversal: ");
        Inorder(root);
        printf("\n");
        break;
    case 6:
        printf("Inorder Traversal without Rec: ");
        InorderR(root);
        printf("\n");
        break;
    case 7:
        printf("Enter element to delete: ");
        int key;
        scanf("%d", &key);
        root = Delete(root, key);
        printf("Element deleted.\n");
        break;
    case 8:
        printf("Height of the Tree is %d: ",Height(root));
        break;
    case 9:
        printf("Number of Leaf Nodes are %d: ",countLeafNodes(root));
        break;
    case 10:
        printf("Total Number of Nodes in the tree are %d: ",countNodes(root));
        break;
    case 11:
        printf("Leaf nodes are: ");
        displayLeafNodes(root);
        printf("\n");
        break;
    case 12:
        printf("Mirror Image Inorder Traversal: ");
        mirror(root);
        displayMirrorImage(root);
        // mirror(root);  // Restore the original tree structure
        printf("\n");
        break;
     case 13:
        printf("Level Order Traversal (Recursive): ");
        levelOrderRecursive(root);
        printf("\n");
        break;
    case 14:
        printf("Level Order Traversal without recusrion: ");
        levelOrderwithoutRecursion(root);
        printf("\n");
        break;
    case 15:
        printf("Exit");
        break;
    
    default:
        break;
    }
}while(n!=15);
free(element);
return 0;
}