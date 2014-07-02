mencoder mf://$1/*_$2_*.jpg -mf w=256:h=256:fps=25:type=jpg -o /dev/null  -ovc x264 \
-x264encopts pass=1:turbo:bitrate=900:bframes=1:\
me=umh:partitions=all:trellis=1:qp_step=4:qcomp=0.7:direct_pred=auto:keyint=300 \
-vf harddup -oac faac -faacopts br=192:mpeg=4:object=2 -channels 2 -srate 48000 \
> /dev/null 2> /dev/null

mencoder mf://$1/*_$2_*.jpg -mf w=256:h=256:fps=25:type=jpg -o $1/output$2.avi  -ovc x264 \
-x264encopts pass=2:turbo:bitrate=900:frameref=5:bframes=1:\
me=umh:partitions=all:trellis=1:qp_step=4:qcomp=0.7:direct_pred=auto:keyint=300 \
-vf harddup -oac faac -faacopts br=192:mpeg=4:object=2 -channels 2 -srate 48000 \
> /dev/null 2> /dev/null

mplayer $1/output$2.avi -dumpaudio -dumpfile $1/output$2.aac > /dev/null 2> /dev/null
mplayer $1/output$2.avi -dumpvideo -dumpfile $1/output$2.h264 > /dev/null 2> /dev/null

mp4creator -create=$1/output$2.aac $1/output$2.mp4 > /dev/null 2> /dev/null
mp4creator -create=$1/output$2.h264 -rate=23.976 $1/output$2.mp4 > /dev/null 2> /dev/null

rm $1/output$2.aac $1/output$2.avi $1/output$2.h264 divx2pass.log