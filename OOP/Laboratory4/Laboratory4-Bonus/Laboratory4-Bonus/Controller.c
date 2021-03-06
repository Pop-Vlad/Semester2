#include <stdlib.h>
#include <string.h>
#include "Controller.h"



void registerRepositoryState(controller* controller_pointer, GenericElement new_history) {

	if (controller_pointer->hystory_of_repository_size >= controller_pointer->hystory_of_repository_capacity) {
		controller_pointer->hystory_of_repository_capacity = (int)controller_pointer->hystory_of_repository_capacity*1.5;
		controller_pointer->hystory_of_repository = (GenericElement*)realloc(controller_pointer->hystory_of_repository, controller_pointer->hystory_of_repository_capacity);
	}

	int i;
	for (i = controller_pointer->repository_index + 1; i < controller_pointer->hystory_of_repository_size; i++) {
		destroyRepositoryState(controller_pointer->hystory_of_repository[i]);
	}
	controller_pointer->repository_index += 1;
	controller_pointer->hystory_of_repository_size = controller_pointer->repository_index + 1;
	controller_pointer->hystory_of_repository[controller_pointer->repository_index] = new_history;
}


int compareBarricadesByVisibility(barricade* object_1, barricade* object_2) {
	return strcmp(object_1->visibility_in_area, object_2->visibility_in_area);
}


void sortAscending(barricade** list_of_barricades, int list_length, int(*key)(barricade*, barricade*)) {
	barricade* auxiliary_pointer = NULL;
	int i, j;
	for (i = 0; i < list_length; i++) {
		for (j = 0; j < list_length; j++) {
			if (key(list_of_barricades[i], list_of_barricades[j]) < 0) {
				auxiliary_pointer = list_of_barricades[i];
				list_of_barricades[i] = list_of_barricades[j];
				list_of_barricades[j] = auxiliary_pointer;
			}
		}
	}
}


void sortDescending(barricade** list_of_barricades, int list_length, int(*key)(barricade*, barricade*)) {
	barricade* auxiliary_pointer = NULL;
	int i, j;
	for (i = 0; i < list_length; i++) {
		for (j = 0; j < list_length; j++) {
			if (key(list_of_barricades[i], list_of_barricades[j]) > 0) {
				auxiliary_pointer = list_of_barricades[i];
				list_of_barricades[i] = list_of_barricades[j];
				list_of_barricades[j] = auxiliary_pointer;
			}
		}
	}
}



controller* createController(repository* repository_pointer) {
	controller* new_controller = (controller*)malloc(sizeof(controller));
	new_controller->the_repository = repository_pointer;
	new_controller->hystory_of_repository = (GenericElement*)malloc(sizeof(GenericElement) * 100);
	new_controller->hystory_of_repository_capacity = 100;
	new_controller->hystory_of_repository_size = 0;
	new_controller->repository_index = -1;
	PastRepositoryState* repository_state = createRepositoryState(new_controller->the_repository);
	registerRepositoryState(new_controller, repository_state);
	return new_controller;
}


void destroyController(controller* controller_pointer) {
	int i;
	for (i = 0; i < controller_pointer->hystory_of_repository_size; i++) {
		destroyRepositoryState(controller_pointer->hystory_of_repository[i]);
	}
	free(controller_pointer->hystory_of_repository);
	free(controller_pointer);
}



int addController(controller* controller_pointer, char* location_code, char* visibility_in_area, char* barricade_type, char* barricade_sturdiness) {
	int return_status;
	int location_code_integer = atoi(location_code);
	int barricade_sturdiness_integer = atoi(barricade_sturdiness);
	barricade* new_barricade = createBarricade(location_code_integer, visibility_in_area, barricade_type, barricade_sturdiness_integer);
	return_status = add(controller_pointer->the_repository, new_barricade);
	if (return_status == 0) {
		PastRepositoryState* new_repository_state = createRepositoryState(controller_pointer->the_repository);
		registerRepositoryState(controller_pointer, new_repository_state);
	}
	return return_status;
}


int updateController(controller* controller_pointer, char* location_code, char* new_visibility_in_area, char* new_barricade_type, char* new_barricade_sturdiness) {
	int return_status;
	int location_code_integer = atoi(location_code);
	int new_barricade_sturdiness_integer = atoi(new_barricade_sturdiness);

	barricade* new_barricade = createBarricade(location_code_integer, new_visibility_in_area, new_barricade_type, new_barricade_sturdiness_integer);
	return_status = update(controller_pointer->the_repository, location_code_integer, new_barricade);
	if (return_status == 0) {
		PastRepositoryState* repository_state = createRepositoryState(controller_pointer->the_repository);
		registerRepositoryState(controller_pointer, repository_state);
	}
	return return_status;
}


