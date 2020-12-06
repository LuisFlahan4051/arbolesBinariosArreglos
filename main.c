#include <stdio.h>

#define MAX 100

int arbolBusquedaBinaria[MAX];

int buscar(int arbolBusquedaBinaria[], int x, int i)
{
    if (arbolBusquedaBinaria[i] == 0)
    {
        //Busqueda sin exito: en arbolBusquedaBinaria[0]...
        //...se guarda la posicion donde no se encontro x...
        //Lo anterior con el ojbjeto que la funcion insertar...
        //...sepa donde insertar...
        arbolBusquedaBinaria[0] = i;
        return 0;
    }
    
    if (arbolBusquedaBinaria[i] < x)
        return buscar(arbolBusquedaBinaria, x, 2 * i + 1);
    else if (arbolBusquedaBinaria[i] > x)
        return buscar(arbolBusquedaBinaria, x, 2 * i);
    else
        return i;
}

int buscarMin(int arbolBusquedaBinaria[], int i)
{
    int j;
    while (arbolBusquedaBinaria[i] != 0)
    {
        j = arbolBusquedaBinaria[i];
        i = 2 * i;
    }
    return j;
}

int buscarMax(int arbolBusquedaBinaria[])
{
    int i = 1, j;
    while (arbolBusquedaBinaria[i] != 0)
    {
        j = arbolBusquedaBinaria[i];
        i = 2 * i + 1;
    }
    return j;
}

