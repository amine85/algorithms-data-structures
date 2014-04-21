#include "binary_search_tree.h"


////////////////////////////////////////////////////////////////
Node::Node()
{
  this->parent = NULL;
  this->right = NULL;
  this->left = NULL;
}

////////////////////////////////////////////////////////////////
Node::Node(int key)
{
  this->key = key;
  this->parent = NULL;
  this->right = NULL;
  this->left = NULL; 
}

////////////////////////////////////////////////////////////////
Node::~Node()
{
  this->parent = NULL;
  this->right = NULL;
  this->left = NULL;
}


/***********************************************************************************************************/

////////////////////////////////////////////////////////////////
Tree::Tree()
{
 this->root = NULL; 
}

////////////////////////////////////////////////////////////////
Tree::~Tree()
{
  this->destroy(this->root);
}

////////////////////////////////////////////////////////////////
void Tree::insertKey(int value, Node * node)
{
  if(root==NULL){	// this is the root node
      this->root = new Node(value);
      return;
  }
  
  if(value >= node->key){
    if(node->right == NULL){
      Node * n = new Node(value);
      n->parent = node;
      node->right = n;
    }
    else{
      this->insertKey(value,node->right);
    }
  }
  else{
      if(node->left == NULL){
	Node * n = new Node(value);
	n->parent = node;
	node->left = n;
      }
      else{
	this->insertKey(value,node->left);
      } 
  }
    
}

////////////////////////////////////////////////////////////////
void Tree::insertMinimal(int values[], int start, int end)
{
  if(end<=start)
    return;
//   if(end>=start)
  {
    int length = end-start+1;
//     int mid = (end-start+1)/2;
    int mid;
    if(length%2==0)
      mid = length/2;
    else
       mid = length/2+1;
    std::cout<<"mid: "<<mid<<std::endl;
    this->insertKey(values[mid],this->root);
    this->insertMinimal(values, start, mid-1);
    this->insertMinimal(values, mid+1, end);
    return;
  }
//   else
//     return;
  
}

////////////////////////////////////////////////////////////////
void Tree::deleteKey(int value)
{

  if(root == NULL)
    return;
  
  Node * node = this->searchKey(value,root);
  if(node == NULL)
    return;
  
  // case 1: node is leaf
   if(node->right == NULL && node->left == NULL)
   {
     if(node->parent->right == node)
       node->parent->right = NULL;
     else
       node->parent->left = NULL;
     
     delete node;
   }
   // case 2: node has only a left or right subtree
   else if(node->right != NULL && node->left == NULL)
   {
	
	node->right->parent = node->parent;
	if(node->parent != NULL)
	{
	  if(node->parent->right == node)
	    node->parent->right = node->right;
	  else
	    node->parent->left = node->right;
	}
	else
	{
	  this->root = node->right; 
	}
     
	delete node;    
   }
   else if(node->right == NULL && node->left != NULL)
   {
	node->left->parent = node->parent;
	if(node->parent != NULL)
	{
	  if(node->parent->right == node)
	    node->parent->right = node->left;
	  else
	    node->parent->left = node->left;
	}
	else
	{
	  this->root = node->left;
	}
    }
   // case 3: node has two childs
   else
   {
     // find minimum in the right subtree or maximum in the left subtree
     Node * nodeMin = findMin(node->right);
     if(nodeMin == NULL)
       return;
     int minVal = nodeMin->key;
     this->deleteKey(minVal);
     node->key = minVal; 
   }
}  
  
////////////////////////////////////////////////////////////////
void Tree::destroy(Node * node)
{
    if(node != NULL)
    {
      this->destroy(node->left);
      this->destroy(node->right);
      std::cout<<"removing value: "<<node->key<<"\n";
      delete node;
    }
}


////////////////////////////////////////////////////////////////
void Tree::inOrder(Node * node)
{
  if(node!=NULL)
  {
    this->inOrder(node->left);
    std::cout<<node->key<<"\t";
    this->inOrder(node->right); 
  }
}


////////////////////////////////////////////////////////////////
void Tree::preOrder(Node * node)
{
  if(node!=NULL)
  {
    std::cout<<node->key<<"\t";    
    this->preOrder(node->left);
    this->preOrder(node->right); 
  }
}

