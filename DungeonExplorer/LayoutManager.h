#pragma once
#define NOMINMAX
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <windows.h>
#include "iomanip"
#include <algorithm>
#include <regex>

class LayoutManager {
private:
	//Singleton
	static LayoutManager& GetInstance() {
		static LayoutManager Instance;
		return Instance;
	}
	LayoutManager(const LayoutManager&) = delete;
	LayoutManager& operator=(const LayoutManager&) = delete;

	//Each display section size
	const int MainLength = 95;
	const int MainHeight = 15;

	const int SideLength = 20;
	const int SideHeight = MainHeight;

	const int LogLength = MainLength + SideLength + 2;
	const int LogHeight = 12;

	//Buffers to store display contents
	std::vector<std::string> MainBuffer;
	std::vector<std::string> SideBuffer;
	std::vector<std::string> LogBuffer;

	//Default constructor
	LayoutManager() {
		MainBuffer = std::vector<std::string>(MainHeight, " ");
		SideBuffer = std::vector<std::string>(SideHeight, " ");
		LogBuffer = std::vector<std::string>(LogHeight, " ");
		SetConsoleTitle(L"Dungeon Explorer");
	}

public:
	//clear console window
	static void ClearWindow() {
		//std::cout << "\033[H";
		//system("cls");
		COORD coord = { 0, 0 };
		DWORD count;
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(hStdOut, &csbi);

		FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
		SetConsoleCursorPosition(hStdOut, coord);
	}

	//Print 3 bufferes together
	static void PrintFrame() {
		LayoutManager& LM = GetInstance();

		//Main & Side
		for (int i = 0; i < LM.MainBuffer.size(); i++) {
			std::stringstream FrameLine;
			FrameLine << "  " << LM.MainBuffer[i] << "  " << LM.SideBuffer[i];
			std::cout << FrameLine.str() << std::endl;
		}

		for (int i = 0; i < LM.LogBuffer.size(); i++) {
			std::stringstream FrameLine;
			FrameLine << "  " << LM.LogBuffer[i];
			std::cout << FrameLine.str() << std::endl;
		}
	}
	static void ResetMain() {
		//Top and bottom border
		LayoutManager& LM = GetInstance();
		LM.MainBuffer[0] = std::string(LM.MainLength, '=');
		LM.MainBuffer[LM.MainHeight - 1] = std::string(LM.MainLength, '=');

		//side borders and inner spaces
		std::stringstream temp;
		temp << "{" << std::string((LM.MainLength - 2), ' ') << "}";
		for (int i = 1; i < LM.MainHeight - 1; i++) {
			LM.MainBuffer[i] = temp.str();
		}

	}

	static void UpdateMain(const std::vector<std::string>& content, int x, int y) {
		LayoutManager& LM = GetInstance();
		//place the content to the coordinate
		for (int i = 0; i < content.size() && y + i < LM.MainHeight - 2; i++) {
			int MaxLength = (std::min)(LM.MainLength - 2 - x, GetPrintLength(content[i]));
			LM.MainBuffer[y + i + 1].replace(x + 1, MaxLength, content[i]);
		}
	}

	//Select How long to replace and overlap
	static void ForceOverlapMain(const std::vector<std::string>& content, int x, int y, int ReplaceLength) {
		LayoutManager& LM = GetInstance();
		//place the content to the coordinate
		for (int i = 0; i < content.size() && y + i < LM.MainHeight - 2; i++) {
			if (!content[i].empty()) {
				LM.MainBuffer[y + i + 1].replace(x + 1, GetPrintLength(content[i]), content[i]);
			}
		}
	}

	static void ResetSide() {
		//Top and bottom border
		LayoutManager& LM = GetInstance();
		LM.SideBuffer[0] = std::string(LM.SideLength, '=');
		LM.SideBuffer[LM.SideHeight - 1] = std::string(LM.SideLength, '=');

		//side borders and inner spaces
		std::stringstream temp;
		temp << "{" << std::string((LM.SideLength - 2), ' ') << "}";
		for (int i = 1; i < LM.SideHeight - 1; i++) {
			LM.SideBuffer[i] = temp.str();
		}

	}

	static void UpdateSide(const std::vector<std::string>& content, int x, int y) {
		LayoutManager& LM = GetInstance();
		//place the content to the coordinate
		for (int i = 0; i < content.size() && y + i < LM.SideHeight - 2; i++) {
			int MaxLength = (std::min)(LM.SideLength - 2 - x, GetPrintLength(content[i]));
			LM.SideBuffer[y + i + 1].replace(x + 1, MaxLength, content[i]);
		}
	}


	//Reset log section
	static void ResetLog() {
		//Top border
		LayoutManager& LM = GetInstance();
		LM.LogBuffer[0] = std::string(LM.LogLength, '=');

		//Inner spaces
		std::stringstream temp;
		temp << std::string(LM.LogLength, ' ');
		for (int i = 1; i < LM.LogHeight - 1; i++) {
			LM.LogBuffer[i] = temp.str();
		}

	}

	static void UpdateLog(const std::vector<std::string>& content, int x, int y) {
		LayoutManager& LM = GetInstance();
		//place the content to the coordinate
		for (int i = 0; i < content.size() && y + i < LM.LogHeight - 1; i++) {
			int MaxLength = (std::min)(LM.LogLength - 2 - x, GetPrintLength(content[i]));
			LM.LogBuffer[y + i + 1].replace(x + 1, MaxLength, content[i]);
		}
	}

	//Get Actual length of printable string without ANSI code
	static int GetPrintLength(std::string value) {
		std::regex ansi_escape("\033\\[[0-9;]*m");	//regex to remove ansi_escape codes
		std::string stripped = std::regex_replace(value, ansi_escape, "");	//remove the ansi code
		return stripped.size();
	}

	static int GetLogHeight() {
		return GetInstance().LogHeight;
	}
	static int GetMainHeight() {
		return GetInstance().MainHeight;
	}
	static int GetSideHeight() {
		return GetInstance().SideHeight;
	}
	static int GetMainLength() {
		return GetInstance().MainLength;
	}
};