int nodoHoja(int arbolBusquedaBinaria[], int n)
{
    if ((arbolBusquedaBinaria[n * 2 + 1] == 0) && (arbolBusquedaBinaria[n * 2] == 0))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int nodoAux = 0;
int recorrerArbolDerecha(int arbolBusquedaBinaria[], int nodo)
{
    arbolBusquedaBinaria[(nodo / 2) + nodoAux] = arbolBusquedaBinaria[nodo];
    arbolBusquedaBinaria[nodo] = 0;
    printf("\nEL valor del nodo %i ha sido movido al nodo %i", nodo, ((nodo / 2) + nodoAux));
    if (arbolBusquedaBinaria[nodo * 2 + 1] != 0)
    {
        nodoAux++;
        recorrerArbolDerecha(arbolBusquedaBinaria, nodo * 2 + 1);
    }
    nodoAux = 0;
    if (arbolBusquedaBinaria[nodo * 2] != 0)
    {
        recorrerArbolDerecha(arbolBusquedaBinaria, nodo * 2);
    }
    return 1;
}

//Falla dotavía
int recorrerArbolIzquierda(int arbolBusquedaBinaria[], int nodo)
{
    arbolBusquedaBinaria[(nodo / 2) - nodoAux] = arbolBusquedaBinaria[nodo];
    arbolBusquedaBinaria[nodo] = 0;
    printf("\nEL valor del nodo %i ha sido movido al nodo %i", nodo, ((nodo / 2) - nodoAux));
    if (arbolBusquedaBinaria[nodo * 2] != 0)
    {
        nodoAux++;
        recorrerArbolIzquierda(arbolBusquedaBinaria, nodo * 2);
        nodoAux = 0;
    }
    //nodoAux = 0;
    if (arbolBusquedaBinaria[nodo * 2 + 1] != 0)
    {
        recorrerArbolIzquierda(arbolBusquedaBinaria, nodo * 2 + 1);
    }
    return 1;
}

void recorrerNodos(int arbolBusquedaBinaria[], int nodo)
{
    int valorNodoHijoIzquierdo, valorNodoHijoDerecho, nodoMinimoSiguiente;
    valorNodoHijoDerecho = arbolBusquedaBinaria[nodo * 2 + 1];
    valorNodoHijoIzquierdo = arbolBusquedaBinaria[nodo * 2];
    nodoMinimoSiguiente = buscar(arbolBusquedaBinaria, buscarMin(arbolBusquedaBinaria, nodo * 2 + 1), 1);

    if (arbolBusquedaBinaria[nodoMinimoSiguiente * 2 + 1] != 0)
    {
        arbolBusquedaBinaria[nodo] = arbolBusquedaBinaria[nodoMinimoSiguiente];
        recorrerArbolDerecha(arbolBusquedaBinaria, nodoMinimoSiguiente * 2 + 1);
    }
    else
    {
        if (arbolBusquedaBinaria[nodoMinimoSiguiente] != arbolBusquedaBinaria[nodo * 2 + 1])
        {
            arbolBusquedaBinaria[nodo] = arbolBusquedaBinaria[nodoMinimoSiguiente];
            arbolBusquedaBinaria[nodoMinimoSiguiente] = 0;
        }
        else
        {
            arbolBusquedaBinaria[nodo] = arbolBusquedaBinaria[nodo * 2 + 1];
            nodoAux = 0;
            recorrerArbolIzquierda(arbolBusquedaBinaria, (nodo * 2 + 1) * 2 + 1);
        }
    }
}

int eliminarNodo(int arbolBusquedaBinaria[], int nodo, int desde)
{
    if (nodo = buscar(arbolBusquedaBinaria, nodo, desde)) // Existe ?
    {
                if (nodoHoja(arbolBusquedaBinaria, nodo)) // Si no tiene hijos
                {
                    arbolBusquedaBinaria[nodo] = 0;
                    printf("\nNumero del nodo %i ha sido eliminado correctamente.", nodo);
                    printf("\nEs un nodo hoja, estructura correcta!");
                    return 1;
                }
                else
                {
                            //Si tiene solo hijo izquiedo
                            if ((arbolBusquedaBinaria[nodo * 2] != 0) && (arbolBusquedaBinaria[nodo * 2 + 1] == 0))
                            {
                                nodoAux = 0;
                                recorrerArbolDerecha(arbolBusquedaBinaria, nodo * 2);
                            } // Si tiene solo hijo derecho
                            else if ((arbolBusquedaBinaria[nodo * 2 + 1] != 0) && (arbolBusquedaBinaria[nodo * 2] == 0))
                            {
                                nodoAux = 0;
                                recorrerArbolIzquierda(arbolBusquedaBinaria, nodo * 2 + 1);
                            }
                            else
                            { //Tiene ambos hijos
                                recorrerNodos(arbolBusquedaBinaria, nodo);
                            }
                            return 1;
                }
    }
    else
    {
        return 0; // No existe
    }
}

int main()
{
    int i, bandera = 1, n, cantidadNodos = 0, escalon = 0, escalones = 0, aux = 0, e = 0;

    
    printf("\ncuantos nodos tiene tu arbol binario?: ");
    scanf("%i", &n);
    printf("\nDame el arbol: ");
    for (i = 1; i <= n; i++)
        scanf("%i", &arbolBusquedaBinaria[i]);
    
    
    printf("\nElemento minimo: %i", buscarMin(arbolBusquedaBinaria, 1));
    printf("\nElemento maximo: %i", buscarMax(arbolBusquedaBinaria));

    
    //Caso 4. (Extra) IMPRIMIR ARBOL.
    cantidadNodos = n;
    escalon = buscar(arbolBusquedaBinaria, buscarMin(arbolBusquedaBinaria, 1), 1);
    escalones = 0;
    do
    {
        escalon = escalon / 2;
        escalones++;
    } while (escalon >= 2);

    escalones = escalones + 2;

    while (bandera)
    {
        printf("\n\n1.- Buscar un numero:");
        printf("\n2.- Insertar un numero:");
        printf("\n3.- Eliminar un numero:");
        printf("\n4.- imprimir arbol:\n");
        printf("opcion?: ");
        scanf("%i", &n);

        switch (n)
        {
        case 1:
            
            printf("\nDame el numero a buscar: ");
            scanf("%i", &n);
            
            
            if (n = buscar(arbolBusquedaBinaria, n, 1))
                printf("\nEl numero que buscas esta en la posicion: %i\n\n", n);
            else
                printf("\nEl numero no esta y deberia estar en la posicion %i", arbolBusquedaBinaria[0]);
            break;
            
        case 2:
            
            
            printf("\nDame el numero a insertar: ");
            scanf("%i", &i);
            
            if (n = buscar(arbolBusquedaBinaria, i, 1))
            {
                printf("\nEl numero ya se encuentra en la posicion %i: ", n);
            }
            else
            {
                arbolBusquedaBinaria[arbolBusquedaBinaria[0]] = i;
                printf("\nEl numero ha sido correctamente insertado en la posicion %i: ", arbolBusquedaBinaria[0]);
            }
            
            break;
        case 3:
            
            printf("\nDame un numero a eliminar: ");
            scanf("%i", &i);
    
            if (n = eliminarNodo(arbolBusquedaBinaria, i, 1))
            {
                printf("\n\nProceso completado!");
            }
            else
            {
                printf("\nEl numero en el nodo %i. No existe.", arbolBusquedaBinaria[0]);
            }
            
            break;
        case 4:
            
            
            aux = escalones;

            printf("\nArbol:");
            escalon = 1;
            printf("\nNodo:  ");
            for (i = 1; i <= 20; i++)
            {
                printf("%i ", i);
            }
            printf("\nValor: ");
            for (i = 1; i <= 20; i++)
            {
                printf("%i ", arbolBusquedaBinaria[i]);
            }
            printf("\n\n");

            for (i = 1; i <= aux; i++)
            {
                printf("  ");
            }

            for (i = 1; i <= (cantidadNodos * 2 + 1) * 2 + 1; i++)
            {

                printf("%i ", arbolBusquedaBinaria[i]);

                if (i == escalon)
                {
                    printf("\n");
                    escalon = escalon * 2 + 1;
                    aux--;
                    for (e = 1; e <= aux; e++)
                    {
                        printf("  ");
                    }
                }
            }
            break;
        default:
            bandera = 0;
            break;
        }
    }
    getchar();
    return 0;
}

