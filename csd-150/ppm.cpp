/*
 *  uoc/csd-150/ppm.cpp
 *
 *  Copyright (C) 2025, infdv <infdv.me@gmail.com>
 */

#include <algorithm>  // includes std::min() for the nested
#include <fstream>    // For file I/O
#include <iostream>
#include <vector>  // library to use vectors. Technically can be done with arrays since oly 2 colours are needed.

// #include "color.h"
// #include "vec3.h"

int getValidInt(const std::string &prompt, int min, int max) {
  int value;
  while (true) {
    std::cout << prompt;
    std::cin >> value;
    if (std::cin.fail() || value < min || value > max) {
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
    } else {
      return value;
    }
  }
}

void generatePPM(int width, int height, std::vector<int> color1, std::vector<int> color2, int pattern, int size) {
  std::ofstream image("output.ppm");
  if (!image) {
    std::cout << "Error opening file.\n";
    return;
  }

  // PPM Header
  image << "P3\n" << width << " " << height << "\n255\n";

  // Pattern
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      bool useColor1 = false;

      switch (pattern) {
        case 1:  // Horizontal lines
          useColor1 = (y / size) % 2 == 0;
          break;
        case 2:  // Vertical lines
          useColor1 = (x / size) % 2 == 0;
          break;
        case 3:  // Checkerboard
          useColor1 = ((x / size) % 2) == ((y / size) % 2);
          break;
        case 4:  // Nested squares (credits to google & gpt for the math)
          int minDist = std::min({x, y, width - x - 1, height - y - 1});
          useColor1 = (minDist / size) % 2 == 0;
          break;
      }

      std::vector<int> color = useColor1 ? color1 : color2;
      image << color[0] << " " << color[1] << " " << color[2] << " ";
    }
    image << "\n";
  }

  image.close();
  std::cout << "PPM file 'output.ppm' generated successfully.\n";
}

int main() {
  // I limited it to 1000 for efficiency's shake
  int width = getValidInt("Enter image width: ", 1, 1000);
  int height = getValidInt("Enter image height: ", 1, 1000);

  std::vector<int> color1(3), color2(3);
  std::cout << "Enter Color1 (R G B) (0-255): ";
  for (int &c : color1) c = getValidInt("", 0, 255);

  std::cout << "Enter Color2 (R G B) (0-255): ";
  for (int &c : color2) c = getValidInt("", 0, 255);

  std::cout << "Select a pattern:\n"
            << "1 - Horizontal Lines\n"
            << "2 - Vertical Lines\n"
            << "3 - Checkerboard\n"
            << "4 - Nested Squares\n";

  int pattern = getValidInt("Enter pattern (1-4): ", 1, 4);
  int size = getValidInt("Enter pattern size: ", 1, std::min(width, height));

  generatePPM(width, height, color1, color2, pattern, size);

  return 0;
}
 
