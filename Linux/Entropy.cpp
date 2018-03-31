#include "Entropy.h"
#include "Shared.h"

const std::string Symbols  = "`~!@#$%^&*()-_=+[{]}\\|';/?.>,<";
const std::string Numerals = "0123456789";
const std::string Alphabeticals = "abcedfghijklmnopqrstuvwxyz"
                                  "ABCEDFGHIJKLMNOPQRSTUVWXYZ";

std::string AddEntropy(const std::string &Input, const std::string &Entropy, const FILES Files, const NOISE Noise)
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
    for (const std::string &ILine : ILines)
    {
        if(Noise == NOISE::PREPEND || Noise == NOISE::SUFFIX)
        {
            std::string ONoise = ELines[rand() % ELines.size()];

            if(Noise == NOISE::PREPEND)
                Output += ONoise.append(" ").append(ILine);

            if(Noise == NOISE::SUFFIX)
                Output += ILine + std::string(" ").append(ONoise);
        }

        if(Noise == NOISE::SYMBOL)
        {
            for(int o = 0; o < ILine.length(); o++)
                Output += std::string(1, Symbols[rand() % Symbols.length()]) + ILine[o];

            Output += std::string(1, Symbols[rand() % Symbols.length()]);
        }

        if(Noise == NOISE::ALPHANUMERIC)
        {
            for(int o = 0; o < ILine.length(); o++)
            {
                if(isdigit(ILine[0]))
                    Output += std::string(1, Alphabeticals[rand() % Alphabeticals.length()]) + ILine[o];
                else
                    Output += std::string(1, Numerals[rand() % Numerals.length()]) + ILine[o];
            }

            if(isdigit(ILine[0]))
                Output += std::string(1, Alphabeticals[rand() % Alphabeticals.length()]);
            else
                Output += std::string(1, Numerals[rand() % Numerals.length()]);
        }

        Output += "\n";
    }

    return Output;


}
