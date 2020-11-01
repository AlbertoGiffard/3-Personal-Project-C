#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"

int controller_loadFromText(char* path, LinkedList* pArrayListEmployee)
{
    FILE* pFile;
    if(pFile != NULL)
    {
        pFile = fopen(path, "r");
        parser_EmployeeFromText(pFile,pArrayListEmployee);
    }

    return 1;
}


int controller_loadFromBinary(char* path, LinkedList* pArrayListEmployee)
{
    FILE* pFile;
    if(pFile != NULL)
    {
        pFile = fopen(path, "rb");
        parser_EmployeeFromBinary(pFile, pArrayListEmployee);
    }

    return 1;
}

int firstLetterUp(char data[], int length)
{
    int i;

    for(i = 0;i < length; i++)
    {
        data[i] = tolower(data[i]);
    }
    for(i = 0;i < length;i++)
    {
        if(i == 0)
        {
            data[i] = toupper(data[i]);
        }

        if(data[i] == ' ')
        {
            data[i + 1] = toupper(data[i + 1]);
        }

    }
    return 0;
}
int validateId(LinkedList* pArrayListEmployee, char id[])
{
    int listLength;
    int i;
    int idNumber;
    int result;
    char idString[50];
    Employee* aux;
    listLength = ll_len(pArrayListEmployee);
    result = 1;
    for(i = 0; i < listLength; i++)
    {
        aux = (Employee*) ll_get(pArrayListEmployee, i);
        employee_getId(aux, &idNumber);
        itoa(idNumber, idString, 10);
        if(strcmp(id, idString) == 0)
        {
            result = 0;
            break;
        }
    }
    return result;
}
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
    int id;
    int newId;
    char idString[10];
    char name[50];
    char workHours[50];
    char salary[50];
    Employee* aux;

    printf("Ingrese el id:");
    scanf("%d", &id);
    while(!(id > 0 && id < 100000))
    {
        printf("Error, reingrese el id:");
        scanf("%d", &id);
    }
    itoa(id, idString, 10);
    newId = validateId(pArrayListEmployee, idString);
    while(newId != 1)
    {
        printf("Id en uso, reingrese uno nuevo:");
        scanf("%d", &id);
        while(!(id > 0 && id < 100000))
        {
            printf("Error, reingrese el id:");
            scanf("%d", &id);
        }
        itoa(id, idString, 10);
        newId = validateId(pArrayListEmployee, idString);
    }
    printf("Ingrese un nombre:");
    fflush(stdin);
    gets(name);
    firstLetterUp(name, 50);
    printf("Ingrese las horas trabajadas:");
    fflush(stdin);
    gets(workHours);
    printf("Ingrese el salario:");
    fflush(stdin);
    gets(salary);
    aux = employee_newParametros(idString, name, workHours, salary);
    if(aux != NULL)
    {
        ll_add(pArrayListEmployee, aux);
    }
    return 1;
}


int controller_editEmployee(LinkedList* pArrayListEmployee)
{
    int i;
    int listLength;
    int id;
    int idFound;
    int option;
    int result;
    char newName[50];
    int newSalary;
    int newWorkHours;
    Employee* aux;
    printf("Indique el id del empleado que quiere modificar:");
    fflush(stdin);
    scanf("%d", &id);
    listLength = ll_len(pArrayListEmployee);
    result = 0;
    for(i = 0; i < listLength; i++)
    {
        aux = (Employee*) ll_get(pArrayListEmployee, i);
        employee_getId(aux, &idFound);
        if(id == idFound)
        {
            result = 1;
            DataOfOneEmployee(aux);
            printf("Que campo quiere modificar:\n");
            printf("1. Nombre\n");
            printf("2. Sueldo\n");
            printf("3. Horas trabajadas\n");
            printf("4. Regresar\n");
            printf("Elija una opción: ");
            scanf("%d", &option);
            switch(option)
            {
                case 1:
                    printf("Indique el nuevo nombre: ");
                    fflush(stdin);
                    gets(newName);
                    firstLetterUp(newName, 50);
                    employee_setNombre(aux, newName);
                    break;
                case 2:
                    printf("Indique el nuevo sueldo: ");
                    scanf("%d", &newSalary);
                    employee_setSueldo(aux, newSalary);
                    break;
                case 3:
                    printf("Indique las nuevas horas trabajadas: ");
                    scanf("%d", &newWorkHours);
                    employee_setHorasTrabajadas(aux, newWorkHours);
                    break;
                default:
                    break;
            }
        }
    }
    if(option == 1 || option == 2 || option == 3)
    {
        printf("                 |\n");
        printf("Modificado el empleado exitosamente\n");
        printf("                 |\n");
    }
    if(result == 0)
    {
        printf("No se encontró ningún empleado por ese id\n");
    }

    return 1;
}


