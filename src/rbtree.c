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


// 메모리 해제
void postorder_delete_rbtree(rbtree *t, node_t *x) {
  if (x != t->nil) {
    postorder_delete_rbtree(t, x->left); //왼쪽 노드들 전부 해제
    postorder_delete_rbtree(t, x->right);// 오른쪽 노드들 전부 해제
    free(x);
  }
}

void delete_rbtree(rbtree *t) {
  postorder_delete_rbtree(t, t->root);
  free(t->nil);
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
  node_t *uncle; // 삼촌
  while(node->parent->color == RBTREE_RED){ // 부모의 색이 빨강일때만
    if (node->parent == node->parent->parent->left){ // 부모가 조부모의 왼쪽 자식일때
      uncle= node->parent->parent->right; // 삼촌은 조부모의 오른쪽자식
      if (uncle->color == RBTREE_RED){ // 삼촌이 빨강일 경우 case # 1
        node->parent->color = RBTREE_BLACK; // 부모 = 검정
        uncle->color = RBTREE_BLACK; // 삼촌 = 검청
        node->parent->parent->color = RBTREE_RED; // 조부모의 색 = 레드
        node = node->parent->parent; // 노드를 조부모로 변경 -> 조부모의 케이스 확인 용도
      }
      else { // 삼촌이 검정일 때
      if( node == node->parent->right){ // 노드가 부모의 오른쪽 자식일 때 case # 2 // 왼쪽으로 펴주기
        node = node->parent; // 노드를 부모로 변경
        left_rotate(t,node); // 왼쪽으로 회전


        }
        node->parent->color = RBTREE_BLACK; // 노드 부모의 색 = 검정
        node->parent->parent->color = RBTREE_RED; // 조부모의 색 = 빨강
        right_rotate(t,node->parent->parent); //조부모 기준으로 오른쪽 회전
      }
    }else{ // 부모가 오른쪽 자식일 때
       uncle= node->parent->parent->left; // 삼촌 = 조부모의 왼쪽
      if (uncle->color == RBTREE_RED){ // 삼촌이 빨강일때
        node->parent->color = RBTREE_BLACK; // 부모의 색 = 검정
        uncle->color = RBTREE_BLACK; //삼촌의 색 = 검정
        node->parent->parent->color = RBTREE_RED; // 조부모의 색 = 빨강
        node = node->parent->parent; // 노드를 조부모로 변경
      }else { // 삼촌의 색이 검정일 때
      if( node == node->parent->left){ // 노드가 왼쪽 자식일 때 
        node = node->parent; // 노드를 부모로 변경
        right_rotate(t,node); // 부모기준으로 오른쪽 회전

      }
      node->parent->color = RBTREE_BLACK; // 부모의 색을 검정
      node->parent->parent->color = RBTREE_RED; // 조부모의 색을 빨강
      left_rotate(t,node->parent->parent); // 조부모 기준으로 오른쪽 회전
      }
    }
  
  }
  t->root->color =RBTREE_BLACK; // 루트 = 검정
}


void right_rotate(rbtree *t, node_t *node){
   node_t* y = node->left; // y = 노드의 왼쪽자식
  node->left = y->right; // 노도의 왼쪽 자식 = y의 오른쪽 자식

  if ( y->right != t->nil){ // y의 오른쪽 자식이 nil이 아닐때
    y->right->parent = node; // y의 오른쪽 노드의 부모 = 노드로 변경
  }

  y->parent = node->parent; // y의 부모 = 노드의 부모로 변경

  if( node->parent == t->nil){ // 노드의 부모가 nil이라면
    t->root = y; // y는 root
  }
  else if(node==node->parent->right){ //노드가 노드 부모의 오른쪽 자식일때
    node->parent->right =y; // 노드의 부모의 오른쪽은 y
  }else{// 노드 부모의 왼쪽 자식일 때
    node->parent->left = y; // 노드 부모의 왼쪽 자식은 y
  }
  y->right = node; //y의 오른쪽노드는 노드
  node->parent = y; // 노드의 부모는 y

}

