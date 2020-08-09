#pragma once




#include <iostream>
using namespace std;
//Класс должен быть шаблонным.Через параметры шаблона задается максимальная длина одного
//пакета, максимальное число пакетов в очереди и максимальный размер всей очереди пакетов в
//байтах.

template < int fifo_depth, int packet_size, int fifo_size>
class test_fifo
{
private:

	unsigned int max_packet_size = packet_size;	//максимальный размер пакета
	unsigned int max_fifo_depth = fifo_depth;		//размер в элементах очереди
	unsigned int max_fifo_size = fifo_size;		//максимально возможный размер в байтах, в общем случае может быть не равен max_packet_size*max_fifo_depth
	struct packet
	{
	public:
		unsigned int id;
		unsigned int size;
		unsigned char payload[packet_size];
	};

	packet queue[fifo_depth] = {};
	unsigned int in = 0;
	unsigned int out = 0;
	unsigned int total_size = 0;

	bool isFull()
	{
		if (((in > out) ? (in - out) : (out - in)) > max_fifo_depth)
			return true;
		else
			return false;
	}

	bool isEmpty()
	{
		if (out == in)
			return true;
		else
			return false;
	}
	


public:
	test_fifo() {}

	void ShowQueue()
	{
		for (int i = 0; i < in; i++)
		{
			std::cout << queue[i].id << std::endl;
		}
	}

	// Поместить пакет в очередь
	// data - содержимое пакета
	// dataCount - длина пакета в байтах
	// packetId - идентификатор пакета
	// return - результат постановки пакета в очередь:
	// true - пакет помещен в очередь
	// false - длина пакета превышает максимально допустимую, число пакетов в очереди или
	// суммарный размер пакетов в очереди превысили максимально допустимые
	bool Push(unsigned char* data, unsigned int dataCount, unsigned int packetId)
	{
		//проверка на запоненность очереди
		if (isFull())
			return false;
		//остальные две проверки
		if ((dataCount > max_packet_size) ||
			(total_size > max_fifo_size - dataCount))
			return false;
		queue[in].id = packetId;
		queue[in].size = dataCount;
		total_size += dataCount;
		std::memset((unsigned char*)queue[in].payload, 0, packet_size);
		std::memcpy((unsigned char*)queue[in].payload, data, dataCount);

		in += 1;
		if (in > max_fifo_depth)
			in = 0;

		return true;
	}


	// Извлечь пакет из очереди
	// buffer - приемный буфер, куда помещаются данные извлеченные из очереди
	// bufferSize - размер приемного буфера
	// dataCount - фактический размер пакета, извлеченного из очереди
	// packetId - идентификатор пакета, извлеченного из очереди
	// return - результат извлечения пакета из очереди:
	// true - пакет извлечен и помещен в буфер (в том числе, если размер пакета превысил
	// размер приемного буфера)
	// false - очередь пуста
	

	bool Pop(unsigned char* buffer, unsigned int bufferSize, unsigned int& dataCount, unsigned int& packetId)
	{
		if (isEmpty())
			return false;
		
		
		
		
		dataCount = queue[out].size;
		total_size -= dataCount;
		packetId = queue[out].id;
		std::memcpy(buffer, queue[out].payload, bufferSize < dataCount ? dataCount: bufferSize);
	
		out += 1;
		if (out > max_fifo_depth)
			out = 0;

		return true;
	}
};

