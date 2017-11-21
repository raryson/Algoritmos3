/*
 * TITULO: Resposta do Exercício T25
 * DATA: 14/Novembro/2017
 * 
*/

#include <stdio.h>
#include <stdlib.h>

#define STRMAX 	100

/* T21 com suporte a arquivos BINÁRIOS
 * 
 * A mudança é tão pouca, mas tão pouca, que foi colocado tags
 * indicando onde houveram mudanças. Observe as marcações T25
 */

/* NOVO NO T25.
 * Um define para o nome do arquivo, só para ficar legal 
 * */
#define NOMEARQBIN "dados.bin"
/* FIM DO NOVO */

struct FUNC {
    char nome[STRMAX + 1];
    char endereco[STRMAX+1];
    int reg;
    double sal;
    char top;
};

/* Da resposta do T14 
 * Função que converte a string s para letras maiúsculas */
int maiusculas(char s[])
{
    int i;

    for (i = 0; s[i]; i++) {
        if ((s[i] >= 'a') && (s[i] <= 'z')) {
            s[i] = s[i] - 32;
        }
    }
    /* Ao olhar a tabela ascii percebe-se que o 'A'==65 e o 'a'==97
     * A dirença entre um caractere minúsculo e o mesmo em maiúsculo
     * é de 32. Converter então basta diminuir 32 (claro, desde que
     * se tenha certeza de que é uma letra minúscula, por isto o
     * if) */
    return (i);                 // retorna o tamanho (strlen) de s
}


/* Adaptado para ler de qualquer lugar */
int lestring(char s[], int max, FILE * onde)
{
    int i = 0;
    char letra;

    for (i = 0; i < (max - 1); i++) {
        letra = fgetc(onde);
        /* Pulando o ENTER. O car 13 só é final de linha em textos
         * padrão DOS (e o DOS tem também o 10)*/
        if (letra == 13) {
            i--;
            continue;
        }
        /* Texto DOS e LINUX tem 10 no final de linha (LINE FEED) */
        if ((letra == 10) && (i == 0)) {
            i = i - 1;
            continue;
        }
        if (letra == 10) {
            break;
        }
        s[i] = letra;
    }
    s[i] = 0;
    return (i);
}

/* Porque nós não programamos mais para cusar buffer overflow */
int copiaSeguro(char d[], int max, char o[])
{
    int i;

    for (i = 0; o[i]; i++) {
        if (i >= max)
            break;
        d[i] = o[i];
    }
    d[i] = 0;
    return (i);
}


/* imprime os dados do vetor em um arquivo TEXTO */
int salvaArqTXT(struct FUNC f[], int qtd, FILE * onde)
{
    int i;

    fprintf(onde, "%d\n", qtd);

    for (i = 0; i < qtd; i++) {
        fprintf(onde, "%s\n", f[i].nome);
        fprintf(onde, "%s\n", f[i].endereco);
        fprintf(onde, "%d\n", f[i].reg);
        fprintf(onde, "%lf\n", f[i].sal);
    }
}

/* Adaptado para ler de qualquer lugar */
double lefunc(struct FUNC f[], int qtd, int maxstr, FILE * onde)
{
    int i;
    double tot = 0;
    int tam;

    if (onde == stdin) {
        printf("# Digite os dados para %d funcionários\n", qtd);
    }

    for (i = 0; i < qtd; i++) {
        if (onde == stdin) {
            printf("\n# --- func [%d] ---\n", i);
            printf("# Nome do funcionario:\n");
        }
        lestring(f[i].nome, maxstr, onde);
        maiusculas(f[i].nome);

        if (onde == stdin)
            printf("\n# Endereço:\n");
        
        lestring(f[i].endereco, maxstr, onde);
        
        if (onde == stdin)
            printf("\n# Número do registro:\n");
        while (fscanf(onde, "%d", &f[i].reg) == 0) {
            printf("ERRO entrada invalida\n");
            printf("# ERRO. Digitou lixo\n");
            while (fgetc(onde) != '\n');
            printf("\n# Número do registro:\n");
        }

        if (onde == stdin)
            printf("\n# Valor do salário, em reais:\n");
        while (fscanf(onde, "%lf", &f[i].sal) == 0) {
            printf("ERRO entrada invalida\n");
            printf("# ERRO. Digitou lixo\n");
            while (fgetc(onde) != '\n');
            if (onde == stdin)
                printf("\n# Valor do salário, em reais:\n");
        }
        tot += f[i].sal;
    }
    return (tot);
}

int tamanho(char s[])
{
    int i = 0;
    for (i = 0; s[i]; i++);
    return (i);
}


