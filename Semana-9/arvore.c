#include <stdio.h>
#include <stdlib.h>

typedef long TipoChave;

typedef struct Registro {
    TipoChave Chave;
} Registro;

typedef struct No No;
typedef No* Apontador;
typedef Apontador TipoDicionario;

struct No {
    Registro Reg;
    Apontador pEsq, pDir;
};

int Altura( No *pRaiz )
{
    int iEsq,iDir;
    if (pRaiz == NULL)
        return 0;
    iEsq = Altura( pRaiz->pEsq );
    iDir = Altura( pRaiz->pDir );
    if ( iEsq > iDir )
        return iEsq + 1;
    else
    return iDir + 1;
}

int FB (No *pRaiz)
{
    if ( pRaiz == NULL ) 
        return 0;
    return Altura( pRaiz->pEsq ) - Altura( pRaiz->pDir );
}

void RSE( No **ppRaiz ){
    No *pAux;
    pAux = ( *ppRaiz )->pDir;
    ( *ppRaiz )->pDir = pAux->pEsq;
    pAux->pEsq = ( *ppRaiz );
    ( *ppRaiz ) = pAux;
}

void RSD( No**ppRaiz ){
    No *pAux;
    pAux = ( *ppRaiz )->pEsq;
    ( *ppRaiz )->pEsq = pAux->pDir;
    pAux->pDir = ( *ppRaiz );
    ( *ppRaiz ) = pAux;
}

int BalancaEsquerda( No **ppRaiz ){
    int fbe = FB ( ( *ppRaiz )->pEsq );
    if ( fbe > 0 ){
        RSD( ppRaiz );
        return 1;
    }
    else if ( fbe < 0 ){
        RSE( &( ( *ppRaiz )->pEsq ) );
        RSD( ppRaiz );
        return 1;
    }
    return 0;
}

int BalancaDireita( No **ppRaiz ){
    int fbd = FB( ( *ppRaiz )->pDir );
    if( fbd < 0 ){
        RSE( ppRaiz );
        return 0;
    }
    else if( fbd > 0 ){
        RSD( &( ( *ppRaiz )->pEsq ) );
        RSE( ppRaiz );
        return 0;
    }
}

int Balanceamento( No **ppRaiz ){
    int fb = FB( *ppRaiz );
    if ( fb > 1 )
        return BalancaEsquerda( ppRaiz );
    else if ( fb <-1 )
        return BalancaDireita( ppRaiz );
    else
        return 0;
}

int Push( No **ppRaiz, Registro *x ) {
    if ( *ppRaiz == NULL ) {
        *ppRaiz = ( No* )malloc( sizeof( No ) );
        ( *ppRaiz )->Reg = *x;
        ( *ppRaiz )->pEsq = NULL;
        ( *ppRaiz )->pDir = NULL;
        return 1;
    } else if ( ( *ppRaiz )->Reg.Chave > x->Chave ) {
        if ( Push( &( *ppRaiz )->pEsq, x ) ) {
            if ( Balanceamento( ppRaiz ) )
                return 0;
            else
                return 1;
        }
    } else if ( ( *ppRaiz )->Reg.Chave < x->Chave ) {
        if ( Push( &( *ppRaiz )->pDir, x ) ) {
            if ( Balanceamento( ppRaiz ) )
                return 0;
            else
                return 1;
        } else
            return 0;
    } else
        return 0;
}

int isAVL( No *pRaiz ){
    int fb;
    if ( pRaiz == NULL )
        return 1;
    if ( !isAVL( pRaiz->pEsq ) )
        return 0;
    if ( !isAVL( pRaiz->pDir ) )
        return 0;

    fb = FB ( pRaiz );
    if ( ( fb > 1 ) || ( fb <-1 ) )
        return 0;
    else
        return 1;
}

void PrintTree( No *pRaiz, int nivel ) {
    int i;
    if ( pRaiz != NULL ) {
        PrintTree( pRaiz->pDir, nivel + 1 );
        for ( i = 0; i < nivel; i++ ) printf("    ");
        printf( "%ld\n", pRaiz->Reg.Chave );
        PrintTree( pRaiz->pEsq, nivel + 1 );
    }
}

void FreeTree(No *pRaiz) {
    if ( pRaiz != NULL ) {
        FreeTree( pRaiz->pEsq );
        FreeTree( pRaiz->pDir );
        free( pRaiz );
    }
}
int main(){

    TipoDicionario arvore = NULL;
    Registro registro;
    char opcao;

    do {
        printf("Digite o valor da chave: ");
        scanf("%ld", &registro.Chave);

        if (Push(&arvore, &registro)) {
            printf("Insercao realizada com sucesso.\n");
        } else {
            printf("Erro na insercao.\n");
        }

        PrintTree(arvore, 0);

        if ( isAVL( arvore ) ) {
            printf("A arvore eh AVL.\n");
        } else {
            printf("A arvore nao eh AVL.\n");
        }

        printf("Deseja inserir mais um elemento? (S/N): ");
        scanf(" %c", &opcao);
    } while (opcao == 'S' || opcao == 's');

    FreeTree(arvore);
    return 0;
}