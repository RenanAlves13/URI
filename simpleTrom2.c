#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Operações de entrada/saída
#define READ 10
#define WRITE 11
//Operações de carregamento/armazenamento
#define LOAD 20
#define STORE 21
//Operações aritméticas
#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33
//Operações de transferência de controle
#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43

#define MAX 100

int memory[MAX];

struct
{
	int tm_mday;
	int tm_mon;
	int tm_hour;
	int tm_year;
	int tm_min;
	int tm_sec;
	
}tm;

typedef struct 
{
	int dia;
	int mes;
	int ano;
	int hora;
	int min;
	int sec;
	char descricao[MAX];
}dados;

typedef struct 
{
	int dia;
	int mes;
	int ano;
	int hora;
	int min;
	int sec;
}atualiza;

void menu()
{
	printf("*** Digite uma op��o ***\n");
	printf("1 - Carregar/executar um c�digo SML.\n");
	printf("2 - Criar um novo c�digo.\n");
	printf("3 - Pesquisar c�digos existentes.\n");
	printf("4 - Para sair.\n");
	printf("Digite sua op��o: ");
}

void inicializa(int codigo[],int max)
{
    int i;
	for(i = 0; i < MAX; i++)
	{
		codigo[i] = 0;
	}
}

void dataHora()
{
	
	struct tm *data;
	dados acesso;
	
	time_t segundos;
	time(&segundos);
	
	data = localtime(&segundos);

	printf("Descri��o do c�digo[ m�ximo %d letras]: ", MAX);
	fflush(stdin);
	/*Salvando em um tipo de estrutura diferente para salvar no arquivo bin�rio, pois com o outro struct n�o foi 
	poss�vel.*/
	gets(acesso.descricao);
	acesso.dia = data->tm_mday;;
	acesso.mes = data->tm_mon+1;
	acesso.ano = data->tm_year+1900;
	acesso.hora = data->tm_hour;
	acesso.min = data->tm_min;
	acesso.sec = data->tm_sec;
	
	FILE *arqBin;
	
	
	arqBin = fopen("PROG.bin", "ab");
	
	if( arqBin == NULL){
		printf("N�o foi possivel abrir o arquivo bin�rio.\n");
	}
	
	fwrite(&acesso, sizeof(dados), 1, arqBin);
	
	fclose(arqBin);	
}

void pesquisar()
{
	FILE *arqBin;
	dados acesso;
	int i = 1;
	
	arqBin = fopen("PROG.bin", "rb");
	if(!arqBin){
		printf("N�o foi possivel abrir o arquivo bin�rio.\n");
	}
	printf("\n");
	while(fread(&acesso, sizeof(dados), 1, arqBin)){
		printf("Arquivo n�mero %d:\nData: %d/%d/%d\nHora: %d:%d:%d\nDescri��o: %s.\n", i++, acesso.dia, acesso.mes, acesso.ano, acesso.hora, acesso.min, acesso.sec, acesso.descricao);
		printf("\n");
	}
	
	fclose(arqBin);
}

int instrucao(int codigo[],int max)
{
	int instrucao, operationCode;
	int i = 0;
	
	printf("Digite as instru��es( entre 0 e 9999, e -9999 para encerrar):\n");
	while(instrucao != -9999){
		do{
			printf("%d  ? ", i);
			scanf("%5d", &instrucao);
		}while((instrucao > 9999) || (instrucao <= 0 && instrucao != -9999));
		
		operationCode = instrucao / 100;
		
		if(instrucao == -9999)
		{
			continue;
		}
		else if((operationCode != READ)&&(operationCode != WRITE)&&(operationCode != LOAD)&&
		(operationCode != STORE)&&(operationCode != ADD)&&(operationCode != SUBTRACT)&&
		 (operationCode != DIVIDE)&&(operationCode != MULTIPLY)&&(operationCode != BRANCH)&&
		 (operationCode != BRANCHNEG)&&(operationCode != BRANCHZERO)&&(operationCode != HALT)){
			 printf("Opera��o inv�lida!\nDigite outra opera��o:\n");
			 	
		}else{
			codigo[i] = instrucao;
			++i;
		}
	}
	return i;
}

void dump(int accumulator, int instructionCounter, int instructionRegister, int operationCode, int operand)
{
	int i, j = 0, in = 0;
	int linha[] = {0,1,2,3,4,5,6,7,8,9};
	int coluna[] = {0,10,20,30,40,50,60,70,80,90};
	
	printf("\naccumulator: %27d\n", accumulator);
	printf("instructionCounter: %20d\n", instructionCounter);
	printf("instructionRegister: %19d\n", instructionRegister);
	printf("operationCode: %25d\n", operand);
	printf("operand: %31d\n", operand);
	printf("MEMORY:\n\n");
	
	for(i = 0; i < 10; i++)
	{
		if(i == 0){
			printf("%10d", linha[i]);
		}else{
			printf("%8d", linha[i]);
		}
	}
	printf("\n");
	for(i = 0; i < 10; i++)
	{
		printf("%d", coluna[i]);
		in = in + 10;
		for(;j < in; j++){
			if(j == 0){
				printf("%9d", memory[j]);//8
			}else if(j < 10){
				printf("%8d", memory[j]);
			} else{
				printf("%8d", memory[j]);
			}
		}
		printf("\n");
	}
}

