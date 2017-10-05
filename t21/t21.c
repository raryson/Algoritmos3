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

int cadastraFunc(struct FUNCIONARIO func){
	int tamanhoDaString, numeroLido;
	double salarioLido;
	do{
		printf("#Digite o nome do funcionario:\n");
		tamanhoDaString = lestring(func.nome, STRMAX);
		if(tamanhoDaString <= 0 || tamanhoDaString > STRMAX){
			printf("Digite um nome valido");
		}
	}while(tamanhoDaString == 0 || tamanhoDaString > STRMAX);
	
	
	do{
		printf("#Digite o endereco do funcionario:\n");
		tamanhoDaString = lestring(func.endereco, STRMAX);
		if(tamanhoDaString <= 0 || tamanhoDaString > STRMAX){
			printf("Digite um endereco valido");
		}
	}while(tamanhoDaString == 0 || tamanhoDaString > STRMAX);
	
	
	do{
		printf("#Digite o numero do funcionario:\n");
		numeroLido = scanf("%d", func.numero);
	}while(numeroLido != 1);
	
	do{
		printf("#Digite o salario do funcionario:\n");
		salarioLido = scanf("%lf", func.salario);
	}while(salarioLido != 1);

}

int main(int x, char *valor[]){
	int quantidade, i, scanfQuant;
	
	if((atoi(valor[1]) <= 0) || (atoi(valor[1]) > MAXFUNC)){
		do{
			printf("#Digite a quantidade de pessoas da sua empresa:\n");
			scanfQuant = scanf("%d", &quantidade);
			printf("%i", scanfQuant);
		} while(quantidade <= 0 || quantidade > MAXFUNC || scanfQuant != 1);	
	}
	
	struct FUNCIONARIO func[MAXFUNC];
	for(i = 0; i < quantidade; i++){
		cadastraFunc(func[i]);		
	}
	
	return(0);
	
}
