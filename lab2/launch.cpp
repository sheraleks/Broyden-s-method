#include <windows.h>
#include <iostream>
#include "Broyden.h"

//Квадратичная функция
double func(vect_2d arg){
	double x = arg.x;
	double y = arg.y;
	return 100*(y-x)*(y-x) + (1-x)*(1-x);
}

vect_2d grad_func(vect_2d arg){
	double x = arg.x;
	double y = arg.y;
	return vect_2d(202*x-200*y-2, -200*x+200*y); 
}

//Функция Розенброка
double func1(vect_2d arg){
	return 100*(arg.y - arg.x*arg.x)*(arg.y - arg.x*arg.x) + (1-arg.x)*(1-arg.x);
}

vect_2d grad_func1(vect_2d arg){
	return vect_2d(400*arg.x*arg.x*arg.x - 400*arg.x*arg.y + 2*arg.x - 2, 200*(arg.y - arg.x*arg.x)); 
}

//Функция из варианта: 3 / (1 + (x - 2) * (x - 2) + ((y - 2) / 2) * ((y - 2) / 2)) + 2 / (1 + ((x - 2) / 3) * ((x - 2) / 3) + (y - 3) * (y - 3))
double func2(vect_2d arg){
	double x = arg.x;
	double y = arg.y;
	double first = 3.0 / (1 + (x - 2) * (x - 2) + ((y - 2) / 2.0) * ((y - 2) / 2.0));
	double second = 2.0 / (1 + ((x - 2) / 3.0) * ((x - 2) / 3.0) + (y - 3) * (y - 3));
	return first + second;
	//return (-3.0 / (1.0 + (arg.x - 3) * (arg.x - 3) / 4.0 + (arg.y - 2) * (arg.y - 2)) - 3.0 / (1.0 + (arg.x - 1) * (arg.x - 1) + (arg.y - 2) * (arg.y - 2) / 9.0));
}

vect_2d grad_func2(vect_2d arg){
	double x = arg.x, y = arg.y;
	double denom1 = 1 + (x - 2) * (x - 2) + (y - 2) * (y - 2) / 4.0;
	double denom2 = 1 + (x - 2) * (x - 2) / 9.0 + (y - 3) * (y - 3);
	double grad_x = -2 * (x - 2) * (3 / (denom1 * denom1) + 2.0 / 9.0 / (denom2 * denom2));
	double grad_y = 3 * (-y / 2.0 + 1) / (denom1 * denom1) + 2 * (-2 * y + 6) / (denom2 * denom2);
	return vect_2d(grad_x, grad_y);
}


int main(){
	auto f = func1;
	auto g_f = grad_func1;

	Broyden our_meth;
	our_meth.init(f, g_f, 1E-3, 5000);
	vect_2d start(2, 2);
	vect_2d min;

	our_meth.minimization(start, min);

	printf("%.15lf\t%.15lf\n%.15lf\n",min.x, min.y, f(min));
	std::cout.precision(10);
	std::cout << std::scientific;
	std::cout << min.x << " " << min.y << "\n";
	std::cout << f(min) << "\n";
	system("pause");

}