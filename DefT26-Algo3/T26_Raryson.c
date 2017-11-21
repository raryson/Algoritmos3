/* Comente o define abaixo se estiver no DOS/Windows */
//#define LINUX

#include <stdio.h>
#include <stdlib.h>
#define MAXSTRING 10000
///* Coisas que no DOS é de um jeito e no Linux é de outro */
//#ifdef LINUX
///* ----------------------- LINUX ONLY ----------------------------*/
///* Se estiver no LINUX, compila o que segue */
//#include <termios.h>
//#include <unistd.h>
//#define clrscr()    printf("\033[2J")

/* Esta funcão para LINUX é para uso em menus. Ela espera pelo pressionamento
 * de uma tecla, mas quando a mesma é pressionada, não imprime ela
 * na tela. Devido ao terminal, movido a linhas, isto não é tão trivial
 * de se fazer no LINUX
 */
//char le_tecla()
//{
//    struct termios t_orig, t_novo;
//    char letra;
//
//    /* Pega as caracteristicas atuais do terminal */
//    tcgetattr(0, &t_novo);
//
//    t_orig = t_novo;
//    t_novo.c_lflag &= ~(ECHO | ICANON | IEXTEN);
//    tcsetattr(0, TCSADRAIN, &t_novo);
//
//    letra = fgetc(stdin);
//    tcsetattr(0, TCSADRAIN, &t_orig);
//
//    return (letra);
//}

/* ---------------------- FIM LINUX ONLY ---------------------*/
//
//#else
/* ---------------------DOS/Windows ONLY ----------------------*/
/* Se estiver no DOS/WINDOWS (não LINUX) compila o que segue */
#include <conio.h>
/* A funcao getch le uma tecla mas nao imprime ela
   na tela automaticamente. Interessante isto, pois
   ai eu EVITO que se digite coisas indesejaveis
*/
#define le_tecla() getch()
#define clrscr() system("cls");
//#endif
/* ----------------- FIM DOS/WINDOWS ONLY -----------------*/

#define pausa() {printf("Pressione tecla"); le_tecla();}

#define STRMAX 	100
struct FUNC {
    char nome[STRMAX + 1];
    char endereco[STRMAX + 1];
    int reg;
    double sal;
    char top;                   // não é usado no T26, mas se tirar muda o tamanho da estrutura
};


char menu()
{
    char letra;

    clrscr();
    printf("Digite a opção desejada:\n");

    printf("\t[P]esquisar um nome no arquivo\n");
    printf("\t[B]uscar um funcionário de índice X no arquivo\n");
    printf("\t[A]lterar os dados de um funcionario no arquivo\n");
    printf("\t[S]air do programa\n");
    printf("\nSua opção: ");

    while (1) {
        letra = le_tecla();
        if ((letra >= 'a') && (letra <= 'z')) {
            letra = letra - 32;
        }
        switch (letra) {
        case 'P':
        case 'B':
        case 'A':
        case 'S':
            printf("%c\n", letra);
            /* Só imprime se é uma opção válida. Pode pressionar LIXO a vontade
             * que nada acontece
             * */
            return (letra);
        }
    }
}

/* BRINDE GRATIS: função que imprime todos os dados encontrados no arquivo.
 * Deixa o arquivo na posição que estava e retorna quantos imprimiu. 
 * Não precisa passar a quantidade de funcionários, pois ele lê do arquivo
 * Esta função não está sendo chamada no main. Não faz parte do T26. Está
 * aqui para inspiração e testes.
 * */
 
 int safeFflush(){
	while(fgetc(stdin)!='\n');    
}

