#include <random>
#include <functional>
#include <vector>
#include <iostream>

/*
    bubble sort
 */

void bubble_sort(std::vector<int> &input)
{
    for (size_t i = 0; i < input.size() - 1; i++)
    {
        bool swap = false;
        for (size_t j = 0; j < input.size() - 1 - i; j++)
        {
            if (input[j] > input[j + 1])
            {
                std::swap(input[j], input[j + 1]);
                swap = true;
            }
        }
        if (swap == false)
        {
            break;
        }
    }
}

void test_bubble_sort()
{
    std::array<char, 256> line;

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 999);
    auto dice = std::bind(distribution, generator);

    std::vector<int> list_number(100);
    for (size_t i = 0; i < list_number.size(); i++)
    {
        int ran_num = dice();
        list_number[i] = ran_num;
    }

    for (size_t i = 0; i < list_number.size(); i++)
    {
        snprintf(line.data(), line.size(), "list_number[%03lu] = %03d", i, list_number[i]);
        std::cout << line.data() << std::endl;
    }

    bubble_sort(list_number);

    std::cout << std::endl
              << std::endl;

    for (size_t i = 0; i < list_number.size(); i++)
    {
        snprintf(line.data(), line.size(), "list_number[%03lu] = %03d", i, list_number[i]);
        std::cout << line.data() << std::endl;
    }
}

int main(int argc __attribute__((unused)), char const *argv[] __attribute__((unused)))
{
    test_bubble_sort();
    return 0;
}
