#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function to encrypt the PowerShell script strings
void encryptStrings(char* script) {
    // Advanced encryption algorithm (you can use any secure encryption library here)
    // For demonstration purposes, we will use a simple XOR-based encryption with a random key
    char key = rand() % 256;
    size_t len = strlen(script);
    for (size_t i = 0; i < len; ++i) {
        script[i] = script[i] ^ key;
    }
}

// Function to rename PowerShell script variables
void renameVariables(char* script) {
    // Replace PowerShell variables with randomly generated names
    // For simplicity, we'll use single-character variable names
    for (char c = 'a'; c <= 'z'; ++c) {
        char varName[3];
        snprintf(varName, sizeof(varName), "$%c", c);

        char replacement[3];
        snprintf(replacement, sizeof(replacement), "$%c", 'a' + rand() % 26);

        char* pos = strstr(script, varName);
        while (pos != NULL) {
            strncpy(pos, replacement, 2);
            pos = strstr(pos + 2, varName);
        }
    }
}

// Function to obfuscate control flow by introducing junk loops and conditionals
void obfuscateControlFlow(char* script) {
    // Introduce random junk loops and conditionals to confuse analysis
    // You can implement more sophisticated transformations based on the script's structure
    const char* loopTemplate = "for ($i=0; $i<%d; ++$i) { }\n";
    const char* conditionalTemplate = "if (%s) { }\n";

    int numTransformations = 5;
    int scriptLen = strlen(script);

    for (int i = 0; i < numTransformations; ++i) {
        int transformType = rand() % 2; // 0 for loop, 1 for conditional

        if (transformType == 0) {
            int numIterations = rand() % 10 + 1;
            int insertPos = rand() % scriptLen;
            char loopCode[50];
            snprintf(loopCode, sizeof(loopCode), loopTemplate, numIterations);
            memmove(script + insertPos + strlen(loopCode), script + insertPos, scriptLen - insertPos);
            memcpy(script + insertPos, loopCode, strlen(loopCode));
            scriptLen += strlen(loopCode);
        } else {
            int conditionLength = rand() % 10 + 1;
            int insertPos = rand() % scriptLen;
            char condition[20];
            for (int j = 0; j < conditionLength; ++j) {
                condition[j] = 'a' + rand() % 26;
            }
            condition[conditionLength] = '\0';

            char conditionalCode[50];
            snprintf(conditionalCode, sizeof(conditionalCode), conditionalTemplate, condition);
            memmove(script + insertPos + strlen(conditionalCode), script + insertPos, scriptLen - insertPos);
            memcpy(script + insertPos, conditionalCode, strlen(conditionalCode));
            scriptLen += strlen(conditionalCode);
        }
    }
}

// Function to perform code restructuring
void restructureCode(char* script) {
    // Add random comments, line breaks, and indentation to make the script less readable
    int len = strlen(script);
    int numLineBreaks = rand() % 5 + 1;
    for (int i = 0; i < numLineBreaks; ++i) {
        int insertPos = rand() % len;
        memmove(script + insertPos + 2, script + insertPos, len - insertPos);
        script[insertPos] = '\n';
        script[insertPos + 1] = '/';
    }

    // Add random indentation
    int numIndentations = rand() % 5 + 1;
    for (int i = 0; i < numIndentations; ++i) {
        int insertPos = rand() % len;
        memmove(script + insertPos + 4, script + insertPos, len - insertPos);
        memcpy(script + insertPos, "    ", 4);
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
    srand((unsigned int)time(NULL)); // Seed the random number generator
    encryptStrings(script);
    renameVariables(script);
    obfuscateControlFlow(script);
    restructureCode(script);

    // Write the obfuscated script to the output file
    fputs(script, outputFile);

    fclose(inputFile);
    fclose(outputFile);
    free(script);
}

int main() {
    const char* inputFilePath = "input.ps1";     // Replace with your input PowerShell file path
    const char* outputFilePath = "output.ps1";   // Replace with the desired output obfuscated file path

    obfuscatePowerShellScript(inputFilePath, outputFilePath);
    printf("Obfuscation complete.\n");

    return 0;
}
