#include <iostream>
#include <functional>
#include <random>
#include <list>

template <typename T>
class my_queue
{
private:
    std::list<T> __list;

public:
    my_queue(/* args */){};
    ~my_queue(){};

    void enqueue(const T &t)
    {
        __list.push_back(t);
    }
    T dequeue(void)
    {
        auto v = __list.front();
        __list.pop_front();
        return v;
    }

    bool empty(void)
    {
        return __list.empty();
    }

    int size(void)
    {
        return __list.size();
    }
};

template <typename K, typename V>
class simple_bin_tree
{
    struct simple_bin_tree_none
    {
        static unsigned long long int COUNT;

        const K key;
        V val;
        simple_bin_tree_none *lnode;
        simple_bin_tree_none *rnode;

        simple_bin_tree_none(const K &k, const V &v) : key(k), val(v), lnode(nullptr), rnode(nullptr)
        {
            simple_bin_tree_none::COUNT++;
            if (simple_bin_tree::DEBUG)
            {
                std::cerr << "created simple_bin_tree_none "
                          << this << ", count = " << simple_bin_tree_none::COUNT << std::endl;
            }
        };
        ~simple_bin_tree_none()
        {
            if (lnode != nullptr)
            {
                delete lnode;
            }
            if (rnode != nullptr)
            {
                delete rnode;
            }

            simple_bin_tree_none::COUNT--;

            if (simple_bin_tree::DEBUG)
            {
                std::cerr << "destroyed simple_bin_tree_none "
                          << this << ", count = " << simple_bin_tree_none::COUNT << std::endl;
            }
        };
    };

private:
    simple_bin_tree_none *__root;

public:
    simple_bin_tree(/* args */);
    ~simple_bin_tree();

    static bool DEBUG;

    void add(const K &k, const V &v);

    void printBinaryTreeDepthOrder();
};

template <typename K, typename V>
bool simple_bin_tree<K, V>::DEBUG = true;

template <typename K, typename V>
unsigned long long int simple_bin_tree<K, V>::simple_bin_tree_none::COUNT = 0;

template <typename K, typename V>
simple_bin_tree<K, V>::simple_bin_tree() : __root(nullptr)
{
}

template <typename K, typename V>
simple_bin_tree<K, V>::~simple_bin_tree()
{
    if (__root != nullptr)
    {
        delete __root;
    }
}

template <typename K, typename V>
void simple_bin_tree<K, V>::add(const K &k, const V &v)
{
    auto node = new (std::nothrow) simple_bin_tree_none(k, v);
    if (node == nullptr)
    {
        throw std::runtime_error("simple_bin_tree::add cannot allocate memory to new node");
    }

    if (__root == nullptr)
    {
        __root = node;
    }
    else
    {
        std::function<void(simple_bin_tree_none * node, simple_bin_tree_none * new_node)> insert;

        insert = [&insert](simple_bin_tree_none *node, simple_bin_tree_none *new_node) {
            if (node->key == new_node->key)
            {
                // update val and remove newnode;
                node->val = new_node->val;
                delete new_node;
            }
            else
            {
                auto &ref_node_ptr = (node->key < new_node->key) ? node->rnode : node->lnode;
                if (ref_node_ptr == nullptr)
                {
                    ref_node_ptr = new_node;
                }
                else
                {
                    insert(ref_node_ptr, new_node);
                }
            }
        };

        insert(__root, node);
    }
}

template <typename K, typename V>
void simple_bin_tree<K, V>::printBinaryTreeDepthOrder()
{
    my_queue<std::pair<simple_bin_tree_none *, int>> queue;
    if (__root != nullptr)
    {
        queue.enqueue(std::make_pair(__root, 0));
    }
    int current_level = 1;
    while (!queue.empty())
    {
        auto node_ptr = queue.dequeue();

        std::cout << node_ptr.first->val << " ";
        if (--current_level == 0)
        {
            std::cout << std::endl;
        }

        if (node_ptr.first->lnode != nullptr)
        {
            queue.enqueue(std::make_pair(node_ptr.first->lnode, node_ptr.second + 1));
        }

        if (node_ptr.first->rnode != nullptr)
        {
            queue.enqueue(std::make_pair(node_ptr.first->rnode, node_ptr.second + 1));
        }

        if (current_level == 0)
        {
            current_level = queue.size();
        }
    }
}

int main(int argc __attribute__((unused)), char const *argv[] __attribute__((unused)))
{
    // simple_bin_tree<int, int>::DEBUG = false;
    simple_bin_tree<int, int> my_tree;

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(-20, 20);
    auto dice = std::bind(distribution, generator);
    for (size_t i = 0; i < 20; i++)
    {
        int ran_num = dice();
        // int ran_num = i;
        std::cout << "my_tree.add(" << ran_num << "," << ran_num << ")" << std::endl;
        my_tree.add(ran_num, ran_num);
    }

    my_tree.printBinaryTreeDepthOrder();

    std::cout << "-----------auto clean up-----------" << std::endl;
    return 0;
}
