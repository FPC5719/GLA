{
GLA中的视角变换函数
}
{$IFDEF GLA_INTERFACE}
{$IFDEF GLA_DEBUG}
{$INFO Compiling gla_camera.inc::interface}
{$ENDIF}
procedure glaMoveCamera(t:extended);
procedure glaMoveCameraY(t:extended);
procedure glaTurnCamera(drd,dud:extended);
procedure glaMoveCameraTo(nx,ny,nz:extended);
procedure glaTurnCameraTo(nrd,nud:extended);
procedure glaModifyCamera;
{$ENDIF}

{$IFDEF GLA_IMPLEMENTATION}
{$IFDEF GLA_DEBUG}
{$INFO Compiling gla_camera.inc::implementation}
{$ENDIF}
var
	ud,rd,x,y,z:extended;

procedure glaMoveCamera(t:extended);
begin
	x:=x+sin(rd*PI/180)*t;
	z:=z+cos(rd*PI/180)*t;
end;
procedure glaMoveCameraY(t:extended);
begin
	y:=y+t;
end;
procedure glaTurnCamera(drd,dud:extended);
begin
	rd:=rd+drd; ud:=ud+dud;
	if rd>180 then rd:=rd-360;
	if rd<-180 then rd:=rd+360;
	if ud>90 then ud:=90;
	if ud<-90 then ud:=-90;
end;
procedure glaMoveCameraTo(nx,ny,nz:extended);
begin
	x:=nx; y:=ny; z:=nz;
end;
procedure glaTurnCameraTo(nrd,nud:extended);
begin
	rd:=nrd; ud:=nud;
end;
procedure glaModifyCamera;
begin
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity;
	gluPerspective(60,1,0.01,30);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity;
	glRotatef(ud,1,0,0);
	glRotatef(360-rd,0,1,0);
	glTranslatef(x,y,z);
end;
{$ENDIF}