#pragma once

#include <iostream>
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

void threshold(color **data);

color** loadimage(std::string fileloca) {
				std::ifstream input_image;
				input_image.open(fileloca);
				image Frame;
				for (int i = 0; i < 600; ++i) {
								Frame.data[i] = new color[600];
				}
				input_image.read((char*)&Frame, sizeof(Frame));
				threshold(Frame.data);
				return Frame.data;
}

void threshold(color **data) {
				for (int i = 0; i < 600; ++i) {
								for (int j = 0; j < 600; ++j) {
												if (data[i][j].blue < 40)
																data[i][j].blue = 0;
												else
																data[i][j].blue = 1;
												if (data[i][j].green < 40)
																data[i][j].green = 0;
												else
																data[i][j].green = 2;
												if (data[i][j].red < 40)
																data[i][j].red = 0;
												else
																data[i][j].red = 3;
												//std::cout <<(int)data[i][j].red<<"\n"<< (int)data[i][j].green << "\n" << (int)data[i][j].blue << "\n";
								}
				}
}