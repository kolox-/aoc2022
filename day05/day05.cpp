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
    while (getline(in, tmp)) {
        if (tmp.empty()) {
            break;
        }
        raw_inputs.emplace_back(std::move(tmp));
    }

    // Get the indexes of the char for each stack in the strings
    std::string_view stack_ids = raw_inputs.back();
    std::vector<int> stack_indexes;

    for (auto it = stack_ids.begin();; ++it) {
        it = std::find_if(it, stack_ids.end(),
                          [](unsigned char ch) { return !std::isspace(ch); });
        if (it == stack_ids.end()) {
            break;
        }
        stack_indexes.push_back(std::distance(stack_ids.begin(), it));
    }
    raw_inputs.pop_back();
    std::reverse(raw_inputs.begin(), raw_inputs.end());

    ElfStacks stacks(stack_indexes.size());

    // Build each stack using the index we just calculated
    for (size_t i = 0; i != stack_indexes.size(); ++i) {
        auto index = stack_indexes[i];
        for (const auto& str : raw_inputs) {
            unsigned char ch = str[index];
            if (!std::isspace(ch)) {
                stacks[i].push(ch);
                // std::cout << "Pushed " << ch << " to " << i << std::endl;
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
