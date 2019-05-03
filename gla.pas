{
GL Addons
对GL、GLU中的东西进行了一定的整合
（或许）可以简化使用
FPC5719
2019.3
}
{$MODE OBJFPC}
{$DEFINE GLA_DEBUG}
unit gla;

interface

uses
	gl,glu,glext,windows,
	gMap,gUtil,
	fpImage,fpReadBMP,fpReadJPEG,fpReadPNG,fpReadGIF;

{$IFNDEF GLA_INTERFACE}
{$DEFINE GLA_INTERFACE}
{$ENDIF}
{$IFDEF GLA_IMPLEMENTATION}
{$UNDEF GLA_IMPLEMENTATION}
{$ENDIF}

{$INCLUDE gla_base.inc}
{$INCLUDE gla_file.inc}
{$INCLUDE gla_math.inc}
{$INCLUDE gla_camera.inc}
{$INCLUDE gla_texture.inc}
{$INCLUDE gla_model.inc}

implementation

{$IFNDEF GLA_IMPLEMENTATION}
{$DEFINE GLA_IMPLEMENTATION}
{$ENDIF}
{$IFDEF GLA_INTERFACE}
{$UNDEF GLA_INTERFACE}
{$ENDIF}

{$INCLUDE gla_base.inc}
{$INCLUDE gla_file.inc}
{$INCLUDE gla_math.inc}
{$INCLUDE gla_camera.inc}
{$INCLUDE gla_texture.inc}
{$INCLUDE gla_model.inc}

end.