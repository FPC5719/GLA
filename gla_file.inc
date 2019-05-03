{$IFDEF GLA_INTERFACE}
{$IFDEF GLA_DEBUG}
{$INFO Compiling gla_math::interface}
{$ENDIF}
type
	TGLAByteFile=file of byte;

procedure glaReadPointer(var f:TGLAByteFile;const len:longint;const ptr:pointer);
procedure glaWritePointer(var f:TGLAByteFile;const len:longint;const ptr:pointer);
{$ENDIF}

{$IFDEF GLA_IMPLEMENTATION}
{$IFDEF GLA_DEBUG}
{$INFO Compiling gla_math::implementation}
procedure glaReadPointer(var f:TGLAByteFile;const len:longint;const ptr:pointer);
var
	i:longint;
begin
	for i:=0 to len-1 do read(f,PByte(ptr)[i]);
end;
procedure glaWritePointer(var f:TGLAByteFile;const len:longint;const ptr:pointer);
var
	i:longint;
begin
	for i:=0 to len-1 do write(f,PByte(ptr)[i]);
end;
{$ENDIF}

{$ENDIF}