#include <iostream>
#include <Windows.h>
#include <math.h>

class Equation
{
public:
    double firstCoef, secondCoef, thirdCoef;

    Equation(double a, double b, double c)
    {
        firstCoef = a;
        secondCoef = b;
        thirdCoef = c;
    }
    double getD()
    {
        return secondCoef * secondCoef - (4 * firstCoef * thirdCoef);
    }

    double getRootD()
    {
        return std::sqrt(getD());
    }

    //Является ли квадратным
    bool isQuadratic()
    {
        return firstCoef > 0;
    }

    //Существуют ли корни квадратного уравнения
    bool isRootsExit()
    {
        return getD() >= 0;
    }

    void firstRoot()
    {
        double result = (-secondCoef + getRootD()) / (2*firstCoef);
        std::cout << "Корень первый = " << result;
    }

    void secondRoot()
    {
        double result = (-secondCoef - getRootD()) / (2 * firstCoef);
        std::cout << "Корень второй = " << result;
    }

    void solveQuadraticEquation()
    {
        //HANDLE hThread1, hThread2;
        //DWORD IDThread1, IDThread2;
        //
        //hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)firstRoot, NULL, 0, &IDThread1);
        //hThread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)secondRoot, NULL, 0, &IDThread2);
        //
        //
        //WaitForSingleObject(hThread1, INFINITE);
        //WaitForSingleObject(hThread2, INFINITE);
        //
        //CloseHandle(hThread1);
        //CloseHandle(hThread2);
     }

    //Является ли линейным
    bool isLinear()
    {
        return !isQuadratic() && secondCoef > 0;
    }

    void solveLinearEquation()
    {
        double result = -thirdCoef / secondCoef;
        std::cout << "Корень = "<<result;
    }

    //Является ли уравнение
    bool isNotEquation()
    {
        return !isQuadratic() && !isLinear();
    }

    void solveNotEquation()
    {
        bool result = thirdCoef == 0 ? true : false;

        if (result)
            std::cout << "Решение все действительные числа";
        else
            std::cout << "Решений на действительном множестве нет";
    }
};

void firstRoot(Equation eq)
{
    double result = (-eq.secondCoef - eq.getRootD()) / (2 * eq.firstCoef);
    std::cout << "Корень первый = " << result <<std::endl;
}

void secondRoot(Equation eq)
{
    
    double result = (-eq.secondCoef + eq.getRootD()) / (2 * eq.firstCoef);    
    std::cout << "Корень второй = "<< result << std::endl;
}

int main()
{
    setlocale(LC_ALL, "rus");
    double firstCoef=1, secondCoef=2, thirdCoef=-3;
    Equation equation = Equation(firstCoef, secondCoef, thirdCoef);

    std::cout << "d = " << equation.getD() << std::endl;
    std::cout << "a = " << equation.firstCoef << std::endl;
    std::cout << "b = " << equation.secondCoef << std::endl;
    std::cout << "c = " << equation.thirdCoef << std::endl;

    if (equation.isNotEquation())
    {
        equation.solveNotEquation();
    }
    else if (equation.isLinear())
    {
        equation.solveLinearEquation();
    }
    else if(equation.isRootsExit())
    {
        HANDLE hThread1, hThread2;
        DWORD IDThread1, IDThread2;

        hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)firstRoot, &equation, 0, &IDThread1);
        if (hThread1 == NULL)
            return GetLastError();
        hThread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)secondRoot, &equation, 0, &IDThread2);
        if (hThread2 == NULL)
            return GetLastError();

        WaitForSingleObject(hThread1, INFINITE);
        WaitForSingleObject(hThread2, INFINITE);

        CloseHandle(hThread1);
        CloseHandle(hThread2);
    }
    else
    {
        std::cout << " Корней нет на вещественном множестве";
    }

}

