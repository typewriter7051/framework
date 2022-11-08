#include "../sound.h"

class Utility : public Sound::Effect {
public:

	void setGain(float g);
	void setMix(float m);
	void setWidth(float w);
	void setPan(float p);

private:

	// Value between 0 and 1;
	float width;

	// -1 for left and 1 for right.
	float pan;

	void processBuffer(std::vector<float>&) override;

};