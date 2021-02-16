# This is a sample .feature file
# Squish feature files use the Gherkin language for describing features, a short example
# is given below. You can find a more extensive introduction to the Gherkin format at
# https://github.com/cucumber/cucumber/wiki/Gherkin
Feature: Testing a REST API Two

  Scenario: User can create another user
	When user sends a user creation request
	Then the server returns a success status code
	And a payload containing user data
