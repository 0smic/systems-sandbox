# systems-sandbox

## Clipboard Inspector (Windows, C)

### Overview

This project interacts directly with the Windows API to:

- Access and lock the system clipboard
- Identify the current clipboard owner (process + PID)
- Query process information using psapi
- Enumerate all available clipboard formats
- Extract and display clipboard data (Unicode and ANSI)

Unlike high-level tools, this program works close to the system layer, exposing how clipboard data is structured and managed internally.

### Features

- Retrieves clipboard owner window and resolves it to a process ID
- Fetches process name using GetModuleBaseName
- Enumerates all clipboard formats using EnumClipboardFormats
- Differentiates between:
  - Standard formats (CF_TEXT, CF_UNICODETEXT, etc.)
  - Registered/custom formats
- Safely locks and reads clipboard memory (GlobalLock)
- Supports both Unicode and ASCII text extraction

### How It Works

1  Opens the clipboard using OpenClipboard
2  Gets the current owner window via GetClipboardOwner
3  Resolves process ID with GetWindowThreadProcessId
4  Opens the process with OpenProcess
5  Retrieves process name using GetModuleBaseName
6  Enumerates clipboard formats
7  Attempts to read:
  - CF_UNICODETEXT
  - Fallback to CF_TEXT
8  Prints extracted data
