#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

/**
 * Written by (Pin3apple) 
 * This obfuscator and deobfuscator provides:
 * 1. Multiple layers of encryption (XOR + optional Base64).
 * 2. Additional obfuscation techniques:
 *    - Variable renaming
 *    - Control flow manipulation
 *    - Junk code insertion
 *    - Code restructuring
 * 3. Basic error handling to prevent crashes on file I/O.
 * 
 * Compile:
 *   gcc obfuscator.c -o obfuscator
 * 
 * Usage:
 *   ./obfuscator <input_file> <output_file> <mode> [--base64]
 * 
 *   mode: 0 = Obfuscate, 1 = Deobfuscate
 *   --base64 (optional): Adds an extra layer of Base64 encoding/decoding
 */

// --------------------------- CONFIGURATION -----------------------------------

// Change these keys to secure keys for production use:
#define XOR_KEY  123    // Simple XOR key, consider using a random or user-provided key
#define MAX_LINE 4096   // Maximum line size for file operations

// --------------------------- UTILITY FUNCTIONS -------------------------------

/**
 * Read the entire file into a dynamically allocated buffer.
 * 
 * @param filePath  Path to the file to read.
 * @param fileSize  Output parameter to store the file size.
 * @return          Pointer to the dynamically allocated buffer containing file content
 */
