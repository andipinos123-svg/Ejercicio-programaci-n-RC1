#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "funciones.h"

float validarFloatRango(float a, float b){
    float num;
    int val;
    do
    {
        val = scanf("%f", &num);
        while(getchar() != '\n');

        if (val != 1){
            printf("Error: debe ingresar un numero\n");
        }
        else if (num < a || num > b){
            printf("Error: el valor debe estar entre %.2f y %.2f\n", a, b);
        }

    } while (val != 1 || num < a || num > b);

    return num;
}

int validarEnteroRango(int a, int b){
    float numF;
    int val;
    do
    {
        val = scanf("%f", &numF);
        while(getchar() != '\n');

        if (val != 1){
            printf("Error: debe ingresar un numero entero valido\n");
        }
        else if (numF != (int)numF){
            printf("Error: no puede ingresar decimales, debe ser un numero entero\n");
            val = 0;
        }
        else if ((int)numF < a || (int)numF > b){
            printf("Error: el valor debe estar entre %d y %d\n", a, b);
        }

    } while (val != 1 || numF != (int)numF || (int)numF < a || (int)numF > b);

    return (int)numF;
}

void leercadena(char *cadena, int n){
    fgets(cadena, n, stdin);
    int len = strlen(cadena) - 1;
    cadena[len] = '\0';
}

void limpiarEspacios(char *cadena){
    int inicio = 0;
    int fin = 0;
    int i;

    while (cadena[fin] != '\0'){
        fin++;
    }
    while (fin > 0 && (cadena[fin-1] == ' ' || cadena[fin-1] == '\t')){
        fin--;
    }
    cadena[fin] = '\0';

    while (cadena[inicio] == ' ' || cadena[inicio] == '\t'){
        inicio++;
    }
    if (inicio > 0){
        for (i = 0; i <= fin - inicio; i++){
            cadena[i] = cadena[i + inicio];
        }
    }
}

void leerNombre(char *cadena, int n){
    int vacio;
    do{
        leercadena(cadena, n);
        limpiarEspacios(cadena);
        vacio = (cadena[0] == '\0');
        if (vacio == 1){
            printf("Error: el nombre no puede estar vacio. Intente de nuevo: ");
        }
    } while (vacio == 1);
}

int compararCadenas(char *a, char *b){
    int largoA = 0;
    int largoB = 0

    while (a[largoA] != '\0'){
        largoA++;
    }
    while (b[largoB] != '\0'){
        largoB++;
    }

    if (largoA != largoB){
        return 0;
    }

    for (int i = 0; i < largoA; i++){
        if (tolower((unsigned char)a[i]) != tolower((unsigned char)b[i])){
            return 0;
        }
    }
    return 1;
}

void registrarProducto(int *id, char nombres[][50], float *tiempo, float *recurso, int *demanda, int *contP){
    if (*contP >= 5){
        printf("Error: ya se registraron los 5 productos\n");
        return;
    }
    printf("Ingrese los datos del producto %d:\n", *contP);
    id[*contP] = *contP;
    int repetido;
    do{
        repetido = 0;
        printf("Nombre: ");
        leerNombre(nombres[*contP], 50);
        for (int i = 0; i < *contP; i++){
            if (compararCadenas(nombres[*contP], nombres[i]) == 1){
                repetido = 1;
                printf("Error: ya existe un producto con ese nombre\n");
                break;
            }
        }
    } while (repetido == 1);
    printf("Tiempo de fabricacion por unidad (horas): ");
    tiempo[*contP] = validarFloatRango(0.01, 1000);
    printf("Recursos por unidad: ");
    recurso[*contP] = validarFloatRango(0.01, 10000);
    printf("Cantidad demandada: ");
    demanda[*contP] = validarEnteroRango(1, 100000);
    (*contP)++;
}

void mostrarProductos(int *id, char nombres[][50], float *tiempo, float *recurso, int *demanda, int n, int contP){
    printf("%-4s  %-15s  %-15s  %-15s  %-10s\n", "ID", "Nombre", "Tiempo/u (h)", "Recursos/u", "Demanda");
    for (int i = n; i < contP; i++){
        printf("%-4d  %-15s  %-15.2f  %-15.2f  %-10d\n", id[i], nombres[i], tiempo[i], recurso[i], demanda[i]);
    }
}

