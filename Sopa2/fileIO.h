#ifndef FILEIO_H
#define FILEIO_H

#include <string>
#include <vector>

std::vector<std::string> readFile(const std::string& filename);
void writeFile(const std::string& filename, const std::vector<std::string>& words);

#endif

