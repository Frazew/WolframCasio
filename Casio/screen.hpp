#ifndef SCREEN_H
#define SCREEN_H

extern "C" {
	#include "syscall.h"
	#include "fxlib.h"
	#include "string.h"
}

#define SCR_NBRLINES 10
#define SCR_CHARSPERLINE 21

class Screen{
	public :
		Screen();
		void rewritescreen();
		void write(char data);
		void clear();
		void newline();
		void setString(char* str, unsigned char line);
		void writeLine(char* str);
		void setActualLine(unsigned char line);
	private :
		char screenContent[SCR_NBRLINES][SCR_CHARSPERLINE+1];
		int actualLine;
};


#endif // SCREEN_H