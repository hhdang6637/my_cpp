#include <iostream>
#include <fstream>
#include <string>
#include <malloc.h>
#include <sys/mman.h>

void show_mem_map(const char *file)
{
    std::string filename = "/proc/self/";
    filename.append(file);
    std::string line;

    std::ifstream file_stream(filename);
    if (file_stream.is_open())
    {
        std::cout << "********" << filename << "********" << std::endl;
        while (std::getline(file_stream, line))
        {
            std::cout << line << std::endl;
        }
    }
    else
    {
        std::cerr << "canot open file " << filename << std::endl;
    }
}

int main(int argc __attribute__((unused)), char const *argv[] __attribute__((unused)))
{
    int alloc_size = 1024 * 1024 * 256;

    void *ptr = malloc(alloc_size);
    if (mlock(ptr, alloc_size) == -1)
    {
        std::cerr << "cannot request mlock for " << ptr << std::endl;
        switch (errno)
        {
        case ENOMEM:
            std::cerr << "ENOMEM: nonzero RLIMIT_MEMLOCK soft resource limit" << std::endl;
            break;
        case EPERM:
            std::cerr << "EPERM : caller not privileged" << std::endl;
            break;
        default:
            std::cerr << "errno: " << errno << std::endl;
        }
    }

    show_mem_map("maps");
    show_mem_map("status");
    return 0;
}
