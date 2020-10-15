# ComsProgram basic simulation of a ARP comunication

# Compiled with g++ c++17

El archivo que se corre es terminal.cpp dentro de este archivo ya se encuentran las pruebas para contestar las preguntas, sin embargo se van hacer algunas preguntas a ciertas funciones para que pueda ser leíble la información

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
38105 registros

¿Cuántos récords hay del segundo día registrado? ¿Qué día es este?
El segundo dia es: 11
El segundo dia hay: 3314 registros

¿Alguna de las computadoras pertenece a Jeffrey, Betty, Katherine, Scott, Benjamin, Samuel o Raymond?
En el registro scott si tiene una compu

¿Cuál es la dirección de la red interna de la compañía?
la Ip local de la red es: 10.8.134

¿Alguna computadora se llama server.reto.com?
No hay un usuario llamado server.reto.com en el registo

¿Qué servicio de mail utilizan (algunas ideas: Gmail, Hotmail, Outlook, Protonmail)?
En el registro se ocupa el servicio: outlook

Considerando solamente los puertos destino ¿Qué puertos abajo del 1000 se están usando? Lista los puertos e investiga que aplicación/servicio lo utiliza generalmente.
Si hay un puerto de destino menor a 1000

Se estan Ocupando los servicios:
aol, outlook, -, finance, investopedia, go, msn, tripadvisor, steampowered, zillow, gamepedia, allrecipes, npr, rottentomatoes, healthline, ca, macys, steamcommunity, paypal, live, lowes, cnet, usatoday, mail, cbssports, genius, usnews, ebay, facebook, homedepot, weather, quizlet, amazon, twitter, wiktionary, youtube, microsoft, linkedin, pinterest, britannica, apple, cnn, bbb, xfinity, glassdoor, etsy, books, mapquest, imdb, wellsfargo, office, ign, washingtonpost, google, accuweather, retailmenot, hulu, yelp, theguardian, yahoo, netflix, webmd, roblox, techradar, foxnews, apartments, instagram, dictionary, espn, wikihow, quora, craigslist, en, bankofamerica, wayfair, fb, medicalnewstoday, nytimes, usps, spotify, bestbuy, play, merriam-webster, chase, fandom, nih, indeed, huffpost, groupon, target, yellowpages, irs, mayoclinic, expedia, businessinsider, forbes, bleacherreport, reddit, urbandictionary, foodnetwork, walmart, mkevjvtfe6dxajlsdfhb, k9oggvetufjky45ogief,

Puertos de destino activos:
443, 993, 53, 67, 465, 80, -, 135, 965,

# Avance 2

Este programa mula la conexión de una red en la que múltiples computadoras se conectan entre sí.

Para hacer esto poble se ocuparon dos tipos de estructuras de datos abstractas, una que almacena todos los registros cómo la fecha la hora a la que se envió la IP el puerto y el host tanto para la conexión de origen y destino.

La otra estructura de datos Almacena las computadoras por las cual es envió una transmisión o se recibió, en esta estructura se se almacena el nombre del host la IP de la computadora y las conexiones que ha realizado Tanto como entrantes como salientes y sus índices. las conexiones entrantes 7 zip io utilizar la estructura de datos de pilas debido a la naturaleza de los requisitos que se tenían “de manera eficiente obtener la última conexión entrante y que permita leerlas desde la última a la primera.” Ya que las pilas tienen una naturaleza de la primera en entrar es la última en salir. para las conexiones salientes se decidió utilizar collapse ya que el requisito era el inverso a las conexiones entrantes, en este se pedía que se leyera desde la primera hasta la última y como la naturaleza de las colas es la primera en entrar es la primera en salir estructura iba a ser perfecta para obtener el resultado esperado.

para poder ordenar y procesar estos datos se decidieron ocupar diferentes algoritmos. Para poder hacer un ordenamiento de los registros se ocupó el algoritmo merge sort ya que este algoritmo tiene una naturaleza de dividir y conquistar y es 1 de los algoritmos más optimizados para trabajar con grandes cantidades de datos, por lo cual le va a permitir a mi programa poder implementarse de manera eficiente en el futuro con una estabilidad constante. Este algoritmo cuenta con una complejidad de O(n log n). Para realizar las búsquedas a través de los registros ocupo una búsqueda por bifurcación, esta funciona similar a una búsqueda binaria pero su diferencia ya sé en qué está bifurca por ambos lados para encontrar el tipo de datos sin importar el orden de la lista. este algoritmo cuenta con una complejidad de O(log n).

Para para poder realizar un análisis de la red se necesitan generar las computadoras, Para este se desarrollaron dos diferentes métodos el primero es computerAnalisis(), el cual genera un análisis completo de toda la red y crea computadoras buscando que no se repitan y si se repiten agrega una conexión a la computadora, este algoritmo debido a las necesidades del problema recorre toda la lista de registros y tiene que hacer una búsqueda en la lista de computadoras para ver si ya hay un precedente de esta computadora debido a esta naturaleza el algoritmo cuenta con una complejidad temporal de O(n log n) constantemente. El otro algoritmo singleConectionAssessment() Realiza el mismo algoritmo que el de ComputerAnalisis sin embargo agrega una capa de filtrado Para solo realizar la búsqueda si se encuentra Una IP deseada en el registro, debido a esto la complejidad temporal en el mejor de los casos es O(n) y en el peor de los casos sí tiene la misma complejidad qué ComputerAnális de O(n log n)

División de trabajo:
Javier Alejandro Martínez Noe:
IP
Hora
Fecha
ADT
terminal
Master:
dayCond
dayBusquedaCond
horaCond
quickSort
partition
busqueda
busquedaArbol
printVector
getAllServicesCond
getActivePortsDestinyCond
getActivePortsOriginCond
numeroDeRegistros
addRegister
sortByTime
Display
busquedaDia
diaRelativo
GetAllServices
getActivePortsDestiny
getActivePortsOrigin
diaRelativo

Ricardo Uraga de la Fuente:
Puerto
HostName
DataBase
CsvReader
Master:
puertoMinBusquedaCond
OrdenadorBusquedaCond
ServicioBusquedaCond
busquedaUsuarioCompletoCond
busquedaServicio
busquedaOrdenador
busquedaUsuarioCompleto
conseguirIpLocal
busquedaMinpuerto
