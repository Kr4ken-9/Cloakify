/*
   base64.cpp and base64.h

   base64 encoding and decoding with C++.

   Version: 1.01.00

   Copyright (C) 2004-2017 René Nyffenegger

   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely, subject to the following restrictions:

   1. The origin of this source code must not be misrepresented; you must not
      claim that you wrote the original source code. If you use this source code
      in a product, an acknowledgment in the product documentation would be
      appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
      misrepresented as being the original source code.

   3. This notice may not be removed or altered from any source distribution.

   René Nyffenegger rene.nyffenegger@adp-gmbh.ch

 */

#include "base64.h"


static const std::string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz"
                "0123456789+/";

static inline bool is_base64(unsigned char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string ReplaceAll(std::string str, std::string from, std::string to) {
    size_t pos = 0;
    while ((pos = str.find(from, pos)) != std::string::npos) {
        str.replace(pos, from.length(), to);
        pos += to.length();
    }
    return str;
}

std::string RemoveAll(std::string str, std::string toErase) {
    if (toErase.length() < 1 || str.length() < 1) {
        return str;
    }
    size_t pos = 0;
    while ((pos = str.find(toErase, pos)) != std::string::npos) {
        str.erase(pos, toErase.length());
    }
    return str;
}

std::string InsertRepeat(std::string str, size_t repeatEvery, std::string toRepeat, bool includeEnd) {
    if (repeatEvery < 1 || toRepeat == "" || toRepeat == "\0" || str.length() < 1 || toRepeat.length() < 1) {
        return str;
    }
    size_t pos = repeatEvery;
    while (pos < str.size()) {
        str.insert(pos, toRepeat);
        pos += repeatEvery + toRepeat.length();
    }
    if (pos == str.length() && includeEnd) {
        str += toRepeat;
    }
    return str;
}

std::string Encoding::Base64::ToSafeUrlBase64(std::string base64) {
    base64 = ReplaceAll(base64, "+", "-");
    base64 = ReplaceAll(base64, "/", "_");
    base64 = ReplaceAll(base64, "=", ",");
    return base64;
}

std::string Encoding::Base64::ToUnsafeUrlBase64(std::string base64) {
    base64 = ReplaceAll(base64, "-", "+");
    base64 = ReplaceAll(base64, "_", "/");
    base64 = ReplaceAll(base64, ",", "=");
    return base64;
}

std::string Encoding::Base64::RemoveLineBreaks(std::string base64) {
    return RemoveAll(base64, LINE_BREAKS_CHAR);
}

std::string Encoding::Base64::InsertLineBreaks(std::string base64, size_t lineBreakAppear) {
    return InsertRepeat(base64, lineBreakAppear, LINE_BREAKS_CHAR, false);
}

std::string Encoding::Base64::Encode(std::string data, bool toUrlSafe, size_t lineBreaks ) {
    size_t in_len = data.length();
    std::string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];
    int ac = 0;
    while (in_len--) {
        char_array_3[i++] = (unsigned char) data[ac++];
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; (i < 4); i++) {
                ret += base64_chars[char_array_4[i]];
            }
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 3; j++) {
            char_array_3[j] = '\0';
        }

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++) {
            ret += base64_chars[char_array_4[j]];
        }

        while ((i++ < 3)) {
            ret += '=';
        }

    }
    if(lineBreaks>0)
    {
        ret = InsertLineBreaks(ret, lineBreaks);
    }
    ret = toUrlSafe ? ToSafeUrlBase64(ret) : ret;
    return ret;
}

std::string Encoding::Base64::Decode(std::string base64) {
    base64 = ToUnsafeUrlBase64(base64);
    base64 = RemoveLineBreaks(base64);
    int in_len = base64.size();
    int i = 0;
    int j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    std::string ret;

    while (in_len-- && (base64[in_] != '=') && is_base64(base64[in_])) {
        char_array_4[i++] = base64[in_];
        in_++;
        if (i == 4) {
            for (i = 0; i < 4; i++)
                char_array_4[i] = base64_chars.find(char_array_4[i]);

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; (i < 3); i++)
                ret += char_array_3[i];
            i = 0;
        }
    }

    if (i) {
        for (j = 0; j < i; j++)
            char_array_4[j] = base64_chars.find(char_array_4[j]);

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);

        for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
    }

    return ret;
}
