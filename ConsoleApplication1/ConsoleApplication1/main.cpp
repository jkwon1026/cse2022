#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>    // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"

const int width = 640;
const int height = 480;

float* pixels = new float[width*height *  3];

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

void drawLine2(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int j = j0; j <= j1; j++)
	{
		const int i = (i1 - i0)*(j - j0) / (j1 - j0) + i0;

		drawPixel(i, j, red, green, blue);
	}
}

void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(i, j, red, green, blue);
	}
}

void drawOnPixelBuffer()
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f); // white background

												 //for (int i = 0; i<width*height; i++) {
												 // pixels[i * 3 + 0] = 1.0f; // red 
												 // pixels[i * 3 + 1] = 1.0f; // green
												 // pixels[i * 3 + 2] = 1.0f; // blue
												 //}

	const int i = rand() % width, j = rand() % height;
	//drawPixel(i, j, 0.0f, 0.0f, 0.0f);

	// drawing a line
	//TODO: anti-aliasing
	int i0 = 50, i1 = 200, ix;
	int j0 = 50, j1 = 50;
	int k, z;
	float r, g, b;

	r = 0;
	g = 0;
	b = 0;


	

	for (z = 0; z<3; z++)
		for (k = 0; k<3; k++)
			drawLine(50 + z, 300 + k, 100 + z, 380 + k, 0, 0, 0);



	drawLine(250, 300, 350, 300, r, g, b);
	drawLine2(250, 300, 250, 400, r, g, b);
	drawLine(250, 400, 350, 400, r, g, b);
	drawLine2(350, 300, 350, 400, r, g, b);


	for (z = 0; z < 100; z++)
		drawLine(400, 300 + z, 500, 300 + z, r, g, b);



	drawLine(50, 50, 200, 50, r, g, b);
	drawLine(50, 50, 150, 100, r, g, b);
	drawLine(150, 100, 200, 50, r, g, b);



	drawLine(250, 100, 300, 50, r, g, b);
	drawLine(250, 100, 300, 150, r, g, b);
	drawLine(300, 150, 370, 100, r, g, b);
	drawLine(340, 50, 370, 100, r, g, b);
	drawLine(300, 50, 340, 50, r, g, b);




	

	for (z = 50; z < 200; z++)
	{
		for (k = 425; k < 600; k++)
		{

			ix = k + z*width;

			if ((k - 500)*(k - 500) + (z - 125)*(z - 125) > 50 * 49 && (k - 500)*(k - 500) + (z - 125)*(z - 125) < 50 * 51)
			{
				pixels[ix * 3 + 0] = 0;
				pixels[ix * 3 + 1] = 0;
				pixels[ix * 3 + 2] = 0;
			}
		}
	}
}


//TODO: try moving object


int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}



	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

							  /* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);

		drawOnPixelBuffer();

		//TODO: RGB struct
		//Make a pixel drawing function
		//Make a line drawing function

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		drawLine(1, 1, 200, 200, 0, 0, 0);


		std::this_thread::sleep_for(std::chrono::milliseconds(300));
	}





	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}
