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
	
	printf("#\nFuncionario adicionado com sucesso!\n\n");

}


int main(int x, char *valor[]){
	int quantidade, i, scanfQuant;
	
	if((atoi(valor[1]) <= 0) || (atoi(valor[1]) > MAXFUNC)){
		printf("ERRO %s\n", valor[1]);
		do{
			printf("#Digite a quantidade de pessoas da sua empresa:\n");
			scanfQuant = scanf("%d", &quantidade);
			if(scanfQuant == 0){
				printf("ERRO entrada invalida\n");
				safeFflush();  
			}
		} while(quantidade <= 0 || quantidade > MAXFUNC || scanfQuant != 1);	
	}else{
		quantidade = atoi(valor[1]);
	}
	
	struct FUNCIONARIO func[MAXFUNC];
	
	for(i = 0; i < quantidade; i++){
		cadastraFunc(func, i);		
	}
	
	for(i = 0; i < quantidade; i++){
		printf("\nNome\tEndereco\tNumero\tSalario\n");
		printf("%s\t%s\t%d\t%lf\n", func[i].nome, func[i].endereco, func[i].numero, func[i].salario);
	}
	
	int qualEmaior = strCompare(func[0].nome, func[1].nome);
	
	printf("O maior e %d");
	
	return(0);
	
}
