#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this;
    this = (LinkedList *)malloc(sizeof(LinkedList));
    if(this != NULL)
    {
        this->size=0;
        this->pFirstNode = NULL;
    }
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
        returnAux = this -> size;
    }

    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
    Node* pNode = NULL;
    int i;
    int len;

    len = ll_len(this);

    if(nodeIndex >= 0 && this != NULL && nodeIndex < len)
    {
        pNode = this-> pFirstNode;
        if(nodeIndex != 0)
        {
            for(i = 0; i < nodeIndex; i++)
            {
                pNode = pNode->pNextNode;
            }
        }
    }

    return pNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    int len = ll_len(this);

    if(this != NULL && nodeIndex >= 0 && nodeIndex <= len)
    {
        Node* pNode = (Node*) calloc(sizeof(Node), 1);

        pNode->pElement = pElement;

        if(nodeIndex == 0)
        {
            pNode->pNextNode = getNode(this, 0);
            this->pFirstNode = pNode;
        }
        else
        {
            Node* pNodeSig = NULL;
            Node* pNodeAnt = NULL;
            int i;

            pNodeSig = this->pFirstNode;

            for(i = 0; i < nodeIndex; i++)
            {
                pNodeAnt = pNodeSig;
                pNodeSig = pNodeSig->pNextNode;
            }

            pNodeAnt->pNextNode = pNode;
            pNode->pNextNode = pNodeSig;
        }
        this->size++;
        returnAux = 0;
    }

    return returnAux;
}


/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if(this != NULL)
    {
        int flag = -1;
        flag = addNode(this, this->size, pElement);
        if(flag != -1)
        {
            returnAux = 0;
        }
    }

    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* nodeAux = NULL;
    int len = ll_len(this);

    if(this != NULL && index >= 0 && index < len)
    {
        nodeAux = getNode(this, index);
        returnAux = nodeAux->pElement;
    }

    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node* nodeAux = NULL;

    int len = ll_len(this);

    if(this != NULL && index >= 0 && index < len)
    {
        nodeAux = getNode(this, index);
        nodeAux->pElement = pElement;
        returnAux = 0;
    }

    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    int len = ll_len(this);

    if (this != NULL && index >= 0 && index < len)
    {
        Node* pNodeAnt = getNode(this, index-1);
        Node* pNode = getNode(this, index);

        if(pNodeAnt != NULL)
        {
            pNodeAnt->pNextNode = pNode->pNextNode;
        }

        free(pNode);
        this -> size--;
        returnAux = 0;
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
        int len = ll_len(this);
        int i;

        for(i = 0; i < len; i++)
        {
            ll_remove(this, i);
        }
        returnAux = 0;
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
        ll_clear(this);
        free(this);
        returnAux = 0;
    }

    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if(this != NULL)
    {
        int len = ll_len(this);
        int i;
        void* pVoidAux;

        for(i = 0; i < len; i++)
        {
            pVoidAux = ll_get(this, i);
            if(pVoidAux == pElement)
            {
                returnAux = i;
                break;
            }
        }
    }

    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
        if(this -> size == 0)
        {
            returnAux = 1;
        }
        else
        {
            returnAux = 0;
        }
    }

    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    int len = ll_len(this);

    if(this != NULL && index >= 0 && index <= len)
    {
        int flag = -1;

        flag = addNode(this, index, pElement);

        if(flag == 0)
        {
            returnAux = 0;
        }
    }

    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    int len = ll_len(this);

    if(this != NULL && index >= 0 && index <= len)
    {
        returnAux = ll_get(this, index);
        ll_remove(this, index);
    }

    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if(this != NULL)
    {
        if(ll_indexOf(this, pElement) == -1)
        {
            returnAux = 0;
        }
        else
        {
            returnAux = 1;
        }

    }

    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;

    if(this != NULL && this2 != NULL)
    {
        returnAux = 1;

        void* pVoid = NULL;
        int i;
        int lenTwo = ll_len(this2);

        for(i = 0; i < lenTwo; i++)
        {
            pVoid = ll_get(this2, i);

            if(!ll_contains(this, pVoid))
            {
                returnAux = 0;
                break;
            }
        }
    }

    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    int len = ll_len(this);

    if(this != NULL && from >= 0 && from < len && to > from && to >= 0 && to <= len)
    {
        cloneArray = ll_newLinkedList();

        if(cloneArray != NULL)
        {
            int i;
            void* pVoidAux = NULL;

            for(i = from; i < to; i++)
            {
                pVoidAux = ll_get(this, i);
                ll_add(cloneArray, pVoidAux);
            }
        }

    }

    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;

    if(this != NULL)
    {
        void* pVoidAux;
        cloneArray = ll_newLinkedList();
        int len = ll_len(this);
        int i;
        for(i = 0; i < len; i ++)
        {
            pVoidAux = ll_get(this, i);
            ll_add(cloneArray, pVoidAux);
        }
    }

    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
     * \param pList LinkedList* Puntero a la lista
     * \param pFunc (*pFunc) Puntero a la funcion criterio
     * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
     * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                    ( 0) Si ok
*/
int ll_sort(LinkedList* this, int (*pFunc)(void*,void*), int order)
{
    int returnAux =-1;

    if(this != NULL && pFunc != NULL && order >= 0 && order <= 1)
    {
        returnAux = 0;
        int i;
        int continuar;
        Node* actualElement = NULL;
        Node * prevElement = NULL;
        void* auxElement = NULL;
        int expected = 1;

        do
        {
            continuar = 0;

            if(order)
            {
                expected = -1;
            }
            int len = ll_len(this);
            for(i = 0; i < len; i++)
            {
                actualElement = getNode(this, i);
                prevElement = getNode(this, i-1);
                if(actualElement != NULL && prevElement != NULL)
                {
                    if(pFunc(actualElement->pElement, prevElement->pElement) == expected)
                    {

                        auxElement = actualElement->pElement;
                        actualElement->pElement = prevElement->pElement;
                        prevElement->pElement = auxElement;
                        continuar = 1;
                    }
                }

            }
        }
        while(continuar);
    }

    return returnAux;

}


/** \brief Filtra los elementos de la lista utilizando la funcion criterio recibida como parametro
     * \param this LinkedList* Puntero a la lista
     * \param pFunc (*pFunc) Puntero a la funcion criterio
     * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_filter(LinkedList* this, int (*pFunc)(void*,int), int aux)
{
    LinkedList* filterList = NULL;

    if(this != NULL)
    {
        filterList = ll_newLinkedList();

        void* pVoid;
        int i;
        int len = ll_len(this);
        for(i = 0; i < len; i++)
        {
            pVoid = ll_get(this, i);
            if(pVoid != NULL)
            {
                if(pFunc(pVoid,aux))
                {
                    ll_add(filterList, pVoid);
                }
            }

        }

    }
    return filterList;
}

int ll_map(LinkedList* this, void* (*pFunc)(void*))
{
    int retorno = -1;

    if(this != NULL)
    {
        void* pVoid;
        void* pVoidAux;
        int i;
        int len = ll_len(this);
        for(i = 0; i < len; i++)
        {
            pVoid = ll_get(this, i);
            if(pVoid != NULL)
            {
                pVoidAux = pFunc(pVoid);
                retorno = ll_set(this, i, pVoidAux);
            }

        }

    }
    return retorno;
}
