#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Employee.h"
#include "bibliotecaGetsYComprobaciones.h"
#include <conio.h>

Employee* employee_new()
{
    Employee* employee;

    employee = (Employee*) calloc(sizeof(Employee),1);

    return employee;
}

Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* direccionStr)
{
    Employee* employee;

    employee = employee_new();

    if(employee != NULL)
    {
        employee_setNombre(employee, nombreStr);
        employee_setHorasTrabajadas(employee, atoi(horasTrabajadasStr));
        employee_setSueldo(employee, 0);
        employee_setId(employee, atoi(idStr));
        employee_setDireccion(employee, direccionStr);
    }
    else
    {
        printf("No se pudo cargar los datos de empleado");
    }

    return employee;
}

int employee_setId(Employee* this,int id)
{
    int status = 0;
    if(this != NULL)
    {
        status = 1;
        this->id = id;
    }

    return status;
}
int employee_getId(Employee* this,int* id)
{
    int status = 0;

    if(this != NULL)
    {
        *id = this->id;
        status = 1;
    }
    return status;
}

int employee_setNombre(Employee* this,char* nombre)
{
    int status = 0;
    if(this != NULL)
    {
        status = 1;
        strcpy(this->nombre, nombre);
    }

    return status;
}
int employee_getNombre(Employee* this,char* nombre)
{
    int status = 0;
    if(this != NULL)
    {
        status = 1;
        strcpy(nombre, this->nombre);
    }

    return status;
}
int employee_setDireccion(Employee* this,char* direccion)
{
    int status = 0;
    if(this != NULL)
    {
        status = 1;
        strcpy(this->direccion, direccion);
    }

    return status;
}
int employee_getDireccion(Employee* this,char* direccion)
{
    int status = 0;
    if(this != NULL)
    {
        status = 1;
        strcpy(direccion, this->direccion);
    }

    return status;
}
int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
    int status = 0;
    if(this != NULL)
    {
        status = 1;
        this->horasTrabajadas = horasTrabajadas;
    }

    return status;
}
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
    int status = 0;
    if(this != NULL)
    {
        status = 1;
        *horasTrabajadas = this->horasTrabajadas;
    }

    return status;
}

int employee_setSueldo(Employee* this,int sueldo)
{
    int status = 0;
    if(this != NULL)
    {
        status = 1;
        this->sueldo = sueldo;
    }

    return status;
}
int employee_getSueldo(Employee* this,int* sueldo)
{
    int status = 0;
    if(this != NULL)
    {
        status = 1;
        *sueldo = this->sueldo;
    }

    return status;
}

void employee_ListAnEmployee(Employee* employee)
{
    printf("ID        NOMBRE     DIRECCION  \n");
    printf("%-4d - %10s  - %10s \n", employee->id, employee->nombre, employee->direccion);
}

int employee_editEmployeeName(Employee* employee)
{
    char auxName[128];
    char option;
    system("cls");
    printf("MODIFICAR NOMBRE\n\n");
    employee_ListAnEmployee(employee);
    getStringOnly("\nIngrese el nuevo nombre: ", auxName);
    option = getChar("\n\nEsta seguro que desea modificar el nombre (S/N)?: ");
    if(option == 's' || option == 'S')
    {
       strcpy(employee->nombre, auxName);
    }
    return 1;
}

int employee_editEmployeeHours(Employee* employee)
{
    int auxHours;
    char option;
    int flagHours = 0;

    system("cls");
    printf("MODIFICAR HORAS TRABAJADAS\n\n");
    employee_ListAnEmployee(employee);
    do
    {
        auxHours = getIntOnly("Ingrese las nuevas horas trabajadas: ");
        if(flagHours < 0)
        {
            printf("\nLas horas no pueden ser menor a 0.");
        }
        else
        {
            flagHours = 1;
        }
    }while(flagHours != 1);
    option = getChar("\n\nEsta seguro que desea modificar las horas trabajadas (S/N)?: ");
    if(option == 's' || option == 'S')
    {
       employee ->horasTrabajadas = auxHours;
    }
    return 1;
}

int employee_editEmployeeSalary(Employee* employee)
{
    int auxSalary;
    char option;
    int flagSalary = 0;

    system("cls");
    printf("MODIFICAR SALARIO\n\n");
    employee_ListAnEmployee(employee);
    do
    {
        auxSalary = getIntOnly("Ingrese el nuevo salario: ");
        if(flagSalary < 0)
        {
            printf("\nEl salario no puede ser menor a 0.");
        }
        else
        {
            flagSalary = 1;
        }
    }while(flagSalary != 1);
    option = getChar("\n\nEsta seguro que desea modificar el salario (S/N)?: ");
    if(option == 's' || option == 'S')
    {
       employee ->sueldo = auxSalary;
    }
    return 1;
}

int employee_sortById(void* first, void* second)
{
    Employee* employeeOne;
    Employee* employeeTwo;
    int aux = 0;

    employeeOne = (Employee*)first;
    employeeTwo = (Employee*)second;

    if(employeeOne -> id > employeeTwo -> id)
    {
        aux = 1;
    }
    else if(employeeOne -> id < employeeTwo -> id)
    {
        aux = -1;
    }
    return aux;
}

int employee_sortByHours(void* first, void* second)
{
    Employee* employeeOne;
    Employee* employeeTwo;
    int aux = 0;

    employeeOne = (Employee*)first;
    employeeTwo = (Employee*)second;

    if(employeeOne -> horasTrabajadas > employeeTwo -> horasTrabajadas)
    {
        aux = 1;
    }
    else if(employeeOne -> horasTrabajadas < employeeTwo -> horasTrabajadas)
    {
        aux = -1;
    }
    return aux;
}

int employee_sortByName(void* first, void* second)
{
    Employee* employeeOne;
    Employee* employeeTwo;
    int aux = 0;

    employeeOne = (Employee*)first;
    employeeTwo = (Employee*)second;

    aux = stricmp(employeeOne -> nombre, employeeTwo -> nombre);

    return aux;
}

int employee_sortBySalary(void* first, void* second)
{
    Employee* employeeOne;
    Employee* employeeTwo;
    int aux = 0;

    employeeOne = (Employee*)first;
    employeeTwo = (Employee*)second;

    if(employeeOne -> sueldo > employeeTwo -> sueldo)
    {
        aux = 1;
    }
    else if(employeeOne -> sueldo < employeeTwo -> sueldo)
    {
        aux = -1;
    }

    return aux;
}

void* employee_calcularSueldo(void* aux)
{
    Employee* employee = aux;
    if(employee->horasTrabajadas >= 80 && employee->horasTrabajadas <= 120)
    {
        employee->sueldo = employee->horasTrabajadas * 180;
    }else if(employee->horasTrabajadas > 120 && employee->horasTrabajadas <= 160)
    {
        employee->sueldo = employee->horasTrabajadas * 240;
    }else if(employee->horasTrabajadas > 160 && employee->horasTrabajadas <= 240)
    {
        employee->sueldo = employee->horasTrabajadas * 350;
    }

    return employee;
}

int employee_filtrarSueldoPromedio(void* aux,int prom)
{
    Employee* employeeAux = aux;
    int retorno = 0;

    if(employeeAux->sueldo > prom)
    {
        retorno = 1;
    }

    return retorno;
}
