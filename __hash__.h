#include "__lib__.h"

int hash(char *str, int size){
	int total = 0;
	for (int i = 0 ; i < strlen(str) ; i++){
		total += str[i];
	}
	return total % size;
}
