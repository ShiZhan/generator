if [ $1 ]; then
    read S0 D0 S1 D1 <<< ${1//:/ }
else
    script_fn=$(basename "$0")
    echo "$script_fn <s0:d0:s1:d1>"
    echo "example: $script_fn 3:4:3:4"
    exit 1
fi
MAX_ID0=$(( (1 << S0) - 1 ))
IDS0=`seq 0 $MAX_ID0`
EDGE_FILE="r0-$S0-$D0-r1-$S1-$D1.edges"
DICT_FILE="$EDGE_FILE.dict"
# DICT_FILE="/dev/null"
cat \
    <(./rmat -s $S1 -d $D1 | while read u v
    do
        for i in $IDS0
        do
            echo "$i#"$u" $i#"$v
        done
    done) \
    <(./rmat -s $S0 -d $D0 | while read u v
    do
        echo $u"#0 "$v"#0"
    done) | \
shuf | \
awk -v dict_file=$DICT_FILE 'BEGIN { i=0 } {
    if (!($1 in dict)) dict[$1]=i++
    if (!($2 in dict)) dict[$2]=i++
    print dict[$1]" "dict[$2]
} END {
    for (i in dict) {
        print i" "dict[i] > dict_file
    }
}' > $EDGE_FILE
