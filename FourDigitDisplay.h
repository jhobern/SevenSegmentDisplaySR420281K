/*
	Author	: Jonathan Andrew Hobern
	Date	: 19/12/15
	License	: GNU LESSER GENERAL PUBLIC LICENSE Version 3, 29 June 2007

This library is used to power the SR420281K 7 segment (8 with decimal points), 4 digit displays.

*/

#ifndef FOURDIGITDISPLAY_HPP
#define FOURDIGITDISPLAY_HPP

#include <Arduino.h>

class FourDigitDisplay
{
public:
	FourDigitDisplay(const int digitPins[], const int segmentPins[]);

	/*
		displayInteger displays the last num_digits_ digits from value onto the display
		For example, the number abcdefg would be displayed as defg.
		The numbers are right justified.
	*/
	void displayInteger(const int& value);

	/*
		displayText displays the first num_digits characters from a given array of text
		onto the display.
		For example, the text "abcdefg" would be displayed as abcd
		The text is left justified.
	*/
	void displayText(const char* text);

	/*
		displayText is overloaded to work with Arduino strings too, for ease of use
	*/
	void displayText(String text);


	/*
		displayScrollingText provides a method to display long strings on the small display.
		The entire string is displayed one time per method call.
		text is the string that is to be displayed
		characterDelay is the length of time to wait before scrolling the text along one character
	*/
	void displayScrollingText(String text, long characterDelay);

private:
	//These constants represent the number of digits and segments in the display
	static const int num_digits_ = 4;
	static const int num_segments_ = 8;
	
	//two arrays that are used to store which pins drive the digits of the display,
	//and which pins drive the segment. Each array is in order, i.e. the first element
	//of digitPins_ drives the first digit of the display etc.
	int digitPins_[num_digits_];
	int segmentPins_[num_segments_];

	/*
		displayCharacter displays a single character at the given position on the display.
	*/
	void displayCharacter(const char& character, const char& position);

	/*
		displayDigit is used to display a single digit at a given position in the display
	*/
	void displayDigit(const char& character, const char& position);

	//digitSegments_ stores the list of segments that should be turned on in order
	//to display a particular digit.
	//digitSegments_[n] is an array, with 1 in position m if segment m should be turned on
	//in order to display digit n correctly, and a 0 in position m otherwise.
	const char digitSegments_[10][num_segments_] = {
		{1,1,1,1,1,1,0,0}, //0
		{0,1,1,0,0,0,0,0}, //1
		{1,1,0,1,1,0,1,0}, //2
		{1,1,1,1,0,0,1,0}, //3
		{0,1,1,0,0,1,1,0}, //4
		{1,0,1,1,0,1,1,0}, //5
		{1,0,1,1,1,1,1,0}, //6
		{1,1,1,0,0,0,0,0}, //7
		{1,1,1,1,1,1,1,0}, //8
		{1,1,1,1,0,1,1,0}  //9
	};

	//characterSegments_ stores the list of segments that should be turned on in order
	//to display a particular character.
	//charactersSegments_[c-'a'] is an array, with 1 in position m if segment m should be turned on
	//in order to display character c correctly, and a 0 in position m otherwise.
	const char characterSegments_[26][num_segments_] = {
		{1,0,1,0,1,1,1,0}, //A
		{0,0,1,1,1,1,1,0}, //b
		{1,0,0,1,1,1,0,0}, //C
		{0,1,1,1,1,0,1,0}, //d
		{1,1,0,1,1,1,1,0}, //e
		{1,0,0,0,1,1,1,0}, //F
		{1,1,1,1,0,1,1,0}, //g
		{0,1,1,0,1,1,1,0}, //H
		{0,0,0,0,1,1,0,0}, //I
		{0,1,1,1,1,0,0,0}, //J
		{1,0,1,0,1,1,1,0}, //k
		{0,0,0,1,1,1,0,0}, //L
		{1,0,1,0,1,0,0,0}, //m
		{1,1,1,0,1,1,0,0}, //n
		{0,0,1,1,1,0,1,0}, //o
		{1,1,0,0,1,1,1,0}, //p
		{1,1,1,0,0,1,1,1}, //q
		{1,1,0,0,1,1,0,0}, //r
		{1,0,1,1,0,1,1,0}, //S
		{0,0,0,1,1,1,1,0}, //t
		{0,0,1,1,1,0,0,1}, //u
		{0,0,1,1,1,0,0,0}, //v
		{0,1,0,1,0,1,0,0}, //w
		{0,1,1,0,1,1,1,0}, //X
		{0,1,1,1,0,1,1,0}, //y
		{1,1,0,1,1,0,1,0}, //Z
	};
};

#endif //FOURDIGITDISPLAY_HPP