#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to obfuscate the PowerShell script
void obfuscatePowerShellScript(const char* inputPath, const char* outputPath) {
    FILE* inputFile = fopen(inputPath, "r");
    FILE* outputFile = fopen(outputPath, "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Error opening files\n");
        return;
    }

    // Character substitution mapping
    const char* obfuscatedCharacters[] = { "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "-", "+", "=", "{", "}", "[", "]", ":", ";", "\"", "\'", "<", ">", ",", ".", "/", "?", "\\", "|", "~" };

    char line[1024];
    while (fgets(line, sizeof(line), inputFile)) {
        for (int i = 0; line[i] != '\0'; ++i) {
            char c = line[i];
            if (c >= 'A' && c <= 'Z') {
                line[i] = 'A' + (c - 'A' + 1) % 26;
            } else if (c >= 'a' && c <= 'z') {
                line[i] = 'a' + (c - 'a' + 1) % 26;
            } else if (c >= '0' && c <= '9') {
                line[i] = '0' + (c - '0' + 1) % 10;
            } else if (c == ' ') {
                line[i] = ' ';
            } else {
                // Replace special characters with obfuscated characters
                line[i] = obfuscatedCharacters[c % (sizeof(obfuscatedCharacters) / sizeof(obfuscatedCharacters[0]))][0];
            }
        }
        fputs(line, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);
}

int main() {
    const char* inputFilePath = "input.ps1";     // Replace with your input PowerShell file path
    const char* outputFilePath = "output.ps1";   // Replace with the desired output obfuscated file path

    obfuscatePowerShellScript(inputFilePath, outputFilePath);
    printf("Obfuscation complete.\n");

    return 0;
}
