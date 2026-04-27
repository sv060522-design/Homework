#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cctype>

std::string s;
std::mutex m;
std::condition_variable cv;
bool ready = false;
bool done = false;

void readFile()
{
    std::ifstream in("invisible_man.txt");

    if (!in.is_open())
    {
        std::unique_lock<std::mutex> lock(m);
        done = true;
        cv.notify_one();
        return;
    }

    std::string t;

    while (std::getline(in, t))
    {
        std::unique_lock<std::mutex> lock(m);

        cv.wait(lock, []()
        {
            return !ready;
        });

        s = t;
        ready = true;

        cv.notify_one();

        cv.wait(lock, []()
        {
            return !ready;
        });
    }

    std::unique_lock<std::mutex> lock(m);
    done = true;
    cv.notify_one();
}

void printFile()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(m);

        cv.wait(lock, []()
        {
            return ready || done;
        });

        if (!ready && done)
        {
            break;
        }

        std::string t = s;

        lock.unlock();

        for (char& c : t)
        {
            c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        }

        std::cout << t << std::endl;

        lock.lock();

        s.clear();
        ready = false;

        cv.notify_one();
    }
}

int main()
{
    std::thread t1(readFile);
    std::thread t2(printFile);

    t1.join();
    t2.join();

    return 0;
}