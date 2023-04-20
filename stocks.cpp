#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
const int size = 30;
void clear();

void print(char map[][30],int yPos,int value){
	for (int i = 0 ; i < size ; i++){
		if (yPos == i){
			printf("%d ",100-value);
		}
		else{
			printf("   ");
		}
		for (int j = 0 ; j < size ; j++){
			printf("%c",map[i][j]);
		}
		printf("\n");
	}
}

int main(){
	srand(time(0));
	
	int init;
	init = rand() % 50 + 1;
	int forward = 1;
	int limits[5] = {10,100,1000,10000};
	int currLimit = 0;
	
	char map[size][size] = {'\0'};
	
	for (int i = 0 ; i < size ; i++){
		for (int j = 0 ; j < size ; j++){
			if (j == 0){
				map[i][j] = '|';
			}
			else if (i == 29){
				map[i][j] = '_';
			}
			else {
				map[i][j] = ' ';
			}
		}
	}
	
	while(true){
		clear();
		int max = init+rand()%10+1;
		int min = init-rand()%10+1;
		
		bool trend = rand()%2;
		if (trend){
			init = max;
		}
		else{
			init = min;
		}
		int yPos;
		if (init <= 0){
			init+=20;
		}
		if (init >= 100){
			init-=20;
		}
		if (init){
			int remainder = init % limits[currLimit];
			yPos = (init-remainder) / limits[currLimit];
		}
//		else if (init < 1000){
//			int remainder = init % limits[currLimit+1];
//			yPos = (init-remainder) / limits[currLimit+1];			
//		}
		
		int xPos = forward;
		
		//memmove
		if (forward >= 29){
			int a = size-1;	
			for (int i = 0 ; i < a ; i++){
				map[i][1] = '\0';
			}
			
			for (int i = 0 ; i < a ; i++){
				for (int j = 2 ; j < size ; j++){
					map[i][j-1] = map[i][j];
				}
			}
			
			for (int i = 0 ; i < a ; i++){
				map[i][29] = '\0';
			}			
			
			for (int i = 0 ; i < a ; i++){
				if (yPos != i){
					map[i][28] = ' ';
				}
				else{
					map[yPos][28] = '#';
				}
			}
		}
		else{
			map[yPos][xPos] = '#';	
		}
	
//		printf("X ->%d  Y -> %d\n",xPos,yPos);
//		printf("%d\n",init);

		forward++;
		print(map,yPos,init);	
		Sleep(10);
	}

//	int arr[3][3] = {
//		{1,2,3},
//		{1,2,3},
//		{1,2,3}
//	};
//	
//	for (int i = 0 ; i < 3 ; i++){
//		arr[i][0] = '\0';
//	}
//	
//	for (int i = 0 ; i < 3 ; i++){
//		for (int j = 1; j < 3 ; j++){
//			arr[i][j-1] = arr[i][j];
//		}
//	}
//	
//	for (int i = 0 ; i < 3 ; i++){
//		arr[i][2] = '\0';
//	}
//	
//	
//	
//	
//	
//	for (int i = 0 ; i < 3 ; i++){
//		for (int j = 0 ; j < 3 ; j++){
//			printf("%d",arr[i][j]);
//		}
//		printf("\n");
//	}
	

	
	return 0;
}




void clear(){
	system("CLS");
}
