/**
 * ============================================================================
 * PROGRAMA PRINCIPAL: CALCULADORA EDUCATIVA DE MATRICES
 * ============================================================================
 * 
 * main.cpp - Archivo principal que integra todas las funcionalidades
 * 
 * Este archivo contiene el menú principal, la gestión de matrices,
 * y las funciones para cada operación disponible.
 * 
 * AUTOR: Desarrollador Senior C++
 * PROPÓSITO: Curso de Fundamentos de Programación
 * VERSIÓN: 3.0 (Completa y documentada)
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <ctime>

// Constantes globales
#ifndef MAX_FILAS
#define MAX_FILAS 15
#define MAX_COLUMNAS 15
#define TOLERANCIA 1e-10
#endif

// Incluir todos los módulos
#include "01_utils.cpp"
#include "02_aritmetica.cpp"
#include "03_determinante_cofactores.cpp"
#include "04_determinante_gauss.cpp"
#include "05_inversa.cpp"
#include "06_sistemas_ecuaciones.cpp"
#include "07_valores_propios.cpp"
#include "08_descomposiciones.cpp"
#include "09_operaciones_avanzadas.cpp"
#include "10_aplicaciones.cpp"
#include "11_testing.cpp"

// ============================================================================
// ESTRUCTURAS DE DATOS
// ============================================================================

/**
 * Estructura para almacenar información de una matriz
 * nombre: Letra identificadora (A-Z)
 * datos: Array bidimensional con los valores
 * filas: Número de filas
 * columnas: Número de columnas
 * inicializada: Indica si la matriz tiene datos válidos
 */
struct MatrizInfo {
    double datos[MAX_FILAS][MAX_COLUMNAS];
    int filas;
    int columnas;
    char nombre;
    bool inicializada;
};

// ============================================================================
// VARIABLES GLOBALES
// ============================================================================

MatrizInfo matrices[26];  // Arreglo de 26 matrices (A-Z)
int matrizActual = 0;      // Índice de la matriz actualmente seleccionada (0 = A)

// ============================================================================
// FUNCIONES DE UTILIDAD Y GESTIÓN
// ============================================================================

/**
 * Inicializa el sistema de matrices
 * Configura todas las matrices como vacías
 */
void inicializarSistema() {
    for (int i = 0; i < 26; i++) {
        matrices[i].filas = 0;
        matrices[i].columnas = 0;
        matrices[i].nombre = 'A' + i;
        matrices[i].inicializada = false;
        inicializarCeros(matrices[i].datos, MAX_FILAS, MAX_COLUMNAS);
    }
    
    // Inicializar semilla para números aleatorios
    srand(time(NULL));
}

/**
 * Limpia el buffer de entrada después de una lectura
 * Previene problemas con caracteres residuales
 */
void limpiarBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/**
 * Pausa la ejecución hasta que el usuario presione Enter
 */
void pausa() {
    std::cout << "\nPresione Enter para continuar...";
    limpiarBuffer();
    std::cin.get();
}

/**
 * Muestra el encabezado de una sección
 * @param titulo Título de la sección
 */
void mostrarEncabezado(const char* titulo) {
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "  " << titulo << std::endl;
    std::cout << std::string(80, '=') << std::endl;
}

/**
 * Muestra el menú principal
 */
void mostrarMenu() {
    std::cout << "\n" << std::string(100, '=') << std::endl;
    std::cout << "     🧮 CALCULADORA EDUCATIVA DE MATRICES - FUNDAMENTOS DE PROGRAMACIÓN 🧮" << std::endl;
    std::cout << std::string(100, '=') << std::endl;
    
    // Mostrar matrices disponibles
    std::cout << "\n📊 MATRICES DISPONIBLES:" << std::endl;
    std::cout << "   ";
    for (int i = 0; i < 26; i++) {
        if (i > 0 && i % 8 == 0) std::cout << "\n   ";
        if (matrices[i].inicializada) {
            std::cout << " " << matrices[i].nombre << ":" 
                      << matrices[i].filas << "×" << matrices[i].columnas << " ";
        } else {
            std::cout << " " << matrices[i].nombre << ":[vacía] ";
        }
    }
    std::cout << "\n\n   ▶ Matriz actual: " << matrices[matrizActual].nombre;
    if (matrices[matrizActual].inicializada) {
        std::cout << " (" << matrices[matrizActual].filas << "×" 
                  << matrices[matrizActual].columnas << ")";
    }
    
    std::cout << "\n\n" << std::string(100, '-') << std::endl;
    std::cout << "📋 OPERACIONES DISPONIBLES:" << std::endl;
    std::cout << std::string(100, '-') << std::endl;
    
    std::cout << "\n🔹 GESTIÓN DE MATRICES:" << std::endl;
    std::cout << "   1.  Ingresar matriz manualmente" << std::endl;
    std::cout << "   2.  Generar matriz aleatoria" << std::endl;
    std::cout << "   3.  Mostrar matriz actual" << std::endl;
    std::cout << "   4.  Cambiar matriz actual" << std::endl;
    std::cout << "   5.  Copiar matriz a otra" << std::endl;
    
    std::cout << "\n🔹 OPERACIONES BÁSICAS:" << std::endl;
    std::cout << "   6.  Sumar matrices (A + B)" << std::endl;
    std::cout << "   7.  Restar matrices (A - B)" << std::endl;
    std::cout << "   8.  Multiplicar matrices (A × B)" << std::endl;
    std::cout << "   9.  Multiplicar por escalar (k × A)" << std::endl;
    std::cout << "   10. Calcular determinante" << std::endl;
    std::cout << "   11. Comparar métodos de determinante" << std::endl;
    std::cout << "   12. Calcular matriz inversa (A⁻¹)" << std::endl;
    std::cout << "   13. Calcular matriz transpuesta (Aᵀ)" << std::endl;
    std::cout << "   14. Calcular traza (tr(A))" << std::endl;
    std::cout << "   15. Elevar a potencia (Aⁿ)" << std::endl;
    
    std::cout << "\n🔹 ÁLGEBRA LINEAL AVANZADA:" << std::endl;
    std::cout << "   16. Resolver sistema de ecuaciones (Ax = b)" << std::endl;
    std::cout << "   17. Clasificar sistema lineal" << std::endl;
    std::cout << "   18. Calcular rango y nulidad" << std::endl;
    std::cout << "   19. Descomposición LU (A = L·U)" << std::endl;
    std::cout << "   20. Descomposición QR (A = Q·R)" << std::endl;
    std::cout << "   21. Valores propios (método de potencia)" << std::endl;
    std::cout << "   22. Exponencial de matriz (eᴬ)" << std::endl;
    
    std::cout << "\n🔹 APLICACIONES PRÁCTICAS:" << std::endl;
    std::cout << "   23. Regresión lineal (mínimos cuadrados)" << std::endl;
    std::cout << "   24. Transformación 2D (rotación)" << std::endl;
    std::cout << "   25. Cadena de Markov" << std::endl;
    
    std::cout << "\n🔹 HERRAMIENTAS EDUCATIVAS:" << std::endl;
    std::cout << "   26. Ejecutar pruebas exhaustivas" << std::endl;
    std::cout << "   27. Ver conceptos teóricos" << std::endl;
    std::cout << "   28. Guardar matriz en archivo" << std::endl;
    std::cout << "   29. Cargar matriz desde archivo" << std::endl;
    std::cout << "   30. Demostrar propiedades de matrices" << std::endl;
    
    std::cout << "\n🔹 SALIR:" << std::endl;
    std::cout << "   0.  Salir del programa" << std::endl;
    
    std::cout << "\n" << std::string(100, '=') << std::endl;
    std::cout << "Seleccione una opción (0-30): ";
}

// ============================================================================
// FUNCIONES DE GESTIÓN DE MATRICES (Opciones 1-5)
// ============================================================================

