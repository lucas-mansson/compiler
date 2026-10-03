#include <cstdlib>
#include <fstream>
#include <iostream>
#include <print>
#include <sstream>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Error: Missing source file" << std::endl;
        exit(1);
    }

    char* file_name = argv[1];
    std::ifstream file(file_name);
    if (!file) {
        std::cerr << "Error: Could not open file" << std::endl;
        exit(1);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    std::string source = buffer.str();

    std::println("{}", source);
}
