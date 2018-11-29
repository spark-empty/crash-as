
import re

def gen_service_table(file):
    reName = re.compile(r'#define\s+SID_(\w+)\s+(\w+)')
    fp = open(file)
    cstr = 'local l_service = { '
    id = 0
    for el in fp.readlines():
        if(reName.search(el)):
            grp = reName.search(el).groups()
            id += 1
            cstr += '[%s]="%s",'%(grp[1],grp[0].replace('_', ' ').lower())
            if(id%3 == 0):
                cstr += '\n\t\t'
    cstr+='}\n\n'
    fp.close()
    print(cstr)
    
def gen_nrc_table(file):
    reName = re.compile(r'#define\s+DCM_E_(\w+)\s+\(\(Dcm_NegativeResponseCodeType\)(\w+)\)')
    fp = open(file)
    cstr = 'local l_nrc = { '
    id = 0
    for lineno,el in enumerate(fp.readlines()):
        if(reName.search(el)):
            grp = reName.search(el).groups()
            id += 1
            cstr += '[%s]="%s",'%(grp[1],grp[0].replace('_', ' ').lower())
            if(id%3 == 0):
                cstr += '\n\t\t'
    cstr+='}\n\n'
    fp.close()
    print(cstr) 
    

if(__name__ == '__main__'):
    gen_service_table('D:/repository/as/com/as.infrastructure/diagnostic/Dcm/Dcm_Internal.h')
    gen_nrc_table('D:/repository/as/com/as.infrastructure/include/Dcm_Types.h')
    