#include <windows.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>




char reserved_num[30] = {};
char reserved_alph[30] = {};
char customer_id[30][14] = {}, customer_name[30][50] = {}, customer_phone[30][12] = {};
float total_price = 0, base_price = 0;




struct Destination  {
    char *location;
    float distance;
};


struct Details {
    char customer_name[400];
    int customer_tracker;
    char customer_number[14];
    char customer_ic[14];
    char bus_date[11];
    char bus_time[5];
    char gender;
    int depart;
    int destination;
};
struct Favorite {
    char customer_ic[14];
    char seat_alph;
    int seat_id;
    struct Details fav_customer_detail;
};



struct Destination destination[9] = {
    {"JOHOR", 90},
    {"SELANGOR", 171},
    {"KEDAH", 353},

    {"Selangor - Kedah", 180.1801802},
    {"Selangor - Johor", 342.1},
    {"Selangor - Kedah", 371.6},

    {"Kedah - Kedah", 180.1801802},
    {"Kedah - Selangor", 371.6},
    {"Kedah - Johor", 706.4},

    };
struct Details customer_detail[30];
// struct Favorite fav_trip[30] = {{"030520100839", 'A',1,0, "1010"}};
struct Favorite fav_trip[30];
// int favorite_trip_size =  sizeof fav_trip / sizeof fav_trip[0];
// struct order_detail customer_detail[30];


int order_tracker = 0, favorite_trip_tracker = 0;
int customer_tracker = 1;

int reserved_checker(char target_alph, int target_id)   {
 
    for (int i = 0; i < order_tracker + 1; i++)    {
        if (target_alph == reserved_alph[i] && target_id == reserved_num[i])    {
            return customer_detail[i].customer_tracker;
        }
        
    }
    return -1;
}

void bus_diagram()  {
    char seat_alph[3] = {'A', 'B', 'C'};
    printf("\nBus Seats Diagram (A - Single seat / BC - Couple Seat / X - Unavailable / (M) - Male / (F) - Female): \n\n");
    for (int i = 0; i < 10; i++)    {
        for (int j = 0; j < 3; j++) {
            switch (j)  {
                case 1: printf("\t");break;
                case 2: printf(" ");break;
                default: printf("\n");
            }
            int reserved_check = reserved_checker(seat_alph[j], i+1);
        //    printf("%d", reserved_check);
            
            if (reserved_check == -1 )   {
                printf("%c%d", seat_alph[j], i+1);
            }   else    {
                if (j != 0) {
                    printf("(%c)", customer_detail[reserved_check].gender);
                }   else    {
                    printf("X");
                }
            }
        }
    }
}



