#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

int power_base(int base, int size);
void power_base_test();

char digit_to_char(unsigned int i);
void digit_to_char_test();

std::string out_base(long int v, int b2);
void out_base_test();

long int base_in(int b1, const std::string &s);
void base_in_test();

std::string convert_base(int b1, const std::string &s, int b2);
void convert_base_test();

std::string ConvertBase(const std::string &s, int b1, int b2);
void ConvertBaseTest();

int main(int argc __attribute((unused)), char const *argv[] __attribute((unused)))
{
    // std::string s = "0123456";
    // convert_base(10, s, 10);
    // power_base_test();
    // digit_to_char_test();
    // out_base_test();
    // base_in_test();
    // convert_base_test();
    ConvertBaseTest();
    return 0;
}

int power_base(int base, int size)
{
    int s = 1;

    for (int i = 0; i < size; i++)
    {
        s *= base;
    }

    return s;
};

void power_base_test()
{
    int i;

    i = power_base(10, 2);
    std::cout << "i = power_base(10, 2); i = " << i << std::endl;

    if (i != 100)
    {
        throw "power_base_test got exception";
    }

    i = power_base(10, 3);
    std::cout << "i = power_base(10, 3); i = " << i << std::endl;
    if (i != 1000)
    {
        throw "power_base_test got exception";
    }

    i = power_base(10, 0);
    std::cout << "i = power_base(10, 0); i = " << i << std::endl;
    if (i != 1)
    {
        throw "power_base_test got exception";
    }
}

char digit_to_char(unsigned int i)
{
    if (i <= 9)
    {
        return '0' + (i - 0);
    }
    else if (i <= 15)
    {
        return 'A' + (i - 10);
    }
    else
    {
        throw "invalid input";
    }
};

void digit_to_char_test()
{
    try
    {
        std::cout << "digit_to_char(0)  -> " << digit_to_char(0) << std::endl;
        std::cout << "digit_to_char(9)  -> " << digit_to_char(9) << std::endl;
        std::cout << "digit_to_char(10) -> " << digit_to_char(10) << std::endl;
        std::cout << "digit_to_char(15) -> " << digit_to_char(15) << std::endl;
        std::cout << "digit_to_char(16) -> " << digit_to_char(16) << std::endl;
        throw "digit_to_char_test got exception";
    }
    catch (...)
    {
    }
}

std::string out_base(long int v, int b2)
{
    std::string out = "";
    bool nagative = false;
    if (v < 0)
    {
        nagative = true;
        v = -v;
    }

    while (v > 0)
    {
        out += digit_to_char(v % b2);
        v = v / b2;
    }

    if (nagative)
    {
        out += '-';
    }

    std::reverse(out.begin(), out.end());

    return out;
};

void out_base_test()
{
    std::cout << "out_base(129, 16) -> " << out_base(129, 16) << std::endl;
    std::cout << "out_base(129, 10) -> " << out_base(129, 10) << std::endl;
    std::cout << "out_base(129, 8)  -> " << out_base(129, 8) << std::endl;
    std::cout << "out_base(129, 2)  -> " << out_base(129, 2) << std::endl;

    std::cout << "out_base(-129, 16) -> " << out_base(-129, 16) << std::endl;
    std::cout << "out_base(-129, 10) -> " << out_base(-129, 10) << std::endl;
    std::cout << "out_base(-129, 8)  -> " << out_base(-129, 8) << std::endl;
    std::cout << "out_base(-129, 2)  -> " << out_base(-129, 2) << std::endl;
}

long int base_in(int b1, const std::string &s)
{
    bool nagative = false;
    long int s_val = 0;

    for (int i = s.size() - 1; i >= 0; i--)
    {
        if (i == 0 && s[i] == '-')
        {
            nagative = true;
            break;
        }

        int v = s[i] - '0';
        if (v != 0)
        {
            s_val += v * power_base(b1, (s.size() - 1) - i);
        }
    }

    if (nagative)
    {
        s_val = -s_val;
    }

    return s_val;
}

