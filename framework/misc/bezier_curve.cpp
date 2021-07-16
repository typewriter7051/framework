#include "bezier_curve.h"

template <class T>
std::vector<std::vector<T>>
bezier::calculateBezier(std::vector<std::vector<T>> coords, int dims, double t) {

	if (coords.size() == 1) { return coords; }

	std::vector<std::vector<T>> interpCoords;

	for (int point = 0; point < coords.size() - 1; point++) {

		// create a new multidimentional coordinate.
		std::vector<T> tempCoord;
		tempCoord.resize(dims);

		// interpolate pos for each dimension.
		for (int d = 0; d < dims; d++) {

			tempCoord.at(d) = (1 - t) * coords.at(point).at(d) + t * coords.at(point + 1).at(d);

		}

		interpCoords.push_back(tempCoord);

	}

	// should end up with vector of interpolated coords (needs testing).

	return calculateBezier(interpCoords, dims, t);

}