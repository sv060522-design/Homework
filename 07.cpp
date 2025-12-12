#include <iostream>
#include <queue>
#include <vector>
#include "image.hpp"

struct Point {
    int x, y;
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

bool isWhite(const Image::Color& c) {
    return c.r == 255 && c.g == 255 && c.b == 255;
}

bool isGreen(const Image::Color& c) {
    return c.r == 0 && c.g == 255 && c.b == 0;
}

bool isRed(const Image::Color& c) {
    return c.r == 255 && c.g == 0 && c.b == 0;
}

bool isBlack(const Image::Color& c) {
    return c.r == 0 && c.g == 0 && c.b == 0;
}

bool inBounds(int x, int y, int w, int h) {
    return x >= 0 && x < w && y >= 0 && y < h;
}

void findPath(Image& img) {
    int w = img.getWidth();
    int h = img.getHeight();

    Point start = {-1, -1};
    Point end = {-1, -1};

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            Image::Color c = img.getPixel(x, y);
            if (isGreen(c)) {
                start = {x, y};
            }
            if (isRed(c)) {
                end = {x, y};
            }
        }
    }

    if (start.x == -1 || end.x == -1) {
        return;
    }

    std::vector<std::vector<int>> dist(h, std::vector<int>(w, -1));
    std::vector<std::vector<Point>> prev(h, std::vector<Point>(w, {-1, -1}));

    std::queue<Point> q;
    dist[start.y][start.x] = 0;
    q.push(start);

    int dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1};

    while (!q.empty()) {
        Point cur = q.front();
        q.pop();

        if (cur == end) {
            break;
        }

        for (int i = 0; i < 8; ++i) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];

            if (!inBounds(nx, ny, w, h)) continue;

            Image::Color nc = img.getPixel(nx, ny);
            if (isBlack(nc)) continue;

            if (dist[ny][nx] == -1) {
                dist[ny][nx] = dist[cur.y][cur.x] + 1;
                prev[ny][nx] = cur;
                q.push({nx, ny});
            }
        }
    }

    if (dist[end.y][end.x] == -1) {
        return;
    }

    Point cur = end;
    while (!(cur == start)) {
        if (!(cur == end) && !isGreen(img.getPixel(cur.x, cur.y))) {
            img.setPixel(cur.x, cur.y, Image::Color{0, 0, 255});
        }
        cur = prev[cur.y][cur.x];
    }
}

int main() {
    std::vector<std::string> files = {"asteroids.ppm", "maze.ppm", "spiral.ppm", "strange.ppm"};

    for (const auto& file : files) {
        std::cout << file << "->" << std::endl;

        Image img(file);
        findPath(img);

        std::string output = "path_" + file;
        img.savePPMBinary(output);

        std::cout  << output << std::endl;
    }

    return 0;
}