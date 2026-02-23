# dfa_tokens.py

def is_plus(s: str) -> bool:
    return s == "+"

def is_increment(s: str) -> bool:
    return s == "++"

def is_integer_1digit(s: str) -> bool:
    return len(s) == 1 and s[0].isdigit()

def is_id(s: str) -> bool:
    # DFA:
    # q0: inicio
    # q1: ya leí la primera letra (aceptación posible)
    # q2: espero minúscula (para comenzar un par)
    # q3: espero dígito (para cerrar el par)
    if len(s) == 0:
        return False

    i = 0

    # Primer char: [A-Za-z]
    if not s[i].isalpha():
        return False
    i += 1

    # Luego cero o más pares: ([a-z][0-9])*
    # Eso significa que el resto debe tener longitud par y alternar: minúscula, dígito
    while i < len(s):
        # espero minúscula
        if not ('a' <= s[i] <= 'z'):
            return False
        i += 1
        if i >= len(s):
            return False
        # espero dígito
        if not s[i].isdigit():
            return False
        i += 1

    return True

def accepts_token(s: str) -> bool:
    # Importante: orden. "++" antes que "+"
    if is_increment(s):
        return True
    elif is_plus(s):
        return True
    elif is_integer_1digit(s):
        return True
    elif is_id(s):
        return True
    else:
        return False

def main():
    try:
        with open("archivo.txt", "r", encoding="utf-8") as f:
            for line in f:
                raw = line.rstrip("\n")
                s = raw.strip()  # quita espacios alrededor

                # Si quieres tratar líneas vacías como NO ACEPTA:
                if s == "":
                    print(f"\"{raw}\" NO ACEPTA")
                    continue

                if accepts_token(s):
                    print(f"\"{raw}\" ACEPTA")
                else:
                    print(f"\"{raw}\" NO ACEPTA")

    except FileNotFoundError:
        print("Error: no se encontró 'archivo.txt' en el directorio actual.")
    except Exception as e:
        print(f"Error inesperado: {e}")

if __name__ == "__main__":
    main()