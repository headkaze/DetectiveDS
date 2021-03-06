#include <nds.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "sprite_misc.h"
#include "Text.h"
#include "CConsole.h"

CConsole::CConsole(CCursor* pCursor)
{
	m_pCursor = pCursor;
	m_consoleMode = CONSOLEMODE_NORMAL;
	
	m_gfxArrowUp = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	m_gfxArrowDown = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	
	dmaCopy(sprite_miscTiles + 256 * 6, m_gfxArrowUp, 32 * 32);
	dmaCopy(sprite_miscTiles + 256 * 7, m_gfxArrowDown, 32 * 32);
	
	for(int i=0; i<CONSOLE_MAX_TEXT; i++)
		strcpy(m_textArray[i], "");

	for(int i=0; i<CONSOLE_MENU_MAX_TEXT; i++)
		strcpy(m_menuArray[i], "");
	
	Clear();
}

CConsole::~CConsole()
{
}

void CConsole::Clear()
{
	m_frameCount = 0;
	m_lineCount = 0;
	m_linePos = 0;
	m_lineOffset = 0;
		
	ClearText();
	
	m_pCursor->SetPosition(CONSOLE_MAP_X, CONSOLE_MAP_Y);
	
	HideArrows();
}

void CConsole::ClearText()
{
	for(int i=0; i<CONSOLE_MAX_VISIBLE_TEXT; i++)
	{
		static char buf[CONSOLE_MAP_WIDTH+2];
		sprintf(buf, "%*s", CONSOLE_MAP_WIDTH, "");
		DrawString(buf, CONSOLE_MAP_X, CONSOLE_MAP_Y + i, false);
	}
}

bool CConsole::AddText(const char* text)
{
	m_consoleMode = CONSOLEMODE_NORMAL;
	
	Clear();
	
	if(text == NULL)
		return false;
	
	m_lineCount = WordWrap(text);
	
	if(m_lineCount > CONSOLE_MAX_VISIBLE_TEXT)
	{
		ShowArrows();
		
		return true;
	}
	
	return false;
}

void CConsole::DrawText()
{
	for(int i=0; i<CONSOLE_MAX_VISIBLE_TEXT && m_lineOffset + i < m_lineCount; i++)
		DrawString(m_textArray[m_lineOffset + i], CONSOLE_MAP_X, CONSOLE_MAP_Y + i, false);
}

void CConsole::Update()
{
	m_frameCount++;
	
	if(m_frameCount > 3)
	{
		m_frameCount = 0;
		
		if(m_linePos < m_lineCount && m_linePos < CONSOLE_MAX_VISIBLE_TEXT)
		{	
			DrawString(m_textArray[m_linePos], CONSOLE_MAP_X, CONSOLE_MAP_Y + m_linePos, false);
			m_linePos++;
			
			m_pCursor->SetPosition(CONSOLE_MAP_X, CONSOLE_MAP_Y + m_linePos);
		}
	}
}

void CConsole::Move(DirectionType directionType)
{
	switch(directionType)
	{
		case DIRECTION_UP:
			if(m_lineOffset > 0)
				m_lineOffset--;
			break;
		case DIRECTION_DOWN:
			if(m_lineOffset + CONSOLE_MAX_VISIBLE_TEXT < m_lineCount)
				m_lineOffset++;
			break;
		case DIRECTION_LEFT:
		case DIRECTION_RIGHT:
			break;
	}
	
	ClearText();
	DrawText();
}

bool CConsole::CheckTouch(int x, int y)
{
	if(x > 140 && x < 140 + 20 && y > 120 && y < 120 + 12)
	{
		Move(DIRECTION_UP);
		return true;
	}
	
	if(x > 140 && x < 140 + 20 && y > 176 && y < 176 + 12)
	{
		Move(DIRECTION_DOWN);
		return true;
	}
	
	return false;
}

void CConsole::ClearMenu()
{
	m_menuCount = 0;
	m_menuPos = 0;
	m_menuOffset = 0;
	
	for(int i=0; i<CONSOLE_MENU_MAX_TEXT; i++)
		strcpy(m_menuArray[i], "");
	
	ClearMenuText();
	HideArrows();
}

void CConsole::ClearMenuText()
{
	for(int i=0; i<CONSOLE_MENU_VISIBLE_TEXT; i++)
	{
		static char buf[CONSOLE_MENU_MAP_WIDTH+2];
		sprintf(buf, "%*s", CONSOLE_MENU_MAP_WIDTH, "");
		DrawString(buf, CONSOLE_MENU_MAP_X, CONSOLE_MENU_MAP_Y + i, false);
	}
}

bool CConsole::AddMenuItem(const char* text, void* object)
{
	if(m_menuCount < CONSOLE_MENU_MAX_TEXT)
	{
		strcpy(m_menuArray[m_menuCount], text);
		m_objectArray[m_menuCount] = object;
		
		m_menuCount++;
		
		return true;
	}
	
	return false;
}

