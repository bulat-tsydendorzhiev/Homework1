#include <stdio.h>
#include <locale.h>

int writeData(int* number1, int* number2)
{
    int amountOfValues;
    char check;

    printf("¬ведите длину сортируемого массива: ");
    amountOfValues = scanf_s("%d%c", number1, &check);
    
}

int tests(void)
{

}

int main(void)
{
    setlocale(LC_ALL,"Rus");
	return 0;
}