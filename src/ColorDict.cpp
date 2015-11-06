/*
 * ColorDict
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
#include "NamedColorTable.hpp"

int main(int argc, char** argv) {
  using namespace kallaballa;

  if (argc != 2) {
    std::cerr << "Usage: colorDict <24bit hex color>" << std::endl;
    std::cerr << "Example: colorDict ffffff" << std::endl;
    return 1;
  }

  NamedColorTree ral;
  ral.readFromFile("colordict.txt");

  NamedColor sample;
  sample.rgb = strtol(argv[1], NULL, 16);

  auto nearest = ral.find_nearest(sample);

  std::cout
    << std::dec << int(nearest.second) << "\t#"
    << std::setfill('0') << std::setw(6) << std::hex << (*nearest.first).rgb << "\t"
    << (*nearest.first).name << std::endl;
}
