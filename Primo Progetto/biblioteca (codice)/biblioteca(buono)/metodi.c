#include "funzioni.h"
#define MAXNOME 255
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAXTITOLO 20




//metodo per il menu
int menu(){
int scelta; /*Questa variabile sarà utilizzata nella switch per decidere che cosa fare...*/

printf("* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~  \nBenvenuto nel programma di gestione biblioteca\n* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~   \n");


    printf(" 1. Mostra archivio\n");
    printf(" 2. Richiedi libro\n");
    printf(" 3. Restituire libro\n");
    printf(" 4. Esegui richiesta\n");
    printf(" 5. Uscire\n");
   
    printf("Inserisci scelta:");
    scanf("%d",&scelta); /*Viene inserito nella variabile var il numero inserito dall'utente e di conseguenza inserito nel ciclo Switch*/
while(scelta<0 || scelta>5) {
      printf("Questo tasto non consente di effetuare scelte! Riprova!\n");
      printf("Scelta: ");
      scanf("%d", &scelta);
   return scelta;
  }
return scelta;
}


struct libri *nuovoNodo(char *titolo ,char *autore, int cod_id)
{
 struct libri *nodo;

    nodo = (struct libri *) malloc(sizeof(struct libri));
        if (nodo == NULL) return NULL;
        strcpy(nodo->titolo, titolo);
        strcpy(nodo->autore, autore);
        nodo->cod_id =cod_id;
        nodo->next = NULL;
 return nodo;
}


struct libri *inserisciLista(struct libri *nodo, struct libri *lista)
{

if (lista==NULL) return nodo;
   lista->next = inserisciLista(nodo, lista->next);
return lista;
}


void gestioneErrore()
{
 printf("Errore\n");
  exit(0);
}


struct libri *leggiFile(FILE *fp, struct libri *lista)
{
    char titolo[MAXTITOLO];
    char autore[MAXAUTORE];
    int cod_id;
    struct libri *nodo;

 while(fscanf(fp,"%s%s%d",titolo,autore,&cod_id)==3){
    nodo = nuovoNodo(titolo, autore, cod_id);
      if (nodo == NULL)
         gestioneErrore();
           lista = inserisciLista(nodo, lista);
}

return lista;

}


void SearchBook (struct libri *l, char titolo[]){
int trovato = 0 ;
while (l != NULL && trovato != 1) {
   if(strcmp(l->titolo, titolo)==0) {
      printf("\nIl libro richiesto e' presente nell'archivio ed la richiesta è stata accettata quindi il libro è stato prestato con successo.\n");
      trovato=1;
    }
l = l->next;
}
  if(trovato != 1)
   printf("\nIl libro richiesto non e' presente nell'archivio la richiesta è stata rifiutata. La invitiamo ad richiederlo nei prossimi giorni.\n");
}


list insertTail(list L, char titolo[], char autore[] ,int cod_id) {
  if (L != NULL) {
      L->next = insertTail(L->next, titolo, autore, cod_id);
      
  }else{
      L = initList(titolo,autore,cod_id);
}
  return L;
}


list initList(char titolo[] ,char autore[] ,int cod_id) {
  list L = (list)malloc(sizeof(struct libri));
   strcpy(L->titolo, titolo);
   strcpy(L->autore, autore);
   L->cod_id= cod_id;
   L->next = NULL;
 return L;
}


void printList(list L) {
if (L != NULL) {
    printf("%s %s %d\t\n", L->titolo, L->autore, L->cod_id );
    
    printList(L->next);
  }
}


void freeNodo(struct libri *nodo)
{
   free((void *) nodo);
}


void freeLista(struct libri *lista)
{
  if (lista != NULL) {
    freeLista(lista->next);
    freeNodo(lista);
  }
}

list DeleteBook(list lis, char titolo[])
{
if(!lis) return NULL;
    if(strcmp(lis->titolo, titolo)==0)
  {
    list tmp = lis->next;
    freeNodo(lis);
    return tmp;
   }
lis->next = DeleteBook(lis->next, titolo);
return lis;
}
