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
	
	printf("# Somatorios:\n");
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


int main(){
	
	int numeroElementos, vetorElementos[TAM], contador, numeroInserido, vetorOrdenado[TAM];
	
	printf("# Quantos elementos você quer (1 a 10000)");
	scanf("%d", &numeroElementos);
	
	if(numeroElementos < 0 || numeroElementos > TAM){
		printf("ERRO. TAMANHO INVALIDO\n");
		return(0);
	}
	
	printf("# Digite %d números positivos ou negativos sem repetir\n", numeroElementos);
	
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
	calculaSomatorio(vetorElementos, numeroElementos);
	
	
	
	
	
	
	
}
