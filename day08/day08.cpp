#include <utils.hpp>

using namespace std::chrono;

using Grid = std::vector<std::vector<int>>;
using Results = std::unordered_set<cb::Point>;

Grid parse_input(std::fstream& in) {
    Grid grid;
    std::string raw;
    while (in) {
        std::vector<int> row;
        std::getline(in, raw);
        if (raw.empty()) {
            break;
        }
        for (const auto& ch : raw) {
            row.push_back(ch - '0');
        }
        grid.push_back(std::move(row));
    }
    return grid;
}

Results height_check(const Grid& grid) {
    Results res;

    auto comp_and_update = [&grid, &res](auto& biggest, auto i, auto j) {
        if (grid[i][j] > biggest) {
            biggest = grid[i][j];
            res.emplace(i, j);
        }
    };

    for (int i = 0; i < grid.size(); ++i) {
        int biggest = -1;
        for (int j = 0; j < grid.size(); ++j) {
            comp_and_update(biggest, i, j);
        }
        biggest = -1;
        for (int j = grid.size() - 1; j >= 0; --j) {
            comp_and_update(biggest, i, j);
        }
    }

    for (int j = 0; j < grid.size(); ++j) {
        int biggest = -1;
        for (int i = 0; i < grid.size(); ++i) {
            comp_and_update(biggest, i, j);
        }
        biggest = -1;
        for (int i = grid.size() - 1; i >= 0; --i) {
            comp_and_update(biggest, i, j);
        }
    }
    return res;
}

int score(int a, int b, int c, int d) { return a * b * c * d; }

int score_tree(const Grid& grid, int y, int x) {
    const size_t grid_sz = grid.size();
    if (y == 0 || x == 0 || y == grid_sz - 1 || x == grid_sz - 1) {
        // multiplication will give 0 anyway
        return 0;
    }
    // now we're guaranteed to not be on the edge

    const int height = grid[y][x];

    int east_count = 0;
    for (int j = x + 1; j < grid_sz; ++j) {
        ++east_count;
        if (grid[y][j] >= height) {
            // hit another tree
            break;
        }
    }

    int west_count = 0;
    for (int j = x - 1; j >= 0; --j) {
        ++west_count;
        if (grid[y][j] >= height) {
            // hit another tree
            break;
        }
    }

    int south_count = 0;
    for (int i = y + 1; i < grid_sz; ++i) {
        ++south_count;
        if (grid[i][x] >= height) {
            // hit another tree
            break;
        }
    }

    int north_count = 0;
    for (int i = y - 1; i >= 0; --i) {
        ++north_count;
        if (grid[i][x] >= height) {
            // hit another tree
            break;
        }
    }
    return score(west_count, east_count, north_count, south_count);
}

int best_viewpoint(const Grid& grid) {
    int best_score_so_far{0};
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid.size(); ++j) {
            int score = score_tree(grid, i, j);
            best_score_so_far =
                score > best_score_so_far ? score : best_score_so_far;
        }
    }
    return best_score_so_far;
}

int part_one(std::string_view filename) {
    std::fstream infile(filename);
    auto grid = parse_input(infile);
    auto start = high_resolution_clock::now();

    Results results = height_check(grid);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "time taken: " << duration.count() << " us" << std::endl;
    return results.size();
}

int part_two(std::string_view filename) {
    std::fstream infile(filename);
    auto grid = parse_input(infile);
    auto start = high_resolution_clock::now();

    auto res = best_viewpoint(grid);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "time taken: " << duration.count() << " us" << std::endl;
    return res;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << argc << " Require path to input file as only argument"
                  << std::endl;
    }
    const std::string_view path{argv[1]};
    std::cout << "Filename: " << path << "\n\n";
    std::cout << "Part one: \n" << part_one(path) << "\n\n";
    // short: 21, long: 1703
    std::cout << "Part two: \n" << part_two(path) << std::endl;
    // short: 8, long: 496650
}
