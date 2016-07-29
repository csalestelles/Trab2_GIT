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

TipoNo *nil;
int sideofNode, count, Opcoes;


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
    novo->cor = PRETO;
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

TipoNo *InserirNaArvore(TipoNo *raiz, TipoNo *novo){
    while(novo != raiz && novo->pai->cor == VERMELHO){
        if(novo->pai == novo->pai->pai->esquerdo){
            TipoNo *aux = novo->pai->pai->direito;
            if(aux->cor == VERMELHO){ //CASO 1
                novo->pai->cor = PRETO;
                aux->cor = PRETO;
                novo->pai->pai->cor = VERMELHO;
                novo = novo->pai->pai;
            }
            else{
                if(novo == novo->pai->direito){ //CASO 2
                    novo = novo->pai;
                    raiz = RotacaoEsquerda(raiz, novo);
                }
                novo->pai->cor = PRETO;   //CASO 3
                novo->pai->pai->cor = VERMELHO;
                raiz = RotacaoDireita(raiz, novo->pai->pai);
            }
        }
        else{
            if(novo->pai == novo->pai->pai->direito){
                TipoNo *aux = novo->pai->pai->esquerdo;
                if(aux->cor == VERMELHO){
                    novo->pai->cor = PRETO;
                    aux->cor = PRETO;
                    novo->pai->pai->cor = VERMELHO;
                    novo = novo->pai->pai;
                }
                else{
                    if(novo == novo->pai->esquerdo){
                        novo = novo->pai;
                        raiz = RotacaoDireita(raiz, novo);
                    }
                    novo->pai->cor = PRETO;
                    novo->pai->pai->cor = VERMELHO;
                    raiz = RotacaoEsquerda(raiz, novo->pai->pai);
                }
            }
        }
    }
    raiz->cor = PRETO;
    return raiz;
}
TipoNo *InserirNo(TipoNo *raiz, int elemento){
    TipoNo *novo = CriarNo(elemento);
    TipoNo *atual = nil;
    TipoNo *aux = raiz;
    if(raiz == nil){
        raiz = CriarNo(novo->chave);
        raiz->cor = PRETO;
        return raiz;
    }
    while(aux != nil){
        atual = aux;
        if(novo->chave < aux->chave)
            aux = aux->esquerdo;
        else if(novo->chave > aux->chave)
            aux = aux->direito;
        else{
            printf("O elemento %d ja existe na Arvore!!!\n\n",novo->chave);
            return raiz;
        }
    }
    novo->pai = atual;
    if(atual == nil)
        raiz = novo;
    else if(novo->chave < atual->chave)
        atual->esquerdo = novo;
    else
        atual->direito = novo;
    
    novo->esquerdo = nil;
    novo->direito = nil;
    novo->cor = VERMELHO;
    
    raiz = InserirNaArvore(raiz, novo);
    return raiz;
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
        else if (elemento == aux->chave)
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
    
    *raiz = InserirNo(*raiz, elemento);
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
    if(isequal(treep, p) == TRUE)
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
    TipoNo *raiz = nil;
    Opcoes = Menu();
    SelecionarOpcao(&raiz,Opcoes);
    system("cls");
    printf("\tPrograma Finalizado\n");
    return 0;
}