/**
 * Opción 1: Ingresar matriz manualmente
 */
void opcionIngresarMatriz() {
    mostrarEncabezado("INGRESAR MATRIZ MANUALMENTE");
    
    std::cout << "Matriz objetivo: " << matrices[matrizActual].nombre << std::endl;
    std::cout << "Número de filas (1-" << MAX_FILAS << "): ";
    std::cin >> matrices[matrizActual].filas;
    std::cout << "Número de columnas (1-" << MAX_COLUMNAS << "): ";
    std::cin >> matrices[matrizActual].columnas;
    
    if (matrices[matrizActual].filas <= 0 || matrices[matrizActual].filas > MAX_FILAS || 
        matrices[matrizActual].columnas <= 0 || matrices[matrizActual].columnas > MAX_COLUMNAS) {
        std::cout << "❌ Error: Dimensiones no válidas!" << std::endl;
        return;
    }
    
    std::cout << "\nIngrese los valores de la matriz (por filas):" << std::endl;
    for (int i = 0; i < matrices[matrizActual].filas; i++) {
        std::cout << "Fila " << i+1 << ": ";
        for (int j = 0; j < matrices[matrizActual].columnas; j++) {
            std::cin >> matrices[matrizActual].datos[i][j];
        }
    }
    
    matrices[matrizActual].inicializada = true;
    std::cout << "\n✅ Matriz ingresada correctamente:" << std::endl;
    mostrarMatriz(matrices[matrizActual].datos, matrices[matrizActual].filas, 
                  matrices[matrizActual].columnas);
}

/**
 * Opción 2: Generar matriz aleatoria
 */
void opcionGenerarAleatoria() {
    mostrarEncabezado("GENERAR MATRIZ ALEATORIA");
    
    std::cout << "Matriz objetivo: " << matrices[matrizActual].nombre << std::endl;
    std::cout << "Número de filas: ";
    std::cin >> matrices[matrizActual].filas;
    std::cout << "Número de columnas: ";
    std::cin >> matrices[matrizActual].columnas;
    
    int min, max;
    std::cout << "Valor mínimo: ";
    std::cin >> min;
    std::cout << "Valor máximo: ";
    std::cin >> max;
    
    // Generar matriz con valores aleatorios enteros
    for (int i = 0; i < matrices[matrizActual].filas; i++) {
        for (int j = 0; j < matrices[matrizActual].columnas; j++) {
            matrices[matrizActual].datos[i][j] = min + rand() % (max - min + 1);
        }
    }
    
    matrices[matrizActual].inicializada = true;
    std::cout << "\n✅ Matriz aleatoria generada:" << std::endl;
    mostrarMatriz(matrices[matrizActual].datos, matrices[matrizActual].filas, 
                  matrices[matrizActual].columnas);
}

/**
 * Opción 3: Mostrar matriz actual
 */
void opcionMostrarMatriz() {
    mostrarEncabezado("MOSTRAR MATRIZ ACTUAL");
    
    if (!matrices[matrizActual].inicializada) {
        std::cout << "⚠ La matriz " << matrices[matrizActual].nombre << " no ha sido inicializada." << std::endl;
        return;
    }
    
    std::cout << "Matriz " << matrices[matrizActual].nombre << " (" 
              << matrices[matrizActual].filas << "×" << matrices[matrizActual].columnas << "):" << std::endl;
    mostrarMatriz(matrices[matrizActual].datos, matrices[matrizActual].filas, 
                  matrices[matrizActual].columnas);
}

/**
 * Opción 4: Cambiar matriz actual
 */
void opcionCambiarMatriz() {
    mostrarEncabezado("CAMBIAR MATRIZ ACTUAL");
    
    char letra;
    std::cout << "Seleccione matriz (A-Z): ";
    std::cin >> letra;
    
    if (letra >= 'A' && letra <= 'Z') {
        matrizActual = letra - 'A';
        std::cout << "✅ Ahora trabajando con matriz " << matrices[matrizActual].nombre << std::endl;
        
        if (matrices[matrizActual].inicializada) {
            std::cout << "Dimensiones: " << matrices[matrizActual].filas << "×" 
                      << matrices[matrizActual].columnas << std::endl;
        } else {
            std::cout << "⚠ Esta matriz aún no ha sido inicializada." << std::endl;
        }
    } else if (letra >= 'a' && letra <= 'z') {
        matrizActual = letra - 'a';
        std::cout << "✅ Ahora trabajando con matriz " << char('A' + matrizActual) << std::endl;
        
        if (matrices[matrizActual].inicializada) {
            std::cout << "Dimensiones: " << matrices[matrizActual].filas << "×" 
                      << matrices[matrizActual].columnas << std::endl;
        } else {
            std::cout << "⚠ Esta matriz aún no ha sido inicializada." << std::endl;
        }
    } else {
        std::cout << "❌ Error: Debe ingresar una letra de la A a la Z." << std::endl;
    }
}

/**
 * Opción 5: Copiar matriz a otra
 */
void opcionCopiarMatriz() {
    mostrarEncabezado("COPIAR MATRIZ");
    
    if (!matrices[matrizActual].inicializada) {
        std::cout << "⚠ La matriz origen no ha sido inicializada." << std::endl;
        return;
    }
    
    char destino;
    std::cout << "Matriz origen: " << matrices[matrizActual].nombre << std::endl;
    std::cout << "Matriz destino (A-Z): ";
    std::cin >> destino;
    
    int idxDestino;
    if (destino >= 'A' && destino <= 'Z') {
        idxDestino = destino - 'A';
    } else if (destino >= 'a' && destino <= 'z') {
        idxDestino = destino - 'a';
    } else {
        std::cout << "❌ Error: Destino no válido." << std::endl;
        return;
    }
    
    // Copiar datos
    matrices[idxDestino].filas = matrices[matrizActual].filas;
    matrices[idxDestino].columnas = matrices[matrizActual].columnas;
    copiarMatriz(matrices[matrizActual].datos, matrices[idxDestino].datos, 
                 matrices[matrizActual].filas, matrices[matrizActual].columnas);
    matrices[idxDestino].inicializada = true;
    
    std::cout << "✅ Matriz copiada de " << matrices[matrizActual].nombre 
              << " a " << char('A' + idxDestino) << std::endl;
}

// ============================================================================
// FUNCIONES DE OPERACIONES BÁSICAS (Opciones 6-15)
// ============================================================================

/**
 * Opción 6: Sumar matrices
 */
void opcionSumarMatrices() {
    mostrarEncabezado("SUMA DE MATRICES (A + B)");
    
    if (!matrices[matrizActual].inicializada) {
        std::cout << "⚠ La matriz actual no está inicializada." << std::endl;
        return;
    }
    
    std::cout << "Matriz A (" << matrices[matrizActual].nombre << "):" << std::endl;
    mostrarMatriz(matrices[matrizActual].datos, matrices[matrizActual].filas, 
                  matrices[matrizActual].columnas);
    
    char letraB;
    std::cout << "\nSeleccione matriz B para sumar (A-Z): ";
    std::cin >> letraB;
    
    int idxB;
    if (letraB >= 'A' && letraB <= 'Z') idxB = letraB - 'A';
    else if (letraB >= 'a' && letraB <= 'z') idxB = letraB - 'a';
    else {
        std::cout << "❌ Error: Matriz no válida." << std::endl;
        return;
    }
    
    if (!matrices[idxB].inicializada) {
        std::cout << "⚠ La matriz B no está inicializada." << std::endl;
        return;
    }
    
    if (matrices[matrizActual].filas != matrices[idxB].filas || 
        matrices[matrizActual].columnas != matrices[idxB].columnas) {
        std::cout << "❌ Error: Las matrices deben tener las mismas dimensiones." << std::endl;
        std::cout << "A: " << matrices[matrizActual].filas << "×" << matrices[matrizActual].columnas << std::endl;
        std::cout << "B: " << matrices[idxB].filas << "×" << matrices[idxB].columnas << std::endl;
        return;
    }
    
    // Crear matriz resultado en la posición siguiente a Z (usaremos A como base temporal)
    double resultado[MAX_FILAS][MAX_COLUMNAS];
    sumarMatrices(matrices[matrizActual].datos, matrices[idxB].datos, resultado,
                  matrices[matrizActual].filas, matrices[matrizActual].columnas);
    
    std::cout << "\nMatriz B (" << matrices[idxB].nombre << "):" << std::endl;
    mostrarMatriz(matrices[idxB].datos, matrices[idxB].filas, matrices[idxB].columnas);
    
    std::cout << "\n✅ Resultado de A + B:" << std::endl;
    mostrarMatriz(resultado, matrices[matrizActual].filas, matrices[matrizActual].columnas);
}

