#!/bin/bash

folder=$1

cat <<EOF>$2
#ifndef IMAGES_H_
# define IMAGES_H_

# include <3ds.h>

EOF

for f in $folder/*.png; do
    fr=$(file $f)
    ff=$(basename $f | sed -r 's/^(.*)\.[^.]+$/\1/')
    FF=$(echo "$ff" | tr '[a-z]\-\.' '[A-Z]__')
    echo '# include "'$ff'_bgr.h"' >>$2
    w=$(echo "$fr" | sed -r 's/[^,]+, ([0-9]+).*/\1/')
    h=$(echo "$fr" | sed -r 's/[^,]+, [0-9]+ x ([0-9]+).*/\1/')
    echo '# define I_'$FF'_W '$w >>$2
    echo '# define I_'$FF'_H '$h >>$2
done

echo -e '\n#endif' >>$2