import os
import glob
import sipconfig 

def sip_makefile(module):
    # The name of the SIP build file generated by SIP and used by the build
    # system.
    build_file = "%s.sbf"%(module)
    
    # Get the SIP configuration information.
    config = sipconfig.Configuration()
    
    # Run SIP to generate the code.
    os.system(" ".join([config.sip_bin, "-c", ".", "-b", build_file, "%s.sip"%(module)]))
    
    # Create the Makefile.
    makefile = sipconfig.SIPModuleMakefile(config, build_file)
    
    # Add the library we are wrapping.  The name doesn't include any platform
    # specific prefixes or extensions (e.g. the "lib" prefix on UNIX, or the
    # ".dll" extension on Windows).
    makefile.extra_libs = [module]
    makefile.extra_lib_dirs = ['.']
    makefile.extra_defines  = ['DYNAMIC_XLDRIVER_DLL','POINTER_32=']
    makefile.extra_cflags = ['--std=gnu99']
    # Generate the Makefile itself.
    makefile.generate()
    
if __name__ == '__main__':
    for i in glob.glob('*.sip'):
        os.system('d:/python34/sip.exe -c . %s'%(i))
        sip_makefile(i[:-4])  
        break  