/**
 * Opción 7: Restar matrices
 */
void opcionRestarMatrices() {
    mostrarEncabezado("RESTA DE MATRICES (A - B)");
    
    if (!matrices[matrizActual].inicializada) {
        std::cout << "⚠ La matriz actual no está inicializada." << std::endl;
        return;
    }
    
    std::cout << "Matriz A (" << matrices[matrizActual].nombre << "):" << std::endl;
    mostrarMatriz(matrices[matrizActual].datos, matrices[matrizActual].filas, 
                  matrices[matrizActual].columnas);
    
    char letraB;
    std::cout << "\nSeleccione matriz B para restar (A-Z): ";
    std::cin >> letraB;
    
    int idxB;
    if (letraB >= 'A' && letraB <= 'Z') idxB = letraB - 'A';
    else if (letraB >= 'a' && letraB <= 'z') idxB = letraB - 'a';
    else {
        std::cout << "❌ Error: Matriz no válida." << std::endl;
        return;
    }
    
    if (!matrices[idxB].inicializada) {
        std::cout << "⚠ La matriz B no está inicializada." << std::endl;
        return;
    }
    
    if (matrices[matrizActual].filas != matrices[idxB].filas || 
        matrices[matrizActual].columnas != matrices[idxB].columnas) {
        std::cout << "❌ Error: Las matrices deben tener las mismas dimensiones." << std::endl;
        return;
    }
    
    double resultado[MAX_FILAS][MAX_COLUMNAS];
    restarMatrices(matrices[matrizActual].datos, matrices[idxB].datos, resultado,
                   matrices[matrizActual].filas, matrices[matrizActual].columnas);
    
    std::cout << "\nMatriz B (" << matrices[idxB].nombre << "):" << std::endl;
    mostrarMatriz(matrices[idxB].datos, matrices[idxB].filas, matrices[idxB].columnas);
    
    std::cout << "\n✅ Resultado de A - B:" << std::endl;
    mostrarMatriz(resultado, matrices[matrizActual].filas, matrices[matrizActual].columnas);
}

/**
 * Opción 8: Multiplicar matrices
 */
void opcionMultiplicarMatrices() {
    mostrarEncabezado("MULTIPLICACIÓN DE MATRICES (A × B)");
    
    if (!matrices[matrizActual].inicializada) {
        std::cout << "⚠ La matriz actual no está inicializada." << std::endl;
        return;
    }
    
    std::cout << "Matriz A (" << matrices[matrizActual].nombre << "):" << std::endl;
    mostrarMatriz(matrices[matrizActual].datos, matrices[matrizActual].filas, 
                  matrices[matrizActual].columnas);
    
    char letraB;
    std::cout << "\nSeleccione matriz B para multiplicar (A-Z): ";
    std::cin >> letraB;
    
    int idxB;
    if (letraB >= 'A' && letraB <= 'Z') idxB = letraB - 'A';
    else if (letraB >= 'a' && letraB <= 'z') idxB = letraB - 'a';
    else {
        std::cout << "❌ Error: Matriz no válida." << std::endl;
        return;
    }
    
    if (!matrices[idxB].inicializada) {
        std::cout << "⚠ La matriz B no está inicializada." << std::endl;
        return;
    }
    
    if (matrices[matrizActual].columnas != matrices[idxB].filas) {
        std::cout << "❌ Error: Dimensiones incompatibles para multiplicación." << std::endl;
        std::cout << "A: " << matrices[matrizActual].filas << "×" << matrices[matrizActual].columnas << std::endl;
        std::cout << "B: " << matrices[idxB].filas << "×" << matrices[idxB].columnas << std::endl;
        std::cout << "Se requiere: columnas de A = filas de B" << std::endl;
        return;
    }
    
    double resultado[MAX_FILAS][MAX_COLUMNAS];
    multiplicarMatrices(matrices[matrizActual].datos, matrices[idxB].datos, resultado,
                        matrices[matrizActual].filas, matrices[matrizActual].columnas, 
                        matrices[idxB].columnas);
    
    std::cout << "\nMatriz B (" << matrices[idxB].nombre << "):" << std::endl;
    mostrarMatriz(matrices[idxB].datos, matrices[idxB].filas, matrices[idxB].columnas);
    
    std::cout << "\n✅ Resultado de A × B (" 
              << matrices[matrizActual].filas << "×" << matrices[idxB].columnas << "):" << std::endl;
    mostrarMatriz(resultado, matrices[matrizActual].filas, matrices[idxB].columnas);
}

/**
 * Opción 9: Multiplicar por escalar
 */
void opcionMultiplicarEscalar() {
    mostrarEncabezado("MULTIPLICACIÓN POR ESCALAR (k × A)");
    
    if (!matrices[matrizActual].inicializada) {
        std::cout << "⚠ La matriz actual no está inicializada." << std::endl;
        return;
    }
    
    double escalar;
    std::cout << "Ingrese el valor del escalar (k): ";
    std::cin >> escalar;
    
    std::cout << "\nMatriz original " << matrices[matrizActual].nombre << ":" << std::endl;
    mostrarMatriz(matrices[matrizActual].datos, matrices[matrizActual].filas, 
                  matrices[matrizActual].columnas);
    
    double resultado[MAX_FILAS][MAX_COLUMNAS];
    multiplicarPorEscalar(matrices[matrizActual].datos, resultado, escalar,
                          matrices[matrizActual].filas, matrices[matrizActual].columnas);
    
    std::cout << "\n✅ Resultado de " << escalar << " × " 
              << matrices[matrizActual].nombre << ":" << std::endl;
    mostrarMatriz(resultado, matrices[matrizActual].filas, matrices[matrizActual].columnas);
}

/**
 * Opción 10: Calcular determinante con teoría
 */
