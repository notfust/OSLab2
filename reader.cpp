#include <iostream>
#include <Windows.h>
#include <fileapi.h>
#include <string>

using namespace std;

int main() {
	int menuItem = 0;
	string name, mapName;
	HANDLE fileMap = NULL, file = NULL;
	void* mapView = NULL;
	do {
		{
			system("cls");
			cout << "1. OpenFileMapping" << endl;
			cout << "2. MapViewOfFile" << endl;
			cout << "3. Read data for file" << endl;
			cout << "4. UnmapViewOfFile and Exit" << endl;
			cout << "Enter menu item: ";
			cin >> menuItem;
			cin.get();
		}
		system("cls");
		switch (menuItem)
		{
		case 1: {
			fileMap = OpenFileMapping(
				FILE_MAP_ALL_ACCESS, //режим доступа
				true, //флаг наследования
				"Map" //имя
				/*NULL*/
			);
			if (!fileMap) cout << "Error " << GetLastError() << endl;
			cout << "Press enter...";
			cin.get();
			break;
		}
		case 2: {
			mapView = MapViewOfFile(
				fileMap, //дескр. объекта проецируемый файл
				FILE_MAP_ALL_ACCESS, //режим доступа
				0, //старшее слово DWORD смещения
				0, //младшее слово DWORD смещения
				0 //кол-во байт отображения (отобразить целиком)
			);
			if (mapView == INVALID_HANDLE_VALUE) {
				std::cout << "Error " << GetLastError() << endl;
			}
			cout << "Press enter...";
			cin.get();
			break;
		}
		case 3: {
			string data(reinterpret_cast<char*>(mapView));
			cout << "Read data: " << data << endl;
			cout << "Press enter...";
			cin.get();
			break;
		}
		case 4: {
			CloseHandle(fileMap);
			break;
		}
		}
	} while (menuItem != 4);

	return 0;
}
