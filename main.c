#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"


/****************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.bin (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.bin (modo binario).
    10. Salir
*****************************************************/
int main_menu();

int main()
{
    setlocale(LC_ALL, "");
    int option;
    char id[10];
    LinkedList* list;
    list = ll_newLinkedList();

    do
    {
        option = main_menu();
        switch(option)
        {
            case 1:
                if(controller_loadFromText("data.csv", list) == 1)
                {
                    if(controller_loadIdFromText("id.csv", id) == 1)
                    {
                        printf("           |\n");
                        printf("Carga de datos exitosa\n");
                        printf("           |\n");
                    }
                } else
                {
                    printf("                 |\n");
                    printf("Hubo un error en la carga de datos\n");
                    printf("                 |\n");
                }
                break;
            case 2:
                if(controller_loadFromBinary("data.bin", list) == 1)
                {
                    if(controller_loadIdFromBinary("id.bin", id) == 1)
                    {
                        printf("           |\n");
                        printf("Carga de datos exitosa\n");
                        printf("           |\n");
                    }
                } else
                {
                    printf("                 |\n");
                    printf("Hubo un error en la carga de datos\n");
                    printf("                 |\n");
                }
                break;
            case 3:
                if(controller_addEmployee(list, id) == 1)
                {
                    printf("                 |\n");
                    printf("Cargado el nuevo empleado exitosamente\n");
                    printf("                 |\n");
                } else
                {
                    printf("                     |\n");
                    printf("Hubo un error en la carga del nuevo empleado\n");
                    printf("                     |\n");
                }
                break;
            case 4:
                if(ll_isEmpty(list) != 1)
                {
                    if(controller_editEmployee(list) != 1)
                    {
                        printf("                |\n");
                        printf("Hubo un error en la modificación\n");
                        printf("                |\n");

                    }
                } else
                {
                    printf("                   |\n");
                    printf("Debe cargar un dato al menos para modificar\n");
                    printf("                   |\n");
                }
                break;
            case 5:
                if(ll_isEmpty(list) != 1)
                {
                    if(controller_removeEmployee(list) != 1)
                    {
                        printf("               |\n");
                        printf("Hubo un error al dar de baja\n");
                        printf("               |\n");

                    }
                } else
                {
                    printf("                     |\n");
                    printf("Debe cargar un dato al menos para dar de baja\n");
                    printf("                     |\n");
                }
                break;
            case 6:
                if(ll_isEmpty(list) != 1)
                {
                    if(controller_ListEmployee(list) != 1)
                    {
                        printf("               |\n");
                        printf("Hubo un error en poder listar\n");
                        printf("               |\n");
                    }
                } else
                {
                    printf("                     |\n");
                    printf("Debe cargar un dato al menos para poder listar\n");
                    printf("                     |\n");
                }
                break;
            case 7:
                if(ll_isEmpty(list) != 1)
                {
                    if(controller_sortEmployee(list) == 1)
                    {
                        printf("                  |\n");
                        printf("      Ordenado correctamente\n");
                        printf("Se puede visualizar en la opción 6\n");
                        printf("                  |\n");
                    } else
                    {
                        printf("         |\n");
                        printf("Error al ordenar\n");
                        printf("         |\n");
                    }
                } else
                {
                    printf("                     |\n");
                    printf("Debe cargar un dato al menos para poder listar\n");
                    printf("                     |\n");
                }
                break;
            case 8:
                if(controller_saveAsText("data.csv", list) == 1)
                {
                    if(controller_saveIdAsText("id.csv", id) == 1)
                    {
                        printf("           |\n");
                        printf("Guardado de datos exitoso\n");
                        printf("           |\n");
                    }
                } else
                {
                    printf("               |\n");
                    printf("Hubo un error en el guardado\n");
                    printf("               |\n");
                }
                break;
            case 9:
                if(controller_saveAsBinary("data.bin", list) == 1)
                {
                    if(controller_saveIdAsBinary("id.bin", id) == 1)
                    {
                        printf("           |\n");
                        printf("Guardado de datos exitoso\n");
                        printf("           |\n");
                    }
                } else
                {
                    printf("               |\n");
                    printf("Hubo un error en el guardado\n");
                    printf("               |\n");
                }
                break;
        }
    }while(option != 10);


    return 0;
}

int main_menu()
{
    int option;

    printf("---------------------------------------\n");
    printf("|           Bienvenido a TP. 3        |\n");
    printf("---------------------------------------\n");
    printf("1. Cargar los datos de los empleados desde el archivo data.csv (modo texto)\n");
    printf("2. Cargar los datos de los empleados desde el archivo data.bin (modo binario)\n");
    printf("3. Alta de empleado\n");
    printf("4. Modificar datos de empleado\n");
    printf("5. Baja de empleado\n");
    printf("6. Listar empleados\n");
    printf("7. Ordenar empleados\n");
    printf("8. Guardar los datos de los empleados en el archivo data.csv (modo texto)\n");
    printf("9. Guardar los datos de los empleados en el archivo data.bin (modo binario)\n");
    printf("10. Salir\n");
    printf("Elija una opción: ");
    scanf("%d", &option);

    return option;
}
