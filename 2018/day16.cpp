
#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>
#include <tuple>
#include <vector>
#include <map>

/*
Addition:

    addr (add register) stores into register C the result of adding register A and register B.
    addi (add immediate) stores into register C the result of adding register A and value B.
    */

int registers[4];

void addr(int rA, int rB, int rC) { registers[rC] = registers[rA] + registers[rB]; }
void addi(int rA, int B, int rC) { registers[rC] = registers[rA] + B; }
#if 0
Multiplication:

    mulr (multiply register) stores into register C the result of multiplying register A and register B.
    muli (multiply immediate) stores into register C the result of multiplying register A and value B.
#endif

void mulr(int rA, int rB, int rC) { registers[rC] = registers[rA] * registers[rB]; }
void muli(int rA, int B, int rC) { registers[rC] = registers[rA] * B; }

#if 0
Bitwise AND:

    banr (bitwise AND register) stores into register C the result of the bitwise AND of register A and register B.
    bani (bitwise AND immediate) stores into register C the result of the bitwise AND of register A and value B.

#endif
void banr(int rA, int rB, int rC) { registers[rC] = registers[rA] & registers[rB]; }
void bani(int rA, int B, int rC) { registers[rC] = registers[rA] & B; }

#if 0
Bitwise OR:

    borr (bitwise OR register) stores into register C the result of the bitwise OR of register A and register B.
    bori (bitwise OR immediate) stores into register C the result of the bitwise OR of register A and value B.

#endif
void borr(int rA, int rB, int rC) { registers[rC] = registers[rA] | registers[rB]; }
void bori(int rA, int B, int rC) { registers[rC] = registers[rA] | B; }

#if 0
Assignment:

    setr (set register) copies the contents of register A into register C. (Input B is ignored.)
    seti (set immediate) stores value A into register C. (Input B is ignored.)
#endif
void setr(int rA, int /*rB*/, int rC) { registers[rC] = registers[rA]; }
void seti(int rA, int /*B*/, int rC) { registers[rC] = rA; }


#if 0
Greater-than testing:

    gtir (greater-than immediate/register) sets register C to 1 if value A is greater than register B. Otherwise, register C is set to 0.
    gtri (greater-than register/immediate) sets register C to 1 if register A is greater than value B. Otherwise, register C is set to 0.
    gtrr (greater-than register/register) sets register C to 1 if register A is greater than register B. Otherwise, register C is set to 0.

#endif
void gtir(int A, int rB, int rC) { registers[rC] = A > registers[rB]; }
void gtri(int rA, int B, int rC) { registers[rC] = registers[rA] > B; }
void gtrr(int rA, int rB, int rC) { registers[rC] = registers[rA] > registers[rB]; }

#if 0
Equality testing:

    eqir (equal immediate/register) sets register C to 1 if value A is equal to register B. Otherwise, register C is set to 0.
    eqri (equal register/immediate) sets register C to 1 if register A is equal to value B. Otherwise, register C is set to 0.
    eqrr (equal register/register) sets register C to 1 if register A is equal to register B. Otherwise, register C is set to 0.

#endif

void eqir(int rA, int rB, int rC) { registers[rC] = rA == registers[rB]; }
void eqri(int rA, int B, int rC) { registers[rC] = registers[rA] == B; }
void eqrr(int rA, int rB, int rC) { registers[rC] = registers[rA] == registers[rB]; }


using RegsVal = std::tuple<int, int, int, int>;
using Instr = std::tuple<int, int, int, int>;

RegsVal getRegsVal(const std::string &s) {
    std::stringstream ss;

    for (auto &c : s.substr(1, s.size() - 2))
        if (c != ',')
            ss << c;
    int a, b, c, d;
    ss >> a >> b >> c >> d;
    return std::make_tuple(a, b, c, d);
}

Instr getInstr(const std::string &s) {
    std::stringstream ss;
    ss << s;
    int a, b, c, d;
    ss >> a >> b >> c >> d;
    return std::make_tuple(a, b, c, d);
}

using F = void(*)(int rA, int rB, int rC);

static std::vector<std::pair<int, F>> instr_set = {
    { 0xFF, addr },
    { 0xFF, addi },
    { 0xFF, mulr },
    { 0xFF, muli },
    { 0xFF, banr },
    { 0xFF, bani },
    { 0xFF, borr },
    { 0xFF, bori },
    { 0xFF, setr },
    { 0xFF, seti },
    { 0xFF, gtir },
    { 0xFF, gtri },
    { 0xFF, gtrr },
    { 0xFF, eqir },
    { 0xFF, eqri },
    { 0xFF, eqrr }
};

bool checkOne(F f, const RegsVal &before, const Instr &instr, const RegsVal &after) {
    auto regs = std::tie(registers[0], registers[1], registers[2], registers[3]);
    regs = before;
    int a, b, c;
    std::tie(std::ignore, a, b, c) = instr;
    f(a, b, c);
    return regs == after;
}

size_t check(const RegsVal &before, const Instr &instr, const RegsVal &after) {

    size_t count = 0;
    for (auto &f : instr_set) {
        if (checkOne(f.second, before, instr, after))
            count++;
    }
    return count;
}

void workout(const std::vector<std::tuple<RegsVal, Instr, RegsVal>> &inputs) {
    size_t guessed = 0;
    while (guessed != instr_set.size()) {
        for (auto &e : inputs) {
            RegsVal before, after;
            Instr instr;
            std::tie(before, instr, after) = e;
            size_t count = 0;
            for (auto &f : instr_set) {
                if (f.first == 0xFF) {
                    if (checkOne(f.second, before, instr, after))
                        count++;
                }
            }
            if (count == 1) {
                for (auto &f : instr_set) {
                    if (f.first == 0xFF) {
                        if (checkOne(f.second, before, instr, after)) {
                            f.first = std::get<0>(instr);
                            guessed++;
                        }
                    }
                }
            }
        }
    }
}

int main() {
    std::string line1, line2, line3, line4;

    std::vector<std::tuple<RegsVal, Instr, RegsVal>> inputs;
    do {
        getline(std::cin, line1);
        if (line1.empty())
            break;

        getline(std::cin, line2);
        getline(std::cin, line3);
        getline(std::cin, line4);

        auto before = getRegsVal(line1.substr(8, std::string::npos));
        auto instr = getInstr(line2);
        auto after = getRegsVal(line3.substr(8, std::string::npos));

        if (!line4.empty())
            std::cout << "Something went wrong..." << std::endl;
        
        inputs.emplace_back(std::make_tuple(before, instr, after));
    } while (true);

    size_t count = 0;
    for (auto &e : inputs) {
        RegsVal before, after;
        Instr instr;
        std::tie(before, instr, after) = e;
        auto c = check(before, instr, after);
        if (c >= 3)
            count++;
    }

    std::vector<Instr> program;
    while (getline(std::cin, line1)) {

        if (line1.empty())
            continue;

        program.emplace_back(getInstr(line1));
    }

    std::cout << "Part 1: " << count << std::endl;

    workout(inputs);

    std::sort(instr_set.begin(), instr_set.end());

    /* Registers starts with the value of 0 */
    for (auto &r : registers)
        r = 0;

    for (const auto &i : program) {
        int op, a, b, c;
        std::tie(op, a, b, c) = i;
        auto f = instr_set[op].second;
        f(a, b, c);
    }

    std::cout << "Part2: " << registers[0] << std::endl;
}
