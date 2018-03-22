#include "../Linux/base64.cpp"
#include "../Linux/Cloakify.cpp"

int main()
{
    std::cout << Cloak("Noodles", "topWebsites", FILES::BOTH);
    return 0;
}