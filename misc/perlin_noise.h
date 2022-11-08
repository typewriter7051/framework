#include <random>
#include <fstream>
#include <vector>

class PerlinNoise {
public:

	//--------------------------------------------------------------------------------
	// Constructors & Destructors.

	PerlinNoise() : seed(0), freq(1) {

		rng.seed(seed);

		dis = std::make_unique<std::uniform_real_distribution<float>>(0, 6.2831853);

	}

	PerlinNoise(long s, float f, float xP, float yP) : seed(s), freq(f) {

		rng.seed(seed);

		dis = std::make_unique<std::uniform_real_distribution<float>>(0, 6.2831853);

	}

	//--------------------------------------------------------------------------------
	// Getters & Setters.

	float getValue(float x, float y);

	std::vector<float> getChunk(long x, long y, unsigned int res);

	long getSeed() { return seed; }

	void setSeed(long s) { rng.seed(s); }

	long getRng() { return rng(); }

	float getFloat() { return (*dis)(rng); }

	unsigned int getOctaveLimit() { return uniOctaveLimit; }

	std::fstream* getFilePointer() { return &file; }

private:

	//--------------------------------------------------------------------------------
	// Quick and small 2D vector class.

	template <typename T>
	struct vector2 {

		vector2() : x(0), y(0) {}

		vector2(T a, T b) : x(a), y(b) {}

		T x;
		T y;

	};

	//--------------------------------------------------------------------------------
	// Octave class.

	class Octave {
	public:

		vector2<float> phase;
		int harmonic;
		float amp;

		std::vector<float> gridAgls;

		float getValue(float x, float y);

		void getGridAngles(std::fstream* file, PerlinNoise* pn);

	private:

		float getAngle(int x, int y) { return gridAgls.at(harmonic * y + x); }

		float generateRandomAngle(long x, long y, PerlinNoise* pn);

	};

	//--------------------------------------------------------------------------------
	// Chunk class.

	class Chunk {
	public:

		Chunk() {}

		Chunk(vector2<long> p) : pos(p) {}

		float getValue(float x, float y);
		
		void loadChunk(std::string id, long x, long y, PerlinNoise* pn);

		vector2<long> getPos() { return pos; }

	private:

		vector2<long> pos;

		int octaveLimit;

		std::vector<Octave> octaves;

	};

	//--------------------------------------------------------------------------------
	// Private variables.

	// RNG related stuff.

	std::mt19937 rng;
	std::unique_ptr<std::uniform_real_distribution<float>> dis;

	// File and name handling.

	std::fstream file;
	std::string id;

	// General info.

	long seed;
	float freq;

	// Universal octave limit, can vary between chunks.
	unsigned int uniOctaveLimit;
	std::vector<Chunk> chunks;

	//--------------------------------------------------------------------------------
	// Private helper functions.

	// Save and load chunk info.
	void saveChunkInfo();

	void getChunkInfo();

};