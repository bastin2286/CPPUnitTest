package com.mycompany.app;

/**
 * Hello world!
 */
public class App
{

    private static String MESSAGE = "Hello World!";

    public App() 
    {
    	//Do nothing
    }

    public static void main(String[] args) 
    {
    
      String Test = "";
    	if(args == null)
    	{
    	   Test = "Pass";
    	}
    	else
    	{
    	  Test = args[0];
    	}
    	
    	String test = "";
    	if(Test.equals("Pass"))
    	{
    		test = "Pass";
    	}
    	else
    	{
    		test = "Fail";
    	}
    	MESSAGE = test;
    }

    public static String getMessage() {
        return MESSAGE;
    }

}
