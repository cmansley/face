
find $1 -name *_$2_head.jpg > fromfile
find $1 -name *_$2_head.jpg | sed -e 's/.*\([a-z]\{4\}\).*\([0-9]\{3\}\)_[0-9].*/\2.jpg/' > tofile
find $1 -name *_$2_head.jpg | sed -e 's/.*/cp/' > cmdfile

#shuf < tofile > tofilerand

paste cmdfile fromfile tofilerand > bashfile

rm cmdfile fromfile tofile tofilerand

sh bashfile

rm bashfile

outfile=$(echo $1 | sed 's/.*\([a-z]\{4\}[012]\).*/\1/')_$2_norm

python qt.py $outfile.mov 1 25 true *.jpg

rm *.jpg