#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function to encrypt the PowerShell script strings
void encryptStrings(char* script) {
    // Simple XOR-based encryption
    char key = 0x7F;
    size_t len = strlen(script);
    for (size_t i = 0; i < len; ++i) {
        script[i] = script[i] ^ key;
    }
}

// Function to rename PowerShell script variables
void renameVariables(char* script) {
    // Replace common PowerShell variables with random names
    const char* variables[] = { "$_", "$args", "$true", "$false", "$null", "$input", "$output" };
    const int numVariables = sizeof(variables) / sizeof(variables[0]);

    for (int i = 0; i < numVariables; ++i) {
        int len = strlen(variables[i]);
        char replacement[len + 1];
        for (int j = 0; j < len; ++j) {
            replacement[j] = 'a' + rand() % 26;
        }
        replacement[len] = '\0';

        char* pos = strstr(script, variables[i]);
        while (pos != NULL) {
            strncpy(pos, replacement, len);
            pos = strstr(pos + len, variables[i]);
        }
    }
}

// Function to obfuscate the PowerShell script
void obfuscatePowerShellScript(const char* inputPath, const char* outputPath) {
    FILE* inputFile = fopen(inputPath, "r");
    FILE* outputFile = fopen(outputPath, "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Error opening files\n");
        return;
    }

    // Read the entire script into memory
    fseek(inputFile, 0, SEEK_END);
    long scriptSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);
    char* script = (char*)malloc(scriptSize + 1);
    fread(script, scriptSize, 1, inputFile);
    script[scriptSize] = '\0';

    // Perform obfuscation steps
    encryptStrings(script);
    renameVariables(script);

    // Write the obfuscated script to the output file
    fputs(script, outputFile);

    fclose(inputFile);
    fclose(outputFile);
    free(script);
}

int main() {
    srand((unsigned int)time(NULL)); // Seed the random number generator

    const char* inputFilePath = "input.ps1";     // Replace with your input PowerShell file path
    const char* outputFilePath = "output.ps1";   // Replace with the desired output obfuscated file path

    obfuscatePowerShellScript(inputFilePath, outputFilePath);
    printf("Obfuscation complete.\n");

    return 0;
}
