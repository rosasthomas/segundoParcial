#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "bibliotecaGetsYComprobaciones.h"
#include "Controller.h"
#include "Employee.h"

int main()
{
   int option = 0;
    int flag = 1;
    LinkedList* listaEmpleados = ll_newLinkedList();
    if(listaEmpleados == NULL)
    {
        printf("Error en crear la lista");
        exit(EXIT_FAILURE);
    }
    do
    {
        flag = ll_isEmpty(listaEmpleados);
        option = getIntOnly("Base de empleados\n\n1. Cargar los datos de los empleados .\n"
                            "2. Listar empleados.\n"
                            "3. Calcular sueldo.\n"
                            "4. Generar salida.\n"
                            "5. Salir.\n"
                            "Ingrese una opcion: ");
        switch(option)
        {
        case 1://cargar texto
            if(controller_loadFromText("empleados.csv",listaEmpleados))
            {
                system("cls");
                printf("Se cargo correctamente.\n");
            }
            else
            {
                system("cls");
                printf("No se ha podido cargar.\n");
            }
            break;
        case 2:
            if(flag == 0)
            {
                if(!controller_sortEmployee(listaEmpleados))
                {
                    system("cls");
                    controller_ListEmployee(listaEmpleados);
                }
                else
                {
                    system("cls");
                    printf("No se pudieron ordenar los empleados.\n");
                }
            }
            else
                printf("No se cargaron empleados\n");
            break;
        case 3://sueldo
            if(controller_calcularSueldo(listaEmpleados) == 0)
            {
                system("cls");
                printf("Se calculo el sueldo correctamente.\n");
            }
            else
            {
                system("cls");
                printf("No se ha podido calcular el sueldo.\n");
            }
            break;
        case 4://guardar
             if(flag == 0)
            {
                controller_guardarFiltrado(listaEmpleados);
            }
            else
                printf("No se cargaron empleados\n");
            break;
        case 5:
            option = 5;
            ll_deleteLinkedList(listaEmpleados);
            break;
        default:
            printf("\nLa opcion ingresada no es valida");
        }
        system("pause");
        system("cls");
    }
    while(option != 5);

    return 0;
}
