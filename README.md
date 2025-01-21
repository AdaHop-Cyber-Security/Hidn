# Hidn

Updated version of the provided C obfuscator code with decryption functionality added. This version includes an option to decrypt an obfuscated PowerShell script by applying the same XOR-based encryption key. 

DO NOT UPLOAD TO VIRUSTOTAL.COM OR EQUIVALENT!

---

Compile:

On Linux/macOS:
gcc obfuscator.c -o obfuscator

On Windows (using MinGW):
cmd
gcc obfuscator.c -o obfuscator.exe

---

How to Use the Program

Obfuscation:

To obfuscate the script:
./obfuscator input.ps1 output_obfuscated.ps1 0

Example:
obfuscator.exe input.ps1 output_obfuscated.ps1 0


Decryption:

To deobfuscate the script:
./obfuscator output_obfuscated.ps1 output_decrypted.ps1 1


Example:
obfuscator.exe output_obfuscated.ps1 output_decrypted.ps1 1

---

Explanation of Changes and Features:

1. Encryption and Decryption:
    
    - XOR-based encryption to obscure the script.
    - Toggle between obfuscation and decryption using command-line arguments.
    
2. File Handling:
    
    - Reads script content from a file.
    - Writes obfuscated/decrypted content to a new file.
    
3. Randomization:
    
    - Variable renaming and control flow obfuscation with random elements.
    - Junk code insertion.
