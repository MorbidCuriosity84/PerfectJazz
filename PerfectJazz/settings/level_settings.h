#pragma once
#include <string>

/*
* This is how levels are represented. Each number corresponds to the index of a wave filename
* in the array below. In the current naive implementation, this limits us to 10 possible 
* different waves and might be better replaced or augmented with a random wave generator to 
* add the ability for infinte but varied levels. Equally full use of the standard ASCII table gives us 
* the potential for 128 different waves or 96 not including speical chars (NUL, CR etc.) and the extended
* table gives us a total of 256. This could be something to look into for future.
*/

//Sets up a string array with the different waves per each level
static std::string levels[5] =
{
	/*
	"5",
	"542413",
	"002361",
	"154232",
	"540132",*/
	"1",
	"1",
	"1",
	"1",
	"1",
};

//Sets up the waves fileanmes in an array of strings
static std::string waveFilenames[10] = {
	"wave0",
	"wave1",
	"wave2",
	"wave3",
	"wave4",
	"wave5",
	"wave6",
	"wave7",
	"wave8",
	"wave9",
};


