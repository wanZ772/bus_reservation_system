#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char reserved_num[30] = {};
char reserved_alph[30] = {};
char customer_id[30][14] = {}, customer_name[30][50] = {}, customer_phone[30][12];
int order_tracker = 0;
int customer_tracker = 1;

int reserved_checker(char target_alph, int target_id)   {
 ;
    for (int i = 0; i < order_tracker + 1; i++)    {
        if (target_alph == reserved_alph[i] && target_id == reserved_num[i])    {
            return 1;
        }
        
    }
    return 0;
}

void bus_diagram()  {
    char seat_alph[3] = {'A', 'B', 'C'};
    printf("\nBus Seats Diagram: \n\n");
    for (int i = 0; i < 10; i++)    {
        for (int j = 0; j < 3; j++) {
            switch (j)  {
                case 1: printf("\t");break;
                case 2: printf(" ");break;
                default: printf("\n");
            }
            int reserved_check = reserved_checker(seat_alph[j], i+1);
            if (reserved_check == 0 )   {
                printf("%c%d", seat_alph[j], i+1);
            }   else    {
                printf("X");
            }
        }
    }
}



int seat_reservation()  {
    char target_seat = 'D';
    int target_id = 0;    
    printf("\nSelect seat: ");
    scanf(" %1c%1d", &target_seat, &target_id);
    system("cls");
    printf("\nReserving seat: %c%d", target_seat, target_id);

    int reserved_check = reserved_checker(target_seat, target_id);
    if (reserved_check == 0) {
        reserved_alph[order_tracker] = target_seat;
        reserved_num[order_tracker] = target_id;
        
        return 1;
    }   else    {
        return 0;
    }
}

void show_customers()   {
    for (int i = 0; i < 30; i++)    {
        printf("Checking for customer %d: %s\n", i, customer_id[i]);
    }
}


void customer_list_update(char ic[14], char name[100], char phone[14]) {
    // printf("%d", order_tracker);
    strcpy(customer_id[order_tracker], ic);
    strcpy(customer_name[order_tracker], name);
    strcpy(customer_phone[order_tracker], phone);
    printf("\nYour name is: %s\n", name);
}

void payment()  {
    char name[100] = "", ic[14] = "", phone[14] = "";
    // printf("Current tracker: %d\n", order_tracker);
    printf("\nName: ");
    scanf(" %s", name);
    printf("Ic Number: ");
    scanf("%s", ic);
    printf("Phone Number: ");
    scanf(" %s", phone);
    if (ic != "" || name != "" || phone != "")  {
        
        customer_list_update(ic, name, phone);
        order_tracker++;

    } else  {
        printf("Invalid payment!");
    }
    
    show_customers();
    
}




void order_check(char target_id[12]) {
    system("cls");
    printf("\nDetails for customer: %s\n", target_id);
    for (int i = 0; i < 30; i++)    {
        if (strcmp(target_id, customer_id[i]) == 0)    {
            printf("\n\n");
            printf("\nIc Number: %s", customer_id[i]);
            printf("\nName: %s", customer_name[i]);
            printf("\nPhone: %s", customer_phone[i]);
            printf("\nSeat: %c%d", reserved_alph[i], reserved_num[i]);
        }
    }
}

void main()  {

    while (1){

        int option;
        printf("\n\nOption (1 - Select Seat / 2 - Exit / 3 - Reservation Check)>> ");
        scanf(" %d", &option);
        if (option == 2)    {
            break;
        }   else if (option == 1)   {
            system("cls");
        }   else if (option == 3)   {
            char target_id[12];
            printf("Enter IC Number: ");
            scanf(" %s", target_id);
            order_check(target_id);
            continue;
        }
        bus_diagram();
        int reservation_result = seat_reservation();
        if (reservation_result ==  1)   {
            payment();
        }   else    {
            printf("\nSEAT RESERVATION FAILED! PLEASE TRY ANOTHER SEAT!\n");
        }
    }
    
}