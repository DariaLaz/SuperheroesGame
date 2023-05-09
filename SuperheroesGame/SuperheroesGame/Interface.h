#pragma once
#include "System.h"

void menu(System& system);
void login(System& system);
void logout(System& system);

void command(System& system);

String& lower(String& str);
void addSyperhero(System& system);

Power getPower(String& pow);
Mode getMode(String& mode);

//personal
void deleteMe(System& system);
void logout(System& system);
