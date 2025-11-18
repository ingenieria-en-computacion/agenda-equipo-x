#include "agenda.h"
#include <stdio.h>
#include <string.h>

// Esta función se encarga de iniciar el número de contactos a cero
void iniciar_agenda(Agenda *agenda){
    agenda->num_contactos = 0;
}

// Varible que lleva la cuenta de cuantos contactos hay en la agenda
int num_contactos;

// Esta función sirve para agregar un contacto nuevo en la agenda
void agregar_contacto(Agenda *agenda, Contacto c){
    if (buscar_contacto_x_telefono(agenda, c.telefono) != -1){
    printf("Ya existe un contacto con ese número telefónico.\n\n");
        return;
    }
    if (agenda->num_contactos < MAX_CONTACTOS){
        agenda->contactos[agenda->num_contactos] = c;
        agenda->num_contactos++;
    }
    else{
        printf("La agenda está llena, no se puede agregar más contactos.\n");
    }
}

// Esta función sirve para buscar un contacto por nombre en la agenda y retorna la posición del contacto si exisite
// En caso contrario retorna -1
int buscar_contacto(Agenda *agenda, char *nombre){
    for (int i = 0, j = agenda->num_contactos; i < j; i++){
        if (strcmp(agenda->contactos[i].nombre, nombre) == 0){
            return i;
        }
    }
    return -1;
}

// Esta función  sirve para buscar un contacto por su número de telefono en la agenda
int buscar_contacto_x_telefono(Agenda *agenda, char telefono[]){
    for (int i = 0; i < agenda->num_contactos; i++){
        if (strcmp(agenda->contactos[i].telefono, telefono) == 0){
            return i;
        }
    }
    return -1;
}

// Esta función sirve para ordenar los contactos por nombres de forma ascendente
void ordenar_contactos(Agenda *a){
    int i, j;
    Contacto temp;
    for (i = 0; i < a->num_contactos; i++){
        for (j = 0; j < a->num_contactos - i - 1; j++){
            if (strcmp(a->contactos[j].nombre, a->contactos[j + 1].nombre) > 0){
                temp = a->contactos[j];
                a->contactos[j] = a->contactos[j + 1];
                a->contactos[j + 1] = temp;
            }
        }
    }
}

// Esta función sirve para ordenar los contactos por nombres de forma descendente
void ordenar_contactos_inv(Agenda *a){
    int i, j;
    Contacto temp;
    for (i = 0; i < a->num_contactos; i++){
        for (j = 0; j < a->num_contactos - i - 1; j++){
            if (strcmp(a->contactos[j].nombre, a->contactos[j + 1].nombre) < 0){
                temp = a->contactos[j];
                a->contactos[j] = a->contactos[j + 1];
                a->contactos[j + 1] = temp;
            }
        }
    }
}

// Función auxiliar para imprimir un contacto
void mostrar_contacto(Contacto c){
    printf("%s|%s|%d|%d|%s|%d\n", c.nombre, c.apellido, c.dia_nacimiento, c.mes_nacimiento, c.telefono, c.tipo_numero);
}

// Función auxiliar para leer un contacto
void leer_contacto(Contacto *c){
    int valido;
    do{
        int dias_por_mes[] ={31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        valido = 1;

        printf("Ingrese el nombre: ");
        scanf("%s", c->nombre);
        printf("Ingrese el apellido: ");
        scanf("%s", c->apellido);
        printf("Ingrese el día de nacimiento: ");
        scanf("%d", &c->dia_nacimiento);
        printf("Ingrese el mes de nacimiento (0-11): ");
        scanf("%d", (int *)&c->mes_nacimiento);
        printf("Ingrese el número de teléfono: ");
        scanf("%s", c->telefono);
        printf("Ingrese el tipo de número (0-CASA, 1-MOVIL, 2-OFICINA, 3-OTRO): ");
        scanf("%d", (int *)&c->tipo_numero);

        // Validaciones
        if (c->mes_nacimiento >= ENERO && c->mes_nacimiento <= DICIEMBRE){
            if (c->dia_nacimiento < 1 || c->dia_nacimiento > dias_por_mes[c->mes_nacimiento]){
                printf("Día inválido para el mes indicado.\n");
                valido = 0;
            }
        }
        else{
            printf("Mes fuera de rango.\n");
            valido = 0;
        }

        if (strlen(c->telefono) != 10){
            printf("Número telefónico inválido.\n");
            valido = 0;
        }

        if (c->tipo_numero < CASA || c->tipo_numero > OTRO){
            printf("Tipo de teléfono inválido.\n");
            valido = 0;
        }

        if (!valido)
            printf("\nSe encontraron errores. Ingrese todos los datos nuevamente.\n\n");
    }while (!valido);
}

// Función que imprime todos los contactos de la agenda en pantalla
void imprimir_agenda(Agenda agenda){
    if (agenda.num_contactos == 0){
        printf("~~~ Agenda vacía. ~~~\n");
        return;
    }

    printf("\n~~~ Contactos en agenda ~~~\n");
    for (int i = 0; i < agenda.num_contactos; i++){
        mostrar_contacto(agenda.contactos[i]);
    }
}


// Función que sirve para cargar contactos escritos en un archivo a la agenda
void cargar_contactos(char *filename, Agenda *agenda){
    FILE *file = fopen(filename, "r");
    if (!file){
        printf("No se pudo abrir el archivo %s\n", filename);
        return;
    }

    Contacto c;
    while (fscanf(file, "%[^|]|%[^|]|%d|%d|%[^|]|%d\n",
                  c.nombre,
                  c.apellido,
                  &c.dia_nacimiento,
                  (int *)&c.mes_nacimiento,
                  c.telefono,
                  (int *)&c.tipo_numero) == 6){

        agregar_contacto(agenda, c);
    }

    fclose(file);
    printf("Contactos cargados correctamente desde %s.\n", filename);
}

// Función que sirve para guardar todos los contactos de la agenda en un archivo
void guardar_contactos(char *filename, Agenda agenda){
      FILE *file = fopen(filename, "w");
    if (!file){
        printf("No se pudo abrir el archivo %s \n", filename);
        return;
    }

    for (int i = 0; i < agenda.num_contactos; i++){
        Contacto c = agenda.contactos[i];
        fprintf(file, "%s|%s|%d|%d|%s|%d\n", c.nombre, c.apellido, c.dia_nacimiento, c.mes_nacimiento, c.telefono, c.tipo_numero);
    }

    fclose(file);
    printf("Contactos guardados correctamente en %s.\n", filename);
}