int seat_reservation()  {
    char target_seat = 'D';
    int target_id = 0;    
    int wanted_seat = 3;
    total_price = 0;
    printf("\nSeat wanted (1 - %d): ", 30-order_tracker);
    scanf(" %d", &wanted_seat);
    bus_diagram();
    for (int i = 0; i < wanted_seat; i++)    {
        printf("\nSelect seat (%d / %d): ", i+1, wanted_seat);
        scanf(" %1c%2d", &target_seat, &target_id);    

        if (reserved_checker(target_seat, target_id) == -1)  {
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
        printf("Checking for customer %d: %s", i, customer_detail[i].customer_ic);
        printf("%c\n", customer_detail[i].gender);
    }
}


void customer_list_update(char ic[14], char name[100], char phone[14], int gender, int depart, int destination, int fav_booking) {
    // printf("%d", order_tracker);
    strcpy(customer_id[order_tracker], ic);
    
    // strcpy(customer_detail[order_tracker].customer_ic, ic);


    //  char *customer_name;
    // int customer_tracker;
    // char *customer_number;
    // char *customer_ic;
    // char *bus_date;
    // char *bus_time;
    // char gender;


    strcpy(customer_detail[order_tracker].customer_ic, ic);
    strcpy(customer_detail[order_tracker].customer_name, name);
    customer_detail[order_tracker].customer_tracker = order_tracker;
    strcpy(customer_detail[order_tracker].customer_number, phone);
    strcpy(customer_detail[order_tracker].bus_date, "12-04-2024");
    strcpy(customer_detail[order_tracker].bus_time, "1010");
    customer_detail[order_tracker].depart = depart;
    customer_detail[order_tracker].destination = destination;


    strcpy(customer_name[order_tracker], name);
    strcpy(customer_phone[order_tracker], phone);

    if (gender == 1)    {
        customer_detail[order_tracker].gender = 'M';
    }   else    {
        customer_detail[order_tracker].gender = 'F';
    }

    char buffer[1024];
    FILE *database = fopen("database.json", "a");
    // fprintf(database, "\n%s", customer_detail[order_tracker].customer_ic);
    fprintf(database, "%s,%c,%d,%s,%s,%c,%d,%d,%d,%s,%s\n",customer_detail[order_tracker].customer_ic,
    reserved_alph[order_tracker], 
    reserved_num[order_tracker],
    customer_detail[order_tracker].customer_number,
    customer_detail[order_tracker].customer_name,
    customer_detail[order_tracker].gender,
    customer_detail[order_tracker].customer_tracker,
    customer_detail[order_tracker].depart,
    customer_detail[order_tracker].destination,
    customer_detail[order_tracker].bus_date,
    customer_detail[order_tracker].bus_time);
    fclose(database);

    

    
    


    printf("\nName: %s\n", customer_detail[order_tracker].customer_name);
    printf("Customer Tracker ID: %d\n", customer_detail[order_tracker].customer_tracker);
    printf("Phone Number: %s\n", customer_detail[order_tracker].customer_number);
    printf("IC Number: %s\n", customer_detail[order_tracker].customer_ic);
    printf("Trip Date: %s\n", customer_detail[order_tracker].bus_date);
    printf("Departure Time: %s\n", customer_detail[order_tracker].bus_time);
    if (fav_booking == 0)  {
        int fav;
    printf("\n\nSAVE AS FAVORITE TRIP (1 - Yes Please / 0 - No Thanks)? ");
    scanf("%d", &fav);
    if (fav == 1)   {
        strcpy(fav_trip[favorite_trip_tracker].customer_ic, ic);
        fav_trip[favorite_trip_tracker].seat_alph = reserved_alph[customer_detail[order_tracker].customer_tracker];
        fav_trip[favorite_trip_tracker].seat_id = reserved_num[customer_detail[order_tracker].customer_tracker];
        strcpy(fav_trip[favorite_trip_tracker].fav_customer_detail.customer_number, phone);
        strcpy(fav_trip[favorite_trip_tracker].fav_customer_detail.customer_name, name);
        strcpy(fav_trip[favorite_trip_tracker].fav_customer_detail.bus_time, "1010");
        strcpy(fav_trip[favorite_trip_tracker].fav_customer_detail.bus_date, "12-04-2024");
        fav_trip[favorite_trip_tracker].fav_customer_detail.depart = depart;
        fav_trip[favorite_trip_tracker].fav_customer_detail.destination = destination;


        FILE *favorite_trip_database = fopen("favorite_trip_database.log", "a");
        fprintf(favorite_trip_database, "%s,%c,%d,%s,%s,%s,%s,%d,%d\n", 
        fav_trip[favorite_trip_tracker].customer_ic,
        fav_trip[favorite_trip_tracker].seat_alph,
        fav_trip[favorite_trip_tracker].seat_id,
        fav_trip[favorite_trip_tracker].fav_customer_detail.customer_number,
        fav_trip[favorite_trip_tracker].fav_customer_detail.customer_name,
        fav_trip[favorite_trip_tracker].fav_customer_detail.bus_time,
        fav_trip[favorite_trip_tracker].fav_customer_detail.bus_date,
        fav_trip[favorite_trip_tracker].fav_customer_detail.depart,
        fav_trip[favorite_trip_tracker].fav_customer_detail.destination


        );
        fclose(favorite_trip_database);



        favorite_trip_tracker++;
    }
    }
    order_tracker++;
}

int select_destination()    {
    // banner();
    int depart, desti;
    
      time_t t = time(NULL);
  struct tm tm = *localtime(&t);
    printf("\nnow: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    for (int i = 0; i < 3; i++) {
        if (i % 3 == 0){printf("\n");}
        printf("\n%d - %s", i+1, destination[i].location);
    }
    printf("\nDeparture -> ");
    scanf(" %d", &depart);
    printf("Destination -> ");
    scanf(" %d", &desti);
    int route[2] = {depart -1, desti-1};
    system("cls");
    // base_price = 12;
    base_price = ((3.33 * destination[route[0]].distance) + (3.33 * destination[route[1]].distance)) / 30;
    // base_price = 3.33 * 2 * destination[desti-1].distance / 30;
    printf("\n%s -> %s", destination[route[0]].location, destination[route[1]].location);
    printf("\nPrice per ticket: RM%.0f\n", base_price);

    return *route;
}

void payment(int seats, int depart, int destination)  {
    
    char name[100] = "", ic[14] = "", phone[14] = "";
    int gender;
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
    printf("1 - Male / 2 - FEMALE >> ");
    scanf(" %d", &gender);
    if (ic != "" || name != "" || phone != "" || (gender > 0 && gender < 3))  {
        for (int i = 0; i < seats; i++) {
            customer_list_update(ic, name, phone, gender, depart, destination, 0);
            // order_tracker++;
        }
        
        

    } else  {
        printf("Invalid payment!");
    }
    
    show_customers();
    
    
}




void order_check(char target_id[12]) {
    
    printf("\nDetails for customer: %s\n", target_id);
    for (int i = 0; i < order_tracker; i++)    {
        if (strcmp(target_id, customer_detail[i].customer_ic) == 0)    {
            printf("\n\n");
            printf("\nIc Number: %s", customer_detail[i].customer_ic);
            printf("\nName: %s", customer_detail[i].customer_name);
            printf("\nPhone: %s", customer_detail[i].customer_number);
            printf("\nSeat: %c%d", reserved_alph[customer_detail[i].customer_tracker], reserved_num[customer_detail[i].customer_tracker]);
            printf("\nTrip: %s -> %s", destination[customer_detail[i].depart].location, destination[customer_detail[i].destination].location);
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
printf("Developed by Syntax Error");
   
}


// favorite booking function
void favorite_trip()    {
    char ic[14];
    int trip_id;
    printf("Enter Your IC Number: ");
    scanf(" %s", ic);
    for (int i = 0; i < 30; i++)    {
        if (strcmp(fav_trip[i].customer_ic, ic) == 0)   {
            printf("%s\n", fav_trip[i].fav_customer_detail.customer_number);
            printf("[ %d ] %s -> %s (%c%d) @ Time: %s\n", i+1, destination[fav_trip[i].fav_customer_detail.depart].location, destination[fav_trip[i].fav_customer_detail.destination].location, fav_trip[i].seat_alph, fav_trip[i].seat_id, fav_trip[i].fav_customer_detail.bus_time);
        }
    }
    printf("\n\nTrip >> ");
    scanf("%d", &trip_id);
    trip_id--;
    int reserved_check = reserved_checker(fav_trip[trip_id].seat_alph, fav_trip[trip_id].seat_id);
    if (reserved_check == -1)   {
        reserved_alph[order_tracker] = fav_trip[trip_id].seat_alph;
        reserved_num[order_tracker] = fav_trip[trip_id].seat_id;
        // customer_list_update(char ic[14], char name[100], char phone[14], int gender, int trip, int fav_trip)
        customer_list_update(fav_trip[trip_id].customer_ic, fav_trip[trip_id].fav_customer_detail.customer_name, fav_trip[trip_id].fav_customer_detail.customer_number, fav_trip[trip_id].fav_customer_detail.gender, fav_trip[trip_id].fav_customer_detail.depart,fav_trip[trip_id].fav_customer_detail.destination, 1);
    }   else {
        system("cls");
        printf("\nYOUR FAVORITE SEAT IS NOT AVAILABLE! PLEASE CHOOSE ANOTHER SEAT!\n");
        
        int seats = seat_reservation();

        payment(seats, fav_trip[trip_id].fav_customer_detail.depart,fav_trip[trip_id].fav_customer_detail.destination);
    }
    }

// test database function
void test_database()    {
    char buffer[1024];
    FILE *database = fopen("database.json", "r");
    while (fgets(buffer, sizeof buffer, database))  {
        printf("IC: %s\n", strtok(buffer, ","));
        printf("Seat: %s", strtok(NULL, ","));
        printf("%s\n", strtok(NULL, ","));
        printf("Phone Number: %s\n", strtok(NULL, ","));
        printf("Name: %s\n", strtok(NULL, ","));
        
    }
    // fprintf(database, "");
    // while (fgetc(buffer, 1024, database))   {
    //     printf("%s", buffer[0]);
    // }
    fclose(database); 
}

// keep track on trip
void trip_tracker()   {
    int target_destination;
    char *location;
    
    char ic[14];
    printf("Enter your IC Number: ");
    scanf(" %s", ic);
    for (int i = 0; i < order_tracker + 1; i++) {
        if (strcmp(ic, customer_detail[i].customer_ic) == 0)    {
            target_destination = customer_detail[i].destination;
            banner();
            printf("\n\nYour Trip: %s -> %s\n", destination[customer_detail[i].depart].location, destination[customer_detail[i].destination].location);
            break;
        }   else    {
            banner();
            printf("IC Number not found!");
            return;
        }
    }
    while (1)   {
        char buffer[1024];
    FILE *current_location = fopen("location.log", "r");
        fgets(buffer, sizeof(buffer), current_location);
        printf("\rCurrent location: %.10s", buffer);
        if (strcmp(buffer, destination[target_destination].location) == 0)    {
            for (int i = 0; i < 20; i++) {
                Beep(1000,500);
            }
            // sleep(10);
            // sound(100);
            fclose(current_location);
            break;
        }
        
        sleep(1/2);
        
        fclose(current_location);
    }
}

// init database and load all data
void initialize_database()  {
    printf("\nloading database . . . .");
    char buffer[1024];
    FILE *database = fopen("database.json", "r");
    while (fgets(buffer, sizeof buffer, database)) {


            // char customer_name[400];
            // int customer_tracker;
            // char customer_number[14];
            // char customer_ic[14];
            // char bus_date[10];
            // char bus_time[4];
            // char gender;
            // int trip;



        // 030520100839,B,1,0108712675,MUHAMMAD NAJWAN BIN HASSAN,M,1,12-04-2024,1010
        char alph[1], gender[1];
        strcpy(customer_detail[order_tracker].customer_ic, strtok(buffer, ",")); // customer ic
        strcpy(alph, strtok(NULL, ",")); // convert customer seat (string -> char)
        reserved_alph[order_tracker] = *alph; // customer seat
        reserved_num[order_tracker] = atoi(strtok(NULL, ",")); // customer seat id
        strcpy(customer_detail[order_tracker].customer_number, strtok(NULL, ",")); // customer phone number
        strcpy(customer_detail[order_tracker].customer_name, strtok(NULL, ",")); // customer name
        strcpy(gender, strtok(NULL, ",")); // convert customer gender (string -> char)
        customer_detail[order_tracker].gender = *gender; // customer gender
        customer_detail[order_tracker].customer_tracker = order_tracker; // customer order tracker
        customer_detail[order_tracker].depart = atoi(strtok(NULL, ",")); // customer depart id
        customer_detail[order_tracker].destination = atoi(strtok(NULL, ",")); // customer destination id
        // strcpy(customer_detail[order_tracker].bus_date, strtok(NULL, ",")); // customer trip date
        // strcpy(customer_detail[order_tracker].bus_time, strtok(NULL, ",")); // customer trip time
        order_tracker++;
        // printf("%s", strtok(NULL, ","));
        // printf("%s", strtok(NULL, ","));

    }
    fclose(database);
    

    FILE *favorite_trip_database = fopen("favorite_trip_database.log", "r");
    while (fgets(buffer, sizeof(buffer), favorite_trip_database))   {
        char alph[1], gender[1];
        strcpy(fav_trip[favorite_trip_tracker].customer_ic, strtok(buffer, ","));
        strcpy(alph, strtok(NULL, ","));
        fav_trip[favorite_trip_tracker].seat_alph = * alph;
        fav_trip[favorite_trip_tracker].seat_id = atoi(strtok(NULL, ","));
        strcpy(fav_trip[favorite_trip_tracker].fav_customer_detail.customer_number, strtok(NULL, ","));
        strcpy(fav_trip[favorite_trip_tracker].fav_customer_detail.customer_name, strtok(NULL, ","));
        strcpy(fav_trip[favorite_trip_tracker].fav_customer_detail.bus_time, strtok(NULL, ","));
        strcpy(fav_trip[favorite_trip_tracker].fav_customer_detail.bus_date, strtok(NULL, ","));
        fav_trip[favorite_trip_tracker].fav_customer_detail.depart = atoi(strtok(NULL, ","));
        fav_trip[favorite_trip_tracker].fav_customer_detail.destination = atoi(strtok(NULL, ","));
        favorite_trip_tracker++;
    }
// printf("%c%d -> %c", reserved_alph[0],reserved_num[0], customer_detail[0].gender);
}


// main function
void main()  {
   
    
    banner();
    initialize_database();
    // scanf("%d");
    while (1){
        
        int option;
        
        printf("\n\nOption (1 - Booking / 2 - Exit / 3 - Reservation Check / 4 - Favorite Trip) / 5 - Trip Tracker>> ");
        scanf(" %d", &option);
        if (option == 2)    {
            banner();
            break;
        }   else if (option == 1)   {
            
            banner();
            int trip[] = {select_destination()};
            int seats = seat_reservation();
        
            payment(seats, trip[0], trip[1]);
        }   else if (option == 3)   {
            char target_id[12];
            printf("Enter IC Number: ");
            scanf(" %s", target_id);
            banner();
            order_check(target_id);
            continue;
        }   else if (option == 4)   {
            favorite_trip();
        } else if (option == 5) {
            trip_tracker();
            
        } else    {
            continue;
        }
        
     
    }
    }