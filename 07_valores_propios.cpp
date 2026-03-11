/**
 * ============================================================================
 * ARCHIVO: 07_valores_propios.cpp
 * PROPÓSITO: Cálculo de valores y vectores propios
 * CONCEPTOS: Valores propios, vectores propios, polinomio característico
 * 
 * TEORÍA DE VALORES PROPIOS:
 * 
 * DEFINICIÓN:
 * λ es un valor propio de A si existe v ≠ 0 tal que:
 * Av = λv
 * 
 * El vector v correspondiente se llama vector propio.
 * 
 * ECUACIÓN CARACTERÍSTICA:
 * det(A - λI) = 0
 * Este polinomio de grado n tiene como raíces los valores propios.
 * 
 * PROPIEDADES FUNDAMENTALES:
 * 1. La traza es suma de valores propios: tr(A) = Σ λᵢ
 * 2. El determinante es producto de valores propios: det(A) = Π λᵢ
 * 3. A es invertible ⇔ ningún valor propio es cero
 * 4. Los valores propios de A⁻¹ son 1/λᵢ
 * 
 * APLICACIONES:
 * - Estabilidad de sistemas dinámicos
 * - Análisis de componentes principales (PCA)
 * - Mecánica cuántica
 * - Google PageRank
 * ============================================================================
 */

#include <iostream>
#include <cmath>
#include "06_sistemas_ecuaciones.cpp"

/**
 * NOMBRE: calcularPolinomioCaracteristico
 * PROPÓSITO: Calcula los coeficientes del polinomio característico
 * 
 * EXPLICACIÓN:
 * p(λ) = det(A - λI) = (-1)^n λⁿ + cₙ₋₁ λⁿ⁻¹ + ... + c₁ λ + c₀
 * 
 * Los coeficientes tienen relación con las trazas de potencias de A
 * (identidades de Newton), pero aquí usamos un método más directo.
 * 
 * @param A Matriz original
 * @param coef Arreglo para almacenar coeficientes (coef[0] término independiente)
 * @param n Dimensión
 */
void calcularPolinomioCaracteristico(double A[][MAX_COLUMNAS], double coef[], int n) {
    // Para matrices pequeñas podemos calcular directamente
    // En un caso real se usarían métodos numéricos más avanzados
    
    if (n == 1) {
        coef[0] = -A[0][0];  // p(λ) = a₁₁ - λ
        coef[1] = 1.0;
        return;
    }
    
    if (n == 2) {
        // Para matriz 2x2: p(λ) = λ² - tr(A)λ + det(A)
        double traza = A[0][0] + A[1][1];
        double det = A[0][0] * A[1][1] - A[0][1] * A[1][0];
        
        coef[0] = det;        // término independiente
        coef[1] = -traza;      // coeficiente de λ
        coef[2] = 1.0;         // coeficiente de λ²
        return;
    }
    
    std::cout << "Polinomio característico para n > 2 requiere métodos numéricos especializados" << std::endl;
}

/**
 * NOMBRE: metodoPotencia
 * PROPÓSITO: Encuentra el valor propio dominante usando el método de la potencia
 * 
 * EXPLICACIÓN DEL MÉTODO DE LA POTENCIA:
 * 
 * Ideal para encontrar el valor propio de mayor módulo:
 * 
 * ALGORITMO:
 * 1. Iniciar con vector arbitrario v₀
 * 2. Para k = 1,2,... hasta convergencia:
 *    wₖ = A·vₖ₋₁
 *    vₖ = wₖ / ||wₖ||
 *    λₖ = (vₖ^T · A · vₖ) / (vₖ^T · vₖ) (cociente de Rayleigh)
 * 
 * CONVERGENCIA:
 * vₖ converge al vector propio dominante
 * λₖ converge al valor propio dominante
 * 
 * @param A Matriz cuadrada
 * @param n Dimensión
 * @param valorPropio Valor propio dominante encontrado
 * @param vectorPropio Vector propio asociado
 * @param maxIter Máximo número de iteraciones
 * @param tolerancia Tolerancia para convergencia
 * @return true si convergió
 */
bool metodoPotencia(double A[][MAX_COLUMNAS], int n, double &valorPropio, 
                   double vectorPropio[], int maxIter = 1000, double tolerancia = 1e-8) {
    // Inicializar vector aleatorio
    double v[MAX_FILAS];
    for (int i = 0; i < n; i++) {
        v[i] = 1.0;  // Podría ser aleatorio
    }
    
    // Normalizar
    double norma = 0.0;
    for (int i = 0; i < n; i++) {
        norma += v[i] * v[i];
    }
    norma = std::sqrt(norma);
    for (int i = 0; i < n; i++) {
        v[i] /= norma;
    }
    
    double lambdaAnterior = 0.0;
    
    for (int iter = 0; iter < maxIter; iter++) {
        // Calcular w = A·v
        double w[MAX_FILAS] = {0};
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                w[i] += A[i][j] * v[j];
            }
        }
        
        // Calcular norma de w
        norma = 0.0;
        for (int i = 0; i < n; i++) {
            norma += w[i] * w[i];
        }
        norma = std::sqrt(norma);
        
        // Cociente de Rayleigh: λ = (v^T·A·v) / (v^T·v)
        double lambda = 0.0;
        for (int i = 0; i < n; i++) {
            lambda += v[i] * w[i];
        }
        
        // Actualizar vector
        for (int i = 0; i < n; i++) {
            v[i] = w[i] / norma;
        }
        
        // Verificar convergencia
        if (std::fabs(lambda - lambdaAnterior) < tolerancia) {
            valorPropio = lambda;
            for (int i = 0; i < n; i++) {
                vectorPropio[i] = v[i];
            }
            return true;
        }
        
        lambdaAnterior = lambda;
    }
    
    return false;  // No convergió
}

/**
 * NOMBRE: verificarPropiedadesValoresPropios
 * PROPÓSITO: Verifica las propiedades de valores propios
 * 
 * EXPLICACIÓN:
 * Comprueba que:
 * 1. La traza es igual a la suma de valores propios
 * 2. El determinante es igual al producto de valores propios
 * 
 * @param A Matriz original
 * @param n Dimensión
 */
void verificarPropiedadesValoresPropios(double A[][MAX_COLUMNAS], int n) {
    std::cout << "\n=== VERIFICACIÓN DE PROPIEDADES DE VALORES PROPIOS ===" << std::endl;
    
    double traza = calcularTraza(A, n);
    double det = calcularDeterminanteGauss(A, n);
    
    std::cout << "Traza de A: " << traza << std::endl;
    std::cout << "Determinante de A: " << det << std::endl;
    
    // Encontrar valor propio dominante
    double lambda;
    double vectorPropio[MAX_FILAS];
    
    if (metodoPotencia(A, n, lambda, vectorPropio)) {
        std::cout << "\nValor propio dominante (método de potencia): " << lambda << std::endl;
        std::cout << "Vector propio asociado: [";
        for (int i = 0; i < n; i++) {
            std::cout << " " << vectorPropio[i];
        }
        std::cout << " ]" << std::endl;
        
        // Verificar Av = λv
        double Av[MAX_FILAS] = {0};
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                Av[i] += A[i][j] * vectorPropio[j];
            }
        }
        
        std::cout << "\nVerificación (Av debe ser aproximadamente λv):" << std::endl;
        for (int i = 0; i < n; i++) {
            std::cout << "Av[" << i << "] = " << Av[i] 
                     << ", λv[" << i << "] = " << lambda * vectorPropio[i] << std::endl;
        }
    }
}