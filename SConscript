#import rtconfig

from building import *

cwd  = GetCurrentDir()
CPPPATH = [cwd]

LOCAL_CFLAGS = ''
LOCAL_CFLAGS += ' -DPLATFORM_ARM_QEMU'
LOCAL_CFLAGS += ' -I' + cwd + '.'
LOCAL_CFLAGS += ' -I' + cwd + '/src'
LOCAL_CFLAGS += ' -I' + cwd + '/src/logo_images'

src = Glob('src/*.c')
src += Glob('src/logo_images/*.c')

group = DefineGroup('GuitarPedals', src, depend = ['PKG_USING_GUITAR_PEDALS'], CPPPATH = CPPPATH, LOCAL_CFLAGS = LOCAL_CFLAGS)

Return('group')
