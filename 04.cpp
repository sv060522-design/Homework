#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <future>
#include <chrono>
#include <cctype>

using namespace std::chrono_literals;

std::string word(std::istream& in)
{
    std::string s;
    char c;

    while (in.get(c))
    {
        if (std::isspace((unsigned char)c))
            continue;

        if (c == '#')
        {
            std::string t;
            std::getline(in, t);
            continue;
        }

        s += c;
        break;
    }

    while (in.get(c))
    {
        if (std::isspace((unsigned char)c))
        {
            in.unget();
            break;
        }

        if (c == '#')
        {
            in.unget();
            break;
        }

        s += c;
    }

    return s;
}

int read(std::istream& in, int mx)
{
    char a, b;

    if (mx <= 255)
    {
        if (!in.get(a))
            return -1;

        return (unsigned char)a;
    }

    if (!in.get(a) || !in.get(b))
        return -1;

    return ((unsigned char)a) * 256 + (unsigned char)b;
}

std::string calc(const std::string& name)
{
    std::ifstream in(name, std::ios::binary);

    if (!in)
        return "File " + name + " do not exist";

    std::string type = word(in);
    std::string sw = word(in);
    std::string sh = word(in);
    std::string sm = word(in);

    if (type != "P3" && type != "P6")
        return "File " + name + " has wrong format";

    if (sw.empty() || sh.empty() || sm.empty())
        return "File " + name + " has wrong format";

    int w = std::stoi(sw);
    int h = std::stoi(sh);
    int mx = std::stoi(sm);

    if (w <= 0 || h <= 0 || mx <= 0)
        return "File " + name + " has wrong format";

    unsigned long long sr = 0;
    unsigned long long sg = 0;
    unsigned long long sb = 0;
    unsigned long long cnt = 1ULL * w * h;

    if (type == "P3")
    {
        for (unsigned long long i = 0; i < cnt; ++i)
        {
            std::string ar = word(in);
            std::string ag = word(in);
            std::string ab = word(in);

            if (ar.empty() || ag.empty() || ab.empty())
                return "File " + name + " has wrong format";

            sr += std::stoi(ar);
            sg += std::stoi(ag);
            sb += std::stoi(ab);
        }
    }
    else
    {
        char c;
        in.get(c);

        if (c == '\r' && in.peek() == '\n')
            in.get(c);

        for (unsigned long long i = 0; i < cnt; ++i)
        {
            int r = read(in, mx);
            int g = read(in, mx);
            int b = read(in, mx);

            if (r < 0 || g < 0 || b < 0)
                return "File " + name + " has wrong format";

            sr += r;
            sg += g;
            sb += b;
        }
    }

    return "Average color of " + name + " is: (" +
           std::to_string(sr / cnt) + ", " +
           std::to_string(sg / cnt) + ", " +
           std::to_string(sb / cnt) + ")";
}

void print(std::vector<std::future<std::string>>& v)
{
    for (size_t i = 0; i < v.size();)
    {
        if (v[i].wait_for(0ms) == std::future_status::ready)
        {
            std::cout << v[i].get() << std::endl;
            v.erase(v.begin() + i);
        }
        else
        {
            ++i;
        }
    }
}

int main()
{
    std::vector<std::future<std::string>> v;
    std::string s;

    while (true)
    {
        print(v);

        std::cout << "Enter image name: ";
        std::cin >> s;

        if (s == "quit")
            break;

        v.push_back(std::async(std::launch::async, calc, s));
    }

    for (auto& x : v)
        std::cout << x.get() << std::endl;
}