/*
 * blue4-lib.h
 *
 *  Created on: 4/4/2017
 *      Author: alejandrokrumkamp
 */

#ifndef BLUE4_LIB_H_
#define BLUE4_LIB_H_

	/**
	* @NAME: assert
	* @DESC: evalua que dos strings sean iguales
	*/
	void assert(char * aString, char * anotherString);

	/**
	* @NAME: asserti
	* @DESC: evalua que dos ints sean iguales
	*/
	void asserti(int aInt, int anotherInt);

	/**
	* @NAME: charToString
	* @DESC: Pasa un char a un String
	*/
	char* charToString(char element);

	/**
	* @NAME: concat
	* @DESC: concatena n elementos
	*/
	char* concat(int n_args, ...);

	/**
	* @NAME: killme
	* @DESC: mata el proceso actual
	*/
	void killme();

	/**
	* @NAME: obtenerConfiguracion
	* @DESC: devuelve el valor int de un atributo de un archivo de configuracion
	*/
	int obtenerConfiguracion(char *rutaArchivo,char *propiedadConfiguracion);

	/**
	* @NAME: obtenerConfiguracionString
	* @DESC: devuelve el valor string de un atributo de un archivo de configuracion
	*/
	char* obtenerConfiguracionString(char *rutaArchivo,char *propiedadConfiguracion);

	/**
	* @NAME: obtenerConfiguracionArray
	* @DESC: devuelve el valor array de un atributo de un archivo de configuracion
	*/
	char** obtenerConfiguracionArray(char *rutaArchivo,char *propiedadConfiguracion);

	/**
	* @NAME: recvall
	* @DESC: recibe un mensaje a traves de sockets
	*/
	int recvall(int s, char *buf, int *len);

	/**
	* @NAME: rutaAbsoluta
	* @DESC: devuelve la ruta de la carpeta donde se esta ejecutando la carpeta
	* Si esta en /Debug devolvera un nivel mas arriba de la carpeta actual
	*/
	char * rutaAbsoluta();

	/**
	* @NAME: rutaAbsolutaDe
	* @DESC: concatena rutaAbsoluta() con el nombre de archivo pasado por parametro
	*/
	char * rutaAbsolutaDe(char * archivo);

	/**
	* @NAME: sendall
	* @DESC: envia un mensaje a traves de sockets
	*/
	int sendall(int s, char *buf, int *len);

	/**
	* @NAME: test
	* @DESC: imprime por pantalla un string
	*/
	void test(char * aString);

	/**
	* @NAME: testi
	* @DESC: imprime por pantalla un int
	*/
	void testi(int aInt);

#endif /* BLUE4_LIB_H_ */