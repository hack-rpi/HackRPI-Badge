#ifndef __HACKBADGE_HPP__
#define __HACKBADGE_HPP__

class HackBadge {
	public:
		// Constants //
		
		/// Number of pixels in a single row of a single matrix.
		static const MATRIX_WIDTH   = 8;
		/// Number of rows in a single matrix.
		static const MATRIX_HEIGHT  = 8;
		/// Number of LED matrices on the badge.
		static const NUM_MATRICES   = 2;
		/// Total number of pixels on the badge.
		static const NUM_PIXELS     = MATRIX_WIDTH * MATRIX_HEIGHT * NUM_MATRICES;
		/// Total number of bytes to represent all pixels on the badge (rounded up).
		static const NUM_BYTES      = (NUM_PIXELS - 1) / 8 + 1;
	
	private:
		// Private members //
		
		/// The byte array representing the LED array's pixels.
		/// Each pixel is a bit, with the top left pixel being the LSB of index 0.
		/// Index 1 corresponds to the top row of the second matrix, and index 2
		/// corresponds to the second row of the first matrix, etc.
		uint8_t pixels[NUM_BYTES];
		
	public:
		void writePixel(uint8_t, uint8_t);
}

#endif