void left_rotate(rbtree *t, node_t *node){ // 왼쪽 회전
   node_t* y = node->right; // y = 노드의 오른쪽 자식
  node->right = y->left; // 노드의 오른쪽 = y의 왼쪽 자식

  if ( y->left != t->nil){ // y의 왼쪽 자식이 nil이 아닐때
    y->left->parent =node; // y의 왼쪽 자식의 부모 = 노드
  }

  y->parent = node->parent; // y의 부모 = 노드의 부모



  if( node->parent == t->nil){ // 노드의 부모가 nil일 때
    t->root = y; // t의 루트는 y
  }
  else if(node==node->parent->left){ // 노드가 부모의 왼쪽 자식일 때
    node->parent->left =y; // 노드의 부모의 왼쪽 자식 = y
  }else{ // 노드가 부모의 왼쪽 자식이 아닐때
    node->parent->right = y; // 부모의 오른쪽 자식 = y
  }
  y->left = node; // y의 왼쪽 = 노드 
  node->parent = y; // 노드의 왼쪽 =  y
  // 회전

}   
node_t *rbtree_find(const rbtree *t, const key_t key) { // 노드 찾기
  node_t *find_node = t->root; // 루트 노드부터 시작
  while(find_node != t->nil){ // 찾는 노드가 nil이 아닐때
    if(key == find_node->key){ // 키가 같으면 key를 리턴 - 찾은 경우
      return find_node; // 노드 반환
    }else if(key > find_node->key){ // 키가 find_node의 키보다 크면
      find_node = find_node->right; // 오른쪽 탐색
    }else{ // 아니면
      find_node = find_node->left; // 왼쪽 탐색
    }
  }
  return NULL; // 없을 경우
}

node_t *rbtree_min(const rbtree *t) {  // 최소값 반환
  // TODO: implement find
  node_t *min_node = t->root; // t->root부터 시작
  while (min_node->left != t->nil){ // 왼쪽노드가 nil일때까지
     min_node = min_node->left;
  }
  return min_node;
}

node_t *rbtree_max(const rbtree *t) { // 최대값 반환
  // TODO: implement find
   node_t *max_node = t->root; // t->root부터 시작
  while (max_node->right != t->nil){ // 오른쪽 노드가 nil일때까지
     max_node = max_node->right;
  }
  return max_node;
}

node_t *tree_minimum(const rbtree *t, node_t *sub_root){
    // TODO: implement find
    node_t *r = sub_root;
    if (r == t -> nil)
        return r;
    while (r -> left != t -> nil)
    {
        r = r -> left;
    }
    return r;
}

//////////////////////////// 삭제

