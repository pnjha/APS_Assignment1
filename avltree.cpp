#include <iostream>
#define ll long long int 

using namespace std;

int TERM_FLAG = 0;
int smallest;
int child=0;

struct node* deleteNode(struct node*,int);
struct node* reBalance(struct node*);

struct node {
    ll value;
    node *left;
    node *right;
};

struct node* createNode(struct node *ptr,ll value){
    ptr = (struct node*)malloc(sizeof(struct node));
    ptr->left = NULL;
    ptr->right = NULL;
    ptr->value = value;
    return ptr;
}

int height(struct node* root){

    int rightSubTree=0,leftSubTree=0;
    
    if(root==NULL)
        return 0;

    leftSubTree = 1+height(root->left);
    rightSubTree = 1+height(root->right);

    return rightSubTree>leftSubTree?rightSubTree:leftSubTree;
}


struct node * insertNode(struct node * root,ll value){
    if(root==NULL){
        root = createNode(root,value);
        return root;
    }else if(value>root->value){
        root->right = insertNode(root->right,value);
    }else if(value<root->value){
        root->left = insertNode(root->left,value);
    }
    root = reBalance(root);
    return root;
}

int search(struct node * root,ll value){

    if(root==NULL)
        return 0;
    if(root->value==value)
        return 1;
    
    return search(root->left,value)||search(root->right,value)?1:0;
}

struct node * smallestValue(struct node * root){
    struct node * ptr;

    if(root->left==NULL)
        return root;
    ptr = smallestValue(root->left);
    return ptr;
}

int traverseTree(struct node * root,ll rank){
    
    int value;
    
    if(root==NULL)
        return -1;

    value = traverseTree(root->left,rank);
    
    if(TERM_FLAG==1)
        return value; 
    else
        child++;

    if(child==rank){
        TERM_FLAG = 1;
        return root->value;
    }

    value = traverseTree(root->right,rank);

    return value;
}


void inorderTraversal(struct node *root){
    if(root==NULL)
        return;
    inorderTraversal(root->left);
    cout<<root->value<<" ";
    inorderTraversal(root->right);

}

void preorderTraversal(struct node *root){
    if(root==NULL)
        return;
    cout<<root->value<<" ";
    inorderTraversal(root->left);
    
    inorderTraversal(root->right);

}

struct node* inorderSucessor(struct node* root){
    struct node* temp = root;
    while(temp->left!=NULL){
        temp = temp->left;
    }
    return temp;
}

struct node* reBalance(struct node* root){
    if (root == NULL){
        return root;
    }

     int diffroot,diffrootright,diffrootleft;
     
     if(root!=NULL){
         
        diffroot = height(root->left) - height(root->right);
     }
    if (root->left!=NULL){
        
        diffrootleft = height(root->left->left) - height(root->left->right);
    }
    if(root->right!=NULL){
        
        diffrootright = height(root->right->left) - height(root->right->right);    
    } 
     
 
    // left left imbalance
    if (diffroot>1&&diffrootleft>=0){
        struct node *temp1, *temp2;
    
        temp1 = root->left;
        temp2 = temp1->right;
        temp1->right = root;
        root->left = temp2;

        return temp1; 
    }
 
    // left right imbalance
    if (diffroot>1&&diffrootleft<0){    
        
        struct node *temp1, *temp2,*temp3,*temp4;    

        temp1 = root->left->right;
        temp2 = temp1->left;
        temp1->left = root->left;
        root->left->right = temp2;
        root->left = temp1;
        
        temp3 = root->left;
        temp4 = temp3->right;
        temp3->right = root;
        root->left = temp4;

        return temp3; 
    }
 
    // right right imbalance
    if (diffroot<-1&&diffrootright<=0){
        //return rotateLeft(root);
        
        struct node *temp1, *temp2;    

        temp1 = root->right;
        temp2 = temp1->left;
        temp1->left = root;
        root->right = temp2;

        return temp1;
    }
 
    // right left imbalance
    if (diffroot<-1&&diffrootright>0){    
        
        struct node *temp1, *temp2,*temp3,*temp4;
    
        temp1 = root->right->left;
        temp2 = temp1->right;
        temp1->right = root->right;
        root->right->left = temp2;
        root->right = temp1;
        
        temp3 = root->right;
        temp4 = temp3->left;
        temp3->left = root;
        root->right = temp4;

        return temp3;
    }
    
    return root;
}

struct node* deleteNode(struct node* root, int value)
{
    if (root == NULL){
        return root;
    }
 
    if (value<root->value){
        root->left = deleteNode(root->left,value);
    }
    else if(value>root->value){
        root->right = deleteNode(root->right,value);
    }
    else{
        struct node *temp;
        
        if(root->left==NULL&&root->right==NULL){
            temp = root;
            root = NULL;
            free(temp);
        }
        else if(root->left!=NULL&&root->right==NULL){
            temp = root->left;
            *root = *temp;
            free(temp);
        }else if(root->left==NULL&&root->right!=NULL){
            temp = root->right;
            *root = *temp;
            free(temp);
        }else{
             struct node* temp = inorderSucessor(root->right);
             root->value = temp->value;
             root->right = deleteNode(root->right,temp->value);
         }   
         
    }
    
    root = reBalance(root);
     
    return root;
}


int main(){

    ll n=0,m=0,value=0;
    
    cin>>n>>m;
    int flag=1;
    struct node *root = NULL, *temp1 = NULL , *temp2 = NULL; 

    while(n--){
        cin>>value;
        root = insertNode(root,value);
    }

    ll query=0;

    while(m--){
        cin>>query>>value;
        if(query==1){
            root = insertNode(root,value);
        }else if(query==2){
            cout<<search(root,value)<<"\n";
        }else if(query==3){
            int kmin = traverseTree(root,value);
            cout<<kmin<<"\n";
            TERM_FLAG = 0;
            child = 0;
            root = deleteNode(root,kmin);
        }
        
    }

    return 0;
}