#include <stdio.h>
#include <stdlib.h>
// #include <string.h>

int tracker = 0;
int reserved[30] = {};

int reserved_seat_check(int id) {
    for (int i = 0; i < 30; i ++)   {
        if (id == reserved[i])  {
            return 1;
        }
    }
}  

void bus_diagram()  {
    int i = 1;
    printf("SEATS DIAGRAM: \n");
    while (i <= 30) {
        for (int j = 0; j < 3; j++) {
            switch (j)  {
                case 1: printf("\t"); break;
                case 2: printf(" "); break;
                default: printf("\n"); break;
            }
            if (reserved_seat_check(i) == 0)    {
                printf("%d", i);
            }   else    {
                printf("X");
            }
            i++;
        }
    }
}

void show_all_seats() {
    for (int i = 0; i < tracker; i++)   {
        printf("Reserved ID: %d\n", reserved[i]);
    }
}

int seat_reservation(int id) {
    printf("\nChecking for seat: %d\n", id);
    for (int i = 0; i < tracker + 1; i++)   {
        if (id == reserved[i]) {
            return 0;
        }
    }
    reserved[tracker] = id;
    tracker++;
    return 1;

}

void payment()  {
    char *name, *ic, *phone;
    printf("\nName: ");
    scanf("%s", &name);
    printf("\nIC: ");
    scanf("%s", &ic);
    printf("\nPhone Number: ");
    scanf("%s", &phone);

    if (name == "" || ic == "" || phone == "")  {
        printf("\nINVALID PAYMENT!\n");
        reserved[tracker] = 0;
        tracker--;
    }
}

void select_seat()  {
    int id;
    printf("\nSelect seat: ");
    scanf("%d", &id);
    if (id >= 1 && id <= 30)    {
        int reservation_result = seat_reservation(id);
        if (reservation_result == 1)    {
            // payment();
        } 
    }   else    {
        printf("Invalid seat!");
    }
        
}

int main()  {

    while (1)   {
        bus_diagram();
        select_seat();
        system("cls");
        
    }

}