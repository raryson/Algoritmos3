#include <stdio.h>
#include <stdlib.h>
#define TAM 20000


int validaLetras(char s[], char novoVetor[], int max){
	int i = 0, contador= 0;
	
	
	for(;i < max; i++){
		if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] == 10) || (s[i] == 36)){
	        if(s[i] != 10 && s[i] != 36){
	        	novoVetor[contador] = s[i];
	        	contador++;
			}
			
		}
	}
	return (contador);

}

int lestring(char s[], int max)
{
    int i = 0, contador= 0;
    char letra;

    /* max é o tamanho que "s" pode receber. Deve ser passado o tamanho mesmo, 
       ou seja, se for passado 100 a função já se encarrega de não deixar
       passar de 99 cars (+1 do finalizador)
     */
    for (i = 0; i < (max - 1); i++) {
        /* Lê um único caractere do teclado */

        letra = fgetc(stdin);
    
     

        /* Veja RARYSON que se encontrou um ENTER (\n) mas não leu nenhum
         * caractere válido (i continua sendo 0), não aceita. Precisa ler algo.
         * Decrementa o i para anular o efeito do i++ do laço
         * e volta no laço com continue
         */
        if ((letra == '\n') && (i == 0)) {
            i = i - 1;
            continue;
        }

        /* Agora se leu um enter ("\n") já tendo lido caracteres válidos, 
         * então o usuário terminou de digitar sua string e ela possui ao 
         * menos um caractere válido
         */
        if (letra == '\n')
            break;
            
        s[i] = letra;


        /* se o caractere lido não é ENTER, apenas o coloca no vetor sting */
     
    
}
    /* Sairá do laço anterior por dois motivos:
       a) usuário digitou ENTER e tem ao menos um car válido
       b) mesmo usuário não tendo digitado ENTER, já se leu caracteres suficientes
       para encher o s, de acordo com o max (para evitar o overflow)
     */

    /* Finaliza a string */
    s[i] = 0;                   // s[i] = '\0'; é a mesma coisa

    /* retorna a quantidade de cars lidos (pode ser útil). Então, esta função
       le uma string e retorna o seu tamanho
     */
    return (i);
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
		if((frases[contador] >= 'a') && (frases[contador] <= 'z')){
			continue;
		}
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
		
		transformaMinuscula(frases, tamanhoDasFrases);
		
		if(frases[contador] == 'a'){
			frases[contador] = frases[contador] +23;
		}else if(frases[contador] == 'b'){
			frases[contador] = frases[contador] +23;	
		}else if(frases[contador] == 'c'){
			frases[contador] = frases[contador] +23;	
		}else{
			frases[contador] = frases[contador] -3;
		}
	
	}
	

//	
//	for(contador = 0; contador < tamanhoDasFrases; contador++){
//		frases[contador] = frases[contador];
//	}
	
}

int printa(char *frases, int tamanhoDasFrases){
	int contador;
	
	printf("\n");
	for(contador = 0; contador < tamanhoDasFrases; contador++){
		printf("%c", frases[contador]);
	}
}


