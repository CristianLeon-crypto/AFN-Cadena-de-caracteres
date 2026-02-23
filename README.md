# AFD - Autómata Finito Determinista

## ¿Qué hace esto?

Este programa lee un archivo `.txt` línea por línea y decide si cada token es válido o no según estas reglas:

| Token | Patrón | Ejemplo |
|---|---|---|
| **Id** | Letra seguida de minúsculas o dígitos | `abc`, `A`, `a1b2` |
| **Suma** | Solo un `+` | `+` |
| **Incremento** | Dos `+` seguidos | `++` |
| **Entero** | Solo dígitos | `123`, `9` |

Si no cumple ninguna regla → **NO ACEPTA**

---

## ¿Cómo funciona por dentro?

El AFD va leyendo cada carácter del token uno por uno y cambia de estado según lo que encuentre:

- **q0** → estado inicial, espera el primer carácter
- **q1** → estado de aceptación, sigue leyendo
- **-1** → estado muerto, ya no hay vuelta atrás

Por ejemplo para un **Id**:
A b c 1 2
q0 → q1 → q1 → q1 → q1 ✅ ACEPTA


Para algo inválido:
1 a b c
q0 → q1(entero) pero luego encuentra 'a' → muerto ❌ NO ACEPTA


---

## ¿Cómo se ejecuta?

### Python

No necesitas instalar nada, solo tener Python 3.

```bash
python3 quiz.py archivo.txt


### C
Primero hay que compilar (solo una vez):

gcc quiz.c -o QuizC

Luego ejecutar:

./QuizC archivo.txt

¿Cómo debe ser el archivo.txt?
Un token por línea, así de simple:

abc
A
+
++
123
1abc
@hello

Ejemplo de salida
ACEPTA: 'abc' -> Id
ACEPTA: 'A' -> Id
ACEPTA: '+' -> Suma
ACEPTA: '++' -> Incremento
ACEPTA: '123' -> Entero
NO ACEPTA: '1abc'
NO ACEPTA: '@hello'

Estructura del proyecto
📁 proyecto/
├── afd.py       # versión Python
├── afd.c        # versión C
└── archivo.txt  # archivo de entrada