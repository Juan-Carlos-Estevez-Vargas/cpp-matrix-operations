/**
 * ============================================================================
 * ARCHIVO: 02_aritmetica.cpp
 * PROPÓSITO: Operaciones aritméticas básicas con matrices
 * CONCEPTOS: Suma, resta, multiplicación, producto por escalar
 * 
 * TEORÍA:
 * Las operaciones aritméticas con matrices extienden las operaciones
 * aritméticas de números reales, pero con reglas específicas.
 * ============================================================================
 */

#include <iostream>
#include "01_utils.cpp"

/**
 * NOMBRE: sumarMatrices
 * PROPÓSITO: Calcula la suma de dos matrices
 * 
 * EXPLICACIÓN MATEMÁTICA:
 * La suma de matrices A + B se define elemento a elemento:
 * (A + B)ᵢⱼ = Aᵢⱼ + Bᵢⱼ
 * 
 * PROPIEDADES:
 * - Conmutativa: A + B = B + A
 * - Asociativa: (A + B) + C = A + (B + C)
 * - Elemento neutro: A + 0 = A
 * - Requiere mismas dimensiones
 * 
 * @param A Primera matriz
 * @param B Segunda matriz
 * @param resultado Matriz resultado (A + B)
 * @param filas Número de filas
 * @param columnas Número de columnas
 * @return true si la operación fue exitosa
 */
bool sumarMatrices(double A[][MAX_COLUMNAS], double B[][MAX_COLUMNAS], 
                    double resultado[][MAX_COLUMNAS], int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            resultado[i][j] = A[i][j] + B[i][j];
        }
    }
    return true;
}

/**
 * NOMBRE: restarMatrices
 * PROPÓSITO: Calcula la resta de dos matrices (A - B)
 * 
 * EXPLICACIÓN MATEMÁTICA:
 * La resta se define como: A - B = A + (-B)
 * (A - B)ᵢⱼ = Aᵢⱼ - Bᵢⱼ
 * 
 * @param A Primera matriz
 * @param B Segunda matriz
 * @param resultado Matriz resultado (A - B)
 * @param filas Número de filas
 * @param columnas Número de columnas
 * @return true si la operación fue exitosa
 */
bool restarMatrices(double A[][MAX_COLUMNAS], double B[][MAX_COLUMNAS], 
                    double resultado[][MAX_COLUMNAS], int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            resultado[i][j] = A[i][j] - B[i][j];
        }
    }
    return true;
}

/**
 * NOMBRE: multiplicarPorEscalar
 * PROPÓSITO: Multiplica una matriz por un escalar
 * 
 * EXPLICACIÓN MATEMÁTICA:
 * El producto por escalar multiplica cada elemento por el escalar:
 * (c·A)ᵢⱼ = c · Aᵢⱼ
 * 
 * PROPIEDADES:
 * - Distributiva respecto a suma de matrices: c(A + B) = cA + cB
 * - Distributiva respecto a suma de escalares: (c + d)A = cA + dA
 * - Asociativa mixta: (cd)A = c(dA)
 * - Elemento neutro: 1·A = A
 * 
 * @param matriz Matriz original
 * @param resultado Matriz resultado (c·A)
 * @param escalar Valor escalar
 * @param filas Número de filas
 * @param columnas Número de columnas
 */
void multiplicarPorEscalar(double matriz[][MAX_COLUMNAS], double resultado[][MAX_COLUMNAS], 
                          double escalar, int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            resultado[i][j] = matriz[i][j] * escalar;
        }
    }
}

