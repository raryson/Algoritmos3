/*Defini��o:

Fa�a um programa em C ANSI que solicite que o usu�rio digite N elementos
inteiros, positivos ou negativos. N n�o pode ser maior que 10000. 

Usu�rio deve dizer qual o tamanho de N no in�cio (deve ler do teclado).
(simplesmente encerrar a execu��o se for um valor de N inv�lido. N inv�lido
ser� menor ou igual a 0 ou maior que 10000)

Armazene todos os elementos digitados em um vetor de inteiros antes de 
realizar qualquer opera��o com eles.

Ap�s a digita��o e armazenamento de todos os inteiros, para cada inteiro 
armazenado no vetor, fa�a:

a) Informe se o n�mero � par ou impar. 
b) informe se o n�mero � primo. Se n�o for primo, imprima o PRIMEIRO divisor
encontrado (evidentemente descartando o 1).

c) Ao final do c�digo, imprima a soma de todos os elementos positivos
*/

#include <stdio.h>
#include <stdlib.h>
#define TAM 10000

void checaPar(int valorASerChecado){
	if(valorASerChecado % 2 == 0){
		printf("\tPAR\t");
	}else{
		printf("\tIMPAR\t");
	}
}

void checaPrimo(int valorASerChecado){
	int contador1, contador2 = 0, valorMultiplicado;
	if(valorASerChecado < 0){
		valorASerChecado = -valorASerChecado;
	}
	
	for(contador1 = 1; valorASerChecado >= contador1 ; contador1++){
		if(valorASerChecado % contador1 ==0){
			contador2++;
		}
	}
	if(contador2 == 2){
		printf("\tPRIMO\t");
	}else if(contador2 == 1){
		printf("\tNAO PRIMO\t");
	}else if(contador2 == 0){
		printf("\tNAO PRIMO\t");
	}else{
		for(contador1 = 1, contador2 = 1; valorASerChecado >= contador1 ; contador1++){
		if(valorASerChecado % contador1 ==0){
			contador2++;
			if(contador2 == 3){
					printf("\tNAO PRIMO\t(DIVIDE POR %i)", contador1);
					contador2 = 0;
				}
			}
		}
	}	
	
}

int main(){
	int valor, contador = 0, soma = 0;
	
	printf("# Quantos elementos voce quer? (1 a 10000)\n");
	scanf("%i", &valor);
	if(valor <= 0 || valor > TAM){
		printf("# Erro. Valor %i invalido", valor);
		printf("\nENCERRADO: ERRO");
	}else{
	
	
		int array[valor];
		printf("# Digite %i numeros inteiros positivos ou negativos:\n", valor);
		for(; contador < valor; contador++){
			scanf("%i", &array[contador]);
		}
		
		printf("# Lido com sucesso %i inteiros\n", valor);
		for(contador = 0; contador < valor; contador++){
			printf("\t%i\t", array[contador]);
			checaPar(array[contador]);
			checaPrimo(array[contador]);
			if(array[contador] > 0){
				soma += array[contador];
			}
			printf("\n");
		}
		printf("SOMA %i", soma);
	}
	exit(0);

}
