#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {

    TreeMap * arbol = (TreeMap *)malloc(sizeof(TreeMap));  
    arbol->lower_than = lower_than;
  
    return arbol;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
   if (tree == NULL || key == NULL || value == NULL) {
        return; // 
    }

  if(searchTreeMap(tree, key) != NULL) return;
    
    if (tree->root == NULL) { 
        TreeNode*node = createTreeNode(key, value);
        
        tree->root = node;
        tree->current = node;
        return;
    }
    
    TreeNode* current = tree->root;
    TreeNode* parent_node = NULL;
    
    while (current != NULL) {
        if (tree->lower_than(key, current->pair->key)) {
            parent_node = current;
            current = current->left;
        } else if (tree->lower_than(current->pair->key, key)) {
            parent_node = current;
            current = current->right;
        } 
    }
    
    TreeNode* node = createTreeNode(key, value);
    node->parent = parent_node;
    
    if (tree->lower_than(key, parent_node->pair->key)) {
        parent_node->left = node;
    } else {
        parent_node->right = node;
    }
    
    tree->current = node;
}


TreeNode * minimum(TreeNode * x){
 if (x == NULL) {
        return NULL;
    }
    while (x->left != NULL) {
        x = x->left;
    }
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
    if(node == NULL) {
      return;
    }

   if (node->left == NULL && node->right == NULL) { 
        if (node->parent == NULL) { 
            tree->root = NULL;
        } else {
            if (node->parent->left == node) {
               node->parent->left = NULL;
            } else {
                node->parent->right = NULL;
            }
        }
        free(node);
     
    } else if(node->left == NULL || node->right == NULL) {
        TreeNode *hijoNodo;
        if (node->left != NULL) {
            hijoNodo = node->left;
        } else {
            hijoNodo = node->right;
        }

     if (node->parent == NULL) { 
            tree->root = hijoNodo;
            hijoNodo->parent = NULL;
        } else {
            if (node->parent->left == node) {
                node->parent->left = hijoNodo;
            } else {
                node->parent->right = hijoNodo;
            }
            hijoNodo->parent = node->parent;
        }
        free(node);
     
    }



  
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}

Pair * searchTreeMap(TreeMap * tree, void* key) {
  tree->current = tree->root;

  if(tree->root == NULL) return NULL;

  while(tree->current != NULL) {
    if(is_equal(tree, tree->current->pair->key, key)) {
      return tree->current->pair;
    }

    if(tree->lower_than(tree->current->pair->key, key)) {
      tree->current = tree->current->right;
    } else {
      tree->current = tree->current->left;
    }
  }
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
