{
GLA中的模型导入、导出及处理模块
}
{$IFDEF GLA_INTERFACE}
{$IFDEF GLA_DEBUG}
{$INFO Compiling gla_model::interface}
{$ENDIF}
type
	TGLAModelVertex=record
		a:TGLAVertex3D;
		b:TGLAVertex2D;
	end;
	
procedure glaLoadVertex(var f:TGLAByteFile;var v:TGLAModelVertex);
procedure glaSaveVertex(var f:TGLAByteFile;const v:TGLAModelVertex);

type
	TGLASurface=class
	private type
		TLL=specialize TLess<longint>;
		TMV=specialize TMap<longint,TGLAModelVertex,TLL>;
	private
		vtx:TMV;
	public
		constructor Create;
		destructor Destroy;override;
		procedure SaveToFile(var f:TGLAByteFile);
		procedure LoadFromFile(var f:TGLAByteFile);
		procedure AddVertex(v:TGLAModelVertex);
		property Vertexes:TMV read vtx;
	end;

type
	TGLAModel=class
	private type
		TLL=specialize TLess<longint>;
		TMS=specialize TMap<longint,TGLASurface,TLL>;
	private
		sur:TMS;
	public
		constructor Create;
		destructor Destroy;override;
		procedure SaveToFile(var f:TGLAByteFile);
		procedure LoadFromFile(var f:TGLAByteFile);
		procedure AddSurface(s:TGLASurface);
		property Surfaces:TMS read sur;
		function BuildDisplayList(txr:GLUint):GLUint;
	end;
{$ENDIF}

{$IFDEF GLA_IMPLEMENTATION}
{$IFDEF GLA_DEBUG}
{$INFO Compiling gla_model::inplementation}
{$ENDIF}
procedure glaLoadVertex(var f:TGLAByteFile;var v:TGLAModelVertex);
begin
	glaLoadVertex(f,v.a); glaLoadVertex(f,v.b);
end;
procedure glaSaveVertex(var f:TGLAByteFile;const v:TGLAModelVertex);
begin
	glaSaveVertex(f,v.a); glaSaveVertex(f,v.b);
end;

constructor TGLASurface.Create;
begin
	vtx:=TMV.Create;
end;
destructor TGLASurface.Destroy;
begin
	vtx.Destroy;
end;
procedure TGLASurface.SaveToFile(var f:TGLAByteFile);
var
	i,len:longint;
	v:TGLAModelVertex;
begin
	len:=vtx.Size;
	glaWritePointer(f,sizeof(len),@len);
	for i:=1 to len do begin
		v:=vtx.Items[i];
		glaSaveVertex(f,v);
	end;
end;
procedure TGLASurface.LoadFromFile(var f:TGLAByteFile);
var
	i,len:longint;
	v:TGLAModelVertex;
begin
	vtx.Destroy;
	vtx:=TMV.Create;
	glaReadPointer(f,sizeof(len),@len);
	for i:=1 to len do begin
		glaLoadVertex(f,v);
		vtx.Items[i]:=v;
	end;
end;
procedure TGLASurface.AddVertex(v:TGLAModelVertex);
begin
	vtx.Items[vtx.Size+1]:=v;
end;

constructor TGLAModel.Create;
begin
	sur:=TMS.Create;
end;
destructor TGLAModel.Destroy;
begin
	sur.Destroy;
end;
procedure TGLAModel.SaveToFile(var f:TGLAByteFile);
var
	i,len:longint;
begin
	len:=sur.Size;
	glaWritePointer(f,sizeof(len),@len);
	for i:=1 to len do
		sur.Items[i].SaveToFile(f);
end;
procedure TGLAModel.LoadFromFile(var f:TGLAByteFile);
var
	i,len:longint;
begin
	glaReadPointer(f,sizeof(len),@len);
	for i:=1 to len do begin
		sur.Items[i]:=TGLASurface.Create;
		sur.Items[i].LoadFromFile(f);
	end;
end;
procedure TGLAModel.AddSurface(s:TGLASurface);
begin
	sur.Items[sur.Size+1]:=s;
end;

function TGLAModel.BuildDisplayList(txr:GLUint):GLUint;
var
	res:GLUint;
	i,j:longint;
begin
	res:=glGenLists(1);
	glBindTexture(GL_TEXTURE_2D,txr);
	glNewList(res,GL_COMPILE);
	for i:=1 to sur.Size do begin
		glBegin(GL_POLYGON);
		for j:=1 to sur.Items[i].vtx.Size do begin
			with sur.Items[i].vtx.Items[j] do begin
				glTexCoord2f(b.x,b.y);
				glVertex3f(a.x,a.y,a.z);
			end;
		end;
		glEnd;
	end;
	glEndList;
	exit(res);
end;
{$ENDIF}