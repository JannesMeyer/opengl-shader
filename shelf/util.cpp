#include "util.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <gl/glew.h>
#include <fstream>

/*
 * Boring, non-OpenGL-related utility functions
 */

char* file_contents(const std::string& filename, GLint* length) {
	using namespace std;
	ifstream file (filename, ios::in | ios::binary | ios::ate);
	if (!file) {
		throw std::runtime_error("Unable to open file");
	}

	ifstream::pos_type size = file.tellg();
	char* buffer = new char [size];
	file.seekg(0, ios::beg);
	file.read(buffer, size);
	
	//delete[] buffer;
	return buffer;
}