## Overview

This is an **MFC-based VC++ Dialog Application** developed using **Visual Studio 2015**. The application provides a user-friendly interface for managing employee details stored in an XML file named **EData.xml**. The core functionalities include:

- **INSERT**: Add new employee records.
- **DELETE**: Remove existing employee records.
- **UPDATE**: Modify and update employee information.

## Features

- **User Interface**:
  - A simple and intuitive **dialog-based user interface** built with **Microsoft Foundation Classes (MFC)**.
  - **Main Application Class**: `EDataDisplayApp` manages the overall application lifecycle.
  - **Dialog Class**: `EDataDisplayDlg` handles the main user interface for employee management operations.

- **XML Data Handling**:
  - Employee details are stored in an XML file named **EData.xml**, located in the same folder as the executable (.exe) file.

- **Logging**:
  - The application generates a log file named **AppLog.log**, which records significant events, errors, and informational messages during the application's operation. This log file is also stored in the same folder as the executable, providing a valuable resource for debugging and monitoring the application's behavior.

## Prerequisites

- **Visual Studio 2015**: This project is developed using Visual Studio 2015. Ensure you have it installed to build and run the application.
- **Windows OS**: The application is designed for Windows platforms.

## Compatibility

- The application has been tested and is fully compatible with **Visual Studio 2022**. No code modifications are required to build or run the project in Visual Studio 2022.

## How to Build

1. **Clone the repository** to your local machine.
2. **Open the solution file** (`EDataDisplay.sln`) located in the **Source code** folder using **Visual Studio 2015**.
3. **Build the solution** by selecting **Build Solution** from the **Build** menu.
4. **In Case of Build Failures**: If the build process encounters any issues, you can run the **pre-built executable** located in the **Release folder**. This folder contains a working version of the application to ensure continued functionality.
   ![EMP_GUI_IMAGE](https://github.com/user-attachments/assets/490a73e1-f65b-4875-a7b9-10581083823e)


