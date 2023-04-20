#include "__lib__.h"
#include "__hash__.h"
const int DB_LIMIT = 997;
const int DATABASE_TABLE_LIMIT = 997;
const int TABLE_COLUMN_LIMIT = 11;

struct IntColumn{
	int integer[100];
	int length;
	char intName[100];
	IntColumn* next;
};

struct StringColumn{
	char string[100][100];
	int length;
	char stringName[100];
	StringColumn* next;
};

struct DateColumn{
	char date[100][100];
	int length;
	char dateName[100];
	DateColumn* next;
};

struct FloatColumn{
	float fpoint[100];
	int length;
	char floatName[100];
	FloatColumn* next;
};
//database->

struct Table{
	char tableName[100];
	IntColumn *intHead[TABLE_COLUMN_LIMIT], *intNext[TABLE_COLUMN_LIMIT], *intTail[TABLE_COLUMN_LIMIT];
	StringColumn  *strHead[TABLE_COLUMN_LIMIT], *strNext[TABLE_COLUMN_LIMIT], *strTail[TABLE_COLUMN_LIMIT];
	DateColumn    *dateHead[TABLE_COLUMN_LIMIT], *dateNext[TABLE_COLUMN_LIMIT], *dateTail[TABLE_COLUMN_LIMIT];
	FloatColumn   *floatHead[TABLE_COLUMN_LIMIT], *floatNext[TABLE_COLUMN_LIMIT], *floatTail[TABLE_COLUMN_LIMIT];
	int length;
	int rows;
	Table* next;
}*Tables[997];

struct FK{
	struct Table* source;
	struct Table* dest;
};

struct Database{
	char dbName[100];
	Table* tablesHead[997];
	Table* tablesTail[997];
	FK* foreignKeys;
	int totalTables;
}*Databases[997];



IntColumn* newInt(char* name){
	IntColumn* temp = (IntColumn*)malloc(sizeof(IntColumn));
	memset(temp->integer,NULL,100*sizeof(int));
	strcpy(temp->intName,name);
	temp->next = NULL;
	temp->length = 0;
	return temp;
}

StringColumn* newString(char* name){
	StringColumn* temp = (StringColumn*)malloc(sizeof(StringColumn));
	memset(temp->string,NULL,100*sizeof(char[100]));
	strcpy(temp->stringName,name);
	temp->length = 0;
	temp->next = NULL;
	return temp;
}

DateColumn* newDate(char* name){
	DateColumn* temp = (DateColumn*)malloc(sizeof(DateColumn));
	memset(temp->date,NULL,100*sizeof(char[100]));
	strcpy(temp->dateName,name);
	temp->length = 0;
	temp->next = NULL;
	return temp;
}

FloatColumn* newFloat(char* name){
	FloatColumn* temp = (FloatColumn*)malloc(sizeof(FloatColumn));
	memset(temp->fpoint,NULL,100*sizeof(float));
	strcpy(temp->floatName,name);
	temp->length = 0;
	temp->next = NULL;
	return temp;
}

Table* newTable(char *tableName){
	Table* temp = (Table*) malloc(sizeof(Table));
	memset(temp->intHead,NULL,11*sizeof(IntColumn*)); memset(temp->intNext,NULL,11*sizeof(IntColumn*)); memset(temp->intTail,NULL,11*sizeof(IntColumn*));
	memset(temp->strHead,NULL,11*sizeof(StringColumn*)); memset(temp->strNext,NULL,11*sizeof(StringColumn*)); memset(temp->strTail,NULL,11*sizeof(StringColumn*));
	memset(temp->dateHead,NULL,11*sizeof(DateColumn*)); memset(temp->dateNext,NULL,11*sizeof(DateColumn*)); memset(temp->dateTail,NULL,11*sizeof(DateColumn*));
	memset(temp->floatHead,NULL,11*sizeof(FloatColumn*)); memset(temp->floatNext,NULL,11*sizeof(FloatColumn*)); memset(temp->floatTail,NULL,11*sizeof(FloatColumn*));
	
	strcpy(temp->tableName,tableName);
	temp->length = 0;
	temp->rows = 0;
	temp->next = NULL;
	return temp;
}

Database* newDatabase(char *dbName){
	Database* temp = (Database*) malloc(sizeof(Database));
	strcpy(temp->dbName,dbName);
	temp->totalTables = 0;
	memset(temp->tablesTail,0,997*sizeof(Table*));
	memset(temp->tablesHead,0,997*sizeof(Table*));
	temp->foreignKeys = NULL;
	return temp;
}


int totaldb = 0;
Database* pushDatabase(char* dbName){
	Database* temp = newDatabase(dbName);
	int pos = hash(dbName,DB_LIMIT);
	if (totaldb == DB_LIMIT) return NULL;
	
	if (Databases[pos] == NULL){
		Databases[pos] = temp;
	}
	else{
		while(Databases[pos] != NULL){
			pos = (pos + 1) % DB_LIMIT;
		}
		Databases[pos] = temp;
	}
	totaldb++;
	return temp;
}

//database-

Table* pushTable(char *tableName,Database* db){
	int pos = hash(tableName,DATABASE_TABLE_LIMIT);
	Table* temp = newTable(tableName);
	
	if (db->tablesHead[pos] == NULL){
		db->tablesHead[pos] = db->tablesTail[pos] = temp;	
	}
	else{
		db->tablesTail[pos]->next = temp;
		db->tablesTail[pos] = temp;
	}
	return temp;
}

IntColumn* pushIntCol(char* intStr, Table* table){
	int pos = hash(intStr,TABLE_COLUMN_LIMIT);
	IntColumn* temp = newInt(intStr);
	
	if (table->intHead[pos] == NULL){
		table->intHead[pos] = table->intTail[pos] = temp;
	}
	else{
		table->intTail[pos]->next = temp;
		table->intTail[pos] = temp;	
	}
	return temp;
}

StringColumn* pushStrCol(char* StrStr, Table *table){
	int pos = hash(StrStr,TABLE_COLUMN_LIMIT);
	StringColumn* temp = newString(StrStr);
	
	if (table->strHead[pos] == NULL){
		table->strHead[pos] = table->strTail[pos] = temp;
	}
	else{
		table->strTail[pos]->next = temp;
		table->strTail[pos] = temp;	
	}
	return temp;
}

DateColumn* pushDateCol(char* dateStr, Table* table){
	int pos = hash(dateStr,TABLE_COLUMN_LIMIT);
	DateColumn* temp = newDate(dateStr);
	
	if (table->dateHead[pos] == NULL){
		table->dateHead[pos] = table->dateTail[pos] = temp;
	}
	else{
		table->dateTail[pos]->next = temp;
		table->dateTail[pos] = temp;	
	}
	return temp;
}

FloatColumn* pushFloatCol(char* floatStr, Table* table){
	int pos = hash(floatStr,TABLE_COLUMN_LIMIT);
	FloatColumn* temp = newFloat(floatStr);
	
	if (table->floatHead[pos] == NULL){
		table->floatHead[pos] = table->floatTail[pos] = temp;
	}
	else{
		table->floatTail[pos]->next = temp;
		table->floatTail[pos] = temp;	
	}
	return temp;
}


