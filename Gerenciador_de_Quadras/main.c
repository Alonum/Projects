/*Objetivos:

		Arrumar bug de leitura quando colocar palavra nos horarios
  		Adicionar Formulario de Contrato por Locatario

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LSIZE 200
#define DIR "..\\Gerenciador_de_Quadras\\Data\\"
#define DAYDIR "..\\Gerenciador_de_Quadras\\Data\\days.txt"

#define LBREMOVER(string) string[strlen(string)-1] = '\0';
#define FAILVERIFY(pointer) if(pointer == NULL){printf("ERROR!!");exit(1);}

#define WINDOWS system("cls");
#define LINUX system("clear");

#define CLEARSCREEN WINDOWS

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
	int Index, IndexTime, IndexCompare, IndexPosition, IndexNegative;
	//wip
	

	char Directory[LSIZE];// = DIR;

	FILE *FilePointer;//Ponteiro de Arquivo
	char *InfoCompare;// = malloc(10*sizeof(char));
	char *UserCommand;// = malloc(LSIZE*sizeof(char));
	char *TextData;// = malloc(LSIZE*sizeof(char));

	char *QuadraCompare;// = malloc(LSIZE*sizeof(char));
	char *TimeCompare;// = malloc(LSIZE*sizeof(char));

	struct Date *ActualDate;
	struct QuadraInfo *InfoAtual;
//	ActualDate = (struct Date*) malloc(sizeof(struct Date));
//	InfoAtual = (struct QuadraInfo*) malloc(sizeof(struct QuadraInfo));

start:
	
	InfoCompare = malloc(10*sizeof(char));
	UserCommand = malloc(LSIZE*sizeof(char));
	TextData = malloc(LSIZE*sizeof(char));
	QuadraCompare = malloc(LSIZE*sizeof(char));
	TimeCompare = malloc(LSIZE*sizeof(char));
	ActualDate = (struct Date*) malloc(sizeof(struct Date));
	InfoAtual = (struct QuadraInfo*) malloc(sizeof(struct QuadraInfo));

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


		/*Adicionar dia do agendamento em days .txt*/
		//Verifica primeiro se ha algum agendamento

		FilePointer = fopen(DAYDIR, "r");
		IndexPosition = 0;
		fseek(FilePointer,0, SEEK_SET);
		while(fgetc(FilePointer)!= EOF){
			for(Index=0;fgetc(FilePointer)!= '>';Index++){
				fseek(FilePointer,IndexPosition*sizeof(char), SEEK_SET);
				TextData[Index] = fgetc(FilePointer);
				IndexPosition++;
			}
			IndexPosition += 3;
			TextData[Index] = '\0';
			if(!strcmp(ActualDate->FullDate, TextData)){
				goto next;
			}
		
		fgetc(FilePointer);
		}
		//marca no arquivo, caso nao ache oposicao
		fclose(FilePointer);
		strcpy(TextData, ActualDate->FullDate);
		TextData[Index]= '>';
		TextData[Index+1]= '\n';
		TextData[Index+2]= '\0';
		FilePointer= fopen(DAYDIR, "a");
		fwrite(TextData, sizeof(char), strlen(TextData), FilePointer);
		fclose(FilePointer);
