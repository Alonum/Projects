/*Objetivos:
		*Criar função de adquirir data
			*Criar a funcionalidade
			*Criar ponteiros de struct para utilizar dentro da função
			*Criar a função modularizada
			*Trocar nomes e etc e ver se funciona
		
		*Verificar se leitura de txts não existentes é inválido
		
		*Verificar criação de txts e leitura dos mesmos depois

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LSIZE 200
#define DIR "C:\\Users\\a249664\\Documents\\Projeto SI203B\\Data\\"
#define LBREMOVER(string) string[strlen(string)-1] = '\0';

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
	
	struct Date ActualDate;
	//Adquirir Data
	printf("Insira a data:\nDia:\t");
	fgets(ActualDate.day,5,stdin);			LBREMOVER(ActualDate.day)
	if(strlen(ActualDate.day)<2){
		ActualDate.day[1] = ActualDate.day[0];
		ActualDate.day[0] = '0';
		ActualDate.day[2] = '\0';
	}
	
	printf("Mes:\t");
	fgets(ActualDate.month,5,stdin);		LBREMOVER(ActualDate.month)
	if(strlen(ActualDate.month)<2){
		ActualDate.month[1] = ActualDate.month[0];
		ActualDate.month[0] = '0';
		ActualDate.month[2] = '\0';
	}
	
	printf("Ano:\t");
	fgets(ActualDate.year,10,stdin);			LBREMOVER(ActualDate.year)
	
	ActualDate.FullDate[0] = ActualDate.day[0];ActualDate.FullDate[1] = ActualDate.day[1];ActualDate.FullDate[2] = '.';
	ActualDate.FullDate[3] = ActualDate.month[0];ActualDate.FullDate[4] = ActualDate.month[1];ActualDate.FullDate[5] = '.';
	ActualDate.FullDate[6] = ActualDate.year[0];ActualDate.FullDate[7] = ActualDate.year[1];ActualDate.FullDate[8] = ActualDate.year[2];ActualDate.FullDate[9] = ActualDate.year[3];ActualDate.FullDate[10] = '\0';
	printf("%s\n", ActualDate.FullDate);
	//Adquirir Data


	
	
	return 0;	
}
