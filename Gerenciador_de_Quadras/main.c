/*Objetivos:
		*Criar função de adquirir data** FEITO FEITO FEITO FEITO
			*Criar a funcionalidade**
			*Criar ponteiros de struct para utilizar dentro da função**
			*Criar a função modularizada**
			*Trocar nomes e etc e ver se funciona**
		
		*Verificar se leitura de txts não existentes é inválido
		
		*Verificar criação de txts e leitura dos mesmos depois

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LSIZE 200
#define DIR "C:\\Users\\a249664\\Documents\\Projeto SI203B\\Data\\"
#define LBREMOVER(string) string[strlen(string)-1] = '\0';

void DateTreat(char *Date);
void DateGet(char *day, char *month, char *year);
void DateFormat(char *day, char *month, char *year, char *entiredate);


struct QuadraInfo{
	char name[LSIZE];
	char date[10];
	char time[10];
	char status[20];
};
struct Date{
	char day[5];
	char month[5];
	char year[10];	
	char hour[5];
	char minutes[5];
	char FullDate[30];
};


int main(){
	
	FILE *FilePointer;//Ponteiro de Arquivo
	char Directory[LSIZE] = DIR;
	
	struct Date *ActualDate;
	ActualDate = (struct Date*) malloc(sizeof(struct Date));

	DateGet(ActualDate->day, ActualDate->month, ActualDate->year);
	DateFormat(ActualDate->day,ActualDate->month,ActualDate->year,ActualDate->FullDate);
	printf("%s\n", ActualDate->FullDate);
	//Adquirir Data


	
	
	return 0;	
}



void DateGet(char *day, char *month, char *year){
    
    start:    
        printf("Insira o dia:\t");
        fgets(day,10,stdin); LBREMOVER(day)
        if(atoi(day)>31 || atoi(day)<1){
            printf("Dia invalido, insira dados novamente\n");
            goto start;
        }
        printf("Insira o mes:\t");
        fgets(month,10,stdin); LBREMOVER(month)
        if(atoi(month)>12 || atoi(month)<1){
            printf("Mes invalido, insira dados novamente\n");
            goto start;
        }
        printf("Insira o ano:\t");
        fgets(year,10,stdin); LBREMOVER(year)
        if(strlen(year)!=4){
            printf("Ano invalido, insira dados novamente\n");
            goto start;

        }    
        DateTreat(day);DateTreat(month);
}

void DateTreat(char *Date){
    if(strlen(Date)<2){
        Date[1] = Date[0];
        Date[0] = '0';
        Date[2] = '\0';
    }
}

void DateFormat(char *day, char *month, char *year, char *entiredate){
    
	entiredate[0] = day[0];entiredate[1] = day[1];entiredate[2] = '.';
	entiredate[3] = month[0];entiredate[4] = month[1];entiredate[5] = '.';
	entiredate[6] = year[0];entiredate[7] = year[1];entiredate[8] = year[2];entiredate[9] = year[3];entiredate[10] = '\0';
}

