#pragma once

#include <vector>

class Fibonacci
{
public:
	Fibonacci();
	Fibonacci(unsigned initiatSteps);

	inline unsigned current() { return _currentStep; }
	unsigned next();
	unsigned calculateValue(unsigned position);

	inline unsigned calculatedSteps() { return _calculatedSteps.size(); }
protected:
	std::vector<unsigned> _calculatedSteps;
	unsigned _currentStep;
	unsigned _stepCount;
private:

};