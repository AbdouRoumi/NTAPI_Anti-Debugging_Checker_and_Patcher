
# NTAPI Anti-Debugging Checker and Patcher

<a href="https://git.io/typing-svg"><img src="https://readme-typing-svg.demolab.com?font=Fira+Code&pause=1000&width=435&lines=NTAPI+Anti-Debugging+Tool;Bypass+Anti-Debugging+Mechanisms" alt="Typing SVG" /></a>

## Disclaimer

This tool is intended for educational purposes only. It demonstrates how to check and modify the `BeingDebugged` flag in the Process Environment Block (PEB) of a target process using NTAPI functions. The tool is meant to help users understand anti-debugging techniques in a legal and controlled environment.

**Do not use this tool for any malicious or unauthorized activities.** The author is not responsible for any misuse of this tool. Always obtain proper authorization before using this tool on any system.

## Overview

The **NTAPI Anti-Debugging Checker and Patcher** allows you to check if a process is being debugged and modify the `BeingDebugged` flag in the PEB to bypass basic anti-debugging mechanisms. This project is useful for security researchers ,Malware developers and Analysts interested in understanding how anti-debugging techniques work at a low level.

## Features

- **Check Debugging Status**: Determine if a process is being debugged by reading the `BeingDebugged` flag from the PEB.
- **Modify Debugging Flag**: Patch the `BeingDebugged` flag to prevent the target process from detecting that it is being debugged.
- **NTAPI Integration**: Utilize low-level NTAPI functions to interact with the target process.

## Getting Started

### Prerequisites

- **Operating System**: Windows 10 or later.
- **Development Environment**: Visual Studio or any C/C++ compiler that supports Windows APIs.
- **Permissions**: Administrator privileges may be required to modify the PEB of certain processes.

### Building the Project

1. Clone the repository:

    ```bash
    git clone https://github.com/YourUsername/NTAPI_AntiDebugging_Checker.git
    cd NTAPI_AntiDebugging_Checker
    ```

2. Open the project in Visual Studio or compile it using your preferred C/C++ compiler.

3. Build the project:
    - In Visual Studio, select `Build > Build Solution`.
    - Alternatively, use `cl` from the command line:

      ```bash
      cl /EHsc /Fe:AntiDebugChecker.exe AntiDebugChecker.cpp
      ```

### Usage

1. Run the tool with the target process ID (PID):

    ```bash
    AntiDebugChecker.exe <PID>
    ```

2. The tool will:
   - Open a handle to the target process.
   - Retrieve the PEB base address.
   - Check the `BeingDebugged` flag.
   - Optionally, modify the `BeingDebugged` flag to prevent the target process from detecting the debugger.

### Example

```bash
AntiDebugChecker.exe 1234
```

This command will check and optionally patch the `BeingDebugged` flag in the process with PID 1234.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contributing

If you would like to contribute to this project, please fork the repository and submit a pull request.
