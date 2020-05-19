#include <utility>
#include <string>
#include <queue>
#include <iostream>
#include <set>

/**
 * We have seen how trees can be stored in 1-based arrays, where the left child of a node stored at index i is located at 2,
 * the right child is at 2 i + 1, and the parent is at floor (i/2)
 * 
 * For a node i, we can go directly to following nodes:
 * 1) Add:              (i + a) mod N
 * 2) Sub:              (i - s + N) mod N
 * 3) Multiplication:   (i * m) mod N
 * 4) Div:              (i / d) mod N (/ is integer division)
 * 5) Exponentiation:   (i ^ 2) mod N
 * 
 * Give a start node of 0 and target node, find the shortest path between these nodes
 * 
 * Input rule: 1 <= a, s, m, d and t < N = 1,000,001
 * 
 * Example:
 * input: 2 4 6 8 195
 * output: seeaamd
 * s : (      0 - 4 + 1000001) % 1000001 	= 999997
 * e : ( 999997 ^ 2) % 1000001 	= 16
 * e : (     16 ^ 2) % 1000001 	= 256
 * a : (    256 + 2) % 1000001 	= 258
 * a : (    258 + 2) % 1000001 	= 260
 * m : (    260 * 6) % 1000001 	= 1560
 * d : (   1560 / 8) % 1000001 	= 195
 */

std::string sovle(unsigned int a, unsigned int s, unsigned int m, unsigned int d, unsigned int t)
{

    const long int N = 1000001;
    if (a >= N || s >= N || m >= N || d >= N || t >= N ||
        a < 1 || s < 1 || m < 1 || d < 1 || t < 1)
    {
        std::cout << "0 < parameters < " << N << "\n";
        return "";
    }

    std::pair<std::string, long int> node_zero{"", 0};

    std::queue<std::pair<std::string, long int>> queue_nodes;
    queue_nodes.push(node_zero);

    std::set<int> unique_locations;
    while (!queue_nodes.empty())
    {
        std::pair<std::string, long int> node = queue_nodes.front();

        queue_nodes.pop();

        auto location = std::get<1>(node);
        std::string cur_path = std::get<0>(node);
        if (location == t)
        {
            std::cout << cur_path << "\n";
            return cur_path;
        }
        else if (unique_locations.insert(location).second == false)
        {
            // std::cout << "dulicate value " << location << "\n";
            continue;
        }

        queue_nodes.push(std::make_pair(cur_path.append("a"), (location + a) % N));
        queue_nodes.push(std::make_pair(cur_path.append("e"), (location * location) % N));
        queue_nodes.push(std::make_pair(cur_path.append("d"), (location / d) % N));
        queue_nodes.push(std::make_pair(cur_path.append("m"), (location * m) % N));
        queue_nodes.push(std::make_pair(cur_path.append("s"), (location - s + N) % N));
    }

    return "";
}

int main(int argc, char const *argv[])
{
    if (argc == 6)
    {
        sovle(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
    }
    else
    {
        std::cout << "Wrong parameters: tree_of_number <int a> <int s> <int m> <int d> <int t>\n";
    }

    return 0;
}
