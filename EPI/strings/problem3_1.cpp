/*
A string is a sequence of characters. A string may encode an integer, e.g., “123”
encodes 123. In this problem, you are to implement methods that take a string
representing an integer and return the corresponding integer, and vice versa. Your
code should handle negative integers. You cannot use library functions like stoi in
C++ and parseInt in Java.
 */

#include <string>
#include <iostream>
#include <algorithm>

int string2int(const std::string &s)
{

    if (s.empty())
    {
        return 0;
    }

    bool nagative = (s[0] == '-');
    int n = 0;

    for (size_t i = (nagative ? 1 : 0); i <= s.size() - 1; i++)
    {
        if (isdigit(s[i]))
        {
            n = n * 10 + (s[i] - '0');
        }
        else
        {
            return 0;
        }
    }

    return nagative ? -n : n;
}

void string2int_test()
{
    std::cout << "string2int('-123456')  -> " << string2int("-123456") << std::endl;
    std::cout << "string2int('123456')   ->  " << string2int("123456") << std::endl;
    std::cout << "string2int('464647')   ->  " << string2int("464647") << std::endl;
    std::cout << "string2int('1')   ->  " << string2int("1") << std::endl;
}

std::string int2string(int i)
{
    std::string s;
    bool nagative = false;
    if (i < 0)
    {
        nagative = true;
        i = -i;
    }

    do
    {
        s.push_back((i % 10) + '0');
        i /= 10;
    } while (i);

    if (nagative)
    {
        s.push_back('-');
    }
    std::reverse(s.begin(), s.end());

    return s;
}

void int2string_test()
{
    std::cout << "int2string(-123456)  -> " << int2string(-123456) << std::endl;
    std::cout << "int2string(123456)   ->  " << int2string(123456) << std::endl;
    std::cout << "int2string(464647)   ->  " << int2string(464647) << std::endl;
    std::cout << "int2string(0)   ->  " << int2string(0) << std::endl;
}

int main(int argc, char const *argv[])
{
    string2int_test();
    int2string_test();
    return 0;
}
