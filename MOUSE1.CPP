#include <string.h>
#include <dos.h>
#include<graphics.h>

int x,y,button;

load_driver()
{
	union REGS in,out;

	in.x.ax=0;
	int86(0x33,&in,&out);
	return(out.x.ax);
}

show_mouse()
{
	union REGS in,out;

	in.x.ax=1;
	int86(0x33,&in,&out);
}

hide_mouse()
{
	union REGS in,out;

	in.x.ax=2;
	int86(0x33,&in,&out);
}

mouse_position()
{
	union REGS in,out;

	in.x.ax=3;
	int86(0x33,&in,&out);
	button=out.x.bx;
	x=out.x.cx;
	y=out.x.dx;
}

int button_pressed(int button_no)
{
	union REGS r;

	r.x.ax=0x0005;
	r.x.bx=button_no;
	int86(0x33, &r, &r);
	return r.x.bx;
}

int button_released(int button_no)
{
	union REGS r;

	r.x.ax=0x0006;
	r.x.bx=button_no;
	int86(0x33, &r, &r);
	return r.x.bx;
}

void limited_mouse(int x1,int y1,int x2,int y2)
{
	union REGS in, out;

	in.x.ax=7;
	in.x.cx=x1;
	in.x.dx=x2;
	int86(0x33,&in,&out);

	in.x.ax=8;
	in.x.cx=y1;
	in.x.dx=y2;
	int86(0x33,&in,&out);

}


void mouse(char *action)
{
	if(strcmp(action,"load & show")==0) {load_driver();show_mouse();}
	else if(strcmp(action,"load")==0) load_driver();
	else if(strcmp(action,"show")==0) show_mouse();
	else if(strcmp(action,"hide")==0) hide_mouse();
	else if(strcmp(action,"pos")==0) mouse_position();

}
