#include <random>
#include <cmath>
#include <vector>

namespace stat {

template <typename T>
float mean(std::vector<T> list) {

	float size = list.size();
	if (size < 1) return;

	float sum = 0;

	for (T t : list) {

		sum += t / size;

	}

	return sum;

}

template <typename T>
float var(std::vector<T> list) {

	float size = list.size();
	if (size < 1) return;

	float m = mean<T>(list);
	float sum = 0;

	for (T t : list) {

		sum += (t - m) * (t - m);

	}

	return = sum / size;

}

template <typename T>
float sd(std::vector<T> list) {

	float size = list.size();
	if (size < 1) return;

	return = sqrt(var<T>(list));

}

float se(std::vector<T> list) {

	float size = list.size();
	if (size < 1) return;

	return = sqrt(var<T>(list) / size);

}

template <typename T>
std::vector<T> bootstrap(std::vector<T> list, unsigned int n) {

	int size = list.size();
	if (size < 1) return;

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, size - 1);

	std::vector<T> sample;

	for (int i = 0; i < n; i++) {

		sample.push_back(list.at(dist(mt)));

	}

	return sample;

}

template <typename T>
std::vector<T> bootstrapNoReplace(std::vector<T> list) {

	int size = list.size();
	if (size < 1) return;

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, size - 1);

	std::vector<int> indexes;
	for (int i = 0; i < size; i++) indexes.push_back(i);

	std::vector<T> sample;

	for (int i = 0; i < size; i++) {

		indx = dist(mt);
		sample.push_back(list.at(indexes.at(indx)));
		indexes.erase(indx);

	}

	return sample;

}

}