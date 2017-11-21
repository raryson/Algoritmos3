/* Comente o define abaixo se estiver no DOS/Windows */
#define LINUX

#include <stdio.h>
#include <stdlib.h>

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

    /* Itens a serem programados aqui:
     * - Variáveis
     * - abrir arquivo que vem de argv[1] como binário
     * - ler quantidade de itens
     * - deixar aberto para leitura e escrita 
     * - se Não conseguiu abrir ou se não tem itens, abortar (só funciona
     *   com um arquivo com funcionários em BINÁRIO.
     * - Todas as funções devem receber o FILE do arquivo já aberto
     *   no modo que permita ler e escrever.
     * */
     
    checaValido = fread(&tamanho, sizeof(int), 1, arq);
    if(checaValido != 1){
    	printf("Quantidade no arquivo bin invalida");
    	return(1);
	}

     
     
    for (opcao = menu(); opcao != 'S'; opcao = menu()) {
        switch (opcao) {
        case 'P':
        	printf("\t\t%d\t\t", tamanho);
        	printf("Digite um nome para ser lido na String");
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
             
            break;
        case 'B':
            /* Usar função:
             * - solicitar um inteiro de 0 a qtd-1
             * - ir, por fseek, direto na posição do arquivo onde está este funcionário
             * - imprimir os seus dados
             * - Voltar a este menu
             * */
            break;
        case 'A':
            /* UNICA OPÇÃO QUE ESCREVE NO ARQUIVO 
             * O arquivo está SEMPRE ABERTO 
             * Usar função: 
             * - ler o indice de 0 a qtd-1
             * - Usar a mesma função 'B' para obter e inmprimir os dados do funcionário
             * - Ler em uma variável novos dados para este funcionário
             * - Atualizar na posição correta os dados deste funcionário
             * (não vale fazer em outro arquivo, PRECISA ir na posição do arquivo
             * onde ele está e salvar em cima)
             * */
            break;
        case 'S':
            /* Fechar arquivo binário, encerrar programa */
            break;
        }
        pausa();
    }
}
