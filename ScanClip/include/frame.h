
#ifndef FRAME_H
#define FRAME_H

#define ImageW 400
#define ImageH 400

struct Color {
	Color () {}
	Color (float red, float green, float blue)
		:r(red), g(green), b(blue) {}
	float r, g, b;		// Color (R,G,B values)
};

class Frame {
public:

	Color shade;
	float framebuffer[ImageH][ImageW][3];

	// Draws the scene
	void drawit(void);

	// Clears framebuffer to black
	void clearFramebuffer();

	// Sets pixel x,y to the color RGB
	void setFramebuffer(int x, int y);
};

#endif

