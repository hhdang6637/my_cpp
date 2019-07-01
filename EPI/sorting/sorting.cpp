#include <random>
#include <functional>
#include <vector>
#include <iostream>
#include <algorithm>

void print_list(const std::vector<int> &list)
{
    std::array<char, 256> line;

    for (size_t i = 0; i < list.size(); i++)
    {
        snprintf(line.data(), line.size(), "list[%06lu] = %06d", i, list[i]);
        std::cout << line.data() << std::endl;
    }
}

void test_sort(uint size, std::function<void(std::vector<int> &)> f_sort, int start = 0, int end = 999)
{
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(start, end);
    auto dice = std::bind(distribution, generator);

    std::vector<int> list_number(size);
    std::generate(list_number.begin(), list_number.end(), dice);

    print_list(list_number);

    f_sort(list_number);

    std::cout << std::endl
              << std::endl;

    print_list(list_number);
}

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

/*
    heap sort
 */

void heap_sort(std::vector<int> &input)
{

    std::function<void(int *array, int n, int p)> heapify;
    heapify = [&heapify](int *array, int n, int p) {
        int l = p * 2 + 1;
        int r = l + 1;
        int largest = p;

        if (l < n && array[l] > array[largest])
        {
            largest = l;
        }

        if (r < n && array[r] > array[largest])
        {
            largest = r;
        }

        if (largest != p)
        {
            std::swap(array[largest], array[p]);
            heapify(array, n, largest);
        }
    };

    for (int i = (int)input.size() / 2 - 1; i >= 0; i--)
    {
        heapify(input.data(), input.size(), i);
    }

    for (int i = input.size() - 1; i >= 0; i--)
    {
        std::swap(input[i], input[0]);
        heapify(input.data(), i, 0);
    }
}

void quick_sort(std::vector<int> &input)
{
    std::function<int(int *array, int low, int high)> partition;
    partition = [](int *array, int low, int high) {
        int pivot = low - 1;
        for (int i = low; i <= high - 1; i++)
        {
            if (array[i] <= array[high])
            {
                pivot++;
                std::swap(array[pivot], array[i]);
            }
        }

        pivot++;
        std::swap(array[pivot], array[high]);

        return pivot;
    };

    std::function<void(int *, int, int)> quick_sort_internal;

    quick_sort_internal = [&partition, &quick_sort_internal](int *array, int low, int high) {
        if (low < high)
        {
            int pivot = partition(array, low, high);
            // Separately sort elements before
            // partition and after partition
            quick_sort_internal(array, low, pivot - 1);
            quick_sort_internal(array, pivot + 1, high);
        }
    };

    quick_sort_internal(input.data(), 0, input.size() - 1);
}

int main(int argc __attribute__((unused)), char const *argv[] __attribute__((unused)))
{
    // test_sort(10, bubble_sort);
    // test_sort(100, heap_sort);
    test_sort(100, quick_sort);
    return 0;
}
