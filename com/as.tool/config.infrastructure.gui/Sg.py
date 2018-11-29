__hh__ = '''
/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2015  AS <parai@foxmail.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */
 '''
 
import sys,os
from PIL import Image
import xml.etree.ElementTree as ET
import re
import glob

reSgBMP = re.compile(r'SgBMP\{(\d+)\}')
reSgTXT = re.compile(r'SgTXT\{(\d+)\}')

__SGL_MAX = 0


def CName(s):
    return s.replace('.','_').replace('/','_').replace('\\','_')

class Sg():
    def __init__(self,file,option=None):
        self.file = file
        self.option = option

    def getPixel(self, IM, x, y):
        rgb = IM.getpixel((x,y))
        if(type(rgb) == int):
            pass
        elif(len(rgb) == 4):
            rgb = (rgb[0]<<16) + (rgb[1]<<8) + rgb[2] + (rgb[3]<<24)
        elif(len(rgb) == 3):
            rgb = (rgb[0]<<16) + (rgb[1]<<8) + rgb[2]
        else:
            print('rgb is', rgb)
            assert(0)
        return rgb

    def toU8Dot(self,fp,X=0,Y=0):

        name = os.path.basename(self.file)
        name = name[:name.find('.')]
        code = hex(ord(name))[2:].upper()
        aname = os.path.abspath(self.file)
        fp.write('static const uint8 sgf_dot_%s[] = \n{'%(code))

        try:
            IM = Image.open(self.file)
        except NameError:
            fp.write('\t0\n};\n')
            return
        fp.write('\n\t%s,%s,/* size(w,h) */'%(IM.size[0],IM.size[1]))
        for y in range(0,IM.size[1]):
            fp.write('\n\t')
            DOT = B = 0
            for x in range(0,IM.size[0]):
                rgb = self.getPixel(IM,x,y)
                if(rgb != 0):
                    DOT = DOT|(1<<B);    
                B += 1;
                if(B == 8):
                    fp.write('0x%-2X,'%(DOT))
                    DOT = 0;B = 0;
            if(B>0):
                fp.write('0x%-2X,'%(DOT))
        fp.write('\n};\n')
    def filterForTelltale(self,rgb):
        # as I don't want to use GIMP to create each valid TT PNG, so just
        # use this API to filter out the black color
        alpha = (rgb>>24) & 0xFF;
        #if(alpha == 0): # this is empty color
        #    return 0
        r = (rgb>>16) & 0xFF;
        g = (rgb>>8) & 0xFF;
        b = (rgb>>0) & 0xFF;
        if(r < 80 and g < 80 and b < 80): # black
            return 0
        if(r > 0xE0 and g > 0xE0 and b > 0xE0): # white
            return 0
        return rgb

    def toU8Pixel(self,fp,X=0,Y=0):
        name = CName(os.path.basename(self.file))
        aname = os.path.abspath(self.file)
        fp.write('#include "Sg.h"\n')
        fp.write('static const uint32 %s_bmp[] = \n{'%(name))
        IM = Image.open(self.file)
        for y in range(0,IM.size[1]): # height
            fp.write('\n\t')
            for x in range(0,IM.size[0]): # width
                rgb = self.getPixel(IM,x,y)
                if(name[:3]=='tt_'):
                    rgb = self.filterForTelltale(rgb)
                fp.write('0x%-8X,'%(rgb))
        fp.write('\n};\n')
        fp.write('static const SgBMP %s_BMP=\n'%(name))
        fp.write('{  /* %s */\n'%(aname))
        fp.write('\t/*x=*/%s,\n'%(X))
        fp.write('\t/*y=*/%s,\n'%(Y))
        fp.write('\t/*w=*/%s,\n'%(IM.size[0])) # width
        fp.write('\t/*h=*/%s,\n'%(IM.size[1])) # height
        fp.write('\t/*p=*/%s_bmp\n};\n'%(name))

def GetSgImage(IML=[],fp=None):
    for image in IML:
        if(fp != None):
            Sg(image[0]).toU8Pixel(fp,image[1],image[2])

def GetSgFont(IML=[],fp=None):
    for image in IML:
        if(fp != None):
            Sg(image).toU8Dot(fp)
            
