# This is a sample .feature file
# Squish feature files use the Gherkin language for describing features, a short example
# is given below. You can find a more extensive introduction to the Gherkin format at
# https://github.com/cucumber/cucumber/wiki/Gherkin
Feature:Testing a REST API Three

  Scenario: User can browse the list of all available colors and delete one of them
	Given the user has fetched the list of all colors
	When user sends a delete request for one of them
	Then the server returns a success status code
