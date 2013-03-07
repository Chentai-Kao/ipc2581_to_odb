#!/usr/bin/python

# class name without prefix
names = ['Butterfly', 'Circle', 'Contour', 'Diamond', 'Donut', \
         'Ellipse', 'Hexagon', 'Moire', 'Octagon', 'Oval', \
         'RectCenter', 'RectCham', 'RectCorner', 'RectRound', 'Thermal', \
         'Triangle']

for name in names:
    # .h file
    f = open('sp' + name.lower() + '.h', 'w')
    f.write('#ifndef __SP%s_H__\n' % name.upper())
    f.write('#define __SP%s_H__\n' % name.upper())
    f.write('\n')
    f.write('#include "standardprimitive.h"\n')
    f.write('\n')
    f.write('class Sp%s : public StandardPrimitive\n' % name)
    f.write('{\n')
    f.write('public:\n')
    f.write('};\n')
    f.write('\n')
    f.write('#endif')
    f.close()
    # .cpp file
    f = open('sp' + name.lower() + '.cpp', 'w')
    f.write('#include "%s"\n' % ('sp' + name.lower() + '.h'))
    f.close()
