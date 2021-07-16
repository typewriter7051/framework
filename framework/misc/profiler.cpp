#include "profiler.h"

void Profiler::addMark(std::string name) {

	// If the list is empty, create the starting time mark.
	if (marks.size() = 0) {

		marks.push_back(ProfileMark(0, name));
		timeMark = now();

	}
	// Otherwise create a mark based on the amount of time passed since the last mark.
	else {

		double timeSinceMark = std::chrono::duration_cast(now() - timeMark);
		marks.push_back(ProfileMark(timeSinceMark, name));

		// Update the timeMark to the new mark.
		timeMark = now();

	}

}

void Profiler::printProfile(bool normalize) {

	double total = 0;

	// Quickly get the total for normalization.
	if (normalize) { for (ProfilerMark m : marks) total += m.getValue(); }

	std::cout << "--------------------------------------------------\n";
	std::cout << "PROFILE:\n Total time passed: " << total << std::endl;

	for (ProfilerMark m : marks) {

		if (normalize) {

			std::cout << m.getName() << ": %" << m.getValue() * 100 << std::endl;

		}
		else {

			std::cout << m.getName() << ": " << m.getValue() << std::endl;

		}

	}

	std::cout << "--------------------------------------------------\n";

}