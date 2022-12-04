#include <utils.hpp>

const std::regex re("^(\\d+)-(\\d+),(\\d+)-(\\d+)$");

struct Assignment {
    int begin;
    int end;
};

using ElfPair = std::pair<Assignment, Assignment>;

constexpr bool subset(Assignment a, Assignment b) {
    return ((b.begin >= a.begin && b.end <= a.end) ||
            (a.begin >= b.begin && a.end <= b.end));
}

constexpr bool disjoint(Assignment a, Assignment b) {
    return (a.begin > b.end || a.end < b.begin);
}

auto parse(std::fstream& in) {
    std::vector<ElfPair> out;
    std::string raw;
    std::smatch match;
    while (getline(in, raw)) {
        std::regex_match(raw, match, re);
        assert(match.ready());
        assert(match.size() == 5);
        out.push_back({{std::stoi(match[1]), std::stoi(match[2])},
                       {std::stoi(match[3]), std::stoi(match[4])}});
    }
    return out;
}

int part_one(std::string_view filename) {
    std::fstream infile(filename);
    auto inputs = parse(infile);

    return std::count_if(inputs.begin(), inputs.end(), [](auto& pair) {
        return subset(pair.first, pair.second);
    });
}

int part_two(std::string_view filename) {
    std::fstream infile(filename);
    auto inputs = parse(infile);

    return std::count_if(inputs.begin(), inputs.end(), [](auto& pair) {
        return !disjoint(pair.first, pair.second);
    });
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << argc << " Require path to input file as only argument"
                  << std::endl;
    }
    const std::string_view path{argv[1]};
    std::cout << "Filename: " << path << "\n\n";
    std::cout << "Part one: \n" << part_one(path) << "\n\n";
    // short: 2, long: 562
    std::cout << "Part two: \n" << part_two(path) << std::endl;
    // short: 4, long: 924
}
