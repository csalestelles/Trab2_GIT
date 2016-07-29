//
//  main.c
//  Trab2_GIT
//
//  Created by Caio Arthur on 7/28/16.
//  Copyright © 2016 Caio Arthur. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define BLACK 0
#define RED 1

#define LEFT 2
#define RIGHT 3

#define TRUE 4
#define FALSE 5

struct noh
{
    int key;
    struct noh *father;
    struct noh *left;
    struct noh *right;
    int color;
};
typedef struct noh rnTree;

rnTree *nil, *mainRoot;
rnTree *insertNode(rnTree *root, int value), *removeNode(rnTree *root, int value);
int sideofNode, count, selectedOption;

rnTree *createNewNode(int value)
{
    
    rnTree *newNode = (rnTree*)malloc(sizeof(rnTree));
    
    if(newNode == NULL)
    {
        printf("Erro de alocacao");
        
        return nil;
    }
    
    newNode->father = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->key = value;
    newNode->color = BLACK;
    
    return newNode;
}

/* ---------------------------------------------------------------------------------------->
 *
 *                                                                                         MINHA__FUNÇÕES
 *  --------------------------------------------------------------------------------------->
 */

int color(rnTree *node)
{
    if (node == NULL)
        return BLACK;
    else
        return node->color;
}

void switchColor(rnTree *node)
{
    if (node->color == BLACK)
        node->color = RED;
    else
        node->color = BLACK;
}

rnTree *acessBrother(rnTree *root)
{
    if (root->father->left == root)
        
        sideofNode = RIGHT;
    return root->father->right;
    
    sideofNode = LEFT;
    return root->father->left;
}

int sideOfNode(rnTree *root)
{
    if (root->father->left == root)
    {
        return LEFT;
    }
    return RIGHT;
}

/* ------------------------------------------------------------>
 *
 *                                                                  IMPRESSÃO
 *  ----------------------------------------------------------->
 */


void addspacenew (int depth) {
    int i = 0;
    
    while (i < depth)
    {
        if ( i == depth - 1)
            printf("|___");
        else
            printf("    ");
        i++;
    }
}

void addnullnew ()
{
    printf("NULL\n");
}


int isequal(rnTree *p, rnTree *q)
{
    if (p == NULL && q == NULL)
        return TRUE;
    else if (p->key == q->key)
        return TRUE;
    else
        return FALSE;
}

int getdepth (rnTree *treep, rnTree *p)
{
    if (treep == NULL || p == NULL)
        return 0;
    
    if (isequal(treep, p) == TRUE)
        return 0;
    
    else if (treep->key > p->key)
        return getdepth(treep->left, p) + 1;
    else
        return getdepth(treep->right, p) + 1;
}

void printlevelordernew(rnTree *p, rnTree *treep, int depth)
{
    if (treep == NULL)
        return;
    
    if (p == NULL)
    {
        addspacenew(depth + 1);
        addnullnew();
        return;
    }
    
    depth = getdepth(treep, p);
    
    addspacenew(depth);
    
    if (p->color == BLACK)
        printf("%i - %s\n", p->key, "B");
    else
        printf("%d - %s\n", p->key, "R");
    
    printlevelordernew(p->right, treep, depth);
    printlevelordernew(p->left, treep, depth);
}


/* ------------------------------------------------------------>
 *
 *                                                                  MENU
 *  ----------------------------------------------------------->
 */

int Menu(void)
{
    int option;
    
    printf("\nInserir na árvore             - 1\nRemover Valor                 - 2\nExibir                        - 3\nBuscar Valor                  - 4\nExibir altura da árvore       - 5\nNúmero de elementos na árvore - 6\nSair                          - 0\n\nOpção: ");
    scanf("%d", &option);
    return option;
}

void inserting()
{
    int valuetoBeInserted;
    
    printf("\nNúmero à ser inserido: ");
    scanf("%d", &valuetoBeInserted);
    printf("\n\n\n");
    
    mainRoot = insertNode(mainRoot, valuetoBeInserted);
}

void delete()
{
    int valuetoBeDeleted;
    
    printf("\nNúmero à ser removido: ");
    scanf("%d", &valuetoBeDeleted);
    printf("\n\n\n");
    
    mainRoot = removeNode(mainRoot, valuetoBeDeleted);
}

void findValue(rnTree *root, int value)
{
    if (!root)
        printf("\n Valor não está na árvore!\n");
    
    else if (root->key == value)
        printf("\nO valor %d está na árvore!\n", value);
    else if (root->key > value)
        findValue(root->left, value);
    
    else
        findValue(root->right, value);
}

void search()
{
    int valuetoBeSearched;
    
    printf("\nBuscar Valor: ");
    scanf("%d", &valuetoBeSearched);
    printf("\n\n\n");
    
    findValue(mainRoot, valuetoBeSearched);
    
}

