#include "../Linux/base64.cpp"
#include "../Linux/Cloakify.cpp"
#include <iostream>

int main()
{
    std::cout << FileToString("Makefile");
    return 0;
}