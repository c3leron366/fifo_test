#pragma once




#include <iostream>
using namespace std;
//����� ������ ���� ���������.����� ��������� ������� �������� ������������ ����� ������
//������, ������������ ����� ������� � ������� � ������������ ������ ���� ������� ������� �
//������.
//fifo_depth(������������ ����� ������� � ������� ),
//packet_size(������������ ����� ������ ������ ),
//fifo_size(������������ ������ ���� ������� ������� � ������)
template < unsigned int fifo_depth, unsigned int packet_size, unsigned int fifo_size>
class test_fifo
{
private:

	
	struct packet
	{
		unsigned int id;
		unsigned int size;
		unsigned char payload[packet_size];
	};

	packet queue[fifo_depth] = {};
	unsigned int total_size = 0;

	
	


public:


	unsigned int in = 0;
	unsigned int out = 0;
	unsigned int count = 0;
	unsigned int max_packet_size = packet_size;	//������������ ������ ������
	unsigned int max_fifo_depth = fifo_depth;	//������ � ��������� �������
	unsigned int max_fifo_size = fifo_size;		//����������� ��������� ������ � ������, � ����� ������ ����� ���� �� ����� max_packet_size*max_fifo_depth

	test_fifo() {}


	bool isFull()
	{
		if (count == max_fifo_depth)
			return true;
		else 
			return false;
	}

	bool isEmpty()
	{
		if ((out == in) && !isFull())
			return true;
		else
			return false;
	}

	// ��������� ����� � �������
	// data - ���������� ������
	// dataCount - ����� ������ � ������
	// packetId - ������������� ������
	// return - ��������� ���������� ������ � �������:
	// true - ����� ������� � �������
	// false - ����� ������ ��������� ����������� ����������, ����� ������� � ������� ���
	// ��������� ������ ������� � ������� ��������� ����������� ����������
	bool Push(unsigned char* data, unsigned int dataCount, unsigned int packetId)
	{
		//�������� �� ������������ �������
		if (isFull())
			return false;

		//elements[tail] = x
		
		//��������� ��� ��������
		if ((dataCount > max_packet_size) ||
			(total_size > max_fifo_size - dataCount))
			return false;

		queue[in].id = packetId;
		queue[in].size = dataCount;
		total_size += dataCount;
		std::memset((unsigned char*)queue[in].payload, 0, max_packet_size);
		std::memcpy((unsigned char*)queue[in].payload, data, dataCount);
		count += 1;
		in = (in + 1) % max_fifo_depth;
		
		return true;
	}


	// ������� ����� �� �������
	// buffer - �������� �����, ���� ���������� ������ ����������� �� �������
	// bufferSize - ������ ��������� ������
	// dataCount - ����������� ������ ������, ������������ �� �������
	// packetId - ������������� ������, ������������ �� �������
	// return - ��������� ���������� ������ �� �������:
	// true - ����� �������� � ������� � ����� (� ��� �����, ���� ������ ������ ��������
	// ������ ��������� ������)
	// false - ������� �����
	bool Pop(unsigned char* buffer, unsigned int bufferSize, unsigned int& dataCount, unsigned int& packetId)
	{
		
		if (isEmpty())
			return false;
		
		dataCount = queue[out].size;
		total_size -= dataCount;
		packetId = queue[out].id;
		std::memset(buffer, 0, bufferSize);
		std::memcpy(buffer, queue[out].payload, bufferSize > dataCount ? dataCount: bufferSize);
		count -= 1;
		out = (out + 1) % max_fifo_depth;
		
		return true;
	}
};

