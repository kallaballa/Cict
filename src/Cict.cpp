/*
 * Cict
 * Copyright (C) 2015 Amir Hassan <amir@viel-zu.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <iostream>
#include <iomanip>
#include <limits>
#include "NamedColorTree.hpp"

static long parse24bitHexRGB(const char *str) {
    errno = 0;
    char *temp;
    long val = strtol(str, &temp, 16);

    if (std::string(str).length() != 6 || temp == str ||
        *temp != '\0' ||
        ((val == std::numeric_limits<long>().min() || val == std::numeric_limits<long>().max()) && errno == ERANGE)) {
         std::cerr << "'" << str << "' is not a 24bit hexadecimal value." << std::endl;
         std::cerr << "For example white is represented by the following string ffffff" << std::endl;
         exit(1);
    }
    return val;
}

int main(int argc, char** argv) {
  using namespace kallaballa;

  if (argc != 2) {
    std::cerr << "Usage: cict <24bit hex color>" << std::endl;
    std::cerr << "Example: cict ffffff" << std::endl;
    return 1;
  }

  NamedColorTree colorTree;
  colorTree.readFromFile("colordict.txt");

  NamedColor sample;
  sample.rgb = parse24bitHexRGB(argv[1]);

  auto nearest = colorTree.find_nearest(sample);

  std::cout
    << std::dec << int(nearest.second) << "\t#"
    << std::setfill('0') << std::setw(6) << std::hex << (*nearest.first).rgb << "\t"
    << (*nearest.first).name << std::endl;
}
