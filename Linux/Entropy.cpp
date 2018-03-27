#include "Entropy.h"
#include "Shared.h"

std::string AddEntropy(const std::string Input, const std::string Entropy, const FILES Files, const NOISE Noise)
{
    std::string UsableInput = Input;

    if(Files == FILES::BOTH || Files == FILES::INPUT)
        UsableInput = FileToString(UsableInput);

    std::string UsableEntropy = Entropy;

    if(Files == FILES::BOTH || Files == FILES::ENTROPY)
        UsableEntropy = FileToString(UsableEntropy);

    std::vector<std::string> ILines = split(UsableInput, '\n');
    std::vector<std::string> ELines = split(UsableEntropy, '\n');
    std::string Output;

    srand((int)time(0));
    for(int i = 0; i < ILines.size(); i++)
    {
        std::string ILine = ILines[i];

        if(Noise == NOISE::PREPEND)
        {
            std::string Noise = ELines[rand() % ELines.size()];

            ILines[i] = Noise + " " + ILine;
        }

        Output += ILines[i] + "\n";
    }

    return Output;


}
