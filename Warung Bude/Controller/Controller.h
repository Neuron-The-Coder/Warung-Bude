#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include "../Model/Model.h"

void Entt(){ //Press ENTER thing
    puts("Press ENTER to continue");
    getchar();
}

int isValidName (char * word){ //Cek apakah nama gaada uppercase

    int no = 0;
    for (int i=0; word[i] != '\0'; i++){
        if (isupper(word[i])){
            no = 1;
            break;
        }
    }
    return no;

}

Dish *newDish(char *name, int price, int qty){ //Buat dish baru (utk menu atau orderan)
    Dish *temp = (Dish*) malloc (sizeof (Dish));
    strcpy(temp->name, name);
    temp->price = price;
    temp->stock = qty;

    temp->next = NULL;
    temp->prev = NULL;

    return temp;
}

Customer *newCustomer (char *names){ //Buat customer
    Customer *temp = (Customer *) malloc (sizeof (Customer));
    strcpy(temp->name, names);
    temp->headOrder = NULL;
    temp->tailOrder = NULL;
    temp->prev = NULL;
    temp->next = NULL;
    return temp;
}

void PushDish(char* newname, int newprice, int newstock){ //Push Dish ke Menu
    Dish *temp = newDish((char *) newname, newprice, newstock);
    if (!headDish){
        headDish = tailDish = temp;
    }
    else {
        tailDish->next = temp;
        temp->prev = tailDish;
        tailDish = temp;
    }
}

int ShowDish(){ //Print semua dish yang ada
    if (!headDish){
        puts("Nothing Here");
        return -1;
    }   
    else {
        puts("O===========================================O");
        puts("| No |         Name         | Qty |  Price  | ");
        puts("O===========================================O");
        Dish *now = headDish;
        int i = 1;
        while (now){
            printf("| %-2d | %-20s | %-3d | Rp%-5d |\n", i, now->name, now->stock, now->price);
            i++;
            now = now->next;
        }
        puts("O===========================================O");
        return 1;
    }
}

void OSwhat(){ //Define ini OS apa
	printf ("System OS: ");	
	#ifdef _WIN32
		puts ("Windows 32-bit");
	#elif _WIN64
		puts ("Windows 64-bit");
	#elif __APPLE__ || __MACH__
		puts("Mac OSX");
  	#elif __linux__
  		puts("Linux");
  	#elif __FreeBSD__
  		puts("FreeBSD");
  	#elif __unix || __unix__
  		puts("Unix");
  	#else
  		puts("Other");
  	#endif
}

void Date(){ //Print date
	
	time_t a; //declare var utk waktu
	struct tm *b; //declare nama struct 
	time (&a); // ambil pointer a
	b = localtime(&a); //Assign pointer struct
	
	char date[30];
	char days[7][20] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
	char months[13][10] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Des"};
	
	printf("%s %d-%s-%d %02d:%02d:%02d\n", days[b->tm_wday], b->tm_mday, months[b->tm_mon], b->tm_year+1900, b->tm_hour, b->tm_min, b->tm_sec);

}

int RemoveDish(char * gudbai){ //Remove dish dari menu

    if (headDish && headDish == tailDish && strcmp(gudbai, headDish->name) == 0){
        headDish = tailDish = NULL;
        free(headDish);
        return 1;
    }

    else if (headDish && strcmp(gudbai, headDish->name) == 0){
        Dish *baii = headDish;
        headDish = headDish->next;
        baii->next = NULL;
        headDish->prev = NULL;
        free(baii);
        return 1;
    }

    else if (strcmp(gudbai, tailDish->name) == 0){
        Dish *baii = tailDish;
        tailDish = tailDish->prev;
        tailDish->next = NULL;
        baii->prev = NULL;
        free(baii);
        return 1;
    }

    else {
        Dish *baii = headDish;
        while (baii){
            if (strcmp(baii->name, gudbai) == 0) break;
            baii = baii->next;
        }
        if (!baii) return -1;
        (baii->prev)->next = baii->next;
        (baii->next)->prev = baii->prev;
        baii->next = NULL;
        baii->prev = NULL;
        free(baii);
        return 1;
    }
}

int DJB (char* name){ //DJB
    int hashed = 5381;
    int c;

    while (c = *name++)
    hashed = ((hashed << 5) + hashed) + c; 

    return (hashed % 26);
}

void PushCustomer(char *name){ //Push new customer ke hashtable
    Customer *temp = newCustomer((char*) name);
    int idx = DJB((char*) name);

    if (!headCustomer[idx]){
        headCustomer[idx] = tailCustomer[idx] = temp;
    }
    else { //pushTail
        tailCustomer[idx]->next = temp;
        temp->prev = tailCustomer[idx];
        tailCustomer[idx] = temp; 
    }
}

