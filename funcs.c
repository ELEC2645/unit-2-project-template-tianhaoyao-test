#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
#include <ctype.h>
#include <math.h>
#include "funcs.h"



// Calculate Buck converter
void calculate_buck_dutyratio(char *mode,  Saving *value)//Calculate duty ratio
{
    input_valid_Vo(value);
    input_valid_Vi(value);
    input_valid_delta_i(value);

    save_record(value);

    if (strcmp(mode, "CCM") == 0) {
        value->K = value->Vo / value->Vi;    // Buck CCM
    } 
    else {
        value->K = (value->Vo * value->delta_i) / (value->Vi - value->Vo);    // Buck DCM
    }

    if (value->K < 0 || value->K > 1){
        printf("\nWarning: Duty ratio out of typical 0~1 range!\n");
    }
    else{    
        printf("Mode: %s\n", mode);
        printf("Duty Ratio K = %.6lf\n", value->K);
    }
}

void calculate_buck_ripple_current( Saving *value)//Calculate ripple current
{
    input_valid_duty_ratio(value);
    input_valid_Vo(value);
    input_valid_L(value);
    input_valid_fs(value);

    save_record(value);

    value->delta_i = (1 - value->K) * value->Vo * 1000 / (value->L * value->fs);//formula
    printf("Ripple current delta_i = %.6lf A\n", value->delta_i);
}

void calculate_buck_ripple_voltage( Saving *value)//Calculate ripple voltage
{
    input_valid_duty_ratio(value);
    input_valid_Vo(value);
    input_valid_L(value);
    input_valid_C(value);
    input_valid_fs(value);

    save_record(value);

    value->delta_v  = value->Vo * (1 - value->K) * 1000000000/ (8 * value->C * value->fs * value->fs * value->L);//formula
    printf("Ripple voltage delta_v  = %.6lf V\n", value->delta_v);
}

void calculate_buck_inductance( Saving *value)//Calculate inductance
{
    input_valid_duty_ratio(value);
    input_valid_Vo(value);
    input_valid_fs(value);
    input_valid_delta_i(value);

    save_record(value);

    value->L = (1 - value->K) * value->Vo * 1000 / (value->delta_i * value->fs);// formula
    printf("Required L = %.6lf mH\n", value->L);
}

void calculate_buck_capacitor( Saving *value)//Calculate capacitance
{
    input_valid_duty_ratio(value);
    input_valid_Vo(value);
    input_valid_fs(value);
    input_valid_delta_v(value);
    input_valid_L(value);

    save_record(value);
   
    value->C = value->Vo * (1 - value->K)* 1000/ (value->delta_v * value->fs * value->fs * 8 * value->L); //formula 
    printf("Capacitance C = %.6lfuF\n", value->C);
}

//BOOST
void calculate_boost_dutyratio(char *mode,  Saving *value)//Calculate duty ratio
{
    input_valid_Vo(value);
    input_valid_Vi(value);
    input_valid_delta_i(value);
    
    save_record(value);

    if (strcmp(mode, "CCM") == 0) {
       value->K = 1 - value->Vi / value->Vo;    // Boost CCM
    } 
    else {
        value->K = (value->Vo * value->delta_i - value->Vi * value->delta_i) / (value->Vi);    // Boost DCM
    }

    if (value->K < 0 || value->K > 1){
        printf("\nWarning: Duty ratio out of typical 0~1 range!\n");
    }
    else{    
        printf("Mode: %s\n", mode);
        printf("Duty Ratio K = %.6lf\n", value->K);
    }
   
}

void calculate_boost_ripple_current( Saving *value)//Calculate ripple current
{
    input_valid_duty_ratio(value);
    input_valid_Vi(value);
    input_valid_L(value);
    input_valid_fs(value);

    save_record(value);

    value->delta_i = (value->Vi * value->K) * 1000 / (value->L * value->fs);//formula
    printf("Ripple current delta_i = %.6lf A\n", value->delta_i);
}

