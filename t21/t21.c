#include <stdio.h>
#include <stdlib.h>
#define MAXFUNC 1000
#define STRMAX  500


struct FUNCIONARIO{
	char nome[STRMAX];
	char endereco[STRMAX];
	int numero;
	double salario;
};


int strCompare(char str1[], char str2[]){
	int contador;
	
	for(contador = 0; str1[contador]; contador++){
		  
		if(str1[contador] - str2[contador] == 0){
			continue;
		}else{
			return(str1[contador] - str2[contador]);		
		}
		
	}
	return(str1[contador] - str2[contador]);	
}

int transformaMaiuscula(char *frases){
	int contador;
	for(contador = 0; frases[contador]; contador++){
		if((frases[contador] >= 'A') && (frases[contador] <= 'Z') || frases[contador] == ' ' || (frases[contador] >= '1' && frases[contador] <= '9' )){
			continue;
		}
		frases[contador] = frases[contador] -32 ;
	}
}

int strCopy(char str1[], char str2[], int tamanho){
	int contador;
	
	for(contador = 0; contador < tamanho; contador++){
		str1[contador] = 0;
	}
	
	for(contador = 0;  contador < tamanho; contador++){
		str1[contador] = str2[contador];
	}
	str1[contador+1] = 0;
	return(contador);
}

int safeFflush(){
	while(fgetc(stdin)!='\n');    
}
int lestring(char s[], int max)
{
    int i = 0;
    char letra;

    for (i = 0; i < (max - 1); i++) {
    
        letra = fgetc(stdin);

        if ((letra == '\n') && (i == 0)) {
            i = i - 1;
            continue;
        }

      
        if (letra == '\n')
            break;

        s[i] = letra;
    }

    s[i] = 0;                   
    return (i);
}

int cadastraFunc(struct FUNCIONARIO func[], int cont){
	int tamanhoDaString, numeroLido;
	double salarioLido;
	do{
		printf("#Digite o nome do funcionario:\n");
		tamanhoDaString = lestring(func[cont].nome, STRMAX);
		if(tamanhoDaString <= 0 || tamanhoDaString > STRMAX){
			printf("ERRO entrada invalida\n");
		}
	}while(tamanhoDaString == 0 || tamanhoDaString > STRMAX);
	
	transformaMaiuscula(func[cont].nome);
	
	do{
		printf("#Digite o endereco do funcionario:\n");
		tamanhoDaString = lestring(func[cont].endereco, STRMAX);
		if(tamanhoDaString <= 0 || tamanhoDaString > STRMAX){
			printf("ERRO entrada invalida\n");
		}
	}while(tamanhoDaString == 0 || tamanhoDaString > STRMAX);
	
	
	do{
		printf("#Digite o numero do funcionario:\n");
		numeroLido = scanf("%d", &func[cont].numero);
		if(numeroLido == 0){
			printf("ERRO entrada invalida\n");
			safeFflush();  
		}
	}while(numeroLido != 1);
	
	do{
		printf("#Digite o salario do funcionario:\n");
		salarioLido = scanf("%lf", &func[cont].salario);
		if(salarioLido == 0){
			printf("ERRO entrada invalida\n");
			safeFflush();  
		}
	}while(salarioLido != 1);
	
	printf("\n#Funcionario adicionado com sucesso!\n\n");

}


