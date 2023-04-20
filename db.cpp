#include "__lib__.h"
#include "__init__.h"
#include "__view__.h"
#include "__checker__.h"

void mainMenu();
void redirect();
Database* dbReturn(char*);

void addTable(){
	char tableName[100];
	char dbName[100];
	bool prompt;
	if (totaldb == 0){
		printf("There is no database available!\n");
	}
	else{
		do{
			prompt = true;
			printDB();
			printf("\n");
			printf("Insert Database Name: ");	
			scanf("%[^\n]s",dbName);
			getchar();
			if (dbCheck(dbName) == false) {
				printf("Database not found in the system\n\n");
				prompt = false;
			}
		}
		while(prompt == false);
	
		
		printf("What is the table name? ");
		scanf("%[^\n]s",tableName);
		getchar();
		char desiredTable[20];
		char desiredName[50];
		char allDatatypes[100][20];
		char allDatanames[100][50];
		char fixedDT[10][10] = {"int","string","float","date"};
		int iterator = 0;
		do{
			bool valid;
			do{
				valid = false;
				printf(" What data type do you want to insert? [int, string, float, date]\n Type 'exit' to cancel, 'stop' to stop\n >> ");
				scanf("%[^\n]s",desiredTable);
				getchar();
				strlwr(desiredTable);
				if (strcmp(desiredTable,"exit") == 0 || strcmp(desiredTable,"stop") == 0){
					break;
				}
				for (int i = 0 ; i < 4; i++){
					if (strcmp(desiredTable,fixedDT[i]) == 0){
						valid = true;					
						break;
					}
				}
			}
			while(valid == false);
			
			if (strcmp(desiredTable,"exit") == 0){
				break;
			}
			else if (strcmp(desiredTable,"stop") == 0){
				break;
			}
			
			do{
				printf("What will be %s table name be? [length must be bigger than 2] : ",desiredTable);
				scanf("%[^\n]s",desiredName);
				getchar();
				strlwr(desiredName);
				if (strcmp(desiredName,"exit") == 0 || strcmp(desiredTable,"stop") == 0){
					break;
				}
			}
			while(strlen(desiredName) < 2);
			
			if (strcmp(desiredName,"exit") == 0){
				break;
			}
			else if (strcmp(desiredName,"stop") == 0){
				break;
			}		
			strcpy(allDatatypes[iterator],desiredTable);
			strcpy(allDatanames[iterator],desiredName);
			iterator++;
			memset(desiredTable,'\0',20);
			memset(desiredName,'\0',50);
		}
		while(true);
		
		if (strcmp(desiredName,"exit") == 0 || strcmp(desiredTable,"exit") == 0){
			printf("Table was not created, Press enter to continue...");
		}
		else if (strcmp(desiredName,"stop") == 0 || strcmp(desiredTable,"stop") == 0){
			Table* temp = pushTable(tableName,dbReturn(dbName));
	
			for (int i = 0 ; i < iterator ; i++){
				if (strcmp(allDatatypes[i],"int") == 0){
					pushIntCol(allDatanames[i],temp);
				}
				else if (strcmp(allDatatypes[i],"string") == 0){
					pushStrCol(allDatanames[i],temp);
				}
				else if (strcmp(allDatatypes[i],"float") == 0){
					pushFloatCol(allDatanames[i],temp);
				}
				else{
					pushDateCol(allDatanames[i],temp);
				}
				temp->length++;
			}
			printf("Table successfully added in the database, Press enter to continue\n");
		}
	}
	redirect();
}



void addDatabase(){
	char dbName[100];
	bool test;
	memset(dbName,'\0',100);
	do{
		test = false;
		printf("What is the database name?\n");
		scanf("%[^\n]s",dbName);
		getchar();
		if (dbCheck(dbName)){
			printf("Database already exist in the system!\n");
			memset(dbName,'\0',100);
			test = true;
		}
	}
	while(test == true || strlen(dbName) == 0);
	
	pushDatabase(dbName);
	printf("Database is created!\n");
	redirect();
}

void viewAllTables(){
	char dbName[100];
	bool prompt;
	if (totaldb == 0){
		printf("There is no database available!\n");
	}
	else{
		do{
			prompt = true;
			printDB();
			printf("\n");
			printf("Insert Database Name: ");	
			scanf("%[^\n]s",dbName);
			getchar();
			if (dbCheck(dbName) == false) {
				printf("Database not found in the system\n\n");
				prompt = false;
			}
		}
		while(prompt == false);
		printAllTable(dbReturn(dbName));
		redirect();
	}
}

