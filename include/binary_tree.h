#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include <stdbool.h>
#include <stdlib.h>

struct binary_node {
  void* value;
  struct binary_node* left_node;
  struct binary_node* right_node;
} binary_node;

struct binary_tree {
  struct binary_node* root_node;
  size_t value_size;
  enum compare (*compare_value)(void*,void*);
  void (*copy_value)(void*, void*);
  void (*delete_value)(void*);
  char* (*value_to_string_function)(void*);
} binary_tree;

enum compare { LT, GT, EQ };
enum children_population { NONE, LEFT, RIGHT, BOTH };

bool insert_value(struct binary_tree* root, void* value);
bool delete_value(struct binary_tree* root, void* value);
bool find_value(struct binary_tree* root, void* value);
bool print_tree_infix(struct binary_tree* root);
bool print_tree_prefix(struct binary_tree* root);
bool print_tree_postfix(struct binary_tree* root);


enum children_population has_children(struct binary_node* node);
#endif
