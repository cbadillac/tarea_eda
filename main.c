#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>


typedef struct extract_data
{
	int id;
	char *last_name;
	char *name;
	int old;
	struct extract_data *next;
} node, *data_pnode;



static FILE *file;

double quadratic_sum(data_pnode list,double prom)
{
	data_pnode p = NULL;
	p = list;
	double cont = 0;
	for (; p !=NULL ; p = p->next){
		cont = cont + ((p->old -prom)*(p->old -prom));
	}
	return cont;
}

int sum_data(data_pnode list)
{
	data_pnode p = NULL;
	p = list;
	int cont = 0;
	for (; p !=NULL ; p = p->next){
		cont = cont + p->old;
	}
	return cont;
}

int count(data_pnode list)
{	
	data_pnode p = NULL;
	p = list;
	int cont = 0;
	for (; p !=NULL ; p = p->next)
		cont++;
	
	return cont;
}

node* create_node(int* id, char* last_name, char* name, int* old)
{
	node* pointer_node = NULL;
	if ((pointer_node = (node*)malloc(sizeof(node)))==NULL){
		printf("ERROR: Do not possible create Node\n");
		exit(1);
	}else{
		pointer_node->id        = (*id);
		pointer_node->last_name = strdup(last_name);
		pointer_node->name      = strdup(name);
		pointer_node->old       = (*old);
		pointer_node->next      = NULL;
	}
	return(pointer_node);
}


bool is_repeat(data_pnode list, char* last_name, char* name, int* old)
{
	if (list == NULL)
		return false;
	do
	{
		bool aux1 = (strcmp(list->last_name, last_name) == 0);

		bool aux2 = (strcmp(list->name, name) == 0);

		bool aux3 = ((*old) == list->old);

		if (aux1 && aux2 && aux3){

			return true;
		}
		list = list->next;
	
	} while (list != NULL);
	return false;
}
node* save_line(data_pnode list, data_pnode actual_list)
{

	char *name = NULL;
	char *last_name = NULL;
	node* list_aux = NULL;
	name = (char*)malloc(sizeof(char)*1024);
	last_name = (char*)malloc(sizeof(char)*1024);
	int id = 0;
	int old = 0;

	if (fscanf(file, "%d %s %s %d", &id, last_name, name, &old) <= 0)
		return NULL;
	
	if(is_repeat(list, last_name, name, &old)){

		
		free(name);
		free(last_name);

		return actual_list;

	}else{
		
		list_aux = create_node(&id, last_name, name, &old);
	}

	free(name);
	free(last_name);
	return list_aux;
}

int main(int argc, char const *argv[])
{
	


	file = fopen("data.txt", "r");
	data_pnode list = NULL;
	data_pnode list_aux = NULL;
	list = save_line(list, list);
	list_aux = list;

	do
	{
		list_aux->next = NULL;
		list_aux->next = save_line(list, list_aux);
		
		list_aux       = list_aux->next;		
	} while (list_aux != NULL);


	double prom    = sum_data(list)/count(list);
	double dsv_std = sqrt(quadratic_sum(list, prom)/count(list));
	printf("%.2f %.2f\n", prom, dsv_std);
	fclose(file);
	return 0;
}