def GenearteSgBMP(widget,fph,fpc):            
    global __SGL_MAX
    fp = open('SgRes/%s.c'%(widget.attrib['name']),'w')
    size = int(reSgBMP.search(widget.attrib['type']).groups()[0],10)
    IML = []
    for p in widget:
        if(p.tag=='SgBMP'):
            IML.append((p.attrib['locate'],p.attrib['x'],p.attrib['y']))
    if(len(IML) == size):
        GetSgImage(IML,fp)
    else:
        raise Exception('size SG widget picture is not right <size=%s,len(SgPciture)=%s>!'%(size,len(IML)))
    fp.write('static const SgBMP* %s_BMPS[%s] = \n{\n'%(widget.attrib['name'],size))
    for i,(file,x,y) in enumerate(IML):
        name = CName(os.path.basename(file))
        fp.write('\t&%s_BMP,\n'%(name))
        fph.write("#define SGR_%-32s %s\n"%(name.upper(),i))
    fp.write('};\n\n')
    
    fp.write('const SgSRC %s_SRC = \n{\n'%(widget.attrib['name']))
    fp.write('\t/*t =*/%s,\n'%('SGT_BMP'))
    fp.write('\t/*rs=*/%s,\n'%(size))
    fp.write('\t/*r =*/(const SgRes**)%s_BMPS,\n'%(widget.attrib['name']))
    fp.write('\t/*rf=*/(void*(*)(void*))%s,\n'%(widget.attrib['refresh']))
    fp.write('\t/*cf=*/(void(*)(void*))%s,\n'%(widget.attrib['cache']))
    fp.write('\t/*weight=*/%s,\n'%(widget.attrib['weight']))
    fp.write('\t/*name=*/"%s"\n'%(widget.attrib['name']))
    fp.write('};\n\n')
    
    if(widget.attrib['refresh'] != 'NULL'):
        fph.write('extern void* %s(SgWidget* w);\n'%(widget.attrib['refresh']))

    if(widget.attrib['cache'] != 'NULL'):
        fph.write('extern void %s(SgWidget* w);\n'%(widget.attrib['cache']))
    
    fph.write('extern const SgSRC %s_SRC;\n'%(widget.attrib['name']))
    
    fpc.write('\t{ /* SGW_%s */\n'%(widget.attrib['name'].upper()))
    fpc.write('\t\t/*x =*/%s,\n'%(widget.attrib['x']))
    fpc.write('\t\t/*y =*/%s,\n'%(widget.attrib['y']))
    fpc.write('\t\t/*w =*/%s,\n'%(widget.attrib['w']))
    fpc.write('\t\t/*h =*/%s,\n'%(widget.attrib['h']))
    fpc.write('\t\t/*c =*/%s,\n'%(0))
    fpc.write('\t\t/*d =*/%s,\n'%('0xFFFF/*no rotation*/'))
    fpc.write('\t\t/*l =*/%s,\n'%(widget.attrib['layer']))
    if(int(widget.attrib['layer'],10) > __SGL_MAX ): __SGL_MAX = int(widget.attrib['layer'],10)
    name = CName(os.path.basename(IML[0][0]))
    fpc.write('\t\t/*ri=*/SGR_%s,\n'%(name.upper()))
    fpc.write('\t\t/*src =*/&%s_SRC\n'%(widget.attrib['name']))
    fpc.write('\t},\n')  
    fp.close()  
def GenearteSgTXT(widget,fph,fpc):
    global __SGL_MAX
    fp = open('SgRes/%s.c'%(widget.attrib['name']),'w')
    fp.write('#include "Sg.h"\n')
    size = int(reSgTXT.search(widget.attrib['type']).groups()[0],10)
    
    FNT = []
    for p in widget:
        if(p.tag=='SgTXT'):
            FNT.append(p.attrib['refer'])
    if(len(FNT) == size):
        pass
    else:
        raise Exception('size SG widget text is not right <size=%s,len(SgTXT)=%s>!'%(size,len(FNT)))
    fp.write('static const SgTXT* %s_TXTS[%s] = \n{\n'%(widget.attrib['name'],size))
    for i,font_name in enumerate(FNT):
        fp.write('\t&sgf%s,\n'%(font_name))
        fph.write("#define SGR_%-32s %s\n"%(font_name.upper(),i))
    fp.write('};\n\n')
    
    if(widget.attrib['refresh'] != 'NULL'):
        fph.write('extern void* %s(SgWidget* w);\n'%(widget.attrib['refresh']))
    
    fph.write('extern const SgSRC %s_SRC;\n'%(widget.attrib['name']))    
    fp.write('const SgSRC %s_SRC = \n{\n'%(widget.attrib['name']))
    fp.write('\t/*t =*/%s,\n'%('SGT_TXT'))
    fp.write('\t/*rs=*/%s,\n'%(size))
    fp.write('\t/*r =*/(const SgRes**)%s_TXTS,\n'%(widget.attrib['name']))
    fp.write('\t/*rf=*/(void*(*)(void*))%s\n'%(widget.attrib['refresh']))
    fp.write('};\n\n')
    
    fpc.write('\t{ /* SGW_%s */\n'%(widget.attrib['name'].upper()))
    fpc.write('\t\t/*x =*/%s,\n'%(widget.attrib['x']))
    fpc.write('\t\t/*y =*/%s,\n'%(widget.attrib['y']))
    fpc.write('\t\t/*w =*/%s,\n'%(widget.attrib['w']))
    fpc.write('\t\t/*h =*/%s,\n'%(widget.attrib['h']))
    fpc.write('\t\t/*c =*/%s,\n'%(0))
    fpc.write('\t\t/*d =*/%s,\n'%('0xFFFF/*no rotation*/'))
    fpc.write('\t\t/*l =*/%s,\n'%(widget.attrib['layer']))
    if(int(widget.attrib['layer'],10) > __SGL_MAX ): __SGL_MAX = int(widget.attrib['layer'],10)
    fpc.write('\t\t/*ri=*/SGR_%s,\n'%(font_name.upper()))
    fpc.write('\t\t/*src =*/&%s_SRC\n'%(widget.attrib['name']))
    fpc.write('\t},\n') 
    
    fp.close()  

