#pragma once

#include <QtNetwork/qudpsocket.h>

class Receiver : public QObject
{
	Q_OBJECT

public:
	Receiver();
	~Receiver();
	static void init();

private slots:
	void processPendingDatagrams();

private:
	static void start();

	QUdpSocket *udpSocket = nullptr;
};


