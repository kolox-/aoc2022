#include <utils.hpp>

std::vector<int> get_elves_totals(std::fstream& infile) {
    std::vector<int> totals;
    while (infile) {
        auto vec = cb::parse_stream_ints_until_newline(infile);
        totals.push_back(std::accumulate(vec.begin(), vec.end(), 0));
    }
    return totals;
}

int part_one(const std::string& filename) {
    std::fstream infile(filename);
    auto totals = get_elves_totals(infile);
    return *std::max_element(totals.begin(), totals.end());
}

int part_two(const std::string& filename) {
    std::fstream infile(filename);
    auto totals = get_elves_totals(infile);
    if (totals.size() < 3) {
        return -1;
    }
    // can just use a prio queue & iter to avoid the sort but i'm lazy
    std::partial_sort(totals.begin(), totals.begin() + 3, totals.end(),
                      std::greater<>());
    return std::accumulate(totals.begin(), totals.begin() + 3, 0);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << argc << " Require path to input file as only argument"
                  << std::endl;
    }
    std::string path{argv[1]};
    std::cout << "Filename: " << path << "\n\n";
    std::cout << "Part one: \n" << part_one(path) << "\n\n";
    // short: 24000, long: 69693
    std::cout << "Part two: \n" << part_two(path) << std::endl;
    // short: 45000, long: 200945
}
