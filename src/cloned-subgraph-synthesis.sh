S0=4
D0=4
S1=4
D1=4
IDS0=`seq 0 $[ (1 << S0) - 1 ]`
MAP_FILE="vertices.map"
# MAP_FILE="/dev/null"
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
awk -v map_file=$MAP_FILE 'BEGIN { i=0 } {
    if (!($1 in dict)) dict[$1]=i++
    if (!($2 in dict)) dict[$2]=i++
    print dict[$1]" "dict[$2]
} END {
    for (i in dict) {
        print i" "dict[i] > map_file
    }
}' > graph.edges
