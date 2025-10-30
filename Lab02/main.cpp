#include <iostream>
#include "CNumber.h"

int main() {
    CNumber a(200);
    CNumber b(10);
    CNumber c(-50);
    CNumber d(0);


    std::cout << a.sToStr() << " + " << b.sToStr() << " = " << (a + b).sToStr() << std::endl;
    std::cout << c.sToStr() << " + " << a.sToStr() << " = " << (c + a).sToStr() << std::endl;

    std::cout << a.sToStr() << " - " << b.sToStr() << " = " << (a - b).sToStr() << std::endl;
    std::cout << c.sToStr() << " - " << a.sToStr() << " = " << (c - a).sToStr() << std::endl;

    std::cout << a.sToStr() << " * " << b.sToStr() << " = " << (a * b).sToStr() << std::endl;
    std::cout << c.sToStr() << " * " << b.sToStr() << " = " << (c * b).sToStr() << std::endl;

    std::cout << a.sToStr() << " / " << b.sToStr() << " = " << (a / b).sToStr() << std::endl;
    std::cout << a.sToStr() << " / " << c.sToStr() << " = " << (a / c).sToStr() << std::endl;
    std::cout << a.sToStr() << " / " << d.sToStr() << " = " << (a / d).sToStr() << std::endl;

    return 0;
}
