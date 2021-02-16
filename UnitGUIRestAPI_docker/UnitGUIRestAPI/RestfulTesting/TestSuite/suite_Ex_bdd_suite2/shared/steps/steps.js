// A quick introduction to implementing scripts for BDD tests:
//
// This file contains snippets of script code to be executed as the .feature
// file is processed. See the section 'Behaviour Driven Testing' in the 'API
// Reference Manual' chapter of the Squish manual for a comprehensive reference.
//
// The functions Given/When/Then/Step can be used to associate a script snippet
// with a pattern which is matched against the steps being executed. Optional
// table/multi-line string arguments of the step are passed via a mandatory
// 'context' parameter:
//
//   When("I enter the text", function(context) {
//     <code here>
//   });
//
// The pattern is a plain string without the leading keyword, but a couple of
// placeholders including |any|, |word| and |integer| are supported which can
// be used to extract arbitrary, alphanumeric and integer values resp. from the
// pattern; the extracted values are passed as additional arguments:
//
//   Then("I get |integer| different names", function(context, numNames) {
//     <code here>
//   });
//
// Instead of using a string with placeholders, a regular expression object can
// be passed to Given/When/Then/Step to use regular expressions.
//

import * as names from 'names.js';

When("user sends a registration request without password", function(context) {
    var client = new XMLHttpRequest();
    client.open('POST', 'https://reqres.in/api/register', false);
    client.setRequestHeader("Content-Type", "application/json");
    var data = '{"email": "tester@froglogic.com"}';
    client.send(data);
    context.userData["sentData"] = data;
    context.userData["status"] = client.status;
    context.userData["response"] = JSON.parse(client.response);
});

Then("the server returns an error status code", function(context) {
    test.verify( context.userData["status"] == 400 );
});

Then("a payload containing an error message", function(context) {
    var response = context.userData["response"];
    test.log("Response: " + response["error"]);
    test.verify( response["error"] !== undefined );
});


When("user sends a user creation request", function(context) {
    var client = new XMLHttpRequest();
    client.open('POST', 'https://reqres.in/api/users', false);
    var data = {"email": "tester@froglogic.com"};
    client.send(data);
    context.userData["sentData"] = data;
    context.userData["status"] = client.status;
    context.userData["response"] = JSON.parse(client.response);
});

Then("the server returns a success status code", function(context) {
    var status = context.userData["status"];
    test.log("Response status: " + status);    
    test.verify( status == 200 || status == 201 || status == 204 );
});

Then("a payload containing user data", function(context) {
    var response = context.userData["response"];
    test.log("Response id: " + response["id"] );     
    test.log("Response Created At: " + response["createdAt"] );          
    test.verify( response["id"] !== undefined );
    test.verify( response["createdAt"] !== undefined );
});



Given("the user has fetched the list of all colors", function(context) {
    var client = new XMLHttpRequest();
    var current_page = 1;
    var last_page;
    var colors = [];

    do {
    client.open('GET', 'https://reqres.in/api/colors?page='+current_page.toString(), false);
    client.send();

    var response = JSON.parse(client.response);
    last_page = response["total_pages"];
    
    test.log("Response total_pages: " + response["total_pages"] );  
    test.log("Response data Length: " + response["data"].length );   
    test.log("Response data: " + response["data"]);     
    
    for (var i =0; i < response["data"].length; ++i) {
        colors.push(response["data"][i]);  
    }
    current_page++;
    } while (current_page != last_page) ;

    context.userData["status"] = client.status;
    context.userData["colors"] = colors;
    context.userData["response"] = JSON.parse(client.response);
});

function getRandomInt(max) {
    return Math.floor(Math.random() * Math.floor(max));
}

When("user sends a delete request for one of them", function(context) {
    var random = getRandomInt( context.userData["colors"].length - 1 );
    
    var client = new XMLHttpRequest();
    client.open('DELETE', 'https://reqres.in/api/colors/'+random.toString(), false);
    client.send();
    
    test.log("colours Length -1: " +(context.userData["colors"].length - 1).toString()); 
    test.log("Random : " +random.toString());     
    context.userData["status"] = client.status;
    test.log("client.status : " +context.userData["status"]);        
});