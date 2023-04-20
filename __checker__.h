Database* dbReturn(char* dbName){
	Database* temp = NULL;
	bool found = false;
	for (int i = 0 ; i < DB_LIMIT ; i++){
		if (Databases[i] != NULL){
			if (strcmp(Databases[i]->dbName,dbName) == 0){
				temp = Databases[i];
				found = true;
				break;
			}
			if (found == true) break;
		}
	}
	return temp;	
}

bool dbCheck(char *dbName){
	bool found = false;
	Database* db = NULL;
	for (int i = 0 ; i < DB_LIMIT ; i++){
		if (Databases[i] != NULL){
			if (strcmp(Databases[i]->dbName,dbName) == 0){
				found = true;
				break;
			}
			if (found == true) break;
		}
	}
	return found;
}

Table* tableReturn(char* dbName, char* tableName){
	Table* tb = NULL;
	Database* db = dbReturn(dbName);
	int len = 997;
	bool v = false;
	for (int i = 0 ; i < len ; i++){
		Table* t = db->tablesHead[i];
		
		while(t){
			if (strcmp(tableName,t->tableName) == 0){
				tb = t;
				v = true;
				break;
			}
			if (v == true) break;
			t = t->next;
		}
		if (v == true) break;
	}
	return tb;
}

bool tableCheck(char*dbName, char *tableName){
	
	Database* db = dbReturn(dbName);
	int len = 997;
	
	for (int i = 0 ; i < len ; i++){
		Table* t = db->tablesHead[i];
		
		while(t){
			if (strcmp(tableName,t->tableName) == 0){
				return true;
			}
			t = t->next;
		}
	}
	
	return false;
}

IntColumn* intReturn(Table* tb, char* intName){
	int len = 11;
	
	for (int i = 0 ; i < len ; i++){
		IntColumn* ic = tb->intHead[i];
		while(ic){
			if (strcmp(ic->intName,intName) == 0){
			return ic;
			}
		}
	}

	return NULL;
}

// Returns a pointer to the StringColumn structure with the specified name
StringColumn* stringReturn(Table* tb, char* stringName) {
	int len = 11;
	
	for (int i = 0 ; i < len ; i++){
		StringColumn* sc = tb->strHead[i];
		while(sc){
			if (strcmp(sc->stringName,stringName) == 0){
				return sc;
			}
		}
	}
    return NULL;
}

// Returns a pointer to the DateColumn structure with the specified name
DateColumn* dateReturn(Table* tb, char* dateName) {
 	int len = 11;
	
	for (int i = 0 ; i < len ; i++){
		DateColumn* dc = tb->dateHead[i];
		while(dc){
			if (strcmp(dc->dateName,dateName) == 0){
			return dc;
			}
		}
	}
    return NULL;
}

// Returns a pointer to the FloatColumn structure with the specified name
FloatColumn* floatReturn(Table* tb, char* floatName) {
	int len = 11;
	
	for (int i = 0 ; i < len ; i++){
		FloatColumn* fc = tb->floatHead[i];
		while(fc){
			if (strcmp(fc->floatName,floatName) == 0){
			return fc;
			}
		}
	}
    return NULL;
}




