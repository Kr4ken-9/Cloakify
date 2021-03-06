#include "Entropy.h"


const std::string Symbols  = "`~!@#$%^&*()-_=+[{]}\\|';/?.>,<";
const std::string Numerals = "0123456789";
const std::string Alphabeticals = "abcedfghijklmnopqrstuvwxyz"
                                  "ABCEDFGHIJKLMNOPQRSTUVWXYZ";

std::string RemoveEntropy(const std::string &Input, const FILES Files, const NOISE Noise, const char &Separator)
{
    std::string UsableInput = Input;

    if(Files == FILES::BOTH || Files == FILES::INPUT)
        UsableInput = FileToString(UsableInput);

    std::vector<std::string> Lines = split(UsableInput, Separator);
    std::string Output;

    if(Noise == NOISE::AFAF)
    {
        for (int i = 0; i < Lines.size(); i++)
        {
            std::vector <std::string> Parts = split(Lines[i], ' ');

            bool Prefix = true;

            if ((i + 1) % 3 == 0)
                Prefix = !Prefix;

            if (Prefix)
                Output += Parts[1];
            else
                Output += Parts[0];

            Output += Separator;
        }

        return Output;
    }

    for(const std::string &Line : Lines)
    {
        if(Noise == NOISE::PREPEND || Noise == NOISE::SUFFIX)
        {
            std::vector<std::string> Parts = split(Line, ' ');

            if(Noise == NOISE::PREPEND)
                Output += Parts[1];

            if(Noise == NOISE::SUFFIX)
                Output += Parts[0];
        }

        if(Noise == NOISE::ALPHANUMERIC || Noise == NOISE::SYMBOL)
        {
            for(int i = 0; i < Line.size(); i++)
            {
                if(i == 0)
                    continue;

                Output += Line[i];
                i++;
            }
        }

        Output += Separator;
    }

    return Output;
}

std::string AddEntropy(const std::string &Input, const std::string &Entropy, const FILES Files, const NOISE Noise, const char &Separator)
{
    std::string UsableInput = Input;

    if(Files == FILES::BOTH || Files == FILES::INPUT)
        UsableInput = FileToString(UsableInput);

    std::string UsableEntropy = Entropy;

    if(Files == FILES::BOTH || Files == FILES::ENTROPY)
        UsableEntropy = FileToString(UsableEntropy);

    std::vector<std::string> ILines = split(UsableInput, Separator);
    std::vector<std::string> ELines = split(UsableEntropy, '\n');
    std::string Output;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wsign-conversion"
    srand((int)time(0));
#pragma clang diagnostic pop

    if(Noise == NOISE::AFAF)
    {
        std::vector<std::string> RandFreq = nullptr;

        for(int i = 0; i < 5; i++)
            RandFreq.push_back(ELines[rand() % ELines.size()]);

        for(int o = 0; o < ILines.size(); o++)
        {
            std::string ILine = ILines[o];
            std::string ELine = RandFreq[rand() % RandFreq.size()];
            bool Prefix = true;

            if((o + 1) % 3 == 0)
                Prefix = !Prefix;

            if(Prefix)
                Output += ELine.append(" ").append(ILine);
            else
                Output += ILine + std::string(" ").append(ELine);

            Output += Separator;
        }

        return Output;
    }

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

        Output += Separator;
    }

    return Output;


}
