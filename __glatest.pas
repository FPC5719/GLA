{$MODE DELPHI}
uses
	gl,glu,gla,windows;
var
	hwindow:DWord;
procedure Destroy(wp,lp:DWord);
begin
	PostQuitMessage(0);
end;
procedure Paint(wp,lp:DWord);
begin
	glClear(GL_COLOR_BUFFER_BIT);
	glaModifyCamera;
	glBegin(GL_LINES);
		glColor3f(1,0,0);
		glVertex3f(0,0,0);
		glVertex3f(1,0,0);
	glEnd;
	glBegin(GL_LINES);
		glColor3f(0,1,0);
		glVertex3f(0,0,0);
		glVertex3f(0,1,0);
	glEnd;
	glBegin(GL_LINES);
		glColor3f(0,0,1);
		glVertex3f(0,0,0);
		glVertex3f(0,0,1);
	glEnd;
	glFlush;
	glaFlush;
end;
procedure Keyboard(wp,lp:DWord);
begin
	case chr(wp) of
		'w':glaMoveCamera(0.1);
		's':glaMoveCamera(-0.1);
		'z':glaMoveCameraY(0.1);
		'c':glaMoveCameraY(-0.1);
		'k':glaTurnCamera(0,1);
		'i':glaTurnCamera(0,-1);
		'j':glaTurnCamera(1,0);
		'l':glaTurnCamera(-1,0);
		#27:PostQuitMessage(0);
	end;
end;
var
	nx,ny:Word;
procedure Mouse(wp,lp:DWord);
var
	x,y,w,h,l,t:Word;
	r:Rect;
begin
	GetWindowRect(hwindow,r);
	h:=r.bottom-r.top-GetSystemMetrics(4)-GetSystemMetrics(5);
	w:=r.right-r.left-GetSystemMetrics(6)*2;
	l:=r.left+GetSystemMetrics(6);
	t:=r.top+GetSystemMetrics(4);
	{ writeln(l,' ',t,' ',h,' ',w); }
	x:=Hi(lp); y:=Lo(lp);
	writeln('::',x,' ',y);
	writeln(':::',w div 2,' ',h div 2);
	glaTurnCamera(0,x-w div 2);
	SetCursorPos(t+h div 2,l+w div 2);
	glaRedisplay;
end;
begin
	glaInit;
	hwindow:=glaCreateWindow(100,100,400,400,'test');
	glaBindFunc(WM_DESTROY,Destroy);
	glaBindFunc(WM_PAINT,Paint);
	glaBindFunc(WM_CHAR,Keyboard);
	glaBindFunc(WM_MOUSEMOVE,Mouse);
	glaMoveCameraTo(0,0,0);
	glaTurnCameraTo(0,0);
	nx:=65535; ny:=65535;
	glaLoop;
end.