#pragma once

#include <QtNetwork/qudpsocket.h>
#include <memory>
#include "Labyrinth.h"

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
	Vector2 start;
	Vector2 end;

	static void startReceiving();
	std::vector<double> getNumbers(const std::string& line);
	bool startsWith(const std::string& line, const std::string& find);

	std::shared_ptr<Labyrinth> lab;

	QUdpSocket *udpSocket = nullptr;
};


