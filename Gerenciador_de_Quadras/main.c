/*Objetivos:
		*Criar fun??o de adquirir data** FEITO FEITO FEITO FEITO
			*Criar a funcionalidade**
			*Criar ponteiros de struct para utilizar dentro da fun??o**
			*Criar a fun??o modularizada**
			*Trocar nomes e etc e ver se funciona**
		
		*Verificar se leitura de txts n?o existentes ? inv?lido
		
		*Verificar cria??o de txts e leitura dos mesmos depois


FEITO				*Adicionar Quadra Volei, Quadra Basquete, Quadra Futebol
A FAZER				*Adicionar Preco 200 Reais Fixo
QUASE FEITO			*Finalizar Protótipo de Verificacao	
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
void InfoGet(char *hour, char *minutes, char *name, char *document, char *type);
void InfoFormat(char *hour, char *minutes, char *name, char *document, char *type, char *fullcase);
void LowerCase(char *string);

struct QuadraInfo{
	char name[LSIZE];
	char type[20];
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
	
	//wip
	int Index, IndexCompare, IndexPosition, IndexNegative;
	//wip
	
	FILE *FilePointer;//Ponteiro de Arquivo
	char Directory[LSIZE];// = DIR;
	char *InfoCompare = malloc(10*sizeof(char));
	char *UserCommand = malloc(LSIZE*sizeof(char));
	char *TextData = malloc(LSIZE*sizeof(char));
	struct Date *ActualDate;
	struct QuadraInfo *InfoAtual;
	ActualDate = (struct Date*) malloc(sizeof(struct Date));
	InfoAtual = (struct QuadraInfo*) malloc(sizeof(struct QuadraInfo));

start:
	Directory[0] ='\0';
	strcpy(Directory, DIR); //Reinicia diretorio
	strcpy(TextData, "Emtpy\0"); //Reinicia info de output dos arquivos
	
	
	printf("\n\nOperacoes de Agendamento:\n\n\tMarcar\t\t\tConsultar\t\tDeletar\n\n\t\t   ");
	fgets(UserCommand, LSIZE, stdin); LBREMOVER(UserCommand)
	LowerCase(UserCommand);

/* Prot?ipo de Escrita */	
	if(!(strcmp(UserCommand, "marcar"))){
		printf("\nData do agendamento:\n\n");
		
		/*Adquirir nome do arquivo do dia desejado*/
		DateGet(ActualDate->day, ActualDate->month, ActualDate->year);
		DateFormat(ActualDate->day,ActualDate->month,ActualDate->year,ActualDate->FullDate);
		strcat(Directory, ActualDate->FullDate);
		/*Verificar informacoes do agendamento*/
		printf("Insira as informacoes do Agendamento\n\n");
		InfoGet(InfoAtual->hour, InfoAtual->minutes, InfoAtual->name, InfoAtual->cpf, InfoAtual->type);
        InfoFormat(InfoAtual->hour, InfoAtual->minutes, InfoAtual->name, InfoAtual->cpf, InfoAtual->type,InfoAtual->fullcase);
        /*Verificar o arquivo              WIP TOTAL */
        FilePointer = fopen(Directory, "r");
        IndexPosition = 0;
        IndexNegative = 0;
        while(fgetc(FilePointer)!= EOF){
			printf("\nComecando em %d\n", IndexPosition);
			//Procura Hora
			for(Index=0;fgetc(FilePointer) != ':'; Index++){
				fseek(FilePointer,IndexPosition*sizeof(char), SEEK_SET);
				InfoCompare[Index] = fgetc(FilePointer);
				IndexPosition++;
			}
			//Move uma posicao depois de : na string
            IndexPosition++;
            
            InfoCompare[2] = '\0';
            //Adiciona hora a IndexCompare
            IndexCompare = atoi(InfoCompare);
            printf("\nHora Atual:%s\n", InfoCompare);
            //Procura Minutos
           	for(Index=0;fgetc(FilePointer) != ';'; Index++){
				fseek(FilePointer,IndexPosition*sizeof(char), SEEK_SET);
				InfoCompare[Index] = fgetc(FilePointer);
				IndexPosition++;
			}
			
			InfoCompare[2] = '\0';
			
			for(;fgetc(FilePointer)!= '>';){
				IndexPosition++;
				//printf("\nAchamos a quebra de linha\n");
				fseek(FilePointer,IndexPosition*sizeof(char), SEEK_SET);
			}
			IndexPosition+=3;
			
			//Compara minutos, se houver qualquer minuto adicional, conta a hora.
			if(atoi(InfoCompare)>1){
				IndexCompare++;
				IndexNegative++;
			}
			if((IndexCompare-IndexNegative)-atoi(InfoAtual->hour)<=1 && IndexCompare-atoi(InfoAtual->hour) >=-1){
        		printf("Hora ja marcada, pois %d menos %d, resulta em %d", IndexCompare, atoi(InfoAtual->hour), IndexCompare-atoi(InfoAtual->hour));
        		
			}
			else
       			printf("Hora nao marcada, pois %d menos %d, resulta em %d", IndexCompare, atoi(InfoAtual->hour), IndexCompare-atoi(InfoAtual->hour));
		
        }
        printf("Fim do programa");
        fclose(FilePointer);
        return 0;
        /*Escrever em arquivo*/
        FilePointer = fopen(Directory, "a");
		fwrite(InfoAtual->fullcase, sizeof(char), strlen(InfoAtual->fullcase), FilePointer);
		fclose(FilePointer);
		free(InfoAtual);
		free(ActualDate);
		goto start;
	}
