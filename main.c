#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
 int idEquipo;
 char nombreEquipo[30];
 int idJugador;
 int nroCamisetaJugador;
 char nombreJugador[30];
 int puntosAnotados;
}stJugadorEquipo;

typedef struct
{
 stJugadorEquipo p;
 struct nodoDoble * siguiente;
 struct nodoDoble * anterior;
}nodoDoble;

nodoDoble * inicLista2();
nodoDoble * crearNodo2(stJugadorEquipo A);
void agregarPrincipio2(nodoDoble ** lista, nodoDoble * nuevo);
nodoDoble * archivoToLista2(char archivo[],nodoDoble * lista);

nodoDoble * buscarUltimo(nodoDoble * lista);
void mostrarListaInver2(nodoDoble * lista);
void mostrarUno(stJugadorEquipo p);

nodoDoble * busquedaUltimoRec2(nodoDoble * lista);
void borrarUltimoNodo2(nodoDoble ** lista);

typedef struct
{
    stJugadorEquipo p;
    struct nodo * siguiente;
}nodo;

nodo * inicLista();
nodo * crearNodo(stJugadorEquipo p);
nodo * agregarPrincipio(nodo * lista, nodo * nuevo);
nodo * agregarEnOrden(nodo * lista, nodo * nuevo);
nodo * equipoToLista(nodo * lista, nodoDoble * lista2, char equipo[]);
void mostrarListaRec(nodo * lista);


void PagoTotal(nodoDoble * lista, int *menos, int * mas);

int main()
{
    nodoDoble * lista2 = inicLista2();
    printf("Lista mostrada invertido:\n");
    lista2 = archivoToLista2("ListadoJugadores.dat",lista2);
    mostrarListaInver2(lista2);

    system("PAUSE");
    system("cls");

    printf("Lista despues de borrar el ultimo nodo:\n");
    borrarUltimoNodo2(&lista2);
    mostrarListaInver2(lista2);

    system("PAUSE");
    system("cls");

    char equip[30];
    printf("Ingrese equipo a buscar: ");
    fflush(stdin);
    gets(equip);
    nodo * lista = inicLista();
    lista = equipoToLista(lista,lista2,equip);
    mostrarListaRec(lista);

    system("PAUSE");
    system("cls");

    int mas = 0;
    int menos = 0;
    PagoTotal(lista2,&menos,&mas);
    printf("\nTotal a pagar a los que hicieron menos de 40 puntos: $%d",menos);
    printf("\nTotal a pagar a los que hicieron mas de 40 puntos:   $%d",mas);
    return 0;
}

/*1. Recorrer el archivo de jugadores y construir con dichos datos una LISTA DOBLEMENTE ENLAZADA de Jugadores.
 Para realizar esto, se deberá:
    • crear la estructura necesaria,
    • inicializar lo que corresponda,
    • y codificar las funciones que sean necesarias, modularizando de forma correcta.
    • Los datos deben ser agregados en el lugar de la lista en el cual resulte más  EFICIENTE realizar el proceso de agregado (al final?, al principio?, o en orden?),
    • y la función que los agrega a la lista debe utilizar como parámetro un PUNTERO DOBLE a la lista.
*/

nodoDoble * inicLista2()
{
    return NULL;
}

nodoDoble * crearNodo2(stJugadorEquipo A)
{
    nodoDoble * nuevo = (nodoDoble*)malloc(sizeof(nodoDoble));
    nuevo->p = A;
    nuevo->siguiente = NULL;
    nuevo->anterior = NULL;
    return nuevo;
}

void agregarPrincipio2(nodoDoble ** lista, nodoDoble * nuevo)
{
    if((*lista)==NULL)
        (*lista) = nuevo;
    else
    {
        (*lista)->anterior = nuevo;
        nuevo->siguiente = (*lista);
        nuevo->anterior = NULL;
        (*lista) = nuevo;
    }
}

nodoDoble * archivoToLista2(char archivo[],nodoDoble * lista)
{
    stJugadorEquipo A;
    nodoDoble * nuevo;
    FILE * archi = fopen(archivo,"rb");
    if(archi!=NULL)
    {
        while(fread(&A,sizeof(stJugadorEquipo),1,archi)>0)
        {
            nuevo = crearNodo2(A);
            agregarPrincipio2(&lista,nuevo);
        }
        fclose(archi);
    }
    return lista;
}

/*2. Hacer una función que muestre la LISTA DOBLEMENTE ENLAZADA obtenida en el punto  anterior, modularizando de forma correcta.
    • La lista deberá ser mostrada AL REVÉS de manera ITERATIVA. Para ello, pensar  qué parámetros deberá recibir.
*/

nodoDoble * buscarUltimo(nodoDoble * lista)
{
    nodoDoble * seg = lista;
    if(seg!=NULL)
    {
        while(seg->siguiente!=NULL)
        {
            seg=seg->siguiente;
        }
    }
    return seg;
}

void mostrarListaInver2(nodoDoble * lista)
{
    nodoDoble * ultimo = buscarUltimo(lista);
    if(ultimo!=NULL)
    {
        while(ultimo!=NULL)
        {
            mostrarUno(ultimo->p);
            ultimo = ultimo->anterior;
        }
    }
}