int main(int x, char *valor[]){
	int quantidade, i, scanfQuant, 	qualEMaior, auxInt, j;
	double auxDouble, qualEMaiorDouble, contSalario = 0;
	char aux[STRMAX];
	
	if((atoi(valor[1]) <= 0) || (atoi(valor[1]) > MAXFUNC)){
		if(valor[1] != NULL){
			printf("ERRO %s\n", valor[1]);
		}
		do{
			printf("#Digite a quantidade de pessoas da sua empresa:\n");
			scanfQuant = scanf("%d", &quantidade);
			if(scanfQuant == 0){
				printf("ERRO entrada invalida\n");
				safeFflush();  
			}else if(quantidade > MAXFUNC || quantidade <= 0){
				printf("ERRO %d\n", quantidade);
			}
		} while(quantidade <= 0 || quantidade > MAXFUNC || scanfQuant != 1);	
	}else{
		quantidade = atoi(valor[1]);
	}
	
	struct FUNCIONARIO func[MAXFUNC];
	
	for(i = 0; i < quantidade; i++){
		cadastraFunc(func, i);		
	}


	//ordena��o de ordem alfabetica
	
	for(j = 1; j < quantidade; j++){

		for(i = 1; i < quantidade; i++){
			qualEMaior =  strCompare(func[i-1].nome, func[i].nome);
			
			if(qualEMaior > 0){
				//troco nome
				strCopy(aux, func[i-1].nome, sizeof(aux));
				strCopy(func[i-1].nome, func[i].nome, sizeof(func[i-1].nome));
				strCopy(func[i].nome, aux, sizeof(func[i].nome));
				
				//trocop endere�o
				strCopy(aux, func[i-1].endereco,  sizeof(aux));
				strCopy(func[i-1].endereco, func[i].endereco, sizeof(func[i-1].endereco));
				strCopy(func[i].endereco, aux, sizeof(func[i].endereco));
				
				//troco numero
				auxInt = func[i-1].numero;
				func[i-1].numero = func[i].numero;
				func[i].numero = auxInt;
				
				//troco salario
				auxDouble = func[i-1].salario;
				func[i-1].salario = func[i].salario;
				func[i].salario = auxDouble;
				
			}
		}
	}
	
	printf("\n#VALORES ORDENADOS POR ORDEM ALFABETICA\n");			
	for(i = 0; i < quantidade; i++){
		
		printf("%06d %s, %s, R$ %.2lf\n", func[i].numero, func[i].nome, func[i].endereco, func[i].salario);
	}
	
	if(quantidade < 10){
		//lista o numero de quantidade
		for(j = 1; j < quantidade; j++){
			for(i = 1; i < quantidade; i++){
				qualEMaiorDouble =  func[i].salario - func[i-1].salario;
				if(qualEMaiorDouble > 0){
					
						//troco nome
				strCopy(aux, func[i-1].nome,  sizeof(aux));
				strCopy(func[i-1].nome, func[i].nome, sizeof(func[i-1].nome));
				strCopy(func[i].nome, aux, sizeof(func[i].nome));
				
				//trocop endere�o
				strCopy(aux, func[i-1].endereco,  sizeof(aux));
				strCopy(func[i-1].endereco, func[i].endereco,  sizeof(func[i-1].endereco));
				strCopy(func[i].endereco, aux, sizeof(func[i].endereco));
				
				//troco numero
				auxInt = func[i-1].numero;
				func[i-1].numero = func[i].numero;
				func[i].numero = auxInt;
					
					auxDouble = func[i-1].salario;
					func[i-1].salario = func[i].salario;
					func[i].salario = auxDouble;
				}
			}
		}
	}else{
		//lista os 10
		for(j = 1; j < quantidade; j++){

			for(i = 1; i < quantidade; i++){
				qualEMaiorDouble =  func[i].salario - func[i-1].salario;
				if(qualEMaiorDouble > 0){
					
						//troco nome
				strCopy(aux, func[i-1].nome, sizeof(aux));
				strCopy(func[i-1].nome, func[i].nome, sizeof(func[i-1].nome));
				strCopy(func[i].nome, aux, sizeof(func[i].endereco));
				
				//trocop endere�o
				strCopy(aux, func[i-1].endereco, sizeof(aux));
				strCopy(func[i-1].endereco, func[i].endereco, sizeof(func[i-1].nome));
				strCopy(func[i].endereco, aux, sizeof(func[i].endereco));
				
				//troco numero
				auxInt = func[i-1].numero;
				func[i-1].numero = func[i].numero;
				func[i].numero = auxInt;
					auxDouble = func[i-1].salario;
					func[i-1].salario = func[i].salario;
					func[i].salario = auxDouble;
				}
			}
		}
	}

	printf("\n#TOP 10 SALARIOS TUCHUTUHTUCHU\n");
	if(quantidade < 10){
		for(i = 0; i < quantidade; i++){
			printf("R$   %.2lf %s\n", func[i].salario, func[i].nome);
		}
	
	}else{
		for(i = 0; i < 10; i++){
			printf("R$   %.2lf %s\n", func[i].salario, func[i].nome);
		}
	
	}
	
	for(i = 0; i < quantidade; i++){
		contSalario += func[i].salario;
	}
	
	printf("#Folha de salario total:\n");
	printf("\nR$ %.2lf\n", contSalario);
	
	printf("#FIM");
	
	return(0);
	
}