char* readFile(const char* filePath, long* fileSize) {
    FILE* file = fopen(filePath, "rb");
    if (!file) {
        fprintf(stderr, "[-] Error opening file: %s\n", filePath);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    *fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (*fileSize <= 0) {
        fprintf(stderr, "[-] File is empty or unreadable.\n");
        fclose(file);
        return NULL;
    }

    char* buffer = (char*)malloc(*fileSize + 1);
    if (!buffer) {
        fprintf(stderr, "[-] Memory allocation failed.\n");
        fclose(file);
        return NULL;
    }

    size_t readBytes = fread(buffer, 1, *fileSize, file);
    buffer[readBytes] = '\0'; // Null terminate
    fclose(file);

    return buffer;
}

/**
 * Write content to a file.
 * 
 * @param filePath  Path to the output file.
 * @param data      Pointer to the data buffer to write.
 */
int writeFile(const char* filePath, const char* data) {
    FILE* file = fopen(filePath, "wb");
    if (!file) {
        fprintf(stderr, "[-] Error creating file: %s\n", filePath);
        return 0;
    }

    size_t dataLen = strlen(data);
    fwrite(data, 1, dataLen, file);
    fclose(file);
    return 1;
}

/**
 * XOR-based encryption/decryption. 
 * This function can be applied twice to get back original data.
 * 
 * @param buffer  The string buffer to be modified in place.
 */
void xorEncryptDecrypt(char* buffer) {
    size_t len = strlen(buffer);
    for (size_t i = 0; i < len; i++) {
        buffer[i] ^= XOR_KEY;
    }
}

/**
 * Base64 Encoding Table
 */
static const char b64_table[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/**
 * Base64 encode a buffer. 
 * 
 * @param in        Input data buffer
 * @param inLen     Length of input data
 * @param outLen    Output parameter for the length of encoded data
 * @return          Dynamically allocated encoded string (must be free'd by caller)
 */
char* base64Encode(const unsigned char* in, size_t inLen, size_t* outLen) {
    size_t encLen = 4 * ((inLen + 2) / 3);
    char* out = (char*)malloc(encLen + 1); 
    if (!out) {
        fprintf(stderr, "[-] Memory allocation failed for Base64 encode.\n");
        return NULL;
    }

    size_t i, j;
    for (i = 0, j = 0; i < inLen;) {
        uint32_t octet_a = i < inLen ? (unsigned char)in[i++] : 0;
        uint32_t octet_b = i < inLen ? (unsigned char)in[i++] : 0;
        uint32_t octet_c = i < inLen ? (unsigned char)in[i++] : 0;

        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        out[j++] = b64_table[(triple >> 3 * 6) & 0x3F];
        out[j++] = b64_table[(triple >> 2 * 6) & 0x3F];
        out[j++] = b64_table[(triple >> 1 * 6) & 0x3F];
        out[j++] = b64_table[(triple >> 0 * 6) & 0x3F];
    }

    // Add padding
    for (size_t k = 0; k < (3 - (inLen % 3)) % 3; k++) {
        out[encLen - 1 - k] = '=';
    }
    out[encLen] = '\0';
    *outLen = encLen;

    return out;
}

/**
 * Base64 decode a buffer.
 * 
 * @param in        Input string (Base64 encoded)
 * @param outLen    Output parameter for the length of decoded data
 * @return          Dynamically allocated decoded data (must be free'd by caller)
 */
unsigned char* base64Decode(const char* in, size_t* outLen) {
    // Build decoding table
    static int tableBuilt = 0;
    static unsigned char decodingTable[256];
    if (!tableBuilt) {
        for (int i = 0; i < 64; i++) {
            decodingTable[(unsigned char)b64_table[i]] = i;
        }
        tableBuilt = 1;
    }

    size_t inLen = strlen(in);
    if (inLen % 4 != 0) {
        fprintf(stderr, "[-] Invalid Base64 input length.\n");
        return NULL;
    }

    size_t outputLen = inLen / 4 * 3;
    if (in[inLen - 1] == '=') outputLen--;
    if (in[inLen - 2] == '=') outputLen--;

    unsigned char* out = (unsigned char*)malloc(outputLen + 1);
    if (!out) {
        fprintf(stderr, "[-] Memory allocation failed for Base64 decode.\n");
        return NULL;
    }

    for (size_t i = 0, j = 0; i < inLen;) {
        uint32_t sextet_a = in[i] == '=' ? 0 & i++ : decodingTable[(int)in[i++]];
        uint32_t sextet_b = in[i] == '=' ? 0 & i++ : decodingTable[(int)in[i++]];
        uint32_t sextet_c = in[i] == '=' ? 0 & i++ : decodingTable[(int)in[i++]];
        uint32_t sextet_d = in[i] == '=' ? 0 & i++ : decodingTable[(int)in[i++]];

        uint32_t triple = 
            (sextet_a << 3 * 6) +
            (sextet_b << 2 * 6) +
            (sextet_c << 1 * 6) +
            (sextet_d << 0 * 6);

        if (j < outputLen) out[j++] = (triple >> 2 * 8) & 0xFF;
        if (j < outputLen) out[j++] = (triple >> 1 * 8) & 0xFF;
        if (j < outputLen) out[j++] = (triple >> 0 * 8) & 0xFF;
    }
    out[outputLen] = '\0';
    *outLen = outputLen;

    return out;
}

// --------------------------- OBFUSCATION TECHNIQUES -------------------------

/**
 * Rename PowerShell variables by replacing $a, $b, ..., $z
 * with random single-letter variable names.
 */
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

/**
 * Introduce junk loops, conditionals, and fake functions
 * to break the natural flow of the code.
 */
void obfuscateControlFlow(char* script) {
    const char* loopTemplate = "\nfor ($i=0; $i<%d; ++$i) { #junk loop }\n";
    const char* conditionalTemplate = "\nif (%s) { #junk conditional }\n";
    const char* functionTemplate = "\nfunction %s { Write-Host 'fake func' }\n";

    int numTransformations = 5;
    int scriptLen = (int)strlen(script);

    for (int i = 0; i < numTransformations; i++) {
        int transformType = rand() % 3; 
        int insertPos = rand() % (scriptLen + 1);

        if (transformType == 0) {
            // Insert junk loop
            int numIterations = rand() % 10 + 1;
            char loopCode[80];
            snprintf(loopCode, sizeof(loopCode), loopTemplate, numIterations);

            memmove(script + insertPos + strlen(loopCode),
                    script + insertPos,
                    scriptLen - insertPos + 1);
            memcpy(script + insertPos, loopCode, strlen(loopCode));
            scriptLen += (int)strlen(loopCode);

        } else if (transformType == 1) {
            // Insert junk conditional
            int conditionLength = rand() % 5 + 3;
            char condition[20];
            for (int j = 0; j < conditionLength; j++) {
                condition[j] = 'a' + rand() % 26;
            }
            condition[conditionLength] = '\0';

            char conditionalCode[80];
            snprintf(conditionalCode, sizeof(conditionalCode), conditionalTemplate, condition);

            memmove(script + insertPos + strlen(conditionalCode),
                    script + insertPos,
                    scriptLen - insertPos + 1);
            memcpy(script + insertPos, conditionalCode, strlen(conditionalCode));
            scriptLen += (int)strlen(conditionalCode);

        } else {
            // Insert fake function
            int funcNameLen = rand() % 5 + 3;
            char funcName[20];
            for (int j = 0; j < funcNameLen; j++) {
                funcName[j] = 'a' + rand() % 26;
            }
            funcName[funcNameLen] = '\0';

            char functionCode[80];
            snprintf(functionCode, sizeof(functionCode), functionTemplate, funcName);

            memmove(script + insertPos + strlen(functionCode),
                    script + insertPos,
                    scriptLen - insertPos + 1);
            memcpy(script + insertPos, functionCode, strlen(functionCode));
            scriptLen += (int)strlen(functionCode);
        }
    }
}

/**
 * Randomly inserts line breaks and indentation
 * to make the script less readable.
 */
void restructureCode(char* script) {
    int scriptLen = (int)strlen(script);
    int numLineBreaks = rand() % 5 + 1;
    for (int i = 0; i < numLineBreaks; i++) {
        int insertPos = rand() % (scriptLen + 1);
        const char* lineBreak = "\n//";
        int lbLen = (int)strlen(lineBreak);

        memmove(script + insertPos + lbLen, script + insertPos, scriptLen - insertPos + 1);
        memcpy(script + insertPos, lineBreak, lbLen);
        scriptLen += lbLen;
    }

    int numIndentations = rand() % 5 + 1;
    for (int i = 0; i < numIndentations; i++) {
        int insertPos = rand() % (scriptLen + 1);
        const char* indent = "    ";
        int indentLen = (int)strlen(indent);

        memmove(script + insertPos + indentLen, script + insertPos, scriptLen - insertPos + 1);
        memcpy(script + insertPos, indent, indentLen);
        scriptLen += indentLen;
    }
}

// --------------------------- MAIN PROCESS LOGIC ------------------------------

/**
 * processScript:
 *   - Reads the input script.
 *   - Depending on the mode (obfuscate/deobfuscate), applies transformations.
 *   - Writes the transformed content to the output file.
 * 
 * @param inputPath   Path to the input PowerShell script.
 * @param outputPath  Path to the output obfuscated/deobfuscated file.
 * @param mode        0 for obfuscation, 1 for deobfuscation.
 * @param useBase64   If non-zero, apply an additional layer of Base64 encoding/decoding.
 */
void processScript(const char* inputPath, const char* outputPath, int mode, int useBase64) {
    long fileSize = 0;
    char* script = readFile(inputPath, &fileSize);
    if (!script) {
        return; // Error already printed
    }

    // Seed random for obfuscation transformations
    srand((unsigned int)time(NULL));

    if (mode == 0) {
        // ---------------- Obfuscation ----------------
        printf("[*] Obfuscating script...\n");

        // 1. First XOR encryption
        xorEncryptDecrypt(script);

        // 2. Optional Base64 encoding
        if (useBase64) {
            size_t encodedLen = 0;
            unsigned char* scriptUnsigned = (unsigned char*)script; 
            size_t scriptLen = strlen(script);
            char* encoded = base64Encode(scriptUnsigned, scriptLen, &encodedLen);
            if (!encoded) {
                free(script);
                return;
            }
            free(script);
            script = encoded;  // script now contains Base64 encoded text
        }

        // 3. Additional obfuscation transformations
        renameVariables(script);
        obfuscateControlFlow(script);
        restructureCode(script);

        // Write out obfuscated result
        if (writeFile(outputPath, script)) {
            printf("[+] Obfuscation complete. Output saved to %s\n", outputPath);
        }
    } else if (mode == 1) {
        // -------------- Deobfuscation ---------------
        printf("[*] Deobfuscating script...\n");

        // If script is Base64-encoded, decode first
        if (useBase64) {
            size_t decodedLen = 0;
            unsigned char* decoded = base64Decode(script, &decodedLen);
            if (!decoded) {
                free(script);
                return;
            }
            free(script);
            script = (char*)malloc(decodedLen + 1);
            if (!script) {
                fprintf(stderr, "[-] Memory allocation failed.\n");
                free(decoded);
                return;
            }
            memcpy(script, decoded, decodedLen);
            script[decodedLen] = '\0';
            free(decoded);
        }

        // XOR decrypt
        xorEncryptDecrypt(script);

        // Write out deobfuscated result
        if (writeFile(outputPath, script)) {
            printf("[+] Decryption complete. Output saved to %s\n", outputPath);
        }
    } else {
        fprintf(stderr, "[-] Invalid mode. Use 0 for obfuscation or 1 for deobfuscation.\n");
    }

    free(script);
}

// --------------------------- MAIN ENTRY POINT --------------------------------

int main(int argc, char* argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <input_file> <output_file> <mode> [--base64]\n", argv[0]);
        fprintf(stderr, "       mode: 0 = Obfuscate, 1 = Deobfuscate\n");
        fprintf(stderr, "       --base64 (optional): Adds an extra layer of Base64 encoding/decoding\n");
        return 1;
    }

    const char* inputFilePath  = argv[1];
    const char* outputFilePath = argv[2];
    int mode                   = atoi(argv[3]);
    int useBase64              = 0; // By default, do not use Base64

    // Check for optional --base64 argument
    for (int i = 4; i < argc; i++) {
        if (strcmp(argv[i], "--base64") == 0) {
            useBase64 = 1;
        }
    }

    processScript(inputFilePath, outputFilePath, mode, useBase64);

    return 0;
}
