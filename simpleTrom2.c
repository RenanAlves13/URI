#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//OperaÃ§Ãµes de entrada/saÃ­da
#define READ 10
#define WRITE 11
//OperaÃ§Ãµes de carregamento/armazenamento
#define LOAD 20
#define STORE 21
//OperaÃ§Ãµes aritmÃ©ticas
#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33
//OperaÃ§Ãµes de transferÃªncia de controle
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
	printf("*** Digite uma opção ***\n");
	printf("1 - Carregar/executar um código SML.\n");
	printf("2 - Criar um novo código.\n");
	printf("3 - Pesquisar códigos existentes.\n");
	printf("4 - Para sair.\n");
	printf("Digite sua opção: ");
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

	printf("Descrição do código[ máximo %d letras]: ", MAX);
	fflush(stdin);
	/*Salvando em um tipo de estrutura diferente para salvar no arquivo binário, pois com o outro struct não foi 
	possível.*/
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
		printf("Não foi possivel abrir o arquivo binário.\n");
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
		printf("Não foi possivel abrir o arquivo binário.\n");
	}
	printf("\n");
	while(fread(&acesso, sizeof(dados), 1, arqBin)){
		printf("Arquivo número %d:\nData: %d/%d/%d\nHora: %d:%d:%d\nDescrição: %s.\n", i++, acesso.dia, acesso.mes, acesso.ano, acesso.hora, acesso.min, acesso.sec, acesso.descricao);
		printf("\n");
	}
	
	fclose(arqBin);
}

int instrucao(int codigo[],int max)
{
	int instrucao, operationCode;
	int i = 0;
	
	printf("Digite as instruções( entre 0 e 9999, e -9999 para encerrar):\n");
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
			 printf("Operação inválida!\nDigite outra operação:\n");
			 	
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
			printf("\nEscrevendo da memória para o terminal: %d.\n", memory[operand]);
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
				printf("Divisão por zero não podem ser realizadas!\n");
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
			printf("*** Execução do Simpletron encerrada de forma anormal. ***\n");
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
	printf("\nInforme o número do programa: ");
	
	do{
		scanf("%d", &num);
		sprintf(nome, "PROG%d.txt", num - 1);
		arq = fopen(nome, "r");
		if(arq == NULL){
			printf("Você está tentando acessar um arquivo que não existe!\nTerminando a execução do programa\n");
			break;
		}else{
			i++;
		}
	}while( i == 0);
	
	i = 0;	
	if(arq != NULL){
		printf("Exibindos as instruções do arquivo:\n");
		printf("%s\n", "Instruções:");
			
		while(!feof(arq)){
			fscanf( arq, "%d", &instrucao); 
			printf("%d  ? %d\n", i, instrucao);
			memory[i] = instrucao;
			++i;
		}
		memory[i - 1] = 0;
		
		printf("Iniciando a execução do código SML!\n");
		fclose(arq);
		
		num--;
		
		FILE *arqBin;
		arqBin = fopen("PROG.bin", "rb+");
		
		if(!arqBin){
			printf("Não foi possível fazer a atualização de acesso!\n");
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
				printf("\nOpção inválida! Digite uma opção válida: ");
			}
			else if(sizeof(opc) != 4){
				printf("Só aceitamos números!\nEncerrando a execução do programa!\n");
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
				printf("O nome do arquivo é:\n%s\n", nome);
				
				fflush(stdin);
				
				//Salvando no arquivo txt
				for(i = 0; i < j; i++)
				{
					fprintf(arq, "%d\n", codigo[i]);
				}
				//Salvando no arquivo binário
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
