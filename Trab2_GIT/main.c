/*
 
 IMPLEMENTAÇÃO DA ÁRVORE RUBRO-NEGRA
 AED II - PROF. EDSON NASCIMENTO
 
 CAIO ARTHUR SALES TELLES                 21453444
 STANRLEY DA CONCEIÇÃO PINHEIRO           XXXXXXXX
 
 
            **************************************
 */




#include <stdio.h>
#include <stdlib.h>

#define PRETO 0
#define VERMELHO 1
#define TRUE 4
#define FALSE 5

//----------------------------------> Definição da estrutura de um nó da árvore

typedef struct no{
    struct no *esquerdo;
    struct no *direito;
    struct no *pai;
    int chave;
    int cor;
}TipoNo;


//----------------------------------> Variáveis globais

TipoNo *nil, *auxFather;
int count, Opcoes;

TipoNo *ProcuraNo(TipoNo *raiz, int elemento);

//----------------------------------> Criação e alocação do nó

TipoNo *CriarNo(int elemento){
    TipoNo *novo = (TipoNo*)malloc(sizeof(TipoNo));
    if(novo == nil){
        printf("Erro de alocacao");
        return nil;
    }
    novo->pai = nil;
    novo->esquerdo = nil;
    novo->direito = nil;
    novo->chave = elemento;
    novo->cor = VERMELHO;
    return novo;
}


//----------------------------------> ROtações

TipoNo *RotacaoEsquerda(TipoNo *raiz, TipoNo *No_A){
    TipoNo *No_B = No_A->direito;
    No_A->direito = No_B->esquerdo;
    if(No_B->esquerdo != nil)
        No_B->esquerdo->pai = No_A;
    No_B->pai = No_A->pai;
    if(No_A->pai == nil)
        raiz = No_B;
    else{
        if(No_A == No_A->pai->esquerdo)
            No_A->pai->esquerdo = No_B;
        else
            No_A->pai->direito = No_B;
    }
    No_B->esquerdo = No_A;
    No_A->pai = No_B;
    return raiz;
}
TipoNo *RotacaoDireita(TipoNo *raiz, TipoNo *No_A){
    TipoNo *No_B = No_A->esquerdo;
    No_A->esquerdo = No_B->direito;
    if(No_B->direito != nil)
        No_B->direito->pai = No_A;
    No_B->pai = No_A->pai;
    if(No_A->pai == nil)
        raiz = No_B;
    else{
        if(No_A == No_A->pai->direito)
            No_A->pai->direito = No_B;
        else
            No_A->pai->esquerdo = No_B;
    }
    No_B->direito = No_A;
    No_A->pai = No_B;
    return raiz;
}






//----------------------------------> Inserção e "Balanceamento" das cores

int compara(int key1, int key2)
{
    if (key1 == key2)
        return 0;
    
    else if (key2 < key1)
        return -1;
    
    else
        return 1;
        
}

int eVermelho(TipoNo *node)
{
    if (node != nil && node->cor == VERMELHO)
        return TRUE;
    else
        return FALSE;
}


int eFilhoEsquerdo(TipoNo *node)
{
    if (node == node->pai->esquerdo)
        return TRUE;
    else
        return FALSE;
}

void raizNegra(TipoNo *root)
{
    if (root)
        root->cor = PRETO;
}

TipoNo *insere(TipoNo *root, TipoNo *node)
{
    int aux;
    
    if (root == nil)
    {
        node->pai = auxFather;
        return node;
    }
    else
    {
        aux = compara(root->chave, node->chave);
        
        if (aux ==  0)
            printf("\nNó já se encontra na árvore!\n\n");
        
        else if (aux < 0)
        {
            auxFather = root;
            root->esquerdo = insere(root->esquerdo, node);
        }
        else
        {
            auxFather = root;
            root->direito = insere(root->direito, node);
        }
        
    }
    
    return root;
}


//-------> Tratamento dos casos na Inserção


