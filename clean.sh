find temp -name *_head -exec rm -Rf '{}' \; -print
find temp -type f -not -name *.jpg -exec rm '{}' \; -print