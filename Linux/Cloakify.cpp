#include "Cloakify.h"

const std::string _base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz"
                "0123456789+/";

std::string FileToString(const std::string FileName)
{
    std::ifstream in (FileName.c_str());

    return static_cast<std::stringstream const&>(std::stringstream() << in.rdbuf()).str();
}

std::string Cloak(const std::string Input, bool File)
{
    std::string Input64;

    if(File)
        Input64 = Encoding::Base64::Encode(FileToString(Input));
    else
        Input64 = Encoding::Base64::Encode(Input);


}