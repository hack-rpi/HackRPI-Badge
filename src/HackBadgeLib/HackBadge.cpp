#include "HackBadge.hpp"

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
