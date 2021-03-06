#include <iostream>
#include <windows.h>
#include <conio.h>
#include <thread>
#include "SendKeys.h"
#include "Point.h"
#include <vector>
#include <fstream>
#include <ctime>
#include <string>
using namespace std;

vector < vector<Point*>> mouseMovements;
vector<Point*> mousePaths;
POINT p;
ofstream datafile;
clock_t begintime = clock();
static boolean once = false;
vector < vector<Point*>> fromFileMouseMovements;
double replicaTime;
CSendKeys sk;
vector<Point*> fromFileMousePaths;
int selector;

//Prototypes
void callMainMenu();

//Functions
void executeBattleNet() {
	system("\"C:\\Program Files (x86)\\Battle.net\\Battle.net Launcher.exe\"");
}
void createMouseEvent() {
	while (true) {

		if (GetAsyncKeyState(VK_LBUTTON) < 0)
		{
			if (GetCursorPos(&p)) {
				Point* x = new Point(p.x, p.y);
				x->setTime();
				mousePaths.push_back(x);
				begintime = clock();
				once = true;
			}
			Sleep(20);
		}
		if (once == true && (GetAsyncKeyState(VK_LBUTTON) >= 0) && (double(clock() - begintime) / CLOCKS_PER_SEC > 1)) {
			cout << "new event recorded,do you want to save it?Press 1 for YES,Press 2 for NO" << endl;
			cin >> selector;
			if (selector == 1) {
				mouseMovements.push_back(mousePaths);
				datafile.open("mousepaths.txt", ios_base::app);
				int diff = ((mousePaths.at(mousePaths.size() - 1)->time) - (mousePaths.at(0)->time));
				datafile << "New Mouse Movement\n" << "Time:" << diff << "\n";
				for (int i = 0;i < mouseMovements.size();i++) {
					vector<Point*> mousePath = mouseMovements.at(i);
					for (int j = 0;j < mousePath.size();j++) {
						datafile << mousePath.at(j)->PrintPoints();
					}
				}
				mousePaths.clear();
				mouseMovements.clear();
				once = false;
				datafile.close();

				cout << "new event saved" << endl;
				break;
			}
			else {
				break;
			}
		}	
	}
	callMainMenu();
}
void loadMouseEvents() {
	string str;
	ifstream in("mousepaths.txt");
	bool controllertwo = false;
	bool controller = true;
	while (getline(in, str)) {
		if (str.compare("New Mouse Movement ") != 0 && str.compare("New Mouse Movement") != 0) {
			controllertwo = true;
			if (str.rfind("Time:", 0) == 0 || str.rfind("Time: ") == 0) {
				string x = str.substr(str.find(':') + 1, str.find(' ')-1);
				replicaTime = stod(x);
				
			}
			else {
				string x = str.substr(0, str.find(' '));
				string y = str.substr(str.find(' ') + 1, str.size() - 1);
				fromFileMousePaths.push_back(new Point(stod(x), stod(y)));
			}
		}
		else {
			if (controllertwo) {
				fromFileMouseMovements.push_back(fromFileMousePaths);
				controller = false;
				fromFileMousePaths.clear();
			}
		}
	}
	if (controller) {
		fromFileMouseMovements.push_back(fromFileMousePaths);
	}
	in.close();
}
void callMouseMovement(int nmbr) {
	
	vector<Point*> movement = fromFileMouseMovements.at(nmbr);
	int i = 0;
	while (i < movement.size())
	{
		Point* temp = movement.at(i);
		i++;
		SetCursorPos(temp->x, temp->y);
		double onepiecetime = replicaTime / movement.size();
		Sleep(onepiecetime);
	}

}
void LoopForCallingMovements() {
	
	while(true){
		
		if ((GetAsyncKeyState('0') & 0x8000) != 0) {
			callMouseMovement(0);
		}
		if ((GetAsyncKeyState('1') & 0x8000) != 0) {
			callMouseMovement(1);
		}
		if ((GetAsyncKeyState('2') & 0x8000) != 0) {
			callMouseMovement(2);
		}
		if ((GetAsyncKeyState('9') & 0x8000) != 0) {
			break;
		}
	}
	callMainMenu();
}
void callMainMenu() {
	cout << endl << "...Overwatch Aim Simulator... " << endl;

	cout << endl << "press 1 to record a new mouse event \npress 2 to load the mouse events\npress 9 to exit\n" << endl;
	cin >> selector;

	switch (selector) {

	case 1:
		cout << "to record a new event you can make your mouse event with leftclicking" << endl;
		createMouseEvent();
		break;
	case 2:
		loadMouseEvents();
		cout << "mouse events loaded..." << endl;
		cout << "you can use them with their shorcut keys" << endl;
		cout << "to quit press " << endl;
		LoopForCallingMovements();
		break;
	case 9:
		exit(0);
	}
}

//Main
int main()
{
	callMainMenu();
	return 0;
}
// "\"C:\\Riot Games\\League of Legends\\LeagueClient.exe\" "
/*
		executeBattleNet();

		//system("taskkill /F /T /IM Battle.net.exe");
		SetCursorPos(400, 1000);


		//sk.SendKeys("nahgirersin1");
		//SetCursorPos(1420, 720);
		Sleep(7000);
		mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		cout << "HEYY" << endl;

		Sleep(12000);
		SetCursorPos(100, 230);
		mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		Sleep(2000);
		SetCursorPos(1000, 500);
		mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

		*/