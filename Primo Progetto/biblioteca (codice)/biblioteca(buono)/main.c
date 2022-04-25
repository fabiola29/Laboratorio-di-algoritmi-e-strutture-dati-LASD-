#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funzioni.h"

int main() {

    int scelta; /*dichiarazione variabile per scelte */
    FILE *fp; /* dichiarazione puntatore al file "Libri.txt"*/
    FILE *fd; /* dichiarazione puntatore al file "Richieste.txt"*/
    struct libri *lista=NULL; //per libri
    char titolo[50]; //dichiarazione della variabile titolo
    char autore[20]; /*dichiarazione variabile autire */
    int id = 0; /*dichiarazione variabile id(codice libro*/
    int n; /*dichiarazione variabile per il numero di libri che si vuole restituire*/
    char nome[255]; /*dichiarazione nome dello studente*/
    char cognome[255]; /*dichiarazione cognome dello studente*/
    char matricola[9];/*dichiarazione matricola dello studente*/
    int m =0;/*dichiarazione variabile per il numero di libri che si desidera richiedere*/
  


   
fp = fopen("Libri.txt","r");
   if (fp == NULL) gestioneErrore();
      lista = leggiFile(fp, lista);
fclose(fp);
    
    
while((scelta = menu())){
  switch (scelta) /* Creo uno switch con 5 case, uno per ogni possibile scelta */
   {

        case 1: /* Case costruito per stampare l'archivio*/
  
             printList(lista);

        break;
   
        case 2: /* Case costruito per richiesta libro*/
        
            printf("\nQuanti libri desideri richiedere ?");
            scanf("%d",&m);
          
           fd=fopen("Richieste.txt","a");
        
         if(fd==NULL)
            printf("Errore in scrittura\n");
         else 
        {
            for(int i=0;i<m;i++)
        {
        
        printf("\nInserisci Cognome dello studente: ");
        scanf("%s",cognome);
        fprintf(fd,"cognome: %s\n",cognome);
        
        printf("\nInserisci il Nome dello studente: ");
        scanf("%254s",nome);
        fprintf(fd,"Nome: %s\n",nome);
        
        printf("\nInserisci Matricola dello studente(9 caratteri): ");
        scanf("%s",matricola);
        fprintf(fd,"Matricola: %s\n",matricola);
        
        printf("\nInserisci titolo del libro che si desidera richiedere: ");
        scanf("%s",titolo);
        fprintf(fd,"titolo: %s\n",titolo);
        
        printf("\nInserisci autore del libro che si desidera richiedere:");
        scanf("%s",autore);
        fprintf(fd,"autore: %s\n",autore);
        
        printf("\nInserisci codice del libro che si desidera richiedre(5 caratteri):");
        scanf("%d", &id);
        fprintf(fd,"codice: %d\n", id);
        
        fprintf(fd, "\n");
        printf("\nRichiesta effettuata con successo\n");
                  
            }
         
            fclose(fd);
        }
       
        break;
 
        case 3: /* Case costruito per restituire un libro tramite codice*/
          
            printf("\nQuanti libri vuoi restituire?:");
            scanf("%d", &n);
              for (int i=0; i<n; i++) {
                   
                   printf("\nInserire titolo: ");
                   scanf("%49s", titolo);
                 
                  printf("\nInserire autore: ");
                  scanf("%19s", autore);
                
                  printf("\nInserire codice(5 caratteri): ");
                  scanf("%d", &id);
                 
                  printf("\nLibro restituito con successo\n");

                    lista = insertTail(lista, titolo, autore, id);
            }
             
       break ;
   
    case 4: /*esegui richiesta*/
    
        fd=fopen("Richieste.txt","r");

        char buf[30];
        // legge le righe in un buffer temporaneo
        for (int i = 0; i < 4; ++i)
            fgets(buf, 30, fd);

        // buf contiene "titolo: TitoloLibro"
        // prendiamo solo "TitoloLibro"
        sscanf(buf, "%*s %s", titolo);

        SearchBook(lista,titolo);
        lista = DeleteBook(lista, titolo);
        fclose(fd);
        
       
    break ;

    case 5: /*Se l'utente vuole uscire dalla biblioteca*/
        
             printf("Grazie per aver scelto il servizio di gestione della biblioteca, torna a trovarci!\n");
        
        return 0;
       
      break;

    
       default: /*Se l'utente sbaglia ad inserire il numero*/
        
               printf("Questo tasto non consente di effetuare scelte! Riprova!\n");
       
        break;
             
      } /*Fine switch*/
   } /*Fine do*/
  return 0;
} /*Fine main*/
