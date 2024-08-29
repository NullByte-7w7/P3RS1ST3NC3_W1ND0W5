// nullbyte made this code, my github https://github.com/NullByte-7w7
// discord: darksec_

#include <stdio.h>
#include <windows.h>


int main(void){

			// set variable
            int process_id;
            char dllpath[100];
            char dllpath2[100];
	    HANDLE hProcess;
            HANDLE memory;
	    HANDLE memory2;
	    HANDLE thread;
	    HANDLE thread2;

            // process target

            printf(" |DLL INJECTOR NULL BYTE| \n");
            printf("[#] TARGET PID -> ");
            scanf("%d", &process_id);

            // dll inject process

            printf("[!] PATH DLL TO INJECT -> ");
            scanf("%s", &dllpath);

			// other dll inject process
			
			printf("[$] PATH DLL TO OTHER DLL ->");
			scanf("%s", &dllpath2);
			
			// open process
           hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process_id);
    		if (hProcess == NULL) {
        		printf("Erro ao abrir o processo \n");
        		return -1;
    		} else {
        		printf("Sucesso ao abrir o processo %i\n", process_id);
    		}
		
            // alloc memory to 1 dll
            memory = VirtualAllocEx(hProcess, NULL, strlen(dllpath) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
			if(memory == NULL){
				
				printf("Não foi possivel alocar memoria na dll 1\n");
				return -1;
			}else{
				
				printf("memoria alocada com sucesso 1 dll\n");
			}
 
 
 			// alloc memory to 2 dll
 			memory2 = VirtualAllocEx(hProcess, NULL, strlen(dllpath2) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
 			if(memory2 == NULL){
 				
 					printf("Não foi possivel alocar memoria na dll 2\n");
					return -1;
			 }else{

					printf("memoria alocada com sucesso 2 dll\n");			 	
			 }
 
 
 			// write memory alloc 1 dll
            BOOL write_ = WriteProcessMemory(hProcess, memory, dllpath, strlen(dllpath) + 1, NULL); 
 			if(!write_){
 				
 				printf("Falha ao escrever na memoria do processo %i\n", process_id);
				return -1;
			 }else{
			 	
			 	printf("Sucesso na escrita da memoria memory\n");
			 }
			
			// write memory alloc 2 dll
			BOOL write__ = WriteProcessMemory(hProcess, memory2, dllpath2, strlen(dllpath2) + 1, NULL);
			if(!write__){
				
					printf("Falha ao escrever na memoria do processo %i\n");
					return -1;
			}else{
				
					printf("Sucesso na escrita da memoria memory2");
			}
			
 			// get fuction LoadLibraryA in kernel32.dll address_dll
            LPVOID address_dll = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
			if(address_dll == NULL){
				
				printf("Falha ao encontrar a funçao na dll kernel32.dll\n");
				return -1;
			}else{
				
				printf("Sucesso ao encontrar LoadLibraryA\n");
			}

			// get fuction LoadLibraryA in kernel32.dll address_dll_
			LPVOID address_dll_ = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
			if(address_dll_ == NULL){
				
				printf("Falha ao encontrar a função na dll kernel32.dll\n");
				return -1;
			}else{
				
				printf("Sucesso ao encontrar LoadLibraryA\n");
			}

			// run thread for LoadLibraryA address_dll
			thread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)address_dll, memory, 0, NULL);
			if(thread == NULL){
				
				printf("Falha ao rodar a thread no address_dll\n");
				return -1;
			}else{
				
				printf("sucesso ao rodar a thread\n");
			}

			// run thread for LoadLibraryA address_dll_
			thread2 = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)address_dll_, memory2, 0, NULL);
			if(thread2 == NULL){
				
				printf("Falha ao rodar a thread no address_dll_\n");
				return -1;
			}else{
				
				printf("Sucesso ao rodar a thread address_dll_\n");
			}

				printf("Credits NullByte, GOOD HACK!\n");

        return 0;
}