/**
 * NOMBRE: multiplicarMatrices
 * PROPÓSITO: Multiplica dos matrices
 * 
 * EXPLICACIÓN MATEMÁTICA:
 * El producto de matrices A (m×n) y B (n×p) da C (m×p):
 * Cᵢⱼ = Σₖ Aᵢₖ · Bₖⱼ  para k = 1,...,n
 * 
 * INTERPRETACIÓN GEOMÉTRICA:
 * La multiplicación de matrices representa composición de
 * transformaciones lineales. Si A y B son transformaciones,
 * AB aplica primero B y luego A.
 * 
 * PROPIEDADES:
 * - Asociativa: (AB)C = A(BC)
 * - Distributiva: A(B + C) = AB + AC
 * - NO conmutativa: AB ≠ BA generalmente
 * 
 * @param A Primera matriz (m×n)
 * @param B Segunda matriz (n×p)
 * @param resultado Matriz resultado (m×p)
 * @param filasA Filas de A (m)
 * @param columnasA Columnas de A / Filas de B (n)
 * @param columnasB Columnas de B (p)
 * @return true si la operación fue exitosa
 */
bool multiplicarMatrices(double A[][MAX_COLUMNAS], double B[][MAX_COLUMNAS], 
                        double resultado[][MAX_COLUMNAS], int filasA, 
                        int columnasA, int columnasB) {
    // Verificar compatibilidad de dimensiones
    if (columnasA <= 0 || filasA <= 0 || columnasB <= 0) {
        return false;
    }
    
    // Inicializar resultado con ceros
    for (int i = 0; i < filasA; i++) {
        for (int j = 0; j < columnasB; j++) {
            resultado[i][j] = 0.0;
        }
    }
    
    // Multiplicación: C[i][j] = Σ A[i][k] * B[k][j]
    for (int i = 0; i < filasA; i++) {
        for (int k = 0; k < columnasA; k++) {
            double a_ik = A[i][k];
            if (std::fabs(a_ik) > TOLERANCIA) {  // Optimización: evitar multiplicar por cero
                for (int j = 0; j < columnasB; j++) {
                    resultado[i][j] += a_ik * B[k][j];
                }
            }
        }
    }
    return true;
}

/**
 * NOMBRE: potenciaMatriz
 * PROPÓSITO: Eleva una matriz cuadrada a una potencia entera
 * 
 * EXPLICACIÓN MATEMÁTICA:
 * A^k = A · A · ... · A (k veces)
 * Por definición: A⁰ = I (matriz identidad)
 * 
 * MÉTODO DE EXPONENCIACIÓN BINARIA:
 * Para grandes exponentes, es más eficiente usar:
 * A^n = (A^(n/2))^2 si n es par
 * A^n = A · A^(n-1) si n es impar
 * 
 * @param matriz Matriz original
 * @param resultado Matriz resultado (A^k)
 * @param n Dimensión de la matriz
 * @param exponente Exponente (debe ser ≥ 0)
 * @return true si la operación fue exitosa
 */
bool potenciaMatriz(double matriz[][MAX_COLUMNAS], double resultado[][MAX_COLUMNAS], 
                   int n, int exponente) {
    if (exponente < 0) {
        return false;  // Exponentes negativos requieren matriz inversa
    }
    
    if (exponente == 0) {
        inicializarIdentidad(resultado, n);
        return true;
    }
    
    if (exponente == 1) {
        copiarMatriz(matriz, resultado, n, n);
        return true;
    }
    
    // Algoritmo de exponenciación binaria (más eficiente)
    double base[MAX_FILAS][MAX_COLUMNAS];
    double temp[MAX_FILAS][MAX_COLUMNAS];
    copiarMatriz(matriz, base, n, n);
    inicializarIdentidad(resultado, n);
    
    int exp = exponente;
    while (exp > 0) {
        if (exp % 2 == 1) {
            // resultado = resultado * base
            double nueva[MAX_FILAS][MAX_COLUMNAS];
            multiplicarMatrices(resultado, base, nueva, n, n, n);
            copiarMatriz(nueva, resultado, n, n);
        }
        // base = base * base
        double baseCuadrada[MAX_FILAS][MAX_COLUMNAS];
        multiplicarMatrices(base, base, baseCuadrada, n, n, n);
        copiarMatriz(baseCuadrada, base, n, n);
        
        exp /= 2;
    }
    
    return true;
}