int rbtree_erase(rbtree *t, node_t *z) {
 
  node_t *y = z; // 삭제하려는 노드 z를 우선 y에 저장. 
  node_t *x;
  color_t y_original_color = y->color; // y의 컬러를 저장

 
  
  if (z->left == t->nil){//유효한 값을 가진 자식이 오른쪽에만 하나 있는 경우
    x = z->right; //오른쪽 자식을 x에 담아두고
    transplant(t, z, z->right); //z의 오른쪽 자식을 z에 위치에 이식(transplant)하면서 z는 제거
    
    
  }else if(z->right == t->nil){//유효한 값을 가진 자식이 왼쪽에만 하나 있는 경우
    x = z->left;
   
    transplant(t, z, z->left);  // z의 왼쪽 자식을 z에 위치에 이식하면서 z는 제거됨
  }else{// 유효한 자식이 둘인 경우
    y = tree_minimum(t,z->right);   // y = z의 오른쪽 서브트리의 최소값 ( z의 successor)
    y_original_color = y->color; // 삭제 되는 컬러 저장
    x = y->right; // x는 y의 오른쪽 서브트리
    if (y->parent == z){ // y의 부모가 z일때
      x->parent = y; // x의 부모는 y  -> z가 삭제 되면서 y가 어차피 parent의 위치로 가기 때문
    }else{ 
      transplant(t, y, y->right); // y를 삭제하면서 y의 오른쪽을 y로 변경
      y->right = z->right; // y의 오른 자식 = z의 오른 자식
      y->right->parent = y; // y의 오른쪽 자식의 부모 = y
    }
    transplant(t, z, y);//z를 삭제하면서 y를 z의 위치로 변경
    y->left = z->left; // z의 왼쪽 서브트리를 y의 왼쪽으로 이식
    y->left->parent = y;
    y->color = z->color;
  }
  
  // fix up
  if (y_original_color == RBTREE_BLACK){ //지워지는 색이 검정일 경우
    node_t *brother;
    while (x!=t->root && x->color == RBTREE_BLACK){// x가 루트가 아니고, x의 컬러가 블랙일때
      if(x == x->parent->left){ // x가 왼쪽 자식일 때
        brother = x->parent->right; // x의 형제
        // x 의 형제가 RED 인 경우
        if(brother->color == RBTREE_RED){ // 형제의 컬러가 레드일때 case # 1
          brother->color = RBTREE_BLACK; // 형제의 컬러 = 검정
          x->parent->color = RBTREE_RED; // x의 부모의 컬러 = 빨강
          left_rotate(t, x->parent); // 부모 기준으로 왼쪽 회전
          brother = x->parent->right; // 형재는 x부모의 오른쪽
        }
        // X의 형제는 BLACK이고 형제의 두 자식이 모두 BLACK인 경우
        if(brother->left->color == RBTREE_BLACK && brother->right->color==RBTREE_BLACK){ // 형제의 왼쪽 색이 검정이고 형제의 오른쪽 컬러가 검정일때 case # 2
          brother->color = RBTREE_RED; // 형제의 컬러 = 빨강
          x = x->parent; // x는 x의 부모
        // X의 형제는 BLACK, 형제의 왼쪽 자식은 RED, 형제의 오른쪽 자식은 BLACK인 경우
        }else{ 
          if(brother->right->color == RBTREE_BLACK){ //형제의 오른쪽 색 = 검정 case # 3
            brother->left->color = RBTREE_BLACK; // 형제의 왼쪽 색 = 검정
            brother->color = RBTREE_RED; // 형제의 컬러 = 빨강
            right_rotate(t, brother); // 오른쪽 회전
            brother = x->parent->right; // 형제 = x의 부모의 오른쪽자식
          }
          // X의 형제는 BLACK이고 형제의 오른쪽 자식은 RED인 경우
          brother->color = x->parent->color; // 형제의 색 = x의 부모의 색 case # 4
          x->parent->color = RBTREE_BLACK;  
          brother->right->color = RBTREE_BLACK;
          left_rotate(t, x->parent);
          x = t->root;
        }
      }else{
        //오른쪽 케이스 ( 왼쪽, 오른쪽만 반대고 동일함)
        brother = x->parent->left;
        if(brother->color == RBTREE_RED){
          brother->color = RBTREE_BLACK;
          x->parent->color = RBTREE_RED;
          right_rotate(t, x->parent);
          brother = x->parent->left;
        }
        if(brother->right->color == RBTREE_BLACK && brother->left->color==RBTREE_BLACK){
          brother->color = RBTREE_RED;
          x = x->parent;
        }else{
          if(brother->left->color == RBTREE_BLACK){
            brother->right->color = RBTREE_BLACK;
            brother->color = RBTREE_RED;
            left_rotate(t, brother);
            brother = x->parent->left;
          }
          brother->color = x->parent->color;
          x->parent->color = RBTREE_BLACK;
          brother->left->color = RBTREE_BLACK;
          right_rotate(t, x->parent);
          x = t->root;
        }
      }
    }
    x->color = RBTREE_BLACK;
  }
  free(z);
  return 0;
  // erase 끝
}

// 이식하는 함수
// 서브 트리 이동을 위해 노드가 u가 루트인 서브트리를 노드 v가 루트인 서브트리로 교체
void transplant(rbtree *t, node_t *u, node_t *v){
  if (u->parent == t->nil){ // u의 부모가 nil 즉, u가 루트노드라면
    t->root = v; //v를  트리의 루트노드로 삼는다.
  }else if(u == u->parent->left){ //u가 부모의 왼쪽 자식일 경우
    u->parent->left = v; //v를 왼쪽 자식으로 이식 (u를 대체)
  }else{ //오른쪽 자식일 경우
    u->parent->right = v; //v를 오른쪽 자식으로 이식
  }
  v->parent = u->parent;
}


// 삭제 ///////////////////////////

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
   node_t *x = t->root;
  if (x == t->nil) {
    return 0;
  }
  int cnt = 0;
  int *idx = &cnt;
  inorder_rbtree_to_array(t, x, arr, idx, n);
  return 0;
}

// [중위 순회]
void inorder_rbtree_to_array(const rbtree *t, node_t *x, key_t *arr, int *idx, const size_t n) {
  if (x == t->nil) {
    return;
  }
  
  inorder_rbtree_to_array(t, x->left, arr, idx, n);
  if (*idx < n) {
    arr[(*idx)++] = x->key;                           // *idx는 0, 1, 2, 3...이다. 그리고 후위 연산자 ++이므로 0부터 인덱스가 시작된다.
  } else {
    return;
  }
  inorder_rbtree_to_array(t, x->right, arr, idx, n);
}



