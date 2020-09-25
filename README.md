# ComsProgram basic simulation of a ARP comunication
#Compiled with g++ c++17

#The csv reader uses the library boost, use: $brew install boost

#For windows follow: https://www.youtube.com/watch?v=TEF5U1AaIV8


El archivo que se corre es terminal.cpp dentro de este archivo ya se encuentran las pruebas para contestar las preguntas, sin embargo se han hecho algunas modificaciones a ciertas funciones para que pueda ser leíble la información 

display(int numero_columnas)
numero_columnas es un número el cual va a indicar cuántas filas se quieren imprimir, 0 para imprimir todas.

busquedaDia(string palabraABuscar, bool impresion)
busquedaMinpuerto(string palabraABuscar, bool impresion)
busquedaServicio(string palabraABuscar, bool impresion)
busquedaOrdenador(string palabraABuscar, bool impresion)

Para estas 4 funciones se ocupan los mismos parámetros con el mismo tipo:

palabraABuscar: aquí se introduce un string al cual dependiendo de cuál es la función que se aplica va a buscar un dato en cierta columna 

impresión: en este apartado se va a introducir un booleano el cuál va indicar si se quieren imprimir todos los registros que cumplan con la condicional de búsqueda.

Estas funciones regresan el número de veces que se encontró tal condicional.

Para el método de ordenamiento sortByTime() se ocupó el algoritmo Quick sort el cual fue seleccionado ya que es un algoritmo de dividir y conquistar, por lo cual para grandes arreglos es bastante eficiente, otro motivo es que es 1 de los algoritmos más utilizados por la industria e incluso con unas pequeñas modificaciones es el algoritmo predeterminado por la std.

Para el método de búsqueda se ocupo un algoritmo diseñado para formar parte de la familia dividir y conquistar, En el cual se produce una bifurcación dividiendo al arreglo a la mitad, tanto por el lado izquierdo como por el derecho. Debido a esto este algoritmo diseñado tiene una complejidad temporal de O(log(n)). Esta búsqueda funciona como un algoritmo universal, para lograr esto se le pasa una función por parametro que determine la condicional por la cual se va a realizar la búsqueda.

¿Cuántos registros tiene tu archivo?
¿Cuántos récords hay del segundo día registrado? ¿Qué día es este?
¿Alguna de las computadoras pertenece a Jeffrey, Betty, Katherine, Scott, Benjamin, Samuel o Raymond?
¿Cuál es la dirección de la red interna de la compañía?
¿Alguna computadora se llama server.reto.com?
¿Qué servicio de mail utilizan (algunas ideas: Gmail, Hotmail, Outlook, Protonmail)?
Considerando solamente los puertos destino ¿Qué puertos abajo del 1000 se están usando? Lista los puertos e investiga que aplicación/servicio lo utiliza generalmente.


División de trabajo:
Javier Alejandro Martínez Noe:
	
Ricardo Uraga de la Fuente:








