/*
 * TITULO: Arquivo para testes do T26
 * DATA: 14/Novembro/2017
 * 
*/

#include <stdio.h>
#include <stdlib.h>

#define STRMAX 	100

struct FUNC {
    char nome[STRMAX + 1];
    char endereco[STRMAX+1];
    int reg;
    double sal;
    char top;
};

/* Mesmo listagem do T23 */
int listagem(struct FUNC f[], int qtd)
{
    int i;
    for (i = 0; i < qtd; i++) {
        printf("%06d %s, %s, R$ %.2lf\n", f[i].reg, f[i].nome, f[i].endereco ? f[i].endereco : "-",
               f[i].sal);
    }
}


int main(int argc, char *argv[])
{
    struct FUNC *f;
    int qtd, ret, tam;
    int bytesNeed;
	FILE *arqbin;
	
	if (argc != 2){
		fprintf(stderr, "ERRO. Preciso receber o nome do arquivo binário\n");
		fprintf(stderr, "Exemplo: %s lixo.bin <ENTER>\n", argv[0]);
		return(1);
	}
	arqbin = fopen(argv[1], "rb");
	if (arqbin==NULL){
		fprintf(stderr, "ERRO. Não pude abrir %s para leitura\n", argv[1]);
		return(2);
	}
	/* Pegando o tamanho do arquivo APENAS para detectar problemas
	 * de tamanhos diferentes de estruturas 
	 * */
	fseek(arqbin, 0, SEEK_END);
	tam = ftell(arqbin);
	fseek(arqbin, 0, SEEK_SET);
	
	/* Le a quantidade */
	ret = fread(&qtd, sizeof(int), 1, arqbin);
	if (ret==0){
		fprintf(stderr, "ERRO. não consegui ler a quantidade\n");
		return(3);
	}
	
	/* Calcula o tamanho, em bytes, que o arquvio binário DEVE TER.
	 * Se ele tem a quantidade no início (um int) e depois os dados
	 * dos funcionários, ele deve ter o tamanho deste int (4?) + o tamanho
	 * total dos dados.
	 * 
	 * Coloquei isto para verificar erros de estruturas. Pode ser que o 
	 * arquivo binário tenha sido criado, por exemplo, com nome tendo
	 * 200 cars. Ai ele tem mais espaço para nome. Não pode.
	 * 
	 * Para arquivos binários funcionarem, todos devem usar a mesma estrutura
	 * e com o mesmo tamanho.
	 * 
	 * Se o arquivo binário foi salvo exatamente como é esta minha estrutura,
	 * então ele deve ter este tamanho: */
	bytesNeed = sizeof(int) + (qtd * sizeof(struct FUNC));
	
	if (tam != bytesNeed){
		fprintf(stderr, "ERRO formato do arquivo. O arquivo deveria ter %d bytes\n", bytesNeed);
		fprintf(stderr, "\tmas ele tem %d bytes de tamanho\n", tam);
		fprintf(stderr, "Verifique se o formato das estruturas é exatamente o mesmo\n");
		return(4);
	}
	
	f = (struct FUNC *) malloc(qtd * sizeof(struct FUNC));
	if (f == NULL){
		fprintf(stderr, "ERRO ao tentar alocar %d funcionários\n", qtd);
		return(5);
	}
	
	fread(f, sizeof(struct FUNC), qtd, arqbin);
	fclose(arqbin);
	
	printf("Foram lidos %d funcionários de %s:\n", qtd, argv[1]);
	listagem(f, qtd);
	
	free(f);
    return (0);
}
