#include "Receiver.h"

#include <thread>
#include <iostream>

Receiver::Receiver()
{
	udpSocket = new QUdpSocket(this);
	udpSocket->bind(45454, QUdpSocket::ShareAddress);

	//connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
}

Receiver::~Receiver()
{
	udpSocket->disconnect();
	delete udpSocket;
}

void Receiver::init() {
	std::thread th(Receiver::start);
	th.detach();
}

void Receiver::start() {
	Receiver r;
	r.processPendingDatagrams();
}


void Receiver::processPendingDatagrams()
{
		QByteArray datagram;
		while (true) {
			while (udpSocket->hasPendingDatagrams()) {
				datagram.resize(int(udpSocket->pendingDatagramSize()));
				udpSocket->readDatagram(datagram.data(), datagram.size());

				std::string data = datagram.data();
				std::cout << data << std::endl;
			}
		}
}