#include "../Linux/base64.cpp"
//#include "../Linux/Cloakify.cpp"
#include "../Linux/Shared.cpp"
#include "../Linux/Entropy.cpp"
#include <iostream>

int main()
{
    /*std::string Cloaked = Cloak("Noodles", "topWebsites", FILES::BOTH);
    std::string Uncloaked = Uncloak(Cloaked, "topWebsites", FILES::CIPHER);
    std::cout << Cloaked << std::endl;
    std::cout << Uncloaked << std::endl;*/

    std::cout << AddEntropy("Noodles", "Entropy", FILES::BOTH, NOISE::SUFFIX);
    return 0;
}