void CConsole::ShowMenu()
{
	m_consoleMode = CONSOLEMODE_MENU;
	
	for(int i=0; i<CONSOLE_MENU_VISIBLE_TEXT && m_menuOffset + i < m_menuCount; i++)
		DrawString(m_menuArray[m_menuOffset + i], CONSOLE_MENU_MAP_X, CONSOLE_MENU_MAP_Y + i, CONSOLE_MENU_MAP_WIDTH, false);
	
	if(m_menuCount > CONSOLE_MENU_VISIBLE_TEXT)
		ShowArrows();
}

void CConsole::HideMenu()
{
	HideSelectorBar();
	HideArrows();
}

void CConsole::MoveSelectorBar(DirectionType directionType)
{
	switch(directionType)
	{
		case DIRECTION_UP:
			if(m_menuPos > 0)
				m_menuPos--;
			else if(m_menuOffset > 0)
				m_menuOffset--;
			break;
		case DIRECTION_DOWN:
			if(m_menuPos < CONSOLE_MENU_VISIBLE_TEXT-1 && m_menuPos < m_menuCount-1)
				m_menuPos++;
			else if(m_menuPos + m_menuOffset < m_menuCount-1)
				m_menuOffset++;
			break;
		case DIRECTION_LEFT:
		case DIRECTION_RIGHT:
			break;
	}
	
	ClearMenuText();
	ShowMenu();
}

void CConsole::DrawSelectorBar()
{
	if(m_menuCount > 0)
	{
		m_selector.SetPosition(CONSOLE_MENU_X - 1, CONSOLE_MENU_Y + m_menuPos * 8 - 1);
		m_selector.Draw();
	}
}

void CConsole::HideSelectorBar()
{
	m_selector.Hide();
}

void CConsole::HideArrows()
{
	oamSet(&oamMain, 119, 140, (m_consoleMode == CONSOLEMODE_NORMAL ? 120 : 144), 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxArrowUp, 0, false, true, false, false, false);
	oamSet(&oamMain, 120, 140, 176, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxArrowDown, 0, false, true, false, false, false);
}

void CConsole::ShowArrows()
{
	oamSet(&oamMain, 119, 140, (m_consoleMode == CONSOLEMODE_NORMAL ? 120 : 144), 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxArrowUp, 0, false, false, false, false, false);
	oamSet(&oamMain, 120, 140, 176, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxArrowDown, 0,	false, false, false, false, false);
}

bool CConsole::CheckMenuTouch(int x, int y)
{
	int mapX = x / 8;
	int mapY = y / 8;
	
	if(mapX < 1 || mapX > 19 || mapY < 18 || mapY > 23)
		return false;
		
	if(x > 140 && x < 140 + 20 && y > 144 && y < 144 + 12)
	{
		//MoveSelectorBar(DIRECTION_UP);
		
		if(m_menuOffset > 0)
			m_menuOffset--;
			
		ClearMenuText();
		ShowMenu();
		
		return false;
	}
	
	if(x > 140 && x < 140 + 20 && y > 176 && y < 176 + 12)
	{
		//MoveSelectorBar(DIRECTION_DOWN);
		
		if(m_menuOffset + CONSOLE_MENU_VISIBLE_TEXT < m_menuCount)
			m_menuOffset++;
			
		ClearMenuText();
		ShowMenu();
		
		return false;
	}

	m_menuPos = mapY - 18;
	
	if(m_menuPos < m_menuCount)
		return true;
	
	return false;
}

int CConsole::WordWrap(const char* text)
{
	char c = '\0';
	static char line[CONSOLE_MAP_WIDTH+2], word[CONSOLE_MAX_WORD+2];
	int newLine = 0, linePos = 0, wordPos = 0, lineCount = 0;

	while(1)
	{
        c = *text++;

        if (c == '\0')
		{
            if (linePos > 0)
			{
                line[linePos] = '\0';
				strcpy(m_textArray[lineCount++], line);
            }

            return lineCount;
        }
		
        if (c == '\n')
			newLine = 1;

        line[linePos++] = word[wordPos++] = c;

        if (isspace(c))
            wordPos = 0;

        if (wordPos > CONSOLE_MAX_WORD)
		{
            word[wordPos] = '\0';
            return lineCount;
        }

        if (newLine || linePos > CONSOLE_MAP_WIDTH)
		{
            newLine = 0;
            linePos -= wordPos;

            while(isspace(line[--linePos]));

            line[linePos + 1] = '\0';
            strcpy(m_textArray[lineCount++], line);
            strncpy(line, word, wordPos);
            linePos = wordPos;
        }
    }

	return lineCount;
}
