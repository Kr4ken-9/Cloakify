#include "Cloakify.h"

const std::string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz"
                "0123456789+/";

std::string FileToString(const std::string FileName)
{
    std::stringstream sstr;
    std::ifstream in;

    in.open(FileName);
    sstr << in.rdbuf();

    return sstr.str();
}

std::string Cloak(const std::string Input, bool File)
{
    std::string Input64;

    if(File)
        Input64 = Encoding::Base64::Encode(FileToString(Input));
    else
        Input64 = Encoding::Base64::Encode(Input);

    return Input64;
}