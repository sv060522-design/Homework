#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

std::vector<std::vector<std::size_t>> calculate_word_lengths(const std::string& filename) {
    std::vector<std::vector<std::size_t>> result;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return result;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::size_t> line_lengths;
        std::istringstream iss(line);  // Я уже до этого изучал C++, поэтому использую здесь поток, так как мне кажется
                                       // это наиболлее просто и удобно
        std::string word;

        while (iss >> word) {
            line_lengths.push_back(word.length());
        }

        result.push_back(line_lengths);
    }

    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    auto result = calculate_word_lengths(filename);

    std::cout << "{";
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << "{";
        for (size_t j = 0; j < result[i].size(); ++j) {
            std::cout << result[i][j];
            if (j < result[i].size() - 1) std::cout << ", ";
        }
        std::cout << "}";
        if (i < result.size() - 1) std::cout << ", ";
    }
    std::cout << "}" << std::endl;

    return 0;
}