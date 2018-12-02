
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <set>

struct Data {
    std::string reg, op, val, ifstr, reg2, test, valtest;
};


int main() {
    std::set<std::string> registers;
    std::vector<Data> program;
    for (std::string linestr; std::getline(std::cin, linestr);) {
        if (linestr.empty())
            break;

        std::istringstream ss(linestr);

        //ojk inc 36 if dtf > 138
        Data data;

        ss >> data.reg >> data.op >> data.val >> data.ifstr >> data.reg2 >> data.test >> data.valtest;

        data.reg += "__"; // prevent conflicts with registers named 'if' or 'for'
        data.reg2 += "__"; // prevent conflicts with registers named 'if' or 'for'

        registers.insert(data.reg);
        program.push_back(data);
    }

    std::cout << "#include <algorithm>\n";
    std::cout << "#include <iostream>\n";
    std::cout << "#include <vector>\n";

    std::cout << "int main() {\n"
              << "std::vector<int> reg_values;\n";

    for (auto reg : registers)
        std::cout << "int " << reg << " = 0;\n";

    for (auto line : program) {
        std::cout << line.ifstr << " (" << line.reg2 << " " << line.test << " " << line.valtest << ") {\n"
                  << "    " << line.reg << (line.op == "inc" ? " += " : " -= ") << line.val << ";\n"
                  << "}\n";
    }
    for (auto reg : registers)
        std::cout << "reg_values.push_back(" << reg << ");\n";

    std::cout << "std::cout << *std::max_element(reg_values.begin(), reg_values.end()) << std::endl;" << std::endl;
    std::cout << "}\n";
}