void caso_1(TipoNo *node, TipoNo *nodeAux)
{
    node->pai->cor = PRETO;
    nodeAux->cor = PRETO;
    node->pai->pai->cor = VERMELHO;
    node = node->pai->pai;
}

void case_2(TipoNo *root, TipoNo *node)
{
    node->pai->cor = PRETO;
    node->pai->pai->cor = VERMELHO;
    if (eFilhoEsquerdo(node->pai) == TRUE)
        root = RotacaoDireita(root, node->pai->pai);
    else
        root = RotacaoEsquerda(root, node->pai->pai);
}

void caso_3(TipoNo *root, TipoNo *node)
{
    node= node->pai;
    if (eFilhoEsquerdo(node) == FALSE)
        root = RotacaoEsquerda(root, node);
    else
        root = RotacaoDireita(root, node);
}

void caso_4(TipoNo *node, TipoNo *nodeAux)    //caso 4 igual caso 1
{
    node->pai->cor = PRETO;
    nodeAux->cor = PRETO;
    node->pai->pai->cor = VERMELHO;
    node = node->pai->pai;
}

void caso_5(TipoNo *root, TipoNo *node)
{
    node->pai->cor = PRETO;
    node->pai->pai->cor = VERMELHO;
    root = RotacaoEsquerda(root, node->pai->pai);
}

void caso_6(TipoNo *root, TipoNo *node)
{
    node = node->pai;
    root = RotacaoDireita(root, node);
}


TipoNo *insere_RN(TipoNo *root, int value)
{
    root = insere(root, CriarNo(value));
    raizNegra(root);
    
    TipoNo *auxiliar;
    TipoNo *node = ProcuraNo(root, value);
    
    if (node->pai != nil && eVermelho(node->pai) == TRUE)
    {
        if (eFilhoEsquerdo(node->pai) == TRUE)
        {
            auxiliar = node->pai->pai->direito;
            
            if (auxiliar != nil && eVermelho(auxiliar) == TRUE)
            {
                node->pai->cor = PRETO;
                auxiliar->cor = PRETO;
                node->pai->pai->cor = VERMELHO;
                node = node->pai->pai;
            }
            else
            {
                if (eFilhoEsquerdo(node) == FALSE)
                {
                    node= node->pai;
                    root = RotacaoEsquerda(root, node);
                }
                node->pai->cor = PRETO;
                node->pai->pai->cor = VERMELHO;
                root = RotacaoDireita(root, node->pai->pai);
            }
        }
        else
        {
            auxiliar = node->pai->pai->esquerdo;
            
            if (auxiliar != nil && eVermelho(auxiliar) == TRUE)
            {
                node->pai->cor = PRETO;
                auxiliar->cor = PRETO;
                node->pai->pai->cor = VERMELHO;
                node = node->pai->pai;
            }
            else
            {
                if (eFilhoEsquerdo(node) == TRUE)
                {
                    node = node->pai;
                    root = RotacaoDireita(root, node);
                }
                node->pai->cor = PRETO;
                node->pai->pai->cor = VERMELHO;
                root = RotacaoEsquerda(root, node->pai->pai);
            }
        }
    }
    
    return root;
}


//----------------------------------> Percorrimento na árvorem nas três maneiras

void PreOrdem(TipoNo *raiz){
    if(raiz == nil)
        return;
    printf("Chave = %.2d", raiz->chave);
    if(raiz->cor == 0)
        printf("\tPRETO\n");
    else
        printf("\tVERMELHO\n");
    
    PreOrdem(raiz->esquerdo);
    PreOrdem(raiz->direito);
}
void Ordem(TipoNo *raiz){
    if(raiz == nil)
        return;
    Ordem(raiz->esquerdo);
    printf("Chave = %.2d", raiz->chave);
    if(raiz->cor == 0)
        printf("\tPRETO\n");
    else
        printf("\tVERMELHO\n");
    Ordem(raiz->direito);
}
void PosOrdem(TipoNo *raiz){
    if(raiz == nil)
        return;
    PosOrdem(raiz->esquerdo);
    PosOrdem(raiz->direito);
    printf("Chave = %.2d", raiz->chave);
    if(raiz->cor == 0)
        printf("\tPRETO\n");
    else
        printf("\tVERMELHO\n");
}






//----------------------------------> Acessar o Menor dos maiores de um nó

TipoNo *MenorDosMaiores(TipoNo *raiz){
    TipoNo *aux = raiz->direito;
    while(aux->esquerdo != nil)
        aux = aux->esquerdo;
    return aux;
}






//----------------------------------> Remoção

TipoNo *RemoverNaArvore(TipoNo *raiz, TipoNo *No){
    TipoNo *aux;
    
    while(No != raiz && No->cor == PRETO){
        if(No == No->pai->esquerdo){
            aux = No->pai->direito;
            if(aux->cor == VERMELHO){ //CASO 1
                aux->cor = PRETO;
                No->pai->cor = VERMELHO;
                raiz = RotacaoEsquerda(raiz, No->pai);
                aux = No->pai->direito;
            }
            if(aux->esquerdo->cor == PRETO && aux->direito->cor == PRETO){//CASO 2
                aux->cor = VERMELHO;
                No = No->pai;
            }
            else{
                if(aux->direito->cor == PRETO){ //CASO 3
                    aux->esquerdo->cor = PRETO;
                    aux->cor = VERMELHO;
                    raiz = RotacaoDireita(raiz, aux);
                    aux = No->pai->direito;
                }
                aux->cor = No->pai->cor; //CASO 4
                No->pai->cor = PRETO;
                aux->direito->cor = PRETO;
                raiz = RotacaoEsquerda(raiz, No->pai);
                No = raiz;
            }
        }
        else{
            aux = No->pai->esquerdo;
            if(aux->cor == VERMELHO){
                aux->cor = PRETO;
                No->pai->cor = VERMELHO;
                raiz = RotacaoDireita(raiz, No->pai);
                aux = No->pai->esquerdo;
            }
            if(aux->direito->cor == PRETO && aux->esquerdo->cor == PRETO){
                aux->cor = VERMELHO;
                No = No->pai;
            }
            else{
                if(aux->esquerdo->cor == PRETO){
                    aux->direito->cor = PRETO;
                    aux->cor = VERMELHO;
                    raiz = RotacaoEsquerda(raiz, aux);
                    aux = No->pai->esquerdo;
                }
                aux->cor = No->pai->cor;
                No->pai->cor = PRETO;
                aux->esquerdo->cor = PRETO;
                raiz = RotacaoDireita(raiz, No->pai);
                No = raiz;
            }
        }
    }
    No->cor = PRETO;
    return raiz;
}
TipoNo *ProcuraNo(TipoNo *raiz, int elemento){
    TipoNo *aux = raiz;
    while(aux != nil){
        if(elemento < aux->chave)
            aux = aux->esquerdo;
        else if (elemento > aux->chave)
            aux = aux->direito;
        else
            return aux;
    }
    return NULL;
}
TipoNo *RemoverNo(TipoNo *raiz, int elemento) {
    TipoNo *No = ProcuraNo(raiz, elemento);
    if(No == NULL){
        printf("Noh nao se encontra na Arvore!\n\n");
        return raiz;
    }
    TipoNo *aux1;
    TipoNo *aux2;
    if(No->esquerdo == nil || No->direito == nil)
        aux1 = No;
    else
        aux1 = MenorDosMaiores(No);
    
    if(aux1->esquerdo != nil)
        aux2 = aux1->esquerdo;
    else
        aux2 = aux1->direito;
    
    aux2->pai = aux1->pai;
    if(aux1->pai == nil)
        raiz = aux2;
    else{
        if(aux1 == aux1->pai->esquerdo)
            aux1->pai->esquerdo = aux2;
        else
            aux1->pai->direito = aux2;
    }
    
    if(aux1 != No)
        No->chave = aux1->chave;
    if(aux1->cor == PRETO)
        raiz = RemoverNaArvore(raiz, aux2);
    
    return raiz;
}





//----------------------------------> Funções de execução das funções do código

void Inserir(TipoNo **raiz){
    int elemento;
    
    printf("Numero a ser inserido: ");
    scanf("%d", &elemento);
    printf("\n\n");
    
    *raiz = insere_RN(*raiz, elemento);
    raizNegra(*raiz);
}
void Remover(TipoNo **raiz){
    int elemento;
    
    printf("Numero a ser removido: ");
    scanf("%d", &elemento);
    printf("\n\n");
    
    *raiz = RemoverNo(*raiz, elemento);
}
void Procura(TipoNo *raiz){
    int elemento;
    
    printf("Numero a ser procurado: ");
    scanf("%d", &elemento);
    printf("\n\n");
    
    TipoNo *No = ProcuraNo(raiz, elemento);
    if(No == NULL)
        printf("Noh nao encontrado\n");
    else
        printf("Noh %d se encontra na arvore!!!\n",No->chave);
}





//----------------------------------> Impressão

void addEspaco(int altura){
    int i = 0;
    
    while(i < altura){
        if( i == altura - 1)
            printf("|___");
        else
            printf("    ");
        i++;
    }
}
void addnullNovo(){
    printf("NULL\n");
}
int eIgual(TipoNo *p, TipoNo *q){
    if (p == NULL && q == NULL)
        return TRUE;
    else if (p->chave == q->chave)
        return TRUE;
    else
        return FALSE;
}
int recebeAltura(TipoNo *treep, TipoNo *p){
    if(treep == nil || p == nil)
        return 0;
    if(eIgual(treep, p) == TRUE)
        return 0;
    else if(treep->chave > p->chave)
        return recebeAltura(treep->esquerdo, p) + 1;
    else
        return recebeAltura(treep->direito, p) + 1;
}
void Imprime(TipoNo *p, TipoNo *treep, int altura){
    if(treep == nil)
        return;
    if(p == nil){
        addEspaco(altura + 1);
        addnullNovo();
        return;
    }
    altura = recebeAltura(treep, p);
    addEspaco(altura);
    if (p->cor == PRETO)
        printf("%i - %s\n", p->chave, "B");
    else
        printf("%d - %s\n", p->chave, "R");
    
    Imprime(p->direito, treep, altura);
    Imprime(p->esquerdo, treep, altura);
}





//----------------------------------> Menu de seleção

int Menu(void){
    int opcao;
    printf("Inserir na arvore\t- 1\nRemover Valor\t\t- 2\nExibir\t\t\t- 3\nBuscar Valor\t\t- 4\nSair\t\t\t- 0\n\nOpcao: ");
    scanf("%d", &opcao);
    return opcao;
}
void SelecionarOpcao(TipoNo **raiz,int value){
    while(value != 0){
        if(value == 1){
            system("cls");
            Inserir(raiz);
        }
        else if(value == 2){
            system("cls");
            Remover(raiz);
            printf(".\n\n");
        }
        else if(value == 3){
            system("cls");
            if((*raiz) == nil)
                printf("Arvore vazia!!!\n\n");
            else{
                Imprime(*raiz, *raiz, -1);
                printf("\n\n");
            }
        }
        else if(value == 4){
            Procura(*raiz);
            printf(".\n\n");
        }
        printf("Inserir na arvore\t- 1\nRemover Valor\t\t- 2\nExibir\t\t\t- 3\nBuscar Valor\t\t- 4\nSair\t\t\t- 0\n\nOpcao: ");
        scanf("%d", &value);
    }
}




//----------------------------------> Função principal (main)

int main(){
    nil = (TipoNo*)malloc(sizeof(TipoNo));
    auxFather = nil;
    TipoNo *raiz = nil;
    Opcoes = Menu();
    SelecionarOpcao(&raiz,Opcoes);
    system("cls");
    printf("\tPrograma Finalizado\n");
    return 0;
}
