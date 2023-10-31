// tiny_lisp.cpp
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <functional>

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

        if (token == "+") {
            int a = stack.top();
            stack.pop();
            int b = stack.top();
            stack.pop();
            stack.push(a + b);
        } else if (token == "-") {

            int a = stack.top();
            stack.pop();
            int b = stack.top();
            stack.pop();
            stack.push(b - a);
        }else if (token == "*") {

            int a = stack.top();
            stack.pop();
            int b = stack.top();
            stack.pop();
            stack.push(a * b);
        }else if (token == "/") {

            int a = stack.top();
            stack.pop();
            int b = stack.top();
            stack.pop();
            if (a == 0) {
                throw std::runtime_error("División por cero.");
            }
            stack.push(b / a);
        } else if (token == "potencia") {
            if (stack.size() < 2) {
                throw std::runtime_error("La potencia necesita dos argumentos");
            }
            int exp = stack.top();
            stack.pop();
            int base = stack.top();
            stack.pop();
            stack.push(std::pow(base, exp));
        }else if (token == "raiz") {
                if (stack.size() < 1) {
                    throw std::runtime_error("La raiz necesita al menos un argumento.");
                }
                int val = stack.top();
                stack.pop();
                stack.push(std::sqrt(val));
            }else {
            stack.push(std::stoi(token));
        }
    }
    if (stack.size() != 1) {
        throw std::runtime_error("Expresión mal formada.");
    }

    return stack.top();
}
bool isOperator(const std::string& token) {
    return token == "+" || token == "*" || token == "-" || token == "/";
}

int main() {
    while (true) {
        std::string input;
        std::cout << "Ingrese una expresion: ";
        std::getline(std::cin, input);

        if (input == "exit") {
            break;
        }
        try {
            Tokens tokens = tokenize(input);
            int result = evaluate(tokens);
            std::cout << "Resultado: " << result << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}
