// ELEC2645 Unit 2 Project Template
// Command Line Application Menu Handling Code

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "funcs.h"

Saving global_value = {0};  //Static struct, all members initialized to 0
Saving *value = &global_value; // Pointer pointing to a static structure

/* Prototypes mirroring the C++ version */
static void main_menu(void);                 /* runs in the main loop */
static void print_main_menu(void);           /* output the main menu description */
static void Calculation_buck_menu(void);          /* Select the converter's calculation menu.*/
static void Calculation_boost_menu(void); 
static void Calculation_buck_boost_menu(void); 
static void Calculation_menu_name(void);   /* output the calculation menu description */
static int  get_user_input(void);            /* get a valid integer menu choice */
static void select_menu_item(int input,Saving *value);     /* run code based on user's choice */
/*Different converters have different corresponding formulas depending on the calculation menu option selected.*/
static void select_calculation_buck_menu_item(int input); 
static void select_calculation_boost_menu_item(int input);
static void select_calculation_buck_boost_menu_item(int input);
static void go_back_to_main(void);           /* wait for 'b'/'B' to continue , return to main menu*/
static int  is_integer(const char *s);       /* validate integer string */

static void get_mode(char *mode, int size);/*Determine whether the converter is in CCM or DCM*/

int SIZE=50;

int main(void)
{   
    /* this will run forever until we call exit(0) in select_menu_item() */
    for(;;) {
        main_menu();
    }
    /* not reached */
    return 0;
}

static void main_menu(void)
{
    print_main_menu();

    {
        int input = get_user_input();
        select_menu_item(input,value);
    }
    
}

static int get_user_input(void)//Obtain the number entered by the user.
{
    enum { MENU_ITEMS = 5 };   /* 1..4 = items, 5 = Exit */
    char buf[128];
    int valid_input = 0;
    int value = 0;

    do {
        printf("\nSelect item: ");
        if (!fgets(buf, sizeof(buf), stdin)) {
            /* EOF or error; bail out gracefully */
            puts("\nInput error. Exiting.");
            exit(1);
        }

        // strip trailing newline
        buf[strcspn(buf, "\r\n")] = '\0';

        if (!is_integer(buf)) {
            printf("Enter an integer!\n");
            valid_input = 0;
        } else {
            value = (int)strtol(buf, NULL, 10);
            if (value >= 1 && value <= MENU_ITEMS) {
                valid_input = 1;
            } else {
                printf("Invalid menu item!\n");
                valid_input = 0;
            }
        }
    } while (!valid_input);

    return value;
}

static int get_user_input_cal(void)//Obtain the number entered by the user.
{
    enum { MENU_ITEMS = 6 };   /* 1..5 = items, 6 = Exit */
    char buf[128];
    int valid_input = 0;
    int value = 0;

    do {
        printf("\nSelect item: ");
        if (!fgets(buf, sizeof(buf), stdin)) {
            /* EOF or error; bail out gracefully */
            puts("\nInput error. Exiting.");
            exit(1);
        }

        // strip trailing newline
        buf[strcspn(buf, "\r\n")] = '\0';

        if (!is_integer(buf)) {
            printf("Enter an integer!\n");
            valid_input = 0;
        } else {
            value = (int)strtol(buf, NULL, 10);
            if (value >= 1 && value <= MENU_ITEMS) {
                valid_input = 1;
            } else {
                printf("Invalid menu item!\n");
                valid_input = 0;
            }
        }
    } while (!valid_input);

    return value;
}

static void select_menu_item(int input, Saving *value)
{

    switch (input) {
        case 1:
            if (confirm_action() == 1) {
                Calculation_buck_menu();
            }
            break;
        case 2:
         if (confirm_action() == 1) {
                Calculation_boost_menu();
            }
            break;
        case 3:
            if (confirm_action() == 1) {
                Calculation_buck_boost_menu();
            }
            break;
        case 4:
            read_file(value);
            go_back_to_main();         
            break;
        default:
            printf("Bye!\n");
            exit(0);
    }
}

static void select_calculation_buck_menu_item(int input)
{
    char mode [SIZE];
    switch (input) {
        case 1:
            if (confirm_action() == 1) {
                do {
                    get_mode(mode, SIZE);
                    calculate_buck_dutyratio(mode, value);
                } while (ask_recalculate());   // Evaluate user input
            }
            break;
        case 2:
            if (confirm_action() == 1) {
                do {
                    calculate_buck_ripple_current(value);
                } while (ask_recalculate());
            } 
            break;
        case 3:
            if (confirm_action() == 1) {
                do {
                    calculate_buck_ripple_voltage(value);
                } while (ask_recalculate()); 
            }
            break;
        case 4:
            if (confirm_action() == 1) {
                do {
                    calculate_buck_inductance(value);
                } while (ask_recalculate());
            } 
            break;
        case 5:
            if (confirm_action() == 1) {
                do {
                    calculate_buck_capacitor(value);
                } while (ask_recalculate()); 
            }            
            break;
        default:
            printf("Bye!\n");
            exit(0);
    }
}

static void Calculation_buck_menu(void)
{
    int input;

    while (1) {
        Calculation_menu_name();
        input = get_user_input_cal();
        if (input == 6) {
            return;
        }
    select_calculation_buck_menu_item(input);
    }


    select_calculation_buck_menu_item(input);
}