void editarProducto(int *id, char nombres[][50], float *tiempo, float *recurso, int *demanda, int contP){
    mostrarProductos(id, nombres, tiempo, recurso, demanda, 0, contP);
    printf("Ingrese el ID del producto a editar (0-%d): ", contP - 1);
    int posicion = validarEnteroRango(0, contP - 1);

    printf("Seleccione el dato a editar 1.Nombre/2.Tiempo/3.Recursos/4.Demanda: ");
    int opc = validarEnteroRango(1, 4);

    switch (opc){
    case 1:{
        char nuevoNombre[50];
        int repetido;
        do{
            repetido = 0;
            printf("Nuevo nombre: ");
            leerNombre(nuevoNombre, 50);
            for (int i = 0; i < contP; i++){
                if (i != posicion && compararCadenas(nuevoNombre, nombres[i]) == 1){
                    repetido = 1;
                    printf("Error: ya existe un producto con ese nombre\n");
                    break;
                }
            }
        } while (repetido == 1);

        strcpy(nombres[posicion], nuevoNombre);
        break;
    }
    case 2:
        printf("Nuevo tiempo de fabricacion por unidad (horas): ");
        tiempo[posicion] = validarFloatRango(0.01, 1000);
        break;
    case 3:
        printf("Nuevos recursos por unidad: ");
        recurso[posicion] = validarFloatRango(0.01, 10000);
        break;
    case 4:
        printf("Nueva cantidad demandada: ");
        demanda[posicion] = validarEnteroRango(1, 100000);
        break;
    }
}

void eliminarProducto(int *id, char nombres[][50], float *tiempo, float *recurso, int *demanda, int *contP){
    mostrarProductos(id, nombres, tiempo, recurso, demanda, 0, *contP);
    printf("Ingrese el ID del producto a eliminar (0-%d): ", *contP - 1);
    int posicion = validarEnteroRango(0, *contP - 1);

    for (int i = posicion; i < *contP - 1; i++){
        strcpy(nombres[i], nombres[i+1]);
        tiempo[i] = tiempo[i+1];
        recurso[i] = recurso[i+1];
        demanda[i] = demanda[i+1];
    }
    (*contP)--;

    for (int i = 0; i < *contP; i++){
        id[i] = i;
    }
    printf("Producto eliminado correctamente\n");
}

void calcularProduccion(char nombres[][50], float *tiempo, float *recurso, int *demanda, int contP){
    float tiempoTotal = 0, recursoTotal = 0;
    float tiempoDisp, recursoDisp;

    printf("Ingrese el tiempo de produccion disponible (horas): ");
    tiempoDisp = validarFloatRango(0, 1000000);
    printf("Ingrese la cantidad de recursos disponibles: ");
    recursoDisp = validarFloatRango(0, 1000000);

    printf("\n%-15s  %-15s  %-15s\n", "Producto", "Tiempo (h)", "Recursos");
    for (int i = 0; i < contP; i++){
        float t = tiempo[i] * demanda[i];
        float r = recurso[i] * demanda[i];
        tiempoTotal = tiempoTotal + t;
        recursoTotal = recursoTotal + r;
        printf("%-15s  %-15.2f  %-15.2f\n", nombres[i], t, r);
    }
    printf("\nTiempo total de fabricacion requerido: %.2f horas\n", tiempoTotal);
    printf("Recursos totales necesarios: %.2f\n", recursoTotal);
    printf("Tiempo disponible: %.2f horas | Recursos disponibles: %.2f\n", tiempoDisp, recursoDisp);

    if (tiempoTotal <= tiempoDisp && recursoTotal <= recursoDisp){
        printf("\nResultado: la fabrica SI puede cumplir con la demanda\n");
        printf("Tiempo sobrante: %.2f horas\n", tiempoDisp - tiempoTotal);
        printf("Recursos sobrantes: %.2f\n", recursoDisp - recursoTotal);
    }else{
        printf("\nResultado: la fabrica NO puede cumplir con la demanda\n");
        if (tiempoTotal > tiempoDisp){
            printf("Faltan %.2f horas de produccion\n", tiempoTotal - tiempoDisp);
        }
        if (recursoTotal > recursoDisp){
            printf("Faltan %.2f unidades de recursos\n", recursoTotal - recursoDisp);
        }
    }
}