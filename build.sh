SUDOKU_DIR=$PWD
BUILD_DIR=$SUDOKU_DIR/build
SOURCE_DIR=$SUDOKU_DIR/source
SCRIPTS_DIR=$SUDOKU_DIR/scripts
LIB=sudoku.cpython-36m-x86_64-linux-gnu.so

mkdir $BUILD_DIR

cd $BUILD_DIR
cmake $SOURCE_DIR
cmake --build .

cd $SCRIPTS_DIR
echo 
if test -f "$LIB"; then
	rm "$LIB"
fi

ln -s "../build/$LIB" .

cd $SUDOKU_DIR
