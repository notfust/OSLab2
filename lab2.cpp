#include <iostream>
#include <windows.h>
#include <vector>

using namespace std;

#define DIV 1024
#define WIDTH 7

int main() {
	int menu_item = 0;

	SYSTEM_INFO siSysInfo;
	GetSystemInfo(&siSysInfo); //получение инфо о вычислительной системе

	MEMORYSTATUS stat;
	GlobalMemoryStatus(&stat); //опрееление статуса виртуальной памяти

	MEMORY_BASIC_INFORMATION  pmbi;
	DWORD  pmbi_size = sizeof(MEMORY_BASIC_INFORMATION);
	
	void* mem_ptr = NULL;

	do {
		{
			system("cls");
			cout << "1. GetSystemInfo" << endl;
			cout << "2. GlobalMemoryStatus" << endl;
			cout << "3. VirtualQuery" << endl;
			cout << "4. VirtualAlloc (reserve)" << endl;
			cout << "5. VirtualAlloc (reserve and transfer)" << endl;
			cout << "6. Writing data to memory cells as specified from the keyboard addresses" << endl;
			cout << "7. VirtualProtect" << endl;
			cout << "8. VirtualFree" << endl;
			cout << "9. Exit" << endl;
			cout << "Enter menu item: ";
			cin >> menu_item;
		}
		system("cls");
		switch (menu_item)
		{
		case 1: {
			cout << "Hardware information:" << endl;
			printf("  OEM ID: %u\n", siSysInfo.dwOemId);
			printf("  Number of processors: %u\n", siSysInfo.dwNumberOfProcessors);
			printf("  Page size: %u\n", siSysInfo.dwPageSize);
			printf("  Processor type: %u\n", siSysInfo.dwProcessorType);
			printf("  Minimum application address: %lx\n", siSysInfo.lpMinimumApplicationAddress);
			printf("  Maximum application address: %lx\n", siSysInfo.lpMaximumApplicationAddress);
			printf("  Active processor mask: %u\n", siSysInfo.dwActiveProcessorMask);
			system("pause");
			break;
		}
		case 2: {
			printf("The MemoryStatus structure is %ld bytes long.\n", stat.dwLength);
			printf("It should be %d.\n", sizeof(stat));
			printf("%ld percent of memory is in use.\n", stat.dwMemoryLoad);
			printf("There are %*ld total %sbytes of physical memory.\n", WIDTH, stat.dwTotalPhys / DIV, "K");
			printf("There are %*ld free %sbytes of physical memory.\n", WIDTH, stat.dwAvailPhys / DIV, "K");
			printf("There are %*ld total %sbytes of paging file.\n", WIDTH, stat.dwTotalPageFile / DIV, "K");
			printf("There are %*ld free %sbytes of paging file.\n", WIDTH, stat.dwAvailPageFile / DIV, "K");
			printf("There are %*lx total %sbytes of virtual memory.\n", WIDTH, stat.dwTotalVirtual / DIV, "K");
			printf("There are %*lx free %sbytes of virtual memory.\n", WIDTH, stat.dwAvailVirtual / DIV, "K");
			system("pause");
			break;
		}
		case 3: {
			VOID* Address = NULL;
			cout << "Min address: " << siSysInfo.lpMinimumApplicationAddress << endl;
			cout << "Max address: " << siSysInfo.lpMaximumApplicationAddress << endl;
			cout << "Enter anddress: ";
			cin >> Address;
			system("cls");
			VirtualQuery(
				Address, //адрес области
				&pmbi, //адрес информационного буфера
				pmbi_size //рамер буфера
			);
			cout << "BaseAddress: " << pmbi.BaseAddress << endl;
			cout << "AllocationBase: " << pmbi.AllocationBase << endl;
			cout << "AllocationProtect: " << pmbi.AllocationProtect << endl;
			cout << "RegionSize: " << pmbi.RegionSize << endl;
			cout << "State: " << pmbi.State << endl;
			cout << "Protect: " << pmbi.Protect << endl;
			cout << "Type: " << pmbi.Type << endl;
			cout << "PartitionId: " << pmbi.PartitionId << endl;
			system("pause");
			break;
		}
		case 4: {
			void* address = NULL;
			cout << "1. Auto mode" << endl;
			cout << "2. Enter the address" << endl;
			cout << "Enter menu item: ";
			cin >> menu_item;
			system("cls");
			switch (menu_item)
			{
			case 1: {
				mem_ptr = VirtualAlloc(
					NULL, //адрес (выберается системой)
					4096, //размер выделяемого региона (байты)
					MEM_RESERVE, //тип распределения памяти
					PAGE_READWRITE //тип защиты доступа (чтение и запись)
				);
				if (mem_ptr != NULL)
					cout << "Memory reserved automatically" << endl;
				break;
			}
			case 2: {
				cout << "Enter address:";
				cin >> address;
				mem_ptr = VirtualAlloc(
					address, //адрес
					4096, //размер (байты)
					MEM_RESERVE, //тип распределения памяти 
					PAGE_READWRITE //тип защиты доступа (чтение и запись)
				);
				cout << "Memory reserved" << endl;
				break;
			}
			default:
				break;
			}
			system("pause");
			break;
		}
		case 5: {
			void* address = NULL;
			cout << "1. Auto mode" << endl;
			cout << "2. Enter the address" << endl;
			cout << "Enter menu item: ";
			cin >> menu_item;
			system("cls");
			switch (menu_item)
			{
			case 1: {
				mem_ptr = VirtualAlloc(
					NULL, 
					4096,
					MEM_COMMIT, //передача физической памяти
					PAGE_READWRITE 
				);
				break;
			}
			case 2: {
				cout << "Enter address:";
				cin >> address;
				mem_ptr = VirtualAlloc(
					address, 
					4096,
					MEM_COMMIT, //передача физической памяти
					PAGE_READWRITE
				);
				break;
			}
			default:
				break;
			}
			system("pause");
			break;
		}
		case 6: {
			cout << "Enter address: ";
			void* mem_for_write;
			cin >> hex >> mem_for_write;
			cin >> dec;
			cin.ignore(32767, '\n');
			cout << "Enter data: ";
			string data_to_write;
			char str[256];
			cin.getline(str, 256);
			for (int i = 0; i < 256; i++)
				reinterpret_cast<char*>(mem_for_write)[i] = str[i];
			cout << "Data insert successfully" << endl;
			system("pause");
			break;
		}
		case 7: {
			PDWORD lpflOldProtect = NULL;
			VOID* address = NULL;
			cout << "Enter address: ";
			cin >> address;
			VirtualQuery(address, &pmbi, pmbi_size);
			cout << "Protect: " << pmbi.Protect << endl;
			cout << "1. READWRITE" << endl;
			cout << "2. READONLY" << endl;
			cout << "3. EXECUTE" << endl;
			cout << "4. EXECUT_READ" << endl;
			cout << "5. EXECUT_READWRITE" << endl;
			cout << "6. NOACCESS" << endl;
			cout << "7. GUARD" << endl;
			cout << "8. NOCACHE" << endl;
			cout << "Enter new protect item: ";
			cin >> menu_item;
			system("cls");
			switch (menu_item)
			{
			case 1: {
				VirtualProtect(address, 4096, PAGE_READWRITE, lpflOldProtect);
				break;
			}
			case 2: {
				VirtualProtect(address, 4096, PAGE_READONLY, lpflOldProtect);
				break;
			}
			case 3: {
				VirtualProtect(address, 4096, PAGE_EXECUTE, lpflOldProtect);
				break;
			}
			case 4: {
				VirtualProtect(address, 4096, PAGE_EXECUTE_READ, lpflOldProtect);
				break;
			}
			case 5: {
				VirtualProtect(address, 4096, PAGE_EXECUTE_READWRITE, lpflOldProtect);
				break;
			}
			case 6: {
				VirtualProtect(address, 4096, PAGE_NOACCESS, lpflOldProtect);
				break;
			}
			case 7: {
				VirtualProtect(address, 4096, PAGE_GUARD, lpflOldProtect);
				break;
			}
			case 8: {
				VirtualProtect(address, 4096, PAGE_NOCACHE, lpflOldProtect);
				break;
			}
			default:
				break;
			}
			system("pause");
			break;
		}
		case 8: {
			if (VirtualFree(mem_ptr, 0, MEM_RELEASE)) cout << "Memory freed" << endl;
			else cout << "Failed!" << endl;;
			system("pause");
			break;
		}
		case 9:
			break;
		default:
			cout << "";
			system("pause");
			break;
		}
	} while (menu_item != 9);
	return 0;
}
