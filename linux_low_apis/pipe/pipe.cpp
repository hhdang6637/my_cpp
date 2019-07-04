#include <iostream>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <signal.h>
#include <sstream>
#include <vector>
#include <array>

static volatile bool stop = false;
static volatile int child_thread_count = 0;
static std::mutex child_thread_count_mutex;

int fds[2];

void test_pipe()
{
    auto thread_f = []() {
        std::stringstream ss;
        ss << std::this_thread::get_id() << " I'm still alive\n";
        std::string line = ss.str();

        while (!stop)
        {
            ::write(fds[1], line.data(), line.size());
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

        ss.clear();
        ss << std::this_thread::get_id() << " CHILD DONE\n";
        line = ss.str();
        ::write(fds[1], line.data(), line.size());

        child_thread_count_mutex.lock();

        if (--child_thread_count == 0)
        {
            close(fds[1]);
        }

        child_thread_count_mutex.unlock();
    };

    std::vector<std::thread> threads;
    for (size_t i = 0; i < 10; i++)
    {
        child_thread_count_mutex.lock();
        child_thread_count++;
        child_thread_count_mutex.unlock();
        threads.emplace_back(std::thread(thread_f));
    }

    char c;
    int len;
    while ((len = ::read(fds[0], &c, 1)) != 0)
    {
        if (len < 0)
        {
            continue;
        }
#if 0
        if (c != '\n')
        {
            std::cout << c;
        }
        else
        {
            std::cout.flush();
            std::this_thread::sleep_for(std::chrono::milliseconds(41));
            std::cout << "\r";
            std::cout.flush();
        }
#else
        std::cout << c;
        // std::cout.flush();
#endif
    }

    close(fds[0]);

    std::cout << "\nMAIN - DONE" << std::endl;

    for (auto &i : threads)
    {
        i.join();
    }
}

int main(int argc __attribute__((unused)), char const *argv[] __attribute__((unused)))
{
    if (::pipe(fds) == -1)
    {
        std::cerr << "cannot request pipe" << std::endl;
        switch (errno)
        {
        default:
            std::cerr << "errno: " << errno << std::endl;
        }
        exit(-1);
    }

    struct sigaction sigact;
    sigact.sa_flags = 0;
    sigemptyset(&sigact.sa_mask);

    sigact.sa_handler = [](int signo) {
        std::array<char, 256> line;
        int n = snprintf(line.data(), line.size(), "CHILD: Received signal %d \n", signo);
        ::write(fds[1], line.data(), n);
        // if (signo == SIGTERM)
        {
            stop = true;
        }
    };

    if (sigaction(SIGQUIT, &sigact, NULL) < 0)
    {
        std::cerr << "sigaction SIGHUP failed" << std::endl;
    }

    if (sigaction(SIGTERM, &sigact, NULL) < 0)
    {
        std::cerr << "sigaction SIGTERM failed" << std::endl;
    }

    if (sigaction(SIGINT, &sigact, NULL) < 0)
    {
        std::cerr << "sigaction SIGINT failed" << std::endl;
    }

    sigaction(SIGQUIT, &sigact, nullptr);
    test_pipe();
    return 0;
}
