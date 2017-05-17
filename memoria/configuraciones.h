/*
 * configuraciones.h
 *
 *  Created on: 27/4/2017
 *      Author: utnso
 */

#ifndef CONFIGURACIONES_H_
#define CONFIGURACIONES_H_


typedef struct
{
	char* puerto;
	int marcos;
	int tamMarco;
	int entradasCache;
	int cachePorProceso;
	int retardo;
}t_configMemoria;

t_configMemoria configDeMemoria;
t_configMemoria obtenerDataConfig();

#endif /* CONFIGURACIONES_H_ */
