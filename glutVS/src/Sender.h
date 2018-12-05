#pragma once

#include <QtNetwork/qudpsocket.h>
#include <vector>

class Sender : public QObject
{
	Q_OBJECT

public:
	Sender();

	static void init();


private slots:
	//void broadcastDatagram();

private:
	static void start();
	void broadcastDatagram();

	QUdpSocket *udpSocket = nullptr;
	int messageNo = 1;
};