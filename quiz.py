import sys

def afd(token):
    try:
        if not token:
            return "NO ACEPTA"

        if token == "++":
            return "Incremento"

        if token == "+":
            return "Suma"

        # --- AFD Entero: [0-9]+ ---
        estado = "q0"
        es_entero = True
        for c in token:
            if estado == "q0":
                if c.isdigit():
                    estado = "q1"
                else:
                    es_entero = False
                    break
            elif estado == "q1":
                if c.isdigit():
                    estado = "q1"
                else:
                    es_entero = False
                    break

        if es_entero and estado == "q1":
            return "Entero"

        # --- AFD Id: [A-Za-z]([a-z]|[0-9])* ---
        estado = "q0"
        es_id = True
        for c in token:
            if estado == "q0":
                if c.isalpha():
                    estado = "q1"
                else:
                    es_id = False
                    break
            elif estado == "q1":
                if c.islower() or c.isdigit():
                    estado = "q1"
                else:
                    es_id = False
                    break

        if es_id and estado == "q1":
            return "Id"

        return "NO ACEPTA"

    except Exception as e:
        return f"ERROR: {e}"


try:
    archivo = open(sys.argv[1], "r")
    lineas = archivo.readlines()
    archivo.close()

    for i, linea in enumerate(lineas, start=1):
        token = linea.strip()
        resultado = afd(token)
        if resultado == "NO ACEPTA":
            print(f"NO ACEPTA: '{token}'")
        else:
            print(f"ACEPTA: '{token}' -> {resultado}")

except FileNotFoundError:
    print(f"ERROR: No se encontró el archivo '{sys.argv[1]}'")
except Exception as e:
    print(f"ERROR inesperado: {e}")