#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "Graph.h"
#include "List.h"
#include "Queue.h"
#include "Menu.h"
#include "ListPrenotazioni.h"
#include "ListUtente.h"

#define  randomize srand(((unsigned int) time(NULL)))
#define  random(x) rand()%x


int main(int argc, char** argv){
  bool Admin;
  char name[50];
  char surname[50];
  char deleteCity[32];
  char cityPartenza[32];
  char cityDestinazione[32];
  char email[100];
  char pwd[20];
  ListPrenotazioni listaDellePrenotazioni = NULL; //per listPrenotazioni
  ListUtente listaUtentiIscritti = populateListWithAdmin(); //per listUtente, inizialmente contiene solo gli admin
  Graph g = populateGraph();
  randomize;
  int mostPopularDestination = -1;
  int loginChoice;
  int adminChoice;
  int userChoice;
  int userLoginChoice;
  bool continueLoop;
  bool continueUserLoop;
  double price;
  double distance;
  List path = NULL;
    int discountPointChoice = 0;
  double bill;
  do{
    loginChoice = LoginMenu();
    if(loginChoice == 0){  /*azioni amministratore*/
        printf("Insert e-mail: ");
        scanf("%s", email);
        clearInputBuffer();
        printf("Insert password(max 7 characters): ");
        scanf("%s", pwd);
        clearInputBuffer();
        Admin = true;
        if(user_exist(listaUtentiIscritti, name, surname, email, pwd, Admin) == true){
            // accesso admin con successo
            printf("Admin access %s %s carried out successfully\n", name, surname);
            continueLoop = true;
        }else{
            // accesso come admin negato
            printf("Login failed!\n");
            continueLoop = false;
        }
         /*
         Se l'admin non e' presente nella data structure degli admin --> continueLoop = false
             In questo modo torna al menu di login e non vengono eseguite operazioni
         */
        while(continueLoop){
          adminChoice = AdminMenu();
          switch (adminChoice){
            case 0: // exit / logout
              continueLoop = false;
              break;
            case 1: /* stampa destinazioni e tratte*/
              printf("\nThe destinations are as follows:\n");
              PrintGraph(g);
              break;
            case 2: /*inserisci destinazioni e tratte*/
              addNode(g, getCityName("new destination(first uppercase character)"));
                  printf("\n~Operation successfully performed~\n");

              break;
            case 3:// aggiungi un arco
            
              printf("\nInsert price of new edge(example 23.78): ");
              scanf("%lf", &price);
              clearInputBuffer();
              printf("\nInsert distance of new edge(example 345.98):");
              scanf("%lf", &distance);
              clearInputBuffer();
              addEdge(g,getCityIndexByName(g,getCityName("new destination(first uppercase character)")), getCityIndexByName(g, getCityName("new destination(first uppercase character)")),price,distance);
              printf("\n ~Operation successfully performed~ \n");
              break;
            case 4: /*cancella destinazioni e tratte che contengono la specifica destinazione*/
              printf("Insert the city to be deleted:\n");
              scanf("%s", deleteCity);
              clearInputBuffer();
              removeNodeByString(g,deleteCity);
              printf("\n~Operation successfully performed~ \n");
              break;
            default: /*Se l'utente sbaglia ad inserire il numero*/
              printf("This button does not allow you to make choices! Try again!\n");
              break;
          }
        }
    }
    else if(loginChoice == 1){ /*azioni utenti*/
      continueLoop = true;
      Admin=false;
      while(continueLoop){
        userLoginChoice = UserMenuLogin();
        switch (userLoginChoice){
          case 0: // quit
            continueLoop = false;
            break;
          case 1: /*effettuo iscrizione*/
            printf("\nInsert name:\n");
            scanf("%s", name);
            printf("\nInsert surname:\n");
            scanf("%s", surname);
            printf("\nInsert e-mail:\n");
            scanf("%s",email);
            printf("\nInsert password(max 7 characters):\n");
            scanf("%s",pwd);
            clearInputBuffer();
            listaUtentiIscritti = user_push(listaUtentiIscritti,name,surname,email,pwd,Admin);
            break;
          case 2: /*effettuo accesso*/
            printf("\nInsert e-mail:\n");
            scanf("%s",email);
            printf("\nInsert password(max 7 characters):\n");
            scanf("%s",pwd);
            clearInputBuffer();
            if(user_exist(listaUtentiIscritti, name, surname, email, pwd,Admin) == false){
              // nel caso l'accesso non va a buon fine si interrompe questo ramo dello switch case
              printf("Unregistered user!\n");
              continueLoop = false;
              break;
            }else{
              // name e surname vengono estratti dalla funzione user_exist
              printf("Welcome %s %s\n", name, surname);
              // in questo ramo l'utente e' riuscito a registrarsi e puo' eseguire operazioni
              continueUserLoop = true;
              while(continueUserLoop){
                //prenotazioni da fare
                path = NULL;
                userChoice = UserMenu();
                switch (userChoice){
                case 0: // logout
                  continueUserLoop = false;
                  break;
                case 1: // tratta piu' economica in termini di prezzo dati due punti --> Dijkstra sugli archi prezzo
                  printf("Insert city of start: ");
                  scanf("%s", cityPartenza);
                  printf("Insert city coming: ");
                  scanf("%s", cityDestinazione);
                  clearInputBuffer();
                  path = dijkstra(g, getCityIndexByName(g, cityPartenza), getCityIndexByName(g, cityDestinazione), BY_PRICE);
                  if(path != NULL){ // la citta' destinazione e' raggiungibile
                    printPath(g, path);
                    printf("Do you want to use your discount point? [1 == Y /0 == n]:");
                    scanf("%d", &discountPointChoice);
                    clearInputBuffer();
                    if(discountPointChoice == 1){
                      // se si usa uno sconto non si ha diritto a punti bonus
                      useDiscoutPoint(listaUtentiIscritti, email, getPriceFromPath(path), &bill);
                      listaDellePrenotazioni = insertTailPrenotazioni(listaDellePrenotazioni, email, cityPartenza, cityDestinazione, bill);
                    }else{
                      // vicerversa se non si usano sconti, si ottengono punti bonus
                      listaDellePrenotazioni = insertTailPrenotazioni(listaDellePrenotazioni, email, cityPartenza, cityDestinazione, getPriceFromPath(path));
                      listaUtentiIscritti = addDiscountPoint(listaUtentiIscritti, email, calculateDiscountPoint(getPriceFromPath(path)));
                    }
                    path = freeList(path);
                  }else{ // la citta' destinazione e' raggiungibile
                    printf("%s Cannot be reached from the city %s\n", cityDestinazione, cityPartenza);
                  }
                  break;
                case 2: // tratta piu' economica in termini di distanza dati due punti --> Dijkstra sugli archi distanza
                  printf("Insert city of start: ");
                  scanf("%s", cityPartenza);
                  printf("Insert city coming: ");
                  scanf("%s", cityDestinazione);
                  clearInputBuffer();
                  path = dijkstra(g, getCityIndexByName(g, cityPartenza), getCityIndexByName(g, cityDestinazione), BY_DISTANCE);
                  if(path != NULL){ // la citta' destinazione e' raggiungibile
                    printPath(g, path);
                    printf("Do you want to use your discount point? [1 == Y /0 == n]:");
                    scanf("%d", &discountPointChoice);
                    clearInputBuffer();
                    if(discountPointChoice == 1){
                      // se si usa uno sconto non si ha diritto a punti bonus
                      useDiscoutPoint(listaUtentiIscritti, email, getPriceFromPath(path), &bill);
                      listaDellePrenotazioni = insertTailPrenotazioni(listaDellePrenotazioni, email, cityPartenza, cityDestinazione, bill);
                    }else{
                      // vicerversa se non si usano sconti, si ottengono punti bonus
                      listaDellePrenotazioni = insertTailPrenotazioni(listaDellePrenotazioni, email, cityPartenza, cityDestinazione, getPriceFromPath(path));
                      listaUtentiIscritti = addDiscountPoint(listaUtentiIscritti, email, calculateDiscountPoint(getPriceFromPath(path)));
                    }
                    path = freeList(path);
                  }else{ // la citta' destinazione e' raggiungibile
                    printf("%s Cannot be reached from the city %s\n", cityDestinazione, cityPartenza);
                  }
                  break;
                case 3: // tratta che minimizza il numero di scali dati due punti --> BFS (opera indistintamente su entrambi gli archi allo stesso modo)
                  printf("Insert city of start: ");
                  scanf("%s", cityPartenza);
                  printf("Insert city coming: ");
                  scanf("%s", cityDestinazione);
                  clearInputBuffer();
                  path = bfs(g, getCityIndexByName(g, cityPartenza), getCityIndexByName(g, cityDestinazione));
                  if(path != NULL){ // la citta' destinazione e' raggiungibile
                    printPath(g, path);
                    printf("Do you want to use your discount point? [1 == Y /0 == n]:");
                    scanf("%d", &discountPointChoice);
                    clearInputBuffer();
                    if(discountPointChoice == 1){
                      // se si usa uno sconto non si ha diritto a punti bonus
                      useDiscoutPoint(listaUtentiIscritti, email, getPriceFromPath(path), &bill);
                      listaDellePrenotazioni = insertTailPrenotazioni(listaDellePrenotazioni, email, cityPartenza, cityDestinazione, bill);
                    }else{
                      // vicerversa se non si usano sconti, si ottengono punti bonus
                      listaDellePrenotazioni = insertTailPrenotazioni(listaDellePrenotazioni, email, cityPartenza, cityDestinazione, getPriceFromPath(path));
                      listaUtentiIscritti = addDiscountPoint(listaUtentiIscritti, email, calculateDiscountPoint(getPriceFromPath(path)));
                    }
                    path = freeList(path);
                  }else{ // la citta' destinazione e' raggiungibile
                    printf("%s  Cannot be reached from the city %s\n", cityDestinazione, cityPartenza);
                  }
                  break;
                case 4: // meta' piu' gettonata, qualora sia possibile dato che e' scelta randomicamente e quindi puo' non essere raggiungibile
                  printf("Insert city of start: ");
                  scanf("%s", cityPartenza);
                  clearInputBuffer();
                  mostPopularDestination = random(g->nodes_count);
                  printf("The most popular destination is: %s\n", g->cityNames[mostPopularDestination]);
                  path = dijkstra(g, getCityIndexByName(g, cityPartenza), mostPopularDestination, BY_PRICE);
                  strcpy(cityDestinazione, g->cityNames[mostPopularDestination]);
                  if(path != NULL){ // la citta' destinazione e' raggiungibile
                    if(mostPopularDestination == getCityIndexByName(g, cityPartenza)){
                      printf("Congratulations you are already in the most popular destination!\n");
                    }
                    printPath(g, path);
                    printf("Do you want to use your discount point? [1 == Y /0 == n]:");
                    scanf("%d", &discountPointChoice);
                    
                    if(discountPointChoice == 1){
                      // se si usa uno sconto non si ha diritto a punti bonus
                      useDiscoutPoint(listaUtentiIscritti, email, getPriceFromPath(path), &bill);
                      listaDellePrenotazioni = insertTailPrenotazioni(listaDellePrenotazioni, email, cityPartenza, cityDestinazione, bill);
                    }else{
                      // vicerversa se non si usano sconti, si ottengono punti bonus
                      listaDellePrenotazioni = insertTailPrenotazioni(listaDellePrenotazioni, email, cityPartenza, cityDestinazione, getPriceFromPath(path));
                      listaUtentiIscritti = addDiscountPoint(listaUtentiIscritti, email, calculateDiscountPoint(getPriceFromPath(path)));
                    }
                    path = freeList(path);
                  }else{ // la citta' destinazione e' raggiungibile
                    printf("The most popular destination: %s cannot be reached from the city %s (of course you're unlucky huh)\n", g->cityNames[mostPopularDestination], cityPartenza);
                  }
                  break;
                case 5: // vedi prenotazioni attive
                  printf("\nBooking by: %s %s: \n", name, surname);
                  filterPrintListPrenotazioni(listaDellePrenotazioni, email);
                  break;
                case 6: // vedi elenco citta;
                  PrintCityGraph(g);
                  break;
                case 7: // vedi grafo completo
                  PrintGraph(g);
                  break;
                default: // scelta invalida
                  printf("This button does not allow you to make choices! Try again!\n");
                  break;
                }
              }
            }
          default: /*Se l'utente sbaglia ad inserire il numero*/
            printf("This button does not allow you to make choices! Try again!\n");
            break;
        }
      }
    }
    //tutti gli altri valori per loginChoice vengono ignorati
  }while(loginChoice != 2);
  printf("Thanks for choosing us, come back to visit us!\n");
  freeGraph(g);
  listaDellePrenotazioni = freeListPrenotazioni(listaDellePrenotazioni);
  listaUtentiIscritti = freeListUtente(listaUtentiIscritti);
  return 0;
}



