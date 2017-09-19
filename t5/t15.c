#include <stdio.h>
#include <stdlib.h>
#define TAM 20000

int lestring(char s[], int max)
{
    int i = 0, contador= 0;
    char letra;

    /* max � o tamanho que "s" pode receber. Deve ser passado o tamanho mesmo, 
       ou seja, se for passado 100 a fun��o j� se encarrega de n�o deixar
       passar de 99 cars (+1 do finalizador)
     */
    for (i = 0; i < (max - 1); i++) {
        /* L� um �nico caractere do teclado */

        letra = fgetc(stdin);
    
        if((letra >= 'a' && letra <= 'z') || (letra >= 'A' && letra <= 'Z') || (letra == 10) || (letra == 36)){
        	if(letra != 10){
        		
        		contador++;	
			}
			
		}


        /* Veja RARYSON que se encontrou um ENTER (\n) mas n�o leu nenhum
         * caractere v�lido (i continua sendo 0), n�o aceita. Precisa ler algo.
         * Decrementa o i para anular o efeito do i++ do la�o
         * e volta no la�o com continue
         */
        if ((letra == '\n') && (i == 0)) {
            i = i - 1;
            continue;
        }

        /* Agora se leu um enter ("\n") j� tendo lido caracteres v�lidos, 
         * ent�o o usu�rio terminou de digitar sua string e ela possui ao 
         * menos um caractere v�lido
         */
        if (letra == '\n')
            break;

        /* se o caractere lido n�o � ENTER, apenas o coloca no vetor sting */
     
    
}
    /* Sair� do la�o anterior por dois motivos:
       a) usu�rio digitou ENTER e tem ao menos um car v�lido
       b) mesmo usu�rio n�o tendo digitado ENTER, j� se leu caracteres suficientes
       para encher o s, de acordo com o max (para evitar o overflow)
     */

    /* Finaliza a string */
    s[i] = 0;                   // s[i] = '\0'; � a mesma coisa

    /* retorna a quantidade de cars lidos (pode ser �til). Ent�o, esta fun��o
       le uma string e retorna o seu tamanho
     */
    return (contador);
}

int transformaMaiuscula(char *frases, int tamanhoDasFrases){
	int contador;
	for(contador = 0; contador < tamanhoDasFrases; contador++){
		if((frases[contador] >= 'A') && (frases[contador] <= 'Z')){
			continue;
		}
		frases[contador] = frases[contador] -32 ;
	}
}

int transformaMinuscula(char *frases, int tamanhoDasFrases){
	int contador;
	for(contador = 0; contador < tamanhoDasFrases; contador++){
		frases[contador] = frases[contador] +32 ;
	}
}

int cifrar(char *frases, int tamanhoDasFrases){
	int contador;	
		
	for(contador = 0; contador < tamanhoDasFrases; contador++){
		if(frases[contador] == 'z'){
			frases[contador] = frases[contador] -23;
		}else if(frases[contador] == 'y'){
			frases[contador] = frases[contador] -23;	
		}else if(frases[contador] == 'x'){
			frases[contador] = frases[contador] -23;	
		}else{
			frases[contador] = frases[contador] + 3;
		}
		
			
	}
	transformaMaiuscula(frases, tamanhoDasFrases);	
	
	
	for(contador = tamanhoDasFrases; contador >= 0; contador--){
		frases[contador+1] = frases[contador];
		if(contador==0){
			frases[contador] = '$';
		}
	
	}

	return(0);
}

int decifrar(char *frases, int tamanhoDasFrases){
	int contador;
	
	for(contador = 0; contador < tamanhoDasFrases; contador++){
		frases[contador] = frases[contador] - 3;	
	}
}

int printa(char *frases, int tamanhoDasFrases){
	int contador;
	
	printf("\n");
	for(contador = 0; contador < tamanhoDasFrases; contador++){
		printf("%c", frases[contador]);
	}
}


int main(){
	int quantidade, cont, tamanhoDasFrases;
	char frases[TAM];
	
	printf("Digite quantas frases voce deseja fazer: ");
	scanf("%d", &quantidade);
	
	if(quantidade < 0){
		return(1);
	}
	
	for(cont = 0; cont < quantidade; cont++){
		tamanhoDasFrases = lestring(frases, TAM);
		if(frases[0] == '$'){
			printf("\nTamanho da frase %d", tamanhoDasFrases);
			//DECIFRAGEM
		}else{
			printf("\nTamanho da frase %d", tamanhoDasFrases);
			cifrar(frases, tamanhoDasFrases);
			printa(frases, tamanhoDasFrases+1);
			//CIFRAGEM
		}
	}
	
	
}
