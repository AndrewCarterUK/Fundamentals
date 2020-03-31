#include <iostream>
#include <vector>

template<typename T >
struct node_t {
    T value;
    node_t<T> * parent{ nullptr };
    node_t<T> * left{ nullptr };
    node_t<T> * right{ nullptr };
};

template<typename T>
class binary_search_tree
{
    private:
        node_t<T> * root{ nullptr };

        void delete_node_tree(node_t<T> * node) {
            if (node->left) {
                delete_node_tree(node->left);
            }

            if (node->right) {
                delete_node_tree(node->right);
            }

            delete node;
        }

    public:
        node_t<T> * insert(T value) {
            auto new_node{ new node_t<T> };

            new_node->value = value;

            if (!root) {
                root = new_node;
                return new_node;
            }

            auto node{ root };

            while (true) {
                if (value < node->value) {
                    if (node->left) {
                        node = node->left;
                    } else {
                        node->left = new_node;
                        new_node->parent = node;
                        return new_node;
                    }
                } else { // if value > node->value
                    if (node->right) {
                        node = node->right;
                    } else {
                        node->right = new_node;
                        new_node->parent = node;
                        return new_node;
                    }
                }
            }

            return new_node;
        }

        node_t<T> * search(T value) {
            auto node{ root };

            while (node) {
                if (node->value == value) {
                    return node;
                }

                if (value < node->value) {
                    node = node->left;
                } else { // if value > node->value
                    node = node->right;
                }
            }

            return nullptr;
        }

        void remove(T value) {
            auto node{ search(value) };

            if (node) {
                remove(node);
            }
        }

        void remove(node_t<T> * node) {
            auto leftmost {
                [] (node_t<T> * node) -> node_t<T> * {
                    while (node->left) {
                        node = node->left;
                    }

                    return node;
                }
            };

            auto unlink_swap {
                [this] (node_t<T> * node, node_t<T> * neighbour) {
                    if (node == root) {
                        root = neighbour;
                    }

                    if (node->parent) {
                        if (node->parent->left == node) {
                            node->parent->left = neighbour;
                        } else if (node->parent->right == node) {
                            node->parent->right = neighbour;
                        }
                    }

                    if (neighbour) {
                        if (neighbour->parent) {
                            // Always a left node as we use leftmost
                            neighbour->left = node->left;
                            neighbour->parent->left = nullptr;
                        }

                        neighbour->parent = node->parent;
                    }
                }
            };

            if (!node->left && !node->right) {
                // No children
                unlink_swap(node, nullptr);
            } else if (!node->left) {
                // One child (right)
                unlink_swap(node, node->right);
            } else if (!node->right) {
                // One child (left)
                unlink_swap(node, node->left);
            } else {
                // Two children
                unlink_swap(node, leftmost(node->right));
            }

            delete node;
        }

        void traverse(void (*callback) (node_t<T> *), node_t<T> * node = nullptr) {
            if (node == nullptr) {
                if (root == nullptr) {
                    return;
                }

                node = root;
            }

            if (node->left) {
                traverse(callback, node->left);
            }

            callback(node);

            if (node->right) {
                traverse(callback, node->right);
            }            
        }

        std::vector<T> to_vector() {
            auto vector_traverse {
                [] (node_t<T> * node, std::vector<T>& result, auto& vector_traverse) {
                    if (node == nullptr) {
                        return;
                    }

                    vector_traverse(node->left, result, vector_traverse);
                    result.push_back(node->value);
                    vector_traverse(node->right, result, vector_traverse);
                }
            };

            std::vector<T> result{ };
            vector_traverse(root, result, vector_traverse);

            return result;
        }

        ~binary_search_tree() {
            if (root) {
                delete_node_tree(root);
            }
        }
};

int main() {
    std::vector<int> my_list{ 101, 202, 100, 203, 444, 593, 208, 534, 352, 242, 252 };
    binary_search_tree<int> tree;

    // Test insert
    for (auto i = 0; i < my_list.size(); i++) {
        tree.insert(my_list[i]);
    }

    // Traverse
    tree.traverse([] (auto node) {
        std::cout << node->value << '\n';
    });


    // Delete
    std::cout << "\nLength Before: " << tree.to_vector().size() << '\n';
    tree.remove(242);
    std::cout << "Length After: " << tree.to_vector().size() << '\n' << '\n';

    return 0;
}
