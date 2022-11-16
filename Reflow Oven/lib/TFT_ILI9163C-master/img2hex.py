
# image convert utilty, takes filename(s) as arguments and creates .h files
# with 24 bit hex values.

from PIL import Image
import os,re
import argparse


code_template = """

#ifndef _{name}_h
#define _{name}_h


/*
File generated from: {file}, size {size}

EXAMPLE:
    tft.displayRGBBitmap(x, y, {name}, {name}Width, {name}Height);
*/

const word {name}Width = {width};
const word {name}Height = {height};
const word PROGMEM {name}[] = {{
{data}
}};

#endif
"""




parser = argparse.ArgumentParser()      
parser.add_argument('file', type=argparse.FileType('rb'), nargs='+')
args = parser.parse_args()

def process(f):
    im = Image.open(f)
    im = im.convert('RGBA')

    rgb565_values = []
    for (r, g, b, a) in im.getdata():
        if a == 0:
            r, g, b = 31, 63, 31
        else:
            r, g, b = r // 8, g // 4, b // 8
        rgb565 = (r << 11) | (g << 5) | b

        rgb565_values.append(rgb565)

    rgb565_hex_text = ', '.join(['0x{0:04x}'.format(rgb565) for rgb565 in rgb565_values])

    var = re.sub(r'[\-\. :]','_', os.path.basename(os.path.splitext(f.name)[0]))
    out = open(var+'.h', 'w')
    source_result = code_template.format(name=var, width=im.width, height=im.height, data=rgb565_hex_text,file=f.name,size=im.size)
#    out.write("# HEX for file: "+f.name+", size: "
#    out.write("const unsigned int PROGMEM "+var+'[] = {\n')
#    out.write(rgb565_hex_text)
#    out.write("\n};\n\n")
    out.write(source_result)
    out.close()

#print (args.file)
for f in args.file:
    process(f)


