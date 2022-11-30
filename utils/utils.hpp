#include <string>
#include <vector>
#include <iostream>
#include <fstream>

namespace cb{

template <typename T>
void parse_stream(std::istream& s, std::vector<T>& out) {
    T var;
    while (s >> var) {
        out.push_back(var);
    }
}

template <typename T>
void print(const std::vector<T>& vec) {
    for (const auto& v : vec) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
}

} // namespace cb
