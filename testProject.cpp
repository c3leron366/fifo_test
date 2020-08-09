// testProject.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "test_fifo.h"

int main()
{
    unsigned char kek[40];
    unsigned int data_count;
    unsigned int packet_id;
    test_fifo< 40, 10, 40 > t;

    test_fifo< 10, 10, 10 > t2;
    
    std::cout << sizeof(t) << std::endl;
    std::cout << sizeof(t2) << std::endl;
    unsigned char test[] = "test";
    
    int id = 0;
    
    if (t.Push(test, 4, id) == false)
        std::cout << "push error" << std::endl;
    else
        std::cout << "push ok" << std::endl;
    if (t.Pop((unsigned char*)kek, 40, data_count, packet_id) == false)
        std::cout << "pop error" << std::endl;
    else {
        std::cout << "packet id:" << packet_id << std::endl;
        std::cout << "data count:" << data_count << std::endl;
        std::cout << "string:" << kek << std::endl;
    }
    if (t.Pop((unsigned char*)kek, 40, data_count, packet_id) == false)
        std::cout << "pop error" << std::endl;
    else {
        std::cout << "packet id:" << packet_id << std::endl;
        std::cout << "data count:" << data_count << std::endl;
        std::cout << "string:" << kek << std::endl;
    }

    for (id = 0;id < 20;id++)
    {
        if (t.Push(test, 4, id) == false)
            std::cout << "push error" << std::endl;
        else
            std::cout << "push ok" << std::endl;
    }
    
    
    for (id = 0;id < 20;id++)
    {
        if (t.Pop((unsigned char*)kek, 40, data_count, packet_id) == false)
            std::cout << "pop error" << std::endl;
        else {
            std::cout << "packet id:" << packet_id << std::endl;
            std::cout << "data count:" << data_count << std::endl;
            std::cout << "string:" << kek << std::endl;
        }
        
    }
    for (id = 0;id < 20;id++)
    {
        if (t.Push(test, 4, id) == false)
            std::cout << "push error" << std::endl;
        else
            std::cout << "push ok" << std::endl;
            
    }


    for (id = 0;id < 20;id++)
    {
        if (t.Pop((unsigned char*)kek, 40, data_count, packet_id) == false)
            std::cout << "pop error" << std::endl;
        else {
            std::cout << "packet id:" << packet_id << std::endl;
            std::cout << "data count:" << data_count << std::endl;
            std::cout << "string:" << kek << std::endl;
        }

    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
