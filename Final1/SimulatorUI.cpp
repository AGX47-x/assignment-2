#include "SimulatorUI.h"
#include <iostream>
#include <iomanip>

using namespace std;

void SimulatorUI::start()
{
    int choice;
    do
    {
        showMenu();
        cin >> choice;
        switch (choice)
        {
        case 1:
            loadProgram();
            break;
        case 2:
            overwriteValue();
            break;
        case 3:
            runProgram();
            break;
        case 4:
            displayState();
            break;
        case 5:
            cout << "Exiting simulator\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5 && askContinueOrExit());
}

void SimulatorUI::showMenu()
{
    cout << "\n==============================\n"
         << "    VOLE MACHINE SIMULATOR   \n"
         << "==============================\n"
         << "1. Load Program from File\n"
         << "2. Overwrite Value (Memory/Register)\n"
         << "3. Run Program\n"
         << "4. Display Simulator State\n"
         << "5. Exit\n"
         << "Enter your choice: ";
}

void SimulatorUI::loadProgram()
{
    string filename;
    int startaddress;
    cout << "Enter name of the program (e.g., file.txt): ";
    cin >> filename;
    cout << "Enter start address in hex (e.g., 00): ";
    cin >> hex >> startaddress;
    if (machine.loadProgram(filename, startaddress))
    {
        cout << "File loaded successfully.\n";
    }
    else
    {
        cout << "Could not open the file.\n";
    }
}

void SimulatorUI::overwriteValue()
{
    int type;
    cout << "1. Overwrite Memory Cell\n2. Overwrite Register\nChoose option: ";
    cin >> type;
    if (type == 1)
    {
        int adr, val;
        cout << "Enter memory address (hex): ";
        cin >> hex >> adr;
        cout << "Enter value (hex): ";
        cin >> hex >> val;
        machine.getMemory().write(adr, val);
    }
    else if (type == 2)
    {
        int regid, val;
        cout << "Enter register index (0-15): ";
        cin >> regid;
        cout << "Enter value (hex): ";
        cin >> hex >> val;
        machine.getRegisters().write(regid, val);
    }
}

void SimulatorUI::runProgram()
{
    cout << "Running program...\n";
    machine.run();
    cout << "Program execution completed or halted.\n";
}

void SimulatorUI::displayState()
{
    cout << "\n--- SIMULATOR STATE ---\n";
    cout << "PC (Hex): 0x" << hex << machine.getPC() << "\n";
    cout << "IR (Hex): " << machine.getIR() << "\n";
    cout << "Halted:   " << (machine.isHalted() ? "Yes" : "No") << "\n";
    cout << "Screen Output: " << machine.getScreen() << "\n";

    cout << "\nRegisters:\n";
    for (int i = 0; i < 16; ++i)
    {
        cout << "R" << i << ": 0x" << setw(2) << setfill('0')
             << hex << machine.getRegisters().read(i) << "  ";
        if ((i + 1) % 4 == 0)
            cout << "\n";
    }
    cout << "\n-----------------------\n";
}

bool SimulatorUI::askContinueOrExit()
{
    char ch;
    cout << "\nWould you like to return to the main menu? (y/n): ";
    cin >> ch;
    return (ch == 'y' || ch == 'Y');
}