static void select_calculation_boost_menu_item(int input)

{
    char mode [SIZE];
    switch (input) {
        case 1:
            if (confirm_action() == 1) {
                do {
                    get_mode(mode, SIZE);
                    calculate_boost_dutyratio(mode,value);
                } while (ask_recalculate()); 
            } 
            break;
        case 2:
            if (confirm_action() == 1) {
                do {
                    calculate_boost_ripple_current(value);
                } while (ask_recalculate());  
            }             
            break;
        case 3:
            if (confirm_action() == 1) {
                do {
                    calculate_boost_ripple_voltage(value);
                
                } while (ask_recalculate()); 
            }    
            break;
        case 4: 
            if (confirm_action() == 1) {
                do {
                    calculate_boost_inductance(value);
                } while (ask_recalculate());
            }          
            break;
        case 5:
            if (confirm_action() == 1) {
                do {
                    calculate_boost_capacitor(value);
                } while (ask_recalculate()); 
            }              
            break;
        default:
            printf("Bye!\n");
            exit(0);
    }
}

static void Calculation_boost_menu(void)
{
    int input;

    while (1) {
        Calculation_menu_name();
        input = get_user_input_cal();

        if (input == 6) {
            return;
        }
    select_calculation_boost_menu_item(input);
    }
}

static void select_calculation_buck_boost_menu_item(int input)

{
    char mode [SIZE];
    switch (input) {
        case 1:
            if (confirm_action() == 1) {
                do {
                    get_mode(mode, SIZE);
                    calculate_buck_boost_dutyratio(mode,value);
                } while (ask_recalculate()); 
            }          
            break;
        case 2:
            if (confirm_action() == 1) {
                do {
                    calculate_buck_boost_ripple_current(value);;
                } while (ask_recalculate());
            }   
            break;
        case 3:
            if (confirm_action() == 1) {
                do {
                    calculate_buck_boost_ripple_voltage(value);
                } while (ask_recalculate());
            }            
            break;
        case 4:
            if (confirm_action() == 1) {
                do {
                    calculate_buck_boost_inductance(value);
                } while (ask_recalculate());
            }            
            break;
        case 5:
            if (confirm_action() == 1) {
                do {
                    calculate_buck_boost_capacitor(value);
                } while (ask_recalculate());
            }             
            break;
        default:
            printf("Bye!\n");
            exit(0);
    }
}

static void Calculation_buck_boost_menu(void)
{
    Calculation_menu_name();  // Display Calculation Menu
    int input = get_user_input_cal();
    select_calculation_buck_boost_menu_item(input);
}

static void print_main_menu(void)//Main menu
{
    printf("\n----------- Main menu -----------\n");
    printf("\n"
           "\t\t\t\t\t\t\n"
           "\t1. Buck converter\t\t\n"
           "\t2. Boost converter \t\t\n"
           "\t3. Buck-boost converter \t\t\n"
           "\t4. Load last record \t\t\n"
           "\t5. Exit\t\t\t\t\n"
           "\t\t\t\t\t\t\n");
    printf("---------------------------------------------\n");
}

static void Calculation_menu_name(void)//Calculation menu
{
    printf("\n----------- Calculation menu -----------\n");
    printf("\n"
           "\t\t\t\t\t\t\n"
           "\t1. Calculate duty ratio\t\t\n"
           "\t2. Calculate ripple current \t\t\n"
           "\t3. Calculate ripple voltage \t\t\n"
           "\t4. Calculate inductance value \t\t\n"
           "\t5. Calculate capacitance value \t\t\n"
           "\t6. Exit\t\t\t\t\n"
           "\t\t\t\t\t\t\n");
    printf("---------------------------------------------\n");
}

static void go_back_to_main(void)//Return to main menu
{
    char buf[64];
    do {
        printf("\nEnter 'b' or 'B' to go back to main menu: ");
        if (!fgets(buf, sizeof(buf), stdin)) {
            puts("\nInput error. Exiting.");
            exit(1);
        }
        buf[strcspn(buf, "\r\n")] = '\0'; /* strip newline */
    } while (!(buf[0] == 'b' || buf[0] == 'B') || buf[1] != '\0');

}

/* Return 1 if s is an optional [+/-] followed by one-or-more digits, else 0. */
static int is_integer(const char *s)//Determine whether the number is an integer.
{
    if (!s || !*s) return 0;

    /* optional sign */
    if (*s == '+' || *s == '-') s++;

    /* must have at least one digit */
    if (!isdigit((unsigned char)*s)) return 0;

    while (*s) {
        if (!isdigit((unsigned char)*s)) return 0;
        s++;
    }
    return 1;
}

static void get_mode(char *mode, int size)//Determine whether the converter is in CCM or DCM
{
    while (1){
        printf("\nEnter your mode CCM or DCM: ");
        fgets(mode, size, stdin);
        mode[strcspn(mode, "\n")] = '\0';

        for (char *p = mode; *p; p++) {
            *p = toupper((unsigned char)*p);
        }

        if (strcmp(mode, "CCM") == 0) {
            printf("You selected CCM\n");
            break;
        }
        else if (strcmp(mode, "DCM") == 0) {
            printf("You selected DCM\n");
            break;
        }
        else {
            printf("Please enter CCM or DCM.\n");
        }   
    }
}