void opcionDeterminanteConTeoria() {
    mostrarEncabezado("DETERMINANTE - CONCEPTO Y CÁLCULO");
    
    if (!matrices[matrizActual].inicializada) {
        std::cout << "⚠ La matriz actual no está inicializada." << std::endl;
        return;
    }
    
    if (!esMatrizCuadrada(matrices[matrizActual].filas, matrices[matrizActual].columnas)) {
        std::cout << "❌ Error: El determinante solo se define para matrices cuadradas." << std::endl;
        std::cout << "La matriz actual es " << matrices[matrizActual].filas << "×" 
                  << matrices[matrizActual].columnas << std::endl;
        return;
    }
    
    // Explicación teórica
    std::cout << "\n📚 CONCEPTO TEÓRICO:" << std::endl;
    std::cout << "El determinante es un número asociado a matrices cuadradas que:" << std::endl;
    std::cout << "  • Indica si la matriz es invertible (det ≠ 0)" << std::endl;
    std::cout << "  • Representa el factor de escala de la transformación lineal" << std::endl;
    std::cout << "  • Da el volumen (con signo) del paralelepípedo formado por los vectores fila" << std::endl;
    
    std::cout << "\n📐 MATRIZ " << matrices[matrizActual].nombre << ":" << std::endl;
    mostrarMatriz(matrices[matrizActual].datos, matrices[matrizActual].filas, 
                  matrices[matrizActual].columnas);
    
    double det1 = calcularDeterminanteCofactores(matrices[matrizActual].datos, 
                                                  matrices[matrizActual].filas);
    double det2 = calcularDeterminanteGauss(matrices[matrizActual].datos, 
                                             matrices[matrizActual].filas);
    
    std::cout << "\n🔢 RESULTADOS:" << std::endl;
    std::cout << "  • Método de cofactores: " << std::fixed << std::setprecision(6) << det1 << std::endl;
    std::cout << "  • Método de Gauss:      " << det2 << std::endl;
    
    if (std::fabs(det2) < TOLERANCIA) {
        std::cout << "\n⚠ CONCLUSIÓN: La matriz es SINGULAR (no invertible)" << std::endl;
        std::cout << "  • det(A) = 0" << std::endl;
        std::cout << "  • La matriz NO tiene inversa" << std::endl;
        std::cout << "  • Los vectores fila/columna son linealmente dependientes" << std::endl;
    } else {
        std::cout << "\n✅ CONCLUSIÓN: La matriz es INVERTIBLE" << std::endl;
        std::cout << "  • det(A) ≠ 0" << std::endl;
        std::cout << "  • La matriz SÍ tiene inversa" << std::endl;
        std::cout << "  • Los vectores fila/columna son linealmente independientes" << std::endl;
    }
}

/**
 * Opción 11: Comparar métodos de determinante
 */
void opcionCompararDeterminantes() {
    mostrarEncabezado("COMPARACIÓN DE MÉTODOS DE DETERMINANTE");
    
    if (!matrices[matrizActual].inicializada) {
        std::cout << "⚠ La matriz actual no está inicializada." << std::endl;
        return;
    }
    
    if (!esMatrizCuadrada(matrices[matrizActual].filas, matrices[matrizActual].columnas)) {
        std::cout << "❌ Error: Se requiere matriz cuadrada." << std::endl;
        return;
    }
    
    compararMetodosDeterminante(matrices[matrizActual].datos, matrices[matrizActual].filas);
}

/**
 * Opción 12: Calcular matriz inversa
 */
void opcionInversa() {
    mostrarEncabezado("CÁLCULO DE MATRIZ INVERSA (A⁻¹)");
    
    if (!matrices[matrizActual].inicializada) {
        std::cout << "⚠ La matriz actual no está inicializada." << std::endl;
        return;
    }
    
    if (!esMatrizCuadrada(matrices[matrizActual].filas, matrices[matrizActual].columnas)) {
        std::cout << "❌ Error: La matriz debe ser cuadrada." << std::endl;
        return;
    }
    
    std::cout << "Matriz original " << matrices[matrizActual].nombre << ":" << std::endl;
    mostrarMatriz(matrices[matrizActual].datos, matrices[matrizActual].filas, 
                  matrices[matrizActual].columnas);
    
    double inversa[MAX_FILAS][MAX_COLUMNAS];
    
    if (calcularInversa(matrices[matrizActual].datos, inversa, matrices[matrizActual].filas)) {
        std::cout << "\n✅ Matriz inversa " << matrices[matrizActual].nombre << "⁻¹:" << std::endl;
        mostrarMatriz(inversa, matrices[matrizActual].filas, matrices[matrizActual].columnas);
        
        // Verificar
        if (verificarInversa(matrices[matrizActual].datos, inversa, matrices[matrizActual].filas)) {
            std::cout << "✅ Verificación: A × A⁻¹ = I (correcto)" << std::endl;
        } else {
            std::cout << "⚠ Verificación: A × A⁻¹ ≈ I (pequeños errores de redondeo)" << std::endl;
        }
    } else {
        std::cout << "\n❌ Error: La matriz no es invertible (determinante = 0)." << std::endl;
    }
}

/**
 * Opción 13: Calcular matriz transpuesta
 */
void opcionTranspuesta() {
    mostrarEncabezado("CÁLCULO DE MATRIZ TRANSPUESTA (Aᵀ)");
    
    if (!matrices[matrizActual].inicializada) {
        std::cout << "⚠ La matriz actual no está inicializada." << std::endl;
        return;
    }
    
    std::cout << "Matriz original " << matrices[matrizActual].nombre << ":" << std::endl;
    mostrarMatriz(matrices[matrizActual].datos, matrices[matrizActual].filas, 
                  matrices[matrizActual].columnas);
    
    double transpuesta[MAX_FILAS][MAX_COLUMNAS];
    calcularTranspuesta(matrices[matrizActual].datos, transpuesta,
                        matrices[matrizActual].filas, matrices[matrizActual].columnas);
    
    std::cout << "\n✅ Matriz transpuesta " << matrices[matrizActual].nombre << "ᵀ:" << std::endl;
    mostrarMatriz(transpuesta, matrices[matrizActual].columnas, matrices[matrizActual].filas);
}

/**
 * Opción 14: Calcular traza
 */
void opcionTraza() {
    mostrarEncabezado("CÁLCULO DE TRAZA (tr(A))");
    
    if (!matrices[matrizActual].inicializada) {
        std::cout << "⚠ La matriz actual no está inicializada." << std::endl;
        return;
    }
    
    if (!esMatrizCuadrada(matrices[matrizActual].filas, matrices[matrizActual].columnas)) {
        std::cout << "❌ Error: La traza solo se define para matrices cuadradas." << std::endl;
        return;
    }
    
    std::cout << "Matriz " << matrices[matrizActual].nombre << ":" << std::endl;
    mostrarMatriz(matrices[matrizActual].datos, matrices[matrizActual].filas, 
                  matrices[matrizActual].columnas);
    
    double traza = calcularTraza(matrices[matrizActual].datos, matrices[matrizActual].filas);
    
    std::cout << "\n✅ Traza tr(A) = " << std::fixed << std::setprecision(4) << traza << std::endl;
    std::cout << "(Suma de los elementos de la diagonal principal)" << std::endl;
}

/**
 * Opción 15: Elevar a potencia
 */
void opcionPotencia() {
    mostrarEncabezado("POTENCIA DE MATRIZ (Aⁿ)");
    
    if (!matrices[matrizActual].inicializada) {
        std::cout << "⚠ La matriz actual no está inicializada." << std::endl;
        return;
    }
    
    if (!esMatrizCuadrada(matrices[matrizActual].filas, matrices[matrizActual].columnas)) {
        std::cout << "❌ Error: La matriz debe ser cuadrada." << std::endl;
        return;
    }
    
    int exponente;
    std::cout << "Ingrese el exponente (entero no negativo): ";
    std::cin >> exponente;
    
    if (exponente < 0) {
        std::cout << "❌ Error: El exponente debe ser no negativo." << std::endl;
        return;
    }
    
    std::cout << "\nMatriz original " << matrices[matrizActual].nombre << ":" << std::endl;
    mostrarMatriz(matrices[matrizActual].datos, matrices[matrizActual].filas, 
                  matrices[matrizActual].columnas);
    
    double resultado[MAX_FILAS][MAX_COLUMNAS];
    
    if (potenciaMatriz(matrices[matrizActual].datos, resultado, 
                       matrices[matrizActual].filas, exponente)) {
        std::cout << "\n✅ Matriz " << matrices[matrizActual].nombre << "^" << exponente << ":" << std::endl;
        mostrarMatriz(resultado, matrices[matrizActual].filas, matrices[matrizActual].columnas);
    } else {
        std::cout << "❌ Error al calcular la potencia." << std::endl;
    }
}

// ============================================================================
// FUNCIONES DE ÁLGEBRA LINEAL AVANZADA (Opciones 16-22)
// ============================================================================

/**
 * Opción 16: Resolver sistema de ecuaciones
 */
