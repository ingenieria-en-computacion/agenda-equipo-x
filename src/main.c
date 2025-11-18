#include <stdio.h>
#include "agenda.h"
#include <locale.h>  

// PROTOTIPO
void mostrar_menu();


int main(){
    setlocale(LC_ALL, "es_MX.UTF-8"); //Solo para soportar caracteres especiales como acentos 

    Agenda agenda;
    iniciar_agenda(&agenda);

    int opcion, pos;
    char nombre[50], telefono[20], archivo[50];
    Contacto c;

    do{
        mostrar_menu();
        scanf("%d", &opcion);

        switch(opcion){

            case 1:
                leer_contacto(&c);
                agregar_contacto(&agenda, c);
                break;

            case 2:
                printf("\nIngrese el nombre a buscar: ");
                scanf("%s", nombre);

                pos = buscar_contacto(&agenda, nombre);
                if (pos != -1) mostrar_contacto(agenda.contactos[pos]);
                else printf("\n\033[91mNo se encontró el contacto.\033[0m\n");
                break;

            case 3:
                printf("\nIngrese el número telefónico: ");
                scanf("%s", telefono);

                pos = buscar_contacto_x_telefono(&agenda, telefono);
                if (pos != -1) mostrar_contacto(agenda.contactos[pos]);
                else printf("\n\033[91mNo se encontró el contacto.\033[0m\n");
                break;

            case 4:
                ordenar_contactos(&agenda);
                break;

            case 5:
                ordenar_contactos_inv(&agenda);
                break;

            case 6:
                imprimir_agenda(agenda);
                break;

            case 7:
                printf("\nArchivo a cargar: ");
                scanf("%s", archivo);
                cargar_contactos(archivo, &agenda);
                break;

            case 8:
                printf("\nArchivo a guardar: ");
                scanf("%s", archivo);
                guardar_contactos(archivo, agenda);
                break;

            case 9:
                printf("\n\033[93mSaliendo...\033[0m\n");
                printf("\n\033[93mGracias por usar la agenda. ¡Hasta luego!\033[0m\n");
                printf("\033[93m______________________________\033[0m\n");
                break;

            default:
                printf("\n\033[91mOpción inválida.\033[0m\n");
        }

    }while(opcion != 9);

    return 0;
}

void mostrar_menu(){
    printf("\n\033[94m~~~~~~~~~ Menú ~~~~~~~~~\033[0m\n");

    printf("1. Agregar contacto\n");
    printf("2. Buscar contacto por nombre\n");
    printf("3. Buscar contacto por número telefónico\n");
    printf("4. Ordenar contactos \033[96m(A-Z)\033[0m\n");
    printf("5. Ordenar contactos \033[96m(Z-A)\033[0m\n");
    printf("6. Mostrar agenda\n");
    printf("7. Cargar contactos desde archivo\n");
    printf("8. Guardar contactos en archivo\n");
    printf("9. Salir\n");
    printf("\033[94mSeleccione una opción: \033[0m");
}
