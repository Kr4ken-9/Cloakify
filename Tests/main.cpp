#include "../src/base64.h"
//#include "../src/Cloakify.h"
#include "../src/Shared.cpp"
#include "../src/Entropy.cpp"
#include <iostream>

int main()
{
	/*std::string Cloaked = Cloak("Noodles", "topWebsites",   FILES::BOTH);
	std::string Uncloaked = Uncloak(Cloaked, "topWebsites", FILES::CIPHER);
	std::cout << Cloaked << std::endl;
	std::cout << Uncloaked << std::endl;*/

	std::string Entropy = AddEntropy("Noodles", "topWebsites", FILES::BOTH, NOISE::FAF);
	//std::string DeEntropy = RemoveEntropy(Entropy, FILES::NONE, NOISE::ALPHANUMERIC);

	std::cout << Entropy /*<< std::endl << DeEntropy << std::endl*/;
	//std::cin.get();
	return 0;
}
