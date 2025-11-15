#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agenda.h"

int main(){
    Agenda agenda;
    iniciar_agenda(&agenda);

    int opcion;
    char nombre_buscar[30];
    char telefono_buscar[25];
    char archivo[256];

    do{
        printf("\n\e[1m\e[0;36m=========== AGENDA ===========\033[0m\e[0m\n");
        printf("1. Agregar contacto\n");
        printf("2. Buscar contacto por nombre\n");
        printf("3. Buscar contacto por telefono\n");
        printf("4. Mostrar todos los contactos\n");
        printf("5. Ordenar A-Z\n");
        printf("6. Ordenar Z-A\n");
        printf("7. Guardar contactos en archivo\n");
        printf("8. Cargar contactos desde archivo\n");
        printf("9. Salir\n");
        printf("Seleccione una opcion: ");
        if(scanf("%d", &opcion) != 1){
            /* Entrada inválida: limpiar stdin y continuar */
            int ch;
            while((ch = getchar()) != '\n' && ch != EOF);
            opcion = 0;
        }

        switch(opcion){
            case 1: {
                Contacto c;
                leer_contacto(&c);
                agregar_contacto(&agenda, c);
                break;
            }
            case 2:
                printf("Nombre a buscar: ");
                scanf(" %29[^\n]", nombre_buscar);
                {
                    int idx = buscar_contacto(&agenda, nombre_buscar);
                    if(idx != -1) mostrar_contacto(agenda.contactos[idx]);
                    else printf("Contacto no encontrado.\n");
                }
                break;
            case 3:
                printf("Telefono a buscar: ");
                scanf(" %24s", telefono_buscar);
                {
                    int idx = buscar_contacto_x_telefono(&agenda, telefono_buscar);
                    if(idx != -1) mostrar_contacto(agenda.contactos[idx]);
                    else printf("Telefono no encontrado.\n");
                }
                break;
            case 4:
                imprimir_agenda(agenda);
                break;
            case 5:
                ordenar_contactos(&agenda);
                printf("Contactos ordenados A-Z.\n");
                break;
            case 6:
                ordenar_contactos_inv(&agenda);
                printf("Contactos ordenados Z-A.\n");
                break;
            case 7:
                printf("Nombre del archivo para guardar: ");
                scanf(" %255s", archivo);
                if(guardar_contactos(&agenda, archivo) == 0)
                    printf("Guardado correctamente en '%s'.\n", archivo);
                else
                    printf("Error al guardar en '%s'.\n", archivo);
                break;
            case 8:
                printf("Nombre del archivo para cargar: ");
                scanf(" %255s", archivo);
                if(cargar_contactos(&agenda, archivo) == 0)
                    printf("Cargado correctamente desde '%s'.\n", archivo);
                else
                    printf("Error al cargar desde '%s'.\n", archivo);
                break;
            case 9:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }

    } while(opcion != 9);

    return 0;
}