void calculate_boost_ripple_voltage( Saving *value)//Calculate ripple voltage
{
    double Io;

    input_valid_duty_ratio(value);
    Io = get_user_input_value("Enter Io (A): ");
    input_valid_C(value);
    input_valid_Vo(value);
    input_valid_R(value);
    input_valid_fs(value);

    save_record(value);

    if (value->Vo == 0){    
        value->delta_v  = value->Vo * value->K * 1000000 / (value->C * value->fs * value->R);//formula
    }
    else{    
        value->delta_v  = Io * value->K * 1000000/ (value->C * value->fs);//formula
    }
    printf("Ripple voltage delta_v  = %.6lf V\n", value->delta_v);
}

void calculate_boost_inductance( Saving *value)//Calculate inductance
{
    input_valid_duty_ratio(value);
    input_valid_Vo(value);
    input_valid_Vi(value);
    input_valid_fs(value);
    input_valid_delta_i(value);

    save_record(value);

    value->L = (1 - value->K) * (value->Vo - value->Vi) * 1000 / (value->delta_i * value->fs);//formula
    printf("Required L = %.6lf mH\n", value->L);
}

void calculate_boost_capacitor( Saving *value)//Calculate capacitance
{
    input_valid_duty_ratio(value);
    input_valid_Vo(value);
    input_valid_fs(value);
    input_valid_delta_v(value);
    input_valid_R(value);  

    save_record(value);

    value->C = value->Vo * value->K * 1000000/ (value->delta_v * value->fs * value->R); //formula 
    printf("Capacitance C = %.6lf uF\n", value->C);
}

//Buck_boost
void calculate_buck_boost_dutyratio(char *mode,  Saving *value)//Calculate duty ratio
{
    input_valid_Vo(value);
    input_valid_Vi(value);
    input_valid_delta_i(value);
    
    save_record(value);

    if (strcmp(mode, "CCM") == 0) {
        value->K = value->Vo / (value->Vo + value->Vi);    // Buck_boost CCM
    } 
    else {
        value->K = (value->Vo * value->delta_i) / value->Vi;    // Buck_boost DCM
    }
    if (value->K < 0 || value->K > 1){
        printf("\nWarning: Duty ratio out of typical 0~1 range!\n");
    }
    else{    
        printf("Mode: %s\n", mode);
        printf("Duty Ratio K = %.6lf\n", value->K);
    }
   
}

void calculate_buck_boost_ripple_current( Saving *value)//Calculate ripple current
{
    input_valid_duty_ratio(value);
    input_valid_Vi(value);
    input_valid_L(value);
    input_valid_fs(value);
    
    save_record(value);

    if (value->K < 0 || value->K > 1){
        printf("Warning: Duty ratio out of typical 0~1 range!\n");
    }
    else{    
        value->delta_i = (value->Vi * value->K) / (value->L * value->fs);//formula
        printf("Ripple current delta_i = %.6lf A\n", value->delta_i);
    }
}

void calculate_buck_boost_ripple_voltage( Saving *value)//Calculate ripple voltage
{
    double Io;
    
    input_valid_duty_ratio(value);
    Io = get_user_input_value("Enter Io (A): ");
    input_valid_C(value);
    input_valid_Vo(value);
    input_valid_R(value);
    input_valid_fs(value);

    save_record(value);

    if (value->K < 0 || value->K > 1){
        printf("Warning: Duty ratio out of typical 0~1 range!\n");
    }
    else{    
        value->delta_v  = value->Vo * value->K * 1000000 / (value->C * value->fs * value->R);//formula
        printf("Ripple voltage delta_v  = %.6lf V\n", value->delta_v);
    }
}

void calculate_buck_boost_inductance( Saving *value)//Calculate inductance
{
    input_valid_duty_ratio(value);
    input_valid_Vo(value);
    input_valid_Vi(value);
    input_valid_fs(value);
    input_valid_delta_i(value);    

    save_record(value);

    if (value->Vo == 0) {
      value->L = value->Vi * value->K * 1000/ (value->fs * value->delta_i);// formula
    } 
    else {
        value->L  = value->Vo * 1000 * (1 - value->K) / (value->delta_i * value->fs);// formula
    }
    printf("Required L = %.6lf mH\n", value->L);
}

