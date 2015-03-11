#include "screen.hpp"
	Screen::Screen()
	{
		//init vars
			for(int i=0;i<SCR_NBRLINES;i++)
			{
				screenContent[i][0]=0;
			}
			actualLine = 0;
		//init screen
			Bdisp_AllClr_DDVRAM();
	}

	void Screen::writeLine(char* str)
	{
		if(screenContent[actualLine][0]!=0)
			newline();
		setString(str,actualLine);
		newline();
		rewritescreen();
	}
	void Screen::setString(char* str, unsigned char line)
	{
		int j;
		for(j=0;j<SCR_CHARSPERLINE;j++)
		{
			if(str[j] == 0)
			{
				break;
			}
			screenContent[line][j]=str[j];
		}
		screenContent[line][j] = 0;
	}
	void Screen::setActualLine(unsigned char line)
	{
		if((int)line >= 0 && (int)line < SCR_NBRLINES)
		{
			actualLine = line;
		}
	}
	
	void Screen::write(char data)
	{
		//verify if the char is a line feed
		if(data == 0xA)
		{
			newline();
		}
		else
		{
			short unsigned int longueur = strlen(screenContent[actualLine]);
			if(longueur >= SCR_CHARSPERLINE)
			{
				newline();
				longueur = 0;
			}
			//Add the new char
				screenContent[actualLine][longueur] = data;
				screenContent[actualLine][longueur+1] = 0;
			//Writing
				char str[] = {data,0};
				PrintMini(longueur*6,6*actualLine,(unsigned char*)str,MINI_OVER);
				Bdisp_PutDisp_DD();
		}
	}
	
	void Screen::clear()
	{
		Bdisp_AllClr_DDVRAM();
		for(int i=0;i<SCR_NBRLINES-1;i++)
		{
			screenContent[i][0] = 0;
		}
		actualLine=0;
	}
	
	void Screen::newline()
	{
		if(actualLine>=SCR_NBRLINES-1)
		{
			//shifts the lines to free the last
			for(int i=0;i<SCR_NBRLINES-1;i++)
			{
				for(int j=0;j<SCR_CHARSPERLINE;j++)
				{
					if(screenContent[i+1][j] == 0)
					{
						screenContent[i][j] = 0;
						break;
					}
					screenContent[i][j]=screenContent[i+1][j];
				}
			}
			screenContent[actualLine][0] = 0;
			rewritescreen();
		}
		else
		{
			actualLine++;
			screenContent[actualLine][0] = 0;
		}
	}
	
	
	void Screen::rewritescreen()
	{
		Bdisp_AllClr_DDVRAM();
		for(int i=0;i<SCR_NBRLINES;i++)
		{
			for(int j=0;j<SCR_CHARSPERLINE;j++)
			{
				if(screenContent[i][j] == 0)
					break;
				char str[] = {screenContent[i][j],0};
				PrintMini(j*6,6*i,(unsigned char*)str,MINI_OVER);
			}
			// PrintMini(0,6*i,(unsigned char*)screenContent[i],MINI_OVER);
		}
		Bdisp_PutDisp_DD();
	}