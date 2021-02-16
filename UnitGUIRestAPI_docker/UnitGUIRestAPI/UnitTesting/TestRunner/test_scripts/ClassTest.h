/******************************************************************************
 * File Name      : ClassTest.h
 *  
 * Description    : This header file contains Testpoints class required for Testing 
 *				    
 * Modifiled Date : 07/12/2020
 *
 *****************************************************************************/
#ifndef CLASSTEST_H
#define CLASSTEST_H


#define TESTING 1

#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<stdlib.h>
#include<stdio.h>

using namespace std;

/****************************************************************************** 
*Class Name		: Testpoints
*
* Description 	: This is the singleton class created to define test variables
*				  used as test points while testing.
* 
*****************************************************************************/
class Testpoints 
{
	static Testpoints *instance;
	int data,d_spec,p_dep,p_veri,d_delete;
  	string p_pass, p_x;
 
 	/***** Private constructor so that no objects can be created.*************/
	Testpoints() 
	{
		data = 0;
		d_spec =0;
		p_dep = 0;
		p_pass = "";
		p_x = "";
	}
	public:
  	int object=0;
  	static Testpoints *getInstance() 
  	{
    	if (!instance)  
    	{
      		instance = new Testpoints;
      	}
      	return instance;
   	}
    
    int getD_delete()
  	{
   		return this ->d_delete;
   	}
   
  	void setD_delete(int _delete)
  	{
  	 	this -> d_delete = _delete;
 	}

    int getPass_veri()
  	{
   		return this ->p_veri;
   	}
   
  	void setPass_veri(int veri)
  	{
  	 	this -> p_veri = veri;
 	}
 	
  	int getP_dep()
  	{
   		return this ->p_dep;
   	}
   
  	void setP_dep(int dep)
  	{
  	 	this -> p_dep = dep;
 	}
   
  	int getD_spec() 
  	{
   		return this -> d_spec;
   	}
   	
   	void setD_spec(int spec) 
   	{
    	this -> d_spec = spec;
   	}

   	string getP_pass() 
   	{
    	return this -> p_pass;
   	}

   	void setP_pass(string pass) 
   	{
    	this -> p_pass = pass;
   	}
   
   	string getP_x() 
   	{
    	return this -> p_x;
   	}

   	void setP_x(string x) 
   	{
    	this -> p_x = x;
   	}

   	int getData() 
   	{
    	return this -> data;
   	}

   	void setData(int data) 
   	{
    	this -> data = data;
   	}
};


#endif
