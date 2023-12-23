#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <iostream>
#include <limits>

#include <chrono>
#include <time.h>
#include <stdlib.h>

// swapping two variables
void valuesSwap(int* left, int* right)
{
    if(left == nullptr || right == nullptr)
    {
        return;
    }

    int temp { *left };

    *left  = *right;
    *right = temp;
}

// array creating and deleting
int* arrayCreate(const int x, const int y = 1, const int z = 1)
{
    if(x < 1 || y < 1 || z < 1)
    {
        return nullptr;
    }

    // array[z][y][x] == array[z * y * x]
    return new(std::nothrow) int[z * y * x] { };
}

int* arrayDelete(int* array)
{
    if(array != nullptr)
    {
        delete[] array;
    }

    return nullptr;
}

// array filling
void arrayFillAscending(int* array, const int x, const int y = 1, const int z = 1)
{
    if(array == nullptr)
    {
        return;
    }

    const int arraySize { z*y*x };

    for(int i { }; i < arraySize; ++i)
    {
        array[i] = i;
    }
}

void arrayFillDescending(int* array, const int x, const int y = 1, const int z = 1)
{
    if(array == nullptr)
    {
        return;
    }

    const int arraySize { z*y*x };

    for(int i { }; i < arraySize; ++i)
    {
        array[i] = (arraySize - 1) - i;
    }
}

void arrayFillShuffle(int* array, const int x, const int y = 1, const int z = 1)
{
    if(array == nullptr)
    {
        return;
    }

    srand(time(nullptr));

    arrayFillAscending(array, x, y, z);

    const int arraySize { z*y*x };

    for(int i { }; i < arraySize; ++i)
    {
        const int randomIndex { rand() % (arraySize - 1) };

        valuesSwap(&array[i], &array[randomIndex]);
    }
}

void arrayFillRandom(int* array, const int x, const int y = 1, const int z = 1)
{
    if(array == nullptr)
    {
        return;
    }

    srand(time(nullptr));

    const int arraySize { z*y*x };

    for(int i { }; i < arraySize; ++i)
    {
        array[i] = (rand() - (RAND_MAX + 1) / 2);
    }
}

// array sorting
void arraySortBubble(int* array, const int x, const int y = 1, const int z = 1)
{
    if(array == nullptr)
    {
        return;
    }

    const int arraySize { z*y*x };

    int right { arraySize - 1 };

    while(right > 0)
    {
        for(int i { }; i < right; ++i)
        {
            int* a { &array[i] }, * b { &array[i + 1] };

            if(*a > *b)
            {
                valuesSwap(a, b);
            }
        }

        right -= 1;
    }
}

void arraySortShaker(int* array, const int x, const int y = 1, const int z = 1)
{
    if(array == nullptr)
    {
        return;
    }

    const int arraySize { z*y*x };

    // a left, a right and the last sorted indices
    int left { }, right { arraySize - 1 }, sorted { };

    do
    {
        for(int i { left }; i < right; ++i)
        {
            int* a { &array[i] }, * b { &array[i + 1] };

            if(*a > *b)
            {
                valuesSwap(a, b);

                sorted = i;
            }
        }

        right = sorted;

        for(int i { right }; i > left; --i)
        {
            int* a { &array[i] }, * b { &array[i - 1] };

            if(*a < *b)
            {
                valuesSwap(a, b);

                sorted = i;
            }
        }

        left = sorted;
    }
    while(left < right);
}

void arraySortSelection(int* array, const int x, const int y = 1, const int z = 1)
{
    if(array == nullptr)
    {
        return;
    }

    const int arraySize { z*y*x };

    for(int i { }; i < arraySize; ++i)
    {
        int indexOfMin { i };

        // finding and index of the smallest value
        {
            int min { array[i] };

            for(int j { i + 1 }; j < arraySize; ++j)
            {
                if(array[j] < min)
                {
                    min = array[j];
                    indexOfMin = j;
                }
            }
        }

        // swapping values of current index and index of the smallest value
        valuesSwap(&array[i], &array[indexOfMin]);
    }
}

// array printing
void arrayPrint(int* array, const int x, const int y = 1, const int z = 1)
{
    // z
    for(int k { }; k < z; ++k)
    {
        // y
        for(int j { }; j < y; ++j)
        {
            std::cout << "[";

            // x
            for(int i { }; i < x; ++i)
            {
                const int xyzIndex { k*y*x + j*x + i };

                std::cout << array[xyzIndex];

                if(i + 1 < x)
                {
                   std::cout << ", ";
                }
            }

            std::cout << "]\n";
        }

        if(k + 1 < z)
        {
           std::cout << "\n";
        }
    }

    std::cout << "\n";
}

