#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  node_t *nil = (node_t*)calloc(1,sizeof(node_t));
  nil -> color = RBTREE_BLACK;
  p->nil = p-> root = nil;
  return p;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  node_t *new_node = (node_t*)calloc(1,sizeof(node_t));
  new_node -> key= key;
  new_node ->color= RBTREE_RED;
  new_node ->left = new_node->right = t->nil;

  node_t *current = t-> root;
  while(current != t->nil){
    if(key<current->key){
      if(current -> left == t -> nil){
        current-> left= new_node;
        break;
      } 
      current = current -> left;
    }
    else{
      if(current -> right == t->nil){
        current -> right = new_node;
        break;
      }
      current = current->right;
    }
   

  }
  new_node -> parent = current;

  if(current == t->nil){
    t-> root = new_node;
  }
  return new_node;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
