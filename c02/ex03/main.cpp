#include "Point.hpp"
#include <iostream>

static void	printResult(const char *label, bool result)
{
	std::cout << label;
	if (result)
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;
}

int	main(void)
{
	Point const	a(0.0f, 0.0f);
	Point const	b(10.0f, 0.0f);
	Point const	c(5.0f, 10.0f);

	Point const	inside(5.0f, 5.0f);
	Point const	outside(12.0f, 5.0f);
	Point const	edge(5.0f, 0.0f);
	Point const	vertex(0.0f, 0.0f);

	std::cout << "Triangle: (0, 0) (10, 0) (5, 10)" << std::endl;
	printResult("Inside    (5, 5):  ", bsp(a, b, c, inside));
	printResult("Outside   (12, 5): ", bsp(a, b, c, outside));
	printResult("On edge   (5, 0):  ", bsp(a, b, c, edge));
	printResult("On vertex (0, 0):  ", bsp(a, b, c, vertex));

	return (0);
}
