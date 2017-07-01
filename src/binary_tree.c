#include "binary_tree.h"

bool insert_value_recur(struct binary_tree* root, struct binary_node* node, void* value){
  if(node == NULL) {
    node = (struct binary_node*) malloc(sizeof(binary_node));
    root->copy_value(node->value, value);
  } else {
    enum compare c = root->compare_value(node->value, value); 
    switch(c) {
      case EQ:
        return false;
        break;
      case LT:
        return insert_value_recur(root, node->left_node, value);
      case GT:
        return insert_value_recur(root, node->right_node, value);
      default:
    }
  }
  return true;
}

bool insert_value(struct binary_tree* root, void* value){
  return insert_value_recur(root, root->root_node, value);
}

bool find_value_recur(struct binary_tree* root, struct binary_node* node, void* value) {
   if(node == NULL) {
     return false;
  } else {
    enum compare c = root->compare_value(node->value, value); 
    if(c == EQ){
      return true;
    } else if (c == LT) {
      return find_value_recur(root, node->left_node, value);
    } else {
      return find_value_recur(root, node->right_node, value);
    }
  }
  return false;   
}

bool find_value(struct binary_tree* root, void* value) {
  return find_value_recur(root, root->root_node, value);
}

enum children_population has_children(struct binary_node* node) {
  if( (node->left_node == NULL) && (node->right_node == NULL) ) {
    return NONE;
  } else if ((node->left_node == NULL) && (node->right_node != NULL)) {
    return RIGHT;
  } else if ((node->left_node != NULL) && (node->right_node == NULL)) {
    return LEFT;
  } else {
    return BOTH;
  }
}

struct binary_node* delete_help(struct binary_tree* root, struct binary_node* node, void* value) {
  struct binary_node *l, *r;
  enum compare c;
  if(node == NULL) {
   return node; 
  } else {
    enum children_population child_case = has_children(node);
    switch(child_case) {
      case NONE:
        if(root->compare_value(node->value, value) == EQ) {
          root->delete_value(node->value);
          free(node);
          return NULL;
        } else {
          return node;
        }
        break;
      case LEFT:
        l = node->left_node;
        c = root->compare_value(node->value, value);
        switch (c) {
          case EQ:
            root->delete_value(node->value);
            free(node);
            return l;
            break;
          case LT:
            return node;
            break;
          case GT:
            node->left_node = delete_help(root, l, value);
            return node;
            break;
          default:
            return node;
        }
        break;
      case RIGHT:
        r = node->right_node;
        c = root->compare_value(node->value, value);
        switch (c) {
          case EQ:
            root->delete_value(node->value);
            free(node);
            return r;
            break;
          case LT:
            node->right_node = delete_help(root, r, value);
            return node;
          case GT:
          default:
            return node;
        }
        break;
      case BOTH:
        l = node->left_node;
        r = node->right_node;
        c = root->compare_value(node->value, value);
        switch(c) {
          case EQ: //super hard
            //may need to create a temp node with temp value
            //temp value comes from some leaf that can fill the given node's place
            //delete leaf | move leaf (change children to match node's children
            //return temp node
          case LT:
            node->right_node = delete_help(root, r, value);
            return node;
            break;
          case GT:
            node->left_node = delete_help(root, l, value);
            return node;
            break;
          default:
            return node;
        }
        break;
      default:
        return node;
    }
  }
  return node;

}

bool delete_value(struct binary_tree* root, void* value) {
  struct binary_node* temp = delete_help(root, root->root_node, value); 
  root->root_node = temp;
  return true;
}
