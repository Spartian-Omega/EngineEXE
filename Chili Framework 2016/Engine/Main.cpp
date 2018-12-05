/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Main.cpp																			  *
*	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Frmework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/

/// Multi-Threading Windows API
#include <Windows.h>
///

#include <string>
#include <sstream>
#include <chrono>

#include "MainWindow.h"
#include "Game.h"
#include "ChiliException.h"

typedef struct ThreadData {
	Game * GameAddress;
}THREADDATA , *PTHREADDATA;

DWORD WINAPI GRAPHICSTHREAD(__in LPVOID lpParameter)
{
	PTHREADDATA pGraphicsThreadData;
	pGraphicsThreadData = (PTHREADDATA)lpParameter;

	std::wstring _debug_wstream = std::to_wstring(GetCurrentThreadId());
	OutputDebugString(L"Thread ID = ");
	OutputDebugString(_debug_wstream.c_str());
	OutputDebugString(L"\n");

	//wait for graphics
	while (pGraphicsThreadData->GameAddress->DRAW){
		double _frameInterval = 0;
		auto start = std::chrono::system_clock::now();
		if (pGraphicsThreadData->GameAddress->HOLD) {
		}
		else {
			pGraphicsThreadData->GameAddress->PushFrame();
		}
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;



		_frameInterval = elapsed_seconds.count();
		_debug_wstream = std::to_wstring(_frameInterval);
		_debug_wstream = L"Frame Interval = " + _debug_wstream + L"\n";
		OutputDebugString(_debug_wstream.c_str());
}
	return 3;
}

int WINAPI wWinMain( HINSTANCE hInst,HINSTANCE,LPWSTR pArgs,INT )
{
	//Graphics Thread
	HANDLE GRAPHICSHANDLE;
	DWORD GRAPHICSTHREADID;
	//
	try
	{
		MainWindow wnd( hInst,pArgs );		
		try
		{
			//Graphics Thread
			Game theGame( wnd );
			PTHREADDATA GRAPHICSTHREADDATA = new ThreadData;
			GRAPHICSTHREADDATA->GameAddress = & theGame;
			GRAPHICSHANDLE = CreateThread(0, 0, GRAPHICSTHREAD, GRAPHICSTHREADDATA, 0, &GRAPHICSTHREADID);
			//
			while( wnd.ProcessMessage() )
			{
				//Game Logic Loop
				theGame.Go();
				//
			}
		}
		catch( const ChiliException& e )
		{
			const std::wstring eMsg = e.GetFullMessage() + 
				L"\n\nException caught at Windows message loop.";
			wnd.ShowMessageBox( e.GetExceptionType(),eMsg );
		}
		catch( const std::exception& e )
		{
			// need to convert std::exception what() string from narrow to wide string
			const std::string whatStr( e.what() );
			const std::wstring eMsg = std::wstring( whatStr.begin(),whatStr.end() ) + 
				L"\n\nException caught at Windows message loop.";
			wnd.ShowMessageBox( L"Unhandled STL Exception",eMsg );
		}
		catch( ... )
		{
			wnd.ShowMessageBox( L"Unhandled Non-STL Exception",
				L"\n\nException caught at Windows message loop." );
		}
	}
	catch( const ChiliException& e )
	{
		const std::wstring eMsg = e.GetFullMessage() +
			L"\n\nException caught at main window creation.";
		MessageBox( nullptr,eMsg.c_str(),e.GetExceptionType().c_str(),MB_OK );
	}
	catch( const std::exception& e )
	{
		// need to convert std::exception what() string from narrow to wide string
		const std::string whatStr( e.what() );
		const std::wstring eMsg = std::wstring( whatStr.begin(),whatStr.end() ) +
			L"\n\nException caught at main window creation.";
		MessageBox( nullptr,eMsg.c_str(),L"Unhandled STL Exception",MB_OK );
	}
	catch( ... )
	{
		MessageBox( nullptr,L"\n\nException caught at main window creation.",
			L"Unhandled Non-STL Exception",MB_OK );
	}

	return 0;
}