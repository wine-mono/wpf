
COMPILE_LIB=csc -target:library

LIB_FLAGS=-debug+ -delaysign+ -keyfile:../../../ecma.pub -langversion:8.0 -nostdlib -noconfig -lib:$(MONO_PREFIX)/lib/mono/4.5-api

LIB_REFS=-r:mscorlib.dll -r:System.dll -r:System.Drawing.dll

LIB_REF_FILES=../../WindowsBase/WindowsBase.dll ../../PresentationCore/PresentationCore.dll

LIB_SRCS=SystemDrawingExtension.cs OtherAssemblyAttrs.cs

all: PresentationFramework-SystemDrawing.dll

PresentationFramework-SystemDrawing.dll: $(LIB_SRCS) $(LIB_REF_FILES)
	$(COMPILE_LIB) $(LIB_FLAGS) $(LIB_REFS) $(LIB_REF_FILES:%=-r:%) -out:$@ $(LIB_SRCS)
	sn -R $@ ../../../mono.snk