int heightOfTree(rnTree *root)
{
    int leftHeight, rightHeight;
    
    if (!root)
    {
        return -1;
    }
    else
    {
        leftHeight = heightOfTree(root->left);
        rightHeight = heightOfTree(root->right);
        
        if (leftHeight > rightHeight)
        {
            return leftHeight + 1;
        }
        else
        {
            return rightHeight + 1;
        }
    }
}

void height()
{
    int valueOfHeight = heightOfTree(mainRoot);
    
    printf("\n\nA árvore tem altura igual à :   %d\n\n", valueOfHeight);
}


int numberOfElements(rnTree *root)
{
    if (root != NULL)
    {
        count++;
        numberOfElements(root->left);
        numberOfElements(root->right);
    }
    return count;
}

int setNumberOfElements(rnTree *root)
{
    int number;
    number = numberOfElements(root);
    count = 0;
    
    return number;
}


void selectOption(int value)
{
    if (value == 1)
    {
        inserting();
        return;
    }
    else if (value == 2)
    {
        delete();
        printf(".\n\n");
        
    }
    else if (value == 3)
    {
        printlevelordernew(mainRoot, mainRoot, -1);
        printf(".\n\n");
        
    }
    else if (value == 4)
    {
        search();
        printf(".\n\n");
        
    }
    else if (value == 5)
    {
        height();
        printf(".\n\n");
        
    }
    else if (value == 6)
    {
        printf("\n\nExiste(m) %d elemento(s) na árvore!\n\n\n", numberOfElements(mainRoot));
        return;
    }
    else if (value == 0)
    {
        exit(0);
    }
    else
    {
        return;
    }
}



/* ---------------------------------------------------------------------------------------->
 *
 *                                                                             MINHAS__FUNÇÕES__________FIM
 *  --------------------------------------------------------------------------------------->
 */




rnTree *leftRotation(rnTree *root, rnTree *node)
{
    rnTree *auxiliar = node->right;
    node->right = auxiliar->left;
    
    if(auxiliar->left!= NULL)
        auxiliar->left->father = node;
    auxiliar->father = node->father;
    
    if(node->father == NULL)
        root = auxiliar;
    else
    {
        if(node == node->father->left)
            node->father->left = auxiliar;
        else
            node->father->right = auxiliar;
    }
    auxiliar->left = node;
    node->father = auxiliar;
    
    return root;
}
rnTree *rightRotation(rnTree *root, rnTree *node)
{
    rnTree *auxiliar = node->left;
    node->left = auxiliar->right;
    
    if(auxiliar->right != NULL)
        auxiliar->right->father = node;
    auxiliar->father = node->father;
    
    if(node->father == NULL)
        root = auxiliar;
    else
    {
        if(node == node->father->right)
            node->father->right = auxiliar;
        else
            node->father->left = auxiliar;
    }
    auxiliar->right = node;
    node->father = auxiliar;
    
    return root;
}
rnTree *insertOnTree(rnTree *root, rnTree *newNode)
{
    while(newNode != root && newNode->father->color == RED)
    {
        if(newNode->father == newNode->father->father->left)
        {
            rnTree *auxiliar = newNode->father->father->right;
            
            if(auxiliar == NULL || auxiliar->color == BLACK)
            { //CASO 1
                if(newNode == newNode->father->right)
                { //CASO 2
                    newNode = newNode->father;
                    root = leftRotation(root, newNode);
                }
                
                newNode->father->color = BLACK;   //CASO 3
                newNode->father->father->color = RED;
                root = rightRotation(root, newNode->father->father);
            }
            else
            {
                newNode->father->color = BLACK;
                auxiliar->color = BLACK;
                newNode->father->father->color = RED;
                newNode = newNode->father->father;
            }
        }
        else
        {
            if(newNode->father == newNode->father->father->right)
            {
                rnTree *auxiliar = newNode->father->father->left;
                
                if(auxiliar == NULL || auxiliar->color == BLACK)
                {
                    if(newNode == newNode->father->left)
                    {
                        newNode = newNode->father;
                        root = rightRotation(root, newNode);
                    }
                    newNode->father->color = BLACK;
                    newNode->father->father->color = RED;
                    root = leftRotation(root, newNode->father->father);
                    
                    
                }
                else
                {
                    newNode->father->color = BLACK;
                    auxiliar->color = BLACK;
                    newNode->father->father->color = RED;
                    newNode = newNode->father->father;
                }
            }
        }
    }
    root->color = BLACK;
    
    return root;
}
rnTree *insertNode(rnTree *root, int value)
{
    rnTree *newNode = createNewNode(value);
    rnTree *auxFather = NULL;
    rnTree *auxiliar = root;
    
    if(root == NULL)
    {
        root = newNode;                 /**************************************************/
        root->color = BLACK;
        
        return root;
    }
    while(auxiliar != NULL)
    {
        auxFather = auxiliar;
        if(newNode->key < auxiliar->key)
            auxiliar = auxiliar->left;
        else if(newNode->key > auxiliar->key)
            auxiliar = auxiliar->right;
        else
        {
            printf("O elemento %d ja existe na Arvore!!!\n",newNode->key);
            
            return root;
        }
    }
    newNode->father = auxFather;
    
    if(auxFather == NULL)
        root = newNode;
    else if(newNode->key < auxFather->key)
        auxFather->left = newNode;
    else
        auxFather->right = newNode;
    
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->color = RED;
    
    root = insertOnTree(root, newNode);
    
    return root;
}