int deleteController(controller* controller_pointer, char* location_code) {
	int return_status;
	int location_code_integer = atoi(location_code);

	return_status = delete(controller_pointer->the_repository, location_code_integer);
	if (return_status == 0) {
		PastRepositoryState* repository_state = createRepositoryState(controller_pointer->the_repository);
		registerRepositoryState(controller_pointer, repository_state);
	}
	return return_status;
}



int undo(controller* controller_pointer) {
	int i;
	if (controller_pointer->repository_index <= 0) {
		return 0;
	}

	PastRepositoryState* state_to_revert_to = (PastRepositoryState*)controller_pointer->hystory_of_repository[controller_pointer->repository_index - 1];
	repository* new_repository = createRepository();
	new_repository->capacity = state_to_revert_to->capacity;
	new_repository->size = state_to_revert_to->size;
	for (i = 0; i < state_to_revert_to->size; i++) {
		barricade* current_barricade = state_to_revert_to->list_of_elements[i];
		barricade* barricade_to_add = createBarricade(current_barricade->location_code, current_barricade->visibility_in_area, current_barricade->barricade_type,
			current_barricade->barricade_sturdiness);
		new_repository->elements[i] = barricade_to_add;
	}

	destroyRepository(controller_pointer->the_repository);
	controller_pointer->the_repository = new_repository;
	controller_pointer->repository_index -= 1;
	return 4;
}


int redo(controller* controller_pointer) {
	int i;
	if (controller_pointer->repository_index >= controller_pointer->hystory_of_repository_size - 1) {
		return 0;
	}

	PastRepositoryState* state_to_revert_to = (PastRepositoryState*)controller_pointer->hystory_of_repository[controller_pointer->repository_index + 1];
	repository* new_repository = createRepository();
	new_repository->capacity = state_to_revert_to->capacity;
	new_repository->size = state_to_revert_to->size;
	for (i = 0; i < state_to_revert_to->size; i++) {
		barricade* current_barricade = state_to_revert_to->list_of_elements[i];
		barricade* barricade_to_add = createBarricade(current_barricade->location_code, current_barricade->visibility_in_area, current_barricade->barricade_type,
			current_barricade->barricade_sturdiness);
		new_repository->elements[i] = barricade_to_add;
	}

	destroyRepository(controller_pointer->the_repository);
	controller_pointer->the_repository = new_repository;
	controller_pointer->repository_index += 1;
	return 4;
}



void listAll(controller* controller_pointer, char* string_to_print) {
	int i;
	char location_code_string[20];
	char barricade_sturdiness_string[20];
	strcpy(string_to_print, "");
	for (i = 0; i < controller_pointer->the_repository->size; i++) {
		barricade* barricade_to_check = (barricade*)controller_pointer->the_repository->elements[i];
		_itoa(barricade_to_check->location_code, location_code_string, 10);
		strcat(string_to_print, location_code_string);
		strcat(string_to_print, " ");
		strcat(string_to_print, barricade_to_check->visibility_in_area);
		strcat(string_to_print, " ");
		strcat(string_to_print, barricade_to_check->barricade_type);
		strcat(string_to_print, " ");
		_itoa(barricade_to_check->barricade_sturdiness, barricade_sturdiness_string, 10);
		strcat(string_to_print, barricade_sturdiness_string);
		strcat(string_to_print, "\n");
	}
}


void listType(controller* controller_pointer, char* test_barricade_type, char* string_to_print) {
	int i;
	char location_code_string[20];
	char barricade_sturdiness_string[20];
	strcpy(string_to_print, "");
	for (i = 0; i < controller_pointer->the_repository->size; i++) {
		barricade* barricade_to_check = (barricade*)controller_pointer->the_repository->elements[i];
		if (strcmp(barricade_to_check->barricade_type, test_barricade_type) == 0) {
			_itoa(barricade_to_check->location_code, location_code_string, 10);
			strcat(string_to_print, location_code_string);
			strcat(string_to_print, " ");
			strcat(string_to_print, barricade_to_check->visibility_in_area);
			strcat(string_to_print, " ");
			strcat(string_to_print, barricade_to_check->barricade_type);
			strcat(string_to_print, " ");
			_itoa(barricade_to_check->barricade_sturdiness, barricade_sturdiness_string, 10);
			strcat(string_to_print, barricade_sturdiness_string);
			strcat(string_to_print, "\n");
		}
	}
}


