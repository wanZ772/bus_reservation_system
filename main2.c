#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

char reserved_num[30] = {};
char reserved_alph[30] = {};
char customer_id[30][14] = {}, customer_name[30][50] = {}, customer_phone[30][12] = {};
float total_price = 0, base_price = 0;




struct Destination  {
    char *location;
    float distance;
};

struct Destination destination[9] = {
    {"Johor - Johor", 180.1801802},
    {"Johor - Selangor", 342.1},
    {"Johor - Kedah", 706.4},

    {"Selangor - Kedah", 180.1801802},
    {"Selangor - Johor", 342.1},
    {"Selangor - Kedah", 371.6},

    {"Kedah - Kedah", 180.1801802},
    {"Kedah - Selangor", 371.6},
    {"Kedah - Johor", 706.4},

    };

struct order_detail {
    char *customer_name;
    int customer_tracker;
    char *customer_number;
    char *customer_ic;
};

// struct order_detail customer_detail[30];


int order_tracker = 0;
int customer_tracker = 1;

int reserved_checker(char target_alph, int target_id)   {
 
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
    int wanted_seat = 3;
    printf("\nSeat wanted (1 - %d): ", 30-order_tracker);
    scanf(" %d", &wanted_seat);
    for (int i = 0; i < wanted_seat; i++)    {
        printf("\nSelect seat (%d / %d): ", i+1, wanted_seat);
        scanf(" %1c%2d", &target_seat, &target_id);    

        if (reserved_checker(target_seat, target_id) == 0)  {
            reserved_alph[order_tracker + i] = target_seat;
            reserved_num[order_tracker + i] = target_id;
            total_price += base_price;
            // order_tracker++;
        }   else    {
            printf("\nSEAT RESERVED! PLEASE CHOOSE ANOTHER SEAT\n");
            --i;
            continue;
        }
    }
    system("cls");
    printf("\nReserving seat:");
        
        return wanted_seat;
 
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

void select_destination()    {
    // banner();
    int depart, desti;
      time_t t = time(NULL);
  struct tm tm = *localtime(&t);
    printf("\nnow: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0){printf("\n");}
        printf("\n%d - %s", i+1, destination[i].location);
    }
    printf("\nDeparture - Destination: ");
    scanf(" %d", &desti);
    system("cls");
    base_price = 3.33 * 2 * destination[desti-1].distance / 30;
    printf("\nPrice per ticket: RM%.2f\n", base_price);

    bus_diagram();
}

void payment(int seats)  {
    char name[100] = "", ic[14] = "", phone[14] = "";
    printf("\n##################################\n");
    printf("##\t      PAYMENT \t\t##\n");
    printf("##\tTotal Price: %.2f \t##\n", total_price);
    printf("##################################\n");
    printf("\nName: ");
    scanf(" %[^\n]%*c", name);
    printf("Ic Number: ");
    scanf("%s", ic);
    printf("Phone Number: ");
    scanf(" %s", phone);
    if (ic != "" || name != "" || phone != "")  {
        for (int i = 0; i < seats; i++) {
            customer_list_update(ic, name, phone);
            order_tracker++;
        }
        
        

    } else  {
        printf("Invalid payment!");
    }
    
    show_customers();
    
}




void order_check(char target_id[12]) {
    
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

void banner()   {
    

// printf(" ______                  ______                                                 _                     _                                     \n");
// printf("(____  \\                (_____ \\                                          _    (_)                   | |                 _                 \n");
// printf(" ____)  ) _   _   ___    _____) )  ____   ___   ____   ____  _   _  ____ | |_   _   ___   ____        \ \   _   _   ___ | |_   ____  ____   \n");
// printf("|  __  ( | | | | /___)  (_____ (  / _  ) /___) / _  ) / ___)| | | |/ _  ||  _) | | / _ \ |  _ \        \ \ | | | | /___)|  _) / _  )|    \ \n");
// printf("| |__)  )| |_| ||___ |        | |( (/ / |___ |( (/ / | |     \ V /( ( | || |__ | || |_| || | | |   _____) )| |_| ||___ || |__( (/ / | | | |\n");
// printf("|______/  \\____|(___/        |_| \\____)(___/  \\____)|_|    \_/  \_||_| \___)|_| \___/ |_| |_|  (______/  \__  |(___/  \___)\____)|_|_|_|\n");
// printf("                                                                                                            (____/                         \n");
 
system("cls");
printf(".-------------------------------------------------------------.\n");
printf("'------..-------------..----------..----------..----------..--.|\n");
printf("|       \\             ||          ||          ||          ||  ||\n");
printf("|        \\            ||          ||          ||          ||  ||\n");
printf("|    ..   ||  _    _  ||    _   _ || _    _   ||    _    _||  ||\n");
printf("|    ||   || //   //  ||   //  // ||//   //   ||   //   //|| /||\n");
printf("|_.------\"''----------''----------''----------''----------''--'|\n");
printf(" |)|      |       |       |       |    |      mga|      ||==|  |\n");
printf(" | |      |  _-_  |       |       |    |  .-.    |      ||==| C|\n");
printf(" | |  __  |.'.-.' |   _   |   _   |    |.'.-.'.  |  __  | \"__=='\n");
printf(" '---------'|( )|'----------------------'|( )|'----------\"\"     \n");
printf("             '-'                          '-'\t");
printf("Developed by Sinners");
   
}

struct order_detail customer_detail[30];
// customer_detail[0] = {"Najwan", 0, "010", "03"};

void main()  {
   
    
    banner();

    while (1){
        
        int option;
        printf("\n\nOption (1 - Booking / 2 - Exit / 3 - Reservation Check)>> ");
        scanf(" %d", &option);
        if (option == 2)    {
            banner();
            break;
        }   else if (option == 1)   {
        
            banner();
        }   else if (option == 3)   {
            char target_id[12];
            printf("Enter IC Number: ");
            scanf(" %s", target_id);
            banner();
            order_check(target_id);
            continue;
        }
        select_destination();
        int seats = seat_reservation();
        
            payment(seats);
     
    }}