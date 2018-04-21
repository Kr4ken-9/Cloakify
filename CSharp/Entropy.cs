using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace Cloakify
{
    public static class Entropy
    {
        public enum NoiseInputMode { Input, Entropy, Both, None };

        private const string SYMBOLS = "`~!@#$%^&*()-_=+[{]}\\|';/?.>,<";
        private const string NUMBERS = "0123456789";
        private const string LETTERS = "abcedfghijklmnopqrstuvwxyzABCEDFGHIJKLMNOPQRSTUVWXYZ";

        private static readonly Random rand = new Random();

        public static string RemoveAlphanumericOrSymbolNoise(string input, NoiseInputMode inputMode)
        {
            if (inputMode == NoiseInputMode.Both || inputMode == NoiseInputMode.Input)
                input = File.ReadAllText(input);

            string[] inputLines = input.Trim('\n').Split('\n');

            StringBuilder result = new StringBuilder();

            foreach (string s in inputLines)
            {
                for (int i = 1; i < s.Length; i += 2)
                    result.Append(s[i]);

                result.Append("\n");
            }

            return result.ToString();
        }

        public static string RemovePrefixNoise(string input, NoiseInputMode inputMode)
        {
            if (inputMode == NoiseInputMode.Both || inputMode == NoiseInputMode.Input)
                input = File.ReadAllText(input);

            string[] inputLines = input.Trim('\n').Split('\n');

            StringBuilder result = new StringBuilder();

            foreach (string s in inputLines)
            {
                result.Append(s.Split(' ')[1]);
                result.Append("\n");
            }

            return result.ToString();
        }

        public static string RemoveSuffixNoise(string input, NoiseInputMode inputMode)
        {
            if (inputMode == NoiseInputMode.Both || inputMode == NoiseInputMode.Input)
                input = File.ReadAllText(input);

            string[] inputLines = input.Trim('\n').Split('\n');

            StringBuilder result = new StringBuilder();

            foreach (string s in inputLines)
            {
                result.Append(s.Split(' ')[0]);
                result.Append("\n");
            }

            return result.ToString();
        }

        public static string RemoveAfafNoise(string input, NoiseInputMode inputMode)
        {
            if (inputMode == NoiseInputMode.Both || inputMode == NoiseInputMode.Input)
                input = File.ReadAllText(input);

            string[] inputLines = input.Trim('\n').Split('\n');

            StringBuilder result = new StringBuilder();

            for (int i = 0; i < inputLines.Length; i++)
            {
                string[] s = inputLines[i].Split(' ');
                result.Append(!((i + 1) % 3 == 0) ? s[1] : s[0]);
                result.Append("\n");
            }

            return result.ToString();
        }

        public static string AddAlphanumericNoise(string input, NoiseInputMode inputMode)
        {
            if (inputMode == NoiseInputMode.Both || inputMode == NoiseInputMode.Input)
                input = File.ReadAllText(input);

            string[] inputLines = input.Trim('\n').Split('\n');

            StringBuilder result = new StringBuilder();

            foreach (string s in inputLines)
            {
                bool isDigit = int.TryParse(s[0].ToString(), out int yourMomIsGay);

                for (int i = 0; i < s.Length; i++)
                    result.Append((isDigit ? LETTERS[rand.Next(LETTERS.Length)] : NUMBERS[rand.Next(NUMBERS.Length)]).ToString() + s[i]);

                result.Append(isDigit ? LETTERS[rand.Next(LETTERS.Length)] : NUMBERS[rand.Next(NUMBERS.Length)]);
                result.Append("\n");
            }

            return result.ToString();
        }

        public static string AddSymbolNoise(string input, NoiseInputMode inputMode)
        {
            if (inputMode == NoiseInputMode.Both || inputMode == NoiseInputMode.Input)
                input = File.ReadAllText(input);

            string[] inputLines = input.Trim('\n').Split('\n');

            StringBuilder result = new StringBuilder();

            foreach (string s in inputLines)
            {
                for (int i = 0; i < s.Length; i++)
                    result.Append(SYMBOLS[rand.Next(SYMBOLS.Length)].ToString() + s[i]);

                result.Append(SYMBOLS[rand.Next(SYMBOLS.Length)]);
                result.Append("\n");
            }

            return result.ToString();
        }

        public static string AddPrefixNoise(string input, string entropy, NoiseInputMode inputMode)
        {
            if (inputMode == NoiseInputMode.Both || inputMode == NoiseInputMode.Input)
                input = File.ReadAllText(input);
            if (inputMode == NoiseInputMode.Both || inputMode == NoiseInputMode.Entropy)
                entropy = File.ReadAllText(entropy);

            string[] inputLines = input.Trim('\n').Split('\n');
            string[] entropyLines = entropy.Trim('\n').Split('\n');

            StringBuilder result = new StringBuilder();

            foreach (string s in inputLines)
            {
                result.Append(entropyLines[rand.Next(entropyLines.Length)] + ' ' + s);
                result.Append("\n");
            }

            return result.ToString();
        }

        public static string AddSuffixNoise(string input, string entropy, NoiseInputMode inputMode)
        {
            if (inputMode == NoiseInputMode.Both || inputMode == NoiseInputMode.Input)
                input = File.ReadAllText(input);
            if (inputMode == NoiseInputMode.Both || inputMode == NoiseInputMode.Entropy)
                entropy = File.ReadAllText(entropy);

            string[] inputLines = input.Trim('\n').Split('\n');
            string[] entropyLines = entropy.Trim('\n').Split('\n');

            StringBuilder result = new StringBuilder();

            foreach (string s in inputLines)
            {
                result.Append(s + ' ' + entropyLines[rand.Next(entropyLines.Length)]);
                result.Append("\n");
            }

            return result.ToString();
        }

        public static string AddAfafNoise(string input, string entropy, NoiseInputMode inputMode)
        {
            if (inputMode == NoiseInputMode.Both || inputMode == NoiseInputMode.Input)
                input = File.ReadAllText(input);
            if (inputMode == NoiseInputMode.Both || inputMode == NoiseInputMode.Entropy)
                entropy = File.ReadAllText(entropy);

            string[] inputLines = input.Trim('\n').Split('\n');
            string[] entropyLines = entropy.Trim('\n').Split('\n');

            StringBuilder result = new StringBuilder();

            List<String> freq = entropyLines.OrderBy(x => rand.Next()).Take(5).ToList();

            for (int i = 0; i < inputLines.Length; i++)
            {
                string l = inputLines[i];
                string e = freq[rand.Next(freq.Count)];

                if (!((i + 1) % 3 == 0))
                    result.Append(e + " " + l);
                else
                    result.Append(l + " " + e);

                result.Append("\n");
            }

            return result.ToString();
        }
    }
}