/* Usado função de ordenamento para ordenar o vetor pelo nome do 
 * funcionário. No T13 eu publiquei uma função quase genérica para ordenar
 * números inteiros. Defendi que qualquer função de ordenamento se resume
 * em apenas duas etapas:
 *  a) comparar coisas
 *  b) trocar de lugar
 * 
 * Então eu, lá na solução do T13, publiquei uma função que ordenava inteiros
 * separando em uma outra função a parte da comparação. Isso fez com que a
 * mesma função pudesse ser usada para ordenar por qualquer critério.
 * 
 * RESSUSCITEI a função aqui, adaptando-a para estruturas
 * */


/* Pede para ordenar pelo nome. Então preciso de um strcmp */
/* Função equivalente ao strcmp que não pode usar */
int comparaSTR(char s1[], char s2[])
{
    int i;

    for (i = 0; s1[i]; i++) {
        if (s1[i] != s2[i]) {
            break;
        }
    }
    return (s1[i] - s2[i]);
}

/* Função que compara e diz para a ordena se eram iguais ou não */
int compara(struct FUNC n1, struct FUNC n2)
{
    return (comparaSTR(n1.nome, n2.nome));
}

/* Ordenamento pela técnica conhecida como select sort
 * Adaptado da resposta do T13.
 * 
 * Pegue a resposta do T13 e veja como foram mínimas as adapatações.
 * Reaproveitamento de código, AGORA, lhe parece mais tentador?
 * 
 *  */
int ordena(struct FUNC v[], int n)
{
    int i, j, menor;
    struct FUNC temp;
    /* Precisei aqui criar um temp para atuar na troca de posições.
     * Já tinha isso no T13, só que lá foi reaproveitado o j para
     * isto
     * */

    for (i = 0; i < n; i++) {
        menor = i;
        for (j = i + 1; j < n; j++) {
            if (compara(v[j], v[menor]) < 0) {
                menor = j;      // novo menor eleito
            }
        }
        if (menor != i) {
            temp = v[menor];
            v[menor] = v[i];
            v[i] = temp;
        }
    }
    return (i);
}

/* Agora que você viu parece fácil, não? */


int listagem(struct FUNC f[], int qtd)
{
    int i;
    for (i = 0; i < qtd; i++) {
        printf("%06d %s, %s, R$ %.2lf\n", f[i].reg, f[i].nome, f[i].endereco ? f[i].endereco : "-",
               f[i].sal);
    }
}

/* Para imprimir os top10 eu poderia ordenar novamente, mas agora ordenando
 * por salário. teria que criar um ordena2, igual ao ordena, mas usando uma
 * outra função de comparação.
 * 
 * Mas preferi colocar em prática uma ideia que passei para alunos que me 
 * perguntaram: encontrar o maior salário de todos e imprimir. Marcar ele para 
 * não imprimir novamente. Repetir 10x. Criei um campo chamado top na estrutura
 * só para isso.
 * 
 * Se top=0, então este salário não foi ainda impresso como maior
 * Se top=1, então ele foi
 * */
int top10(struct FUNC f[], int qtd)
{
    int i, j;
    int ind_maior;              // indice do maior salário encontrado

    for (i = 0; i < qtd; i++) {
        f[i].top = 0;
    }

    for (i = 0; i < 10; i++) {
        if (i >= qtd)
            break;

        ind_maior = -1;
        for (j = 0; j < qtd; j++) {
            if (f[j].top)
                continue;
            if (ind_maior == -1) {
                ind_maior = j;
                continue;
            }

            if (f[j].sal > f[ind_maior].sal) {
                ind_maior = j;
            }
        }
        f[ind_maior].top = 1;

        printf("R$ %10.2lf %s\n", f[ind_maior].sal, f[ind_maior].nome);
    }
}

