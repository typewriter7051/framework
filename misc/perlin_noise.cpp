#include "perlin_noise.h"
#include <string>			// For file name handling.
#include <vector>			// Not for actual unit vectors, just for lists.
#include <sys/stat.h>		// For file checking.

//================================================================================
// Quite unoptimized, but I don't feel like copy+pasting code from stack exchange.

float PerlinNoise::Octave::getValue(float x, float y) {

	// Calculate which grid angles to use.

	int gridX = x * harmonic - phase.x;
	int gridY = y * harmonic - phase.y;

	// Generate 4 gradient vectors.

	// Float representation of the previous calculation.
	float fgridX = x * harmonic - phase.x;
	float fgridY = y * harmonic - phase.y;

	vector2<float> g1(gridX - fgridX	, gridY - fgridY	);
	vector2<float> g2(gridX - fgridX + 1, gridY - fgridY	);
	vector2<float> g3(gridX - fgridX + 1, gridY - fgridY + 1);
	vector2<float> g4(gridX - fgridX	, gridY - fgridY + 1);

	// Retrive the 4 random grid vectors.

	float ang1 = getAngle(gridX    , gridY    );
	float ang2 = getAngle(gridX + 1, gridY    );
	float ang3 = getAngle(gridX + 1, gridY + 1);
	float ang4 = getAngle(gridX    , gridY + 1);

	// This can be optimized using lookup tables.
	vector2<float> vec1(cos(ang1), sin(ang1));
	vector2<float> vec2(cos(ang2), sin(ang2));
	vector2<float> vec3(cos(ang3), sin(ang3));
	vector2<float> vec4(cos(ang4), sin(ang4));

	// Calculate the cross products of the 4 grid vectors and the gradiant.

	float cross1 = vec1.x * g1.x + vec1.y * g1.y;
	float cross2 = vec2.x * g2.x + vec2.y * g2.y;
	float cross3 = vec3.x * g3.x + vec3.y * g3.y;
	float cross4 = vec4.x * g4.x + vec4.y * g4.y;

	// All that's left is bilinear interpolation.

	float xVal = fgridX - gridX;
	float yVal = fgridY - gridY;

	float val12 = xVal * cross1 + (1 - xVal) * cross2;
	float val34 = xVal * cross3 + (1 - xVal) * cross4;
	float val1234 = yVal * val12 + (1 - yVal) * val34;

	return val1234;

}

//================================================================================
// Loads the grid angle values from file, or generates them if data doesn't exist.

void PerlinNoise::Octave::getGridAngles(std::fstream* file, PerlinNoise* pn) {

	if (file->eof()) {

		// No octave data in the file, generate chunk octave.

		gridAgls.resize((harmonic + 1) * (harmonic + 1));

		for (int i = 0; i < (harmonic + 1) * (harmonic + 1); i++) {

			// Generate random vector angle based on position then save to file.
			gridAgls.at(i) = generateRandomAngle(i / (harmonic + 1), i % (harmonic + 1), pn);
			file->write((char *) &gridAgls.at(i), sizeof(float));

		}

	}

	else {

		// Read chunk octave from file.

		gridAgls.resize((harmonic + 1) * (harmonic + 1));

		for (int i = 0; i < (harmonic + 1) * (harmonic + 1); i++) {

			file->read((char*) &gridAgls.at(i), sizeof(float));

		}

	}

}

//================================================================================
// Generate a random vector with magnitude 1.

float PerlinNoise::Octave::generateRandomAngle(long x, long y, PerlinNoise* pn) {

	// Credit goes to Griffin :)
	pn->setSeed(pn->getSeed());
	pn->setSeed(pn->getRng() + x);
	pn->setSeed(pn->getRng() + y);
	pn->setSeed(pn->getRng());

	// Return random angle.
	return pn->getFloat();

}

//================================================================================
// Returns the final height value at position (x, y).

float PerlinNoise::Chunk::getValue(float x, float y) {

	float value = 0;

	for (int o = 0; o < octaveLimit; o++) {

		value += octaves.at(o).getValue(x, y);

	}

	return value;

}

//================================================================================
// Attempts to load chunk from file. If chunk doesn't exist then it automatically generates and saves the chunk.

void PerlinNoise::Chunk::loadChunk(std::string id, long x, long y, PerlinNoise* pn) {

	std::fstream* file = pn->getFilePointer();

	// Chunks will always be stored in a folder called "perlin-chunks" located in the working directory.
	std::string fileName = "perlin-chunks/" + id +
		"." + std::to_string(x) +
		"." + std::to_string(y) +
		".pc";

	unsigned int octaveLimit = pn->getOctaveLimit();

	// Check if the file already exists.
	struct stat buffer;
	bool alreadyExists = (stat(fileName.c_str(), &buffer) == 0);

	// Open the file beforehand.
	file->open(fileName, std::ios::binary);

	if (alreadyExists) {

		// File already exists, load the chunk data.

		file->read((char *) &octaveLimit, sizeof(unsigned int));
		file->read((char *) &x, sizeof(long));
		file->read((char *) &y, sizeof(long));

	}

	else if (file) {

		// If the file doesn't already exist, create a new one.

		// Decide what to set the octave limit first.

		octaves.resize(octaveLimit);

		// Then write to file as metadata.

		file->write((char *) &octaveLimit, sizeof(unsigned int));
		file->write((char *) &x, sizeof(long));
		file->write((char *) &y, sizeof(long));

	}

	else {

		// If the file can't be created.

		return;

	}

	// Octave::getGridAngles() already checks whether it exists
	// in the file or not so no need to put it in the if-else group.
	for (int o = 0; o < octaveLimit; o++) {

		octaves.at(o).getGridAngles(file, pn);

	}

	file->close();

}

//================================================================================

// DEPRECATED.
// DEPRECATED.
// DEPRECATED.

/*
float PerlinNoise::getValue(float x, float y) {

	// Calculate which chunk to use first.
	vector2<long> chunkPos(x * freq, y * freq);

	// Calculate local position within the chunk and retrive the value.

	vector2<float> localPos(x * freq - chunkPos.x, y * freq - chunkPos.y);

	Chunk* chunk = getChunk(chunkPos.x, chunkPos.y);

}
*/

//================================================================================

std::vector<float> PerlinNoise::getChunk(long x, long y, unsigned int res) {

	// Check to see if the chunk's already loaded.

	for (Chunk c : chunks) {

		if (c.getPos().x == x && c.getPos().y == x) {

			// If the requested chunk is found already loaded.

			std::vector<float> chunkList((res + 1) * (res + 1));

			for (int y = 0; y < res + 1; y++) {
				for (int x = 0; x < res + 1; x++) {

					// Calcualte x and y pos, then get the heightvalue and store it to list.

					float xPos = x / float(res);
					float yPos = y / float(res);

					chunkList.at(y * (res + 1) + x) = c.getValue(xPos, yPos);

				}
			}

			return chunkList;

		}

	}

	// If chunk wasn't found already loaded, call Chunk::loadChunk().

	Chunk c;
	c.loadChunk(id, x, y, this);

	// Add newly loaded chunk onto the list.
	chunks.push_back(c);

}