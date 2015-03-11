extern "C" {
#define __KEYBIOS_H__
#include "fxlib.h"
}
#include <iostream>
#include "screen.hpp"
#include "compatibilityscripts.cpp"

#define keypressed(code,min,maj,nbr) \
	if(KeyDown(code)){ \
	(alpha)?sendbyte=(min):((shift) ? sendbyte=(maj) : sendbyte=(nbr)); \
	Serial_WriteByte(sendbyte); \
	if(showSended)screen.write(sendbyte); \
	while(KeyDown(code) && !repetition){Sleep(1);}}

	
	int main()
	{
		//defaults settings
			bool hex = false;
			bool alpha = false;
			bool shift = false;
			bool repetition = false;
			bool showSended = false;
			unsigned char writemode = 0;//0:min , 1:maj, 2:nombres
			unsigned char readbyte = 0;
			unsigned char sendbyte = 0;
			Screen screen;
			screen.setString("    WolframCasio    ",0);
			screen.setString("     par Frazew     ",1);
			screen.setString("--------------------",2);
			screen.setString(" F1 : Effacer ecran ",3);
			screen.setString("  F6/MENU : Fermer  ",4);
			screen.setString("--------------------",5);
			screen.setString("   Votre entree :   ",6);
			screen.setActualLine(7);
			screen.rewritescreen();
		//open com port		
			unsigned char conf[]={0,5,0,0,0,0};
			Serial_Open(conf);
		//Keys
			while(1)
			{
				//F1:Reset
				if(KeyDown(KEY_CTRL_F1)){
					Serial_WriteByte(0x1B);
					screen.clear();
					while(KeyDown(KEY_CTRL_F1)){Sleep(1);}}
				//DEL: undo
				if(KeyDown(KEY_CTRL_DEL)){
					Serial_WriteByte(0x7F);
					screen.clear();
					while(KeyDown(KEY_CTRL_DEL)){Sleep(1);}}
				//ALPHA: well, alpha
				if(KeyDown(KEY_CTRL_ALPHA)){
					alpha=!alpha;
					screen.setActualLine(9);
					screen.rewritescreen();
					while(KeyDown(KEY_CTRL_ALPHA)){Sleep(1);}
				}
				//ALPHA: the same, just shift
				if(KeyDown(KEY_CTRL_SHIFT)){
					shift=!shift;
					screen.setActualLine(9);
					screen.rewritescreen();
					while(KeyDown(KEY_CTRL_SHIFT)){Sleep(1);}
				}
				//F6: Quit
				if(KeyDown(KEY_CTRL_F6)){
					Serial_WriteByte(0x18);
					break;
					while(KeyDown(KEY_CTRL_F6)){Sleep(1);}}
				//MENU: Quit
				if(KeyDown(KEY_CTRL_MENU)){
					Serial_WriteByte(0x18);
					break;
					while(KeyDown(KEY_CTRL_MENU)){Sleep(1);}}
				//EXE: NewLine 
					keypressed(KEY_CTRL_EXE,0xA,0xA,0xA);
				//Letters ? = nothing
					keypressed(KEY_CHAR_0,'z','i','0');
					keypressed(KEY_CHAR_1,'u','?','1');
					keypressed(KEY_CHAR_2,'v','?','2');
					keypressed(KEY_CHAR_3,'w','?','3');
					keypressed(KEY_CHAR_4,'p','?','4');
					keypressed(KEY_CHAR_5,'q','?','5');
					keypressed(KEY_CHAR_6,'r','?','6');
					keypressed(KEY_CHAR_7,'m','?','7');
					keypressed(KEY_CHAR_8,'n','?','8');
					keypressed(KEY_CHAR_9,'o','?','9');
					keypressed(KEY_CTRL_XTT,'a','?','X');
					keypressed(KEY_CHAR_LOG,'b','?','log');
					keypressed(KEY_CHAR_LN,'c','?','ln');
					keypressed(KEY_CHAR_SIN,'d','&','~');//arcsin sin
					keypressed(KEY_CHAR_COS,'e','\"','#');//arccos cos
					keypressed(KEY_CHAR_TAN,'f','\'?','|');//arctan tan
					keypressed(KEY_CHAR_FRAC,'g','?','/');
					keypressed(KEY_CTRL_FD,'h','?','?');
					keypressed(KEY_CHAR_LPAR,'i','?','(');
					keypressed(KEY_CHAR_RPAR,'j','?',')');
					keypressed(KEY_CHAR_COMMA,'k','?',',');
					keypressed(KEY_CHAR_STORE,'l','?','?');
					keypressed(KEY_CHAR_DP,'?','=','.');
					keypressed(KEY_CHAR_PLUS,'x','[','+');
					keypressed(KEY_CHAR_MINUS,'y',']','-');
					keypressed(KEY_CHAR_MULT,'s','{','*');
					keypressed(KEY_CHAR_DIV,'t','}','/');
					keypressed(KEY_CHAR_SQUARE,'?','`','\\');//sqrt ^2
					keypressed(KEY_CHAR_POW,'?','?','^');
					keypressed(KEY_CHAR_EXP,'?','?','@');//pi
					keypressed(KEY_CTRL_LEFT,0x16,0x16,0x16);
					keypressed(KEY_CTRL_RIGHT,0x17,0x17,0x17);
				//Read serial
				if(Serial_ReadByte(&readbyte)==0)
				{
					if(!hex)
					{
						if(readbyte == 0x3) {
							screen.clear();
						}
						else {screen.write(readbyte);}
					}
				}
				
			}
			Serial_Close(1);
	}

extern "C" 
{
	int AddIn_main(int isAppli, unsigned short OptionNum)
	{
		return main();
	}

	#pragma section _BR_Size
	unsigned long BR_Size;
	#pragma section
	#pragma section _TOP
	int InitializeSystem(int isAppli, unsigned short OptionNum){
		return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
	}
	#pragma section
}