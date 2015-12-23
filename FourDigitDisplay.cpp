#include "FourDigitDisplay.h"

FourDigitDisplay::FourDigitDisplay(const int digitPins[], const int segmentPins[])
{
	//copy all of the digit pins and segment pins to this object
	for(int i = 0; i < num_digits_; i++)
	{
		digitPins_[i] = digitPins[i];
	}

	for(int i = 0;i < num_segments_; i++)
	{
		segmentPins_[i] = segmentPins[i];
	}

	//set all of the digit pins to be OUTPUTS, and set them to HIGH, because HIGH == Off
	for(int i=0;i<num_digits_;i++)
	{
		pinMode(digitPins_[i], OUTPUT);
		digitalWrite(digitPins_[i], HIGH);
	}

	//initialise all of the segment pins as outputs
	for(int i=0;i<num_segments_;i++)
	{
		pinMode(segmentPins_[i], OUTPUT);
	}
}

void FourDigitDisplay::displayCharacter(const char& character, const char& position)
{
	//turn on the character in the correct position
	for(int i=0;i<num_digits_;i++)
	{
		if(i != position) {
			digitalWrite(digitPins_[i], HIGH);
		} else {
			digitalWrite(digitPins_[i], LOW);
		}
	}

	//segments is used to point to the correct set of segments for displaying the character
	const char* segments;

	//this character is a digit
	if(character >= '0' && character <='9')
	{
		char c = character - '0';
		segments = digitSegments_[c];
	} 
	//this character is a lower case letter
	else if(character >= 'a' && character <= 'z')
	{
		char c = character - 'a';
		//currently, the same array is used for lower case and upper case letters
		segments = characterSegments_[c];
	}
	//this character is an upper case letter
	else if(character >= 'A' && character <= 'Z')
	{
		char c = character - 'A';
		//currently, the same array is used for lower case and upper case letters
		segments = characterSegments_[c];
	}
	//if we get to this point, the user has asked to display a character that has not been implemented
	//so we just display an underscore, as a placeholder
	else {
		for(int i = 0; i < num_segments_; i++)
		{
			digitalWrite(segmentPins_[i], LOW);
		}
		//segmentPins_[3] is the lowest segment, an underscore
		digitalWrite(segmentPins_[3], HIGH);
	}

	//loop through all of the segments in our character, to decide what to display
	for(int i=0;i<num_segments_;i++)
	{
		//write HIGH if the segment is meant to be turned on for the character, low otherwise
		if(segments[i] == 1) {
			digitalWrite(segmentPins_[i],HIGH);
		} else {
			digitalWrite(segmentPins_[i],LOW);
		}
	}

	//this delay is required in order to stop the characters "bleeding" into other positions
	//If the delay is too high, there will be flickering on the digits. If the display is too low
	//the will be bleeding.
	delay(5);
}

void FourDigitDisplay::displayDigit(const char& value, const char& position)
{
	//we need to add '0' to the digit in order to turn it into the appropriate character
	displayCharacter(value + '0', position);
}

void FourDigitDisplay::displayInteger(const int& value)
{
	//the special case of k being 0 is handled seperately, so that a simpler algorithm
	//can be used to draw all other numbers.
	if(value == 0)
	{
		displayDigit(0, num_digits_ - 1);
		return;
	}
	int k = value;

	//display the digits in the segments from right to left.
	char digit = num_digits_-1;
	for(; digit>=0 && k!=0; k/=10, digit--)
	{
		displayDigit(k%10, digit);
	}
}

void FourDigitDisplay::displayText(const char* text)
{
	//display characters until there are no more characters in the text,
	//or we have run out of digits to use to display characters
	for(char i = 0; text[i] != 0 && i < num_digits_; i++)
	{
		displayCharacter(text[i], i);
	}
}

void FourDigitDisplay::displayText(String text)
{
	//display characters until there are no more characters in the text,
	//or we have run out of digits to use to display characters
	for(int i = 0; i < text.length() && i < num_digits_; i++)
	{
		displayCharacter(text.charAt(i), i);
	}
}