struct tableValues_t
{
    int
    arrayX { },
    arrayY { },
    arrayZ { },

    /*
           bubbleSorted,    bubbleShuffled,    bubbleUnsorted,
           shakerSorted,    shakerShuffled,    shakerUnsorted,
        selectionSorted, selectionShuffled, selectionUnsorted
    */
    array[3 * 3] { };
};

void arrayPrintTable(tableValues_t* table)
{
    char measureTable[256 + 1]
    {
        "array 0D                                        \n"
        "          | sorted     | shuffled   | unsorted  \n"
        "   bubble | 0       ms | 0       ms | 0       ms\n"
        "   shaker | 0       ms | 0       ms | 0       ms\n"
        "selection | 0       ms | 0       ms | 0       ms\n"
    };

    char number[16 + 1] { };

    const int dimentionCount { /*(int)(table->arrayX > 1)*/ 1 + (int)(table->arrayY > 1) + (int)(table->arrayZ > 1) }, size { table->arrayX * table->arrayY * table->arrayZ };
    itoa(dimentionCount, number, 10);
    strncpy(measureTable + 6, number, strlen(number));

    for(int y { }; y < 3; ++y)
    {
        for(int x { }; x < 3; ++x)
        {
            itoa(table->array[y*3 + x], number, 10);
            strncpy(measureTable + 49*(y + 2) + 12 + 13*x, number, strlen(number));
        }
    }

    std::cout << measureTable;
}

using arrayFunction_t = void(*)(int* array, const int x, const int y, const int z);

int64_t arrayMeasureTime(arrayFunction_t fillFunction, arrayFunction_t sortFunction, int* array, const int x, const int y = 1, const int z = 1)
{
    fillFunction(array, x, y, z);

    int64_t elapsedMs { };
    {
        auto begin { std::chrono::steady_clock::now() };

        sortFunction(array, x, y, z);

        auto end { std::chrono::steady_clock::now() };

        elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    }

    return elapsedMs;
}

// array make test and print table
void arrayMakeTest(const int x, const int y = 1, const int z = 1)
{
    int* array { arrayCreate(x, y, z) };
    if(array == nullptr)
    {
        std::cout << "Error arrayCreate!\n";

        return;
    }

    tableValues_t table { };

    table.arrayX = x;
    table.arrayY = y;
    table.arrayZ = z;

    // bubble
    table.array[0] = arrayMeasureTime(arrayFillAscending , arraySortBubble, array, x, y, z);
    table.array[1] = arrayMeasureTime(arrayFillShuffle   , arraySortBubble, array, x, y, z);
    table.array[2] = arrayMeasureTime(arrayFillDescending, arraySortBubble, array, x, y, z);

    // shaker
    table.array[3] = arrayMeasureTime(arrayFillAscending , arraySortShaker, array, x, y, z);
    table.array[4] = arrayMeasureTime(arrayFillShuffle   , arraySortShaker, array, x, y, z);
    table.array[5] = arrayMeasureTime(arrayFillDescending, arraySortShaker, array, x, y, z);

    // bubble
    table.array[6] = arrayMeasureTime(arrayFillAscending , arraySortSelection, array, x, y, z);
    table.array[7] = arrayMeasureTime(arrayFillShuffle   , arraySortSelection, array, x, y, z);
    table.array[8] = arrayMeasureTime(arrayFillDescending, arraySortSelection, array, x, y, z);

    arrayPrintTable(&table);

    array = arrayDelete(array);
}

// console
void consoleCodepage(unsigned int codepage)
{
    SetConsoleOutputCP(codepage);
    SetConsoleCP(codepage);
}

