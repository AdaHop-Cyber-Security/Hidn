import base64
import random

def xor_encrypt_decrypt(data, key):
    result = bytearray()
    for i, byte in enumerate(data):
        result.append(byte ^ key[i % len(key)])
    return bytes(result)

def string_encrypt(s, key):
    encrypted_data = xor_encrypt_decrypt(s.encode(), key)
    return base64.b64encode(encrypted_data).decode()

def split_code(code):
    code_parts = []
    while code:
        part_length = random.randint(30, 50)
        code_parts.append(code[:part_length])
        code = code[part_length:]
    return code_parts

def obfuscate_code(code):
    encryption_key = b'YourEncryptionKeyHere'
    encrypted_strings = {}
    
    # Encrypt strings in the code
    encrypted_code = ""
    while True:
        start_idx = code.find('"')
        if start_idx == -1:
            encrypted_code += code
            break
        
        end_idx = code.find('"', start_idx + 1)
        if end_idx == -1:
            encrypted_code += code
            break

        string_to_encrypt = code[start_idx + 1:end_idx]
        encrypted_string = string_encrypt(string_to_encrypt, encryption_key)
        encrypted_strings[string_to_encrypt] = encrypted_string
        encrypted_code += code[:start_idx] + f'"{encrypted_string}"'
        code = code[end_idx + 1:]

    return encrypted_code, encrypted_strings

def anti_debug_check():
    try:
        import ctypes
        kernel32 = ctypes.WinDLL('kernel32')
        is_debugged = ctypes.c_bool()
        kernel32.IsDebuggerPresent(ctypes.byref(is_debugged))
        if is_debugged.value:
            exit()
    except:
        pass

def main():
    # Load the original code from the file
    input_file = "input.py"
    with open(input_file, "r") as file:
        code = file.read()

    # Apply obfuscation techniques
    encrypted_code, encrypted_strings = obfuscate_code(code)
    code_parts = split_code(encrypted_code)
    anti_debug_check_code = anti_debug_check.__code__.co_code
    
    # Create obfuscated output files
    with open("obfuscated.py", "w") as file:
        file.write("".join(code_parts))

    with open("encrypted_strings.txt", "w") as file:
        for original_string, encrypted_string in encrypted_strings.items():
            file.write(f"{original_string} => {encrypted_string}\n")

if __name__ == "__main__":
    main()
