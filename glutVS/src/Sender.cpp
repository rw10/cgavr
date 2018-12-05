

#include "sender.h"

#include <chrono>
#include <thread>

Sender::Sender()
{
	udpSocket = new QUdpSocket(this);
	//connect(&timer, &QTimer::timeout, this, &Sender::broadcastDatagram);
	//timer.start(1000);
}

void Sender::init() {
	std::thread th(Sender::start);
	th.detach();
}

void Sender::start() {
	Sender s;
	s.broadcastDatagram();
}

void Sender::broadcastDatagram()
{
	while (true) {
		QByteArray datagram = "Broadcast message " + QByteArray::number(messageNo);
		udpSocket->writeDatagram(datagram, QHostAddress::Broadcast, 45454);
		++messageNo;

		std::this_thread::sleep_for(std::chrono::microseconds(2));
	}
}