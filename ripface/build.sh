gcc -ggdb `pkg-config --cflags opencv` -o findface findface.c `pkg-config --libs opencv`;

gcc -ggdb `pkg-config --cflags opencv` -o dumpface dumpface.c `pkg-config --libs opencv`;