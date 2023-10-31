#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <cctype> // Added for isdigit function

typedef std::vector<std::string> Tokens;

Tokens tokenize(const std::string& input) {
    Tokens tokens;
    std::string token;
    std::istringstream stream(input);

    while (stream >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

int evaluate(Tokens& tokens) {
    std::stack<int> stack;

    while (!tokens.empty()) {
        std::string token = tokens.back();
        tokens.pop_back();

        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && isdigit(token[1]))) {
            stack.push(std::stoi(token));
        } else if (token == "+") {
            int result = 0;
            while (!stack.empty()) {
                result += stack.top();
                stack.pop();
            }
            stack.push(result);
        } else if (token == "-") {
            int b = stack.top();
            stack.pop();
            int a = stack.top();
            stack.pop();
            stack.push(a - b);
        } else if (token == "*") {
            int result = 1;
            while (!stack.empty()) {
                result *= stack.top();
                stack.pop();
            }
            stack.push(result);
        } else if (token == "/") {
            int b = stack.top();
            stack.pop();
            int a = stack.top();
            stack.pop();
            if (b == 0) {
                std::cerr << "Error: Dividido entre cero" << std::endl;
                return 0;
            }
            stack.push(a / b);
        } else if (token == "raiz") {
            int a = stack.top();
            stack.pop();
            if (a < 0) {
                std::cerr << "Error: no existen raices de numeros negativos" << std::endl;
            }
            stack.push(a * );
        } else {
            std::cerr << "Error: Token invalido " << token << std::endl;
            return 0;
        }
    }

    if (stack.size() != 1) {
        std::cerr << "Error: Incomplete expression" << std::endl;
        return 0;
    }

    return stack.top();
}

int main() {
    std::string input;
    std::getline(std::cin, input);
    Tokens tokens = tokenize(input);
    int result = evaluate(tokens);

    if (result != 0) {
        std::cout << "Result: " << result << std::endl;
    }

    return result;
}