void calculate_buck_boost_capacitor( Saving *value)//Calculate capacitance
{
    input_valid_duty_ratio(value);
    input_valid_Vo(value);
    input_valid_fs(value);
    input_valid_delta_i(value);
    input_valid_R(value);  
    
    save_record(value);

    value->C = value->Vo * value->K * 1000000 / (value->delta_v * value->fs * value->R); //formula 
    printf("Capacitance C = %.6lf uF\n", value->C);
}

int ask_read_data(void)//Ask the user if they want to read the previous input
{
    int shouldContinue = 0;
    char ending;

    while(shouldContinue ==  0){
        printf("Do you want to read the last data?(Y/N):");
        scanf("%c", &ending);
        while(getchar()!= '\n');
        if(ending == 'Y'||ending == 'y'){
            shouldContinue = 1;
        }
        else if(ending == 'N'|| ending == 'n'){
            break; // jump out of do-while
        }
        else{
            printf("\nError, input(Y/N)\n");
        }   

    }
    return shouldContinue;
}

//Save record to file
void save_record( Saving *value) //Read inquiry
{
    FILE *filePtr;

    filePtr = fopen("record.txt", "w");

    if (filePtr != NULL) {
        fprintf(filePtr, " %.6lf %.6lf %.6lf %.6lf %.6lf %.6lf %.6lf %.6lf %.6lf",

                value->Vi,
                value->Vo,
                value->K,
                value->delta_i,
                value->delta_v,
                value->L,
                value->C,
                value->R,
                value->fs);

        fclose(filePtr);
    }
    else{
        printf("Warning: cannot open file!");
        exit(1);
    }
}

int read_file( Saving *value)
{
    int shouldContinue = ask_read_data();//return 0 for
    if (shouldContinue == 0) {
        return 0;
    }

    FILE *filePtr = fopen("record.txt", "r");
    if (!filePtr) {
        printf("Error: record.txt cannot open \n");
        return 0;
    }

    else{
        fscanf(filePtr, "%lf %lf %lf %lf %lf %lf %lf %lf %lf",
               &value->Vi,
               &value->Vo,
               &value->K,
               &value->delta_i,
               &value->delta_v,
               &value->L,
               &value->C,
               &value->R,
               &value->fs);
    
        fclose(filePtr);

        printf("Vin = %.6lf V\n", value->Vi);
        printf("Vout = %.6lf V\n", value->Vo);
        printf("K = %.6lf\n", value->K);
        printf("delta_I = %.6lf A\n", value->delta_i);
        printf("delta_V = %.6lf V\n", value->delta_v);
        printf("L = %.6lf mH\n", value->L);
        printf("C = %.6lf uF\n", value->C);
        printf("R = %.6lf ohm\n", value->R);
        printf("fs = %.6lf HZ\n", value->fs);

        return 1;
    }
}

double get_user_input_value(char *str)
{
    double value;
    int result;

    while (1) {
        printf("%s", str);

        result = scanf("%lf", &value);

        // Determine whether it is a number
        if (result != 1) {
            printf("Enter a valid number!\n");
            while (getchar() != '\n');//clear the buffer
            continue; // Continue looping
        }
        break; //  Exit the loop
    }

    while(getchar() != '\n');

    return value;
}

//Input validation functions
void input_valid_duty_ratio(Saving *value) //Ensure that user-entered values align with actual conditions.
{
    while (1) {
        value->K = get_user_input_value("\nEnter duty ratio K (0~1): ");
    
        if (value->K < 0 || value->K > 1) {
            printf("\nWarning: Duty ratio out of typical 0~1 range!\n");
        } 
        else {
            break;
         }
    }
}

