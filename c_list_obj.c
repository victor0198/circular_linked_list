#include <stdio.h>
#include <stdlib.h>


typedef struct cell{
	int value;
	struct cell * prev;
	struct cell * next;
}cell;

typedef struct c_list{
	cell * first;
	cell * current;
	cell * last;
	int len;
}c_list;

const struct c_list EMPTY_LIST = {
    NULL, 0
};

cell * new_empty_cell(){
	cell * n_cell = (cell*) malloc(sizeof(cell));
	n_cell->value = 0;
	n_cell->prev = NULL;
	n_cell->next = NULL;
	return n_cell;
}

c_list new_c_list(int len){
	if(len < 1){
		printf("%s", "Can't initialize list, size too small!");
		exit(1);
	}else if(len > 10){
		printf("%s", "Can't initialize list, size too big!");
		exit(2);
	}
	
	c_list list = EMPTY_LIST;
	cell * current;
	list.first = new_empty_cell();
	list.current = list.first;
	current = list.first;
	
	int i = 1;
	for(; i < len; i++){
		cell * next_cell = new_empty_cell();
		current->next = next_cell;
		next_cell->prev = current;
		current = next_cell;
	}
	
	current->next = list.first;	
	list.first->prev = current;
	
	list.last = list.first->prev;
	
	list.len = len;
	
	return list;
}

void print_cl(c_list obj){
	cell * current = obj.first;
	
	printf("\nList(len=%d): ", obj.len);
	
	if(current == NULL){
		printf("%s", "Empty list! Nothing to print!");
	}else{	
		do{
			if(current == obj.current){
				printf("[%d] ", current->value);
			}else if(current == obj.last){
				printf("|%d ", current->value);
			}else{
				printf("%d ", current->value);
			}
			
			current = current->next;
		}while(current != obj.first);
	}
	
	printf("\n\n");
}

void push_cl(c_list * obj, int val){
	
	printf("Pushing: %d\n", val);
	
	obj->current = obj->current->next;
	obj->current->value = val;
	obj->first = obj->current;
	
	if(obj->current == obj->last){
		printf("%s", "---");
		obj->last = obj->last->next;
	}
}

void undo(c_list * list){
	if(list->current != list->last){
		list->current = list->current->prev;
	}
}

void redo(c_list * list){
	if(list->current != list->first){
		list->current = list->current->next;
	}	
}

int main(){
			
	c_list list = new_c_list(5);
	
	char command = 'm';
	
	while(command != 'e'){
		system("cls");
		
		printf("%s", "Show(s), Push(p), Undo(u), Redo(r), Exit(e): \n");
		
		print_cl(list);
		
		command = getch();
				
		if(command == 'p'){
			printf("%s", "value = ");
			int value;
			scanf("%d", &value);
			push_cl(&list, value);
		}
		
		if(command == 'u'){
			undo(&list);
		}
		
		if(command == 'r'){
			redo(&list);
		}
	}	
	// end of Tests
	
	exit(0);
}
