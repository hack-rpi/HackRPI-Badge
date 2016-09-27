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
	pinMode(INPUT_CS, OUTPUT);
	digitalWrite(INPUT_CS, HIGH);
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

void HackBadge::writePixel(size_t x, size_t y, uint8_t brightness)
{
	pixels[x + (y * PIXELS_PER_ROW)] = brightness;
}

uint8_t HackBadge::readPixel(size_t x, size_t y)
{
	return pixels[x + (y * PIXELS_PER_ROW)];
}

size_t HackBadge::characterWidth(char character)
{
	if (character >= TYPESET_FIRST_CHAR && character <= TYPESET_LAST_CHAR)
	{
		size_t offsetIndex = character - TYPESET_FIRST_CHAR;
		size_t charWidth = TYPESET_OFFSETS[offsetIndex + 1] -
						   TYPESET_OFFSETS[offsetIndex];
		return charWidth;
	}
	return 0;
}

size_t HackBadge::writeCharacter(size_t x, char character, uint8_t brightness)
{
	size_t i;
	size_t j;
	if (character >= TYPESET_FIRST_CHAR && character <= TYPESET_LAST_CHAR)
	{
		size_t offsetIndex = character - TYPESET_FIRST_CHAR;
		size_t bitmapIndex = TYPESET_OFFSETS[offsetIndex];
		size_t charWidth   = characterWidth(character);
		for (i = 0; i < charWidth; i++)
		{
			if (x + i < PIXELS_PER_ROW)
			{
				uint8_t column = TYPESET_BITMAP[bitmapIndex + i];
				for (j = 0; j < 8; j++)
				{
					if (column & 0x80)
						writePixel(x + i, j, brightness);
					else
						writePixel(x + i, j, 0);
					column <<= 1;
				}
			}
		}
		return charWidth;
	}
	return 0;
}

size_t HackBadge::textWidth(const char* text)
{
	size_t length = 0;
	for (; *text != '\0'; text++)
	{
		length += characterWidth(*text) + 1;
	}
	length--;
	return length;
}

void HackBadge::writeText(size_t x, const char* text, uint8_t brightness)
{
	size_t xIndex = x;
	size_t i;
	size_t j;
	char curChar;
	for (i = 0; (curChar = text[i]) != '\0'; i++)
	{
		char curChar = text[i];
		xIndex += writeCharacter(xIndex, curChar, brightness);
		if (xIndex < PIXELS_PER_ROW)
		{
			for (j = 0; j < 8; j++)
			{
				writePixel(xIndex, j, 0);
			}
		}
		xIndex += 1;
	}
}

void HackBadge::writeToShiftRegisters(uint8_t row, uint8_t brightness_threshold)
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
			if (readPixel(j + (i * MATRIX_WIDTH), row) > brightness_threshold)
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
	uint8_t j;
	enableDisplay();
	for (i = 0; i < BRIGHTNESS_LEVELS; i++)
	{
		for (j = 0; j < MATRIX_HEIGHT; j++)
		{
			writeToShiftRegisters(j, i);
			delayMicroseconds(TIME_PER_ROW);
		}
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

uint8_t HackBadge::readInputs()
{
	uint8_t shiftVal;
	digitalWrite(INPUT_CS, LOW);
	latch();
	SPI.beginTransaction(spi_settings);
	shiftVal = SPI.transfer(0x00);
	SPI.endTransaction();
	digitalWrite(INPUT_CS, HIGH);
	return shiftVal;
}