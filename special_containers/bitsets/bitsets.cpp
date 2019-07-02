#include <bitset>
#include <iostream>

void test_1()
{
    std::bitset<8> bits_1("11010");
    std::bitset<8> bits_2("10101");

    std::cout << bits_1 << std::endl;
    std::cout << bits_2 << std::endl;

    auto bit_tmp = bits_1;
    std::cout << bit_tmp.operator|=(bits_2) << " or" << std::endl;

    bit_tmp = bits_1;
    std::cout << bit_tmp.operator&=(bits_2) << " and" << std::endl;

    bit_tmp = bits_1;
    std::cout << bit_tmp.operator^=(bits_2) << " xor" << std::endl;

    bit_tmp = bits_1;
    std::cout << bit_tmp.operator~() << " not" << std::endl;
}

int main(int argc __attribute__((unused)), char const *argv[] __attribute__((unused)))
{
    test_1();
    return 0;
}
