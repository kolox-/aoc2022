#include <utils.hpp>

const std::regex re("^move (\\d+) from (\\d+) to (\\d+)$");

using ElfStacks = std::vector<std::stack<char> >;

struct Instruction {
    int repetitions;
    int from;
    int to;
};

ElfStacks parse_stacks(std::fstream& in) {
    std::vector<std::string> raw_inputs;
    std::string tmp;
    // parse down to the empty line to get the stacks
    while (getline(in, tmp)) {
        if (tmp.empty()) {
            break;
        }
        raw_inputs.emplace_back(std::move(tmp));
    }

    // contents of each box start at i=1 and then occur every 4
    std::vector<int> stack_indexes;
    for (int i = 1; i < raw_inputs.front().size(); i += 4) {
        stack_indexes.push_back(i);
    }

    raw_inputs.pop_back();

    // Build each stack using the indexes we just calculated, from bottom up
    ElfStacks stacks(stack_indexes.size());
    std::reverse(raw_inputs.begin(), raw_inputs.end());

    for (size_t i = 0; i != stack_indexes.size(); ++i) {
        auto index = stack_indexes[i];
        for (const auto& str : raw_inputs) {
            unsigned char ch = str[index];
            if (!std::isspace(ch)) {
                stacks[i].push(ch);
            }
        }
    }
    return stacks;
}

int to_index(const std::string& s) {
    // the instruction indexes start from 1, we need to bring to 0
    return std::stoi(s) - 1;
}

std::vector<Instruction> parse_instructions(std::fstream& infile) {
    std::vector<Instruction> out;
    std::string raw;
    std::smatch match;
    while (getline(infile, raw)) {
        std::regex_match(raw, match, re);
        assert(match.ready());
        assert(match.size() == 4);
        out.push_back(
            {std::stoi(match[1]), to_index(match[2]), to_index(match[3])});
    }
    return out;
}

void move(ElfStacks& stacks, Instruction ins) {
    auto& from = stacks[ins.from];
    auto& to = stacks[ins.to];
    for (int i = 0; i != ins.repetitions; ++i) {
        auto tmp = from.top();
        from.pop();
        to.push(tmp);
    }
}

std::string part_one(std::string_view filename) {
    std::fstream infile(filename);
    auto stacks = parse_stacks(infile);
    auto instr = parse_instructions(infile);

    for (auto& ins : instr) {
        move(stacks, ins);
    }

    std::string out;
    for (const auto& stack : stacks) {
        out.push_back(stack.top());
    }

    return out;
}

void move_maintain_order(ElfStacks& stacks, Instruction ins) {
    auto& from = stacks[ins.from];
    auto& to = stacks[ins.to];
    std::stack<int> tmp;
    for (int i = 0; i != ins.repetitions; ++i) {
        tmp.push(from.top());
        from.pop();
    }
    while (!tmp.empty()) {
        to.push(tmp.top());
        tmp.pop();
    }
}

std::string part_two(std::string_view filename) {
    std::fstream infile(filename);
    auto stacks = parse_stacks(infile);
    auto instr = parse_instructions(infile);

    for (auto& ins : instr) {
        move_maintain_order(stacks, ins);
    }

    std::string out;
    for (const auto& stack : stacks) {
        out.push_back(stack.top());
    }

    return out;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << argc << " Require path to input file as only argument"
                  << std::endl;
    }
    const std::string_view path{argv[1]};
    std::cout << "Filename: " << path << "\n\n";
    std::cout << "Part one: \n" << part_one(path) << "\n\n";
    // short: CMZ, long: TLFGBZHCN
    std::cout << "Part two: \n" << part_two(path) << std::endl;
    // short: MCD, long: QRQFHFWCL
}
