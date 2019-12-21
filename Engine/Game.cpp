/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	Vec2 delta_pos = { 0, 0 };
	character.StopMovment();
	if (wnd.kbd.KeyIsPressed('W'))
	{
		character.SetDirection({ 0, 1 });
		delta_pos.y = -1.0f ;
	}

	if (wnd.kbd.KeyIsPressed('A'))
	{
		character.SetDirection({ -1, 0 });
		delta_pos.x = -1.0f;
	}

	if (wnd.kbd.KeyIsPressed('S'))
	{
		character.SetDirection({ 0, -1 });
		delta_pos.y = 1.0f;
	}

	if (wnd.kbd.KeyIsPressed('D'))
	{
		character.SetDirection({ 1, 0 });
		delta_pos.x = 1.0f;
	}

	character.Update(time.Mark(), delta_pos);
}

void Game::ComposeFrame()
{
	character.Draw(gfx);
}
