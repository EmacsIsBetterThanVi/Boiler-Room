if [[ $BOILERROOMPREFIX != "" ]]; then
BOILERROOMPREFIX="~/.local/bin/BoilerRoom/"
fi
prg = $1
shift
socketpath = $1
shift
$BOILERRROOMPREFIX$prg init $socketpath $@ &