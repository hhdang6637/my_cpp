/*
Design a stack that supports a max operation, which returns the
maximum value stored in the stack.
 */

#include <stack>
#include <utility>
#include <iostream>

template <typename T>
class my_stack
{
private:
    std::stack<T> __std_stack;
    std::stack<std::pair<T, int>> __sub_stack;

public:
    my_stack(/* args */){};
    ~my_stack(){};

    void push(const T &t)
    {
        __std_stack.push(t);
        if (__sub_stack.empty() || t > __sub_stack.top().first)
        {
            __sub_stack.push(std::make_pair(t, 1));
        }
        else if (t == __sub_stack.top().first)
        {
            __sub_stack.top().second++;
        }
    }

    void pop()
    {
        if (__sub_stack.empty())
        {
            throw "stack is empty";
        }
        if (__sub_stack.top().first == __std_stack.top())
        {
            if (--__sub_stack.top().second == 0)
            {
                __sub_stack.pop();
            }
        }

        __std_stack.pop();
    }

    T max() const
    {
        if (__sub_stack.empty())
        {
            throw "stack is empty";
        }
        return __sub_stack.top().first;
    }
};

int main(int argc __attribute__((unused)), char const *argv[] __attribute__((unused)))
{
    my_stack<int> stack;

    stack.push(1);
    stack.push(5);
    stack.push(4);
    stack.push(5);
    stack.push(6);
    std::cout << "max " << stack.max() << std::endl;
    stack.pop();
    std::cout << "max " << stack.max() << std::endl;
    stack.pop();
    std::cout << "max " << stack.max() << std::endl;
    stack.pop();
    std::cout << "max " << stack.max() << std::endl;
    stack.pop();
    std::cout << "max " << stack.max() << std::endl;
    return 0;
}