void opcionResolverSistema() {
    mostrarEncabezado("RESOLVER SISTEMA DE ECUACIONES (Ax = b)");
    
    int n;
    std::cout << "Número de ecuaciones (y variables): ";
    std::cin >> n;
    
    if (n <= 0 || n > MAX_FILAS) {
        std::cout << "❌ Error: Dimensión no válida." << std::endl;
        return;
    }
    
    double A[MAX_FILAS][MAX_COLUMNAS];
    double b[MAX_FILAS][MAX_COLUMNAS];
    
    std::cout << "\nIngrese la matriz de coeficientes A (" << n << "×" << n << "):" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "Fila " << i+1 << ": ";
        for (int j = 0; j < n; j++) {
            std::cin >> A[i][j];
        }
    }
    
    std::cout << "\nIngrese el vector de términos independientes b (" << n << " elementos):" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "b[" << i+1 << "]: ";
        std::cin >> b[i][0];
    }
    
    std::cout << "\n📋 SISTEMA:" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "  ";
        for (int j = 0; j < n; j++) {
            std::cout << A[i][j] << "·x" << j+1;
            if (j < n-1) std::cout << " + ";
        }
        std::cout << " = " << b[i][0] << std::endl;
    }
    
    // Resolver por diferentes métodos
    double xGauss[MAX_FILAS][MAX_COLUMNAS];
    double xCramer[MAX_FILAS][MAX_COLUMNAS];
    double xInversa[MAX_FILAS][MAX_COLUMNAS];
    
    bool gaussOK = resolverSistemaGauss(A, b, xGauss, n);
    bool cramerOK = resolverSistemaCramer(A, b, xCramer, n);
    bool inversaOK = resolverSistemaInversa(A, b, xInversa, n);
    
    std::cout << "\n🔍 RESULTADOS:" << std::endl;
    
    if (gaussOK) {
        std::cout << "\n✅ Método de Gauss:" << std::endl;
        for (int i = 0; i < n; i++) {
            std::cout << "  x" << i+1 << " = " << std::setw(10) << xGauss[i][0] << std::endl;
        }
    }
    
    if (cramerOK) {
        std::cout << "\n✅ Regla de Cramer:" << std::endl;
        for (int i = 0; i < n; i++) {
            std::cout << "  x" << i+1 << " = " << std::setw(10) << xCramer[i][0] << std::endl;
        }
    }
    
    if (inversaOK) {
        std::cout << "\n✅ Método de la inversa:" << std::endl;
        for (int i = 0; i < n; i++) {
            std::cout << "  x" << i+1 << " = " << std::setw(10) << xInversa[i][0] << std::endl;
        }
    }
    
    if (!gaussOK && !cramerOK && !inversaOK) {
        std::cout << "\n❌ El sistema no tiene solución única (det(A) = 0)" << std::endl;
    }
}

/**
 * Opción 17: Clasificar sistema lineal
 */
void opcionClasificarSistema() {
    mostrarEncabezado("CLASIFICAR SISTEMA LINEAL");
    
    int n, m;
    std::cout << "Número de ecuaciones: ";
    std::cin >> m;
    std::cout << "Número de variables: ";
    std::cin >> n;
    
    if (n <= 0 || n > MAX_FILAS || m <= 0 || m > MAX_FILAS) {
        std::cout << "❌ Error: Dimensiones no válidas." << std::endl;
        return;
    }
    
    double A[MAX_FILAS][MAX_COLUMNAS];
    double b[MAX_FILAS][MAX_COLUMNAS];
    
    std::cout << "\nIngrese la matriz de coeficientes A (" << m << "×" << n << "):" << std::endl;
    for (int i = 0; i < m; i++) {
        std::cout << "Fila " << i+1 << ": ";
        for (int j = 0; j < n; j++) {
            std::cin >> A[i][j];
        }
    }
    
    std::cout << "\nIngrese el vector de términos independientes b (" << m << " elementos):" << std::endl;
    for (int i = 0; i < m; i++) {
        std::cout << "b[" << i+1 << "]: ";
        std::cin >> b[i][0];
    }
    
    clasificarSistema(A, b, n, m);
}

/**
 * Opción 18: Calcular rango y nulidad
 */
void opcionRangoNulidad() {
    mostrarEncabezado("RANGO Y NULIDAD DE UNA MATRIZ");
    
    if (!matrices[matrizActual].inicializada) {
        std::cout << "⚠ La matriz actual no está inicializada." << std::endl;
        return;
    }
    
    std::cout << "Matriz " << matrices[matrizActual].nombre << ":" << std::endl;
    mostrarMatriz(matrices[matrizActual].datos, matrices[matrizActual].filas, 
                  matrices[matrizActual].columnas);
    
    int rango = calcularRango(matrices[matrizActual].datos, 
                               matrices[matrizActual].filas, 
                               matrices[matrizActual].columnas);
    int nulidad = calcularNulidad(matrices[matrizActual].datos, 
                                   matrices[matrizActual].filas, 
                                   matrices[matrizActual].columnas);
    
    std::cout << "\n📊 RESULTADOS:" << std::endl;
    std::cout << "  • Rango = " << rango << std::endl;
    std::cout << "    (Número de filas/columnas linealmente independientes)" << std::endl;
    std::cout << "  • Nulidad = " << nulidad << std::endl;
    std::cout << "    (Dimensión del espacio nulo = columnas - rango)" << std::endl;
    std::cout << "\n  • Teorema de Rango-Nulidad: rango + nulidad = " 
              << matrices[matrizActual].columnas << std::endl;
}

/**
 * Opción 19: Descomposición LU
 */
void opcionDescomposicionLU() {
    mostrarEncabezado("DESCOMPOSICIÓN LU (A = L·U)");
    
    if (!matrices[matrizActual].inicializada) {
        std::cout << "⚠ La matriz actual no está inicializada." << std::endl;
        return;
    }
    
    if (!esMatrizCuadrada(matrices[matrizActual].filas, matrices[matrizActual].columnas)) {
        std::cout << "❌ Error: La matriz debe ser cuadrada." << std::endl;
        return;
    }
    
    std::cout << "Matriz original " << matrices[matrizActual].nombre << ":" << std::endl;
    mostrarMatriz(matrices[matrizActual].datos, matrices[matrizActual].filas, 
                  matrices[matrizActual].columnas);
    
    double L[MAX_FILAS][MAX_COLUMNAS];
    double U[MAX_FILAS][MAX_COLUMNAS];
    
    if (descomposicionLU(matrices[matrizActual].datos, L, U, matrices[matrizActual].filas)) {
        std::cout << "\n✅ Matriz L (triangular inferior con unos en diagonal):" << std::endl;
        mostrarMatriz(L, matrices[matrizActual].filas, matrices[matrizActual].filas);
        
        std::cout << "\n✅ Matriz U (triangular superior):" << std::endl;
        mostrarMatriz(U, matrices[matrizActual].filas, matrices[matrizActual].filas);
        
        // Verificar
        double LU[MAX_FILAS][MAX_COLUMNAS];
        multiplicarMatrices(L, U, LU, matrices[matrizActual].filas, 
                            matrices[matrizActual].filas, matrices[matrizActual].filas);
        
        std::cout << "\n🔍 Verificación (L·U debe ser igual a A):" << std::endl;
        if (sonMatricesIguales(LU, matrices[matrizActual].datos, 
                               matrices[matrizActual].filas, matrices[matrizActual].filas)) {
            std::cout << "✅ L·U = A (correcto)" << std::endl;
        } else {
            std::cout << "⚠ L·U ≈ A (pequeñas diferencias por redondeo)" << std::endl;
        }
    } else {
        std::cout << "\n❌ No se pudo calcular la descomposición LU." << std::endl;
        std::cout << "Posiblemente se requiere pivoteo (matriz singular o mal condicionada)." << std::endl;
    }
}

/**
 * Opción 20: Descomposición QR
 */
