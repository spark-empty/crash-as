

# board any: for any kind of board

With this any board, no need to submit the bsp code to as to reduce the size of as repository.

## How to use

### 1. place all related code in one directroty(named it as env BOARD_NAME) under directory board.any

```
set BOARD_NAME=THE_NAME_OF_THE_BOARD
mkdir -p %ASROOT%/com/as.application/board.any/%BOARD_NAME%
```

### 2. draft BOARD_NAME/Kconfig, below is a template
```c
config ARCH_ANY
    bool
    default y
    select DEFAULT_ASKAR

config ARCH
    string
    default "none"
```
### 2. draft BOARD_NAME/SConscript, below is a template
```python
import os
from building import *

cwd = GetCurrentDir()

Import('asenv')
ASROOT = asenv['ASROOT']

# draft the default modules
MODULES = ['ECUM','SCHM','MCU',
           'DET',
           'CLIB_STDIO_PRINTF',
           'ASKAR',
           'CAN','CANIF','PDUR','COM','COMM',
           ]

ARCH='none' # set it to "none" if not use the arch in AS
arch='aaaa' # according to implemetation of the boaed

if(asenv['MODULES'] is None):
    asenv['MODULES'] = MODULES
else:
    MODULES = asenv['MODULES']

asenv['ARCH'] = ARCH
asenv['arch'] = arch

objs = []
asenv.Append(CPPPATH=['%s/common'%(cwd)])

if('MCU' in MODULES):
    objs += Glob('config/Mcu*.c')
    objs += Glob('mcal/Mcu*.c')

# add more according to real situation

SelectCompilerXXX() # or draft according your board compiler 
# and any other special compiler FLAGS(AS/CC/LINK)

Return('objs')
```

## how to BUILD

```
set BOARD=any
set ANY=BOARD_NAME
scons --menuconfig
scons
```

