#include "agenda.h"
#include <stdio.h>
#include <string.h>

void mostrar_menu();

int main (){
    Agenda agenda;
    iniciar_agenda(&agenda);

    int opcion;
    char nombre[50]; telefono[10]; archivo[50];
}


void mostrar_menu(){
    printf("~~~ Menú ~~~\n");
    printf("1. Agregar contacto\n");
    printf("2. Buscar contacto por nombre\n");
    printf("3. Buscar contacto por número telefónico\n");
    printf("4. Ordenar contactos (A-Z)\n");
    printf("5. Ordenar contactos (Z-A)\n");
    printf("6. Mostrar agenda\n");
    printf("7. Cargar contactos desde archivo\n");
    printf("8. Guardar contactos en archivo\n");
    printf("9. Salir\n");
    printf("Seleccione una opción: ");
}
