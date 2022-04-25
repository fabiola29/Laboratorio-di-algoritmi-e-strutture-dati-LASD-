#include <stdlib.h>
#include "ListUtente.h"
#include <string.h>
#include <stdio.h>

ListUtente initListUtente(char name[50], char surname[50], char email[50],char password[20], bool isAdmin)
{
    ListUtente L = (ListUtente)malloc(sizeof(struct Utente));
    strcpy(L->name, name);
    strcpy(L->surname, surname);
    strcpy(L->email, email);
    strcpy(L->password, password);
    L->isAdmin =isAdmin;
    L->discountPoint = 0;
    L->next = NULL;
    return L;
}

ListUtente user_push(ListUtente L, char name[50], char surname[50], char email[50], char password[20], bool isAdmin)
{
    if (L != NULL){
        if(strcmp(L->email, email) == 0){
            printf("Email already present, operation canceled\n");
        }
        else{
            L->next = user_push(L->next,name,surname,email,password,isAdmin);
        }
    } else{
        L = initListUtente(name,surname,email, password,isAdmin);
    }
    return L;
}


bool user_exist(ListUtente L, char name[50], char surname[50], char email[50], char password[20], bool isAdmin){
    struct Utente *tmp;
    tmp = L;
    if (tmp != NULL)
     {
        if (strcmp(tmp->email,email)==0 && strcmp(tmp->password, password)==0 && tmp->isAdmin==isAdmin)
        {
            strcpy(name, L->name);
            strcpy(surname, L->surname);
            return true;
        }
        else{
            return user_exist(tmp->next,name, surname, email, password,isAdmin);
        }
    }
    return false;
}

ListUtente freeListUtente(ListUtente L){
    if(L){
        L->next = freeListUtente(L->next);
        free(L);
    }
    return NULL;
}

ListUtente populateListWithAdmin(){
    ListUtente l = NULL;
    l = user_push(l, "Silvia", "Stranieri", "email_stranieri", "password", true);
    l = user_push(l, "Aniello", "Murano", "email_murano", "password", true);
    return l;
}

ListUtente addDiscountPoint(ListUtente L, char email[50], int numPoint){
    if(L){
        if(strcmp(L->email, email) == 0){
            L->discountPoint += numPoint;
        }
        else{
            L->next = addDiscountPoint(L->next, email, numPoint);
        }
    }
    return L;
}

int calculateDiscountPoint(double bill){
    int numPoint = 0;
    if(bill > 0.0 && bill < 100.0){
        numPoint = 8;
    }else if(bill >= 100 && bill < 350){
        numPoint = 13;
    }else if(bill >=350 && bill < 800.0){
        numPoint = 21;
    }else if(bill >= 800.0 && bill < 1200.0){
        numPoint = 36;
    }else{  // bill >= 1200
        numPoint = 55;
    }
    return numPoint;
}

//
ListUtente useDiscoutPoint(ListUtente L, char email[50], double billToPay, double* effectiveBill){
    if(L){
        if(strcmp(L->email, email) == 0){
            printf("You have %d point\n", L->discountPoint);
            printf("With 5 point you can get a discout of 8 euros!\n");
            double maxPointYouCanUse = (billToPay/8);
            printf("At most you can use %.0lf points\n", maxPointYouCanUse);
            double pointToUse;
            int promptMessage = 0;
            do{
                if(promptMessage == 1){
                    printf("Invalid input retry!");
                    promptMessage = 0;
                }
                printf("Insert the amount of point you want to use: ");
                scanf("%lf", &pointToUse);
                if(pointToUse < 0.0 || pointToUse > maxPointYouCanUse){
                    promptMessage = 1;
                }
            }while (pointToUse < 0.0 || pointToUse > maxPointYouCanUse);
            if(pointToUse <= L->discountPoint){
                *effectiveBill = billToPay - 8*pointToUse;
                L->discountPoint -= pointToUse;
                printf("Total bill: %lf\n", *effectiveBill);
            }else{
                printf("You haven't enough point! full bill charged!\n"); // severo ma giusto
                *effectiveBill = billToPay;
            }
            
        }
        else{
            L->next = useDiscoutPoint(L->next, email, billToPay, effectiveBill);
        }
    }
    return L;
}

