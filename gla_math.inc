{
GLA中的数学运算函数
}
{$IFDEF GLA_INTERFACE}
{$IFDEF GLA_DEBUG}
{$INFO Compiling gla_math::interface}
{$ENDIF}
type
	TGLAVertex2D=record
		x,y:extended;
	end;
	TGLAVertex3D=record
		x,y,z:extended;
	end;

operator <(a,b:TGLAVertex2D):boolean;
operator >(a,b:TGLAVertex2D):boolean;
operator <(a,b:TGLAVertex3D):boolean;
operator >(a,b:TGLAVertex3D):boolean;

procedure glaLoadVertex(var f:TGLAByteFile;var v:TGLAVertex2D);
procedure glaSaveVertex(var f:TGLAByteFile;const v:TGLAVertex2D);
procedure glaLoadVertex(var f:TGLAByteFile;var v:TGLAVertex3D);
procedure glaSaveVertex(var f:TGLAByteFile;const v:TGLAVertex3D);
{$ENDIF}

{$IFDEF GLA_IMPLEMENTATION}
{$IFDEF GLA_DEBUG}
{$INFO Compiling gla_math::implementation}
{$ENDIF}
operator <(a,b:TGLAVertex2D):boolean;
begin
	exit((a.x<b.x)or(a.x=b.x)and(a.y<b.y));
end;
operator >(a,b:TGLAVertex2D):boolean;
begin
	exit((a.x>b.x)or(a.x=b.x)and(a.y>b.y));
end;
operator <(a,b:TGLAVertex3D):boolean;
begin
	exit((a.x<b.x)or(a.x=b.x)and(a.y<b.y)or(a.x=b.x)and(a.y=b.y)and(a.z<b.z));
end;
operator >(a,b:TGLAVertex3D):boolean;
begin
	exit((a.x>b.x)or(a.x=b.x)and(a.y>b.y)or(a.x=b.x)and(a.y=b.y)and(a.z>b.z));
end;

procedure glaLoadVertex(var f:TGLAByteFile;var v:TGLAVertex2D);
begin
	glaReadPointer(f,sizeof(v.x),@v.x);
	glaReadPointer(f,sizeof(v.y),@v.y);
end;
procedure glaSaveVertex(var f:TGLAByteFile;const v:TGLAVertex2D);
begin
	glaWritePointer(f,sizeof(v.x),@v.x);
	glaWritePointer(f,sizeof(v.y),@v.y);
end;
procedure glaLoadVertex(var f:TGLAByteFile;var v:TGLAVertex3D);
begin
	glaReadPointer(f,sizeof(v.x),@v.x);
	glaReadPointer(f,sizeof(v.y),@v.y);
	glaReadPointer(f,sizeof(v.z),@v.z);
end;
procedure glaSaveVertex(var f:TGLAByteFile;const v:TGLAVertex3D);
begin
	glaWritePointer(f,sizeof(v.x),@v.x);
	glaWritePointer(f,sizeof(v.y),@v.y);
	glaWritePointer(f,sizeof(v.z),@v.z);
end;
{$ENDIF}