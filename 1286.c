#include <stdio.h>

//Prototipação
int maximo(int a, int b);

struct pedido{
    int tempo;
    int pizzas;
};

struct pedido entrega[21];
int matriz[21][31];

int main(){
	
	int N, P, j, i;
	
	while(scanf("%d", &N) != EOF){
		
		if(N == 0){
			break;
		}
		
		scanf("%d", &P);
					
		for(i = 1; i <= N; i++){
			scanf("%d %d", &entrega[i].tempo, &entrega[i].pizzas);
		}
					
		for(i = 0; i <= N; i++){
						
			for(j = 0; j <= P; j++){
						
				if(i == 0 || j == 0){
                    matriz[i][j] = 0;
                }
                        
                else{
								
					if(entrega[i].pizzas > j){
						matriz[i][j] = matriz[i - 1][j];
					}
					else{
						matriz[i][j] = maximo(matriz[i - 1][j - entrega[i].pizzas] + entrega[i].tempo, matriz[i - 1][j]); 
					}
				}
			}
		}
		printf("%d min.\n", matriz[N][P]);
	}
	
	return 0;
}

int maximo(int a, int b){
	if(a > b){
		return a;
	}
	else{
		return b;
	}
}