
#include <iostream>
#include <vector>
#include <stack>

// Función para ejecutar el código Brainfuck
void executeBrainfuck(const std::string& code) {
    std::vector<int> memory(30000, 0);  // Memoria para el programa Brainfuck
    std::stack<size_t> loopStack;  // Pila para almacenar los índices de bucles

    size_t codePointer = 0;  // Puntero de instrucción del código Brainfuck
    size_t memoryPointer = 0;  // Puntero de memoria

    while (codePointer < code.length()) {
        char instruction = code[codePointer];

        switch (instruction) {
            case '>':
                memoryPointer++;
                break;

            case '<':
                memoryPointer--;
                break;

            case '+':
                memory[memoryPointer]++;
                break;

            case '-':
                memory[memoryPointer]--;
                break;

            case '.':
                std::cout << memory[memoryPointer] << " ";
                break;

            case ',':
                char input;
                std::cin >> input;
                memory[memoryPointer] = input;
                break;

            case '[':
                if (memory[memoryPointer] == 0) {
                    int nestingLevel = 1;
                    while (nestingLevel > 0) {
                        codePointer++;
                        if (code[codePointer] == '[')
                            nestingLevel++;
                        else if (code[codePointer] == ']')
                            nestingLevel--;
                    }
                } else {
                    loopStack.push(codePointer);
                }
                break;

            case ']':
                if (memory[memoryPointer] == 0) {
                    loopStack.pop();
                } else {
                    codePointer = loopStack.top() - 1;
                }
                break;
        }

        codePointer++;
    }
}

int main() {
    int inputValue;

    std::cout << "Ingrese un valor entero: ";
    std::cin >> inputValue;

    // Convertir el valor ingresado a código Brainfuck
    std::string brainfuckCode = "";

    for (int i = 0; i < inputValue; i++) {
        brainfuckCode += "+.";
    }

    // Ejecutar el código Brainfuck
    executeBrainfuck(brainfuckCode);

    return 0;
}