bool isValidCustomer(char * newname){ //Customer ini ada ga?
    bool ok = true;
    for (int i=0; newname[i]!= '\0'; i++){
        if (newname[i] == ' ' || isdigit(newname[i])){
            ok = false;
            break;
        }
    }
    return ok;
}

int FindCustomer(char * name){ //Cari customer pakek DJB dan traverse LL
    int idx = DJB((char *) name);
    int res = 0;
    Customer *now = headCustomer[idx];
    while (now){
        if (strcmp(now->name, name) == 0){
            res = 1;
            break;
        }
        now = now->next;
    }
    return res;

}

void PrintCustomer(){ //Print semua customer (i untuk index)
    int empty = 0;

    for (int i=0; i<26; i++){

        if (!headCustomer[i]) continue;
        else {
            empty = 1;
            Customer *now = headCustomer[i];
            while (now){
                printf ("%-2d | %-20s\n", i, now->name);
                now = now->next;
            }
        }
    }
}

int PushOrder (char* name, char* dishname, int dishamount){ //Push order ke customer (masih pakek struct Dish krn gaada bedanya:))

    //cek apakah nama makanan ada
    Dish *now = headDish;
    while (now){
        if (strcmp(now->name, dishname) == 0) break;
        now = now->next;
    }
    if (!now) return -1;
    else if (now->stock < dishamount) return 0;
    now->stock -= dishamount;
    //Transfer harga per - satuan
    Dish *temp = newDish((char *) dishname, now->price, dishamount);

    int idx = DJB((char*) name);

    Customer *person = headCustomer[idx];
    while (strcmp(person->name, name) != 0) person = person->next;

    if (!(person->headOrder)) person->headOrder = person->tailOrder = temp;
    
    //pushTail
    else {
        (person->tailOrder)->next = temp; //ambil taildish customer->next
        temp->prev = person->tailOrder;
        person->tailOrder = temp;
    }

    return 1;
}

void PopOrder (Customer *baii){ //Pop semua orderan customer setelah checkout biar popcustomer aman :)

    //pophead

    while (baii->headOrder){

        if ((baii->headOrder) == (baii->tailOrder)){
            baii->headOrder = baii->tailOrder = NULL;
            free(baii->headOrder);
        }

        else {

            Dish *baibai = baii->headOrder;
            baii->headOrder = baibai->next;
            (baii->headOrder)->prev = NULL;
            baibai->next = NULL;
            free(baibai);
        }
    }

}

void PopCustomer(int idx, Customer *baii){ //Pop customer 

    //Jika cuma satu elemen
    if (baii == headCustomer[idx] && baii == tailCustomer[idx]){
        headCustomer[idx] = tailCustomer[idx] = NULL;
        free(baii);
    }

    else if (baii == headCustomer[idx]){
        headCustomer[idx] = baii->next;
        headCustomer[idx]->prev = NULL;
        baii->next = NULL;
        free(baii);

    }

    else if (baii == tailCustomer[idx]){
        tailCustomer[idx] = baii->prev;
        tailCustomer[idx]->next = NULL;
        baii->prev = NULL;
        free(baii);

    }

    else {
        //baii udah ketahuan di alamat mana

        (baii->prev)->next = baii->next;
        (baii->next)->prev = baii->prev;
        baii->next = NULL;
        baii->prev = NULL;
        free(baii);
    }



}

int Checks(char * name){ //Ini buat option Checkout

    int idx = DJB((char *) name);
    
    Customer *baii = headCustomer[idx];
    while (strcmp(name, baii->name) != 0) baii = baii->next;

    if (!(baii->headOrder)) return 0; //Gaada yang diorder
    else {

        Dish *bill = baii->headOrder;
        int i = 1;
        //Print full menu
        while (bill){
            printf ("[%d] %-20s x%d\n", i, bill->name, bill->price*bill->stock);
            bill = bill->next;
            i++;
        }

        //popAll
        PopOrder(baii);
        //popCustomer
        PopCustomer(idx, baii);

    }
    return 1;

}

void CLS(){ //CLS
    puts("\n\n\n\n\n\n\n\n\n\n");
}

void PrintSplash(){ //Print splash

    FILE *oof = fopen("splash-screen.txt", "r");
    if (!oof) puts("Splash not found :(");
    else {
        char temp[300];
        while (!feof(oof)){
            fscanf(oof, "#%[^\n]\n", temp);
            printf ("%s\n", temp);
        }
    }
    fclose(oof);	
}
