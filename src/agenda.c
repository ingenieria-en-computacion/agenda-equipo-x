#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agenda.h"

/* Inicializa la agenda */
void iniciar_agenda(Agenda *agenda){
    if(!agenda) return;
    agenda->num_contactos = 0;
}

/* Lee un contacto desde stdin (entradas básicas, sin validación exhaustiva) */
void leer_contacto(Contacto *c){
    if(!c) return;

    printf("Nombre: ");
    scanf(" %29[^\n]", c->nombre);

    printf("Apellido: ");
    scanf(" %29[^\n]", c->apellido);

    printf("Día de nacimiento (1-31): ");
    scanf("%d", &c->dia);

    printf("Mes de nacimiento (1-12): ");
    {
        int m;
        scanf("%d", &m);
        if (m < 1) m = 1;
        if (m > 12) m = 12;
        c->mes = (enum Mes)(m - 1); // guardamos 0..11
    }

    printf("Teléfono: ");
    scanf(" %24s", c->telefono);

    printf("Tipo de teléfono (0:CASA, 1:MOVIL, 2:OFICINA, 3:OTRO): ");
    {
        int t;
        scanf("%d", &t);
        if (t < 0) t = 0;
        if (t > 3) t = 3;
        c->tipo_tel = (enum TipoTelefono)t;
    }
}

/* Agrega contacto si hay espacio */
void agregar_contacto(Agenda *agenda, Contacto c){
    if(!agenda) return;
    if(agenda->num_contactos >= MAX_CONTACTOS){
        printf("La agenda está llena. No se puede agregar.\n");
        return;
    }
    agenda->contactos[agenda->num_contactos++] = c;
}

/* Muestra representación de enums */
static const char *tipo_telefono_str(enum TipoTelefono t){
    switch(t){
        case CASA: return "CASA";
        case MOVIL: return "MOVIL";
        case OFICINA: return "OFICINA";
        default: return "OTRO";
    }
}
static const char *mes_str(enum Mes m){
    static const char *meses[] = {
        "ENERO","FEBRERO","MARZO","ABRIL","MAYO","JUNIO",
        "JULIO","AGOSTO","SEPTIEMBRE","OCTUBRE","NOVIEMBRE","DICIEMBRE"
    };
    if (m < ENERO || m > DICIEMBRE) return "DESCONOCIDO";
    return meses[m];
}

/* Imprime un contacto */
void mostrar_contacto(Contacto c){
    printf("--------------------------------------------------\n");
    printf("Nombre: %s %s\n", c.nombre, c.apellido);
    printf("Nacimiento: %d de %s\n", c.dia, mes_str(c.mes));
    printf("Teléfono: %s (%s)\n", c.telefono, tipo_telefono_str(c.tipo_tel));
    printf("--------------------------------------------------\n");
}

/* Imprime todos los contactos de la agenda */
void imprimir_agenda(Agenda agenda){
    if(agenda.num_contactos == 0){
        printf("No hay contactos.\n");
        return;
    }
    for(int i = 0; i < agenda.num_contactos; i++){
        mostrar_contacto(agenda.contactos[i]);
    }
}

/* Busca por nombre (coincidencia exacta en campo nombre). Devuelve índice o -1 */
int buscar_contacto(Agenda *agenda, char *nombre){
    if(!agenda || !nombre) return -1;
    for(int i = 0; i < agenda->num_contactos; i++){
        if(strcmp(agenda->contactos[i].nombre, nombre) == 0)
            return i;
    }
    return -1;
}

/* Busca por telefono (coincidencia exacta). Devuelve índice o -1 */
int buscar_contacto_x_telefono(Agenda *agenda, char telefono[]){
    if(!agenda || !telefono) return -1;
    for(int i = 0; i < agenda->num_contactos; i++){
        if(strcmp(agenda->contactos[i].telefono, telefono) == 0)
            return i;
    }
    return -1;
}

/* Ordenamiento burbuja A->Z por nombre */
void ordenar_contactos(Agenda *agenda){
    if(!agenda) return;
    int n = agenda->num_contactos;
    Contacto tmp;
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(strcmp(agenda->contactos[j].nombre, agenda->contactos[j+1].nombre) > 0){
                tmp = agenda->contactos[j];
                agenda->contactos[j] = agenda->contactos[j+1];
                agenda->contactos[j+1] = tmp;
            }
        }
    }
}

/* Ordenamiento burbuja Z->A por nombre */
void ordenar_contactos_inv(Agenda *agenda){
    if(!agenda) return;
    int n = agenda->num_contactos;
    Contacto tmp;
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(strcmp(agenda->contactos[j].nombre, agenda->contactos[j+1].nombre) < 0){
                tmp = agenda->contactos[j];
                agenda->contactos[j] = agenda->contactos[j+1];
                agenda->contactos[j+1] = tmp;
            }
        }
    }
}

/* Guardar contactos en archivo.
   Formato por línea:
   nombre apellido dia mes_int telefono tipo_tel_int
   Devuelve 0 si OK, distinto de 0 si error. */
int guardar_contactos(Agenda *agenda, const char *filename){
    if(!agenda || !filename) return 1;
    FILE *f = fopen(filename, "w");
    if(!f){
        perror("Error abriendo archivo para guardar");
        return 2;
    }
    for(int i = 0; i < agenda->num_contactos; i++){
        Contacto *c = &agenda->contactos[i];
        /* Escribimos mes como entero 0..11 y tipo_tel como entero */
        fprintf(f, "%s %s %d %d %s %d\n",
                c->nombre,
                c->apellido,
                c->dia,
                (int)c->mes,
                c->telefono,
                (int)c->tipo_tel);
    }
    fclose(f);
    return 0;
}

/* Cargar contactos desde archivo con mismo formato.
   Devuelve 0 si OK, distinto de 0 si error. */
int cargar_contactos(Agenda *agenda, const char *filename){
    if(!agenda || !filename) return 1;
    FILE *f = fopen(filename, "r");
    if(!f){
        perror("Error abriendo archivo para cargar");
        return 2;
    }

    iniciar_agenda(agenda); // reiniciamos la agenda antes de cargar

    Contacto c;
    /* usamos formateo seguro: %29s, %24s */
    while(1){
        int mes_int, tipo_int;
        int r = fscanf(f, " %29s %29s %d %d %24s %d",
                       c.nombre, c.apellido, &c.dia, &mes_int, c.telefono, &tipo_int);
        if(r == EOF) break;
        if(r != 6){
            /* línea corrupta: la ignoramos */
            char buffer[256];
            if(fgets(buffer, sizeof(buffer), f) == NULL) break;
            continue;
        }
        if(mes_int < 0) mes_int = 0;
        if(mes_int > 11) mes_int = 11;
        if(tipo_int < 0) tipo_int = 0;
        if(tipo_int > 3) tipo_int = 3;
        c.mes = (enum Mes)mes_int;
        c.tipo_tel = (enum TipoTelefono)tipo_int;
        if(agenda->num_contactos < MAX_CONTACTOS){
            agenda->contactos[agenda->num_contactos++] = c;
        } else {
            /* Si se llena, detenemos la carga */
            printf("Se alcanzó el máximo de contactos (%d). Se detuvo la carga.\n", MAX_CONTACTOS);
            break;
        }
    }

    fclose(f);
    return 0;
}
