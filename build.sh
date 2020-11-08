SUDOKU_DIR=$PWD
BUILD_DIR=$SUDOKU_DIR/build
SOURCE_DIR=$SUDOKU_DIR/source
SCRIPTS_DIR=$SUDOKU_DIR/scripts
TESTS_DIR=$SUDOKU_DIR/tests
LIB=sudoku.cpython-36m-x86_64-linux-gnu.so

mkdir $BUILD_DIR

cd $BUILD_DIR

# Building
cmake $SOURCE_DIR
cmake --build .

# Making a link in the scripts directory
cd $SCRIPTS_DIR
echo 
if test -f "$LIB"; then
	rm "$LIB"
fi
ln -s "../build/$LIB" .

# Making a link in the tests directory
cd $TESTS_DIR
echo 
if test -f "$LIB"; then
	rm "$LIB"
fi
ln -s "../build/$LIB" .

# Going back to original dir
cd $SUDOKU_DIR