int SimpleTrom()
{
	
	int accumulator = 0;
	int instructionCounter = 0;
	int instructionRegister;
	int operationCode = 0;
	int operand;
	
	while(/*1*/operationCode != 43)
	{
		instructionRegister = memory[instructionCounter];
		operationCode = instructionRegister / 100;
		operand = instructionRegister % 100;
		instructionCounter++;
		
		//if(operationCode == 43) break;
		
		switch(operationCode)
		{
		case READ:
			printf("\nLer: ");
			
			do{
				scanf("%d", &memory[operand]);
			}while((memory[operand] > 9999) || (memory[operand] < -9999));
			break;
		case WRITE:
			printf("\nEscrevendo da mem�ria para o terminal: %d.\n", memory[operand]);
			break;
		case LOAD:
			accumulator = memory[operand];
			break;
		case STORE:
			memory[operand] = accumulator;
			break;
		case ADD:
			accumulator += memory[operand];
			break;
		case SUBTRACT:
			accumulator -= memory[operand];
			break;
		case DIVIDE:
			if(memory[operand] == 0){
				printf("Divis�o por zero n�o podem ser realizadas!\n");
			}
			else{
				accumulator /= memory[operand];
			}
			break;
		case MULTIPLY:
			accumulator *= memory[operand];
			break;
		case BRANCH:
			instructionCounter = operand;
			break;
		case BRANCHNEG:
			if(accumulator < 0)
			{
				instructionCounter = operand;
			}
			break;
		case BRANCHZERO:
			if(accumulator == 0)
			{
				instructionCounter = operand;
			}
			break;
		case HALT:
			dump(accumulator, instructionCounter, instructionRegister, operationCode, operand);
			break;
		}
		if((accumulator > 9999) || (accumulator < -9999)){
			printf("*** Estouro do acumulador ***\n");
			printf("*** Execu��o do Simpletron encerrada de forma anormal. ***\n");
			dump(accumulator, instructionCounter, instructionRegister, operationCode, operand);
			break;
		}
	}
	return 0;
}

void carregarSML()
{
	char nome[12];
	FILE *arq;
	int instrucao, i = 0, num;
	//dados acesso;
	
	fflush(stdin);
	printf("\nInforme o n�mero do programa: ");
	
	do{
		scanf("%d", &num);
		sprintf(nome, "PROG%d.txt", num - 1);
		arq = fopen(nome, "r");
		if(arq == NULL){
			printf("Voc� est� tentando acessar um arquivo que n�o existe!\nTerminando a execu��o do programa\n");
			break;
		}else{
			i++;
		}
	}while( i == 0);
	
	i = 0;	
	if(arq != NULL){
		printf("Exibindos as instru��es do arquivo:\n");
		printf("%s\n", "Instru��es:");
			
		while(!feof(arq)){
			fscanf( arq, "%d", &instrucao); 
			printf("%d  ? %d\n", i, instrucao);
			memory[i] = instrucao;
			++i;
		}
		memory[i - 1] = 0;
		
		printf("Iniciando a execu��o do c�digo SML!\n");
		fclose(arq);
		
		num--;
		
		FILE *arqBin;
		arqBin = fopen("PROG.bin", "rb+");
		
		if(!arqBin){
			printf("N�o foi poss�vel fazer a atualiza��o de acesso!\n");
		}else
		{
			fseek(arqBin, num * sizeof(dados), SEEK_SET);
			
		    struct tm *data;
			atualiza acesso;
	
			time_t segundos;
			time(&segundos);
	
			data = localtime(&segundos);
			
			acesso.dia = data->tm_mday;
			acesso.mes = data->tm_mon+1;
			acesso.ano = data->tm_year+1900;
			acesso.hora = data->tm_hour;
			acesso.min = data->tm_min;
			acesso.sec = data->tm_sec;
			
			fwrite(&acesso, sizeof(atualiza), 1, arqBin);
			
			fclose(arqBin);	
		}
		
	}
}

int num()
{
	static int n = -1;
	n++;
	if(n > 999)
	{
		n = 0;
	}
	
	return n;
}

int main()
{
	setlocale(LC_ALL, "Portuguese");
	
	int opc = 0;
	FILE *arq;
	char nome[12];
	int codigo[MAX];
	int i, j;
	
	while(opc != 4)
	{
		menu();
		do{
			scanf("%i", &opc);
			if((opc <= 0) || (opc >= 5)){
				printf("\nOp��o inv�lida! Digite uma op��o v�lida: ");
			}
			else if(sizeof(opc) != 4){
				printf("S� aceitamos n�meros!\nEncerrando a execu��o do programa!\n");
				break;
			}
		}while((opc <= 0) || (opc >= 5));
		
		switch(opc)
		{
		case 1:
			carregarSML();
			SimpleTrom();
			break;
		case 2:
			inicializa(codigo, MAX);
			
			j = instrucao(codigo, MAX);
			
			sprintf(nome, "PROG%d.txt", num());
			arq = fopen(nome, "w");
			
			if(arq == NULL)
			{
				printf("Houve um problema na abertura do arquivo.\n");
			}
			else{
				printf("O nome do arquivo �:\n%s\n", nome);
				
				fflush(stdin);
				
				//Salvando no arquivo txt
				for(i = 0; i < j; i++)
				{
					fprintf(arq, "%d\n", codigo[i]);
				}
				//Salvando no arquivo bin�rio
				dataHora();
				fclose(arq);
			}

			break;
		case 3:
			pesquisar();
			break;
		case 4:
			break;
	    }	
	}
	return 0;
}
