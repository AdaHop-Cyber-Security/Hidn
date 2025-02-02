# Obfuscator & Deobfuscator

This repository contains a powerfull obfuscator and deobfuscator for PowerShell scripts. It applies multiple layers of encryption and obfuscation techniques to help mask your code. The tool is written in C and uses basic XOR encryption, with an optional additional Base64 encoding layer. It also includes extra obfuscation transformations such as variable renaming, control flow manipulation (junk loops, conditionals, fake functions), and code restructuring.

## Features

- **XOR Encryption/Decryption:**  
  A simple XOR-based algorithm that can be applied twice to revert to the original content.

- **Optional Base64 Encoding/Decoding:**  
  Adds an extra layer of encoding to the obfuscation process.

- **Additional Obfuscation Techniques:**  
  - **Variable Renaming:** Randomizes PowerShell variable names.
  - **Control Flow Manipulation:** Inserts junk loops, conditionals, and fake functions.
  - **Code Restructuring:** Randomly inserts line breaks and indentations.

- **Basic Error Handling:**  
  Provides messages for file I/O and memory allocation issues.

## Requirements

- GCC or another C compiler

## Compilation

To compile the program, run:

```bash
gcc obfuscator.c -o obfuscator
```

This will generate an executable called `obfuscator`.

## Usage

The executable follows this usage pattern:

```bash
./obfuscator <input_file> <output_file> <mode> [--base64]
```

- `<input_file>`: Path to the PowerShell script (or any text file) you wish to process.
- `<output_file>`: Path where the processed (obfuscated or deobfuscated) file will be saved.
- `<mode>`:  
  - Use `0` for **obfuscation**.
  - Use `1` for **deobfuscation**.
- `[--base64]`: *(Optional)* When provided, applies an extra layer of Base64 encoding (during obfuscation) or decoding (during deobfuscation).

## Examples

### 1. Obfuscate a Script

**Without Base64 Encoding:**

```bash
./obfuscator script.ps1 obfuscated_script.ps1 0
```

**With Base64 Encoding:**

```bash
./obfuscator script.ps1 obfuscated_script.ps1 0 --base64
```

*Output:*  
You should see a message like:  
```
[*] Obfuscating script...
[+] Obfuscation complete. Output saved to obfuscated_script.ps1
```

### 2. Deobfuscate a Script

**Without Base64 Decoding:**

```bash
./obfuscator obfuscated_script.ps1 deobfuscated_script.ps1 1
```

**With Base64 Decoding:**

```bash
./obfuscator obfuscated_script.ps1 deobfuscated_script.ps1 1 --base64
```

*Output:*  
You should see a message like:  
```
[*] Deobfuscating script...
[+] Decryption complete. Output saved to deobfuscated_script.ps1
```

## Notes

- **Randomization:**  
  The obfuscation process includes random transformations (e.g., variable renaming and junk code insertion) so that each run may produce different results.

- **XOR Key:**  
  The XOR key is set to `123` by default. For production use or enhanced security, consider modifying the key in the source code.

- **File Limitations:**  
  The maximum line size for file operations is set to 4096 bytes. Adjust the `MAX_LINE` definition if needed.

## License

This project is provided "as is" without any warranty. Use at your own risk.

## Acknowledgments

Written by Pin3apple – feel free to fork, modify, and contribute!

---

You can adjust the README content as needed. Happy coding!
