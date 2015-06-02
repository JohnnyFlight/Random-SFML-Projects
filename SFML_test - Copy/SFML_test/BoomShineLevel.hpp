#pragma once

class BoomShineLevel
{
public:
	BoomShineLevel();
	BoomShineLevel(unsigned particles, unsigned clicks, unsigned goal);

	inline void setParticles(unsigned particles) { _particles = particles; }
	inline void setClicks(unsigned clicks) { _clicks = clicks; }
	inline void setGoal(unsigned goal) { _goal = goal; }

	inline unsigned particles() { return _particles; }
	inline unsigned clicks() { return _clicks; }
	inline unsigned goal() { return _goal; }

private:
	unsigned _particles;
	unsigned _clicks;
	unsigned _goal;
};