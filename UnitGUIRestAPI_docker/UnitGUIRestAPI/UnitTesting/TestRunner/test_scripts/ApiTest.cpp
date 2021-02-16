/******************************************************************************
 * File Name      : ApiTest.cpp
 *  
 * Description    : This is the file responsible for all the test related to 
 *				     API using Google Test
 *
 * Modifiled Date : 07/12/2020
 *
 *****************************************************************************/
#include <gtest/gtest.h>
#include "../test_library/CsvRead.h"
#include "../utility/TestUtility.h"
#include "TestMain.h"

extern TestUtility s1;
/****************************************************************************** 
*Test Fixture Name : DdsAPI_Test
*
* Description      : This is the test fixture created for testing API.
*		 		     The filename where the test cases are written is declared 
*				     in this.
*
******************************************************************************/
class DdsAPI_Test : public ::testing::Test 
{
	 protected:
		virtual void SetUp() {
    	}
  
  		virtual void TearDown() {
  		}
  		std::string filename;
};
/****************************************************************************** 
*Test Fixture Name : CSVReadType_2
*
* Description      : This test is created using the test fixture DdsAPI_Test.
*		 		     This test uses the input from csv file and tests the api
*					 by passing the data through dds.
*
******************************************************************************/
TEST_F(DdsAPI_Test, CSVReadType_1)
{
	{
		filename = s1.getCsvFilePath("file1");
		CsvReader(filename);
		for(int ab =0; ab<words.size();ab++)
		{
			ASSERT_EQ(words1[ab], s1.evaluvateTestcase(words[ab]));
		}
		
	}
}
/****************************************************************************** 
*Test Fixture Name : CSVReadType_2
*
* Description      : This test is created using the test fixture DdsAPI_Test.
*		 		     This test uses the input from csv file and tests the api
*					 by passing the data through dds
*
******************************************************************************/
TEST_F(DdsAPI_Test, CSVReadType_2)
{
	{
		filename = s1.getCsvFilePath("file2");
		CsvReader(filename);
		for(int ab =0; ab<words.size();ab++)
		{
			ASSERT_EQ(words1[ab], s1.evaluvateTestcase(words[ab]));
		}
		
	}
}

