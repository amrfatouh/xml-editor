#ifndef CORRECTION_H
#define CORRECTION_H
#include <iostream>
#include <string>
#include "check.h"
using namespace std;


int getOpeningBracesIndex(string markedString);

int getClosingBracesIndex(string markedString);

void removeOpeningBraces(string &markedString);

void removeClosingBraces(string &markedString);

void removeBraces(string &markedString);

bool isLegal(char a);


//error 10: <{{!}}
string correctError10(string markedString);


void testCorrectError10();


//error 11: <!{{-}}
string correctError11(string markedString);


void testCorrectError11();


//error 12: <!-- {{--}}
string correctError12(string markedString);


void testCorrectError12();


//error 13: <{{!}}
string correctError13(string markedString);


void testCorrectError13();


//error 14: <{{/}}a>
string correctError14(string markedString);


void testCorrectError14();


//error 15: </{{a}}
string correctError15(string markedString);


void testCorrectError15();


//error 16: </{{a}}
string correctError16(string markedString);


void testCorrectError16();


//error 17: <{{a}}>
string correctError17(string markedString);


void testCorrectError17();


//error 18: <?{{first 3 letters after '?' symbol}}
string correctError18(string markedString);


void testCorrectError18();


//error 19: {{<}}a>
string correctError19(string markedString);


void testCorrectError19();


string correct(string text);


void testCorrect();

#endif // CORRECTION_H
