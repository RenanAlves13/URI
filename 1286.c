#include <stdio.h>

//Roberto deverá entregar e seleciona para ele os pedidos mais demorados.
int main()
{
	int n = 1, max, i, pizza = 0;
	
	while(n != 0){
		scanf("%d", &n);
		scanf("%d", &max);
	    int tempo[n];
		int pizzas[n];
		
		for( i =0; i < n; i++ )
		{
			scanf("%d %d", &tempo[i], &pizzas[i]);
		}
		
		for( i = 0; i < n; i++)
		{
			if(tempo[i])
		}
	}
	
	return 0;
}