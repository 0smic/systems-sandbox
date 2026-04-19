#include<windows.h>
#include<stdio.h>
#include <psapi.h>


int main(){
    // current owner of clipboard
    char CurrentOwnerName[256];
    DWORD pid;

    // opening  clipboard
    if (!OpenClipboard(NULL)){
        printf("error opening clipboard");
    }

    HWND CurrentOwner = GetClipboardOwner(); // fetching owner
    GetWindowThreadProcessId(CurrentOwner, &pid); // fetching process id
    HANDLE process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE, pid); // fetching limited process info
    // fetching process name
    if (GetModuleBaseName(process,NULL,CurrentOwnerName,256) == 0){
        printf("Error happened reteriveing name\n");
    }

    printf("  \t  CLIPBOARD \n");
    printf("\t-------------\n\n");

    printf("    Current Owner Details\n");
    printf("Process id: %lu\n",pid);
    printf("Process Name: %s", CurrentOwnerName);

    UINT format = 0;
    char formatName[256];
    printf("\n\n\tFORMATS OF THE OBJECT IN THE CLIPBOARD\n");
    printf("\t  -------------------------------------\n\n");
        while(( format = EnumClipboardFormats(format)) != 0){
        formatName[0] = '\0';
        if (GetClipboardFormatName(format, formatName, sizeof(formatName))) {
            printf("Format %u: %s\n", format, formatName);
        } else {
            // standard formats
            switch (format) {
                case CF_TEXT: printf("Format %u: CF_TEXT\n", format); break;
                case CF_UNICODETEXT: printf("Format %u: CF_UNICODETEXT\n", format); break;
                case CF_OEMTEXT: printf("Format %u: CF_OEMTEXT\n", format); break;
                case CF_LOCALE: printf("Format %u: CF_LOCALE\n", format); break;
                default: printf("Format %u: (unknown standard)\n", format);
            }
        }
    }


    printf("\n\t\tDATA\n");
    printf("\t\t-----\n\n");
    HANDLE data = GetClipboardData(CF_UNICODETEXT);
    
    if (data != NULL) {
        wchar_t *text = (wchar_t *)GlobalLock(data);
        if (text) {
            wprintf(L"%ls\n", text);
            GlobalUnlock(data);
        }
    } else {
        data = GetClipboardData(CF_TEXT);
        if (data != NULL) {
            char *text = (char *)GlobalLock(data);
            if (text) {
                printf("Data: %s\n", text);
                GlobalUnlock(data);
            }
        } else {
            printf("No printable content\n");
        }
    }

    CloseClipboard();
    CloseHandle(process);

    return 0;
}
