// Maestría en Inteligencia Artificial Aplicada
// Tecnológico de Monterrey
// 
// Curso: Computo en la nube
// Profesor titular: Eduardo Antonio Cendejas Castro
// Profesor asistente: Yetnalezi Quintas Ruiz
// 
// Alumno: Luis Gerardo Sánchez Salazar
// Matrícula: A01232963
//
// 26 de enero de 2025
// Tarea 1: Programación de una solución paralela


// Cargar librerias
#include <iostream>
#include <omp.h>

// Definic constantes
#define N 1000
#define chunk 100
#define mostrar 10

// Definir funciones
void imprimeArreglo(int* d);

// Ciclo principal
int main()
{
    // Menasje de inicializacion
    std::cout << ">> Sumando arrays en paralelo\n";
    std::cout << "\n";

#ifdef _OPENMP
    std::cout << ">> OpenMP OK para trabajar...\n";
    std::cout << "\n";
#else
    std::cout << ">> OpenMP no esta listo para trabajar\n";
#endif

    // Desplegar numero de elementos
    std::cout << ">> Numero de elementos por arreglo: " << N << "\n";

    // Crear y llenar arreglos a y b con numeros random
    int a[N], b[N], c[N];
    int i;
    for (i = -0; i < N; i++)
    {
        a[i] = std::rand() % 100 + 1; //numero random del 1 al 100
        b[i] = std::rand() % 10 + 1; //numero random del 1 al 10
    }

    // Configurar programacion paralela para c=a+b
    int pedazos = chunk;
#pragma omp parallel for \
    shared(a,b,c,pedazos) private(i) \
    schedule(static, pedazos)

    // Ciclo for para llenar c (paralelo)
    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];

    // Imprimir valores de los arrays
    std::cout << "\n";
    std::cout << ">> Primeros " << mostrar << " valores del arreglo A: " << std::endl;
    imprimeArreglo(a);

    std::cout << "\n";
    std::cout << ">> Primeros " << mostrar << " valores del arreglo B: " << std::endl;
    imprimeArreglo(b);

    std::cout << "\n";
    std::cout << ">> Primeros " << mostrar << " valores del arreglo C: " << std::endl;
    imprimeArreglo(c);

    //Desplegar todos los valores de los arrays en forma de columna
    std::cout << "\n";
    std::cout << ">> Sumas de los valores de los arrays:";
    std::cout << "\n";
    for (int i = 0; i < N; i++) {
        std::cout << i + 1 << ") A: " << a[i] << " + B: " << b[i] << " = C: " << c[i];
        std::cout << "\n";
    }

}

void imprimeArreglo(int* d)
{
    std::cout << "[";
    for (int x = 0; x < mostrar; x++) {
        std::cout << d[x];
        if (x < mostrar - 1) {
            std::cout << " , ";
        }
    }
    std::cout << " , ... , " << d[N - 1] << "]";
    std::cout << std::endl;
}
