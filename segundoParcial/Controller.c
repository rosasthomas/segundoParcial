#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "bibliotecaGetsYComprobaciones.h"
#include "parser.h"
#include "Controller.h"
#include <string.h>


/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path, LinkedList* pArrayListEmployee)
{
    int status = 0;
    FILE * pFile;

    pFile = fopen (path, "r");

    if(pFile != NULL)
    {
        parser_EmployeeFromText(pFile, pArrayListEmployee);
        status = 1;
    }
    else
    {
        printf("\nError en abrir archivo.");
    }

    fclose(pFile);
    return status;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path, LinkedList* pArrayListEmployee)
{
    int status = 0;
    FILE * pFile;

    pFile = fopen (path, "rb");

    if(pFile != NULL)
    {
        parser_EmployeeFromBinary(pFile, pArrayListEmployee);
        status = 1;
    }
    else
    {
        printf("\nError en abrir archivo.");
    }

    fclose(pFile);
    return status;

    return 1;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
    Employee* employee;
    int idAuxInt;
    char idAuxStr[100];
    char nameAux[128];
    char horasAux[100];
    char sueldoAux[100];
    char direccionAux[128];
    int flagSalary = 0;
    int flagHours = 0;
    int status = 0;

    idAuxInt = controller_nextId(pArrayListEmployee);
    itoa(idAuxInt, idAuxStr, 10);
    system("cls");
    printf("ALTA\n\n");
    getStringOnly("Ingrese el nombre: ", nameAux);
    do
    {
        getStringNumber("Ingrese las horas trabajadas: ", horasAux);
        if(!strcmp(horasAux, "0"))
        {
            printf("Las horas no pueden ser menor o igual a 0\n");
            flagHours = 0;
        }
        else
        {
            flagHours = 1;
        }
    }
    while(flagHours != 1);
    do
    {
        getStringNumber("Ingrese el sueldo: ", sueldoAux);
        if(!strcmp(sueldoAux, "0"))
        {
            printf("El sueldo no pueden ser menor o igual a 0\n");
            flagSalary = 0;
        }
        else
        {
            flagSalary = 1;
        }
    }
    while(flagSalary != 1);

    employee = employee_newParametros(idAuxStr, nameAux, horasAux, direccionAux);
    if(employee != NULL)
    {
        ll_add(pArrayListEmployee, employee);
        status = 1;
    }

    return status;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
    int idAux;
    int len;
    int status = 0;
    int flag = 0;
    Employee* employeeAux;
    len = ll_len(pArrayListEmployee);

    system("cls");
    printf("MODIFICAR\n\n");
    controller_ListEmployee(pArrayListEmployee);
    idAux = getIntOnly("\nIngrese la ID a modificar: ");


    int i;
    for(i = 0; i < len; i++)
    {
        employeeAux = ll_get(pArrayListEmployee, i);
        if(idAux == employeeAux->id)
        {
            flag = 1;
            int option;
            system("cls");
            do
            {
                printf("MODIFICAR\n\n");

                employee_ListAnEmployee(employeeAux);
                option = getIntOnly("\n1. Nombre\n2. Horas trabajadas\n3. Sueldo\n4. Salir\nIngrese una opcion: ");
                switch(option)
                {
                case 1:
                    employee_editEmployeeName(employeeAux);
                    status = 1;
                    break;
                case 2:
                    employee_editEmployeeHours(employeeAux);
                    status = 1;
                    break;
                case 3:
                    employee_editEmployeeSalary(employeeAux);
                    status = 1;
                    break;
                case 4:
                    option = 4;
                    status = 1;
                    break;
                default:
                    printf("\nLa opcion ingresada no es valida.");
                }
                system("pause");
                system("cls");
            }
            while(option != 4);
            break;
        }
    }

    if(flag != 1)
    {
        printf("No se encontro el ID.");
    }

    return status;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
    int auxId;
    char choice[2];
    Employee * auxEmployee;
    int flag = 0;
    int len = ll_len(pArrayListEmployee);

    printf("BAJA\n\n");

    controller_ListEmployee(pArrayListEmployee);

    auxId = getIntOnly("Ingrese la ID del empleado a dar de baja: ");

    int i;
    for(i = 0; i < len; i++)
    {
        auxEmployee = ll_get(pArrayListEmployee, i);
        if(auxId == auxEmployee->id)
        {
            flag = 1;
            break;
        }
    }

    if(flag)
    {
        system("cls");
        printf("BAJA\n\n");
        employee_ListAnEmployee(auxEmployee);
        getStringLetters("Esta seguro que desea dar de baja este empleado (S/N)?: ", choice);
    }
    if(!stricmp(choice, "s"))
    {
        ll_remove(pArrayListEmployee, i);
    }

    return flag;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    int i;
    int tam;
    Employee* employee;
    int status = 0;

    tam = ll_len(pArrayListEmployee);
    system("cls");
    printf("LISTAR\n\n");
    printf("ID        NOMBRE     DIRECCION\n");
    for(i = 0; i < tam; i++)
    {
        employee = ll_get(pArrayListEmployee, i);
        printf("%-4d - %10s  - %10s\n", employee->id, employee->nombre, employee->direccion);
        status = 1;
    }
    return status;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
    int status;

     status = ll_sort(pArrayListEmployee, employee_sortByName, 1);

    if(status == -1)
    {
        printf("\n No se pudo ordenar los empleados.\n");
    }

    return status;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path, LinkedList* pArrayListEmployee)
{
    FILE* pFile;
    int i;
    int tam;
    int status = 0;

    pFile = fopen(path, "w");
    if(pFile != NULL && pArrayListEmployee != NULL)
    {
        tam = ll_len(pArrayListEmployee);
        fprintf(pFile, "id,nombre,horasTrabajadas,direccion,sueldo\n");
        for(i = 0; i < tam; i++)
        {
            Employee* employee = ll_get(pArrayListEmployee, i);
            fprintf(pFile, "%d,%s,%d,%s,%d\n", employee->id, employee->nombre, employee->horasTrabajadas, employee->direccion,employee->sueldo);
        }
        status = 1;
    }
    fclose(pFile);

    return status;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path, LinkedList* pArrayListEmployee)
{
    FILE* pFile;
    Employee* employee;
    int i;
    int tam;
    int status = 0;

    pFile = fopen(path, "wb");
    if(pFile != NULL && pArrayListEmployee != NULL)
    {
        tam = ll_len(pArrayListEmployee);

        for(i = 0; i < tam; i++)
        {
            employee = ll_get(pArrayListEmployee, i);
            fwrite(employee, sizeof(Employee), 1, pFile);
        }
        status = 1;
    }
    fclose(pFile);

    return status;
}

