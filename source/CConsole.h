#ifndef __CCONSOLE_H__
#define __CCONSOLE_H__

#include <nds.h>
#include "Globals.h"
#include "CCursor.h"
#include "CSelector.h"

#define CONSOLE_X					8
#define CONSOLE_Y					120
#define CONSOLE_WIDTH				144
#define CONSOLE_HEIGHT				64

#define CONSOLE_MAP_X				(CONSOLE_X / 8)
#define CONSOLE_MAP_Y				(CONSOLE_Y / 8)
#define CONSOLE_MAP_WIDTH			(CONSOLE_WIDTH / 8)
#define CONSOLE_MAP_HEIGHT			(CONSOLE_HEIGHT / 8)

#define CONSOLE_MENU_X				8
#define CONSOLE_MENU_Y				144
#define CONSOLE_MENU_WIDTH			144
#define CONSOLE_MENU_HEIGHT			40

#define CONSOLE_MENU_VISIBLE_TEXT	5
#define CONSOLE_MENU_MAX_TEXT		16

#define CONSOLE_MENU_MAP_X			(CONSOLE_MENU_X / 8)
#define CONSOLE_MENU_MAP_Y			(CONSOLE_MENU_Y / 8)
#define CONSOLE_MENU_MAP_WIDTH		(CONSOLE_MENU_WIDTH / 8)
#define CONSOLE_MENU_MAP_HEIGHT		(CONSOLE_MENU_HEIGHT / 8)

#define CONSOLE_MAX_VISIBLE_TEXT	8
#define CONSOLE_MAX_TEXT			16
#define CONSOLE_MAX_WORD			CONSOLE_MAP_WIDTH

enum ConsoleMode
{
	CONSOLEMODE_NORMAL,
	CONSOLEMODE_MENU
};

class CConsole
{
public:
	CConsole(CCursor* pCursor);
	~CConsole();
	
	void Clear();
	void ClearText();
	bool AddText(const char* text);
	void DrawText();
	void Update();
	void Move(DirectionType directionType);
	bool CheckTouch(int x, int y);
	void ClearMenu();
	bool AddMenuItem(const char* text, void* object);
	void ShowMenu();
	void HideMenu();
	bool CheckMenuTouch(int x, int y);

	void MoveSelectorBar(DirectionType directionType);
	void DrawSelectorBar();
	void HideSelectorBar();
	void HideArrows();
	void ShowArrows();
	
	int MenuCount() const { return m_menuCount; }
	int SelectedIndex() const { return (m_menuOffset + m_menuPos); }
	void* SelectedObject() const { return m_objectArray[m_menuOffset + m_menuPos]; }
	
private:
	CCursor* m_pCursor;
	CSelector m_selector;
	
	ConsoleMode m_consoleMode;
	
	int m_linePos;
	int m_lineOffset;
	int m_lineCount;
	
	int m_menuPos;
	int m_menuOffset;
	int m_menuCount;
	
	u16* m_gfxArrowUp;
	u16* m_gfxArrowDown;

	int m_frameCount;

	char m_textArray[CONSOLE_MAX_TEXT][CONSOLE_MAP_WIDTH+2];
	char m_menuArray[CONSOLE_MENU_MAX_TEXT][CONSOLE_MAP_WIDTH+2];
	void* m_objectArray[CONSOLE_MENU_MAX_TEXT];
	
	void ClearMenuText();
	int WordWrap(const char* text);
};

#endif
