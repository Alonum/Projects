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

void SingleNumberTreat(char *Number);
void DateGet(char *day, char *month, char *year);
void DateFormat(char *day, char *month, char *year, char *entiredate);
void InfoGet(char *hour, char *minutes, char *name, char *document);
void InfoFormat(char *hour, char *minutes, char *name, char *document, char *fullcase);
void LowerCase(char *string);

struct QuadraInfo{
	char name[LSIZE];
	char hour[10];
	char minutes[10];
	char cpf[15];
	char fullcase[LSIZE*2];
};
struct Date{
	char day[5];
	char month[5];
	char year[10];	
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
//	InfoAtual = (struct QuadraInfo*) malloc(sizeof(struct QuadraInfo));

start:
	Directory[0] ='\0';
	strcpy(Directory, DIR); //Reinicia diretorio
	strcpy(TextData, "Emtpy\0"); //Reinicia info de output dos arquivos
	InfoAtual = (struct QuadraInfo*) malloc(sizeof(struct QuadraInfo));
	
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
		printf("Insira as informacoes do Agendamento\n\n");
		InfoGet(InfoAtual->hour, InfoAtual->minutes, InfoAtual->name, InfoAtual->cpf);
        InfoFormat(InfoAtual->hour, InfoAtual->minutes, InfoAtual->name, InfoAtual->cpf,InfoAtual->fullcase);
		fwrite(InfoAtual->fullcase, sizeof(char), strlen(InfoAtual->fullcase), FilePointer);
		fclose(FilePointer);
		free(InfoAtual);
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
            printf("Dia invalido, pressione enter para inserir os dados novamente\n");
            while(getchar() != '\n'){getchar();}
            goto start;
        }
        printf("Insira o mes:\t");
        fgets(month,10,stdin); LBREMOVER(month)
        if(atoi(month)>12 || atoi(month)<1){
            printf("Mes invalido, pressione enter para inserir os dados novamente\n");
            while(getchar() != '\n'){getchar();}
            goto start;
        }
        printf("Insira o ano:\t");
        fgets(year,10,stdin); LBREMOVER(year)
        if(strlen(year)!=4){
            printf("Ano invalido, pressione enter para inserir os dados novamente\n");
            while(getchar() != '\n'){getchar();}
            goto start;

        }    
        SingleNumberTreat(day);SingleNumberTreat(month);
}

void SingleNumberTreat(char *Number){
    if(strlen(Number)<2){
        Number[1] = Number[0];
        Number[0] = '0';
        Number[2] = '\0';
    }
}

void DateFormat(char *day, char *month, char *year, char *entiredate){
    
	entiredate[0] = day[0];entiredate[1] = day[1];entiredate[2] = '.';
	entiredate[3] = month[0];entiredate[4] = month[1];entiredate[5] = '.';
	entiredate[6] = year[0];entiredate[7] = year[1];entiredate[8] = year[2];entiredate[9] = year[3];
	entiredate[10] = '.'; entiredate[11] = 't'; entiredate[12] = 'x'; entiredate[13] = 't'; entiredate[14] = '\0';
}

void InfoGet(char *hour, char *minutes, char *name, char *document){
    
    start:    
        printf("Insira a hora:\t");
        fgets(hour,10,stdin); LBREMOVER(hour)   
        if(atoi(hour)>23 || atoi(hour)<0){
            printf("Hora invalida, pressione enter para inserir os dados novamente\n");
            while(getchar() != '\n'){getchar();}
            goto start;
        }
        printf("Insira os minutos:\t");
        fgets(minutes,10,stdin); LBREMOVER(minutes)
        if(atoi(minutes)>59 || atoi(minutes)<1){
            printf("Minuto invalido, pressione enter para inserir os dados novamente\n");
            while(getchar() != '\n'){getchar();}
            goto start;
        }
        printf("Insira o CPF do locatario:\t");
        fgets(document,15,stdin); LBREMOVER(document)
        if(strlen(document)<11 || strlen(document)>11){
            printf("CPF invalido, pressione enter para inserir os dados novamente\n");
            while(getchar() != '\n'){getchar();}
            goto start;
        }
        printf("Insira o nome do locatario:\t");
        fgets(name,LSIZE,stdin); LBREMOVER(name)
            
        SingleNumberTreat(hour);SingleNumberTreat(minutes);
}

void InfoFormat(char *hour, char *minutes, char *name, char *document, char *fullcase){
    fullcase[0] ='>';
    strcpy(fullcase, hour);fullcase[2] = ':';fullcase[3] = '\0';
    strcat(fullcase, minutes);fullcase[strlen(fullcase)] = ';';fullcase[6] = '\0';
    strcat(fullcase, name);fullcase[strlen(fullcase)] = ';';fullcase[7+strlen(name)] = '\0';
    strcat(fullcase, document);fullcase[strlen(fullcase)] = '>';fullcase[8+strlen(name)+strlen(document)] = '\n';
    fullcase[9+strlen(name)+strlen(document)] = '\0';
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
