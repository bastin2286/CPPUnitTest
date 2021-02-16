# This is a sample .feature file
# Squish feature files use the Gherkin language for describing features, a short example
# is given below. You can find a more extensive introduction to the Gherkin format at
# https://github.com/cucumber/cucumber/wiki/Gherkin


Feature: Testing a REST API One

  Scenario: User registration is unsuccessful without password
	When user sends a registration request without password
	Then the server returns an error status code
	And a payload containing an error message
