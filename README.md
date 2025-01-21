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
  
--------------------------------------------------------------------------------------------------------------------------------

How to Compile V2.0

Linux/macOS (with GCC installed):
gcc obfuscator.c -o obfuscator


Windows (with MinGW or similar):
gcc obfuscator.c -o obfuscator.exe
    

How to Run

    Obfuscation (Mode = 0)
    

./obfuscator <input_file> <output_file> 0 [--base64]

    <input_file>: The original PowerShell script you want to obfuscate (e.g. input.ps1).
    <output_file>: The file to which the obfuscated script will be saved (e.g. output.ps1).
    0: Indicates obfuscation mode.
    --base64 (optional): Adds a second layer of Base64 encoding on top of XOR.
    

Example:

./obfuscator input.ps1 output.ps1 0 --base64

Deobfuscation (Mode = 1)

./obfuscator <input_file> <output_file> 1 [--base64]

    <input_file>: The obfuscated PowerShell script you want to restore.
    <output_file>: The file to which the deobfuscated script will be saved.
    1: Indicates deobfuscation mode.
    --base64 (optional): Applies Base64 decoding before the XOR decryption if the original script was obfuscated with --base64.

Example:

    ./obfuscator output.ps1 restored.ps1 1 --base64

Features and Notes

    Multiple Layers of Encryption
        XOR encryption (simple but effective when combined with other techniques).
        Optional Base64 encoding for an added layer of obfuscation.

    Obfuscation Techniques
        Variable Renaming: Renames $a, $b, ..., $z to random single-letter variables.
        Control Flow Manipulation: Inserts random loops, conditionals, and fake functions.
        Junk Code and Restructuring: Adds line breaks, indentation, and commented junk code.

    Usage of rand()
        srand((unsigned int)time(NULL)) seeds the random generator.
        For more secure randomness, consider using a cryptographic RNG on your platform.

    Portability and Safety
        The code performs basic error handling for file reading/writing.
        Memory allocations are checked to avoid segmentation faults.

    Key Customization
        #define XOR_KEY 123 can be changed to any integer.
        For production, consider using a user-supplied XOR key or generating one dynamically.

    Limitations
        Advanced reverse-engineers can still decompile or manually analyze obfuscated scripts.
        This tool is best used as an additional layer of defense.
