#include <stdlib.h>
#include <stdio.h>
#include "Employee.h"
#include <string.h>

/***************Setters****************/
int employee_setId(Employee* this,int id)
{
    int result = 0;
    if(this != NULL && id > 0)
    {
        this->id = id;
        result = 1;
    }
    return result;
}
int employee_setNombre(Employee* this,char* nombre)
{
    int result = 0;
    if(this != NULL && strcmp(nombre, "") != 0)
    {
        strcpy(this->nombre, nombre);
        result = 1;
    }
    return result;
}
int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
    int result = 0;
    if(this != NULL && horasTrabajadas >= 0)
    {
        this->horasTrabajadas = horasTrabajadas;
        result = 1;
    }
    return result;
}
int employee_setSueldo(Employee* this,int sueldo)
{
    int result = 0;
    if(this != NULL && sueldo >= 0)
    {
        this->sueldo = sueldo;
        result = 1;
    }
    return result;
}
/***************Getters****************/
int employee_getId(Employee* this,int* id)
{
    int result = 0;
    if(this != NULL && id > 0)
    {
        *id = this->id;
        result = 1;
    }
    return result;
}
int employee_getNombre(Employee* this,char* nombre)
{
    int result = 0;
    if(this != NULL)
    {
        strcpy(nombre, this->nombre);
        result = 1;
    }
    return result;
}
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
    int result = 0;
    if(this != NULL && horasTrabajadas >= 0)
    {
        *horasTrabajadas = this->horasTrabajadas;
        result = 1;
    }
    return result;
}
int employee_getSueldo(Employee* this,int* sueldo)
{
    int result = 0;
    if(this != NULL && sueldo >= 0)
    {
        *sueldo = this->sueldo;
        result = 1;
    }
    return result;
}
/********************Employees*******************/
Employee* employee_new()
{
    Employee* newEmployee;
    newEmployee = (Employee*)malloc(sizeof(Employee));

    return newEmployee;
}
int validate_fields(char* idStr,char* nombreStr,char* horasTrabajadasStr,char* sueldoStr, Employee* listEmployee)
{
    int result = 0;
    int id = atoi(idStr);
    int workHours = atoi(horasTrabajadasStr);
    int salary = atoi(sueldoStr);

    if(employee_setId(listEmployee, id)) // este es el correcto
    {
        if(employee_setNombre(listEmployee,nombreStr))
        {
            if(employee_setHorasTrabajadas(listEmployee, workHours))
            {
                if(employee_setSueldo(listEmployee, salary))
                {
                    result = 1;
                }
            }
        }
    }
    return result;
}
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr,char* sueldoStr)
{
    Employee* listEmployee;
    listEmployee = employee_new();
    if(listEmployee != NULL)
    {
        if(validate_fields(idStr, nombreStr, horasTrabajadasStr, sueldoStr, listEmployee) == 0)
        {
            free(listEmployee);
            listEmployee = NULL;
        }
    }
    return listEmployee;
}

void employee_delete(Employee* this)
{
    if(this!=NULL)
    {
        free(this);
    }
}
/***********************Compares*****************************/
int employee_CompareByName(Employee* e1, Employee* e2)
{
    return strcmp(e1->nombre, e2->nombre);
}
int employee_CompareById(Employee* e1, Employee* e2)
{
    int result = 0;
    if(e1->id > e2->id)
    {
        result = 1;
    }else
    {
        if(e1->id < e2->id)
        {
            result = -1;
        }
    }
    return result;
}
/*************************Propias**********************/
int DataOfOneEmployee(Employee* dataEmployee)
{
    char name[50];
    int id;
    int workHours;
    int salary;
    employee_getId(dataEmployee, &id);
    employee_getNombre(dataEmployee, name);
    employee_getSueldo(dataEmployee, &salary);
    employee_getHorasTrabajadas(dataEmployee, &workHours);
    printf("--------------------------------------\n");
    printf("|                 DATOS              |\n");
    printf("--------------------------------------\n");
    printf("| NOMBRE | SUELDO | HORAS TRABAJADAS |\n");
    printf("  %-9s %-13d %d\n", name, salary, workHours);

    return 1;
}

