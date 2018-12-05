#pragma once

#include <QtNetwork/qudpsocket.h>
#include <string>

class Sender : public QObject
{
public:
	Sender();

	void callApply();
	void callNewLab();
	void callWall(double x1, double y1, double x2, double y2);
	void callStart(double x, double y);
	void callEnd(double x, double y);

private:
	void broadcastDatagram(const std::string& message);

	QUdpSocket *udpSocket = nullptr;
};