#include "../Linux/base64.cpp"
#include "../Linux/Cloakify.cpp"

int main()
{
    std::string Cloaked = Cloak("Noodles", "topWebsites", FILES::BOTH);
    std::string Uncloaked = Uncloak(Cloaked, "topWebsites", FILES::CIPHER);
    std::cout << Cloaked << std::endl;
    std::cout << Uncloaked << std::endl;
    return 0;
}