next:
		fclose(FilePointer);

		/**/    



		/*Verificar informacoes do agendamento*/
		printf("Insira as informacoes do Agendamento\n\n");
		InfoGet(InfoAtual->hour, InfoAtual->minutes, InfoAtual->name, InfoAtual->cpf, InfoAtual->type);
        InfoFormat(InfoAtual->hour, InfoAtual->minutes, InfoAtual->name, InfoAtual->cpf, InfoAtual->type,InfoAtual->fullcase);
		


		strcpy(Directory, DIR);
		strcat(Directory, ActualDate->FullDate);
   
		 /*Verificar o arquivo              WIP TOTAL */
        FilePointer = fopen(Directory, "r");
        IndexPosition = 0;
		fseek(FilePointer,0, SEEK_SET);
        while(fgetc(FilePointer)!= EOF){
			IndexNegative = 0;//contradiz a soma de hora superior para verificar horarios anteriores ao atual
																	//printf("\nComecando em %d\n", IndexPosition);//debug
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
        												  //  printf("\nHora Atual:%s\n", InfoCompare);//debug
            //Procura Minutos
           	for(Index=0;fgetc(FilePointer) != ';'; Index++){
				fseek(FilePointer,IndexPosition*sizeof(char), SEEK_SET);
				InfoCompare[Index] = fgetc(FilePointer);
				IndexPosition++;
			}
			//Apos este for, o proximo caractere vem depois de ;, ou seja, a quadra que esta logo em seguida
			InfoCompare[2] = '\0';
			
			

			//Compara as horas entre si, e caso o horario inserido seja menor que o marcado, e tenha minutos, insere uma hora a mais.
			IndexTime=atoi(InfoAtual->hour);
			if(atoi(InfoAtual->minutes)>0 && atoi(InfoAtual->hour)<IndexCompare){
				IndexTime++;
			}
			//Compara minutos, se houver qualquer minuto adicional, conta a hora. Incrementa IndexNegative para contrariar a condicao no caso de horarios anteriores.
			if(atoi(InfoCompare)>1){
				IndexCompare++;
				IndexNegative++;
			}

			
														//printf("O caractere atual eh:\t%c\n", fgetc(FilePointer));//debug
			//if de caso a hora seja menos q duas entre cada
			IndexPosition++;//Sai de ;
			if((IndexCompare-IndexNegative)-IndexTime<=1 && IndexCompare-IndexTime >=-1){
				for(Index=0;fgetc(FilePointer)!= ';';Index++){
					fseek(FilePointer,IndexPosition*sizeof(char), SEEK_SET);
					TextData[Index] = fgetc(FilePointer);
					IndexPosition++;
				}
				TextData[Index]='\0';
				if(!strcmp(TextData, InfoAtual->type)){
					printf("\n\nQuadra Reservada no momento\n\n");
						fclose(FilePointer);
						free(QuadraCompare); 
						free(TimeCompare); 
						free(InfoAtual);
						free(ActualDate);
						free(TextData);
						free(InfoCompare);
						free(UserCommand);
					printf("\nPressione enter para continuar\n");
					while(getchar() != '\n'){getchar();}
					CLEARSCREEN
					goto start;
				}
			}
												//	printf("Hora ja marcada, pois %d menos %d, resulta em %d\n A quadra atual eh: %s\n", IndexCompare, IndexTime, IndexCompare-IndexTime,TextData);
												//printf("Hora nao marcada, pois %d menos %d, resulta em %d", IndexCompare, Index, IndexCompare-Index);
			//Procura a proxima linha
			for(;fgetc(FilePointer)!= '\n';){
				IndexPosition++;
																										//printf("\nAchamos a quebra de linha\n");
				fseek(FilePointer,IndexPosition*sizeof(char), SEEK_SET);
			}
			IndexPosition++;

	
        }
        printf("\n\nQuadra Disponivel!\n\n");
		strcpy(TextData, "Emtpy\0"); //Reinicia info de output dos arquivos
        fclose(FilePointer);



        /*Escrever em arquivo*/
        FilePointer = fopen(Directory, "a");
		fwrite(InfoAtual->fullcase, sizeof(char), strlen(InfoAtual->fullcase), FilePointer);
		fclose(FilePointer);
				free(QuadraCompare); 
				free(TimeCompare); 
				free(InfoAtual);
				free(ActualDate);
				free(TextData);
				free(InfoCompare);
				free(UserCommand);
		printf("\nPressione enter para continuar\n");
		while(getchar() != '\n'){getchar();}
		CLEARSCREEN
		goto start;
	}
