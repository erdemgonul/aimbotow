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
void executeBattleNet() {
	system("\"C:\\Program Files (x86)\\Battle.net\\Battle.net Launcher.exe\"");
}

int main()
{
	vector < vector<Point*>> mouseMovements;
	vector<Point*> mousePaths;
	POINT p;
	ofstream datafile;
	clock_t begin=clock();
	static boolean once = false;
	vector < vector<Point*>> fromFileMouseMovements;
	
	CSendKeys sk; 

	
	cout << "hoşt" << endl;
	
		while (true) {
	
			if (GetAsyncKeyState(VK_LBUTTON) < 0)
			{
				
				
				if (GetCursorPos(&p)) {
					mousePaths.push_back(new Point(p.x,p.y));
					begin = clock();
					once = true;
				}
				
				Sleep(100);
			}

			if (once==true && (GetAsyncKeyState(VK_LBUTTON) >= 0)   && (double(clock() - begin) / CLOCKS_PER_SEC > 1)) {
				mouseMovements.push_back(mousePaths);
				mousePaths.clear();

				datafile.open("mousepaths.txt", ios_base::app);
				datafile << "New Mouse Movement\n";
				for (int i = 0;i < mouseMovements.size();i++) {
					vector<Point*> mousePath = mouseMovements.at(i);
					for (int j = 0;j < mousePath.size();j++) {
						datafile << mousePath.at(j)->PrintPoints();
					}
				}
				mouseMovements.clear();
				once = false;
				datafile.close();
			}
			if (GetAsyncKeyState('Q')) {
				string str;
				ifstream in("mousepaths.txt");
				vector<Point*> fromFileMousePaths;
				while (getline(in, str)) {
					if (str.compare("New Mouse Movement ")!=0 && str.compare("New Mouse Movement")!=0) {
						string x = str.substr(0, str.find(' '));
						string y = str.substr(str.find(' ') + 1, str.size()-1);
						cout << x  << y << endl;
						fromFileMousePaths.push_back(new Point(stod(x),stod(y)));

					}
					else {
						fromFileMouseMovements.push_back(fromFileMousePaths);
						//fromFileMousePaths.clear();
					}
				}
				in.close();
			}
			if (GetAsyncKeyState('1')) {
				vector<Point*> movement = fromFileMouseMovements.at(0);
				cout << movement.at(0)->x << endl;
				int i = 0;
				while (i < movement.size())
				{
					Point* temp = movement.at(i);
					i++;
					cout << temp->x << endl;
					SetCursorPos(temp->x,temp->y);
					Sleep(100);
				}
			}
			
				
				
			
		}
		
		
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
	return 0;
}

/*
			else if ((GetKeyState(VK_RBUTTON) & 0x80 ) != 0) {
				mouseMovements.push_back(mousePaths);
				mousePaths.clear();


				datafile << "New Mouse Movement \n";
				for (int i = 0;i<mouseMovements.size();i++) {
					vector<Point*> mousePath=mouseMovements.at(i);
					for (int j = 0;j < mousePath.size();j++) {
						datafile << mousePath.at(j)->PrintPoints();
					}
					mouseMovements.clear();
					break;
				}


			}*/
// "\"C:\\Riot Games\\League of Legends\\LeagueClient.exe\" "