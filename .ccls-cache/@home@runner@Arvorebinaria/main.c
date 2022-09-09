#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* gerar_vetor(int tamanho){ //Função que gera o vetor aleatório

  int *vetor = (int*) malloc(sizeof(int)*tamanho);

  for(int i = 0; i<tamanho; i++){
    vetor[i] = 1 + (rand() % 1000);
  }
  
  return vetor;
}

typedef struct vertice{

  int dado;                  //Chave
  struct vertice *direita;   //Filho a direita
  struct vertice *esquerda;  //Filho a esquerda

}vertice;

vertice* cria_vertice(int valor){ /*Função cria um novo vértice na memória
                                    e retorna o endereço de memória */
    vertice *novo;
    novo = (vertice *)malloc(sizeof(vertice));
    novo->dado = valor;
    novo->direita = novo->esquerda = NULL;
    return novo;
 
}

vertice* insercao(vertice *raiz,int valor){ /*Função insere um novo vértice na árvore
                                              e retorna o endereco de memória da raiz
                                               por meio de um ponteiro da estrutura */
  if(raiz == NULL){            
    return cria_vertice(valor);
    //Se a árvore não tiver nenhum vértice (vazia), faz a inserção do novo vértice
  }

  //chave = condição lógica para onde vai ser inserido o novo

  if(valor < (raiz->dado)){    //Se a chave do novo vértice for MENOR que a raiz
    if(raiz->esquerda == NULL){    
      raiz->esquerda = cria_vertice(valor);
      //Se não houver nenhum vértice na esquerda, faz a insercao
    }
    else{
      insercao(raiz->esquerda,valor);  
      /*Recursividade (chama novamente a função), faz a inserção do novo vértice, 
        a partir do filho da esquerda, considerando o filho da esquerda como nova "raiz" */
      }
  }

  if(valor > (raiz->dado)){  //Se a chave do novo vértice for MAIOR que a raiz
    if(raiz->direita == NULL){
      raiz->direita = cria_vertice(valor);
      //Se não houver nenhum vértice na direita, faz a insercao
    }
    else{
      insercao(raiz->direita,valor);
      /*Recursividade (chama novamente a função), faz a inserção do novo vértice, 
        a partir do filho da direita, considerando o filho da direita como nova "raiz" */
      }
    
  }

  return raiz;
  //Retorna o endereco de memória da raiz
    
}

void imprimir_arvore(vertice *raiz,int barra_t){ /* Função faz a impressao da árvore  
                                                      do jeito solicitado*/

  barra_t++; /* Artifício Técnico (gambiarra):
              barra_t é o contador para contar 
                quantos \t vai ser usado*/

  if(raiz != NULL){

    for(int i = 0; i < barra_t; i++){printf("\t");}
    if(barra_t != 1){printf("+");}           // Artifício Técnico para não imprimir "+" na raiz
    printf("%d\n",raiz->dado);
    imprimir_arvore(raiz->esquerda,barra_t); // Algoritmo segue o mesmo padrão de 
    imprimir_arvore(raiz->direita,barra_t);  //  impressão da função 'pre_order'

  }

}

void pre_order(vertice *raiz){ /* Função primeiro faz impressão da raiz,
                                  depois o vértice da esquerda, 
                                      depois o vértice da direita. 

            A
          /   \
         B     C
        / \   / \
       D   E F   G

  Pre_order: {A, B, D, E, C, F, G}

*/

  if(raiz != NULL){ // Apenas valores diferentes de NULL
    
    printf("%d",raiz->dado);
    if(raiz->esquerda != NULL){printf(", ");} // Artifício Técnico para imprimir ","
    pre_order(raiz->esquerda);                //Recursividade com o filho da esquerda.         
    if(raiz->direita != NULL){printf(", ");}  // Artifício Técnico para imprimir ","
    pre_order(raiz->direita);                 //Recursividade com o filho da direita.

  }


}

void in_order(vertice *raiz){  /* Função percorre os vértices de forma recursiva 
                                  da esquerda para direita e de baixo para cima, 
                                  começando na raiz. 

            A
          /   \
         B     C
        / \   / \
       D   E F   G

  In_order: {D, B, E, A, F, C, G}

*/
  
  if(raiz != NULL){
    
    in_order(raiz->esquerda);                 //Recursividade com o filho da esquerda.   
    if(raiz->esquerda != NULL){printf(", ");} // Artifício Técnico para imprimir ","
    printf("%d",raiz->dado);                  
    if(raiz->direita != NULL){printf(", ");}  // Artifício Técnico para imprimir ","
    in_order(raiz->direita);                  //Recursividade com o filho da direita.   
    
  }

}

void pos_order(vertice *raiz,int valor_raiz){  /* Função percorre os vértices de forma recursiva, 
                                                  onde a raiz é visitada por último,
                                                  então vemos todos os vértices da árvore esquerda, 
                                                  depois direita e por fim a raiz. 

            A
          /   \
         B     C
        / \   / \
       D   E F   G

  In_order: {D, E, B, F, G, C, A}

*/

  
  if(raiz->esquerda != NULL){
    pos_order(raiz->esquerda,valor_raiz); //Recursividade com o filho da esquerda. 

  }

  if(raiz->direita != NULL){
    pos_order(raiz->direita,valor_raiz); //Recursividade com o filho da direita.

  }

  
  printf("%d",raiz->dado);
  if(raiz->dado != valor_raiz){printf(", ");} /* Artifício Técnico para não imprimir ","
                                                  depois do último valor ser imprimido  */
}  

