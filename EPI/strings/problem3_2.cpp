/*
Given a string containing a set of words separated by whitespace, we would like to
transform it to a string in which the words appear in the reverse order. For example,
“Alice likes Bob” transforms to “Bob likes Alice”. We do not need to keep the original
string.
Problem 3.2 : Implement a function for reversing the words in a string s.
 */

#include <iostream>
#include <string>
#include <algorithm>

std::string string_reverse(const std::string &in)
{
    std::string s = in;
    std::reverse(s.begin(), s.end());

    size_t start = 0, end;
    while ((end = s.find(' ', start)) != std::string::npos)
    {
        std::reverse(s.begin() + start, s.begin() + end);
        start = end + 1;
    }

    std::reverse(s.begin() + start, s.end());

    return s;
}

int main(int argc __attribute((unused)), char const *argv[] __attribute((unused)))
{
    std::string s = "Given a string containing a set of words separated";
    std::cout << s << " -> " << string_reverse(s) << std::endl;
    s = " Given a string containing a set of words separated";
    std::cout << s << " -> " << string_reverse(s) << std::endl;
    s = "Given a string containing a set of words separated ";
    std::cout << s << " -> " << string_reverse(s) << std::endl;
    return 0;
}
