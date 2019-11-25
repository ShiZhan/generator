if [[ $# -lt 2 ]]; then
  echo "Usage: script <vertex scale> <average degree>"
  echo "E.g.: script 20 8"
  exit 1
fi

V=$[ 1 << $1 ] # vertex total in power of 2
D=$2           # average degree
M=$[ $V-1 ]    # vertex ID mask
S=$[ 18 ]                # block scale
B=$[ 1 << $S ]           # block size
C=$[ ($V*$D) >> ($S-3) ] # block total

if [[ $C -eq 0 ]]; then
  dd iflag=fullblock if=/dev/urandom bs=$[ $V*$D << 3 ] count=1 2> /dev/null
else
  dd iflag=fullblock if=/dev/urandom bs=$B count=$C 2> /dev/null
fi | od -An -w16 -vtu4 \
   | awk -v m=$M '{print and(m, $1)" "and(m, $2)"\n"and(m, $3)" "and(m, $4)}'
 