void opcionDescomposicionQR() {
    mostrarEncabezado("DESCOMPOSICIÓN QR (A = Q·R)");
    
    if (!matrices[matrizActual].inicializada) {
        std::cout << "⚠ La matriz actual no está inicializada." << std::endl;
        return;
    }
    
    std::cout << "Matriz original " << matrices[matrizActual].nombre << ":" << std::endl;
    mostrarMatriz(matrices[matrizActual].datos, matrices[matrizActual].filas, 
                  matrices[matrizActual].columnas);
    
    double Q[MAX_FILAS][MAX_COLUMNAS];
    double R[MAX_FILAS][MAX_COLUMNAS];
    
    descomposicionQRGramSchmidt(matrices[matrizActual].datos, Q, R,
                                 matrices[matrizActual].filas, 
                                 matrices[matrizActual].columnas);
    
    std::cout << "\n✅ Matriz Q (ortogonal):" << std::endl;
    mostrarMatriz(Q, matrices[matrizActual].filas, matrices[matrizActual].columnas);
    
    std::cout << "\n✅ Matriz R (triangular superior):" << std::endl;
    mostrarMatriz(R, matrices[matrizActual].columnas, matrices[matrizActual].columnas);
    
    // Verificar ortogonalidad
    double QtQ[MAX_FILAS][MAX_COLUMNAS];
    double Qtranspuesta[MAX_FILAS][MAX_COLUMNAS];
    calcularTranspuesta(Q, Qtranspuesta, matrices[matrizActual].filas, matrices[matrizActual].columnas);
    multiplicarMatrices(Qtranspuesta, Q, QtQ, matrices[matrizActual].columnas, 
                        matrices[matrizActual].filas, matrices[matrizActual].columnas);
    
    std::cout << "\n🔍 Verificación (Qᵀ·Q debe ser I):" << std::endl;
    mostrarMatriz(QtQ, matrices[matrizActual].columnas, matrices[matrizActual].columnas);
}

/**
 * Opción 21: Valores propios
 */
void opcionValoresPropios() {
    mostrarEncabezado("VALORES PROPIOS (MÉTODO DE POTENCIA)");
    
    if (!matrices[matrizActual].inicializada) {
        std::cout << "⚠ La matriz actual no está inicializada." << std::endl;
        return;
    }
    
    if (!esMatrizCuadrada(matrices[matrizActual].filas, matrices[matrizActual].columnas)) {
        std::cout << "❌ Error: La matriz debe ser cuadrada." << std::endl;
        return;
    }
    
    verificarPropiedadesValoresPropios(matrices[matrizActual].datos, matrices[matrizActual].filas);
}

/**
 * Opción 22: Exponencial de matriz
 */
void opcionExponencial() {
    mostrarEncabezado("EXPONENCIAL DE MATRIZ (eᴬ)");
    
    if (!matrices[matrizActual].inicializada) {
        std::cout << "⚠ La matriz actual no está inicializada." << std::endl;
        return;
    }
    
    if (!esMatrizCuadrada(matrices[matrizActual].filas, matrices[matrizActual].columnas)) {
        std::cout << "❌ Error: La matriz debe ser cuadrada." << std::endl;
        return;
    }
    
    int terminos;
    std::cout << "Número de términos de la serie (recomendado 10-15): ";
    std::cin >> terminos;
    
    std::cout << "\nMatriz original " << matrices[matrizActual].nombre << ":" << std::endl;
    mostrarMatriz(matrices[matrizActual].datos, matrices[matrizActual].filas, 
                  matrices[matrizActual].columnas);
    
    double resultado[MAX_FILAS][MAX_COLUMNAS];
    exponencialMatriz(matrices[matrizActual].datos, resultado, 
                      matrices[matrizActual].filas, terminos);
    
    std::cout << "\n✅ Exponencial e^" << matrices[matrizActual].nombre << ":" << std::endl;
    mostrarMatriz(resultado, matrices[matrizActual].filas, matrices[matrizActual].columnas);
}

// ============================================================================
// FUNCIONES DE APLICACIONES PRÁCTICAS (Opciones 23-25)
// ============================================================================

/**
 * Opción 23: Regresión lineal
 */
void opcionRegresionLineal() {
    mostrarEncabezado("REGRESIÓN LINEAL POR MÍNIMOS CUADRADOS");
    
    int n;
    std::cout << "Número de puntos: ";
    std::cin >> n;
    
    double x[MAX_FILAS], y[MAX_FILAS];
    std::cout << "\nIngrese los puntos (x y):" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "Punto " << i+1 << ": ";
        std::cin >> x[i] >> y[i];
    }
    
    // Mostrar puntos
    std::cout << "\n📊 Puntos ingresados:" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "  (" << x[i] << ", " << y[i] << ")" << std::endl;
    }
    
    double beta0, beta1;
    regresionLineal(x, y, n, beta0, beta1);
    
    std::cout << "\n📈 RESULTADO:" << std::endl;
    std::cout << "  y = " << std::fixed << std::setprecision(4) << beta0 
              << " + " << beta1 << " x" << std::endl;
    
    // Calcular coeficiente de determinación R²
    double yMedia = 0;
    for (int i = 0; i < n; i++) yMedia += y[i];
    yMedia /= n;
    
    double SStot = 0, SSres = 0;
    for (int i = 0; i < n; i++) {
        double yPred = beta0 + beta1 * x[i];
        SStot += (y[i] - yMedia) * (y[i] - yMedia);
        SSres += (y[i] - yPred) * (y[i] - yPred);
    }
    double R2 = 1 - SSres / SStot;
    
    std::cout << "  R² = " << R2 << " (coeficiente de determinación)" << std::endl;
    
    // Mostrar predicciones
    std::cout << "\n🔍 PREDICCIONES:" << std::endl;
    for (int i = 0; i < n; i++) {
        double yPred = beta0 + beta1 * x[i];
        std::cout << "  x=" << x[i] << ": real=" << y[i] 
                  << ", pred=" << yPred 
                  << ", error=" << y[i] - yPred << std::endl;
    }
}

/**
 * Opción 24: Transformación 2D (rotación)
 */
void opcionTransformacion2D() {
    mostrarEncabezado("TRANSFORMACIÓN 2D - ROTACIÓN");
    
    double x, y, angulo;
    std::cout << "Ingrese las coordenadas del punto (x y): ";
    std::cin >> x >> y;
    std::cout << "Ingrese el ángulo de rotación (grados): ";
    std::cin >> angulo;
    
    // Convertir a radianes
    double anguloRad = angulo * 3.14159265358979323846 / 180.0;
    
    double xr, yr;
    transformacionRotacion2D(x, y, anguloRad, xr, yr);
    
    std::cout << "\n📐 RESULTADO:" << std::endl;
    std::cout << "  Punto original: (" << x << ", " << y << ")" << std::endl;
    std::cout << "  Ángulo: " << angulo << "° (" << anguloRad << " rad)" << std::endl;
    std::cout << "  Punto rotado: (" << xr << ", " << yr << ")" << std::endl;
    
    // Verificar distancia al origen (debe conservarse)
    double distOriginal = std::sqrt(x*x + y*y);
    double distRotado = std::sqrt(xr*xr + yr*yr);
    std::cout << "  Distancia al origen original: " << distOriginal << std::endl;
    std::cout << "  Distancia al origen rotado: " << distRotado << std::endl;
    if (std::fabs(distOriginal - distRotado) < TOLERANCIA) {
        std::cout << "  ✅ La rotación conserva la distancia (es una isometría)" << std::endl;
    }
}

/**
 * Opción 25: Cadena de Markov
 */
