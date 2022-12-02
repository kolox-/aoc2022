#include <utils.hpp>

using Pair_T = std::pair<char, char>;

constexpr char THEIR_BASE = 'A';
constexpr char OUR_BASE = 'X';

constexpr int WIN_PTS = 6;
constexpr int DRAW_PTS = 3;
constexpr int LOSS_PTS = 0;

constexpr int NUM_CHOICES = 3;

enum class Choice { ROCK, PAPER, SCISSORS };

enum class Outcome { DRAW, WIN, LOSE };

constexpr int rotate(int to_rotate, int steps) {
    // Since the precedence is circular (rock < paper < scissors < rock), we
    // often need to rotate the enum values. In this case there are always three
    // values in both enums so we can hardcode.
    return (to_rotate + steps) % NUM_CHOICES;
};

constexpr bool beats(Choice a, Choice b) {
    // Each choice beats the one behind it (ie. rotate by 2) in our enum
    return rotate(static_cast<int>(a), 2) == static_cast<int>(b);
}

constexpr int score(Choice theirs, Choice ours) {
    // choice bonus starts from 1 and is ordered the same as our enum
    constexpr int base_bonus = 1;
    const int bonus = static_cast<int>(ours) + base_bonus;
    if (beats(ours, theirs)) {
        return WIN_PTS + bonus;
    } else if (beats(theirs, ours)) {
        return LOSS_PTS + bonus;
    } else {
        return DRAW_PTS + bonus;
    }
}

constexpr Outcome outcome_from_char(char input) {
    // The order given is X, Y, Z : LOSE, DRAW, WIN
    // Need to rotate them by +2 to match our Outcomes enum for get_move()
    auto zeroed_outcome = input - OUR_BASE;
    return static_cast<Outcome>(rotate(zeroed_outcome, 2));
}

constexpr Choice get_move(Choice theirs, Outcome outcome) {
    // Outcome enum is ordered such that the value is the Choice rotation needed
    // for that outcome (eg. to WIN (enum val 1), we need to select the next
    // (+1) choice in the Choices enum
    auto result_int =
        rotate(static_cast<int>(theirs), static_cast<int>(outcome));
    return static_cast<Choice>(result_int);
}

int part_one(const std::string& filename) {
    std::fstream infile(filename);
    std::vector<Pair_T> pairs;
    cb::parse_pairs(infile, pairs);

    auto score_outcome = [](int acc, auto& pair) {
        auto theirs = static_cast<Choice>(pair.first - THEIR_BASE);
        auto ours = static_cast<Choice>(pair.second - OUR_BASE);
        return acc + score(theirs, ours);
    };
    return std::accumulate(pairs.begin(), pairs.end(), 0, score_outcome);
}

int part_two(const std::string& filename) {
    std::fstream infile(filename);
    std::vector<Pair_T> pairs;
    cb::parse_pairs(infile, pairs);

    auto score_outcome = [](int acc, auto& pair) {
        auto theirs = static_cast<Choice>(pair.first - THEIR_BASE);
        auto outcome = outcome_from_char(pair.second);
        auto ours = get_move(theirs, outcome);
        return acc + score(theirs, ours);
    };

    return std::accumulate(pairs.begin(), pairs.end(), 0, score_outcome);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << argc << " Require path to input file as only argument"
                  << std::endl;
    }
    std::string path{argv[1]};
    std::cout << "Filename: " << path << "\n\n";
    std::cout << "Part one: \n" << part_one(path) << "\n\n";
    // short: 15, long: 8392
    std::cout << "Part two: \n" << part_two(path) << std::endl;
    // short: 12, long: 10116
}
