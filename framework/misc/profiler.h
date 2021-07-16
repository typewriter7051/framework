#include <chrono>
#include <string>
#include <vector>

// Basic profiler mark containing the value and name.
// You can only define via constructor to prevent future alteration.
class ProfilerMark {
public:

	ProfileMark() {}
	ProfileMark(double v, std::string n) : value(v), name(n) {}

	double getValue() { return value; }
	std::string getName() { return name; }

private:

	double value;
	std::string name;
};

// Only profiles time and numerical values (if you wish to input them manually).
class Profiler {
public:

	// I don't reset timeMark here since it already gets
	// reset upon adding the first mark in the list.
	void reset() { marks.clear(); }

	// Used for time benchmarking.
	void addMark(std::string name) {}


	void printProfile(bool normalize) {}

protected:

	std::vector<ProfilerMark> marks;

private:

	typedef std::chrono::high_resolution_clock::now() now();
	std::chrono::steady_clock::time_point timeMark;

};