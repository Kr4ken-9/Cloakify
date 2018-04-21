using System;
using System.IO;
using System.Text;

namespace Cloakify
{
    public static class Cloakify
    {
        public enum InputMode { BothFiles, InputFile, CipherFile, None }

        private const string BASE64CHARACTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

        public static string Cloak(string input, string cipher, InputMode inputMode)
        {
            if (inputMode == InputMode.BothFiles || inputMode == InputMode.CipherFile)
                cipher = File.ReadAllText(cipher);
            if (inputMode == InputMode.BothFiles || inputMode == InputMode.InputFile)
                input = File.ReadAllText(input);

            string input64 = EncodeBase64(input);
            string[] cipherArray = cipher.Split('\n');

            StringBuilder result = new StringBuilder();

            for (int i = 0; i < input64.Length; i++)
            {
                char c = input64[i];

                if (c == '=' && i != input64.Length - 1)
                    if (input64[i + 1] == '=')
                    {
                        result.Append(cipherArray[BASE64CHARACTERS.IndexOf(c) + 1] + '\n');
                        return result.ToString();
                    }

                result.Append(cipherArray[BASE64CHARACTERS.IndexOf(c)] + '\n');
            }

            return result.ToString();
        }

        public static string Uncloak(string input, string cipher, InputMode inputMode)
        {
            if (inputMode == InputMode.BothFiles || inputMode == InputMode.CipherFile)
                cipher = File.ReadAllText(cipher);
            if (inputMode == InputMode.BothFiles || inputMode == InputMode.InputFile)
                input = File.ReadAllText(input);

            string[] inputLines = input.Trim('\n').Split('\n');
            string[] cipherLines = cipher.Trim('\n').Split('\n');

            StringBuilder result = new StringBuilder();

            foreach (string s in inputLines)
            {
                int index = Array.FindIndex(cipherLines, x => x == s);

                if (index == 65)
                {
                    result.Append("==");
                    break;
                }
                else
                    result.Append(BASE64CHARACTERS[index]);
            }

            return DecodeBase64(result.ToString());
        }

        private static string EncodeBase64(string input) =>
            Convert.ToBase64String(Encoding.UTF8.GetBytes(input));

        private static string DecodeBase64(string input) =>
            Encoding.UTF8.GetString(Convert.FromBase64String(input));
    }
}
