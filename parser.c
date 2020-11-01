#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"

int parser_EmployeeFromText(FILE* pFile,LinkedList* pArrayListEmployee)
{
    char id[50];
    char name[50];
    char salary[50];
    char workHours[50];
    Employee* aux;

    while(!feof(pFile))
    {
        fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", id, name, workHours, salary);
        aux = employee_newParametros(id, name, workHours, salary);
        if(aux != NULL)
        {
            ll_add(pArrayListEmployee, aux);
        }
    }
    fclose(pFile);
    return 1;
}

int parser_EmployeeFromBinary(FILE* pFile, LinkedList* pArrayListEmployee)
{
    char id[50];
    char name[50];
    char salary[50];
    char workHours[50];
    Employee* aux;
    while(!feof(pFile))
    {
        fread(id, sizeof(char), 50, pFile);
        if (feof(pFile))
        {
            break;
        }
        //
        fread(name, sizeof(char), 50, pFile);
        fread(workHours, sizeof(char), 50, pFile);
        fread(salary, sizeof(char), 50, pFile);
        aux = employee_newParametros(id, name, workHours, salary);
        if(aux != NULL)
        {
            ll_add(pArrayListEmployee, aux);
        }
    }
    fclose(pFile);

    return 1;
}
