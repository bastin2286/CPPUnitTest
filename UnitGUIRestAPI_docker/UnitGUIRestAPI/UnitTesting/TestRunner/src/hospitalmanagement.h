/******************************************************************************
 * File Name      : hospitalmanagement.h
 *  
 * Description    : This header file contains the declaration of hospitalmanagement 
 *					database functions.
 *				    
 * Modifiled Date : 07/12/2020
 *
 *****************************************************************************/
#ifndef HOSPITAL_H
#define HOSPITAL_H

#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<stdlib.h>
#include<stdio.h>

#define TESTING 1

/* Testing Macro */
#ifdef TESTING

#include "../test_scripts/ClassTest.h"

#endif

#include "hospitalmanagement.h"

using namespace std;

void addDoc();
void displayDoc();
void deleteDoc();
void dispDatabase();
void numberofDocs();
void getDoctorDatabase();
void getDoctor();
void numberofPats();
void addPat();
void displayPat();
void dispPatDatabase();
void numberofPats();
void getPatientDatabase();
void getStatus();

#endif
