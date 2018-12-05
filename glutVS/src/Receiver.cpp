#include "Receiver.h"

#include <thread>
#include <iostream>
#include <ctype.h>

#include "Model.h"

Receiver::Receiver()
{
	udpSocket = new QUdpSocket(this);
	udpSocket->bind(45454, QUdpSocket::ShareAddress);


	lab = std::shared_ptr<Labyrinth>(new Labyrinth);

	//connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
}

Receiver::~Receiver()
{
	udpSocket->disconnect();
	delete udpSocket;
}

void Receiver::init() {
	std::thread th(Receiver::startReceiving);
	th.detach();
}

void Receiver::startReceiving() {
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
				//std::cout << data << std::endl;

				if (startsWith(data, "NEWLAB")) {
					lab = std::shared_ptr<Labyrinth>(new Labyrinth);
					std::cout << "started new labyrinth" << std::endl;
				}
				else if (startsWith(data, "WALL")) {
					std::vector<double> nums = getNumbers(data);
					if (nums.size() == 4) {
						lab->addWall(
							Vector2(nums[0], nums[1]),
							Vector2(nums[2], nums[3])
						);
						std::cout << "wall added: " << data << std::endl;
					}
					else {
						std::cout << "wall not added, needs 2 x/y-points" << std::endl;
					}
				}
				else if (startsWith(data, "START")) {
					std::vector<double> nums = getNumbers(data);
					if (nums.size() == 2) {
						start = Vector2(nums[0], nums[1]);
						std::cout << "start set: " << data << std::endl;
					}
					else {
						std::cout << "start not set, needs 2 values (x,y)" << std::endl;
					}
				}
				else if (startsWith(data, "END")) {
					std::vector<double> nums = getNumbers(data);
					if (nums.size() == 2) {
						end = Vector2(nums[0], nums[1]);
						std::cout << "end set: " << data << std::endl;
					}
					else {
						std::cout << "end not set, needs 2 values (x,y)" << std::endl;
					}
				}
				else if (startsWith(data, "APPLY")) {
					lab->initRouting();

					Model& model = Model::get();
					model.setLab(lab);
					model.setStart(start.x, start.y);
					model.setEnd(end.x, end.y);
					model.calculateRoute();

					std::cout << "Applied all received data!" << std::endl;
				}
				else {
					std::cout << "ignored line: " << data << std::endl;
				}
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
}

bool Receiver::startsWith(const std::string& line, const std::string& find) {
	if (find.size() > line.size()) {
		return false;
	}

	return line.compare(0, find.size(), find) == 0;
}

std::vector<double> Receiver::getNumbers(const std::string& original) {
	std::vector<double> numbers;

	std::string n = "";
	for (char c : original) {
		if (isdigit(c) || c == '.') {
			n += c;
		}
		else {
			if (n.size() != 0) {
				double d = std::stod(n);
				numbers.push_back(d);
				n = "";
			}
		}
	}
	if (n.size() != 0) {
		double d = std::stod(n);
		numbers.push_back(d);
	}

	return numbers;
}