void listSturdinessAscending(controller* controller_pointer, char* test_barricade_sturdiness, char* string_to_print) {
	int i;
	barricade* list_of_filtered_barricades[1000];
	int length = 0;
	char location_code_string[20];
	char barricade_sturdiness_string[20];
	int test_barricade_sturdiness_integer = atoi(test_barricade_sturdiness);
	strcpy(string_to_print, "");

	for (i = 0; i < controller_pointer->the_repository->size; i++) {
		barricade* barricade_to_check = (barricade*)controller_pointer->the_repository->elements[i];
		if (barricade_to_check->barricade_sturdiness <= test_barricade_sturdiness_integer) {
			list_of_filtered_barricades[length] = controller_pointer->the_repository->elements[i];
			length += 1;
		}
	}

	sortAscending(list_of_filtered_barricades, length, compareBarricadesByVisibility);

	for (i = 0; i < length; i++) {
		_itoa(list_of_filtered_barricades[i]->location_code, location_code_string, 10);
		strcat(string_to_print, location_code_string);
		strcat(string_to_print, " ");
		strcat(string_to_print, list_of_filtered_barricades[i]->visibility_in_area);
		strcat(string_to_print, " ");
		strcat(string_to_print, list_of_filtered_barricades[i]->barricade_type);
		strcat(string_to_print, " ");
		_itoa(list_of_filtered_barricades[i]->barricade_sturdiness, barricade_sturdiness_string, 10);
		strcat(string_to_print, barricade_sturdiness_string);
		strcat(string_to_print, "\n");
	}
}


void listSturdinessDescending(controller* controller_pointer, char* test_barricade_sturdiness, char* string_to_print) {
	int i;
	barricade* list_of_filtered_barricades[1000];
	int length = 0;
	char location_code_string[20];
	char barricade_sturdiness_string[20];
	int test_barricade_sturdiness_integer = atoi(test_barricade_sturdiness);
	strcpy(string_to_print, "");

	for (i = 0; i < controller_pointer->the_repository->size; i++) {
		barricade* barricade_to_check = (barricade*)controller_pointer->the_repository->elements[i];
		if (barricade_to_check->barricade_sturdiness <= test_barricade_sturdiness_integer) {
			list_of_filtered_barricades[length] = controller_pointer->the_repository->elements[i];
			length += 1;
		}
	}

	sortDescending(list_of_filtered_barricades, length, compareBarricadesByVisibility);

	for (i = 0; i < length; i++) {
		_itoa(list_of_filtered_barricades[i]->location_code, location_code_string, 10);
		strcat(string_to_print, location_code_string);
		strcat(string_to_print, " ");
		strcat(string_to_print, list_of_filtered_barricades[i]->visibility_in_area);
		strcat(string_to_print, " ");
		strcat(string_to_print, list_of_filtered_barricades[i]->barricade_type);
		strcat(string_to_print, " ");
		_itoa(list_of_filtered_barricades[i]->barricade_sturdiness, barricade_sturdiness_string, 10);
		strcat(string_to_print, barricade_sturdiness_string);
		strcat(string_to_print, "\n");
	}
}



PastRepositoryState* createRepositoryState(repository* repository) {
	PastRepositoryState* repository_state = (PastRepositoryState*)malloc(sizeof(PastRepositoryState));
	repository_state->capacity = repository->capacity;
	repository_state->size = repository->size;
	repository_state->list_of_elements = (GenericElement*)malloc(sizeof(GenericElement) * repository_state->capacity);
	
	int i;
	for (i = 0; i < repository->size; i++) {
		barricade* barricade_to_add = (barricade*)repository->elements[i];
		barricade* new_barricade = createBarricade(barricade_to_add->location_code, barricade_to_add->visibility_in_area, barricade_to_add->barricade_type,
			barricade_to_add->barricade_sturdiness);
		repository_state->list_of_elements[i] = new_barricade;
	}

	return repository_state;
}


void destroyRepositoryState(PastRepositoryState* repository_state) {
	int i;
	for (i = 0; i < repository_state->size; i++) {
		destroyBarricade(repository_state->list_of_elements[i]);
	}
	free(repository_state->list_of_elements);
	free(repository_state);
}