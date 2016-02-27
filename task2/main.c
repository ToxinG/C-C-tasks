#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

struct Note {
	int id;
	char *name;
	char *nmbr;
};

struct DataBase {
	int size;
	Note *contact;
};

struct Stack {
	int *num;
	int top;
	int size;
};

FILE *data;
const char *nameOfFile;
DataBase phBook;
int currentID;
Stack freeInd;

char *getword(FILE *in) {
	char *slark = (char *)malloc(0 * sizeof(char));
	char c = fgetc(in);
	int i = 0, j = 0;
	while ((c != ' ') && (c != '\n') && (c != EOF)) {
		if (j % 64 == 0) {
			j++;
			slark = (char *)realloc(slark, j * 64 * sizeof(char));
		}
		slark[i] = c;
		i++;
		c = fgetc(in);
	}
	slark[i] = '\0';
	return slark;
}

bool inputIsCorrect(char *input) {
	if (input == "") {
		printf("Error: input is missing.\n");
		return false;
	}
	int i = 0;
	if (isalpha(input[0])) {
		while (input[i] != '\0') {
			if (!isalpha(input[i++])) {
				printf("Error: only letters (A-Z, a-z) are allowed for names.\n");
				return false;
			}
		}
	}
	else {
		while (input[i] != '\0') {
			if (isdigit(input[i++])) {
				return true;
			}
		}
		printf("Error: numbers without any digits are not allowed.\n");
		return false;
	}
	return true;
}

char *unify(char *input) {
	char *ans = (char *)malloc(strlen(input) * sizeof(char));
	int i = 0, j = 0;
	if (isalpha(input[0])) {
		while (input[i] != '\0')
			ans[i] = tolower(input[i++]);
		ans[i] = '\0';
	}
	else {
		while (input[i] != '\0')
		{
			if (isdigit(input[i]))
				ans[j++] = input[i];
			i++;
		}
		ans[j] = '\0';
	}
	return ans;
}

void find(char *input) {
	bool ans = false;
	input = unify(input);
	if (isdigit(input[0])) {
		for (int i = 0; i < phBook.size; i++) {
			if ((phBook.contact[i].id > 0) && (unify(phBook.contact[i].nmbr) == input)) {
				printf("%d %s %s\n", phBook.contact[i].id, phBook.contact[i].name, phBook.contact[i].nmbr);
				ans = true;
			}
		}
	}
	else {
		for (int i = 0; i < phBook.size; i++) {
			if ((phBook.contact[i].id > 0) && (strstr(unify(phBook.contact[i].name), input))) {
				printf("%d %s %s\n", phBook.contact[i].id, phBook.contact[i].name, phBook.contact[i].nmbr);
				ans = true;
			}
		}
	}
	if (ans == false) {
		printf("Error: no contacts with given informaion have been found.\n");
	}
	return;
}

void create(char *name, char *number) {
	if (freeInd.top > 0) {
		phBook.contact[freeInd.num[freeInd.top - 1]].id = currentID;
		phBook.contact[freeInd.num[freeInd.top - 1]].name = name;
		phBook.contact[freeInd.num[freeInd.top - 1]].nmbr = number;
		freeInd.top--;
	}
	else {
		phBook.contact[phBook.size].id = currentID;
		phBook.contact[phBook.size].name = name;
		phBook.contact[phBook.size].id = currentID;
		phBook.size++;
		fprintf(data, "%d, %s %s\n", currentID++, name, number);
		return;
	}
}

void del(int id) {
	int x = -1;
	for (int i = 0; i < phBook.size; i++) {
		if (phBook.contact[i].id == id) {
			x = i;
			break;
		}
	}
	if (x >= 0) {
		phBook.contact[x].id = 0;
		freeInd.num[freeInd.top++] = x;
		if (freeInd.top == freeInd.size) {
			freeInd.size *= 2;
			freeInd.num = (int *)realloc(freeInd.num, freeInd.size * sizeof(int));
		}
		for (int i = 0; i < phBook.size; i++) {
			if (phBook.contact[i].id > 0)
				fprintf(data, "%d %s %s\n", phBook.contact[i].id, phBook.contact[i].name, phBook.contact[i].nmbr);
		}
		return;
	}
}

void change(int id, char *cmd, char *input) {
	int x = -1;
	for (int i = 0; i < phBook.size; i++) {
		if (phBook.contact[i].id == id) {
			x = i;
			break;
		}
	}
	if (x >= 0) {
		if (cmd == "number")
			strcpy(phBook.contact[x].nmbr, input);
		else if (cmd == "name")
			strcpy(phBook.contact[x].name, input);
		else {
			printf("Error: failed to identify the command.\n");
			return;
		}
		for (int i = 0; i < phBook.size; i++) {
			if (phBook.contact[i].id > 0)
				fprintf(data, "%d %s %s\n", phBook.contact[i].id, phBook.contact[i].name, phBook.contact[i].nmbr);
		}
	}
	return;
}

int main(int argc, char * argv[]) {
	nameOfFile = argv[1];
	data = fopen(nameOfFile, "a+");
	phBook.size = 0;
	phBook.contact = (Note *)malloc(phBook.size * sizeof(Note));
	freeInd.top = 0;
	freeInd.size = 1;
	freeInd.num = (int *)malloc(freeInd.size * sizeof(int));
	int id, idmax = 0;
	while (fscanf(data, "%d", &id) == 1) {
		phBook.size++;
		phBook.contact = (Note *)realloc(phBook.contact, phBook.size * sizeof(Note));
		phBook.contact[phBook.size - 1].id = id;
		phBook.contact[phBook.size - 1].name = getword(data);
		phBook.contact[phBook.size - 1].nmbr = getword(data);
	}
	if (phBook.size == 0)
		currentID = 1;
	else
		currentID = phBook.contact[phBook.size - 1].id + 1;
	char *cmd = (char *)malloc(8 * sizeof(char));
	char *name, *number, *input;
	while (0 == 0) {
		scanf("%s", cmd);
		if (cmd == "find") {
			input = getword(stdin);
			if (inputIsCorrect(input))
				find(input);
			free(input);
		}
		else if (cmd == "create") {
			name = getword(stdin);
			number = getword(stdin);
			create(name, number);
			free(name);
			free(number);
		}
		else if (cmd == "delete") {
			scanf("%d", &id);
			del(id);
		}
		else if (cmd == "change") {
			scanf("%d %s", &id, cmd);
			input = getword(stdin);
			if (inputIsCorrect(input))
				change(id, cmd, input);
			free(input);
		}
		else if (cmd == "exit") {
			fclose(data);
			free(phBook.contact);
			free(freeInd.num);
			free(cmd);
			free(input);
			free(name);
			free(number);
		}
		else {

		}
	}
	return 0;
}