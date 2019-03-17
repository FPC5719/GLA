{
GLA中的基本窗口操作函数
}
{$IFDEF GLA_INTERFACE}
{$IFDEF GLA_DEBUG}
{$INFO Compiling gla_base::interface}
{$ENDIF}
const
	GLACLASSNAME='GLAWNDCLS';

type
	TGLACallback=procedure(wp,lp:DWord);
	TGLALess=specialize TLess<DWord>;
	TGLACallbackMap=specialize TMap<DWord,TGLACallback,TGLALess>;
	TGLACallbackMapIterator=TGLACallbackMap.TIterator;

function glaInit:boolean;
function glaCreateWindow(x,y,w,h:DWord;s:PChar):DWord;
procedure glaBindFunc(msg:DWord;func:TGLACallback);
procedure glaLoop;
procedure glaRedisplay;
procedure glaFlush;
{$ENDIF}

{$IFDEF GLA_IMPLEMENTATION}
{$IFDEF GLA_DEBUG}
{$INFO Compiling gla_base::inplementation}
{$ENDIF}
var
	__map:TGLACallbackMap;
	__dc,__hw:DWord;

function __WindowProc(wnd,msg,wp,lp:DWord):DWord;stdcall;export;
var
	i:TGLACallbackMapIterator;
begin
	i:=__map.Find(msg);
	if i=NIL then
		exit(DefWindowProc(wnd,msg,wp,lp))
	else begin
		i.Value(wp,lp);
		exit(0);
	end;
end;
procedure __EnableOpenGL(var hw,dc,rc:DWord);
var
	pfd:PIXELFORMATDESCRIPTOR;
	iFormat:longint;
begin
    dc:=GetDC(hw);
    FillChar(pfd,sizeof(pfd),0);
    pfd.nSize:=sizeof(pfd);
    pfd.nVersion:=1;
    pfd.dwFlags:=PFD_DRAW_TO_WINDOW or PFD_SUPPORT_OPENGL or PFD_DOUBLEBUFFER;
    pfd.iPixelType:=PFD_TYPE_RGBA;
    pfd.cColorBits:=24;
    pfd.cDepthBits:=16;
    pfd.iLayerType:=PFD_MAIN_PLANE;
    iFormat:=ChoosePixelFormat(dc,pfd);
    SetPixelFormat(dc,iFormat,@pfd);
    rc:=wglCreateContext(dc);
    wglMakeCurrent(dc,rc);
end;

function glaInit:boolean;
var
	cls:WNDCLASS;
begin
	__map:=TGLACallbackMap.Create;
	with cls do begin
		Style:=CS_HREDRAW or CS_VREDRAW;
		lpfnWndProc:=WndProc(@__WindowProc);
		cbClsExtra:=0;
		cbWndExtra:=0;
		hInstance:=system.MainInstance;
		hIcon:=LoadIcon(0,IDI_APPLICATION);
		hCursor:=LoadCursor(0,IDC_ARROW);
		hbrBackground:=0;
		lpszMenuName:=NIL;
		lpszClassName:=GLACLASSNAME;
	end;
	exit(RegisterClass(cls)<>0);
end;
function glaCreateWindow(x,y,w,h:DWord;s:PChar):DWord;
var
	hw,dc,rc:DWord;
begin
	hw:=CreateWindow(GLACLASSNAME,s,WS_OVERLAPPEDWINDOW,x,y,
		w,h,0,0,system.MainInstance,NIL);
	__hw:=hw;
	if hw<>0 then begin
		__EnableOpenGL(hw,dc,rc);
		__dc:=dc;
		ShowWindow(hw,SW_SHOW);
		UpdateWindow(hw);
	end;
	exit(hw);
end;
procedure glaBindFunc(msg:DWord;func:TGLACallback);
begin
	__map.Items[msg]:=func;
end;
procedure glaLoop;
var
	amsg:MSG;
begin
	glaRedisplay;
	while GetMessage(@amsg,0,0,0) do begin
		TranslateMessage(amsg);
		DispatchMessage(amsg);
	end;
end;
procedure glaRedisplay;
begin
	InvalidateRect(__hw,NIL,TRUE);
	UpdateWindow(__hw);
end;
procedure glaFlush;
begin
	SwapBuffers(__dc);
end;
{$ENDIF}