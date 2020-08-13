// testProject.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include "test_fifo.h"

unsigned char test[] = "test";
const unsigned int fifo_depth = 3;
const unsigned int packet_size = 10;
const unsigned int fifo_size = 200;
test_fifo< fifo_depth, packet_size, fifo_size > t;


bool test_push_too_many_times()
{
    int errors = 0;

    
    for (int id = 0; id < fifo_depth + 1; id++)
    {

        if (t.Push(test, sizeof(test), id) == false)
            errors += 1;
       
        test[0] += 1;
        //std::cout << "in: " << t.in << std::endl;
    }

    if (errors == 1)
        return true;
    else
        return false;
}


bool test_pop_size_issue()
{
    int errors = 0;
    
    unsigned int data_count;
    unsigned int packet_id;
    unsigned char kek[2];
    
    if (t.Push(test, sizeof(test), 1356) == false)
        errors += 1;
    
    try 
    {
        t.Pop(kek, sizeof(kek), data_count, packet_id);
    }
    catch (...)
    {
        errors += 1;
    }
        
    if (errors > 0)
        return false;
    else
        return true;
}

bool test_pop_too_many_times()
{
    int errors = 0;
    unsigned char kek[40];
    unsigned int data_count;
    unsigned int packet_id;
    
    //std::cout << "test_pop_too_many_times" << std::endl;
    for (int id = 0; id < fifo_depth + 1; id++)
    {

        if (t.Pop(kek,sizeof(kek), data_count, packet_id) == false)
            errors += 1;

        test[0] += 1;
        //std::cout << "out: " << t.out << std::endl;
    }

    if (errors == 1)
        return true;
    else
        return false;
}


bool test_push_then_pop_same_times()
{
    int errors = 0;
    unsigned char kek[40];
    unsigned int data_count;
    unsigned int packet_id;

    for (int id = 0; id < fifo_depth + 1; id++)
    {
        if (t.Push(test, sizeof(test), id) == false)
            errors += 1;
        //std::cout << "count: " << t.count << std::endl;
        if (t.Pop((unsigned char*)kek, 8, data_count, packet_id) == false)
            errors += 1;
        //std::cout << "count: " << t.count << std::endl;
        test[0] += 1;
    }
    if (errors == 0)
        return true;
    else
        return false;
}



int main()
{    
    unsigned int errors = 0;
 
    std::cout << sizeof(t) << std::endl;
    std::cout << t.max_fifo_depth << std::endl;
    std::cout << 0 % 3 << std::endl;
    std::cout << 1 % 3 << std::endl;
    std::cout << 2 % 3 << std::endl;
    std::cout << 3 % 3 << std::endl;


    for (int i = 0;i < 10;i++)
    {
        if (!test_push_too_many_times())
            std::cout << "test_push_too_many_times......FAILED" << std::endl;
        else
            std::cout << "test_push_too_many_times......OK" << std::endl;

        if (!test_pop_too_many_times())
            std::cout << "test_pop_too_many_times.......FAILED" << std::endl;
        else
            std::cout << "test_pop_too_many_times.......OK" << std::endl;
    }
    if (!test_push_then_pop_same_times())
        std::cout << "test_push_then_pop_same_times.......FAILED" << std::endl;
    else
        std::cout << "test_push_then_pop_same_times.......OK" << std::endl;
        
    if (!test_pop_size_issue())
        std::cout << "test_pop_size_issue.......FAILED" << std::endl;
    else
        std::cout << "test_pop_size_issue.......OK" << std::endl;
    

    


    /*
    int id = 0;
    
    for (int id = 0;id < 7;id++)
    {
        if (t.Push(test, sizeof(test), id) == false)
        {
            std::cout << "push error" << std::endl;
            errors += 1;
        }
        else
        {
            std::cout << "push ok" << std::endl;
        }
        test[0] += 1;
    }
    
    for (id = 0; id < 20; id++)
    {
        if (t.Pop((unsigned char*)kek, 8, data_count, packet_id) == false)
        {
            //std::cout << "pop error" << std::endl;
            errors += 1;
        }
        else 
        {
            //std::cout << "packet id:" << packet_id << std::endl;
            if (packet_id != id)
                errors += 1;
        }
    }

    
    id = 0;
    
    */
    return 0;   
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
