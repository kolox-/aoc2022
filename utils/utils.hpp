#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

namespace cb {

template <typename T>
void parse_stream(std::istream& s, std::vector<T>& out) {
    T var;
    while (s >> var) {
        out.push_back(var);
        std::cout << var << std::endl;
    }
}

template <typename T1, typename T2>
void parse_pairs(std::istream& s, std::vector<std::pair<T1, T2> >& out) {
    T1 a;
    T2 b;
    while (s >> a >> b) {
        // std::cout << a << "," << b << std::endl;
        out.emplace_back(a, b);
    }
}

inline std::vector<int> parse_stream_ints_until_newline(std::istream& s) {
    std::vector<int> out;
    std::string raw;
    while (std::getline(s, raw)) {
        if (raw.empty()) {
            return out;
        }
        // std::cout << raw << std::endl;
        out.push_back(std::stoi(raw));
    }
    return out;
}

template <typename T>
void print(const std::vector<T>& vec) {
    for (const auto& v : vec) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
}

}  // namespace cb