void opcionCadenaMarkov() {
    mostrarEncabezado("CADENA DE MARKOV");
    
    int n;
    std::cout << "Número de estados: ";
    std::cin >> n;
    
    double P[MAX_FILAS][MAX_COLUMNAS];
    std::cout << "\nIngrese la matriz de transición P (" << n << "×" << n << "):" << std::endl;
    std::cout << "(Cada fila debe sumar 1.0)" << std::endl;
    
    for (int i = 0; i < n; i++) {
        double suma = 0;
        std::cout << "Fila " << i+1 << ": ";
        for (int j = 0; j < n; j++) {
            std::cin >> P[i][j];
            suma += P[i][j];
        }
        if (std::fabs(suma - 1.0) > 0.01) {
            std::cout << "⚠ Advertencia: La fila " << i+1 << " suma " << suma 
                      << " (debería ser 1.0)" << std::endl;
        }
    }
    
    double estadoInicial[MAX_FILAS];
    std::cout << "\nIngrese el vector de probabilidades iniciales (" << n << " elementos):" << std::endl;
    double sumaInicial = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> estadoInicial[i];
        sumaInicial += estadoInicial[i];
    }
    if (std::fabs(sumaInicial - 1.0) > 0.01) {
        std::cout << "⚠ Advertencia: La suma es " << sumaInicial 
                  << " (debería ser 1.0)" << std::endl;
    }
    
    int pasos;
    std::cout << "\nNúmero de pasos a simular: ";
    std::cin >> pasos;
    
    double estadoFinal[MAX_FILAS];
    cadenaMarkov(P, estadoInicial, pasos, estadoFinal, n);
    
    std::cout << "\n📊 RESULTADOS:" << std::endl;
    std::cout << "  Estado inicial: [";
    for (int i = 0; i < n; i++) {
        std::cout << " " << estadoInicial[i];
    }
    std::cout << " ]" << std::endl;
    
    std::cout << "  Después de " << pasos << " pasos: [";
    for (int i = 0; i < n; i++) {
        std::cout << " " << std::fixed << std::setprecision(4) << estadoFinal[i];
    }
    std::cout << " ]" << std::endl;
    
    // Buscar distribución estacionaria (aproximada)
    double Pk[MAX_FILAS][MAX_COLUMNAS];
    potenciaMatriz(P, Pk, n, 100);  // Aproximación a P^∞
    
    std::cout << "\n📈 Distribución estacionaria (aproximada):" << std::endl;
    std::cout << "  [";
    for (int j = 0; j < n; j++) {
        std::cout << " " << std::fixed << std::setprecision(4) << Pk[0][j];
    }
    std::cout << " ] (fila de P^100)" << std::endl;
}

// ============================================================================
// FUNCIONES DE HERRAMIENTAS EDUCATIVAS (Opciones 26-30)
// ============================================================================

/**
 * Opción 26: Ejecutar pruebas exhaustivas
 */
void opcionEjecutarPruebas() {
    mostrarEncabezado("PRUEBAS EXHAUSTIVAS DEL SISTEMA");
    ejecutarTodasLasPruebas();
}

/**
 * Opción 27: Ver conceptos teóricos
 */
void opcionVerConceptos() {
    mostrarEncabezado("CONCEPTOS TEÓRICOS DE MATRICES");
    
    std::cout << "\n📚 1. MATRIZ:" << std::endl;
    std::cout << "   Definición: Arreglo rectangular de números dispuestos en filas y columnas." << std::endl;
    std::cout << "   Notación: A = [aᵢⱼ] donde i = 1..m, j = 1..n" << std::endl;
    std::cout << "   Dimensión: m × n (m filas, n columnas)" << std::endl;
    
    std::cout << "\n📚 2. OPERACIONES BÁSICAS:" << std::endl;
    std::cout << "   • Suma: (A + B)ᵢⱼ = Aᵢⱼ + Bᵢⱼ (mismas dimensiones)" << std::endl;
    std::cout << "   • Resta: (A - B)ᵢⱼ = Aᵢⱼ - Bᵢⱼ (mismas dimensiones)" << std::endl;
    std::cout << "   • Multiplicación: (AB)ᵢⱼ = Σₖ Aᵢₖ Bₖⱼ (columnasA = filasB)" << std::endl;
    std::cout << "   • Producto escalar: (cA)ᵢⱼ = c·Aᵢⱼ" << std::endl;
    
    std::cout << "\n📚 3. DETERMINANTE:" << std::endl;
    std::cout << "   • Solo para matrices cuadradas" << std::endl;
    std::cout << "   • det(I) = 1" << std::endl;
    std::cout << "   • det(AB) = det(A)·det(B)" << std::endl;
    std::cout << "   • det(A) ≠ 0 ⇔ A es invertible" << std::endl;
    std::cout << "   • det(Aᵀ) = det(A)" << std::endl;
    
    std::cout << "\n📚 4. MATRIZ INVERSA:" << std::endl;
    std::cout << "   • A·A⁻¹ = A⁻¹·A = I" << std::endl;
    std::cout << "   • (A⁻¹)⁻¹ = A" << std::endl;
    std::cout << "   • (AB)⁻¹ = B⁻¹A⁻¹" << std::endl;
    std::cout << "   • (Aᵀ)⁻¹ = (A⁻¹)ᵀ" << std::endl;
    std::cout << "   • A⁻¹ = (1/det(A))·adj(A)" << std::endl;
    
    std::cout << "\n📚 5. SISTEMAS LINEALES:" << std::endl;
    std::cout << "   • Forma matricial: Ax = b" << std::endl;
    std::cout << "   • Si det(A) ≠ 0: x = A⁻¹b" << std::endl;
    std::cout << "   • Regla de Cramer: xᵢ = det(Aᵢ)/det(A)" << std::endl;
    
    std::cout << "\n📚 6. VALORES PROPIOS:" << std::endl;
    std::cout << "   • Definición: Av = λv, v ≠ 0" << std::endl;
    std::cout << "   • Ecuación característica: det(A - λI) = 0" << std::endl;
    std::cout << "   • La traza es la suma de valores propios" << std::endl;
    std::cout << "   • El determinante es el producto de valores propios" << std::endl;
    
    std::cout << "\n📚 7. RANGO Y NULIDAD:" << std::endl;
    std::cout << "   • Rango: número de filas/columnas linealmente independientes" << std::endl;
    std::cout << "   • Nulidad: dimensión del espacio nulo" << std::endl;
    std::cout << "   • Teorema: rango + nulidad = número de columnas" << std::endl;
}

/**
 * Opción 28: Guardar matriz en archivo
 */
void opcionGuardarMatriz() {
    mostrarEncabezado("GUARDAR MATRIZ EN ARCHIVO");
    
    if (!matrices[matrizActual].inicializada) {
        std::cout << "⚠ La matriz actual no está inicializada." << std::endl;
        return;
    }
    
    char nombreArchivo[100];
    std::cout << "Nombre del archivo (ej: matriz.txt): ";
    std::cin >> nombreArchivo;
    
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cout << "❌ Error: No se pudo crear el archivo." << std::endl;
        return;
    }
    
    // Guardar dimensiones
    archivo << matrices[matrizActual].filas << " " 
            << matrices[matrizActual].columnas << std::endl;
    
    // Guardar datos
    for (int i = 0; i < matrices[matrizActual].filas; i++) {
        for (int j = 0; j < matrices[matrizActual].columnas; j++) {
            archivo << matrices[matrizActual].datos[i][j];
            if (j < matrices[matrizActual].columnas - 1) {
                archivo << " ";
            }
        }
        archivo << std::endl;
    }
    
    archivo.close();
    std::cout << "✅ Matriz guardada en '" << nombreArchivo << "'" << std::endl;
}

/**
 * Opción 29: Cargar matriz desde archivo
 */
