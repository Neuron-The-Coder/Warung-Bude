#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../Controller/Controller.h"

void AddDish(){
    CLS();
    char newname[255];
    int newprice;
    int newqty;

    do{
        printf ("Input Dish Name [Lowercase only]: ");
        scanf ("%[^\n]", newname); getchar();
    } while ((isValidName((char *)newname)) == 1);

    do{
        printf ("Input Dish Price [1000 - 50000]: ");
        scanf ("%d", &newprice); getchar();
    } while (newprice < 1000 || newprice > 50000);

    do{
        printf ("Input Dish Stock[1 - 999]: ");
        scanf ("%d", &newqty); getchar();
    } while (newqty < 1 || newqty > 999);

    PushDish((char*) newname, newprice, newqty);
    puts("Dish Successfully Added");
    Entt();
} 

void RemoveDish(){
    CLS();
    char gudbai[255];
    if (ShowDish() == -1){
        Entt();
        return;
    }
    else{
        printf ("Dish Name: ");
        scanf ("%[^\n]", gudbai); getchar();
    }

    if (RemoveDish((char*) gudbai) == -1) {
        puts("Cannot found your dish");
    }
    else {
        puts("Successfully remove your dish!");
    }
    Entt();
}

void AddCustomer(){
    CLS();
    char newname[255];

    while(1){
        printf ("Name [No space and digits allowed]: ");
        scanf ("%[^\n]", newname); getchar();
        
        if ((isValidCustomer((char*) newname))) break;
    }

    PushCustomer((char *) newname);
    puts("Success :)");
    Entt();

}

void SearchCustomer(){
    CLS();
    char name[255];
    while(1){
        printf ("Name [No space and digits allowed]: ");
        scanf ("%[^\n]", name); getchar();
        
        if ((isValidCustomer((char*) name))) break;
    }
    int a = FindCustomer((char*) name);
    if (a == 1) puts("Customer exist");
    else puts ("Customer doesn\'t exist");
    Entt();
}

void ViewCustomer(){
    CLS();
    PrintCustomer();
    Entt();
}

void Order(){
    CLS();
    char name[255];
    //int no = 1;
    while (1){
        printf ("Insert name [Must exist]: ");
        scanf ("%[^\n]", name); getchar();
        if (FindCustomer((char*)name) == 1) break;
        else puts("Customer Doesn\'t Exist!");
    }

    int howmuch = 0;
    printf ("Insert the amount of dish: ");
    scanf ("%d", &howmuch); getchar();

    for (int i=1; i<=howmuch; i++){
        printf ("[%d] Dish name an number [Name] x[Amount]:  ", i);
        char dishnames[255];
        int dishamounts;
        scanf ("%[^ ] x%d", dishnames, &dishamounts); getchar();
        int ok = PushOrder((char*) name, (char*) dishnames, dishamounts);

        if (ok == -1) puts("Food doesn't exist");
        else if (ok == 1) puts("Success!");
        else if (ok == 0) puts("Too much!!!");
    }
    puts("Done!");
    Entt();
}

void CheckOut(){
    CLS();
    char name[255];
    int no = 1;

    while (1){
        printf ("Insert name [Must exist]: ");
        scanf ("%[^\n]", name); getchar();
        if (FindCustomer((char*)name) == 1) no = 1;
        else no = 0;
        break;
    }

    if (no == 0){
        puts("Customer does not exist");
        Entt();
        return;
    }

    int ok = Checks((char *) name);
    if (ok == 0) puts ("He/she doesnt order anything!");
    else puts ("Successfully checked out");
    Entt();
}

int main(){
    
    int pick = 0;
    do{
        CLS();
        OSwhat();
        Date();
        puts("WARUNG BUDE :)");
        puts("==============================");
        puts("1. Add Dish");
        puts("2. Remove Dish");
        puts("3. Add Customer");
        puts("4. Search Customer");
        puts("5. View Warteg");
        puts("6. Order");
        puts("7. Checkout");
        puts("8. Exit Warteg :(");

        printf (">> ");
        scanf ("%d", &pick); getchar();

        if(pick == 1) AddDish();
        else if (pick == 2) RemoveDish();
        else if (pick == 3) AddCustomer();
        else if (pick == 4) SearchCustomer();
        else if (pick == 5) ViewCustomer();
        else if (pick == 6) Order();
        else if (pick == 7) CheckOut();

    } while (pick != 8);

    //Fungsi 8
    CLS();
    puts("Expand your terminal in full screen for something special!");
    puts("Press ENTER if you are ready !");
    getchar();
    PrintSplash();
    puts("Thanks :)");
    return 0;
}
