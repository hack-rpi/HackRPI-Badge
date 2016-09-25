#include "HackBadge.hpp"
#include "typeset.h"

// memset
#include <string.h>

HackBadge::HackBadge()
{
	// Initialize member variables
	spi_settings = SPISettings(SPI_SPEED_HZ, MSBFIRST, SPI_MODE0);
	// Initialize hardware
	pinMode(OE_PIN, OUTPUT);
	pinMode(LATCH_PIN, OUTPUT);
	SPI.begin();
	// Reset display
	clear();
	draw();
}

void HackBadge::clear()
{
	memset(pixels, 0, NUM_PIXELS);
}

void HackBadge::latch()
{
	digitalWrite(LATCH_PIN, LOW);
	digitalWrite(LATCH_PIN, HIGH);
}

void HackBadge::enableDisplay()
{
	digitalWrite(OE_PIN, LOW);
}

void HackBadge::disableDisplay()
{
	digitalWrite(OE_PIN, HIGH);
}

void HackBadge::writePixel(uint8_t x, uint8_t y, uint8_t brightness)
{
	pixels[x + (y * PIXELS_PER_ROW)] = brightness;
}

uint8_t HackBadge::readPixel(uint8_t x, uint8_t y)
{
	return pixels[x + (y * PIXELS_PER_ROW)];
}

size_t HackBadge::writeCharacter(uint8_t x, char character)
{
	size_t i;
	size_t j;
	if (character >= TYPESET_FIRST_CHAR && character <= TYPESET_LAST_CHAR)
	{
		size_t typesetIndex = character - TYPESET_FIRST_CHAR;
		size_t charWidth = TYPESET_OFFSETS[typesetIndex + 1] -
		                   TYPESET_OFFSETS[typesetIndex];
		for (i = 0; (i < charWidth) && (x + i < PIXELS_PER_ROW); i++)
		{
			uint8_t column = TYPESET_BITMAP[typesetIndex + i];
			for (j = 0; j < 8; j++)
			{
				if (column & 0x80)
					writePixel(x + i, j, 255);
				else
					writePixel(x + i, j, 0);
				column <<= 1;
			}
		}
		return charWidth;
	}
	return 0;
}

void HackBadge::writeText(uint8_t x, char* text, size_t textLength)
{
	size_t xIndex = x;
	size_t i;
	for (i = 0; i < textLength; i++)
	{
		char curChar = text[i];
		xIndex += writeCharacter(xIndex, curChar);
	}
}

void HackBadge::writeToShiftRegisters(uint8_t row)
{
	uint8_t i;
	uint8_t j;
	uint8_t bytes[NUM_MATRICES];
	memset(bytes, 0, NUM_MATRICES);
	for (i = 0; i < NUM_MATRICES; i++)
	{
		bytes[i] = 0;
		for (j = 0; j < MATRIX_WIDTH; j++)
		{
			if (readPixel(j + (i * MATRIX_WIDTH), row) > 0)
			{
				bytes[i] |= (1 << j);
			}
		}
	}
	SPI.beginTransaction(spi_settings);
	SPI.write(bytes[0]);
	SPI.write(1 << row);
	SPI.write(bytes[1]);
	SPI.endTransaction();
	latch();
}

void HackBadge::draw()
{
	uint8_t i;
	enableDisplay();
	for (i = 0; i < MATRIX_HEIGHT; i++)
	{
		writeToShiftRegisters(i);
		delayMicroseconds(TIME_PER_ROW);
	}
	disableDisplay();
}

void HackBadge::drawFor(uint32_t duration)
{
	uint32_t startTime = millis();
	while ((uint32_t)(millis() - startTime) <= duration)
	{
		draw();
		yield();
	}
}
