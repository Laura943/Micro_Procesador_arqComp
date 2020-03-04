# Microprocesador

Se crea un repositorio para la simulacion de un microprocesador, producto implementado en la materia de Arquitectura de Computadoras. Se necesita tener instalado SystemC.

# Diseño del MicroProcesador
	![Diseño Microprocesador](https://github.com/Laura943/Micro_Procesador_arqComp/bolb/master/MPR.png)s

# Proceso de Instalacion de SystemC

### Pasos

1.- Instala el paquete **build-essential**, necesario para compilar paquetes de Debian, y que contiene los compiladores gcc/g++. El comando es:

```
$ sudo apt-get install build-essential
```

2.- Crea una carpeta llamada **arq_comp** donde tendrás toda tu información del curso agrupada en un solo sitio, incluida la instalación de System-C. Posicionate dentro de esta carpeta y corre lo siguiente:

```shell
$ wget https://accellera.org/images/downloads/standards/systemc/systemc-2.3.3.tar.gz

### Y luego para descomprimir

$ tar -xvf systemc-2.3.3.tar.gz
```

3.- Accede al directorio `systemc-2.3.3/` y crea un directorio llamado `objdir/`.

4.- Accede a `objdir/` y crea una carpeta en el directorio `/usr/local/`:

```
$ sudo mkdir /usr/local/systemc-2.3.3
```

5.- Desde `objdir/` de nuevo, corre el script que defina la ruta de instalación en el sistema:

```
$ sudo ../configure --prefix=/usr/local/systemc-2.3.3/
```

6.- Ejecuta ahora los siguientes comandos de compilación:

```shell
$ sudo make

### Y luego

$ sudo make install

```

7.- Si no has tenido errores, entonces SystemC debió instalarse de manera correcta en tu sistema. Para probar que esto es cierto, posicionate en `arq_comp/` y crea una carpeta llamada ejemplos. Dentro de dicha carpeta, crea un archivo llamado hello.cpp en el cual agregarás el siguiente código:

```c++
#include <systemc.h>

SC_MODULE (hello_world) {
  SC_CTOR (hello_world) {
  }

  void say_hello() {
    cout << "Hello World SystemC-2.3.3.\n";
  }
};

int sc_main(int argc, char* argv[]) {
  hello_world hello("HELLO");
  hello.say_hello();
  return(0);
}
```

8.- Exporta la variable de entorno que contendrá la dirección de instalación de SystemC:

```shell
export SYSTEMC_HOME=/usr/local/systemc-2.3.3/
```

9.- Compila el código utilizando g++, para ello, utiliza este comando si tu distro es de 64 bits.

```
g++ -I. -I$SYSTEMC_HOME/include -L. -L$SYSTEMC_HOME/lib-linux64 -Wl,-rpath=$SYSTEMC_HOME/lib-linux64 -o hello hello.cpp -lsystemc -lm
```

Si es de 32 bits:

```
g++ -I. -I$SYSTEMC_HOME/include -L. -L$SYSTEMC_HOME/lib-linux -Wl,-rpath=$SYSTEMC_HOME/lib-linux -o hello hello.cpp -lsystemc -lm
```

10.- Corre tu programa. Si no hubo error de ningún tipo, entonces la instalación fue correcta.


# Integrantes
Juan Carrero
Mery Gonzalez
Laura Rosales