/* Prot?ipo de Leitura */
	else if(!(strcmp(UserCommand, "consultar"))){

		printf("\nEscolha um dia de agendamento:\n\n");
		//lista os dias disponiveis para consulta
		FilePointer = fopen(DAYDIR, "r");
		IndexPosition = 0;
		fseek(FilePointer,0, SEEK_SET);
		while(fgetc(FilePointer)!= EOF){
			for(Index=0;fgetc(FilePointer)!= '\n';Index++){
					fseek(FilePointer,IndexPosition*sizeof(char), SEEK_SET);
					TextData[Index] = fgetc(FilePointer);
					IndexPosition++;
				//printf("\ntiming: %d %s\n",IndexTime,  TextData);
			}
			TextData[10]= '\0';
			TextData[2]= '/';
			TextData[5]= '/';
			if(strcmp(TextData, "00/00/0000"))
			printf("%s\n", TextData);
			IndexPosition +=2;
		//	if(!strcmp(ActualDate->FullDate, TextData)){
		//		goto next;
		//	}
		fgetc(FilePointer);
		}
		fclose(FilePointer);
		strcpy(TextData, "Emtpy\0"); //Reinicia info de output dos arquivos
		//adquire o dia desejado
		printf("\n");
		DateGet(ActualDate->day, ActualDate->month, ActualDate->year);
		DateFormat(ActualDate->day,ActualDate->month,ActualDate->year,ActualDate->FullDate);
		strcat(Directory, ActualDate->FullDate);
		FilePointer = fopen(Directory, "r");
		if(FilePointer == NULL){
			printf("\n!!Data Invalida!!\n");
			goto start;
		}
		//WIP
		printf("\nEscolha o horario e quadra que deseja consultar\n\n");
		IndexPosition = 0;
		fseek(FilePointer,0, SEEK_SET);
		while(fgetc(FilePointer) != EOF){
			for(Index=0;fgetc(FilePointer) != ';'; Index++){
				fseek(FilePointer,IndexPosition*sizeof(char), SEEK_SET);
				InfoCompare[Index] = fgetc(FilePointer);
				IndexPosition++;
			}
			IndexPosition++;
			InfoCompare[Index] = '\0';
			printf("Horario: %s\t\t--\t\t", InfoCompare);
			for(Index=0;fgetc(FilePointer) != ';'; Index++){
				fseek(FilePointer,IndexPosition*sizeof(char), SEEK_SET);
				InfoCompare[Index] = fgetc(FilePointer);
				IndexPosition++;
			}
			InfoCompare[Index] = '\0';
			printf("Quadra de %s\n", InfoCompare);

			for(;fgetc(FilePointer)!='\n';){
				fseek(FilePointer,IndexPosition*sizeof(char), SEEK_SET);
				IndexPosition++;
			}

			IndexPosition++;
			fgetc(FilePointer);
		}

		//Escolhe a hora que deseja utilizar
	choose:
		printf("\nInsira a hora:\t");
        fgets(TextData,10,stdin); LBREMOVER(TextData)   
        if(atoi(TextData)>22 || atoi(TextData)<0){
            printf("Hora invalida, pressione enter para inserir os dados novamente\n");
            while(getchar() != '\n'){getchar();}
            goto choose;
        }
        printf("Insira os minutos:\t");
        fgets(InfoCompare,10,stdin); LBREMOVER(InfoCompare)
        if(atoi(InfoCompare)>59 || atoi(InfoCompare)<0 ||(atoi(TextData)==22 && atoi(InfoCompare)>0)){
            printf("Minuto invalido, pressione enter para inserir os dados novamente\n");
            while(getchar() != '\n'){getchar();}
            goto choose;
        }
		//trata a hora para ficar igual a string
		SingleNumberTreat(TextData);
		SingleNumberTreat(InfoCompare);
		TextData[2] = ':';
		TextData[3] = '\0';
		strcat(TextData, InfoCompare);
		//escolhe a quadra que deseja utilizar

	choosequadra:
		printf("Insira a quadra:\t");
		fgets(InfoCompare,20,stdin); LBREMOVER(InfoCompare)
		LowerCase(InfoCompare);
		if(!(!strcmp(InfoCompare,"volei") || !strcmp(InfoCompare ,"futebol") || !strcmp(InfoCompare, "basquete"))){
			printf("Quadra invalida, pressione enter para inserir os dados novamente\n");
			while(getchar() != '\n'){getchar();}
			goto choosequadra;
		}
		
		//compara o horario e quadra escolhida com os horarios e quadras de dentro
		strcpy(QuadraCompare, InfoCompare);
		strcpy(TimeCompare, TextData);
		fseek(FilePointer,0, SEEK_SET);
		IndexPosition = 0;
		

		while(fgetc(FilePointer) != EOF){
			for(Index=0;fgetc(FilePointer) != ';'; Index++){
				fseek(FilePointer,IndexPosition*sizeof(char), SEEK_SET);
				InfoCompare[Index] = fgetc(FilePointer);
				IndexPosition++;
			}
			IndexPosition++;
			InfoCompare[Index] = '\0';
			if(!strcmp(InfoCompare, TimeCompare)){
				for(Index=0;fgetc(FilePointer) != ';'; Index++){
					fseek(FilePointer,IndexPosition*sizeof(char), SEEK_SET);
					InfoCompare[Index] = fgetc(FilePointer);
					IndexPosition++;
				}
				InfoCompare[Index] = '\0';
				if(!strcmp(InfoCompare, QuadraCompare)){
					printf("\n\n\nInfo da data:\n\nHorario: %s\t\t\tQuadra: %s\n",TimeCompare, QuadraCompare);
					IndexPosition++;
					for(Index=0;fgetc(FilePointer) != ';'; Index++){
						fseek(FilePointer,IndexPosition*sizeof(char), SEEK_SET);
						InfoCompare[Index] = fgetc(FilePointer);
						IndexPosition++;
					}
					IndexPosition++;
					InfoCompare[Index] = '\0';
					printf("Locatario: %s\t\t", InfoCompare);

					for(Index=0;fgetc(FilePointer) != '>'; Index++){
						fseek(FilePointer,IndexPosition*sizeof(char), SEEK_SET);
						InfoCompare[Index] = fgetc(FilePointer);
						IndexPosition++;
					}
					InfoCompare[Index] = '\0';
					printf("CPF: %s\nValor: R$200.00\n\n", InfoCompare);

					printf("\nPressione enter para continuar\n");
					while(getchar() != '\n'){getchar();}
					CLEARSCREEN
				free(QuadraCompare); 
				free(TimeCompare); 
				free(InfoAtual);
				free(ActualDate);
				free(TextData);
				free(InfoCompare);
				free(UserCommand);
					fclose(FilePointer);
					goto start;
				}
			}

			for(;fgetc(FilePointer)!='\n';){
				fseek(FilePointer,IndexPosition*sizeof(char), SEEK_SET);
				IndexPosition++;
			}

			IndexPosition++;
			fgetc(FilePointer);
		}
		printf("\n\nNenhum agendamento com estes dados encontrados");
		printf("\n\nPressione enter para continuar\n");
		while(getchar() != '\n'){getchar();}
		CLEARSCREEN
		free(QuadraCompare); 
		free(TimeCompare); 
		free(InfoAtual);
		free(ActualDate);
		free(TextData);
		free(InfoCompare);
		free(UserCommand);
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