void PreOrder(rnTree *root)
{
    if(root == NULL)
        return;
    printf("Chave = %.2d", root->key);
    printf("\tCor = %d\n", root->color);
    PreOrder(root->left);
    PreOrder(root->right);
}

/*
 void Ordem(TipoNo *raiz)
 {
 if(raiz == NULL)
 return;
 Ordem(raiz->esquerdo);
 printf("Chave = %.2d", raiz->chave);
 printf("\tCor = %d\n", raiz->cor);
 Ordem(raiz->direito);
 }
 
 void PosOrdem(TipoNo *raiz)
 {
 if(raiz == NULL)
 return;
 PosOrdem(raiz->esquerdo);
 PosOrdem(raiz->direito);
 printf("Chave = %.2d", raiz->chave);
 printf("\tCor = %d\n", raiz->cor);
 }
 */

rnTree *lowerMajor(rnTree *root)
{
    rnTree *aux = root->right;
    while(aux->left != NULL)
        aux = aux->left;
    return aux;
}

int isBlack(rnTree *node)
{
    if (node == NULL || node->color == BLACK)
    {
        return TRUE;
    }
    return FALSE;
}

rnTree *removeFromTree(rnTree *root, rnTree *node)
{
    rnTree *aux;
    
    while(node != root && node->color == BLACK)
    {
        if(node == node->father->left)
        {
            aux = node->father->right;
            
            if(aux->color == RED)
            { //CASO 1
                aux->color = BLACK;
                node->father->color = RED;
                root = leftRotation(root, node->father);
                aux = node->father->right;
            }
            if(isBlack(aux->left) == TRUE && isBlack(aux->right) == TRUE)
            {//CASO 2
                aux->color = RED;
                node = node->father;
            }
            else
            {
                if(isBlack(aux->right) == TRUE)
                { //CASO 3
                    aux->left->color = BLACK;
                    aux->color = RED;
                    root = rightRotation(root, aux);
                    aux = node->father->right;
                }
                aux->color = node->father->color; //CASO 4
                node->father->color = BLACK;
                aux->right->color = BLACK;
                root = leftRotation(root, node->father);
                node = root;
            }
        }
        else
        {
            aux = node->father->left;
            
            if(isBlack(aux->left) == TRUE)
            {
                aux->right->color = BLACK;
                aux->color = RED;
                root = leftRotation(root, aux);
                aux = node->father->left;
                
                aux->color = node->father->color;
                node->father->color = BLACK;
                aux->left->color = BLACK;
                root = rightRotation(root, node->father);
                node = root;
            }
            
            else
            {
                if(aux->color == RED)
                {
                    aux->color = BLACK;
                    node->father->color = RED;
                    root = rightRotation(root, node->father);
                    aux = node->father->left;
                }
                if(isBlack(aux->right) == TRUE && isBlack(aux->left) == TRUE)
                {
                    aux->color = RED;
                    node = node->father;
                }

            }
        }
    }
    node->color = BLACK;
    return root;
}

rnTree *searchNode(rnTree *root, int value)
{
    rnTree *aux = root;
    while(aux != NULL)
    {
        if(value < aux->key)
            aux = aux->left;
        else if (value > aux->key)
            aux = aux->right;
        else if (value == aux->key)
            
            return aux;
    }
    
    return NULL;
}

rnTree *removeNode(rnTree *root, int value)
{
    rnTree *node = searchNode(root, value);
    if(node == NULL)
    {
        printf("Noh nao se encontra na Arvore!\n\n");
        return root;
    }
    rnTree *aux1;
    rnTree *aux2;
    if(node->left == NULL || node->right == NULL)
        aux1 = node;
    else
        aux1 = lowerMajor(node);
    
    if(aux1->left != NULL)
        aux2 = aux1->left;
    else if (aux1->right != NULL)
        aux2 = aux1->right;
    
    if (aux2 != NULL)
    {
        aux2->father = aux1->father;
    }
    
    
    if(aux1->father == NULL)
        root = aux2;
    
    else
    {
        if(aux1 == aux1->father->left)
            aux1->father->left = aux2;
        else
            aux1->father->right = aux2;
    }
    
    if(aux1 != node)
        node->key = aux1->key;
    if(aux1->color == BLACK)
        root = removeFromTree(root, aux2);
    else
        aux2 = NULL;
    
    return root;
}

int main()
{
    selectedOption = Menu();
    selectOption(selectedOption);
    main();
}


