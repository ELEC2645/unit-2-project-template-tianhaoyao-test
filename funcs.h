#ifndef FUNCS_H
#define FUNCS_H

// Define struct person
typedef struct {
    double Vi;
    double Vo;
    double K;
    double delta_i;
    double delta_v;
    double L;
    double C;
    double R;
    double fs;
} Saving;

double  get_user_input_value(char *str);

//file
int ask_read_data(void);
void save_record( Saving *value);
int read_file( Saving *value);

/*These functions are used for calculating expected values.*/
void calculate_buck_dutyratio(char *mode,  Saving *value);
void calculate_buck_ripple_current(Saving *value);
void calculate_buck_ripple_voltage(Saving *value);
void calculate_buck_inductance( Saving *value);
void calculate_buck_capacitor( Saving *value);

void calculate_boost_dutyratio(char *mode,  Saving *value);
void calculate_boost_ripple_current( Saving *value);
void calculate_boost_ripple_voltage( Saving *value);
void calculate_boost_inductance( Saving *value);
void calculate_boost_capacitor( Saving *value);

void calculate_buck_boost_dutyratio(char *mode,  Saving *value);
void calculate_buck_boost_ripple_current( Saving *value);
void calculate_buck_boost_ripple_voltage( Saving *value);
void calculate_buck_boost_inductance( Saving *value);
void calculate_buck_boost_capacitor( Saving *value);

//Input validation functions
void input_valid_duty_ratio(Saving *value);
void input_valid_Vi(Saving *value);
void input_valid_Vo(Saving *value);
void input_valid_L(Saving *value);
void input_valid_C(Saving *value); 
void input_valid_delta_i( Saving *value);
void input_valid_delta_v( Saving *value);
void input_valid_fs(Saving *value);
void input_valid_R(Saving *value);

//Ask the user
int ask_recalculate(void);
int confirm_action(void);

#endif
