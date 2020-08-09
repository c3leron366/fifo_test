#pragma once




#include <iostream>
using namespace std;
//����� ������ ���� ���������.����� ��������� ������� �������� ������������ ����� ������
//������, ������������ ����� ������� � ������� � ������������ ������ ���� ������� ������� �
//������.

template < int fifo_depth, int packet_size, int fifo_size>
class test_fifo
{
private:

	unsigned int max_packet_size = packet_size;	//������������ ������ ������
	unsigned int max_fifo_depth = fifo_depth;		//������ � ��������� �������
	unsigned int max_fifo_size = fifo_size;		//����������� ��������� ������ � ������, � ����� ������ ����� ���� �� ����� max_packet_size*max_fifo_depth
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
		//��������� ��� ��������
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
		std::memcpy(buffer, queue[out].payload, bufferSize < dataCount ? dataCount: bufferSize);
	
		out += 1;
		if (out > max_fifo_depth)
			out = 0;

		return true;
	}
};

