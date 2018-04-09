// cstyle-callback-example.cpp - Ejemplo de callbacks en estilo C
//
//  Situación:
//
//      Una clase "Caller" permite que otra parte del programa se conecte con con ella
//      mediante un callback.
//
//  Compilar:
//
//      g++ -o cstyle-callback-example cstyle-callback-example
//

#include <iostream>

// Por legibilidad, definimos un alias al tipo de la función de callback.
using CallbackFunction = int (*)(int);
// Las funciones se pasan como puntero, por eso lo de (*).
//
// También se puede hacer así:
// typdef  int (*)(int) CallbackFunction;

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
//  Función de callback
//

int callee(int i)
{
    std::cout << "Callback: Dentro de la función callee1()\n";
    return 10 * i;
}

//------------------------------------------------------------------------

int main()
{
    Caller caller;

    // Conectar el callback. En el estilo C simplemente hay que pasar la función callee().
    caller.connectCallback(callee);
    // Probar el callback.
    caller.test();

    return 0;
}
