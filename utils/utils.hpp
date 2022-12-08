#pragma once

#include <algorithm>
#include <boost/functional/hash.hpp>
#include <cassert>
#include <fstream>
#include <iostream>
#include <numeric>
#include <regex>
#include <string>
#include <string_view>
#include <tuple>
#include <vector>

namespace cb {

template <typename T>
void parse_stream(std::istream& s, std::vector<T>& out) {
    T var;
    while (s >> var) {
        out.push_back(var);
        // std::cout << var << std::endl;
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

struct Point {
    Point(int x, int y) : x(x), y(y) {}
    int x{0};
    int y{0};

    bool operator==(Point const& other) const {
        return x == other.x && y == other.y;
    }
};

}  // namespace cb

namespace std {
template <>
struct hash<cb::Point> {
    std::size_t operator()(const cb::Point& p) const {
        size_t seed = 0;
        boost::hash_combine(seed, p.x);
        boost::hash_combine(seed, p.y);
        return seed;
    }
};
}  // namespace std
