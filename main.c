#include <stdio.h>
#include "funciones.h"

int main (int argc, char *argv[]) {
    int id[5];
    char nombres[5][50];
    float tiempo[5];
    float recurso[5];
    int demanda[5];
    int contP = 0;
    int opc;

    do
    {
        printf("\nOPTIMIZACION DE PRODUCCION\n");
        printf("1. Registrar producto\n");
        printf("2. Mostrar productos\n");
        printf("3. Editar producto\n");
        printf("4. Eliminar producto\n");
        printf("5. Calcular y evaluar produccion\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        opc = validarEnteroRango(1, 6);

        switch (opc)
        {
        case 1:
            registrarProducto(id, nombres, tiempo, recurso, demanda, &contP);
            break;
        case 2:
            if (contP == 0) printf("No hay productos registrados\n");
            else mostrarProductos(id, nombres, tiempo, recurso, demanda, 0, contP);
            break;
        case 3:
            if (contP == 0) printf("No hay productos registrados\n");
            else editarProducto(id, nombres, tiempo, recurso, demanda, contP);
            break;
        case 4:
            if (contP == 0) printf("No hay productos registrados\n");
            else eliminarProducto(id, nombres, tiempo, recurso, demanda, &contP);
            break;
        case 5:
            if (contP == 0) printf("No hay productos registrados\n");
            else calcularProduccion(nombres, tiempo, recurso, demanda, contP);
            break;
        case 6:
            printf("Saliendo del programa...\n");
            break;
        default:
            break;
        }
    } while (opc != 6);

    return 0;
}