
void viewTable(Table* t){
	
	for (int i = 0 ; i < t->length ; i++){
		printf("=================");
	}
	
	int width = 15;

	printf("\n");

	for (int i = 0 ; i < TABLE_COLUMN_LIMIT ; i++){
	IntColumn* intCurr = t->intHead[i]; StringColumn* strCurr = t->strHead[i];
	DateColumn* dateCurr = t->dateHead[i]; FloatColumn* floatCurr = t->floatHead[i];
		
		while(intCurr){
			int len = strlen(intCurr->intName);
			int pad = width - len;
			int left = pad / 2;
			int right = pad - left;
			printf("=%*s%s%*s=", left, "", intCurr->intName, right, "");
			intCurr = intCurr->next;
		}
		while(strCurr){
			int len = strlen(strCurr->stringName);
		    int pad = width - len;
		    int left = pad / 2;
		    int right = pad - left;
		    printf("=%*s%s%*s=", left, "", strCurr->stringName, right, "");
			strCurr = strCurr->next;
		}
		while(dateCurr){
			int len = strlen(dateCurr->dateName);
		    int pad = width - len;
		    int left = pad / 2;
		    int right = pad - left;
		    printf("=%*s%s%*s=", left, "", dateCurr->dateName, right, "");
			dateCurr = dateCurr->next;
		}
		while(floatCurr){
			int len = strlen(floatCurr->floatName);
		    int pad = width - len;
		    int left = pad / 2;
		    int right = pad - left;
			printf("=%*s%s%*s=", left, "", floatCurr->floatName, right, "");
			floatCurr = floatCurr->next;
		}	
	}
	
	printf("\n");
	for (int i = 0 ; i < t->length ; i++){
		printf("=================");
	}
	printf("\n");
	
	char strings[t->rows][t->length][100];
	for (int i = 0 ; i < t->rows ; i++){
		for (int j = 0 ; j < t->length ; j++){
			for (int k = 0 ; k < 100 ; k++){
				strings[i][j][k] = '\0';
			}
		}
	}
	
	int r=0,c=0;
	for (int i = 0 ; i < TABLE_COLUMN_LIMIT ; i++){
	IntColumn* intCurr = t->intHead[i]; StringColumn* strCurr = t->strHead[i];
	DateColumn* dateCurr = t->dateHead[i]; FloatColumn* floatCurr = t->floatHead[i];
		char tempstr[100];
		int caught = 0;
		
		while(intCurr){
			for (int j = 0 ; j < t->rows ; j++){
				sprintf(tempstr,"%d",intCurr->integer[j]);
				strcpy(strings[r][c],tempstr);
				memset(tempstr,'\0',100);
				c++;
			}
			c = 0;
			intCurr = intCurr->next;
			r++;
		}
		while(strCurr){
		    for (int j = 0 ; j < t->rows ; j++){
				strcpy(strings[r][c],strCurr->string[j]);
				c++;			
			}
			c = 0;
			strCurr = strCurr->next;
			r++;
		}
		while(dateCurr){
			
		    for (int j = 0 ; j < t->rows ; j++){
				strcpy(strings[r][c],dateCurr->date[j]);
				c++;	
			}
			c = 0;
			dateCurr = dateCurr->next;
			r++;
		}
		while(floatCurr){
		    for (int j = 0 ; j < t->rows ; j++){
				sprintf(tempstr,"%f",floatCurr->fpoint[j]);
				strcpy(strings[r][c],tempstr);
				memset(tempstr,'\0',100);
				c++;
			}
			c = 0;
			floatCurr = floatCurr->next;
			r++;
		}	
	}
	
	int R = t->rows;
	int C = t->length;

	for (int i = 0; i < R; i++) {
        for (int j = i + 1; j < C; j++) {
            // Swap elements
            char temp [100];
            strcpy(temp,strings[i][j]);
            strcpy(strings[i][j],strings[j][i]);
            strcpy(strings[j][i],temp);
        }
    }

	for (int l = 0 ; l < R  ; l++){
		for (int k = 0 ; k < C; k++){
			int len = strlen(strings[l][k]);
		    int pad = width - len;
		    int left = pad / 2;
		    int right = pad - left;
			printf("=%*s%s%*s=", left, "", strings[l][k], right, "");
		}
		printf("\n");

		for (int i = 0 ; i < t->length  ; i++){
			printf("=================");
		}
		printf("\n");
	}
}

void printDB(){
	int iter = 1;
	for (int i = 0 ; i < DB_LIMIT ; i++){
		if (Databases[i]){
			printf("%d. %s\n",iter,Databases[i]->dbName);
			iter++;
		}
	}
}

void printAllTable(Database* db){
	int len = 997;
	
	for (int i = 0 ; i < len ; i++){
		Table* curr = db->tablesHead[i];
		if (curr != NULL){
			printf("Table Name: %s", curr->tableName);
			while(curr){
				int c = 11;
				printf("\nInt: ");
				for (int j = 0 ; j < c ; j++){
					IntColumn *ic = curr->intHead[j];
					while(ic){
						printf("%s | ",ic->intName);
						ic = ic->next;
					};
				}
				printf("NULL");
				printf("\nStr: ");
				for (int j = 0 ; j < c ; j++){
					StringColumn *sc = curr->strHead[j];
					while(sc){
						printf("%s | ",sc->stringName);
						sc = sc->next;
					};
				}
				printf("NULL");
				printf("\nDate: ");
				for (int j = 0 ; j < c ; j++){
					DateColumn *dc = curr->dateHead[j];
					while(dc){
						printf("%s | ",dc->dateName);
						dc = dc->next;
					};
				}
				printf("NULL");
				printf("\nFloat: ");
				for (int j = 0 ; j < c ; j++){
					FloatColumn *fc = curr->floatHead[j];
					while(fc){
						printf("%s | ",fc->floatName);
						fc = fc->next;
					};
				}
				printf("NULL");
				curr = curr->next;
				printf("\n\n");
			}
		}
	}
	
}

void printTable(Database* db){
	int len = 997;
	int iter = 1;
	for (int i = 0 ; i < len ; i++){
		if (db->tablesHead[i] != NULL){
			printf("%d. %s\n",iter,db->tablesHead[i]->tableName);
			iter++;
		}
	}
}

void retreiveTableData(Table* t, char dtArr[100][20], char nameArr[100][100], int* length){
	int iter = 0;
	
	for (int i = 0 ; i < TABLE_COLUMN_LIMIT ; i++){
	IntColumn* intCurr = t->intHead[i]; StringColumn* strCurr = t->strHead[i];
	DateColumn* dateCurr = t->dateHead[i]; FloatColumn* floatCurr = t->floatHead[i];
		
		while(intCurr){
			strcpy(dtArr[iter],"int");
			strcpy(nameArr[iter],intCurr->intName);
			intCurr = intCurr->next;
			iter++;
		}
		while(strCurr){
			strcpy(dtArr[iter],"string");
			strcpy(nameArr[iter],strCurr->stringName);
			strCurr = strCurr->next;
			iter++;
		}
		while(dateCurr){
			strcpy(dtArr[iter],"date");
			strcpy(nameArr[iter],dateCurr->dateName);
			dateCurr = dateCurr->next;
			iter++;
		}
		while(floatCurr){
			strcpy(dtArr[iter],"float");
			strcpy(nameArr[iter],floatCurr->floatName);
			floatCurr = floatCurr->next;
			iter++;
		}	
	}
	
	*length = iter;
	
}
