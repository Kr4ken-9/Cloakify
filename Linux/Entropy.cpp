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

        if(Noise == NOISE::PREPEND || Noise == NOISE::SUFFIX)
        {
            std::string ONoise = ELines[rand() % ELines.size()];

            if(Noise == NOISE::PREPEND)
                ILines[i] = ONoise + " " + ILine;

            if(Noise == NOISE::SUFFIX)
                ILines[i] = ILine + " " + ONoise;
        }

        Output += ILines[i] + "\n";
    }

    return Output;


}
