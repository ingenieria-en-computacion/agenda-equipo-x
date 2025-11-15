#ifndef __AGENDA_H__
#define __AGENDA_H__

#include <stdio.h>

#define MAX_CONTACTOS 100

enum TipoTelefono {CASA = 0, MOVIL = 1, OFICINA = 2, OTRO = 3};
enum Mes 
{
    ENERO = 0, FEBRERO = 1, MARZO = 2, ABRIL = 3, MAYO = 4, JUNIO = 5,
    JULIO = 6, AGOSTO = 7, SEPTIEMBRE = 8, OCTUBRE = 9, NOVIEMBRE = 10, 
    DICIEMBRE = 11
};

struct Persona{
    char nombre[30];
    char apellido[30];
    int dia;           // 1..31
    enum Mes mes;      // 0..11
    char telefono[25];
    enum TipoTelefono tipo_tel;
};

typedef struct Persona Contacto;

typedef struct Agenda{
    Contacto contactos[MAX_CONTACTOS];
    int num_contactos; // Lleva la cuenta de cuantos contactos están en la agenda
} Agenda;


/* Inicializa la agenda (num_contactos = 0) */
void iniciar_agenda(Agenda *agenda);

/* Agrega contacto al final (si hay espacio) */
void agregar_contacto(Agenda *agenda, Contacto c);

/* Imprime todos los contactos */
void imprimir_agenda(Agenda agenda);

/* Busca por nombre - devuelve índice o -1 si no existe */
int buscar_contacto(Agenda *agenda, char *nombre);

/* Busca por teléfono - devuelve índice o -1 si no existe */
int buscar_contacto_x_telefono(Agenda *agenda, char telefono[]);

/* Ordenamiento burbuja A->Z por nombre */
void ordenar_contactos(Agenda *agenda);

/* Ordenamiento burbuja Z->A por nombre */
void ordenar_contactos_inv(Agenda *agenda);

/* Muestra un contacto en pantalla */
void mostrar_contacto(Contacto c);

/* Lee los datos de un contacto desde stdin */
void leer_contacto(Contacto *c);

/* Guardar y cargar desde archivo (ahora reciben Agenda *) */
int guardar_contactos(Agenda *agenda, const char *filename);
int cargar_contactos(Agenda *agenda, const char *filename);

#endif // __AGENDA_H__