int main(int a, char *args[]){
	
	int quantidade, cont, tamanhoDasFrases, tamanhoDoTexto2 = 0, valorDoPrograma = atoi(args[1]);
	char frases[TAM], fraseValidada[TAM];
	int tamanhoDoTexto = 0, tamanhoTotal = 0, verificaValido;
	
	int x = 0;
	if(a == 1){
		
		printf("# Digite quantas frases voce deseja fazer: \n");
		verificaValido = scanf("%d", &quantidade);

		
	
		if(quantidade <= 0 || verificaValido != 1){
			printf("\nERRO ENTRADA");
			while(x != 1){
				printf("\n#Digite novamente\n");
				while(fgetc(stdin) != '\n'){
					continue;
				} 
				verificaValido = scanf("%d", &quantidade);
				if(quantidade > 0 && verificaValido == 1){
					x = 1;
					continue;
				} 
				printf("\nERRO ENTRADA");
			}
			
	
	
		
		
		}
		
		for(cont = 0; cont < quantidade; cont++){
			printf("# Digite 1 frases com at� 20000 cars para cifrar ou decifrar.\n");
			tamanhoDasFrases = lestring(frases, TAM);
			if(frases[0] == '$'){
	
				tamanhoTotal += tamanhoDasFrases-1;
				tamanhoDoTexto2 = validaLetras(frases, fraseValidada, tamanhoDasFrases);
				tamanhoDoTexto += tamanhoDoTexto2;
				decifrar(fraseValidada, tamanhoDoTexto2);
				
				printa(fraseValidada, tamanhoDoTexto2);
				printf("\n");
			
			}else{
			
				tamanhoTotal += tamanhoDasFrases;
				tamanhoDoTexto2 = validaLetras(frases, fraseValidada, tamanhoDasFrases);
				tamanhoDoTexto += tamanhoDoTexto2;
		
				cifrar(fraseValidada, tamanhoDoTexto2);
				printa(fraseValidada, tamanhoDoTexto2+1);
				printf("\n");
		
				//CIFRAGEM
			}
		}
		
		printf("\nCARS %d\nLETRAS %d", tamanhoTotal, tamanhoDoTexto);
		printf("\nFIM\n");
		return (0);
	
		
	}
	if(valorDoPrograma <= 0){
		printf("ERRO. \"%s\" INVALIDO\n", args[1]);
		printf("#Digite quantas frases voce deseja fazer: \n");
		verificaValido = scanf("%d", &quantidade);
		
			
			if(quantidade <= 0){
					printf("\nERRO. TAMANHO INVALIDO");
			while(x != 1){
				printf("\n#Digite novamente\n");
				while(fgetc(stdin) != '\n'){
					continue;
				} 
				verificaValido = scanf("%d", &quantidade);
				if(quantidade > 0){
					x = 1;
					continue;
				} 
				printf("\nERRO. TAMANHO INVALIDO");
					if(verificaValido !=1){
					printf("\nERRO ENTRADA");
			while(y != 1){
				printf("\n#Digite novamente\n");
				while(fgetc(stdin) != '\n'){
					continue;
				} 
				verificaValido = scanf("%d", &quantidade);
				if(quantidade > 0 && verificaValido == 1){
					y = 1;
					continue;
				} 
				printf("\nERRO ENTRADA");
			}
			
			}
			}
			
		
			}
		
		for(cont = 0; cont < quantidade; cont++){
			printf("# Digite 1 frases com at� 20000 cars para cifrar ou decifrar.\n");
			tamanhoDasFrases = lestring(frases, TAM);
			if(frases[0] == '$'){
	
				tamanhoTotal += tamanhoDasFrases-1;
				tamanhoDoTexto2 = validaLetras(frases, fraseValidada, tamanhoDasFrases);
				tamanhoDoTexto += tamanhoDoTexto2;
				decifrar(fraseValidada, tamanhoDoTexto2);
				
				printa(fraseValidada, tamanhoDoTexto2);
				printf("\n");
			
			}else{
			
				tamanhoTotal += tamanhoDasFrases;
				tamanhoDoTexto2 = validaLetras(frases, fraseValidada, tamanhoDasFrases);
				tamanhoDoTexto += tamanhoDoTexto2;
		
				cifrar(fraseValidada, tamanhoDoTexto2);
				printa(fraseValidada, tamanhoDoTexto2+1);
				printf("\n");
				
				//CIFRAGEM
			}
		}
		
		printf("\n%d CARS DIGITADOS\n%d LETRAS", tamanhoTotal, tamanhoDoTexto);
		printf("\nFIM\n");
		return (0);
	
	
	}else{
		
			quantidade = valorDoPrograma;
			for(cont = 0; cont < quantidade; cont++){
			printf("# Digite 1 frases com at� 20000 cars para cifrar ou decifrar.\n");
			tamanhoDasFrases = lestring(frases, TAM);
			if(frases[0] == '$'){
	
				tamanhoTotal += tamanhoDasFrases-1;
				tamanhoDoTexto2 = validaLetras(frases, fraseValidada, tamanhoDasFrases);
				tamanhoDoTexto += tamanhoDoTexto2;
				decifrar(fraseValidada, tamanhoDoTexto2);
				
				printa(fraseValidada, tamanhoDoTexto2);
				printf("\n");
			
			}else{
			
				tamanhoTotal += tamanhoDasFrases;
				tamanhoDoTexto2 = validaLetras(frases, fraseValidada, tamanhoDasFrases);
				tamanhoDoTexto += tamanhoDoTexto2;
		
				cifrar(fraseValidada, tamanhoDoTexto2);
				printa(fraseValidada, tamanhoDoTexto2+1);
				printf("\n");
				
				//CIFRAGEM
			}
		}
		
		printf("\n%d CARS DIGITADOS\n%d LETRAS", tamanhoTotal, tamanhoDoTexto);
		printf("\nFIM\n");
		return (0);
	}
	
	
}
