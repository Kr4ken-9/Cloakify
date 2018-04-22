#include "Cloakify.h"

const std::string _base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/=";

std::string Uncloak(const std::string &Input, const std::string &Cipher, const FILES Files, const char &Separator)
{
    std::vector<std::string> InputCiphered;
    std::vector<std::string> Ciphers;

    if(Files == FILES::BOTH || Files == FILES::CIPHER)
        Ciphers = split(FileToString(Cipher), '\n');
    else
        Ciphers = split(Cipher, '\n');

    if(Files == FILES::BOTH || Files == FILES::INPUT)
        InputCiphered = split(FileToString(Input), Separator);
    else
        InputCiphered = split(Input, Separator);

    std::string Output64;

    for (const std::string &CString : InputCiphered)
    {
        std::ptrdiff_t pos = std::distance(Ciphers.begin(), std::find(Ciphers.begin(), Ciphers.end(), CString));

        if(pos == 65)
        {
            Output64 += "==";
            return Encoding::Base64::Decode(Output64);
        }

        Output64 += _base64_chars[pos];
    }

    return Encoding::Base64::Decode(Output64);
}

std::string Cloak(const std::string &Input, std::string Cipher, const FILES Files, const char &Separator)
{
    std::string Input64;

    if(Files == FILES::BOTH || Files == FILES::INPUT)
        Input64 = Encoding::Base64::Encode(FileToString(Input));
    else
        Input64 = Encoding::Base64::Encode(Input);

    if(Files == FILES::BOTH || Files == FILES::CIPHER)
        Cipher = FileToString(Cipher);

    std::vector<std::string> Ciphers = split(Cipher, '\n');
    std::string Output;

    for(int i = 0; i < Input64.length(); i++)
    {
        const char B64 = Input64[i];

        if(B64 == '=' && i != Input64.length() - 1)
            if(Input64[i + 1] == '=')
            {
                Output += Ciphers[_base64_chars.find(B64) + 1] + Separator;
                return Output;
            }

        Output += Ciphers[_base64_chars.find(B64)] + Separator;
    }

    return Output;
}