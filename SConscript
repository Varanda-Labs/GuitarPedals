import rtconfig

from building import *

src = Glob('*.c')
src += Glob('assets/*.c')

group = DefineGroup('GuitarPedals', src, depend = ['PKG_USING_GUITAR_PEDALS'])

Return('group')
