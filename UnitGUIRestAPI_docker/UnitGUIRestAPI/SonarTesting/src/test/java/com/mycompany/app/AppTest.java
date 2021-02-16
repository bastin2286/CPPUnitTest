package com.mycompany.app;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import org.junit.Before;
import org.junit.Test;
import org.junit.After;
import static org.junit.Assert.*;

/**
 * Unit test for simple App.
 */
public class AppTest
{

    private final ByteArrayOutputStream outContent = new ByteArrayOutputStream();

    @Before
    public void setUpStreams() {
        System.setOut(new PrintStream(outContent));
    }

    @Test
    public void testAppConstructor() {
        try {
            new App();
        } catch (Exception e) {
            fail("Construction failed.");
        }
    }

    @Test
    public void testAppPass()
    {
    	String chk[] = {"Pass"};
    	
        App.main(chk);
        assertEquals("Pass", App.getMessage());
    }
    
    
    @Test
    public void testAppFail()
    {
    	String chk[] = {"Fail"};
    	
        App.main(chk);
        assertEquals("Fail", App.getMessage());
    }
    
    @After
    public void cleanUpStreams() {
        System.setOut(null);
    }

}
