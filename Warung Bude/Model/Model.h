struct Dish {
    char name[255];
    int price, stock;
    Dish *prev, *next;
}*headDish = NULL, *tailDish = NULL;

struct Customer {
    char name[255];
    Dish *headOrder, *tailOrder; //LL nya order;
    Customer *prev, *next; //prev next Hash Table
}*headCustomer[26], *tailCustomer[26];
