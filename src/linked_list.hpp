#include <stdexcept>

template<typename T>
struct node_t {
    T value;
    node_t * next;
};

template<typename T>
class linked_list
{
    private:
        node_t<T> * root{ nullptr };

    public:
        node_t<T> * insert(T value) {
            auto node{ new node_t<T> };
            node->value = value;
            node->next = root;
            root = node;

            return node;
        }

        node_t<T> * find(T value) {
            auto node{ root };

            while (node) {
                if (node->value == value) {
                    return node;
                }

                node = node->next;
            }

            return nullptr;
        }

        void remove(T value) {
            auto ref{ &root };
            auto node{ root };

            while (node) {
                if (node->value == value) {
                    *ref = node->next;
                    delete node;
                    return;
                }

                ref = &(node->next);
                node = node->next;
            }

            throw std::runtime_error("Could not remove node");
        }

        int size() {
            auto node{ root };
            int size{ 0 };

            while (node) {
                size++;
                node = node->next;
            }

            return size;
        }

        ~linked_list() {
            auto node{ root };

            while (node) {
                delete node;

                node = node->next;
            }
        }
};
