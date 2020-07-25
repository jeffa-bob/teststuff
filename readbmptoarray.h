#pragma once

#include <fstream>

struct color {
				unsigned char blue;
				unsigned char green;
				unsigned char red;
};

 struct image {
				char header[54];
				color **data = new color*[600];
};

void threshold(image& Frame);

image* loadimage(std::string fileloca) {
				std::ifstream input_image;
				input_image.open(fileloca);
				image Frame;
				for (int i = 0; i < 600; ++i) {
								Frame.data[i] = new color[600];
				}
				input_image.read((char*)&Frame, sizeof(Frame));
				threshold(Frame);
				return &Frame;
}

void threshold(image& Frame) {
				for (int i = 0; i < 600; ++i) {
								for (int j = 0; j < 600; ++j) {
												if (Frame.data[i][j].blue < 40)
																Frame.data[i][j].blue = 0;
												else
																Frame.data[i][j].blue = 1;
												if (Frame.data[i][j].green < 40)
																Frame.data[i][j].green = 0;
												else
																Frame.data[i][j].green = 1;
												if (Frame.data[i][j].red < 40)
																Frame.data[i][j].red = 0;
												else
																Frame.data[i][j].red = 1;
								}
				}
}