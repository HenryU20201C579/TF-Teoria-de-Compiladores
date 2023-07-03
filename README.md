# TF-Teoria-de-Compiladores
<div style="width: 100%; clear: both;">
<div style="float: center; width: 50%;">
<img src="/assets/logo-upc.png", align="center" style="height: 150px; width: 400px;>
</div>

<div style="float: right; width: 50%;">
<h5 style="margin: 0; padding-top: 22px; text-align:center;">Trabajo Final </h5>
<h5 style="margin: 0; padding-top: 22px; text-align:center;">Teoría de Compiladores </h5>
<div>
<h5 style="margin: 0; padding-top: 22px; text-align:center;">Integrantes: </h5>

<p>Santisteban Cerna, Jose Mauricio - U201922760</p>
<p>Diaz Huarcaya, Henry Josué - U20201c579</p>
<p>Contreras Inostroza, Eduardo Junior - U201414103</p>
</div>


<h5 style="margin: 0; padding-top: 22px; text-align:center;">Profesor: </h5>
<p style="margin: 0; text-align:center;">Canaval Sánchez, Luis Martin</p>
<p style="margin: 0; text-align:center;">Junio 2023</p>
</div>
<div style="width:100%;">&nbsp;</div>

# Indice
1. [Introducción](#data1)
2. [Marco Teórico](#data2)
3. [Desarrollo ](#data3)
4. [Pruebas](#data4)
5. [Conclusiones](#data5)
6. [Bibliografia](#data6)
7. [Anexos](#data7)

#### 1. Introducción <a name="data1"></a>
Dentro del mundo de los lenguajes de programación existen varios ejemplos llenos de originalidad en cuanto al comportamiento y compilación de su sintexis. Uno de estos referentes es el lenguaje BrainFuck, el cual se compone unicamente de 8 caracteres utilizados para comandar las diferentes funciones que este puede realizar al igual que en cualquier otro lenguaje de programación. Dado que este tipo de lenguajes existen para poner a prueba los compiladores ya existentes, el presente trabajo tiene como objetivo replicar los resultados y la sintaxis detrás de este lenguaje de programación mediante un nuevo compilador.
#### 2. Marco Teórico <a name="data2"></a>
Para la comprensión de lo mencionado en este informe, es preciso definir algunos conceptos.
* Lenguage de programación esotérico: es un lenguaje de programación diseñado para probar los límites del diseño de los lenguajes de programación de los compiladores. Suelen contener una sintaxis radicalmente distinta a los lenguajes de programación tradicionales, y se espera que su uso sea extremadamente escaso. Su principal función es la del entretenimiento. (Academia Lab, s.f.)
* Compilador: es un programa que puede leer un lenguaje fuente y traducirlo a un programa equivalente en lenguaje objetivo. Este se componen de dos partes principales: la de análisis (front end) y síntesis (backend). En la primera se analiza la estructura gramatical del programa fuente y los símbolos utilizados, usando los analizadores léxico, sintáctico y semántico. En la segunda, se genera el código y la optimización en el programa objetivo deseado apartir de lo obtenido en el front end. (Jeffery, C. 2021)

#### 3. Desarrollo <a name="data3"></a>
En una primera instancia hay que especificar cómo funciona la lógica semántica y sintáctica detrás del lenguaje de programación Brainfuck. Este solo utiliza en su gramática 8 comandos específicos, ignorando cualquier otro caracter introducido. Los programas cuentan con un arreglo el cual apunta al inicio y las operaciones se realizan sobre el puntero o sobre el elemento en la posición actual en el arreglo. A continuación se explican estos comandos.
| Comando | Descripción  |
|---|---|
|  > |Aumenta el puntero pasando al siguiente elmento del arreglo   |
|  < | Decrementa el puntero  |
|  + | Incrementa en 1 el valor del elemento de la posición actual  |
|- | Disminuye en 1 el valor del elemento en la posición actual|
| .| Imprime el elemento en la posición actual como caracter ASCII|
| ,| Lee un valor de tipo char y lo almacena en la posición actual|
| [| Si el elemento actual es cero, salta al correspondiente comando ], sino continua con el comando|
| ]| Si el elemento actual es cero, continua con el siguiente comando, sino salta a ] |

Una vez comprendido este apartado, se puede proseguir al desarrollo del programa. En primer lugar, se realizó el siguiente [tutorial](/paso%20a%20paso.docx) para mejor comprensión de cómo utilizar el compilador.
````pyton
1.	Configuración del entorno de desarrollo:
	- Asegúrate de tener instalado CMake y LLVM en tu sistema.
	- Crea un directorio de trabajo para el proyecto.
2.	Creación del archivo CMakeLists.txt:
	- Crea un archivo llamado CMakeLists.txt en el directorio de trabajo.
	- Copia el contenido proporcionado en el archivo CMakeLists.txt.
3.	Compilación del proyecto:
	- Abre una terminal y navega hasta el directorio de trabajo.
	- Ejecuta el comando "cmake ." para generar los archivos de compilación.
	- Ejecuta el comando "make" para compilar el proyecto.
4.	Ejecución del compilador:
	- Después de compilar con éxito, ejecuta el compilador utilizando el comando "./BrainF <archivo_de_entrada>".
	- Reemplaza "<archivo_de_entrada>" con el nombre de un archivo de código fuente BrainF válido que desees compilar.
5.	Prueba del compilador:
	- Crea uno o varios archivos de código fuente BrainF con comandos válidos.
	- Ejecuta el compilador utilizando el paso anterior para compilar los archivos de prueba.
	- Verifica los resultados de la compilación y asegúrate de que se genere el ensamblaje LLVM correctamente.

````
Asimismo, se realizó el siguiente diagrama de clases para mejor comprensión de los elementos que conforman el compilador construido.
<img src="/assets/diagrama de clases.jpeg" style="height: 600px; width:700px"/>

En el archivo [CompilerBF.cpp](/CompilerBF.cpp) se observa el código principal del compilador para el lenguaje BrainFuck.
````c++
#include <iostream>
#include <vector>

// Definición del tamaño de la cinta de memoria
const int TAPE_SIZE = 30000;

// Función para ejecutar un programa Brainfuck
void executeBrainfuck(const std::string& code) {
    std::vector<int> tape(TAPE_SIZE, 0);
    int ptr = 0;
    int codePtr = 0;

    while (codePtr < code.length()) {
        switch (code[codePtr]) {
            case '>':
                ptr++;
                break;
            case '<':
                ptr--;
                break;
            case '+':
                tape[ptr]++;
                break;
            case '-':
                tape[ptr]--;
                break;
            case '.':
                std::cout << static_cast<char>(tape[ptr]);
                break;
            case ',':
                // Ignoramos la entrada del usuario en este ejemplo
                break;
            case '[':
                if (tape[ptr] == 0) {
                    int loopCount = 1;
                    while (loopCount > 0) {
                        codePtr++;
                        if (code[codePtr] == '[')
                            loopCount++;
                        else if (code[codePtr] == ']')
                            loopCount--;
                    }
                }
                break;
            case ']':
                if (tape[ptr] != 0) {
                    int loopCount = 1;
                    while (loopCount > 0) {
                        codePtr--;
                        if (code[codePtr] == ']')
                            loopCount++;
                        else if (code[codePtr] == '[')
                            loopCount--;
                    }
                }
                break;
        }

        codePtr++;
    }
}

int main() {
    std::string brainfuckCode = "++++++++++++++++++++++++++++++++++++++++++++		c1v44 : ASCII code of comma>++++++++++++++++++++++++++++++++			c2v32 : ASCII code of space>++++++++++++++++					c3v11 : quantity of numbers to be calculated>							c4v0  : zeroth Fibonacci number (will not be printed)>+							c5v1  : first Fibonacci number<<							c3    : loop counter[							block : loop to print (i)th number and calculate next one>>							c5    : the number to be printed							block : divide c5 by 10 (preserve c5)>							c6v0  : service zero>++++++++++						c7v10 : divisor<<							c5    : back to dividend[->+>-[>+>>]>[+[-<+>]>+>>]<<<<<<]			c5v0  : divmod algo; results in 0 n d_n%d n%d n/d>[<+>-]							c5    : move dividend back to c5 and clear c6>[-]							c7v0  : clear c7>>							block : c9 can have two digits; divide it by ten again>++++++++++						c10v10: divisor<							c9    : back to dividend[->-[>+>>]>[+[-<+>]>+>>]<<<<<]				c9v0  : another divmod algo; results in 0 d_n%d n%d n/d>[-]							c10v0 : clear c10>>[++++++++++++++++++++++++++++++++++++++++++++++++.[-]]c12v0 : print nonzero n/d (first digit) and clear c12<[++++++++++++++++++++++++++++++++++++++++++++++++.[-]] c11v0 : print nonzero n%d (second digit) and clear c11<<<++++++++++++++++++++++++++++++++++++++++++++++++.[-]	c8v0  : print any n%d (last digit) and clear c8<<<<<<<.>.                                              c1c2  : print comma and space							block : actually calculate next Fibonacci in c6>>[>>+<<-]						c4v0  : move c4 to c6 (don't need to preserve it)>[>+<<+>-]						c5v0  : move c5 to c6 and c4 (need to preserve it)>[<+>-]							c6v0  : move c6 with sum to c5<<<-							c3    : decrement loop counter]<<++...	";

    executeBrainfuck(brainfuckCode);

    return 0;
}
````
#### 4. Pruebas <a name="data4"></a>
Para confirmar el funcionamiento del analizador y el compilador, se realizaron las diferentes pruebas. Estas incluyen operaciones matemáticas básicas ([multiplicación](/multiplicar.cpp), [factoriales](/factorial.bf)), la [impresión de un texto](/profe.bf), y funciones con algo de complejidad y recursividad, como imprimir un arreglo de numeros de forma [ascendete]() o [descente](/descendente.cpp) o la sucesión de [fibonacci](/fibonacci.bf).

<img src="/assets/Pruebas.jpeg" style="height: 500px; width:500px"/>

#### 5. Conclusiones <a name="data5"></a>

* LLVM demuestra ser una poderosa herramienta en el campo de la compilación, brindando flexibilidad, eficiencia y potencial para el desarrollo de lenguajes y tecnologías de vanguardia. El estudio de lenguajes como Brainfuck en combinación con LLVM permite explorar aspectos específicos del diseño de lenguajes y comprensión de máquinas de estado, aportando un enfoque analítico y académico valioso a la investigación en este campo.
  
#### 6. Bibliografía <a name="data6"></a>
* Academia Lab. (s.f.). Lenguaje de Programación Esotérico. Disponible en: https://academia-lab.com/enciclopedia/lenguaje-de-programacion-esoterico/
* Jeffery, C. (2021). Build your own programming language. Packt Publishing. Disponible en: https://learning.oreilly.com/library/view/build-your-own/9781800204805/?ar=

#### 7. Anexos <a name="data7"></a>
[Video de exposición](https://www.youtube.com/watch?v=R-pAsDtIsqY)
