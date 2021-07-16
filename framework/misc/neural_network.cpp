#include <vector>

template <class T> // either float of double.
class Node {

	static unsigned int lookupRes;
	T multFactor; // for efficiency.
	static std::vector<T> sigmoidLookup; // range of lookup is from real values -4 to 4.

	T value;

	Node() {

		lookupRes = 80;
		multFactor = lookupRes / (T)8.0;

	}

	void sigmoid() {

		if (value > 4 - 1 / multFactor) value = 1;
		else if (value < -4) value = -1;
		else value = sigmoidLookup.at((value + 4) * multFactor);

	}

};

template <class T> // either float of double.
class LayerConnection {

	unsigned int L1_width, L2_width;

	std::vector<T> weights;
	std::vector<T> biases;

	LayerConnection(unsigned int l1, unsigned int l2) {

		L1_width = l1; // number of nodes in previous layer.
		L2_width = l2; // number of nodes in next layer.

		biases.resize(l2);
		weights.resize(l1 * l2);

	}

};

class Layer {

	std::vector<LayerConnection*> prevCons, nextCons;

	unsigned int width; // number of nodes in the layer.

	float xPos, yPos; // for GUI only.

	Layer() {



	}

	~Layer() {

		delete prevCons, nextCons; // may cause bugs if other layers have same connections but idk.
		prevCons = nextCons = null;

	}

};