void seedTable(){
	char dbName[100];
	char tableName[100];
	int length;
	
	if (totaldb == 0){
		printf("There is no database in the system!");
		redirect();
	}
	else{
		bool prompt;
		bool outofprogram = false;
		char input;
		char dtArr[100][20];
		char nameArr[100][100];
		
		do{
			do{
				prompt = true;
				printDB();
				printf("\n");
				printf("Insert Database Name: ");	
				scanf("%[^\n]s",dbName);
				getchar();
				if (dbCheck(dbName) == false) {
					printf("Database not found in the system\n\n");
					prompt = false;
				}
			}
			while(prompt == false);
//			printAllTable(dbReturn(dbName));
			printf("\nThe database -> %s\n",dbName);	
			
			prompt = true;
			
			
			do{
				do{
					printTable(dbReturn(dbName));
					printf("Insert table name: ");
					scanf("%[^\n]s",tableName);
					getchar();
					if (tableCheck(dbName,tableName) == false){
						printf("Table not found in the system\n\n");
					}	
				}
				while(tableCheck(dbName,tableName) == false);
				viewTable(tableReturn(dbName,tableName));	
				retreiveTableData(tableReturn(dbName,tableName),dtArr,nameArr,&length);				
				do{
					printf("1. Seed column\n");
					printf("2. View another table\n");
					printf("3. Go Back\n");
					printf("4. Exit\n");
					printf(">> "); 
					scanf("%c",&input);
					getchar();
				}
				while(input != '1' && input != '2' && input != '3' && input != '4');
				if (input == '1'){
					printf("Data by order -> ");
					for (int i = 0 ; i < length ; i++){
						printf("%s ",dtArr[i]);
					}
					printf("\n");
					
					bool entry = true;
					char dataInput[200];
					char tempInput[200];
					char dataGiven[10][100];
				int iterator = 0;
					do{
						iterator = 0;
						entry = true;
						printf("Please enter data by order and by type seperated by comma (,)\n>> ");
						scanf("%[^\n]s",dataInput);
						getchar();
						strcpy(tempInput,dataInput);
						char* token = strtok(dataInput,",");
						while(token){
							char* result = strpbrk(token, "0123456789");
							if (strcmp(dtArr[iterator],"int") == 0 || strcmp(dtArr[iterator],"float") == 0){
								if (result == NULL){
									entry = false;
								}
							}
							if (entry == false){
								printf("Please enter valid datatype in order\n");
								break;
							}
							strcpy(dataGiven[iterator],token);
							token = strtok(NULL,",");
							iterator++;
						}
					}
					while(entry == false);
					
					Table* t = tableReturn(dbName,tableName);
					t->rows++;
					for (int i = 0 ; i < iterator ; i++){
						if (strcmp(dtArr[i],"int") == 0){
							IntColumn* ic = intReturn(t,nameArr[i]);
							ic->integer[ic->length] = atoi(dataGiven[i]);
							ic->length++;
						}
						else if (strcmp(dtArr[i],"string") == 0){
							StringColumn* sc = stringReturn(t,nameArr[i]);
							strcpy(sc->string[sc->length],dataGiven[i]);
							sc->length++;
						}
						else if (strcmp(dtArr[i],"date") == 0){
							DateColumn* dc = dateReturn(t,nameArr[i]);
							strcpy(dc->date[dc->length],dataGiven[i]);
							dc->length++;
						}
						else{
							FloatColumn* fc = floatReturn(t,nameArr[i]);
							fc->fpoint[fc->length] = float(atoi(dataGiven[i]));
							fc->length++;
						}
					}
					
					continue;
				}
				else if (input == '2'){
					continue;
				}
				else if (input == '3'){
					break;
				}
				else{
					outofprogram = true;
					break;					
				}
				getchar();
				memset(tableName,'\0',100);
			}while(true);
			memset(dbName,'\0',100);
		} while(outofprogram == false);	
		redirect();	
	}	
	
}