void encontra_folhas(vertice *raiz){

  if(raiz != NULL){
    
    encontra_folhas(raiz->esquerda);  //Recursividade com o filho da esquerda.
    encontra_folhas(raiz->direita);   //Recursividade com o filho da direita.
    if(raiz->direita == NULL && raiz->esquerda == NULL){
      printf("%d, ",raiz->dado);      /* Só vai ser impresso o valor se for uma folha,
                                          isto é, não tendo nenhum filho */
      
    }

  }
  
}

void buscar_vertice(vertice *raiz, int valor){ /* Busca Binaria */

  if(raiz == NULL){
     printf("\nValor gerado: %d; Diagnóstico: Ausente\n",valor);
  }

  if(raiz != NULL){
  
    if(valor > raiz->dado){
      buscar_vertice(raiz->direita,valor);
       /* Se valor de busca for MAIOR que o valor da raiz, continua a busca
            por recursividade pela raiz da direita */
    }
    
    if(valor < raiz->dado){
      buscar_vertice(raiz->esquerda,valor);
       /* Se valor de busca for MENOR que o valor da raiz, continua a busca
            por recursividade pela raiz da esquerda */
    } 
  
    if(valor == raiz->dado){
      printf("\nValor gerado: %d; Diagnóstico: Presente\n",valor);
    }
   
  }
}

vertice* apagar_vertice(vertice *raiz,int vertice){

  if(raiz == NULL){
    printf("Não existe nessa árvore um vértice com esse valor\n");
    return NULL;
  }

  if(raiz != NULL){
      
    if(vertice > raiz->dado){ //Verificando se o valor é MAIOR
      raiz->direita = apagar_vertice(raiz->direita,vertice);
      //Recursividade com a busca sendo a partir do filho da direita
    }
    
    if(vertice < raiz->dado){ //Verificando se o valor é MENOR
      raiz->esquerda = apagar_vertice(raiz->esquerda,vertice);
      //Recursividade com a busca sendo a partir do filho da esquerda
    } 
  
    if(vertice == raiz->dado){ //Encontrou vértice

      if(raiz->direita == NULL && raiz->esquerda == NULL){ //Exclusão de um Vértice Folha
        free(raiz);
        printf("Vértice removido com sucesso\n");
        return NULL;
        
      }

      if(raiz->direita == NULL && raiz->esquerda != NULL){ //Vértice com filho a esquerda
        struct vertice *aux;  //ponteiro auxiliar para fazer a troca
        aux = raiz->esquerda;
        free(raiz);
        printf("Vértice removido com sucesso\n");
        return aux;
        
      }

      if(raiz->direita != NULL && raiz->esquerda == NULL){  //Vértice com filho a direita
        struct vertice *aux;  //ponteiro auxiliar para fazer a troca
        aux = raiz->direita;
        free(raiz);
        printf("Vértice removido com sucesso\n");
        return aux;
        
      }

      else{ //Vértice com filho a direita e esquerda
        struct vertice *aux = raiz->esquerda;
        while(aux->direita != NULL){
          aux = aux->direita;
          /*Encontrando o último vértice na extrema direita
             para fazer a troca e não perder a sequência */
        }
        raiz->dado = aux->dado;
        aux->dado = vertice;
        raiz->esquerda = apagar_vertice(raiz->esquerda,vertice);
        /* Após a troca ser feita, o vértice que vai ser excluido se torna um vértice
            com um filho na esquerda ou um filho na direita ou pode ser apenas um nó,
            isto é, os métodos de exclusão para essas situações já existem. */
        return raiz;
        
      }
    
    }
    
  }

  return raiz;
}

int main() {

  srand(time(NULL));

  int n_vertices = 10 + (rand() % 17);
  int *vetor = gerar_vetor(n_vertices);

  
//------------------- 1° PARTE ---------------------------

  printf("\n1° Saída: \n\n");
  printf("Array Gerado: [");
  for(int i = 0; i<n_vertices; i++){

    if(n_vertices == i+1 ){
      printf("%d] \n",vetor[i]);
    }
    else{
      printf("%d, ",vetor[i]);
    }
   
  }

//------------------- 2° PARTE ---------------------------
  
  vertice *raiz = (vertice*) NULL;

  //int array[9] = {100,19,36,17,3,25,1,2,7};  //Balão de ensaio APAGAR DEPOIS

  for(int i = 0; i<n_vertices;i++){
    raiz = insercao(raiz,vetor[i]);
  }
  
  printf("\n2° Saída: \n\n");

  imprimir_arvore(raiz,0);
  
  printf("\n");

//------------------- 3° PARTE ---------------------------

  printf("\n3° Saída: \n\n");
  printf("Pre-order:{");
  pre_order(raiz);
  printf("}");
  
  printf("\n\n");
  
  printf("In-order:{");
  in_order(raiz);
  printf("}");

  printf("\n\n");
  printf("Pos-order:{");
  pos_order(raiz,vetor[0]);
  printf("}");

//------------------- 4° PARTE ---------------------------

  printf("\n\n4° Saída: \n\n");
  printf("Folhas: [");
  encontra_folhas(raiz);
  printf("]");

//------------------- 5° PARTE ---------------------------

  printf("\n\n\n5° Saída: \n\n");
  
  for(int i  = 0; i<10; i++){
    buscar_vertice(raiz,(300 + (rand() % 276))); 
    
  }

  return 0;
}