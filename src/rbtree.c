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
  node_t *new_node = (node_t*)calloc(1,sizeof(node_t)); // 동적 할당으로 새 노드 생성
  new_node -> key= key; // 받아온 키로 노드 키 지정
  new_node ->color= RBTREE_RED; // 빨간색으로 초기화
  new_node ->left = new_node->right = t->nil; // 왼쪽, 오른쪽 전부 nil로 초기화

  node_t *current = t-> root; //현재 노드 -> rb트리의 루트노드
  while(current != t->nil){ // 현재 노드가 nil노드가 아닐때까지
    if(key<current->key){ // 입력 받은 키가 현재 노드의 키 값보다 작을 경우
      if(current -> left == t -> nil){ // 현재노드의 왼쪽 노드가 nil일 경우
        current-> left= new_node; // 현재 노드의 왼쪽노드에 new_node 넣기
        break; //멈춰
      } 
      current = current -> left; // 현재 노드 = 왼쪽노드
    }
    else{ // 키가 현재노드의 키보다 크거나 같을 경우
      if(current -> right == t->nil){ //현재노드의 오른쪽이 nil노드일 경우
        current -> right = new_node;  // 현재노드의 오른쪽에 new_node넣기
        break;
      }
      current = current->right; //현재 노드 = 오른쪽 노드
    }
   
  
  }
  new_node -> parent = current; // new node의 부모 = 현재노드

  if(current == t->nil){ // 현재노드가 nil노드 일때
    t-> root = new_node; // 루트에 new_node 삽입
  }


  
  rb_insert_fix(t,new_node); //불규칙 판단

  return new_node;
}
void rb_insert_fix(rbtree *t , node_t *node){
  node_t *parent = node->parent;
  node_t *grandParent = parent->parent;
  node_t *uncle;
  while(parent->color == RBTREE_RED){
    if (parent == grandParent->left){
      uncle= grandParent->right;
      if (uncle->color == RBTREE_RED){
        parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        grandParent->color = RBTREE_RED;
        node = grandParent;
      }else {
      if( node == parent->right){
        node = parent;
        left_rotate(t,node);

      }
      parent->color = RBTREE_BLACK;
      grandParent->color = RBTREE_RED;
      right_rotate(t,grandParent);
      }
    }else{
       uncle= grandParent->left;
      if (uncle->color == RBTREE_RED){
        parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        grandParent->color = RBTREE_RED;
        node = grandParent;
      }else {
      if( node == parent->left){
        node = parent;
        right_rotate(t,node);

      }
      parent->color = RBTREE_BLACK;
      grandParent->color = RBTREE_RED;
      left_rotate(t,grandParent);
      }
    }
  }
  t->root->color =RBTREE_BLACK;
}


void right_rotate(rbtree *t, node_t *node){
   node_t* y = node->left;
  node->left = y->right;

  if ( y->right != t->nil){
    y->right->parent = node;
  }

  y->parent = node->parent;

  if( node->parent == t->nil){
    t->root = y;
  }
  else if(node==node->parent->right){
    node->parent->right =y;
  }else{
    node->parent->left = y;
  }
  y->right = node;
  node->parent = y;

}

void left_rotate(rbtree *t, node_t *node){
   node_t* y = node->right;
  node->right = y->left;

  if ( y->left != t->nil){
    y->left->parent =node;
  }

  y->parent = node->parent;



  if( node->parent == t->nil){
    t->root = y;
  }
  else if(node==node->parent->left){
    node->parent->left =y;
  }else{
    node->parent->right = y;
  }
  y->left = node;
  node->parent = y;

}   
node_t *rbtree_find(const rbtree *t, const key_t key) {
  node_t *find_node = t->root;
  while(find_node != t->nil){
    if(key == find_node->key){
      return find_node;
    }else if(key > find_node->key){
      find_node = find_node->right;
    }else{
      find_node = find_node->left;
    }
  }
  return NULL;
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
