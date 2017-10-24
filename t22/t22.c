#include <stdio.h>
#include <stdlib.h>

#define STRMAX  100


struct FUNCIONARIO{
	char nome[STRMAX+1];
	char *endereco;
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
	char aux[2000];
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
		tamanhoDaString = lestring(aux, 20000);
		func[cont].endereco  = malloc(tamanhoDaString * sizeof(func[cont].endereco ) +1);
		strCopy(func[cont].endereco, aux, tamanhoDaString+1);
		
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

int ordenaStructEmOrdemAlfabetica(struct FUNCIONARIO func[], int quantidade)
{	
		int i = 0, j = 0, qualEMaior = 0, auxInt = 0;
		double auxDouble = 0;
		char aux[STRMAX];
		
		for(j = 1; j < quantidade; j++){

			for(i = 1; i < quantidade; i++){
				qualEMaior =  strCompare(func[i-1].nome, func[i].nome);
				
				if(qualEMaior > 0){
					//troco nome
					strCopy(aux, func[i-1].nome, sizeof(aux));
					strCopy(func[i-1].nome, func[i].nome, sizeof(func[i-1].nome));
					strCopy(func[i].nome, aux, sizeof(func[i].nome));
					
					//trocop endereço
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
	
}

int ordenaStructSalario(struct FUNCIONARIO func[], int quantidade){
		int i = 0, j = 0, qualEMaiorDouble = 0, auxInt = 0;
		double auxDouble = 0;
		char aux[STRMAX];
		
		for(j = 1; j < quantidade; j++){
			for(i = 1; i < quantidade; i++){
				qualEMaiorDouble =  func[i].salario - func[i-1].salario;
				if(qualEMaiorDouble > 0){
					
						//troco nome
				strCopy(aux, func[i-1].nome,  sizeof(aux));
				strCopy(func[i-1].nome, func[i].nome, sizeof(func[i-1].nome));
				strCopy(func[i].nome, aux, sizeof(func[i].nome));
				
				//trocop endereço
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
}


int main(int x, char *valor[]){
	int quantidade, i, scanfQuant, 	qualEMaior, auxInt, j;
	double auxDouble, qualEMaiorDouble, contSalario = 0;
	char aux[STRMAX];
	struct FUNCIONARIO *func;
	

	
	if((atoi(valor[1]) <= 0) )  {
		if(valor[1] != NULL){
			printf("ERRO %s\n", valor[1]);
		}
			
		do{
			printf("#Digite a quantidade de pessoas da sua empresa:\n");
			scanfQuant = scanf("%d", &quantidade);
			func = malloc(quantidade * (sizeof(struct FUNCIONARIO)));
			if(scanfQuant == 0){
				printf("ERRO entrada invalida\n");
				safeFflush();  
			}else if(quantidade <= 0){
				printf("ERRO %d\n", quantidade);
			}else if(func == NULL){
				printf("ERRO alocacao\n");
				printf("#Erro, faltou espaco em memoria\n");
			}
		} while(quantidade <= 0 || scanfQuant != 1);	
	}else{
		quantidade = atoi(valor[1]);
	}
	

	
	for(i = 0; i < quantidade; i++){
		cadastraFunc(func, i);		
	}

	ordenaStructEmOrdemAlfabetica(func, quantidade);
	
	printf("\n#VALORES ORDENADOS POR ORDEM ALFABETICA\n");			
	for(i = 0; i < quantidade; i++){
		
		printf("%06d %s, %s, R$ %.2lf\n", func[i].numero, func[i].nome, func[i].endereco, func[i].salario);
	}
	
	if(quantidade < 10){
		//lista o numero de quantidade
		ordenaStructSalario(func, quantidade);
	}else{
		//lista os 10
		ordenaStructSalario(func, quantidade);
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
