#include "HackBadge.hpp"

HackBadge badge;

void setup() {
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		badge.writePixel(i,i,255);
	}
}

void loop() {
	uint8_t i;
	uint8_t j;
	for (i = 0; i < 16; i++)
	{
		badge.clear();
		for (j = 0; j < 8; j++)
		{
			badge.writePixel((i + j) % 16, j, 255);
			badge.writePixel((31 - (i + j)) % 16, j, 255);
		}
		badge.drawFor(62);
	}
}
