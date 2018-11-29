TARGET = AS.pyd
OFILES = sipAScmodule.obj sipASasdev.obj sipAScan.obj
HFILES = sipAPIAS.h 

CC = cl
CXX = cl
LINK = link
CPPFLAGS = -DNDEBUG -DUNICODE -DWIN32 -I. -IC:\Anaconda3\include
CFLAGS = --std=gnu99 -nologo -Zm200 -Zc:wchar_t- -FS -Zc:strictStrings -O2 -MD -W3 -w44456 -w44457 -w44458
CXXFLAGS = -nologo -Zm200 -Zc:wchar_t- -FS -Zc:strictStrings -D_HAS_EXCEPTIONS=0 -O2 -MD -W3 -w34100 -w34189 -w44996 -w44456 -w44457 -w44458 -wd4577
LFLAGS = /NOLOGO /DYNAMICBASE /NXCOMPAT /DLL /MANIFEST /MANIFESTFILE:$(TARGET).manifest /SUBSYSTEM:WINDOWS /INCREMENTAL:NO
LIBS = /LIBPATH:E:\as\release\aslua\out /LIBPATH:C:\Anaconda3\libs pyas.lib aws.lib pthread.lib m.lib PCANBasic.lib pyas.lib wsock32.lib python36.lib
.SUFFIXES: .c .cpp .cc .cxx .C


{.}.cpp{}.obj::
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) -Fo @<<
	$<
<<

{.}.cc{}.obj::
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) -Fo @<<
	$<
<<

{.}.cxx{}.obj::
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) -Fo @<<
	$<
<<

{.}.C{}.obj::
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) -Fo @<<
	$<
<<

{.}.c{}.obj::
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -Fo @<<
	$<
<<

all: $(TARGET)

$(OFILES): $(HFILES)

$(TARGET): $(OFILES)
	$(LINK) $(LFLAGS) /OUT:$(TARGET) @<<
	  $(OFILES) $(LIBS)
<<
	mt -nologo -manifest $(TARGET).manifest -outputresource:$(TARGET);2

install: $(TARGET)
	@if not exist C:\Anaconda3\Lib\site-packages mkdir C:\Anaconda3\Lib\site-packages
	copy /y $(TARGET) C:\Anaconda3\Lib\site-packages\$(TARGET)

clean:
	-del $(TARGET)
	-del sipAScmodule.obj
	-del sipASasdev.obj
	-del sipAScan.obj
	-del $(TARGET).manifest
