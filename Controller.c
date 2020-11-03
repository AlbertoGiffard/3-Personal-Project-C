#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"

int controller_loadIdFromText(char* path , char* id)
{
    FILE* pFile;

    pFile = fopen(path, "r");
    if(pFile != NULL)
    {
        fscanf(pFile, "%[^\n]\n", id);
    }
    fclose(pFile);

    return 1;
}
int controller_loadFromText(char* path, LinkedList* pArrayListEmployee)
{
    FILE* pFile;
    pFile = fopen(path, "r");
    if(pFile != NULL)
    {
        parser_EmployeeFromText(pFile,pArrayListEmployee);
    }

    return 1;
}
int controller_loadIdFromBinary(char* path , char* id)
{
    FILE* pFile;

    pFile = fopen(path, "rb");
    if(pFile != NULL)
    {
        fread(id, sizeof(char), 10, pFile);
    }
    fclose(pFile);

    return 1;
}
int controller_loadFromBinary(char* path, LinkedList* pArrayListEmployee)
{
    FILE* pFile;
    pFile = fopen(path, "rb");
    if(pFile != NULL)
    {
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
int lastId(LinkedList* pArrayListEmployee)
{
    int listLength;
    int i;
    int id;
    Employee* aux;
    listLength = ll_len(pArrayListEmployee);
    id = -1;
    for(i = 0; i < listLength; i++)
    {
        if(i == listLength-1)
        {
            aux = (Employee*) ll_get(pArrayListEmployee, i);
            employee_getId(aux, &id);
            break;
        }
    }
    return id+1;
}
int validateOptions(int since, int until, int option)
{
    while(!(option > since && option < until))
    {
        printf("Indique una opción válida:");
        scanf("%d", &option);
    }
    return option;
}
int controller_addEmployee(LinkedList* pArrayListEmployee, char* idString)
{
    int idInt;
    int workHoursInt;
    int salaryInt;
    char idAux[50];
    char name[50];
    char workHoursString[50];
    char salaryString[50];
    Employee* aux;

    strcpy(idAux, idString);
    /*idInt = lastId(pArrayListEmployee);
    if(idInt != 1)
    {*/
        //itoa(*id, idString, 10);
        printf("Ingrese un nombre:");
        fflush(stdin);
        gets(name);
        firstLetterUp(name, 50);
        printf("Ingrese las horas trabajadas:");
        scanf("%d", &workHoursInt);
        validateOptions(-1, 10000, workHoursInt);
        itoa(workHoursInt, workHoursString, 10);
        printf("Ingrese el salario:");
        scanf("%d", &salaryInt);
        validateOptions(-1, 1000000, salaryInt);
        itoa(salaryInt, salaryString, 10);
        aux = employee_newParametros(idString, name, workHoursString, salaryString);
        if(aux != NULL)
        {
            idInt = atoi(idAux);
            idInt += 1;
            itoa(idInt, idString, 10);
            ll_add(pArrayListEmployee, aux);
        } else
        {
            printf("             |\n");
            printf("Error al cargar el usuario\n");
            printf("             |\n");
        }
    /*} else
    {
        printf("             |\n");
        printf("Error al cargar el usuario\n");
        printf("             |\n");
    }*/
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
        printf("                    |\n");
        printf("No se encontró ningún empleado por ese id\n");
        printf("                    |\n");
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
        printf("                    |\n");
        printf("No se encontró ningún empleado por ese id\n");
        printf("                    |\n");
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
    printf("3. Horas trabajadas\n");
    printf("4. Sueldo\n");
    printf("Elija una opción:");
    scanf("%d", &auxOrderBy);
    validateOptions(0, 5, auxOrderBy);
    printf("En orden:\n");
    printf("1. Ascendente\n");
    printf("2. Descendente\n");
    printf("Elija una opción:");
    scanf("%d", &auxDirection);
    validateOptions(0, 3, auxDirection);
    orderBy = auxOrderBy;
    if(auxDirection == 1)
    {
        direction = auxDirection;
    } else
    {
        direction = 0;
    }
    //swtich
    switch(orderBy)
    {
        case 1:
            ll_sort(pArrayListEmployee, employee_CompareById, direction);
            break;
        case 2:
            ll_sort(pArrayListEmployee, employee_CompareByName, direction);
            break;
        case 3:
            ll_sort(pArrayListEmployee, employee_CompareByWorkHours, direction);
            break;
        case 4:
            ll_sort(pArrayListEmployee, employee_CompareBySalary, direction);
            break;
    }
    return 1;
}
int controller_saveIdAsText(char* path , char* id)
{
    FILE* pFile;
    pFile = fopen(path, "w");
    if(path != NULL)
    {
        fprintf(pFile, "%s\n", id);
    }
    fclose(pFile);
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
    pFile = fopen(path, "w");
    if(pFile != NULL)
    {
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
int controller_saveIdAsBinary(char* path , char* id)
{
    FILE* pFile;
    pFile = fopen(path, "wb");
    if(path != NULL)
    {
        fwrite(id,sizeof(char),10,pFile);
    }
    fclose(pFile);
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
    pFile = fopen(path, "wb");
    if(pFile != NULL)
    {
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

