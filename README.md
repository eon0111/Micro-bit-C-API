# Micro:bit C API

### :bulb: Marco para el desarrollo de aplicaciones C sobre placas Micro:bit

El software, documentación y demás ficheros alojados en este repositorio han sido desarrollados como parte de mi Trabajo Fin de Grado, para el acceso al título de Graduado en Ingeniería Informática por la Universidad de Cantabria.

El proyecto se compone de las siguientes cuatro partes fundamentales:

* Una librería de alto nivel, escrita en el lenguaje C, con la que poder manejar los dispositivos y sensores presentes en la placa de desarrollo Micro:bit
* Las herramientas con que poder compilar y cargar el software desarrollado por medio de la librería
* La documentación asociada a la librería
* El paquete software con que facilitar la instalación tanto de la librería como de las herramientas

### :wrench: Instalación

El script `install.sh` llevará a cabo la instalación del paquete `ubit-1.0-1-amd64.deb` así como sus dependencias (`libpng-dev`), y el conjunto de herramientas empleadas internamente por la herramienta de compilación (`gcc-arm-none-eabi`).
Simplemente deberá ejecutar el script del siguiente modo:

``` bash
sudo ./install.sh
```

### :hammer: Uso de las herramientas

#### Compilación

La herramienta de compilación cruzada `ubit-gcc` admite todas las opciones que pudieran indicarse en un proceso de compilación nativa mediante el compilador `gcc`.

``` bash
ubit-gcc -o [ejecutable] [fuente].c {librerías externas}
```

La herramienta generará un ejecutable en formato `hex` listo para ser cargado en el Micro:bit.

#### Carga de ejecutables

La utilidad `ubit-load` permanecerá a la espera de que se conecte la placa para cargar el ejecutable que se le indique en su memoria flash.
Los ejecutables deberán tener obligatoriamente la extensión `.hex`. De lo contrario, la placa mostrará un error crítico y el código no ejecutará.

``` bash
ubit-load [ejecutable].hex
```
