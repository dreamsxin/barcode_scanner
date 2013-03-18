#ifndef USERINPUT_H_INCLUDED
#define USERINPUT_H_INCLUDED

void get_input(); // get user inputk, store in line[]

void printMainMenu(); // print main menu for root activities

int parse_user_input_activity(); // ask root activity from user

int ask_for_barcode(); // ask user to enter barcode, save input

#endif