void mostrarUno(stJugadorEquipo p)
{
    printf("\n **************** JUGADOR **************************** \n");
    printf("\nId del equipo.........................................: %d ", p.idEquipo);
    printf("\nEquipo...................................................: %s ", p.nombreEquipo);
    printf("\nId del Jugador........................................: %d ", p.idJugador);
    printf("\nNro de camiseta del Jugador.................: %d ", p.nroCamisetaJugador);
    printf("\nApellido y nombre del Jugador...............: %s ", p.nombreJugador);
    printf("\nPuntos anotados por el Jugador.............: %d \n\n", p.puntosAnotados);
}

/*3. En relación a la LISTA DOBLEMENTE ENLAZADA obtenida en el punto anterior debemos realizar lo siguiente:
    • Una función auxiliar RECURSIVA que busque el ultimo nodo de la lista
    • Una función principal que reciba por parámetro un PUNTERO DOBLE a la lista, invoque a la anterior, y borre el último nodo de la lista.
*/

nodoDoble * busquedaUltimoRec2(nodoDoble * lista)
{
    nodoDoble * ulti;
    if(lista==NULL)
        ulti = NULL;
    else
    {
        if(lista->siguiente!=NULL)
            ulti = busquedaUltimoRec2(lista->siguiente);
            else
                ulti = lista;
    }
    return ulti;
}

void borrarUltimoNodo2(nodoDoble ** lista)
{
    nodoDoble * ulti = busquedaUltimoRec2(*lista);
    if((*lista)!=NULL)
    {
       nodoDoble * aBorrar = ulti;
       ulti = ulti->anterior;
       if(ulti!=NULL)
            ulti->siguiente = NULL;
        free(aBorrar);
    }
}

/*4. Para poder analizar información de cada equipo por separado, debemos codificar las funciones
    necesarias para poder generar una LISTA SIMPLEMENTE ENLAZADA con todos los
    jugadores de la Lista doblemente enlazada que pertenezcan a un equipo a elección del
    usuario del sistema (sin borrar los mismos de la Lista Doble original). Para ello se deberá:
        • crear la estructura necesaria,
        • inicializar lo que corresponda,
        • y codificar las funciones que sean necesarias, modularizando de forma correcta..
        • Los jugadores deberán ser agregados a la Lista Simple ordenados de menor a mayor de acuerdo a su cantidad de puntos anotados.
*/

nodo * inicLista()
{
    return NULL;
}

nodo * crearNodo(stJugadorEquipo p)
{
    nodo * nuevo = (nodo*)malloc(sizeof(nodo));
    nuevo->p = p;
    nuevo->siguiente = NULL;
    return nuevo;
}

nodo * agregarPrincipio(nodo * lista, nodo * nuevo)
{
    if(lista==NULL)
        lista = nuevo;
    else
    {
        nuevo->siguiente = lista;
        lista = nuevo;
    }
    return lista;
}

nodo * agregarEnOrden(nodo * lista, nodo * nuevo)
{
    if(lista==NULL)
        lista = nuevo;
    else
    {
        if(lista->p.puntosAnotados > nuevo->p.puntosAnotados)
            lista = agregarPrincipio(lista,nuevo);
            else
            {
                nodo * seg = lista;
                nodo * ante;
                while(seg!=NULL && seg->p.puntosAnotados < nuevo->p.puntosAnotados)
                {
                    ante = seg;
                    seg = seg->siguiente;
                }
                ante->siguiente = nuevo;
                nuevo->siguiente = seg;
            }
    }
    return lista;
}

nodo * equipoToLista(nodo * lista, nodoDoble * lista2, char equipo[])
{
    nodoDoble * seg2 = lista2;
    nodo * nuevo;
    int i = 0;
    if(seg2!=NULL)
    {
        while(seg2!=NULL)
        {
            if(strcmpi(seg2->p.nombreEquipo,equipo)==0)
            {
                nuevo = crearNodo(seg2->p);
                lista = agregarEnOrden(lista,nuevo);
            }
            seg2 = seg2->siguiente;
        }
    }
    return lista;
}


/*5. Hacer una función que muestre la LISTA SIMPLEMENTE ENLAZADA obtenida en el punto anterior,
    • Deberá modularizarse de forma correcta y teniendo en cuenta el código ya realizado en el punto 2.
    • La función principal deberá ser RECURSIVA
*/

void mostrarListaRec(nodo * lista)
{
    if(lista!=NULL)
    {
        mostrarUno(lista->p);
        mostrarListaRec(lista->siguiente);
    }
}


/*6. A los jugadores se les abona un plus por cada punto anotado:
    • a cada jugador que supere los 40 puntos anotados, se le abonan $5.000 por punto
    • a cada jugador que NO supere los 40 puntos anotados, se le abonan $2.000 por punto
    • En una misma función debemos recorrer por única vez la lista y calcular y retornar
    por separado el total a pagar a quienes superan los 40 puntos y el total a pagar a
    quienes no los superan (pensar cómo devolver ambos valores al Main)

*/

void PagoTotal(nodoDoble * lista, int *menos, int * mas)
{
    nodoDoble * seg = lista;
    if(seg!=NULL)
    {
        while(seg!=NULL)
        {
            if(seg->p.puntosAnotados > 40)
                (*mas) = (*mas) + 5000;
            else
                (*menos) = (*menos) + 2000;

            seg = seg->siguiente;
        }
    }
}