def GenearteSgFont(widget,fph,fpc):
    locate = widget.attrib['locate']
    font_name = widget.attrib['name']
    fp = open('SgRes/%s.c'%(font_name),'w')
    fp.write('#include "Sg.h"\n\n')
    IML = []
    for png in glob.glob('%s/*.png'%(locate)):
        IML.append(png)
    GetSgFont(IML,fp)
    
    fp.write('static const uint16 sgf_%s_look_up_table[%s] = \n{'%(font_name,len(IML)))
    chars = []
    for png in IML:
        name = os.path.basename(png)
        name = name[:name.find('.')]
        code = ord(name)
        chars.append(code)
    chars.sort()
    for i,chr in enumerate(chars):
        if(i%4==0):fp.write('\n\t')
        fp.write('0x%-4s,'%(hex(chr).upper()[2:]))
    fp.write('\n};\n\n')
    
    fp.write('static const uint8* sgf_%s_res_pointer_table[%s] = \n{'%(font_name,len(IML)))
    for i,chr in enumerate(chars):
        if(i%4==0):fp.write('\n\t')
        fp.write('sgf_dot_%-4s,'%(hex(chr).upper()[2:]))
    fp.write('\n};\n\n')
    
    fph.write('extern const SgTXT sgf%s;\n'%(font_name))
    
    fp.write('const SgTXT sgf%s = \n{\n'%(font_name))
    fp.write('\t/*l=*/sgf_%s_look_up_table,\n'%(font_name))
    fp.write('\t/*p=*/sgf_%s_res_pointer_table,\n'%(font_name))
    fp.write('\t/*w=*/%s,\n'%(widget.attrib['w']))
    fp.write('\t/*h=*/%s,\n'%(widget.attrib['h']))
    fp.write('\t/*s=*/%s\n'%(len(IML)))
    fp.write('};\n\n')
    
    fp.close()
    
def GenerateWidget(widget,fph,fpc): 
    print('## Process Widget %s'%(widget.attrib['name']))
    
    if(reSgBMP.search(widget.attrib['type']) != None):
        GenearteSgBMP(widget,fph,fpc)
    elif(reSgTXT.search(widget.attrib['type']) != None):  
        GenearteSgTXT(widget,fph,fpc)      
    elif(widget.attrib['type'] == 'SgFont'):  
        GenearteSgFont(widget,fph,fpc)           
    else:
        raise Exception('unknown SG widget type!')
    
def GenerateSg(file):
    global __SGL_MAX
    if(os.path.exists('SgRes')==False): 
        os.mkdir('SgRes') 
    root = ET.parse(file).getroot();
    widgets  = []
    for w in root:
        if(w.tag == 'SgWidget'):widgets.append(w)
        
    fonts  = []
    for f in root:
        if(f.tag == 'SgFont'):fonts.append(f)    
            
    fph = open('SgRes/SgRes.h','w')
    fpc = open('SgRes/SgRes.c','w')
    fpc.write(__hh__)
    fpc.write('\n#include "Sg.h"\n')
    fph.write(__hh__)
    fph.write('\n#ifndef SGRES_H\n#define SGRES_H\n\n')
    fph.write('#define __SG_WIDTH__ %s\n'%(root.attrib['w']))
    fph.write('#define __SG_HEIGHT__ %s\n\n'%(root.attrib['h']))
    fph.write('#define __SG_PIXEL__ %s\n\n'%(root.attrib['p']))
    
    fpc.write('SgWidget SGWidget[%s] = \n{\n'%(len(widgets)))
    for w in widgets:
        GenerateWidget(w,fph,fpc)
    fpc.write('};\n\n')
    # font is a special widget
    for f in fonts:
        GenerateWidget(f,fph,fpc)        
    
    fph.write('\n\n')
    for i,w in enumerate(widgets):
        fph.write('#define SGW_%-32s %s\n'%(w.attrib['name'].upper(),i))
    fph.write('#define SGW_%-32s %s\n'%('MAX',len(widgets)))
    fph.write('\n\nextern SgWidget SGWidget[%s];\n\n'%(len(widgets)))
    fph.write("\n\n#define SGL_MAX %s\n\n"%(__SGL_MAX+1))
    fph.write('#endif\n\n')
    fph.close()
    fpc.close()
    print(">>>>>>>> DONE! <<<<<<<<<")
 
if(__name__ == '__main__'):
    if(len(sys.argv) == 2):
        GenerateSg(sys.argv[1])
        

            
        