void input_valid_Vi(Saving *value) //Ensure that user-entered values align with actual conditions.
{
    while (1) {
        value->Vi = get_user_input_value("\nEnter input voltage Vin (V): ");

        if (value->Vi <= 0) {
            printf("\nWarning: Vin must be > 0!\n");
        } 
        else {
            break;
        }
    }
}

void input_valid_Vo(Saving *value) //Ensure that user-entered values align with actual conditions.
{
    while (1) {
        value->Vo = get_user_input_value("\nEnter output voltage Vout (V): ");

        if (value->Vo <= 0) {
            printf("\nWarning: Vout must be > 0!\n");
        }
        else {
            break;
        }
    }
}

void input_valid_delta_i(Saving *value) //Ensure that user-entered values align with actual conditions.
{
    while (1) {
        value->delta_i = get_user_input_value("\nEnter inductor ripple current delta_i (A): ");

        if (value->delta_i < 0) {
            printf("\nWarning: delta_i cannot be negative!\n");
        } 
        else {
            break;
        }
    }
}

void input_valid_delta_v(Saving *value) //Ensure that user-entered values align with actual conditions.
{
    while (1) {
        value->delta_v = get_user_input_value("\nEnter output ripple voltage delta_v (V): ");

        if (value->delta_v < 0) {
            printf("\nWarning: delta_v cannot be negative!\n");
        } 
        else {
            break;
        }
    }
}

void input_valid_L(Saving *value) //Ensure that user-entered values align with actual conditions.
{
    while (1) {
        value->L = get_user_input_value("\nEnter inductance L (mH): ");

        if (value->L <= 0) {
            printf("\nWarning: Inductance L must be > 0!\n");
        } 
        else {
            break;
        }
    }
}

void input_valid_C(Saving *value) //Ensure that user-entered values align with actual conditions.
{
    while (1) {
        value->C = get_user_input_value("\nEnter capacitance C (uF): ");

        if (value->C <= 0) {
            printf("\nWarning: Capacitance C must be > 0!\n");
        } 
        else {
            break;
        }
    }
}

void input_valid_R(Saving *value) //Ensure that user-entered values align with actual conditions.
{
    while (1) {
        value->R = get_user_input_value("\nEnter load resistance R (ohm): ");

        if (value->R <= 0) {
            printf("\nWarning: Load resistance R must be > 0!\n");
        } 
        else {
            break;
        }
    }
}

void input_valid_fs(Saving *value) //Ensure that user-entered values align with actual conditions.
{
    while (1) {
        value->fs = get_user_input_value("\nEnter switching frequency fs (HZ): ");

        if (value->fs <= 0) {
            printf("\nWarning: fs must be > 0!\n");
        } 
        else {
            break;
        }
    }
}

//Ask the user
int ask_recalculate(void)//Ask if the user want to recalculate.
{    
    int shouldContinue = 0;
    char ending;

    while(shouldContinue ==  0){
        printf("\nDo you want to recalculate?(Y/N):");
        scanf("%c", &ending);
        while(getchar()!= '\n');
        if(ending == 'Y'||ending == 'y'){
            shouldContinue = 1;
            return shouldContinue;//makes sure
        }
        else if(ending == 'N'|| ending == 'n'){
            break; // jump out of do-while
        }
        else{
            printf("\nError, input(Y/N)\n");
        }   
    }
    return shouldContinue;
}

int confirm_action(void)//Ensure users select the option they want.
{    
    int shouldContinue = 0;
    char ending;

    while(shouldContinue ==  0){
        printf("\nIs this the option you want?(Y/N):");
        scanf("%c", &ending);
        while(getchar()!= '\n');
        if(ending == 'Y'||ending == 'y'){
            shouldContinue = 1;
            return shouldContinue;//make sure
        }
        else if(ending == 'N'|| ending == 'n'){
            break; // jump out of do-while
        }
        else{
            printf("\nError, input(Y/N)\n");
        }   
    }
    return shouldContinue;
}