int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
    int i;
    int listLength;
    int id;
    int idFound;
    int index;
    char option;
    int result;
    Employee* aux;

    printf("Indique el id del empleado que quiere dar de baja:");
    fflush(stdin);
    scanf("%d", &id);
    listLength = ll_len(pArrayListEmployee);
    result = 0;
    for(i = 0; i < listLength; i++)
    {
        aux = (Employee*) ll_get(pArrayListEmployee, i);
        employee_getId(aux, &idFound);
        if(id == idFound)
        {
            result = 1;
            DataOfOneEmployee(aux);
            printf("Seguro de querer dar de baja al empleado? Luego no podrá recuperarlo\n");
            printf("Escriba 'S' para si o 'N' para no: ");
            fflush(stdin);
            scanf("%c", &option);
            option = tolower(option);
            while(!(option == 's' || option == 'n'))
            {
                printf("Error, escriba 'S' para si o 'N' para no:");
                fflush(stdin);
                scanf("%c", &option);
                option = tolower(option);
            }
            if(option == 's')
            {
                employee_delete(aux);
                listLength = ll_len(pArrayListEmployee);
                index = ll_indexOf(pArrayListEmployee, aux);
                ll_remove(pArrayListEmployee, index);
                pArrayListEmployee = realloc(pArrayListEmployee, sizeof(LinkedList)*listLength);
                printf("                  |\n");
                printf("Se dió de baja al empleado exitosamente\n");
                printf("                  |\n");
            }
            break;
        }
    }
    if(result == 0)
    {
        printf("No se encontró ningún empleado por ese id\n");
    }

    return 1;
}


int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    Employee* aux;
    char name[50];
    int workHours;
    int salary;
    int listLength;
    int id;
    listLength = ll_len(pArrayListEmployee);
    if(listLength != 0)
    {
        printf("|------------------------------------------|\n");
        printf("| ID | NOMBRE | SALARIO | HORAS TRABAJADAS |\n");
        printf("|------------------------------------------|\n");
        for(int i = 0; i < listLength; i++)
        {
            aux = (Employee*) ll_get(pArrayListEmployee, i);
            employee_getId(aux, &id);
            employee_getNombre(aux, name);
            employee_getSueldo(aux, &salary);
            employee_getHorasTrabajadas(aux, &workHours);
            printf("  %d  %-9s  %-11d  %d\n", id, name, salary, workHours);
        };
    } else
    {
        printf("                   |\n");
        printf("Debe cargar datos para poder listar\n");
        printf("                   |\n");
    }

    return 1;
}


int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
    int orderBy;
    int auxOrderBy;
    int direction;
    int auxDirection;

    printf("Ordenar por:\n");
    printf("1. Id\n");
    printf("2. Nombre\n");
    printf("Elija una opción:");
    scanf("%d", &auxOrderBy);
    while(!(auxOrderBy > 0 && auxOrderBy < 3))
    {
        printf("Indique una opción válida:");
        scanf("%d", &auxOrderBy);
    }
    printf("En orden:\n");
    printf("1. Ascendente\n");
    printf("2. Descendente\n");
    printf("Elija una opción:");
    scanf("%d", &auxDirection);
    while(!(auxDirection > 0 && auxDirection < 3))
    {
        printf("Indique una opción válida:");
        scanf("%d", &auxDirection);
    }
    orderBy = auxOrderBy;
    if(auxDirection == 1)
    {
        direction = auxDirection;
    } else
    {
        direction = 0;
    }
    if(orderBy == 1)
    {
        ll_sort(pArrayListEmployee, employee_CompareById, direction);
    } else
    {
        ll_sort(pArrayListEmployee, employee_CompareByName, direction);
    }
    return 1;
}


int controller_saveAsText(char* path, LinkedList* pArrayListEmployee)
{
    FILE* pFile;
    int id;
    int workHours;
    int salary;
    int listLength;
    int i;
    char name[50];
    char idString[50];
    char salaryString[50];
    char workHoursString[50];
    Employee* aux;
    listLength = ll_len(pArrayListEmployee);
    if(pFile != NULL)
    {
        pFile = fopen(path, "w");

        for(i=0; i<listLength; i++)
        {
            aux = (Employee*) ll_get(pArrayListEmployee, i);
            employee_getId(aux, &id);
            employee_getNombre(aux, name);
            employee_getSueldo(aux, &salary);
            employee_getHorasTrabajadas(aux, &workHours);
            itoa(id, idString, 10);
            itoa(salary, salaryString, 10);
            itoa(workHours, workHoursString, 10);
            fprintf(pFile,"%s,%s,%s,%s\n",idString, name, salaryString, workHoursString);
        }

        fclose(pFile);
    }

    return 1;
}


int controller_saveAsBinary(char* path, LinkedList* pArrayListEmployee)
{
    FILE* pFile;
    int id;
    int workHours;
    int salary;
    int listLength;
    int i;
    char name[50];
    char idString[50];
    char salaryString[50];
    char workHoursString[50];
    Employee* aux;
    listLength = ll_len(pArrayListEmployee);
    if(pFile != NULL)
    {
        pFile = fopen(path, "wb");
        for(i=0; i<listLength; i++)
        {
            aux = (Employee*) ll_get(pArrayListEmployee, i);
            employee_getId(aux, &id);
            employee_getNombre(aux, name);
            employee_getSueldo(aux, &salary);
            employee_getHorasTrabajadas(aux, &workHours);
            itoa(id, idString, 10);
            itoa(salary, salaryString, 10);
            itoa(workHours, workHoursString, 10);
            fwrite(idString,sizeof(char),50,pFile);
            fwrite(name,sizeof(char),50,pFile);
            fwrite(salaryString,sizeof(char),50,pFile);
            fwrite(workHoursString,sizeof(char),50,pFile);
        }

        fclose(pFile);
    }
    return 1;
}

