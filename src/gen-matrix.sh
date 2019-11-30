S=6
D=8
[ $1 ] && S=$1
[ $2 ] && D=$2
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
RMAT="$DIR/rmat"
N=$(( 1 << S ))
MAX_ID=$(( N - 1 ))
SET_ID=`seq 0 $MAX_ID`

sort -m -n -k1 -k2 \
    <(
        for i in $SET_ID; do
            for j in $SET_ID; do
                echo "$i $j"
            done
        done
    ) \
    <(
        $RMAT -s $S -d $D | sort -n -k1 -k2
    ) | uniq -c | \
(
    i=1
    while read l u v; do
        [ $l == 1 ] && printf "0" || printf "1"
        [ $[ i % N ] == 0 ] && printf "\n" || printf ","
        i=$[ i + 1 ]
    done
)