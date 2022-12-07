#include <boost/algorithm/string.hpp>
#include <utils.hpp>

constexpr size_t SMOLBOY_SZ = 100'000;
constexpr size_t SYSTEM_SPACE = 70'000'000;
constexpr size_t SPACE_NEEDED = 30'000'000;

struct Dir {
    Dir(std::string _name) : name(_name){};
    std::string name;
    size_t size{0};
    std::vector<Dir> dirs;

    void clear_sz() { size = 0; }
    void add_file(size_t sz) { size += sz; }
    Dir& add_or_get_dir(std::string_view dirname) {
        auto it = std::find_if(dirs.begin(), dirs.end(), [&dirname](auto& dir) {
            return dir.name == dirname;
        });
        if (it == dirs.end()) {
            return dirs.emplace_back(dirname.data());
        }
        return *it;
    }
};

Dir parse_input(std::fstream& in) {
    std::string raw;
    Dir root("/");
    std::stack<Dir*> stack;
    // throw away first line, push the root dir on stack
    std::getline(in, raw);
    stack.push(&root);
    while (in) {
        Dir* cwd = stack.top();
        std::getline(in, raw);
        if (raw.empty()) {
            break;
        }

        std::vector<std::string> tokens;
        boost::split(tokens, raw, boost::is_any_of(" "));
        if (tokens[1] == "ls") {
            assert(tokens.size() == 2);
            // incase we ls the same dir twice, don't duplicate size count
            cwd->clear_sz();
        } else if (tokens[1] == "cd") {
            assert(tokens.size() == 3);
            std::string_view dirname = tokens[2];
            if (dirname == "..") {
                stack.pop();
            } else {
                // changing dirs, we create it if we didn't already see it in ls
                stack.push(&cwd->add_or_get_dir(dirname));
            }
        } else {
            if (tokens[0] == "dir") {
                stack.top()->add_or_get_dir(tokens[1]);
            } else {  // file
                assert(tokens.size() == 2);
                stack.top()->add_file(std::stoul(tokens[0]));
            }
        }
    }
    return root;
}

size_t node_recursive_size(const Dir& node, size_t& smolboy_total,
                           std::vector<size_t>& dir_totals) {
    size_t node_size = node.size;
    for (auto& dir : node.dirs) {
        node_size += node_recursive_size(dir, smolboy_total, dir_totals);
    }
    if (node_size < SMOLBOY_SZ) {
        smolboy_total += node_size;
    }
    dir_totals.emplace_back(node_size);
    return node_size;
}

int part_one(std::string_view filename) {
    std::fstream infile(filename);
    auto root = parse_input(infile);

    // smolboys are directories with size < SMOLBOY_SZ
    size_t total_smolboys{0};
    std::vector<size_t>
        dir_sizes;  // for pt2 - refactoring this out not worth it
    const auto absolute_total =
        node_recursive_size(root, total_smolboys, dir_sizes);
    return total_smolboys;
}

int part_two(std::string_view filename) {
    std::fstream infile(filename);
    auto root = parse_input(infile);

    size_t total_smolboys{0};
    std::vector<size_t> dir_sizes;
    const auto absolute_total =
        node_recursive_size(root, total_smolboys, dir_sizes);

    std::sort(dir_sizes.begin(), dir_sizes.end());
    const size_t space_unused = SYSTEM_SPACE - dir_sizes.back();
    const size_t deletion_required = SPACE_NEEDED - space_unused;

    return *std::lower_bound(dir_sizes.begin(), dir_sizes.end(),
                             deletion_required);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << argc << " Require path to input file as only argument"
                  << std::endl;
    }
    const std::string_view path{argv[1]};
    std::cout << "Filename: " << path << "\n\n";
    std::cout << "Part one: \n" << part_one(path) << "\n\n";
    // short: 95437, long: 1886043
    std::cout << "Part two: \n" << part_two(path) << std::endl;
    // short: 24933642, long: 3842121
}
