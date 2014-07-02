import os,shutil,sys,time,fnmatch

def findface(arg, dirname, names):
    for old in names:
        filename = os.path.join(dirname,old)
        if os.path.isfile(filename):
            ext = os.path.splitext(old)
            if ext[0]!='log':
                # run command
                cmd = './findface '+filename+' '+os.path.join(dirname,'log.txt')+' '+ext[0]
                print cmd
                os.system(cmd)

def dumpface(arg, dirname, names):
    for old in names:
        if fnmatch.fnmatch(old,'log.txt'):
            newdir = os.path.join(os.path.dirname(dirname),os.path.basename(dirname)+'_head')
            #os.mkdir(newdir)
            cmd = './dumpface '+dirname+' '+newdir+' log.txt'
            print cmd
            os.system(cmd)

def videoface(arg, dirname, names):
    if fnmatch.fnmatch(dirname, '*_head'):
        for i in range(0,8):
            cmd = 'sh encode.sh '+dirname+' %03d' % i
            print cmd
            os.system(cmd)

start = time.time()
#os.path.walk(sys.argv[1],findface,[])
os.path.walk(sys.argv[1],dumpface,[])
#os.path.walk(sys.argv[1],videoface,[])
end = time.time()

t = (end-start)/60.0
print 'Total time elapsed: %0.3f minutes' % t
