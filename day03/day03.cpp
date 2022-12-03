#include <utils.hpp>

using string_it = std::string::iterator;

int priority(char item_type) {
    auto base =
        std::isupper(static_cast<unsigned char>(item_type)) ? 'A' - 26 : 'a';
    // -26 is so capitals start at 27
    return item_type - base + 1;
}

std::string find_dupes(std::string left, std::string right) {
    std::string dupes;
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
    std::set_intersection(left.begin(), left.end(), right.begin(), right.end(),
                          std::back_inserter(dupes));
    assert(dupes.size() > 0);
    return dupes;
}

int part_one(const std::string& filename) {
    std::fstream infile(filename);
    std::vector<std::string> inputs;
    cb::parse_stream(infile, inputs);

    auto acc_dupes = [](int acc, std::string& rucksack) {
        auto pivot = rucksack.size() / 2;
        auto dupes = find_dupes(rucksack.substr(0, pivot),
                                rucksack.substr(pivot));
        return acc + priority(dupes.front());
    };

    return std::accumulate(inputs.begin(), inputs.end(), 0, acc_dupes);
}

int part_two(const std::string& filename) {
    std::fstream infile(filename);
    std::vector<std::string> inputs;
    cb::parse_stream(infile, inputs);

    int acc{0};
    for (auto it = inputs.begin(); it != inputs.end(); ++it) {
        auto& first = *it;
        auto& second = *++it;
        auto& third = *++it;

        auto dupes = find_dupes(find_dupes(first, second), third);
        acc += priority(dupes.front());
    }
    return acc;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << argc << " Require path to input file as only argument"
                  << std::endl;
    }
    std::string path{argv[1]};
    std::cout << "Filename: " << path << "\n\n";
    std::cout << "Part one: \n" << part_one(path) << "\n\n";
    // short: 157, long: 7727
    std::cout << "Part two: \n" << part_two(path) << std::endl;
    // short: 70, long: 2609
}
