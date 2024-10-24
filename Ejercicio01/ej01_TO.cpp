#include <QCoreApplication>
#include <QDebug>
#include <vector>
#include <algorithm>
#include <random>

// Función para determinar si un número es primo
bool esPrimo(int num)
{

    if (num <= 1)
        return false;

    for (int i = 2; i * i <= num; ++i)
    {
        // Verifica que no su residuo con un numero distinto de 1 y si mismo sea 0
        if (num % i == 0)
            return false;
    }
    return true;

    /*
    Optimizacion

    if (num <= 1) return false;
    if (num <= 3) return true;

    //Verifica los numeros saltando todos los multiplos de 2 (pares) y 3 ,
    // evitando combinaciones de (2*3) que son evidentemente no primos

    for (int i = 5; i * i <= num; i = i+6) {
        //Verifica que no su residuo con un numero distinto de 1 y si mismo sea 0
        if (num % i == 0) return false;
    }
    return true;

    */
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::vector<int> numeros;

    // Generar números aleatorios Utilizando rand() del 1 al 1000

    for (int i = 0; i < 100; ++i)
    {
        int numeroAleatorio = rand() % 1000 + 1; // Genera un número entre 1 y 1000
        numeros.push_back(numeroAleatorio);
    }

    // Generar Numero aleatorios utilizando
    //   Generador Aletoriedad : Mersenne Twister
    //   Inicializador: random_device{}
    //   Clase: uniform_int_distribution_{}

    /*
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> distribucion(1, 1000); // Genera números entre 1 y 1000

    for (int i = 0; i < 100; ++i) { // Generar 100 números
        numeros.push_back(distribucion(rng));
    }
    */

    // Contar los números primos menores de 1000
    int cantidadPrimos = std::count_if(numeros.begin(), numeros.end(), [](int num)
                                       { return num < 1000 && esPrimo(num); });

    qDebug() << "Cantidad de números primos menores de 1000:" << cantidadPrimos;

    return a.exec();
}
