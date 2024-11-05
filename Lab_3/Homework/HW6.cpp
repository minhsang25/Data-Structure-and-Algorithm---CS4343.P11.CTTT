#include <iostream>
#include <vector>
#include <string>

void computeLPS(const std::string &pattern, std::vector<int> &lps) {
    int length = 0; // Length of the previous longest prefix suffix
    lps[0] = 0; // lps[0] is always 0
    int i = 1;

    while (i < pattern.length()) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void KMPSearch(const std::string &text, const std::string &pattern) {
    std::vector<int> lps(pattern.length());
    computeLPS(pattern, lps);

    int i = 0; // Index for text
    int j = 0; // Index for pattern

    while (i < text.length()) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == pattern.length()) {
            std::cout << "Found pattern at index " << (i - j) << "\n";
            j = lps[j - 1];
        } else if (i < text.length() && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}

int main() {
    std::string text = "ABABDABACDABABCABAB";
    std::string pattern = "ABABCABAB";
    KMPSearch(text, pattern);
    return 0;
}
