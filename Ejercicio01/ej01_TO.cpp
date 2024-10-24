#include <QCoreApplication>
#include <QDebug>
#include <vector>
#include <algorithm>
#include <random>

// Función para determinar si un número es primo
bool esPrimo(int num) {

    if (num <= 1) return false;

    for (int i = 2; i * i <= num; ++i) {
        //Verifica que no su residuo con un numero distinto de 1 y si mismo sea 0
        if (num % i == 0) return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Generar números aleatorios
    std::vector<int> numeros;
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> distribucion(1, 10000); // Genera números entre 1 y 10000

    for (int i = 0; i < 100; ++i) { // Generar 100 números
        numeros.push_back(distribucion(rng));
    }

    // Contar los números primos menores de 1000
    int cantidadPrimos = std::count_if(numeros.begin(), numeros.end(), [](int num) {
        return num < 1000 && esPrimo(num);
    });

    qDebug() << "Cantidad de números primos menores de 1000:" << cantidadPrimos;


    return a.exec();
}