void viewTable(){
	char dbName[100];
	char tableName[100];
	
	if (totaldb == 0){
		printf("There is no database in the system!");
		redirect();
	}
	else{
		bool prompt;
		bool outofprogram = false;
		char input;

		
		do{
			do{
				prompt = true;
				printDB();
				printf("\n");
				printf("Insert Database Name: ");	
				scanf("%[^\n]s",dbName);
				getchar();
				if (dbCheck(dbName) == false) {
					printf("Database not found in the system\n\n");
					prompt = false;
				}
			}
			while(prompt == false);
//			printAllTable(dbReturn(dbName));
			printf("\nThe database -> %s\n",dbName);	
			
			prompt = true;
			
			
			do{
				do{
					printTable(dbReturn(dbName));
					printf("Insert table name: ");
					scanf("%[^\n]s",tableName);
					getchar();
					if (tableCheck(dbName,tableName) == false){
						printf("Table not found in the system\n\n");
					}	
				}
				while(tableCheck(dbName,tableName) == false);
				viewTable(tableReturn(dbName,tableName));					
				
				do{
					printf("1. View another table\n");
					printf("2. Go Back\n");
					printf("3. Exit\n");
					printf(">> ");
					scanf("%c",&input);
					getchar();
				}
				while(input != '1' && input != '2' && input != '3');
				
				if (input == '1'){
					continue;
				}
				else if (input == '2'){
					break;
				}
				else{
					outofprogram = true;
					break;					
				}
				getchar();
				memset(tableName,'\0',100);
			}while(true);
			memset(dbName,'\0',100);
		} while(outofprogram == false);	
		redirect();	
	}	
}

void mainMenu(){
	char input;
	do{
		system("CLS");
		printf("What do you want to do?\n");
		printf("1. Add Database\n");
		printf("2. Add Table\n");
		printf("3. Seed table\n");
		printf("4. View all tables\n");
		printf("5. View table\n");
		scanf("%c",&input);	
	}
	while(input != '1' && input != '2' && input != '3' && input != '4' && input != '5');
	getchar();
	if (input == '1'){
		addDatabase();
	}
	else if (input == '2'){
		addTable();
	}
	else if (input == '3'){
		seedTable();
	}
	else if (input == '4'){
		viewAllTables();
	}
	else if (input == '5'){
		viewTable();
	}
	else{
		mainMenu();
	}
}

void nullCheck(Database *db){
	for (int i = 0 ; i < 997 ; i++){
		printf("%d. %s\n",i,db->tablesHead[i] == NULL ? "NULL" : "NOT NULL");
	}
}



int main(){

	mainMenu();

//	Database* db = pushDatabase("MyDB");	
//	Table* t = pushTable("Darren",db);
//	pushStrCol("Phone Number",t);
//	pushStrCol("First Name",t);
//	pushStrCol("Last Name",t);
//	pushIntCol("Age",t);
//	
//	Table* t2 = pushTable("Hello world",db);
//	StringColumn* a2 = pushStrCol("Order ID",t2);
//	StringColumn* b2 = pushStrCol("Order Name",t2);
//	DateColumn* c2 =  pushDateCol("Deadline",t2);
//	IntColumn* d2 = pushIntCol("Quantity",t2);	
//	t2->length = 4;
//	t2->rows = 3;
//	
//	a2->length = 4;
//    b2->length = 4;
//    c2->length = 4;
//    d2->length = 4;
//	
//    strcpy(a2->string[0], "ORD001");
//    strcpy(b2->string[0], "Keyboard");
//    strcpy(c2->date[0], "4/10/2023");
//    d2->integer[0] = 10;
//
//    strcpy(a2->string[1], "ORD002");
//    strcpy(b2->string[1], "Mouse");
//    strcpy(c2->date[1], "4/12/2023");
//    d2->integer[1] = 5;
//
//    strcpy(a2->string[2], "ORD003");
//    strcpy(b2->string[2], "Monitor");
//    strcpy(c2->date[2], "4/15/2023");
//    d2->integer[2] = 2;
//    

//    
//    strcpy(a2->string[3], "ORD004");
//    strcpy(b2->string[3], "Microphone");
//    strcpy(c2->date[3], "4/18/2023");
//    d2->integer[3] = 9;
//
//	viewTable(t2);
//	
//	char dtArr[100][20];
//	char nameArr[100][100];
//	int length;
	
//	retreiveTableData(tableReturn("MyDB","Hello world"),dtArr,nameArr, &length);
//	

//	for (int i = 0; i < length; i++) {
//	    printf("%s %s\n", dtArr[i], nameArr[i]);
//	}
	
//	printAllTable(db);
//	printf("%s",Databases[332]->tablesHead[604]->strHead[4]->stringName);

//	Database* db = newDatabase("Wow");


	
	return 0;
}

void redirect(){
	printf("Press enter to continue... ");
	getchar();
	system("CLS");
	mainMenu();
}


