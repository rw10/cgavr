#include "sender.h"

#include <chrono>
#include <thread>

Sender::Sender()
{
	udpSocket = new QUdpSocket(this);
}

void Sender::broadcastDatagram(const std::string& message)
{
	QByteArray datagram = message.data();
	udpSocket->writeDatagram(datagram, QHostAddress::Broadcast, 45454);
}

void Sender::callApply() {
	broadcastDatagram("APPLY");
}

void Sender::callNewLab() {
	broadcastDatagram("NEWLAB");
}

void Sender::callWall(double x1, double y1, double x2, double y2) {
	broadcastDatagram(
		"WALL " +
		std::to_string(x1) + " " +
		std::to_string(y1) + " " +
		std::to_string(x2) + " " +
		std::to_string(y2)
	);
}

void Sender::callStart(double x, double y) {
	broadcastDatagram(
		"START " +
		std::to_string(x) + " " +
		std::to_string(y)
	);
}

void Sender::callEnd(double x, double y) {
	broadcastDatagram(
		"END " +
		std::to_string(x) + " " +
		std::to_string(y)
	);
}