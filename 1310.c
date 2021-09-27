#include <stdio.h>

//Prototipação
int maximo(int a, int b);


int main()
{
	int dias, custo, i, lucro, lucroFinal;
	
	while(scanf("%d", &dias) != EOF){
		
		scanf("%d", &custo);
		
		int vetor[dias];
		
		for(i = 0; i < dias; i++)
		{
			scanf("%d", &vetor[i]);
		}
		lucro = 0;
		lucroFinal = 0;
		for(i = 0; i < dias; i++)
		{
			lucro += (vetor[i] - custo);
			lucro = maximo(lucro, 0);
			lucroFinal = maximo(lucroFinal, lucro);
		}
		printf("%d\n", lucroFinal);
	}
	
	return 0;
}

int maximo(int a, int b)
{
	if(a > b){
		return a;
	}
	else{
		return b;
	}
	return 0;
}