void base_in_test()
{
    /*
    out_base(129, 16) -> 81
    out_base(129, 10) -> 129
    out_base(129, 8)  -> 201
    out_base(129, 2)  -> 10000001
    out_base(-129, 16) -> -81
    out_base(-129, 10) -> -129
    out_base(-129, 8)  -> -201
    out_base(-129, 2)  -> -10000001
     */

    std::cout << "base_in(16, '81')         -> " << base_in(16, "81") << std::endl;
    std::cout << "base_in(10, '129')        -> " << base_in(10, "129") << std::endl;
    std::cout << "base_in(8, '201')         -> " << base_in(8, "201") << std::endl;
    std::cout << "base_in(2, '10000001')    -> " << base_in(2, "10000001") << std::endl;

    std::cout << "base_in(16, '-81')        -> " << base_in(16, "-81") << std::endl;
    std::cout << "base_in(10, '-129')       -> " << base_in(10, "-129") << std::endl;
    std::cout << "base_in(8, '-201')        -> " << base_in(8, "-201") << std::endl;
    std::cout << "base_in(2, '-10000001')   -> " << base_in(2, "-10000001") << std::endl;
}

std::string convert_base(int b1, const std::string &s, int b2)
{

    if ((b1 >= 2 && b1 <= 16) && (b2 >= 2 && b2 <= 16))
    {
        if (b1 == b2)
        {
            return s;
        }
        else
        {
            return out_base(base_in(b1, s), b2);
        }
    }
    else
    {
        return "";
    }
}

void convert_base_test()
{
    std::vector<int> base{2, 8, 10, 16};

    for (const auto &b1 : base)
    {
        for (const auto &b2 : base)
        {
            std::cout << "convert_base(" << b1 << ", '" << out_base(129, b1) << "', " << b2 << ")        -> " << convert_base(b1, out_base(129, b1), b2) << std::endl;
        }
    }

    for (const auto &b1 : base)
    {
        for (const auto &b2 : base)
        {
            std::cout << "convert_base(" << b1 << ", '" << out_base(-129, b1) << "', " << b2 << ")        -> " << convert_base(b1, out_base(-129, b1), b2) << std::endl;
        }
    }

    for (const auto &b1 : base)
    {
        for (const auto &b2 : base)
        {
            std::cout << "convert_base(" << b1 << ", '" << out_base(100000000, b1) << "', " << b2 << ")        -> " << convert_base(b1, out_base(100000000, b1), b2) << std::endl;
        }
    }
}

std::string ConvertBase(const std::string &s, int b1, int b2)
{
    bool is_negative = s.front() == '-' ? true : false;

    long int x = 0;
    for (size_t i = is_negative ? 1 : 0; i < s.size(); ++i)
    {
        x *= b1;
        x += isdigit(s[i]) ? s[i] - '0' : s[i] - 'A' + 10;
    }

    std::string out = "";
    do
    {
        int reminder = x % b2;
        out.push_back(reminder >= 10 ? 'A' + (reminder - 10) : '0' + reminder);
        x /= b2;
    } while (x);

    if (is_negative)
    {
        out.push_back('-');
    }

    std::reverse(out.begin(), out.end());

    return out;
}

void ConvertBaseTest()
{
    std::vector<int> base{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

    int mid_number = 129;

    for (const auto &b1 : base)
    {
        for (const auto &b2 : base)
        {
            std::cout << "ConvertBase(" << b1 << ", '" << out_base(mid_number, b1) << "', " << b2 << ")        -> "
                      << ConvertBase(out_base(mid_number, b1), b1, b2) << std::endl;
        }
    }

    for (const auto &b1 : base)
    {
        for (const auto &b2 : base)
        {
            std::cout << "ConvertBase(" << b1 << ", '" << out_base(-mid_number, b1) << "', " << b2 << ")        -> "
                      << ConvertBase(out_base(-mid_number, b1), b1, b2) << std::endl;
        }
    }
}
