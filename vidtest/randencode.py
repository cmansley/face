def encode(arg, dirname, names):
    if fnmatch.fnmatch(dirname, 'sa1_head'):
        for i in range(0,8):
            cmd = 'sh rand.sh '+dirname+' %03d' % i
            print cmd
            os.system(cmd)

start = time.time()
os.path.walk(sys.argv[1],encode,[])
end = time.time()

t = (end-start)/60.0
print 'Total time elapsed: %0.3f minutes' % t
