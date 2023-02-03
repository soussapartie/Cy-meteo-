#include <stdio.h>
#include <string.h>
#include<stdlib.h>

typedef struct Station Station;
struct Station{
int id;
char date[26];
int P_mer;
int Direc_vent;
int Vit_vent;
int hum;
int press;
int var_press;
int preci;
int coord;
int temper;
int temp_min;
int temp_max;
int altit;
int com;
};

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
}
int mode = 0;
int size = 1;
int temp = 0;
int i = 0;
char c;
FILE *fp = fopen(argv[1],"r");
if (!fp) {
printf("Can't open file %s\n", argv[1]);
return 2;
}
Station** ls = malloc(sizeof(Station*));
Station* s = malloc(sizeof(Station));
char* string = calloc(sizeof(char),26);
while((c = fgetc(fp)) != EOF) {
if(c == '\n') {
ls = realloc(ls, sizeof(Station*) * (size + 1));
ls[size] = s;
size++;
mode = 0;
s = malloc(sizeof(Station));
i = 0;
}
if (c == ';') {
if(mode == 0){
s-> id = temp;
temp = 0;
mode = 1;
}
if(mode == 1){
strcpy(s->date, string);
memset(string, 0, 26);
temp = 0;
mode = 2;
i = 0;
}
if(mode == 2){
s-> P_mer = temp;
temp = 0;
mode = 3;
}
if(mode == 3){
s-> Direc_vent = temp;
temp = 0;
mode = 4;
}
if(mode == 4){
s-> Vit_vent = temp;
temp = 0;
mode = 5;
}
if(mode == 5){
s-> hum = temp;
temp = 0;
mode = 6;
}
if(mode == 6){
s-> press = temp;
temp= 0;
				mode = 7;
			}
			if(mode == 7){
				s-> var_press = temp;
				temp = 0;
				mode = 8;
			}
			if(mode == 8){
				s-> preci = temp;
				temp = 0;
				mode = 9;
			}
			if(mode == 9){
				s-> coord = temp;
				temp = 0;
				mode = 10;
			}
			if(mode == 10){
				s-> temper = temp;
				temp = 0;
				mode = 11;
			}
			if(mode == 11){
				s-> temp_min = temp;
				temp = 0;
				mode = 12;
			}
			if(mode == 12){
				s-> temp_max = temp;
				temp = 0;
				mode = 13;
			}
  			if(mode == 13){
				s-> altit = temp;
				temp = 0;
				mode = 14;
			}
			if(mode == 14){
				s-> com = temp;
				temp = 0;
			}
		}
		else if(mode == 2){
			string[temp] = c;
			temp++;
			}
		else{
			temp * 10;
			temp + (int)(c-'0');
			}
		}

	return 0;
}
	 
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
