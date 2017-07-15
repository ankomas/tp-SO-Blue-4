/*
 * primitivasKernel.c
 *
 *  Created on: 13/7/2017
 *      Author: utnso
 */

#include <parser/metadata_program.h>
#include <parser/parser.h>
#include "conexiones.h"
#include "primitivas.h"
#include "primitivasKernel.h"
#include "capaKernel.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

//Semaforos

void dummy_wait(t_nombre_semaforo identificador_semaforo){
	if(finPrograma_global!='Y')
		return;
	char res;
	printf("Llamada a "YEL"WAIT"RESET" %s\n",identificador_semaforo);

	res=semWait(identificador_semaforo);

	switch(res){
	case 'Y':
		return;
	case 'N':
		setExitCode(&pcb_global,"el semaforo no existe",15);
		return;
	case 'B':
		finPrograma_global='B';
		return;
	}
}

void dummy_signal(t_nombre_semaforo identificador_semaforo){
	if(finPrograma_global!='Y')
		return;
	char res;

	printf("Llamada a "YEL"SIGNAL"RESET" %s\n",identificador_semaforo);

	res=semSignal(identificador_semaforo);

	switch(res){
	case 'Y':
		return;
	case 'N':
		setExitCode(&pcb_global,"el semaforo no existe",15);
		return;
	}
}

//Heap

t_puntero dummy_reservar(t_valor_variable espacio){
	if(finPrograma_global!='Y')
		return -1;
	char res;
	t_pos pos;
	t_puntero puntero;
	printf("Llamada a "YEL"RESERVAR"RESET": %i\n",espacio);
	res=alloc(espacio,&puntero);

	switch(res){
	case 'Y':
		pos=punteroAPos(puntero,tamPag_global);
		printf("Puntero: %i (%i,%i,%i)\n",puntero,pos.pag,pos.off,espacio);
		return puntero;
	case 'N':
		setExitCode(&pcb_global,"error al reservar en heap",16);
		return -1;
	default:
		setExitCode(&pcb_global,"error al reservar en heap",16);
		return -1;
	}
}

void dummy_liberar(t_puntero puntero){
	if(finPrograma_global!='Y')
		return;
	t_pos pos=punteroAPos(puntero,tamPag_global);
	char res;

	printf("Llamada a "YEL"LIBERAR"RESET": %i (%i,%i,%i)\n",puntero,pos.pag,pos.off,pos.size);
	res=liberar(puntero);

	switch(res){
	case 'Y':
		return;
	case 'N':
		setExitCode(&pcb_global,"error al liberar en heap",16);
		return;
	default:
		setExitCode(&pcb_global,"error al liberar en heap",16);
		return;
	}
}

//Filesystem

t_descriptor_archivo dummy_abrir(t_direccion_archivo direccion, t_banderas flags){
	if(finPrograma_global!='Y')
		return -1;
	int res;

	printf("Llamada a "YEL"ABRIR"RESET"\n");
	printf("Direccion: %s\n",direccion);
	printf("L: %i E: %i C: %i\n",flags.lectura,flags.escritura,flags.lectura);

	res=abrirArchivo(direccion,flags);

	if(res==-1){
		setExitCode(&pcb_global,"error al abrir archivo",2);
		return -1;
	}
	printf("File descriptor: %i\n",res);
	return res;
}

void dummy_borrar(t_descriptor_archivo descriptor_archivo){
	if(finPrograma_global!='Y')
		return;
	int res;
	printf("Llamada a "YEL"BORRAR"RESET" %i\n",descriptor_archivo);

	res=borrarArchivo(descriptor_archivo);

	if(res==-1){
		setExitCode(&pcb_global,"error al borrar archivo",17);
	}

}

void dummy_cerrar(t_descriptor_archivo descriptor_archivo){
	if(finPrograma_global!='Y')
		return;
	int res;
	printf("Llamada a "YEL"CERRAR"RESET" %i\n",descriptor_archivo);
	return;
	res=cerrarArchivo(descriptor_archivo);

	if(res==-1){
		setExitCode(&pcb_global,"error al cerrar archivo",18);
	}
}

void dummy_moverCursor(t_descriptor_archivo descriptor_archivo, t_valor_variable posicion){
	if(finPrograma_global!='Y')
		return;
	int res;
	printf("Llamada a "YEL"MOVER CURSOR"RESET" %i\n",descriptor_archivo);
	return;
	res=moverCursor(descriptor_archivo,posicion);

	if(res==-1){
		setExitCode(&pcb_global,"error al cerrar archivo",18);
	}

}

void dummy_escribir(t_descriptor_archivo descriptor_archivo, void* informacion, t_valor_variable tamanio){
	if(finPrograma_global!='Y')
		return;
	int res;
	printf("Llamada a "YEL"ESCRIBIR"RESET" %i,%i\n",descriptor_archivo,tamanio);
	res=escribirArchivo(descriptor_archivo,informacion,tamanio);

	if(res==-1){
		setExitCode(&pcb_global,"error al cerrar archivo",18);
	}
}

void dummy_leer(t_descriptor_archivo descriptor_archivo, t_puntero informacion, t_valor_variable tamanio){
	if(finPrograma_global!='Y')
		return;
	printf("Llamada a "YEL"LEER"RESET" %i,%i,%i\n",descriptor_archivo,informacion,tamanio);
	int res;

	res=leerArchivo(descriptor_archivo, tamanio);

	if(res==-1){
		setExitCode(&pcb_global,"error al cerrar archivo",18);
	}
}

t_descriptor_archivo (*AnSISOP_abrir)(t_direccion_archivo direccion, t_banderas flags);
void (*AnSISOP_borrar)(t_descriptor_archivo descriptor_archivo);
void (*AnSISOP_cerrar)(t_descriptor_archivo descriptor_archivo);
void (*AnSISOP_moverCursor)(t_descriptor_archivo descriptor_archivo, t_valor_variable posicion);
void (*AnSISOP_escribir)(t_descriptor_archivo descriptor_archivo, void* informacion, t_valor_variable tamanio);
void (*AnSISOP_leer)(t_descriptor_archivo descriptor_archivo, t_puntero informacion, t_valor_variable tamanio);

