#include "Cloakify.h"

const std::string _base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

std::string FileToString(const std::string FileName)
{
    std::ifstream ifs(FileName.c_str(), std::ios::in | std::ios::binary | std::ios::ate);

    std::ifstream::pos_type fileSize = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    std::vector<char> bytes(fileSize);
    ifs.read(bytes.data(), fileSize);

    return std::string(bytes.data(), fileSize);
}

std::string FileToLines(const std::string FileName)
{
    std::ifstream File(FileName);
    std::string Line;
    std::string Output;

    while (std::getline(File, Line))
        Output += Line + "\n";

    return Output;
}

std::string Cloak(const std::string Input, std::string Cipher, const FILES Files)
{
    std::string Input64;

    if(Files == FILES::BOTH || Files == FILES::INPUT)
        Input64 = Encoding::Base64::Encode(FileToString(Input));
    else
        Input64 = Encoding::Base64::Encode(Input);

    if(Files == FILES::BOTH || Files == FILES::CIPHER)
        Cipher = FileToLines(Cipher);

    std::vector<std::string> Ciphers = split(Cipher, '\n');
    std::string Output;

    for(int i = 0; i < Input64.length(); i++)
    {
        const char B64 = Input64[i];

        Output += Ciphers[_base64_chars.find(B64)];
    }

    return Output;
}