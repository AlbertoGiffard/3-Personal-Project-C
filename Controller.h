int controller_loadFromText(char* path , LinkedList* pArrayListEmployee);
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee);
int controller_addEmployee(LinkedList* pArrayListEmployee, char* id);
int controller_editEmployee(LinkedList* pArrayListEmployee);
int controller_removeEmployee(LinkedList* pArrayListEmployee);
int controller_ListEmployee(LinkedList* pArrayListEmployee);
int controller_sortEmployee(LinkedList* pArrayListEmployee);
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee);
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee);

//propias
int firstLetterUp(char data[], int length);
int validateId(LinkedList* pArrayListEmployee, char id[]);
int validateOptions(int since, int until, int option);
int lastId(LinkedList* pArrayListEmployee);
int findByName(LinkedList* pArrayListEmployee, char name[]);
int controller_loadIdFromText(char* path , char* id);
int controller_loadIdFromBinary(char* path , char* id);
int controller_saveIdAsText(char* path , char* id);
int controller_saveIdAsBinary(char* path , char* id);
