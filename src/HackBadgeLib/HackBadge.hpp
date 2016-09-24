#ifndef __HACKBADGE_HPP__
#define __HACKBADGE_HPP__

// uint8_t
#include <stdint.h>
// SPISettings
#include <SPI.h>

class HackBadge {
	public:
		// Constants //
		
		// Board-based constants //
		
		/// The pin connected to the shift registers' output enable pins
		static const uint8_t OE_PIN         = 4;
		/// The pin connected to the shift registers' latch pins
		static const uint8_t LATCH_PIN      = 5;
		/// Number of pixels in a single row of a single matrix.
		static const uint8_t MATRIX_WIDTH   = 8;
		/// Number of rows in a single matrix.
		static const uint8_t MATRIX_HEIGHT  = 8;
		/// Number of LED matrices on the badge.
		static const uint8_t NUM_MATRICES   = 2;		

		// Configurable constants //
		
		/// The time between rows being drawn in microseconds.
		static const uint8_t TIME_PER_ROW   = 100;
		/// The SPI clock frequency in megahertz.
		static const uint8_t SPI_SPEED      = 1;
		
		// Derived constants //
		
		/// Number of pixels in a row of the display
		static const uint8_t PIXELS_PER_ROW = MATRIX_WIDTH * NUM_MATRICES;
		/// Total number of pixels on the display.
		static const uint8_t NUM_PIXELS     = PIXELS_PER_ROW * MATRIX_HEIGHT;
		/// The SPI clock frequency in hertz.
		static const uint32_t SPI_SPEED_HZ  = SPI_SPEED * 1000000;

	
	private:
		// Private members //
		
		/// The byte array representing the LED array's pixels.
		/// Each pixel is a byte, with the bottom left pixel being index 0.
		/// Increasing indices move rightwards and loop around to the next row above.
		uint8_t pixels[NUM_PIXELS];
		
		/// The SPI transaction settings when shifting data to/from shift registers
		SPISettings spi_settings;
		
		// Private methods
		
		/// Pulses the shift register latch pins low, causing them to output their register values
		void latch();
		/// Writes one row of the pixel array to the shift registers
		/// \param row The row of the pixel array to write
		void writeToShiftRegisters(uint8_t row);
		/// Enables the display by pulling the shift register output enable pins high.
		void enableDisplay(void);
		/// Disables the display by pulling the shift register output enable pins low.
		void disableDisplay(void);
		
	public:
		// Public methods //
		
		/// Constructs a new HackBadge, clearing the display.
		HackBadge(void);
		/// Sets every pixel on the display to an off state.
		void clear(void);
		/// Sets the brightness of a pixel on the display.
		/// \param x          The x coordinate of the pixel being set (with 0 being the left column)
		/// \param y          The y coordinate of the pixel being set (with 0 being the bottom row)
		/// \param brightness The new brightness of the pixel
		void writePixel(uint8_t x, uint8_t y, uint8_t brightness);
		/// Gets the current brightness of a pixel on the display
		/// \param x The x coordinate of the pixel to read
		/// \param y The y coordinate of the pixel to read
		uint8_t readPixel(uint8_t x, uint8_t y);
		/// Draws the contents of the screen, should be called frequently while screen is on.
		void draw(void);
		/// Continuously draws for an amount of time.
		/// \param duration The amount of time to draw for, in milliseconds.
		void drawFor(uint32_t duration);
};

#endif
