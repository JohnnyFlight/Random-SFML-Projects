#include "Fibonacci.hpp"

Fibonacci::Fibonacci()
{
	_currentStep = 1;
	_stepCount = 2;
	_calculatedSteps = std::vector<unsigned>(2, 1);
}

Fibonacci::Fibonacci(unsigned initialSteps)
{
	_stepCount = initialSteps;
	_calculatedSteps = std::vector<unsigned>(2, 1);

	for (unsigned i = 0; i < initialSteps; i++)
	{
		unsigned size = _calculatedSteps.size();
		_calculatedSteps.push_back(_calculatedSteps[size-1] + _calculatedSteps[size-2]);
	}
}

unsigned Fibonacci::next()
{
	_stepCount++;
	_calculatedSteps.push_back(_calculatedSteps[_calculatedSteps.size()-1] + _calculatedSteps[_calculatedSteps.size()-2]);
	_currentStep = _calculatedSteps[_calculatedSteps.size() - 1];

	return _currentStep;
}

unsigned Fibonacci::calculateValue(unsigned position)
{
	//	If position < steps size
	if (position < _calculatedSteps.size())
	{
		//	Return element in steps
		return _calculatedSteps[position];
	}
	else
	{
		//	Otherwise calculate value up to position
		for (unsigned i = _calculatedSteps.size(); i < position; i++)
		{
			_calculatedSteps.push_back(_calculatedSteps[_calculatedSteps.size()-1] + _calculatedSteps[_calculatedSteps.size()-2]);
		}

		_currentStep = _calculatedSteps[_calculatedSteps.size() - 1];
		return _currentStep;
	}
}