void opcionCargarMatriz() {
    mostrarEncabezado("CARGAR MATRIZ DESDE ARCHIVO");
    
    char nombreArchivo[100];
    std::cout << "Nombre del archivo (ej: matriz.txt): ";
    std::cin >> nombreArchivo;
    
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cout << "❌ Error: No se pudo abrir el archivo." << std::endl;
        return;
    }
    
    // Leer dimensiones
    archivo >> matrices[matrizActual].filas >> matrices[matrizActual].columnas;
    
    if (matrices[matrizActual].filas <= 0 || matrices[matrizActual].filas > MAX_FILAS ||
        matrices[matrizActual].columnas <= 0 || matrices[matrizActual].columnas > MAX_COLUMNAS) {
        std::cout << "❌ Error: Dimensiones no válidas en el archivo." << std::endl;
        archivo.close();
        return;
    }
    
    // Leer datos
    for (int i = 0; i < matrices[matrizActual].filas; i++) {
        for (int j = 0; j < matrices[matrizActual].columnas; j++) {
            archivo >> matrices[matrizActual].datos[i][j];
        }
    }
    
    matrices[matrizActual].inicializada = true;
    archivo.close();
    
    std::cout << "✅ Matriz cargada correctamente:" << std::endl;
    mostrarMatriz(matrices[matrizActual].datos, matrices[matrizActual].filas, 
                  matrices[matrizActual].columnas);
}

/**
 * Opción 30: Demostrar propiedades de matrices
 */
void opcionDemostrarPropiedades() {
    mostrarEncabezado("DEMOSTRACIÓN DE PROPIEDADES DE MATRICES");
    
    if (!matrices[matrizActual].inicializada) {
        std::cout << "⚠ La matriz actual no está inicializada." << std::endl;
        return;
    }
    
    if (!esMatrizCuadrada(matrices[matrizActual].filas, matrices[matrizActual].columnas)) {
        std::cout << "⚠ Algunas propiedades requieren matrices cuadradas." << std::endl;
    }
    
    std::cout << "Matriz A = " << matrices[matrizActual].nombre << ":" << std::endl;
    mostrarMatriz(matrices[matrizActual].datos, matrices[matrizActual].filas, 
                  matrices[matrizActual].columnas);
    
    // Propiedad 1: (Aᵀ)ᵀ = A
    double AT[MAX_FILAS][MAX_COLUMNAS];
    double ATT[MAX_FILAS][MAX_COLUMNAS];
    calcularTranspuesta(matrices[matrizActual].datos, AT,
                        matrices[matrizActual].filas, matrices[matrizActual].columnas);
    calcularTranspuesta(AT, ATT, matrices[matrizActual].columnas, matrices[matrizActual].filas);
    
    std::cout << "\n🔍 Propiedad 1: (Aᵀ)ᵀ = A" << std::endl;
    if (sonMatricesIguales(ATT, matrices[matrizActual].datos,
                           matrices[matrizActual].filas, matrices[matrizActual].columnas)) {
        std::cout << "   ✅ (Aᵀ)ᵀ = A (se cumple)" << std::endl;
    } else {
        std::cout << "   ❌ Error en la propiedad" << std::endl;
    }
    
    // Si es cuadrada, más propiedades
    if (esMatrizCuadrada(matrices[matrizActual].filas, matrices[matrizActual].columnas)) {
        double detA = calcularDeterminanteGauss(matrices[matrizActual].datos, 
                                                 matrices[matrizActual].filas);
        
        // Propiedad 2: det(Aᵀ) = det(A)
        double detAT = calcularDeterminanteGauss(AT, matrices[matrizActual].filas);
        std::cout << "\n🔍 Propiedad 2: det(Aᵀ) = det(A)" << std::endl;
        std::cout << "   det(A) = " << detA << ", det(Aᵀ) = " << detAT << std::endl;
        if (std::fabs(detA - detAT) < TOLERANCIA) {
            std::cout << "   ✅ Se cumple la propiedad" << std::endl;
        } else {
            std::cout << "   ❌ No se cumple (error numérico?)" << std::endl;
        }
        
        // Si es invertible, más propiedades
        if (std::fabs(detA) > TOLERANCIA) {
            double invA[MAX_FILAS][MAX_COLUMNAS];
            calcularInversa(matrices[matrizActual].datos, invA, matrices[matrizActual].filas);
            
            // Propiedad 3: det(A⁻¹) = 1/det(A)
            double detInvA = calcularDeterminanteGauss(invA, matrices[matrizActual].filas);
            std::cout << "\n🔍 Propiedad 3: det(A⁻¹) = 1/det(A)" << std::endl;
            std::cout << "   det(A⁻¹) = " << detInvA << ", 1/det(A) = " << 1.0/detA << std::endl;
            if (std::fabs(detInvA - 1.0/detA) < TOLERANCIA) {
                std::cout << "   ✅ Se cumple la propiedad" << std::endl;
            } else {
                std::cout << "   ❌ No se cumple" << std::endl;
            }
        }
    }
}

// ============================================================================
// FUNCIÓN PRINCIPAL
// ============================================================================

int main() {
    // Configuración inicial
    inicializarSistema();
    
    int opcion;
    
    std::cout << "\n" << std::string(100, '★') << std::endl;
    std::cout << "                     BIENVENIDO A LA CALCULADORA EDUCATIVA DE MATRICES" << std::endl;
    std::cout << std::string(100, '★') << std::endl;
    std::cout << "\nDesarrollada para el curso de FUNDAMENTOS DE PROGRAMACIÓN" << std::endl;
    std::cout << "Este programa te ayudará a comprender los conceptos fundamentales" << std::endl;
    std::cout << "del álgebra lineal a través de ejemplos prácticos e interactivos." << std::endl;
    
    do {
        mostrarMenu();
        std::cin >> opcion;
        
        switch(opcion) {
            // Gestión de matrices (1-5)
            case 1: opcionIngresarMatriz(); break;
            case 2: opcionGenerarAleatoria(); break;
            case 3: opcionMostrarMatriz(); break;
            case 4: opcionCambiarMatriz(); break;
            case 5: opcionCopiarMatriz(); break;
            
            // Operaciones básicas (6-15)
            case 6: opcionSumarMatrices(); break;
            case 7: opcionRestarMatrices(); break;
            case 8: opcionMultiplicarMatrices(); break;
            case 9: opcionMultiplicarEscalar(); break;
            case 10: opcionDeterminanteConTeoria(); break;
            case 11: opcionCompararDeterminantes(); break;
            case 12: opcionInversa(); break;
            case 13: opcionTranspuesta(); break;
            case 14: opcionTraza(); break;
            case 15: opcionPotencia(); break;
            
            // Álgebra lineal avanzada (16-22)
            case 16: opcionResolverSistema(); break;
            case 17: opcionClasificarSistema(); break;
            case 18: opcionRangoNulidad(); break;
            case 19: opcionDescomposicionLU(); break;
            case 20: opcionDescomposicionQR(); break;
            case 21: opcionValoresPropios(); break;
            case 22: opcionExponencial(); break;
            
            // Aplicaciones prácticas (23-25)
            case 23: opcionRegresionLineal(); break;
            case 24: opcionTransformacion2D(); break;
            case 25: opcionCadenaMarkov(); break;
            
            // Herramientas educativas (26-30)
            case 26: opcionEjecutarPruebas(); break;
            case 27: opcionVerConceptos(); break;
            case 28: opcionGuardarMatriz(); break;
            case 29: opcionCargarMatriz(); break;
            case 30: opcionDemostrarPropiedades(); break;
            
            // Salir
            case 0: 
                std::cout << "\n" << std::string(100, '★') << std::endl;
                std::cout << "         ¡GRACIAS POR USAR LA CALCULADORA EDUCATIVA DE MATRICES!" << std::endl;
                std::cout << std::string(100, '★') << std::endl;
                std::cout << "\nDesarrollado para el curso de Fundamentos de Programación" << std::endl;
                std::cout << "© 2024 - Todos los conceptos explicados y demostrados" << std::endl;
                break;
                
            default:
                std::cout << "\n❌ Opción no válida. Intente nuevamente (0-30)." << std::endl;
        }
        
        if (opcion != 0) {
            pausa();
        }
        
    } while (opcion != 0);
    
    return 0;
}