int controller_nextId(LinkedList* listEmployee)
/** \brief calculates the next available ID value
 *
 * \param listEmployee LinkedList* list of employees
 * \return int value of ID
 *
 */
{
    int len = ll_len(listEmployee);
    Employee* auxEmployee;
    int value = 0;
    int i;


    for(i = 0; i < len; i++)
    {
        auxEmployee = ll_get(listEmployee, i);
        if(auxEmployee->id > value)
        {
            value = auxEmployee->id;
        }
    }
    return value + 1;
}

int controller_calcularSueldo(LinkedList* listEmployee)
{
    int status;

    status = ll_map(listEmployee, employee_calcularSueldo);

    return status;
}

int controller_guardarFiltrado(LinkedList* listEmployee)
{
    int retorno = -1;
    if(listEmployee != NULL)
    {
        LinkedList* listaPorSueldos;
        int i;
        int contSueldo = 0;
        int promedio;
        int len = ll_len(listEmployee);
        Employee* auxEmployee;

        for(i = 0; i < len; i++)
        {
            auxEmployee = ll_get(listEmployee, i);
            contSueldo += auxEmployee->sueldo;
        }
        promedio = contSueldo/len;

        listaPorSueldos = ll_filter(listEmployee, employee_filtrarSueldoPromedio, promedio);

        retorno = 0;
        if(controller_saveAsText("sueldos.csv", listaPorSueldos))
                {
                    system("cls");
                    printf("Se guardo correctamente.\n");
                }
                else
                {
                    system("cls");
                    printf("No se pudo guardar los empleados.\n");
                }
    }

    return retorno;
}
