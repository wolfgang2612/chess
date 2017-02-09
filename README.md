# chess
1v1 offline chess game designed in Windows Forms

static Global variables:
whiteBrush : brush for board
blackBrush : brush for board
g : graphics object
height : height of icons
width : width of icons
cellHt : height of cells
cellWd : width of cells
offsetX : x-offset for picturbox
offsetY : y-offset for picturebox
thickPinkPen : Pen for selected piece outline
thickBluePen : Pen for available move outline
thickRedPen : Pen for available kill outline

Global Variables
int: click
bool: whiteTurn
managed CLI 2-d int array: board

static Global functions:
drawBoard : void return type.
	    draws the chessboard
Global functions:
drawPieces : void return type.
	     draws the pieces which are alive on the board
update : void return type.
	 refreshes picturebox,calls drawBoard calls drawPieces
kill: void return type.
      sets the alive status of the piece on specified square as false

board array value definitions					corresponding white pieces
//0 = unoccupied						                        //
//pawn black left to right is 1-8 p1-p8				      //17-24
//black rook left is 9, right is 10 r1-r2			      //25,26
//knight left black 11, right 12 kn1-kn2			      //27,28
//bishop left black 13,right 14	bishop1-bishop2			//29,30
//queen black 15,king 16					                  //31,32	