int impFuncBin(FILE * arq)
{
    int i, qtd;
    int onde, pos;
    struct FUNC func;
    /* Apenas para UM funcionário, pois a ideia aqui é não trabalhar
     * com vetor
     * */

    if (arq == NULL) {
        fprintf(stderr, "# ERRO impFuncBin: arquivo não aberto\n");
        return (0);
    }
    /* A função fread retorna quantos elementos foram lidos com sucesso.
     * Se eu tentar ler de um arquivo que não pode ler, então retornará
     * zero, pois leu ZERO elementos
     * */
    onde = ftell(arq);          // guardando a posição atual do arquivo

    fseek(arq, 0, SEEK_SET);    // indo para o início
    if (fread(&qtd, sizeof(int), 1, arq) == 0) {
        fprintf(stderr, "# ERRO impFuncBin: não pude ler quantidade.");
        fprintf(stderr, "Arquivo binário foi aberto corretamente?\n");
        fseek(arq, onde, SEEK_SET);
        return (0);
    }

    /* Eu podia ir apenas lendo e imprimindo, na sequencia (está comentado) */
    /* COMENTADO A partir daqui:
       for (i=0; i<qtd; i++){
           if (fread(&func, sizeof(struct FUNC), 1, arq)==0){
                fprintf(stderr, "# ERRO impFuncBin: não pude ler func %d.", i);
                fprintf(stderr, "Arquivo binário está correto?\n");
                fseek(arq, onde, SEEK_SET);
                return(0);
           }
           printf("[%d] => \"%s\", \"%s\", \"%d\", \"%lf\"\n", i, func.nome, func.endereco, func.reg, func.sal);
       }
    Ate aqui */

    /* mas achei interessante fazer indo para o indice certo */
    for (i = 0; i < qtd; i++) {
        /* indo para a posição do arquivo onde deverá estar o funcionário i */
        pos = sizeof(int) + (i * sizeof(struct FUNC));
        if (fseek(arq, pos, SEEK_SET) != 0) {
            /* fseek retorna ZERO se conseguiu ir na posição pretendida */
            fprintf(stderr, "# ERRO impFuncBin: fseek não pode ir onde queria\n");
            return (i);
        }

        if (fread(&func, sizeof(struct FUNC), 1, arq) == 0) {
            fprintf(stderr, "# ERRO impFuncBin: não pude ler func %d.", i);
            fprintf(stderr, "Arquivo binário está correto?\n");
            fseek(arq, onde, SEEK_SET);
            return (0);
        }
        printf("[%d] => \"%s\", \"%s\", \"%d\", \"%lf\"\n", i, func.nome, func.endereco, func.reg, func.sal);
    }

	fseek(arq, onde, SEEK_SET);
	return(i);
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



int pesquisaIndex(FILE * arq, int qtd){
	   /* Usar função:
             * - solicitar um inteiro de 0 a qtd-1
             * - ir, por fseek, direto na posição do arquivo onde está este funcionário
             * - imprimir os seus dados
             * - Voltar a este menu
             * */
    
	int checaValido, i, comparacao = 0, index, pos, onde, x;
	
	do{
		printf("\nDigite um numero de 0 a %d\n", qtd-1);
	
		
		x = scanf("%d", &index);
		safeFflush();
		if(index >= 0 && index <= qtd-1){
		
			x = 1;
		}else{
			x = 2;
		}
	}while(x != 1);
	
		

	onde = ftell(arq);  


	pos = sizeof(int) + (index * sizeof(struct FUNC));
	
	 if (fseek(arq, pos, SEEK_SET) != 0) {
            /* fseek retorna ZERO se conseguiu ir na posição pretendida */
            fprintf(stderr, "# ERRO impFuncBin: fseek não pode ir onde queria\n");
            return (i);
    }
	
	struct FUNC func;
	
	
	if (fread(&func, sizeof(struct FUNC), 1, arq) == 0) {
            fprintf(stderr, "# ERRO impFuncBin: não pude ler func %d.", i);
            fprintf(stderr, "Arquivo binário está correto?\n");
            fseek(arq, onde, SEEK_SET);
            return (0);
    }
    printf("[%d] => \"%s\", \"%s\", \"%d\", \"%lf\"\n", index, func.nome, func.endereco, func.reg, func.sal);
    
    return(index);
             
             
}


int alteraBin(FILE * arq, int qtd){

		int index  = pesquisaIndex(arq, qtd), pos, onde;
		int checaSeFor;
	
		printf("\nDigite os novos dados para esse funcionario\n");
		struct FUNC func;
		
		    impFuncBin(arq);
		
		printf("\nO nome sera: ");
		lestring(func.nome, MAXSTRING);
		printf("\nO NOME E %s\n", func.nome);
		printf("\nO numero sera: ");
		scanf("%d", &func.reg);
		printf("\nO endereco sera: ");
		lestring(func.endereco, MAXSTRING);
		printf("\nO salario sera: ");
		scanf("%lf", &func.sal);
		
		pos = sizeof(int) + (index * sizeof(struct FUNC));
	
		if (fseek(arq, pos, SEEK_SET) != 0) {
            /* fseek retorna ZERO se conseguiu ir na posição pretendida */
            fprintf(stderr, "# ERRO impFuncBin: fseek não pode ir onde queria\n");
            return (1);
   		}
   		checaSeFor = fwrite(&func, sizeof(struct FUNC) , 1, arq);
   		if(checaSeFor==0){
   			return(0);
		   }else{
		   	return (1);
		}
		

             
             
}

int pesquisaNome(FILE * arq, int qtd){
	
	 /* Usar função:
             * - pedir um nome (ler em uma string)
             * - procurar o nome no arquivo binário, um a um, desconsiderando
             *   maiúsculas e minúsculas (você guardou aquelas funções de string, não?)
             * - se achar um funcionário com aquele nome, imprimir a posição dele
             *   e os seus demais dados (se ele é o primeiro do arquivo, então ele
             *   é posição ZERO)
             * - Encerrar e voltar aqui, neste menu.
             * - Se existirem mais de um funcionário com o mesmo nome (não deveria), 
             *   considerar apenas o primeiro encontrado)
             * */

	char nome[MAXSTRING];
	int checaValido, i, comparacao = 0;
	
	
	printf("\nDigite um nome para ser pesquisado\n");	
	lestring(nome, MAXSTRING);

	
	struct FUNC func;

	
	for(i = 0; i < qtd; i++){
		
		checaValido = fread(&func, sizeof(struct FUNC), 1, arq);
		if(checaValido == 1){
			
			transformaMaiuscula(nome);
			transformaMaiuscula(func.nome);
			comparacao = strCompare(nome, func.nome);
			if(comparacao == 0){
				 printf("[%d] => \"%s\", \"%s\", \"%d\", \"%lf\"\n", i, func.nome, func.endereco, func.reg, func.sal);
				 return(0);
			}
			
		}else{
			printf("\n\nAconteceu algum erro na leitura da Struct\n");
			return(1);
		}
	}

	
}


int main(int argc, char *argv[])
{
    char opcao;


/* JOGO RAPIDO PARA TESTAR O ARQUIVO bin: 
    FILE *arq;
    arq = fopen("dados.bin", "rb+");
    
    return (0);
*/

	FILE *arq;
	int tamanho, checaValido;
	
	if(argc >= 2){
		arq = fopen(argv[1], "rwb+");
	}else{
		printf("Arquivo nao informado");
		return(1);
	}

     
    checaValido = fread(&tamanho, sizeof(int), 1, arq);
    if(checaValido != 1){
    	printf("Quantidade no arquivo bin invalida");
    	return(1);
	}

     
     
    for (opcao = menu(); opcao != 'S'; opcao = menu()) {
        switch (opcao) {
        case 'P':
        	pesquisaNome(arq, tamanho);
        
             
            break;
        case 'B':
        	pesquisaIndex(arq, tamanho);
           
            break;
        case 'A':
        	alteraBin(arq, tamanho);
         
            break;
        case 'S':
            /* Fechar arquivo binário, encerrar programa */
            
            fclose(arq);
            break;
        }
        pausa();
    }
}
