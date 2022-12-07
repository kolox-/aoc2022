#include <bit>
#include <utils.hpp>

size_t index(unsigned char ch) { return ch - 'a'; }

bool has_dupes(std::string_view::const_iterator left,
               std::string_view::const_iterator right) {
    auto window_size = std::distance(left, right);
    uint64_t mask = 0;
    for (; left != right; ++left) {
        mask |= 1UL << index(*left);
    }
    return std::popcount(mask) != window_size;
}

size_t index_of_dupe(std::string_view str, size_t window_size) {
    for (auto left = str.begin(), right = left + window_size;
         right != str.end(); ++left, ++right) {
        if (!has_dupes(left, right)) {
            return std::distance(str.begin(), right);
        }
    }
    return -1;
}

int part_one(std::string_view filename) {
    std::fstream infile(filename);
    std::string in;
    std::getline(infile, in);
    return index_of_dupe(in, 4);
}

int part_two(std::string_view filename) {
    std::fstream infile(filename);
    std::string in;
    std::getline(infile, in);
    return index_of_dupe(in, 14);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << argc << " Require path to input file as only argument"
                  << std::endl;
    }
    const std::string_view path{argv[1]};
    std::cout << "Filename: " << path << "\n\n";
    std::cout << "Part one: \n" << part_one(path) << "\n\n";
    // short: , long: 1892
    std::cout << "Part two: \n" << part_two(path) << std::endl;
    // short: , long: 2313
}
