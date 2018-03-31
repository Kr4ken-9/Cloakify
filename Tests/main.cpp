#include "../src/base64.h"
#include "../src/Cloakify.h"
#include "../src/Shared.h"
//#include "../src/Entropy.h"
#include <iostream>

int main()
{
	std::string Cloaked = Cloak("Noodles", "topWebsites",   FILES::BOTH);
	std::string Uncloaked = Uncloak(Cloaked, "topWebsites", FILES::CIPHER);
	std::cout << Cloaked << std::endl;
	std::cout << Uncloaked << std::endl;

	//std::cout << AddEntropy("Noodles", "Entropy", FILES::NONE, NOISE::SYMBOL);
	std::cin.get();
	return 0;
}