////////////////////////////////////////////////////////////////
void Tree::postOrder(Node * node)
{
  if(node!=NULL)
  {
    this->postOrder(node->left);
    this->postOrder(node->right); 
    std::cout<<node->key<<"\t";    
  }
}


////////////////////////////////////////////////////////////////
int Tree::findMinimum(Node * node)
{
  if(node!=NULL){
    if(node->left == NULL)
      return node->key;
    else
      this->findMinimum(node->left);
  }
}

////////////////////////////////////////////////////////////////
Node * Tree::findMin(Node * node)
{
  if(node!=NULL){
    if(node->left == NULL)
      return node;
    else
      this->findMin(node->left);
  }
  else
    return NULL;
}

////////////////////////////////////////////////////////////////
int Tree::findMaximum(Node * node)
{
  if(node!=NULL){
    if(node->right == NULL)
      return node->key;
    else
      this->findMaximum(node->right);
  }
}

////////////////////////////////////////////////////////////////
Node * Tree::findMax(Node * node)
{
  if(node!=NULL){
    if(node->right == NULL)
      return node;
    else
      this->findMax(node->right);
  }
  else
    return NULL;
}

////////////////////////////////////////////////////////////////
Node * Tree::searchKey(int value, Node * node)
{
  
  if(node==NULL)
    return NULL;
  
  if(node->key==value)
    return node;
  
  if(value > node->key)
    this->searchKey(value,node->right);
  else
    this->searchKey(value,node->left);
}

////////////////////////////////////////////////////////////////
int Tree::findMaxHeight(Node * node)
{
  if(node==NULL)
    return 0;
  else
    return std::max(findMaxHeight(node->right),findMaxHeight(node->left))+1;
}

////////////////////////////////////////////////////////////////
int Tree::findMinHeight(Node * node)
{
  if(node==NULL)
    return 0;
  else
    return std::min(findMinHeight(node->right),findMinHeight(node->left))+1;
}

////////////////////////////////////////////////////////////////
bool Tree:: checkBalance(Node * node)
{
  int max_height = this->findMaxHeight(node);
  int min_height = this->findMinHeight(node);
  
  if((max_height-min_height)>1)
    return false;
  else
    return true;  
}




/***********************************************************************************************************/
int main()
{
  srand(time(NULL));
  Tree * tree = new Tree();
  
  int value;
  int deleteval;
  int * sorted_values = new int[20];
  for(int i=0; i<20; ++i){
      value = rand()%100;
      sorted_values[i] = 20-i;
      if(i==10)
	deleteval = value;
      std::cout<<value<<"\t";
      tree->insertKey(value,tree->root);
  }
  std::cout<<"\n";
  tree->inOrder(tree->root);
  std::cout<<"\n";
//   std::cout<<"maximum: "<<tree->findMaximum(tree->root)<<"\n";
//   std::cout<<"minimum: "<<tree->findMinimum(tree->root)<<"\n";
//   std::cout<<"value: "<<tree->searchKey(value,tree->root)->key<<"\n";
//   std::cout<<"tree height: "<<tree->findMaxHeight(tree->root)<<"\n";
//   std::cout<<"deleting  value: "<<deleteval<<"\n";
//   tree->deleteKey(deleteval);
//   std::cout<<"\n";
//   tree->inOrder(tree->root);
//   std::cout<<"\n";  
//   std::cout<<"tree height: "<<tree->findHeight(tree->root)<<"\n";
  
  // find and destroy elements after some key value
//   tree->destroy(tree->searchKey(deleteval,tree->root)->right);
//   std::cout<<"\n";
//   tree->inOrder(tree->root);
//   std::cout<<"\n";  
  std::cout<<"tree max height: "<<tree->findMaxHeight(tree->root)<<"\n";
  std::cout<<"tree min height: "<<tree->findMinHeight(tree->root)<<"\n";
  
  Tree * tree2 = new Tree();
  tree2->insertMinimal(sorted_values,0,19);
   std::cout<<"\n";
  tree2->inOrder(tree2->root);
  std::cout<<"\n";    
  
//   delete tree;
  
 return 0; 
}
