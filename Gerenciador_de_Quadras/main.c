/*Objetivos:
		*Criar funÃ§Ã£o de adquirir data** FEITO FEITO FEITO FEITO
			*Criar a funcionalidade**
			*Criar ponteiros de struct para utilizar dentro da funÃ§Ã£o**
			*Criar a funÃ§Ã£o modularizada**
			*Trocar nomes e etc e ver se funciona**
		
		*Verificar se leitura de txts nÃ£o existentes Ã© invÃ¡lido
		
		*Verificar criaÃ§Ã£o de txts e leitura dos mesmos depois

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LSIZE 200
#define DIR "..\\Gerenciador_de_Quadras\\Data\\"

#define LBREMOVER(string) string[strlen(string)-1] = '\0';
#define FAILVERIFY(pointer) if(pointer == NULL){printf("ERROR!!");exit(1);}

void DateTreat(char *Date);
void DateGet(char *day, char *month, char *year);
void DateFormat(char *day, char *month, char *year, char *entiredate);
void LowerCase(char *string);

struct QuadraInfo{
	char name[LSIZE];
	char date[10];
	char time[10];
	char cpf[10];
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
	char Directory[LSIZE];// = DIR;
	char *UserCommand = malloc(LSIZE*sizeof(char));
	char *TextData = malloc(LSIZE*sizeof(char));
	struct Date *ActualDate;
	struct QuadraInfo *InfoAtual;
	ActualDate = (struct Date*) malloc(sizeof(struct Date));

start:
	Directory[0] ='\0';
	strcpy(Directory, DIR); //Reinicia diretorio
	strcpy(TextData, "Emtpy\0"); //Reinicia info de output dos arquivos
	
	printf("\n\nOperacoes de Agendamento:\n\n\tMarcar\t\t\tConsultar\t\tDeletar\n\n\t\t   ");
	fgets(UserCommand, LSIZE, stdin); LBREMOVER(UserCommand)
	LowerCase(UserCommand);

/* Protótipo de Escrita */	
	if(!(strcmp(UserCommand, "marcar"))){
		printf("\nData do agendamento:\n\n");
		DateGet(ActualDate->day, ActualDate->month, ActualDate->year);
		DateFormat(ActualDate->day,ActualDate->month,ActualDate->year,ActualDate->FullDate);
		strcat(Directory, ActualDate->FullDate);
		//printf("%s", Directory);
		FilePointer = fopen(Directory, "a");
		printf("Write your data\n\n");
		fgets(UserCommand, LSIZE, stdin);
		fwrite(UserCommand, sizeof(char), strlen(UserCommand), FilePointer);
		fclose(FilePointer);
		goto start;
	}
/* Protótipo de Leitura */
	else if(!(strcmp(UserCommand, "consultar"))){
		printf("\nPlease insert date\n\n");
		DateGet(ActualDate->day, ActualDate->month, ActualDate->year);
		DateFormat(ActualDate->day,ActualDate->month,ActualDate->year,ActualDate->FullDate);
		strcat(Directory, ActualDate->FullDate);
		FilePointer = fopen(Directory, "r");
		fgets(TextData, LSIZE, FilePointer);
		printf("\nYour info:\n\n%s\n\n", TextData);
		fclose(FilePointer);
		goto start;
	}else{
		printf("\n\n\t\t!!Entrada Invalida!!\n\n");
		goto start;
	}

/*
/*Protótipo de Aquisição de Data
	DateGet(ActualDate->day, ActualDate->month, ActualDate->year);
	DateFormat(ActualDate->day,ActualDate->month,ActualDate->year,ActualDate->FullDate);
	printf("%s\n", ActualDate->FullDate);
	//Adquirir Data
*/
	
	
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
	entiredate[6] = year[0];entiredate[7] = year[1];entiredate[8] = year[2];entiredate[9] = year[3];
	entiredate[10] = '.'; entiredate[11] = 't'; entiredate[12] = 'x'; entiredate[13] = 't'; entiredate[14] = '\0';
}

void LowerCase(char *string){

	int index;
	
	for(index = 0; index<strlen(string); index++)
	{
		if(string[index]<97)
		{
			string[index] +=32;
		}
	}	
}
