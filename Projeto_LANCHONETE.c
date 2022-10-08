#include<stdio.h>
#include<stdlib.h>

//Definição das estruturas
typedef struct{
	char descricaoProduto[50];
	int codigoProduto;
	float valorProduto;
} Produto;

typedef struct{
	char descricaoCliente[50];
	int codigoComanda;
	Produto produto;
} Comanda;

typedef struct no{
	Comanda c;
	struct no *proximo;
} No;

//Impressão dos dados do teclado na fila

void imprimirProduto(Produto produto){
	printf("\n\tPRODUTO\n");
	printf("\t\tDescricao do produto: %s", produto.descricaoProduto);
	printf("\t\tCodigo do produto: %d\n", produto.codigoProduto);
	printf("\t\tValor do produto: %.2f\n", produto.valorProduto);
	
}

void imprimirComanda(Comanda c){
	printf("\n\tNome do cliente: %s", c.descricaoCliente);
	printf("\tCodigo da comanda: %d\n", c.codigoComanda);
	imprimirProduto(c.produto);
}

//leitura dos dados do teclado na fila
Produto lerProduto(){
	Produto produto;
	printf("\nDescricao do produto: ");
	fgets(produto.descricaoProduto, 49, stdin);
	printf("\nCodigo do produto: ");
	scanf("%d", &produto.codigoProduto);
	printf("\nValor do produto: ");
	scanf("%f", &produto.valorProduto);
	getchar();
	
	return produto;
}

Comanda lerComanda(){
	Comanda c;
	printf("\nDigite o seu nome: ");
	fgets(c.descricaoCliente, 49, stdin);
	printf("\nDigite o codigo da comanda: ");
	scanf("%d", &c.codigoComanda);
	fflush (stdin);
	c.produto = lerProduto();
	
	return c;
}

//Inserir, remover e listar a fila
void inserir_na_fila(No **fila, Comanda comanda){
	No *aux, *novo = malloc(sizeof(No));
	if(novo){
		novo->c = comanda;
		novo->proximo = NULL;
		if(*fila == NULL)
		      *fila = novo;
	    else{
	    	aux = *fila;
	    	while(aux->proximo)
	    	    aux = aux->proximo;
	    	aux->proximo =novo;
		}
	}
	else
        printf("\nErro ao alocar memoria\n");
}

No* remover_da_fila(No **fila){
	No *remover = NULL;
	
	if(*fila){
		remover = *fila;
		*fila = remover->proximo;
	}
	else 
	    printf("\tFila vazia\n");
	
	return remover;
}

void imprimir(No *fila){
	printf("\t-------------FILA--------------\n\t");
	while(fila){
		imprimirComanda(fila->c);
		fila = fila->proximo;
		if(fila)
		    printf("\t------------------------------\n\t");
	}
	printf("\n\t-----------FIM FILA-------------\n");
}

//Produtos salvos em arquivo txt
int tam = 10;
Produto lista[10];
int quant = 0;

int cadastrarProduto(){
	if(quant<tam){
		Produto produto;
		scanf("%*c");
		printf("\nDigite a descricao do produto: ");
		fgets(produto.descricaoProduto, 50, stdin);
		printf("Digite o codigo do produto: ");
		scanf("%d", &produto.codigoProduto);
		printf("Digite o valor do produto: ");
		scanf("%f", &produto.valorProduto);
		lista[quant] = produto;
		quant ++;
		return 1;
	}
	else{
		printf("ERRO\n\n");
		return 0;
	}
}


void imprimirLista(){
	int i;
	for(i=0; i<quant; i++){
		printf("\nDescricao do produto: %s", lista[i].descricaoProduto);
		printf("\nCodigo do produto: %d", lista[i].codigoProduto);
		printf("\nValor do produto: %.2f\n\n", lista[i].valorProduto);
	}
}


void salvarEmArquivo(){
	FILE *arq = fopen("lista.txt", "w");
	int i;
	if(arq){
			fprintf(arq, "%d\n\n", quant);
		for(i = 0; i < quant; i++){
			fprintf(arq, "%s", lista[i].descricaoProduto);
			fprintf(arq, "%d\n", lista[i].codigoProduto);
			fprintf(arq, "%.2f\n\n", lista[i].valorProduto);
		}
		fclose(arq);
	}
	else
	    printf("ERRO: nao foi possivel abrir o arquivo\n\n");
}

void lerDoArquivo(){
	FILE *arq = fopen("lista.txt", "r");
	int i;
	if(arq){
		fscanf(arq, "%d\n", &quant);
		for(i = 0; i < quant; i++){
			Produto produto;
			fgets(produto.descricaoProduto, 50, arq);
			fscanf(arq, "%d\n", &produto.codigoProduto);
			fscanf(arq, "%f\n\n", &produto.valorProduto);
			lista[i] = produto;

		}
		fclose(arq);
	}
	else
	    printf("ERRO: nao foi possivel abrir o arquivo\n\n");
}

//Menu principal
int main(){
	No *r, *fila = NULL;
	Comanda c;
	int op;
	
	do{
		printf("\n\n===================================\n");
	    printf("|            LANCHONETE           |\n");
		printf("|---------------------------------|\n");
	    printf("| 1 - Cadastrar Produto           |\n");
	    printf("| 2 - Lista de Produtos           |\n");
	    printf("| 3 - Salvar Produto em arquivo   |\n");
	    printf("| 4 - Ler Produtos do arquivo     |\n");
	    printf("| 5 - Iniciar fila de Comandas    |\n");
	    printf("| 6 - Remover Comanda             |\n");
	    printf("| 7 - Listar Comandas             |\n");
	    printf("| 0 - Sair                        |\n");
	    printf("===================================\n");
		scanf("%d", &op);
		getchar();
		switch(op){
			case 0:
				printf("Thau\n\n");
				break;
			case 1:
				cadastrarProduto();
				break;
			case 2:
				imprimirLista();
				break;
			case 3:
				salvarEmArquivo();
				break;
			case 4:
				lerDoArquivo();
				break;
			case 5:
				c = lerComanda();
				inserir_na_fila(&fila, c);
				break;
			case 6:
				r = remover_da_fila(&fila);
				if(r){
					imprimirComanda(r->c);
					free(r);
				}          
				break;
			case 7:
				imprimir(fila);
				break;
			default:
				printf("Opcao invalida\n\n");
				
		}
	}while(op != 0);
}
