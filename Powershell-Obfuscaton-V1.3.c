#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define KEY 123  // Simple XOR encryption key, change this to a secure key

// Function to encrypt or decrypt the PowerShell script strings
void xorEncryptDecrypt(char* script) {
    size_t len = strlen(script);
    for (size_t i = 0; i < len; ++i) {
        script[i] = script[i] ^ KEY;
    }
}

// Function to rename PowerShell script variables
void renameVariables(char* script) {
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
    const char* loopTemplate = "for ($i=0; $i<%d; ++$i) { }\n";
    const char* conditionalTemplate = "if (%s) { }\n";

    int numTransformations = 5;
    int scriptLen = strlen(script);

    for (int i = 0; i < numTransformations; ++i) {
        int transformType = rand() % 2;

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
    int len = strlen(script);
    int numLineBreaks = rand() % 5 + 1;
    for (int i = 0; i < numLineBreaks; ++i) {
        int insertPos = rand() % len;
        memmove(script + insertPos + 2, script + insertPos, len - insertPos);
        script[insertPos] = '\n';
        script[insertPos + 1] = '/';
    }

    int numIndentations = rand() % 5 + 1;
    for (int i = 0; i < numIndentations; ++i) {
        int insertPos = rand() % len;
        memmove(script + insertPos + 4, script + insertPos, len - insertPos);
        memcpy(script + insertPos, "    ", 4);
    }
}

// Function to read script content from a file
char* readScriptFile(const char* filePath, long* scriptSize) {
    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filePath);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    *scriptSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* script = (char*)malloc(*scriptSize + 1);
    fread(script, *scriptSize, 1, file);
    script[*scriptSize] = '\0';

    fclose(file);
    return script;
}

// Function to write script content to a file
void writeScriptFile(const char* filePath, const char* script) {
    FILE* file = fopen(filePath, "w");
    if (file == NULL) {
        printf("Error writing to file: %s\n", filePath);
        return;
    }
    fputs(script, file);
    fclose(file);
}

// Function to obfuscate or deobfuscate the script
void processScript(const char* inputPath, const char* outputPath, int decrypt) {
    long scriptSize;
    char* script = readScriptFile(inputPath, &scriptSize);
    if (script == NULL) {
        return;
    }

    srand((unsigned int)time(NULL));

    if (decrypt) {
        xorEncryptDecrypt(script);  // Decrypt
    } else {
        xorEncryptDecrypt(script);  // Encrypt
        renameVariables(script);
        obfuscateControlFlow(script);
        restructureCode(script);
    }

    writeScriptFile(outputPath, script);
    free(script);
}

// Main function to handle obfuscation and decryption
int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Usage: %s <input file> <output file> <mode>\n", argv[0]);
        printf("Mode: 0 = Obfuscate, 1 = Deobfuscate\n");
        return 1;
    }

    const char* inputFilePath = argv[1];
    const char* outputFilePath = argv[2];
    int mode = atoi(argv[3]);

    if (mode == 0) {
        printf("Obfuscating script...\n");
        processScript(inputFilePath, outputFilePath, 0);
        printf("Obfuscation complete. Output saved to %s\n", outputFilePath);
    } else if (mode == 1) {
        printf("Deobfuscating script...\n");
        processScript(inputFilePath, outputFilePath, 1);
        printf("Decryption complete. Output saved to %s\n", outputFilePath);
    } else {
        printf("Invalid mode. Use 0 for obfuscation or 1 for decryption.\n");
        return 1;
    }

    return 0;
}
