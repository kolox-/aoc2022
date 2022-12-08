#include <utils.hpp>

int part_one(std::string_view filename) {
    std::fstream infile(filename);

    return -1;
}

int part_two(std::string_view filename) {
    std::fstream infile(filename);

    return -1;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << argc << " Require path to input file as only argument"
                  << std::endl;
    }
    const std::string_view path{argv[1]};
    std::cout << "Filename: " << path << "\n\n";
    std::cout << "Part one: \n" << part_one(path) << "\n\n";
    // short: , long: 
    std::cout << "Part two: \n" << part_two(path) << std::endl;
    // short: , long: 

}
