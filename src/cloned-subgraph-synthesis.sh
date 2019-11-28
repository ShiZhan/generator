if [ $1 ]; then
    read S0 D0 S1 D1 <<< ${1//:/ }
else
    echo "cloned-subgraph-synthesis.sh <s0:d0:s1:d1>"
    echo "  example:                    3:4:3:4"
    exit 1
fi
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
RMAT="$DIR/rmat"
MAX_ID0=$(( (1 << S0) - 1 ))
IDS0=`seq 0 $MAX_ID0`
EDGE_FILE="r0-$S0-$D0-r1-$S1-$D1.edges"
DICT_FILE="$EDGE_FILE.dict"
# DICT_FILE="/dev/null"
cat \
    <($RMAT -s $S0 -d $D0 | while read u v
    do
        echo $u"#0 "$v"#0"
    done) \
    <($RMAT -s $S1 -d $D1 | while read u v
    do
        for i in $IDS0
        do
            echo "$i#"$u" $i#"$v
        done
    done) | \
awk -v dict_file=$DICT_FILE 'BEGIN { i=0 } {
    if (!($1 in dict)) dict[$1]=i++
    if (!($2 in dict)) dict[$2]=i++
    print dict[$1]" "dict[$2]
} END {
    for (i in dict) {
        print i" "dict[i] > dict_file
    }
}' > $EDGE_FILE
