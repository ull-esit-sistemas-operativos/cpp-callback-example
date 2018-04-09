// cpp11-callback-example.cpp - Ejemplo de callbacks en C++11
//
//  Situación:
//
//      Una clase "Caller" permite que otra parte del programa se conecte con con ella
//      mediante un callback.
//
//  Compilar:
//
//      g++ -std=c++11 -o cpp11-callback-example cpp11-callback-example
//

#include <iostream>
#include <functional>       // std::function

// Por legibilidad, definimos un alias al tipo de la función de callback.
using CallbackFunction = std::function<int(int)>;
//
// También se puede hacer así:
// typdef  std::function<int(int)> CallbackFunction;

//
// "Caller" permite conectar un callback y después, cuando lo necesita, llamalo.
//

class Caller
{
public:

    // Los clientes pueden conectar su callback usando esto.
    void connectCallback(CallbackFunction cb) {
        cb_ = cb;
    }

    // Probar el callback para asegurar que funciona.
    void test() {
        std::cout << "Caller::test(): llamando al callback...\n";
        int i = cb_(10);

        std::cout << "Result: " << i << "\n";
    }

private:
    // El callback es proporcionado por el cliente llamando a connectCallback().
    CallbackFunction cb_;
};

//
// Ejemplo 1
//
//  Función de callback
//

int callee1(int i)
{
    std::cout << "Callback: Dentro de la función callee1()\n";
    return 10 * i;
}

//
// Ejemplo 3
//
//
// "Callee" es un clase que imita ser una función.
//

class Callee
{
public:

    Callee(int i) : i_(i) {}

    // La función de callback que Caller llamará.
    int operator ()(int i) {
        std::cout << "Callback: Dentro de la instancia de Callee\n";
        return i_ * i;
    }

private:
    int i_;
};

//------------------------------------------------------------------------

int main()
{
    Caller caller;

    // Ejemplo 1, con una función convencional.

    std::cout << "Ejemplo 1, con una función convencional\n";

    // Conectar el callback. De forma asimilar a cuando se usa el estilo C de pasar punteros
    // a función, simplemente hay que pasar la función callee1().
    caller.connectCallback(callee1);
    // Probar el callback.
    caller.test();

    // Ejemplo 2, con función lambda.

    std::cout << "\nEjemplo 2, con función lambda\n";

    // Conectar el callback. Como antes, pero la función de callback se puede definir de forma
    // en el momento.
    caller.connectCallback([](int i) {
         std::cout << "Callback: Dentro de la función lambda\n";
        return 20 * i;
    });
    // Probar el callback.
    caller.test();

    // Ejemplo 3, con objetos

    std::cout << "\nEjemplo 3, con objetos\n";

    Callee callee3(30);

    // Conectar el callback. Como antes, pero ahora se pasa un objeto Callee que hará de
    // callback.
    caller.connectCallback(callee3);
    // Probar el callback.
    caller.test();

    return 0;
}
