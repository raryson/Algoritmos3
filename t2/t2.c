#include <stdio.h>
#include <stdlib.h>
#define TAM 10000

int verificaSeJaExiste(int *vetor, int numeroASerVerificado, int tamanhoDoVetor){
	int contador;
	
	for(contador = 0; contador < tamanhoDoVetor; contador++){
		
		if(vetor[contador] == numeroASerVerificado){
			return(1);
		}
	}
	return(2);
}

void bubleSort(int *vetor, int tamanhoDoVetor){
	int fimDoVetor, contador, aux;
	for(fimDoVetor = tamanhoDoVetor-1; fimDoVetor > 0; --fimDoVetor){
		for(contador = 0; contador < fimDoVetor; contador++){
			aux = vetor[contador];
			vetor[contador] = vetor[contador+1];
			vetor[contador+1] = aux;
		}
	}
}

void selectionSort(int *vetor, int tamanhoDoVetor){
	int contador1, contador2, min, aux;
	
	for(contador1 = 0; contador1 < (tamanhoDoVetor-1); contador1++ ){
		min = contador1;
		for(contador2 = (contador1 + 1); contador2 < tamanhoDoVetor; contador2++){
			if(vetor[contador2] < vetor[min]){
				min = contador2;
			}
		}
		if(vetor[contador1] != vetor[min]){
			aux = vetor[contador1];
			vetor[contador1] = vetor[min];
			vetor[min] = aux;
		}	
	}
}

void calculaSomatorio(int *vetor, int tamanhoDoVetor){
	int contador = 0, aux, somatorio = 0;
	
	printf("#Somatorios:\n");
	for(; contador < tamanhoDoVetor; contador++){
		if(vetor[contador] >= 50000){
			printf("Somatorio de %d: ERRO", vetor[contador]);
			continue;
		}
		aux = vetor[contador];
		if(aux < 0){
			aux = -aux;
		}
		for(somatorio = 0; aux > 0; aux--){
		
			somatorio += aux;
		}
		printf("Somatorio de %d: %d\n", vetor[contador], somatorio);
	}
}

void printa(int *vetor, int tamanhoDoVetor){
	int contador = 0;
	
	for(;contador < tamanhoDoVetor; contador++){
		printf("%d\t", vetor[contador]);
	}
}

int mdc(int numero1, int numero2){
	int resto;
	
	while(1){
		resto = numero1%numero2;
		if(resto == 0){
			return(numero2);
		}else{
			numero1 = numero2;
			numero2 = resto;
		}
	}

}

void primos(int *vetor, int tamanhoDoVetor){
	int contador = 0, contador2 = 0, resto = 0, aux1 = 0, aux2 = 0, contador4 = 0;
	
	for(;contador < tamanhoDoVetor; contador++){
		if(contador+1 == tamanhoDoVetor){
		
			
			aux1 = vetor[contador];
			aux2 = vetor[0];
			if(aux1 <0){
				aux1 = -aux1;
			}
			if(aux2 <0){
				aux2 = -aux2;
			}
	
			
			if(mdc(aux1, aux2) == 1){
				printf("\n%d e %d: PRIMOS RELATIVOS", vetor[contador], vetor[0] );
			}else{
				printf("\n# NAO SAO PRIMOS RELATIVOS %d e %d", vetor[contador], vetor[0]);
			}
			break;
		}
			
			aux1 = vetor[contador];
			aux2 = vetor[contador+1];
			if(aux1 <0){
				aux1 = -aux1;
			}
			if(aux2 <0){
				aux2 = -aux2;
			}

		
		if(mdc(aux1, aux2) == 1){
			printf("\n%d e %d: PRIMOS RELATIVOS", vetor[contador], vetor[contador+1] );
		}else{
			printf("\n# NAO SAO PRIMOS RELATIVOS %d e %d", vetor[contador], vetor[contador+1]);
		}
	}
	
}





int main(){
	
	int numeroElementos, vetorElementos[TAM], contador, numeroInserido, vetorOrdenado[TAM];
	
	printf("# Quantos elementos voce quer (1 a 10000)\n");
	scanf("%d", &numeroElementos);
	
	if(numeroElementos <= 0 || numeroElementos > TAM){
		printf("ERRO. TAMANHO INVALIDO\n");
		return(0);
	}
	
	printf("# Digite %d numeros positivos ou negativos sem repetir\n", numeroElementos);
	
	for(contador = 0; contador < numeroElementos; contador++){
		scanf("%d", &numeroInserido);	
		if(verificaSeJaExiste(vetorElementos, numeroInserido, numeroElementos) == 1){
			printf("ERRO. JA EXISTE\n");
			printf("# DIGITE NOVAMENTE\n");
			contador--;
			continue;
		}else if(verificaSeJaExiste(vetorElementos, numeroInserido, numeroElementos) == 2){
			vetorElementos[contador] = numeroInserido;
		}
	}
	
	selectionSort(vetorElementos, numeroElementos);
	printf("\n#Valores Ordenados");
	printf("\n#Valor Somatorio");
	calculaSomatorio(vetorElementos, numeroElementos);
	printf("\n#Verificacao de primos relativos\n");
	primos(vetorElementos, numeroElementos);
	

	return(0);
	
}
