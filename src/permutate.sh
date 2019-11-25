EDGES_FILE=$1
MAP_FILE=$2
if [ -z $EDGES_FILE ]; then
    echo "Usage: script <edge list> <vertex map>"
    exit 1
fi
if [ $MAP_FILE ]; then
    awk -v dict_file=$GRAPH_EDGES".dict" 'FNR == NR {
        dict[$1] = NR-1
        i=NR
        next
    } {
        if (!($1 in dict)) dict[$1]=i++
        if (!($2 in dict)) dict[$2]=i++
        print dict[$1]" "dict[$2]
    } END {
        for (i in dict) {
            print i" "dict[i] > dict_file
        }
    }' $MAP_FILE $GRAPH_EDGES
else
    awk -v dict_file=$GRAPH_EDGES".dict" 'BEGIN { i=0 } {
        if (!($1 in dict)) dict[$1]=i++
        if (!($2 in dict)) dict[$2]=i++
        print dict[$1]" "dict[$2]
    } END {
        for (i in dict) {
            print i" "dict[i] > dict_file
        }
    }' $GRAPH_EDGES
fi