/* Prot?ipo de Leitura */
	else if(!(strcmp(UserCommand, "consultar"))){
		printf("\nInsira a data do Agendamento\n\n");
		DateGet(ActualDate->day, ActualDate->month, ActualDate->year);
		DateFormat(ActualDate->day,ActualDate->month,ActualDate->year,ActualDate->FullDate);
		strcat(Directory, ActualDate->FullDate);
		FilePointer = fopen(Directory, "r");
		
		//WIP
		fgets(TextData, 3, FilePointer);
		printf("Hora:%s", TextData);
		for(Index = 0;fgetc(FilePointer) != ';';Index++){
			fseek(FilePointer, sizeof(char), SEEK_CUR);
		//	fgetc(FilePointer);
			TextData[Index] = fgetc(FilePointer);
			printf("\nEstado %d: %s\n", Index, TextData);
		}
		//fgets(TextData, 10, FilePointer);
		printf("Nome: %s", TextData);
		
		printf("\nYour info:\n\n%s\n\n", TextData);
		fclose(FilePointer);
		goto start;
		//WIP
		
	}else{
		printf("\n\n\t\t!!Entrada Invalida!!\n\n");
		goto start;
	}

	goto start;
/*
/*Prot?ipo de Aquisi?o de Data
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

void InfoGet(char *hour, char *minutes, char *name, char *document, char *type){
    
    start:
	
		printf("Insira a quadra:\t");
		fgets(type,20,stdin); LBREMOVER(type)
		LowerCase(type);
		if(!(!strcmp(type,"volei") || !strcmp(type ,"futebol") || !strcmp(type, "basquete"))){
			printf("Quadra invalida, pressione enter para inserir os dados novamente\n");
			while(getchar() != '\n'){getchar();}
			goto start;
		}
        printf("Insira a hora:\t");
        fgets(hour,10,stdin); LBREMOVER(hour)   
        if(atoi(hour)>22 || atoi(hour)<0){
            printf("Hora invalida, pressione enter para inserir os dados novamente\n");
            while(getchar() != '\n'){getchar();}
            goto start;
        }
        printf("Insira os minutos:\t");
        fgets(minutes,10,stdin); LBREMOVER(minutes)
        if(atoi(minutes)>59 || atoi(minutes)<0 ||(atoi(hour)==22 && atoi(minutes)>0)){
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

void InfoFormat(char *hour, char *minutes, char *name, char *document, char *type, char *fullcase){
    fullcase[0] ='>';
    strcpy(fullcase, hour);fullcase[2] = ':';fullcase[3] = '\0';
    strcat(fullcase, minutes);fullcase[strlen(fullcase)] = ';';fullcase[6] = '\0';
    strcat(fullcase, type);fullcase[strlen(fullcase)] = ';';fullcase[7+strlen(type)] = '\0';
    strcat(fullcase, name);fullcase[strlen(fullcase)] = ';';fullcase[8+strlen(type)+strlen(name)] = '\0';
    strcat(fullcase, document);fullcase[strlen(fullcase)] = '>';fullcase[9+strlen(type)+strlen(document)+strlen(name)] = '\n';
	fullcase[10+strlen(name)+strlen(document)+strlen(type)] = '\0';
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
