#include <random>

namespace tmools
{

class RandomDoubleGenerator
{
public:
	static RandomDoubleGenerator& GetInstance();
	double generate();
	double generate(const double lb, const double ub);

private:
	static constexpr double          lowerBound = 0.0;
	static constexpr double          upperBound = 1.0;
	std::random_device               rd;
	std::mt19937                     gen;
	std::uniform_real_distribution<> dis;
	RandomDoubleGenerator() : rd(), gen(rd()), dis(lowerBound, upperBound)
	{
	}
};

inline RandomDoubleGenerator& RandomDoubleGenerator::GetInstance()
{
	static RandomDoubleGenerator instance;
	return instance;
}

double generate_random_double();
double generate_random_double(const double lb, const double ub);

inline double RandomDoubleGenerator::generate()
{
	return dis(gen);
}

inline double RandomDoubleGenerator::generate(const double lb, const double ub)
{
	return lb + (ub - lb) * generate();
}

inline double generate_random_double()
{
	return RandomDoubleGenerator::GetInstance().generate();
}

inline double generate_random_double(const double lb, const double ub)
{
	return RandomDoubleGenerator::GetInstance().generate(lb, ub);
}

}

