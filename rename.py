import os,shutil,sys

def rename(arg, dirname, names):
    for old in names:
        if os.path.isfile(os.path.join(dirname,old)):
            new = old+'.jpg'
            shutil.move(os.path.join(dirname,old),os.path.join(dirname,new))


os.path.walk('photos',rename,[])
