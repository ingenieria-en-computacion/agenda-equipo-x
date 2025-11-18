#include "agenda.h"
#include <stdio.h>
#include <string.h>

// ───────────────────────────────────────────────
// Inicializa la agenda
// ───────────────────────────────────────────────
void iniciar_agenda(Agenda *agenda){
    agenda->num_contactos = 0;
}

// Variable que lleva la cuenta de contactos (NO usada)
int num_contactos;

// ───────────────────────────────────────────────
// Agregar contacto
// ───────────────────────────────────────────────
void agregar_contacto(Agenda *agenda, Contacto c){
    if (buscar_contacto_x_telefono(agenda, c.telefono) != -1){
        printf("\n\033[91mYa existe un contacto con ese número telefónico.\033[0m\n\n");
        return;
    }

    if (agenda->num_contactos < MAX_CONTACTOS){
        agenda->contactos[agenda->num_contactos] = c;
        agenda->num_contactos++;
    }
    else{
        printf("\n\033[91mLa agenda está llena, no se puede agregar más contactos.\033[0m\n");
    }
}

// ───────────────────────────────────────────────
// Buscar por nombre
// ───────────────────────────────────────────────
int buscar_contacto(Agenda *agenda, char *nombre){
    for (int i = 0; i < agenda->num_contactos; i++){
        if (strcmp(agenda->contactos[i].nombre, nombre) == 0){
            return i;
        }
    }
    return -1;
}

// ───────────────────────────────────────────────
// Buscar por teléfono
// ───────────────────────────────────────────────
int buscar_contacto_x_telefono(Agenda *agenda, char telefono[]){
    for (int i = 0; i < agenda->num_contactos; i++){
        if (strcmp(agenda->contactos[i].telefono, telefono) == 0){
            return i;
        }
    }
    return -1;
}

// ───────────────────────────────────────────────
// Orden ascendente A → Z
// ───────────────────────────────────────────────
void ordenar_contactos(Agenda *a){
    for (int i = 0; i < a->num_contactos; i++){
        for (int j = 0; j < a->num_contactos - i - 1; j++){
            if (strcmp(a->contactos[j].nombre, a->contactos[j + 1].nombre) > 0){
                Contacto temp = a->contactos[j];
                a->contactos[j] = a->contactos[j + 1];
                a->contactos[j + 1] = temp;
            }
        }
    }
}

// ───────────────────────────────────────────────
// Orden descendente Z → A
// ───────────────────────────────────────────────
void ordenar_contactos_inv(Agenda *a){
    for (int i = 0; i < a->num_contactos; i++){
        for (int j = 0; j < a->num_contactos - i - 1; j++){
            if (strcmp(a->contactos[j].nombre, a->contactos[j + 1].nombre) < 0){
                Contacto temp = a->contactos[j];
                a->contactos[j] = a->contactos[j + 1];
                a->contactos[j + 1] = temp;
            }
        }
    }
}

// ───────────────────────────────────────────────
// Mostrar un contacto
// ───────────────────────────────────────────────
void mostrar_contacto(Contacto c){
    printf("%s|%s|%d|%d|%s|%d\n",c.nombre,c.apellido,c.dia_nacimiento,c.mes_nacimiento,c.telefono,c.tipo_numero);
}

// ───────────────────────────────────────────────
// Leer un contacto desde teclado
// ───────────────────────────────────────────────
void leer_contacto(Contacto *c){
    int valido;
    do{
        int dias_por_mes[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        valido = 1;

        printf("\nIngrese el nombre: ");
        scanf("%s", c->nombre);

        printf("\nIngrese el apellido: ");
        scanf("%s", c->apellido);

        printf("\nIngrese el día de nacimiento: ");
        scanf("%d", &c->dia_nacimiento);

        printf("\nIngrese el mes de nacimiento (1-12): ");
        scanf("%d", (int *)&c->mes_nacimiento);

        printf("\nIngrese el número de teléfono (10 dígitos): ");
        scanf("%s", c->telefono);

        printf("\nIngrese el tipo de número (0-CASA, 1-MOVIL, 2-OFICINA, 3-OTRO): ");
        scanf("%d", (int *)&c->tipo_numero);

        // Validaciones
        if (c->mes_nacimiento < 1 || c->mes_nacimiento > 12){
            printf("\n\033[91mMes fuera de rango.\033[0m\n");
            valido = 0;
        }
        else if (c->dia_nacimiento < 1 || c->dia_nacimiento > dias_por_mes[c->mes_nacimiento - 1]){
            printf("\n\033[91mDía inválido para el mes indicado.\033[0m\n");
            valido = 0;
        }

        if (strlen(c->telefono) != 10){
            printf("\n\033[91mNúmero telefónico inválido (10 dígitos).\033[0m\n");
            valido = 0;
        }

        if (c->tipo_numero < CASA || c->tipo_numero > OTRO){
            printf("\n\033[91mTipo de teléfono inválido.\033[0m\n");
            valido = 0;
        }

        if (!valido)
            printf("\n\033[91mSe encontraron errores. Ingrese los datos nuevamente.\033[0m\n\n");

    } while (!valido);
}

// ───────────────────────────────────────────────
// Imprimir agenda completa
// ───────────────────────────────────────────────
void imprimir_agenda(Agenda agenda){
    if (agenda.num_contactos == 0){
        printf("\n\033[91m~~~~~~~~~ Agenda vacía ~~~~~~~~~\033[0m\n");
        return;
    }

    printf("\n\033[92m~~~~~~~~~ Contactos en agenda ~~~~~~~~~\033[0m\n");
    for (int i = 0; i < agenda.num_contactos; i++){
        mostrar_contacto(agenda.contactos[i]);
    }
}

// ───────────────────────────────────────────────
// Cargar contactos desde archivo
// ───────────────────────────────────────────────
void cargar_contactos(char *filename, Agenda *agenda){
    FILE *file = fopen(filename, "r");
    if (!file){
        printf("\n\033[91mNo se pudo abrir el archivo\033[0m \033[93m%s.txt\033[0m\n", filename);
        return;
    }

    Contacto c;
    while (fscanf(file, "%[^|]|%[^|]|%d|%d|%[^|]|%d\n",c.nombre, c.apellido,&c.dia_nacimiento, (int *)&c.mes_nacimiento,c.telefono, (int *)&c.tipo_numero) == 6){
        agregar_contacto(agenda, c);
    }

    fclose(file);
    printf("\n\033[92mContactos cargados correctamente desde\033[0m \033[93m%s.txt\033[0m\n", filename);
}

// ───────────────────────────────────────────────
// Guardar contactos en archivo
// ───────────────────────────────────────────────
void guardar_contactos(char *filename, Agenda agenda){
    FILE *file = fopen(filename, "w");
    if (!file){
        printf("\n\033[91mNo se pudo abrir el archivo\033[0m \033[93m%s.txt\033[0m\n", filename);
        return;
    }

    for (int i = 0; i < agenda.num_contactos; i++){
        Contacto c = agenda.contactos[i];
        fprintf(file, "%s|%s|%d|%d|%s|%d\n",c.nombre, c.apellido,c.dia_nacimiento, c.mes_nacimiento,c.telefono, c.tipo_numero);
    }

    fclose(file);
    printf("\n\033[92mContactos guardados correctamente en\033[0m \033[93m%s.txt\033[0m\n", filename);
}
