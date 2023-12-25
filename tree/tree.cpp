#include "tree.hpp"

auto tree::insert(int val) -> tree_node * {
    tree_node* node = find_node(root.get(), val);
     if (node != nullptr) {
        return node;
     }
     tree_node::tree_node* new_node = new tree_node(val);
     if (!root) {
        root.reset(new_node);
        return new_node;
     }
     tree_node* parent = nullptr;
     node = root.get();
     while (node != nullptr) {
        parent = node;
        if (val < node->value) {
          node = node->left.get();
        } else {
          node = node->right.get();
        }
     }
     if (val < parent->value) {
        parent->left.reset(new_node);
     } else {
        parent->right.reset(new_node);
     }
     new_node->parent.reset(parent);
     return new_node;
}

auto tree::remove(int val) -> bool {
    tree_node *node = find_node(root.get(), val);
     if (node == nullptr) {
        return false;
     }
     tree_node *parent = node->parent;
     if (node->left != nullptr && node->right != nullptr) {
        tree_node *successor = node->right;
        while (successor->left != nullptr) {
          successor = successor->left;
        }
        node->value = successor->value;
        node = successor;
     }
     if (node->left != nullptr) {
        parent->replace_child(node, std::move(node->left));
     } else {
        parent->replace_child(node, std::move(node->right));
     }
     delete node;
     return true;
}

void replace_child(tree_node *old_child, std::unique_ptr<tree_node> &&new_child) {
 if (this->left == old_child) {
    this->left = std::move(new_child);
 } else {
    this->right = std::move(new_child);
 }
