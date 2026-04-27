#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <mutex>
#include <cctype>

std::string text;
std::mutex m;
bool done = false;

void readFile()
{
    std::ifstream in("invisible_man.txt");

    if (!in.is_open())
    {
        std::cerr << "File not found." << std::endl;

        std::lock_guard<std::mutex> lock(m);
        done = true;

        return;
    }

    std::string s;

    while (std::getline(in, s))
    {
        if (s.empty())
        {
            continue;
        }

        bool ok = false;

        while (!ok)
        {
            {
                std::lock_guard<std::mutex> lock(m);

                if (text.empty())
                {
                    text = s;
                    ok = true;
                }
            }

            if (!ok)
            {
                std::this_thread::yield();
            }
        }
    }

    std::lock_guard<std::mutex> lock(m);
    done = true;
}

void printText()
{
    while (true)
    {
        std::string s;
        bool ok = false;
        bool stop = false;

        {
            std::lock_guard<std::mutex> lock(m);

            if (!text.empty())
            {
                s = text;
                ok = true;
            }
            else if (done)
            {
                stop = true;
            }
        }

        if (stop)
        {
            break;
        }

        if (ok)
        {
            for (size_t i = 0; i < s.size(); i++)
            {
                s[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(s[i])));
            }

            std::cout << s << std::endl;

            std::lock_guard<std::mutex> lock(m);
            text.clear();
        }
        else
        {
            std::this_thread::yield();
        }
    }
}

int main()
{
    std::thread t1(readFile);
    std::thread t2(printText);

    t1.join();
    t2.join();

    return 0;
}