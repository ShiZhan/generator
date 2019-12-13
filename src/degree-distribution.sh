awk '{ counter[$1]++; counter[$2]++ } END { for (c in counter) { print counter[c] } }' $@ | \
awk '{ counter[$0]++ } END { for (c in counter) { print c","counter[c] } }'