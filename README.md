# Employee Management Application

## Overview

The **Employee Management Application** is a simple tool for managing employee records, developed using MFC VC++ and C++. You can INSERT new records, UPDATE existing ones, and DELETE records when needed. All data is stored in an XML file, and the application runs on Windows.

![EMP_GUI_IMAGE](https://github.com/user-attachments/assets/4c03f30f-557d-460d-a210-22f13ae933f5)

## Features

- **Manage Employee Records**:
  - **INSERT**: Add new employees to the XML file.
  - **UPDATE**: Modify details of existing employees in the XML file.
  - **DELETE**: Remove employees from the XML file.
- **Unique Employee ID**:
  - Each employee gets a unique ID that never repeats, even after a record is deleted or the application is restarted.
- **XML Data Storage**:
  - All employee data is saved in an XML file, ensuring easy storage and retrieval.
  - **Automatic XML Creation**: The application automatically creates the necessary XML file (`EData.xml`) if it doesn't already exist when the application is first run.
  - **Backup of Corrupted XML**: If the XML file becomes corrupted, the application will automatically back up the corrupted XML data, ensuring that no data is lost during the recovery process.
- **Logging**:
  - The application logs all actions, such as INSERT, UPDATE, and DELETE, to a log file for tracking and debugging purposes.
- **User Interface**:
  - The app has a simple and responsive interface, with progress indicators for longer tasks.
- **Age Limit**:
  - The application only accepts ages between 1 and 149.

## Getting Started

### Requirements

- **Operating System**: Windows 10 or later
- **Software**: Visual Studio 2015 or later

### How to Install

1. **Download the Project**:
   **https://github.com/krishnakv24/EmployeeManagementApplication.git**

2. **Build the Application**:
   - Open the project in Visual Studio.
   - Build the solution using MFC VC++.

3. **Run the Application**:
   - You can find a ready-to-use version in the `Release` folder.
   - After building, go to the `Release` or `Debug` folder in the project directory.
   - Double-click `EDataDisplay.exe` to start.

## How to Use

1. **INSERT Employee**:
   - Click the "INSERT" button on the main interface.
   - In the popup window, enter the employee’s name and age.
   - Click the "INSERT" button in the popup to add the employee to the XML file. A unique ID is automatically assigned.
     
     ![image](https://github.com/user-attachments/assets/fe050d15-e63a-4e75-bc22-bdf56c46d8f9)


2. **UPDATE Employee**:
   - Select the employee you want to update from the list.
   - Click the "UPDATE" button on the main interface.
   - Modify the details in the popup window and click "UPDATE" to save the changes in the XML file.

![image](https://github.com/user-attachments/assets/ad5b2a86-b072-4c34-8f61-efc9a87ea21a)


3. **DELETE Employee**:
   - Select the employee you want to delete from the list.
   - Click the "DELETE" button on the main interface.
   - A confirmation popup will appear; confirm the action to remove the employee from the XML file. The unique ID won’t be reused.

     ![image](https://github.com/user-attachments/assets/1c41815a-dbc7-4c61-9e05-a19fb52122d3)

4. **View Records**:
   - All employee records are shown in a list.

     ![image](https://github.com/user-attachments/assets/d20b15ec-cdd0-4bef-9db7-da5a1c907682)


## Files

- **Release Folder**: Contains a ready-to-use version of the application (`EDataDisplay.exe`).
- **EData.xml**: This file stores all employee records and is automatically created if not found when the application is first run. If the XML file is corrupted, a backup is made to prevent data loss.
- **AppLog.log**: This file logs all the actions you perform in the application, including INSERT, UPDATE, and DELETE operations.
