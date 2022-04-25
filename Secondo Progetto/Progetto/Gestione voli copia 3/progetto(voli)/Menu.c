#include <stdio.h>
#include "Menu.h"

int LoginMenu(){
    int choice = -1;
    printf(" * * * * * * * * * * * * * * * * * * * * * * * *    Welcome  to flight booking management\n * * * * * * * * * * * * * * * * * * * * * * * *  \n");
    printf("\nWho are you?\n");
    printf(" 0. Admin\n");
    printf(" 1. User\n");
    printf(" 2. Exit\n");
    printf("Insert your choice:");
    scanf("%d",&choice);
    while (choice < 0 || choice > 2) {
      clearInputBuffer();
      printf("This button does not allow you to make choices! Try again!\n");
      printf("Insert choice thanks: ");
      scanf("%d", &choice);
    }
    return choice;
}

int AdminMenu(){
    int choice = -1;

    printf("  \n                  **************** \n");
    printf("                    ADMINISTATOR        \n");
    printf("                  ****************     \n");

    printf(" 0. Logout\n");
    printf(" 1. Print destinations\n");
    printf(" 2. Insert destinations\n");
    printf(" 3. Insert new edge/ new connection between two city\n");
    printf(" 4. Delete destinations\n");
    
    printf("Insert your choice:");
    scanf("%d",&choice);
    while (choice < 0 || choice > 4) {
      clearInputBuffer();
      printf("This button does not allow you to make choices! Try again!\n");
      printf("Insert your choice:");
      scanf("%d", &choice);
    }
    return choice;
}

int UserMenuLogin(){
    int choice = -1;

    printf(" \n                   **************** \n");
    printf("                         USER          \n");
    printf("                   ****************     \n");
    
    printf(" 0. Quit\n");
    printf(" 1. SignUp\n");
    printf(" 2. SignIn\n");
    
    printf("Insert your choice:");
    scanf("%d",&choice);
    while (choice < 0 || choice > 2) {
      clearInputBuffer();
      printf("This button does not allow you to make choices! Try again!\n");
      printf("Insert your choice:");
      scanf("%d", &choice);
    }
    return choice;
}

int UserMenu(){
    int choice = -1;

    printf("\n                   **************** \n");
    printf("                         USER          \n");
    printf("                   ****************     \n");
    
    printf(" 0. LogOut\n");
    printf(" 1. Booking based on the cheapest route by entering the city and the departure destination\n");
    printf(" 2. Booking based on the shortest routes by entering the city of departure and destination\n");
    printf(" 3. Booking based on the fewer stopover by entering the city of departure and destination\n");
    printf(" 4. Booking based on the most popular destination by entering only the city of departure\n");
    printf(" 5. View prenotations\n");
    printf(" 6. View city list\n");
    printf(" 7. View entire graph\n");
    printf("Insert your choice:");
    scanf("%d",&choice);
    while (choice < 0 || choice > 7) {
      clearInputBuffer();
      printf("This button does not allow you to make choices! Try again!\n");
      printf("Insert your choice:");
      scanf("%d", &choice);
    }
        
    return choice;
}

void clearInputBuffer(){
  char c;
  while((c = getchar()) != '\n' && c != EOF){}
  return;
}