int consoleRead()
{
    int i { };
    std::cin >> i;

    if(std::cin.fail())
    {
        std::cin.clear();
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return i;
}

void consolePause()
{
    [[maybe_unused]] int wait { std::cin.get() };
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// menu
void menuCompareArrayAll()
{
    while(true)
    {
        // clear the console
        system("cls");

        // task
        {
            // array 1D
            arrayMakeTest(10'000, 1, 1);
            std::cout << "\n";

            // array 2D
            arrayMakeTest(10'0, 100, 1);
            std::cout << "\n";

            // array 3D
            arrayMakeTest(10'0, 10, 10);
        }

        // print menu items
        std::cout <<
        "\n"
        "compare array all:\n"
        "1) back\n"
        "> ";

        // get selection
        int i { consoleRead() };

        // handle selection
        if(i == 1)
        {
            break;
        }
    }
}

void menuCompareArray1DWith2D()
{
    while(true)
    {
        // clear the console
        system("cls");

        // task
        {
            // array 1D
            arrayMakeTest(10'000, 1, 1);
            std::cout << "\n";

            // array 2D
            arrayMakeTest(10'0, 100, 1);
        }

        // print menu items
        std::cout <<
        "\n"
        "compare array 1D with 2D:\n"
        "1) back\n"
        "> ";

        // get selection
        int i { consoleRead() };

        // handle selection
        if(i == 1)
        {
            break;
        }
    }
}

void menuCompareArray1DWith3D()
{
    while(true)
    {
        // clear the console
        system("cls");

        // task
        {
            // array 1D
            arrayMakeTest(10'000, 1, 1);
            std::cout << "\n";

            // array 3D
            arrayMakeTest(10'0, 10, 10);
        }

        // print menu items
        std::cout <<
        "\n"
        "compare array 1D with 3D:\n"
        "1) back\n"
        "> ";

        // get selection
        int i { consoleRead() };

        // handle selection
        if(i == 1)
        {
            break;
        }
    }
}

void menuCompareArray2DWith3D()
{
    while(true)
    {
        // clear the console
        system("cls");

        // task
        {
            // array 2D
            arrayMakeTest(10'0, 100, 1);
            std::cout << "\n";

            // array 3D
            arrayMakeTest(10'0, 10, 10);
        }

        // print menu items
        std::cout <<
        "\n"
        "compare array 2D with 3D:\n"
        "1) back\n"
        "> ";

        // get selection
        int i { consoleRead() };

        // handle selection
        if(i == 1)
        {
            break;
        }
    }
}

void menuCompareArray3DWith2D()
{
    while(true)
    {
        // clear the console
        system("cls");

        // task
        {
            // array 3D
            arrayMakeTest(10'0, 10, 10);
            std::cout << "\n";

            // array 2D
            arrayMakeTest(10'0, 100, 1);
        }

        // print menu items
        std::cout <<
        "\n"
        "compare array 3D with 2D:\n"
        "1) back\n"
        "> ";

        // get selection
        int i { consoleRead() };

        // handle selection
        if(i == 1)
        {
            break;
        }
    }
}

void menuCompareArray1DWith()
{
    while(true)
    {
        // clear the console
        system("cls");

        // task
        {

        }

        // print menu items
        std::cout <<
        "compare array 1D with:\n"
        "1) 2D\n"
        "2) 3D\n"
        "3) back\n"
        "> ";

        // get selection
        int i { consoleRead() };

        // handle selection
        // compare array 1D with 2D
        if(i == 1)
        {
            menuCompareArray1DWith2D();
        }
        // compare array 1D with 3D
        else
        if(i == 2)
        {
            menuCompareArray1DWith3D();
        }
        // back
        else
        if(i == 3)
        {
            break;
        }
    }
}

void menuMeasureArray1D()
{
    while(true)
    {
        // clear the console
        system("cls");

        // task
        arrayMakeTest(10'000, 1, 1);

        // print menu items
        std::cout <<
        "\n"
        "measure array 1D:\n"
        "1) back\n"
        "> ";

        // get selection
        int i { consoleRead() };

        // handle selection
        if(i == 1)
        {
            break;
        }
    }
}

void menuActions()
{
    while(true)
    {
        // clear the console
        system("cls");

        // task
        {

        }

        // print menu items
        std::cout <<
        "actions:\n"
        "1) measure array 1D\n"
        "2) compare array 1D with...\n"
        "3) compare array 2D with 3D\n"
        "4) compare array 3D with 2D\n"
        "5) compare array all\n"
        "6) exit\n> ";

        // get selection
        int i { consoleRead() };

        // handle selection
        // measure array 1D
        if(i == 1)
        {
            menuMeasureArray1D();
        }
        // compare array 1D with...
        else
        if(i == 2)
        {
            menuCompareArray1DWith();
        }
        // compare array 2D with 3D
        else
        if(i == 3)
        {
            menuCompareArray2DWith3D();
        }
        // compare array 3D with 2D
        else
        if(i == 4)
        {
            menuCompareArray3DWith2D();
        }
        // compare array all
        else
        if(i == 5)
        {
            menuCompareArrayAll();
        }
        // exit
        else
        if(i == 6)
        {
            break;
        }
    }
}

// main entry
int main()
{
    consoleCodepage(1251);

    menuActions();

    // consolePause();

    return 0;
}