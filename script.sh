#!/bin/bash

#...SECCION DE FUNCIONES

dameProcesos(){
  num_proc=$(ps -a|grep $1|wc -l ) 
  if [ $num_proc -eq 0 ];
  then
    echops -a|grep $1|wc -l
    echo "Lo siento no hay procesos llamados" $1
    exit 
  fi
}
#...dameProcesos()
#...> esta funcion calcula la cantidad,
#...> de procesos.

muestraProcesoConHijos(){
  hijos=0
  for subc in ${id_hijos}; do	
    aux=$(pgrep -P $subc)
    for subd in ${aux} ; do
      hijos=$(($hijos+1))
      echo "soy $subc y tengo $hijos hijos"
    done
    #echo "soy $subc y tengo $hijos hijos"
    hijos=0
  done

}
#...muestraProcesoConHijos()
#...> esta funcion muestra los procesos hijo, apartir del proceso padre.


num_argumentos=$#
if [ $num_argumentos -lt 1 ];
then
    echo "Faltan argumentos: <script><nombre del proceso calcu>"
    exit
fi

#...Mandamos nombre deel proceso a monitorear
echo "Script para monitorear el proceso " $1

#...Obtenemos el numero de procesos calcu
dameProcesos $1
echo "Hay" $num_proc "procesos llamados" $1

#...guardamos el id de cada proceso.
primer_proceso=$(ps -a|grep $1 |head -n 1|awk '{print $1}')
echo "El ID del primer proceso(Padre) " $1 "es " $primer_proceso

#...Mostramos el arbol de procesos antes de crear un clon de "calcu"
echo -e "\nEl arbol de procesos " $1 "antes de crear procesos hijo calcu"
arbol=$(pstree -p $primer_proceso)
echo "$arbol"

#...Mostramos el arbol de procesos antes de la susutitucion y justo cuando se creo o creron hijos.
sleep 5
echo -e "\nEl arbol de procesos " $1 "con hijo o hijos creados"
arbol=$(pstree -p $primer_proceso)
echo "$arbol"

#...Mostrmos el arbol de procesos despues de hacer la susttucion, por el o los procesos expertos.
sleep 5
id_hijos=$(pgrep -P $primer_proceso)
echo -e "\nEl arbol de procesos " $1 "con la susutitucion por el proceso experto" 
arbol=$(pstree -p $primer_proceso)
echo "$arbol"
muestraProcesoConHijos $id_hijos


#...Mostramos el numero maximo de segmentos Totale, de memoria compartida del sistema en bytes.
echo -e "\nEl numero total de segmentos(bytes) del sistema(memoria compartida): " 
echo "$(ipcs -l | grep total|tail -n 2| awk '{print $7}'|head -n 1)"

#...Mostramos el numero maximo de segmentos , memoria compartida que permite crear el sistema a un proceso
echo -e "\nEl numero maximo de segmentos son para un proceso: " 
echo "$(ipcs -l | grep segmentos| awk '{print $5}')"

#...Mostramos el numero maximo de segmentos , memoria compartida que permite crear el sistema a un proceso, en bytes
echo -e "\nEl num. maximo de segmentos son para un proceso(bytes): " 
echo "$( ipcs -l | grep seg.|tail -n 2| awk '{print $6}'|head -n 1)"

#...Mostramos el tamanio de la memoria compartida
echo -e "\nEl Tamanio de la memoria compartida: " 
echo "$(ipcs -p| grep $primer_proceso| head -n 1| awk '{print $1}')"

#...Mostramos el proceso que crea el segmento de memoria compartida
echo -e "\nEl proceso que crea el segmento de memoria compartida: "
echo "$(ipcs -p|grep $primer_proceso|awk '{printf $2}')"

#...Mostramos los prceoso que utilizan la memoria compartida
echo -e "\nLos prceoso que utilizan la memoria compartida: "
echo "$(ipcs -p|grep 33| awk '{print $1}')"