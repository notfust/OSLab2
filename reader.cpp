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
	{
		file = CreateFile(
			"reader.txt",
			GENERIC_WRITE | GENERIC_READ,
			NULL,
			nullptr,
			OPEN_ALWAYS,
			NULL,
			nullptr
		);
		if (file == INVALID_HANDLE_VALUE)
			cout << "Error " << GetLastError() << endl;
		fileMap = CreateFileMappingA(
			file,
			nullptr,
			PAGE_READWRITE,
			0,
			1,
			"Map"
		);
		if (!fileMap) cout << "Error " << GetLastError() << endl;
	}
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
				FILE_MAP_ALL_ACCESS, 
				true, 
				"Map"
				/*NULL*/
			);
			if (!fileMap) cout << "Error " << GetLastError() << endl;
			cout << "Press enter...";
			cin.get();
			break;
		}
		case 2: {
			mapView = MapViewOfFile(
				fileMap,
				FILE_MAP_ALL_ACCESS,
				0, 0, 0
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
			cout << "Read data: " << data << endl;;
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