int main(int argc, char *argv[])
{
    struct FUNC *f;
    int qtd, i, qtdbin;
    double totsal;
    FILE *leitura, *escrita;
	FILE *arqbin;
	

/* NOVO NO T25 */
	qtdbin=0;
	/* Para não mudar muito o código do T23, achei melhor ter duas variáveis
	 * para quantidades. Esta, qtdbin, é apenas para o que tem no arquivo
	 * binário
	 * */
	arqbin = fopen(NOMEARQBIN, "rb");
	if (arqbin){
		/* Se abriu, lê quantidade que tem no arquivo binário */
		fread(&qtdbin, sizeof(int), 1, arqbin);
		printf("# Arquivo %s tem %d funcionarios\n", NOMEARQBIN, qtdbin);
	}
/* FIM DO NOVO */
		
    qtd = 0;

    /* Olha a facilidade! Se não conseguir ler, leitura fica sendo
     * teclado. Assim uso a mesma função 
     * */
    leitura = stdin;
    escrita = NULL;
    f = NULL;

    if (argc == 3) {
        leitura = fopen(argv[1], "r");
        if (leitura) {
            fscanf(leitura, "%d", &qtd);
            printf("# SUCESSO ao abrir %s\n", argv[1]);
            escrita = fopen(argv[2], "w");
            if (escrita == NULL) {
                fclose(leitura);
                leitura = stdin;
                qtd = 0;
                fprintf(stderr, "# ERRO. Não pude abrir %s para escrita\n", argv[1]);
                fprintf(stderr, "# Uso de arquivos ignorado\n");
            }
        } else {
            fprintf(stderr, "# ERRO. Não pude abrir %s para leitura\n", argv[1]);
            fprintf(stderr, "# Uso de arquivos ignorado\n");
            leitura = stdin;
        }
    }
    if ((argc == 2) || (argc > 3)) {
        fprintf(stderr, "# ERRO parametros\n");
        fprintf(stderr, "Você precisa passar dois nomes de arquivos. Uso de arquivos ignorado\n");
    }

    if (qtd > 0) {
		
		/* MUDOU EM RELAÇÃO AO T23 */
        f = (struct FUNC *) malloc( (qtd+qtdbin) * sizeof(struct FUNC));
        /* FIM DA MUDANÇA */
        
        if (f == NULL) {
            printf("ERRO alocação\n");
            printf("# ERRO: não foi possível alocar espaço para %d funcionários\n", qtd);
            printf("# Digite uma quantidade menor de funcionários\n");
            qtd = 0;
            /* se tem qtd é porque leu do arquivo. Se não pode alocar para
             * o que o arquivo diz ter, então não pode ler do arquivo.
             * Convergindo para leitura do teclado 
             * */
            fclose(leitura);
            fclose(escrita);
            leitura = stdin;
            escrita = NULL;
        }
    }
    
    /* Pode já ter lido qtd do arquivo, se houve arquivo aberto */
    while (qtd <= 0) {
        printf("# Quantos funcionários você quer cadastrar:\n");
        if (scanf("%d", &qtd) == 0) {
            printf("ERRO entrada invalida\n");
            printf("# ERRO. Digitou lixo\n");
            while (fgetc(stdin) != '\n');
            continue;
        }
        if (qtd <= 0) {
            printf("ERRO %d\n", qtd);
            printf("# ERRO. quantidade de funcionários deve ser maior que 1\n");
            continue;
        }
        
        /* MODOU EM RELACÃO AO T23 */
        f = (struct FUNC *) malloc( (qtd+qtdbin) * sizeof(struct FUNC));
        /* FIM DA MUDANÇA */
        
        if (f) {
            break;
        }
        printf("ERRO alocação\n");
        printf("# ERRO: não foi possível alocar espaço para %d funcionários\n", qtd);
        printf("# Digite uma quantidade menor de funcionários\n");
        qtd = 0;
    }

/*  NOVO NO T25 */
	if ((arqbin) && (qtdbin>0)){
		
		if (fread(f, sizeof(struct FUNC), qtdbin, arqbin)!=qtdbin){
			fprintf(stderr, "# ERRO. Não pude ler %d dados do binário\n", qtdbin);
			fprintf(stderr, "# ELE ESTÁ ERRADO. IGNORANDO\n");
			qtdbin = 0;
		}
		fclose(arqbin);
	} else {
		qtdbin=0;
	}
	
    totsal = lefunc(f+qtdbin, qtd, STRMAX, leitura);
    /* Ao passar o ponteiro f+qtdbin, tem-se que a leitura do teclado ou 
     * do arquivo TXT se dará após qtdbin posições do vetor */
     
     qtd = qtdbin+qtd;
     
/* FIM DO NOVO */

    if (leitura == stdin)
        printf("# ---- FIM DO CADASTRO DE %d FUNCIONARIOS ----\n", qtd);


    if (escrita) {
        salvaArqTXT(f, qtd, escrita);
    }

/* NOVO NO T25: salvar o arquivo BINÁRIO */
	arqbin = fopen (NOMEARQBIN, "wb");
	if (arqbin==NULL){
		fprintf(stderr, "# ERRO: nao pode abrir %s para escrita\n", NOMEARQBIN);
	} else {
		//i = 200;
		//fwrite(&i, sizeof(int), 1, arqbin);
		fwrite(&qtd, sizeof(int), 1, arqbin);
		
		fwrite(f, sizeof(struct FUNC), qtd, arqbin);
		fclose(arqbin);
	}
/* FIM DO NOVO NO T25 */

    printf("\n# LISTA DOS FUNCIONÁRIOS EM ORDEM ALFABÉTICA\n");
    ordena(f, qtd);
    listagem(f, qtd);

    printf("\n# LISTA DOS TOP 10 MAIORES SALARIOS, EM ORDEM DECRESCENTE\n");
    top10(f, qtd);

    printf("\n# TOTAL DA FOLHA\n");
    printf("R$ %.2lf\n", totsal);

    if (escrita) {
        printf("# %d FUNCIONARIOS ARMAZENADOS EM %s\n", qtd, argv[2]);
        fclose(escrita);
    }

    printf("\n# FIM\n");
    return (0);
}
