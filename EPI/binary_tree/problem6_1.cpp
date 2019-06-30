#include <memory>
#include <iostream>
#include <functional>
#include <vector>

template <typename K, typename V>
class bin_tree
{
    struct bin_tree_node
    {
        const K key;
        V val;
        std::unique_ptr<bin_tree_node> lnode, rnode;
        bin_tree_node(const K &k, const V &v) : key(k), val(v), lnode(nullptr), rnode(nullptr)
        {
            bin_tree_node::COUNT++;
            if (bin_tree::DEBUG)
            {
                std::cerr << "created bin_tree_node "
                          << this << ", count = " << bin_tree_node::COUNT << std::endl;
            }
        };

        ~bin_tree_node()
        {
            bin_tree_node::COUNT--;
            if (bin_tree::DEBUG)
            {
                std::cerr << "destroyed bin_tree_node "
                          << this << ", count = " << bin_tree_node::COUNT << std::endl;
            }
        };

        bin_tree_node &operator=(bin_tree_node &&node)
        {
            key = node.key;
            val = node.val;
            lnode = std::move(node.lnode);
            rnode = std::move(node.rnode);
            return *this;
        };

        static uint32_t COUNT;
    };

private:
    std::unique_ptr<bin_tree_node> __root;

public:
    bin_tree(/* args */);
    ~bin_tree();

    static bool DEBUG;

    void add(const K &k, const V &v);
};

template <typename K, typename V>
bool bin_tree<K, V>::DEBUG = true;

template <typename K, typename V>
uint32_t bin_tree<K, V>::bin_tree_node::COUNT = 0;

template <typename K, typename V>
bin_tree<K, V>::bin_tree(/* args */) : __root(nullptr)
{
}

template <typename K, typename V>
bin_tree<K, V>::~bin_tree()
{
}

template <typename K, typename V>
void bin_tree<K, V>::add(const K &k, const V &v)
{
    std::unique_ptr<bin_tree_node> node(new (std::nothrow) bin_tree_node(k, v));
    if (node.get() == nullptr)
    {
        throw std::runtime_error("bin_tree::add cannot allocate memory to new node");
    }
    if (__root.get() == nullptr)
    {
        __root = std::move(node);
    }
    else
    {
        std::function<void(std::unique_ptr<bin_tree_node> &, std::unique_ptr<bin_tree_node> &)> insertNode;
        insertNode = [&insertNode](std::unique_ptr<bin_tree_node> &node, std::unique_ptr<bin_tree_node> &new_node) {
            auto &refNode = node.get()->val < new_node.get()->val ? node.get()->rnode : node.get()->lnode;
            if (refNode.get() == nullptr)
            {
                refNode = std::move(new_node);
            }
            else
            {
                insertNode(refNode, new_node);
            }
        };

        insertNode(__root, node);
    }
}

int main(int argc __attribute((unused)), char const *argv[] __attribute((unused)))
{
    bin_tree<int, int> tree;

    /*
    for (size_t i = 0; i < 20; i++)
    {
        // int ran_num = dice();
        int ran_num = i;
        std::cout << "tree.add(" << ran_num << "," << ran_num << ")" << std::endl;
        tree.add(ran_num, ran_num);
    }
*/
    std::vector<int> numbers{
        1, -2, 2};

    for (const auto &n : numbers)
    {
        std::cout << "tree.add(" << n << "," << n << ")" << std::endl;
        tree.add(n, n);
    }

    std::cout << "-----------auto clean up-----------" << std::endl;
    return 0;
}
