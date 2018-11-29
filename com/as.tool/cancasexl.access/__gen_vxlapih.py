from pycparser import parse_file, c_parser, c_generator,c_ast
import os

def __GenVxapih__():
    '''convert the vxapi.h to python language
        And then modify if errors '''
    import re
    reDefine = re.compile(r'#define\s+(XL_|LIN_|RECEIVE_|MAX_)(\w+)\s+(.+)')
    reEnum  = re.compile(r'(XL_|LIN_|RECEIVE_)(\w+)\s+=\s+(.+)')
    fp1 = open('../../clang/include/vxlapi.h','r')
    fp2 = open('vxlapih.py','w')
    
    for el in fp1.readlines():
        if(reDefine.search(el)):
            grp = reDefine.search(el).groups()
            name = grp[0] + grp[1]
            value = grp[2].replace('unsigned','').replace('int','').replace('short','').replace('long','') \
                    .replace('char','').replace('(','').replace(')','').replace('//','#').replace('/*','#').replace('*/','')
            fp2.write('%-64s = %s\n'%(name,value))
        elif(reEnum.search(el)):
            grp = reEnum.search(el).groups()
            name = grp[0] + grp[1]
            value = grp[2].replace('unsigned','').replace('int','').replace('short','').replace('long','') \
                    .replace('char','').replace('(','').replace(')','').replace('//','#').replace('/*','#').replace('*/','')
            fp2.write('%-64s = %s\n'%(name,value))
        else:
            fp2.write('#'+el)
    fp2.close()
    fp1.close()
    
def __gen_vxlapi_types():
#     os.system('gcc -E ../../clang/include/vxlapi.h -D__int64=long -DHANDLE=void* -DPOINTER_32= -o vxlapi_temp.h')
#     fp = open('vxlapi_temp.h')
#     fp2 = open('vxlapi.h','w')
#     for lineno,el in enumerate(fp.readlines()):
#         if(lineno > 1983): break
#         fp2.write(el.encode('ascii','ignore'))
#     fp.close()
#     fp2.close()
#     os.remove('vxlapi_temp.h')
    ast =  parse_file('vxlapi.h')
    for node in ast.children():
        node[1].ctopy()

if(__name__ == '__main__'):
    #__GenVxapih__()
    __gen_vxlapi_types()
        
        
        
