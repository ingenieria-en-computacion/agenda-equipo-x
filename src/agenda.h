#ifndef __AGENDA_H__
#define __AGENDA_H__

#define MAX_CONTACTOS 100

enum TipoTelefono {CASA, MOVIL, OFICINA, OTRO};
enum Mes{ENERO=1, FEBERO, MARZO, ABRIL, MAYO, JUNIO, JULIO, AGOSTO, SEPTIEMBRE, OCTUBRE, NOVIEMBRE, DICIEMBRE};

struct Persona{
    char nombre[30];
    char apellido[30];
    int dia_nacimiento;
    enum Mes mes_nacimiento;
    char telefono[10];
    enum TipoTelefono tipo_numero;
};

typedef struct Persona Contacto;

typedef struct Agenda{
    Contacto contactos[MAX_CONTACTOS];
    int num_contactos; //Lleva la cuenta de cuantos contactos están en la agenda
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
void mostrar_contacto(Contacto);

/* Lee los datos de un contacto desde stdin */
void leer_contacto(Contacto *c);

/* Guardar y cargar desde archivo */
void cargar_contactos(char *filename, Agenda *agenda);
void guardar_contactos(char *filename, Agenda agenda);

#endif // __AGENDA_H_
