#ifndef ListUtente_h
#define ListUtente_h
#include <stdbool.h>
#include <stdio.h>

struct Utente{
    char name[50];
    char surname[50];
    char email[50];
    char password[20];
    bool isAdmin;
    int discountPoint;
    struct Utente* next;
};

typedef struct Utente* ListUtente;

ListUtente initListUtente(char name[50], char surname[50], char email[50],char password[20], bool isAdmin);

bool user_exist(ListUtente L, char name[50], char surname[50], char email[50], char password[20], bool isAdmin);

ListUtente user_push(ListUtente L,char name[50], char surname[50], char email[50], char password[20], bool isAdmin);

ListUtente freeListUtente(ListUtente L);

ListUtente populateListWithAdmin(void);

ListUtente addDiscountPoint(ListUtente L, char email[50], int numPoint);

int calculateDiscountPoint(double bill);

ListUtente useDiscoutPoint(ListUtente L, char email[50], double billToPay, double* effectiveBill);

#endif /* ListUtente_h */



